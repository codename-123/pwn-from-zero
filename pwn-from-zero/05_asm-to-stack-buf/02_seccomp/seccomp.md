# seccomp 분석

이 문서는 seccomp 필터가 적용된 바이너리에서 쉘코드를 직접 입력해 실행하는 구조를 분석한 기록입니다. 시스템콜 필터링 우회와 메모리 매핑 기반 쉘코드 실행을 이해하는 데 목적이 있습니다.

## 원본 C코드 요약

```c
void main(int argc, char *argv[]) {
  char *shellcode = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  init();              // 출력 버퍼 제거 + 10초 타임아웃 설정
  banned_execve();     // execve, execveat 시스템콜 차단 (seccomp 필터)

  printf("shellcode: ");
  read(0, shellcode, 0x1000);   // 사용자가 입력한 shellcode를 메모리에 저장

  ((void(*)())shellcode)();     // shellcode 실행
}
```

---

## 어셈블리 해석

### main

```asm
0x5555555552dc <main+15>    mov    r9d, 0 
``` 

- `r9d` 레지스터에 정수 `0` 복사
- `r9d`는 mmap 함수의 여섯 번째 인자로 사용

```asm
0x5555555552e2 <main+21>    mov    r8d, 0xffffffff
```

- `r8d` 레지스터에 `0xffffffff`값 복사
- `r8d`는 mmap 함수의 다섯 번째 인자로 사용

```asm
0x5555555552e8 <main+27>    mov    ecx, 0x22 
```

- `ecx` 레지스터에 `0x22` 값 복사
- `ecx`는 mmap 함수의 네 번째 인자로 사용

```asm
0x5555555552ed <main+32>    mov    edx, 7
```

- `edx` 레지스터에 `7` 값 복사
- `edx` 는 mmap 함수의 세 번째 인자로 사용

```asm
0x5555555552f2 <main+37>    mov    esi, 0x1000
```

- `esi` 레지스터에 `0x1000` 값 복사
- `esi` 는 mmap 함수의 두 번째 인자로 사용

```asm
0x5555555552f7 <main+42>    mov    edi, 0
```

- `edi` 레지스터에 `0` 값 복사
- `edi` 는 mmap 함수의 첫 번째 인자로 사용

```asm
 ► 0x5555555552fc <main+47>    call   mmap@plt                    <mmap@plt>
        addr: 0
        len: 0x1000
        prot: 7
        flags: 0x22 (MAP_PRIVATE|MAP_ANONYMOUS)
        fd: 0xffffffff
        offset: 0
```

- prot가 가르키는 것:
    - PROT_READ: `1`
    - PROT_WRITE: `2`
    - PROT_EXEC: `4` → 최종 값 `7`
> **mmap(null, 0x1000, 7, 0x22 (MAP_PRIVATE|MAP_ANONYMOUS), 0xffffffff(-1), 0);**

```asm
0x555555555301 <main+52>    mov    qword ptr [rbp - 8], rax
```
- 현재 `rbp`의 값: `0x7fffffffdd50`
- `qword ptr [rbp - 8]` 값 연산 → `0x7fffffffdd50` - `8(0x8)` = `0x7fffffffdd48`
- 현재 `rax`의 값: `0x7ffff7fbe000` (mmap 호출의 리턴값으로, 운영체제에서 할당된 메모리 주소로 추정됨)
> 결론: `rax`값 `0x7ffff7fbe000` 을 `0x7fffffffdd48` 주소 에게 복사 → **최종 스택 `0x7fffffffdd48` 주소 안의 값 = `0x7ffff7fbe000`**

```asm
0x555555555305 <main+56>    mov    eax, 0 
```

- `init` 함수 호출 직전 상태 `eax` 레지스터 `0` 으로 초기화.
- 보통 시스템 호출 전 반환값 설정 또는 인자 클리어 용도로 사용

```asm
0x55555555530a <main+61>    call   init
```

- `init` 함수 호출

---

#### init

```asm
0x5555555551f6 <init>       push   rbp
```

- 현재 `rbp`의 값: `0x7fffffffdd50`
- `rbp` 레지스터의 값을 스택(stack)에 저장
- **현재 함수가 끝난 뒤, 이전 함수로 정확하게 돌아가기 위한 기준점 저장**

```asm
0x5555555551f7 <init+1>     mov    rbp, rsp
```

- 현재 `rsp`의 값을 `rbp`에 복사
- 함수 `init`의 새로운 스택 프레임 기준을 설정함
- 이전에 실행된 `push rbp` 이전 함수(main)의 스택 프레임은 보존된 상태
- 현재 `mov rbp, rsp` 새로운 스택 프레임으로 전환.

```asm
0x5555555551fa <init+4>     mov    rax, qword ptr [rip + 0x2e7f]
```

- 다음 명령어의 `rip`의 값: `0x555555555201`
- `qword ptr [rip + 0x2e7f]` 연산 → `0x555555555201` + `0x2e7f` = `0x555555558080`
- `0x555555558080` 주소 검색: **`0x555555558080` <stdin@GLIBC_2.2.5> =     `0x00007ffff7f6b8e0`(glibc의 `_IO_2_1_stdin_` 구조체 주소)**
- `qword ptr [rip + 0x2e7f]` 주소에 `0x00007ffff7f6b8e0` 이 값을 `rax` 레지스터 에게 복사

```asm
0x555555555201 <init+11>    mov    ecx, 0
```

- `ecx` 레지스터에 정수 `0` 복사
- `ecx`는 setvbuf 함수의 네 번째 인자 사용

```asm
0x555555555206 <init+16>    mov    edx, 2
```

- `edx` 레지스터에 정수 `2` 복사
- `edx` 는 setvbuf 함수의 세 번째 인자 사용

```asm
0x55555555520b <init+21>    mov    esi, 0
```

- `esi` 레지스터에 정수 `0` 복사
- `esi` 는 setvbuf 함수의 두 번째 인자 사용

```asm
0x555555555210 <init+26>    mov    rdi, rax
```

- 현재 `rax` 레지스터의 값: `0x7ffff7f6b8e0 (_IO_2_1_stdin_)`
- `rax` 의 값을 `rdi` 레지스터 에게 복사
- `rdi`는 setvbuf 함수의 첫 번재 인자 사용

```asm
0x555555555213 <init+29>    call   setvbuf@plt
```

> **setvbuf(0x7ffff7f6b8e0 (_IO_2_1_stdin_), 0, 2, 0);**

```asm
0x555555555218 <init+34>    mov    rax, qword ptr [rip + 0x2e51]
```

- 다음 명령어 `rip`의 값: `0x55555555521f`
- `qword ptr [rip + 0x2e51]` 연산 → `0x55555555521f` + `0x2e51` = `0x555555558070`
- `0x555555558070` 주소의 값 확인: **`0x555555558070` <stdout@GLIBC_2.2.5>:    `0x00007ffff7f6c5c0` (_IO_2_1_stdout_)의 구조체 주소`**
- `0x00007ffff7f6c5c0` 이 주소를 `rax` 레지스터에게 전달

위와 같음
1. `ecx` = 0
2. `edx` = 2
3. `esi` = 0
4. `rdi` = `0x00007ffff7f6c5c0`

```asm
0x555555555231 <init+59>    call   setvbuf@plt
```
> **setvbuf(0x00007ffff7f6c5c0` (_IO_2_1_stdout_), 0, 2, 0);**

```asm
0x555555555236 <init+64>    lea    rax, [rip - 0x64]
```

- `rip`는 해당 명령어 기준 다음 주소인 `0x55555555523d`를 기준으로 함
- `[rip - 0x64]` → `0x55555555523d` - `0x64` = `0x5555555551d9`
- `rax`에는 주소 `0x5555555551d9`가 저장됨
- `0x5555555551d9` 주소 안의 값: **`0x5555555551d9` <alarm_handler>: `0x20058d48e58948558`**

```asm
0x55555555523d <init+71>    mov    rsi, rax 
```
 
- 현재 `rax`의 값: `0x5555555551d9`
- `rax` 값 을 `rsi` 레지스터 에게 복사
- `rsi`는 signal 함수의 두 번째 인자

```asm
0x555555555240 <init+74>    mov    edi, 0xe
```

- `0xe`의 값을 `edi`에게 복사
- `edi`는 signal 함수의 첫 번째 인자

```asm
0x555555555245 <init+79>    call   signal@plt
```

> **signal(0xe(14), 0x5555555551d9<alarm_handler>);**

```asm
0x55555555524a <init+84>          mov    edi, 0xa
```

- `0xa` 값을 `edi` 레지스터에게 복사
- `edi`는 첫 번째 인자

```asm
0x55555555524f <init+89>          call   alarm@plt
```

> **alarm(0xa(10));**

최종 함수 
```c
setvbuf(0x7ffff7f6b8e0 (_IO_2_1_stdin_), 0, 2, 0);
setvbuf(0x00007ffff7f6c5c0` (_IO_2_1_stdout_), 0, 2, 0);
signal(0xe(14), 0x5555555551d9<alarm_handler>);
alarm(0xa(10));
```

```asm
0x555555555254 <init+94>    nop    
0x555555555255 <init+95>    pop    rbp     RBP => 0x7fffffffdd50
0x555555555256 <init+96>    ret                                <main+66>
```

- 함수 종료 루틴으로, 저장했던 `rbp`를 복원하고 `ret`으로 `main` 함수로 복귀함.

---

### main

```asm
0x55555555530f <main+66>    mov    eax, 0
```

- `eax` 값을 `0`으로 복사 (호출 전 초기화 용도)

```asm
0x555555555314 <main+71>    call   banned_execve
```

- `banned_execve` 함수 호출

---

#### banned_execve

```asm
0x555555555257 <banned_execve>       push   rbp 
0x555555555258 <banned_execve+1>     mov    rbp, rsp
```

- `push rbp`: 현재 함수가 끝난 뒤, 이전 함수로 정확하게 돌아가기 위한 기준점 저장
- `mov rbp, rsp`: 새로운 스택 프레임으로 전환

```asm
0x55555555525b <banned_execve+4>     sub    rsp, 0x10
```

- `rsp(스택)` 공간에 `0x10(16 바이트)` 확보

```asm
0x55555555525f <banned_execve+8>     mov    edi, 0x7fff0000
```

- `0x7fff0000` 값을 `edi` 레지스터 에게 복사
- `edi`는 첫 번째 인자

```asm
0x555555555264 <banned_execve+13>    call   seccomp_init@plt            
```

> **seccomp_init(0x7fff0000);**

- 결론: 현재 흐름은 seccomp 보안 필터링 정책을 초기화하려는 준비 단계이며,
`execve()` 차단을 위한 필터가 이어질 가능성이 크다.

```asm
0x555555555269 <banned_execve+18>    mov    qword ptr [rbp - 8], rax
```

- 현재 `rbp`의 값: `0x7fffffffdd20`
- `qword ptr [rbp - 8]` 연산 수행 → `0x7fffffffdd20` - `0x8(8)` = `0x7fffffffdd18`
- 현재 `rax`의 값: `0x5555555592a0` **(seccomp_init() 호출 결과로 받은 포인터로 추정)**
- 주소 `0x7fffffffdd18` 에게 `rax` 레지스터 값 `0x5555555592a0` 복사
- `0x7fffffffdd18` == `0x5555555592a0`

```asm
0x55555555526d <banned_execve+22>    cmp    qword ptr [rbp - 8], 0
```

- `[rbp - 8]` = `0x7fffffffdd18`
- 현재 `qword ptr [rbp - 8]`주소의 값: `0x5555555592a0`
- `cmp` 명령어 연산 (플래그 레지스터 동작)
- `0x5555555592a0` - `0x0` 

```asm
0x555555555272 <banned_execve+27>  ✔ jne    banned_execve+39
```

- `cmp` 연산 결과가 0일 경우 `Zero Flag(ZF)` 켜짐
- `0x5555555592a0` - `0x0` 결과 0이 아님
- `Zero Flag(ZF)` 꺼진 상태 → `jne` 조건 만족 → **banned_execve+39로 분기**

```asm
0x55555555527e <banned_execve+39>    mov    rax, qword ptr [rbp - 8]
```

- `[rbp - 8]` = `0x7fffffffdd18`
- 현재 `qword ptr [rbp - 8]`주소의 값: `0x5555555592a0`
- `0x5555555592a0` 값을 `rax` 레지스터 에게 복사

```asm
0x555555555282 <banned_execve+43>    mov    ecx, 0
```

- `ecx` 레지스터 에게 `0`의 정수를 복사
- `ecx`는 네 번째 인자

```asm
0x555555555287 <banned_execve+48>    mov    edx, 0x3b
```

- `edx` 레지스터 에게 `0x3b`의 정수를 복사
- `edx`는 세 번째 인자

```asm
0x55555555528c <banned_execve+53>    mov    esi, 0
```

- `esi` 레지스터에게 `0`의 정수를 복사
- `esi`는 두 번째 인자

```asm
0x555555555291 <banned_execve+58>    mov    rdi, rax
```

- 현재 `rax`의 값: `0x5555555592a0`
- `0x5555555592a0` 값을 `rdi` 레지스터에게 복사
- `rdi`는 첫 번째 인자

```asm
0x555555555294 <banned_execve+61>    mov    eax, 0
```

- `eax` 레지스터에 `0`의 정수를 복사
- `eax = 0`은 호출 규약상 **하위 인자 레지스터(r9d 등)를 초기화하는 가장 효율적인 방법**

```asm
0x555555555299 <banned_execve+66>    call   seccomp_rule_add@plt
```

> **seccomp_rule_add(0x5555555592a0(0x7fff0000a1b2c3d4), 0, 0x3b(59), 0);**
> → execve syscall을 호출하면 죽이도록(kill) 필터 규칙을 추가

```asm
0x5555555552a2 <banned_execve+75>    mov    ecx, 0                       ECX => 0
0x5555555552a7 <banned_execve+80>    mov    edx, 0x142                   EDX => 0x142
0x5555555552ac <banned_execve+85>    mov    esi, 0                       ESI => 0
0x5555555552b1 <banned_execve+90>    mov    rdi, rax                     RDI => 0x5555555592a0 ◂— 0x7fff0000a1b2c3d4
0x5555555552b4 <banned_execve+93>    mov    eax, 0                       EAX => 0
```

- `edx` 레지스터에 `0x142`의 값 복사
- 위와 같음

```asm
0x5555555552b9 <banned_execve+98>     call   seccomp_rule_add@plt
```

> **seccomp_rule_add(0x5555555592a0(0x7fff0000a1b2c3d4), 0, 0x142(322), 0);**

```asm
0x5555555552be <banned_execve+103>    mov    rax, qword ptr [rbp - 8]                                                                             
0x5555555552c2 <banned_execve+107>    mov    rdi, rax                 
```

- `qword ptr [rbp - 8]` 값: `0x5555555592a0(0x7fff0000a1b2c3d4)`
- `rax` 레지스터에게 `qword ptr [rbp - 8]` 주소 안의 값을 복사 한 후, `rdi` 레지스터에게 복사
- `rdi`는 첫 번째 인자

```asm
0x5555555552c5 <banned_execve+110>    call   seccomp_load@plt
```

> **seccomp_load(0x5555555592a0(0x7fff0000a1b2c3d4));**

최종 함수

```c
ctx/*0x5555555592a0(내부 값: 0x7fff0000a1b2c3d4)*/ = seccomp_init(0x7fff0000);
if ctx == 0 {
    exit(0);
}
seccomp_rule_add(0x5555555592a0(0x7fff0000a1b2c3d4) /*ctx*/, 0, 0x3b(59) /*execve*/, 0);
seccomp_rule_add(0x5555555592a0(0x7fff0000a1b2c3d4) /*ctx*/, 0, 0x142(322) /*execveat*/, 0);

seccomp_load(0x5555555592a0(0x7fff0000a1b2c3d4) /*ctx*/);
```

```asm
0x5555555552ca <banned_execve+115>    nop    
0x5555555552cb <banned_execve+116>    leave  
0x5555555552cc <banned_execve+117>    ret                                <main+76>

```

- 함수 종료 루틴으로, 저장했던 `rbp`를 복원하고 `ret`으로 `main` 함수로 복귀함.

---

### main

```asm
0x555555555319 <main+76>              lea    rax, [rip + 0xced]
```

- 다음 `rip` 명령어 주소: `0x555555555320`
- `[rip + 0xced]` 연산 수행 → `0x555555555320` + `0xced` = `0x55555555600d`
- `0x55555555600d` 주소 안의 값 검색 → `0x55555555600d`: `"shellcode: "`
- `rax` 레지스터에게 `0x55555555600d` 주소 값 복사.

```asm
0x555555555320 <main+83>              mov    rdi, rax
```

- `rdi` 레지스터 에게 `rax` 값 복사.
- `rdi` 는 첫 번째 인자

```asm
0x555555555323 <main+86>              mov    eax, 0
```

- `eax` 레지스터 `0`으로 초기화
- 가변 인자 함수(`printf`, `scanf`, `execl` 등) 호출 시 AL 레지스터 초기화 관례 `(eax = 0)`.

```asm
0x555555555328 <main+91>              call   printf@plt
```

- `printf` 함수 호출
> **최종 값: printf("shellcode: ")**

```
0x55555555532d <main+96>              mov    rax, qword ptr [rbp - 8]
```

- 현재 `rbp` 레지스터 값: `0x7fffffffdd50`
- `qword ptr [rbp - 8]` 연산 수행 → `0x7fffffffdd50` - `0x8(8)` = `0x7fffffffdd48`
- `0x7fffffffdd48` 주소의 내부 값 분석: **`0x7fffffffdd48`: `0x00007ffff7fbe000` (이전 mmap() 호출로 할당된 메모리 주소)**
- `rax` 레지스터 에게 `0x00007ffff7fbe000` 값을 복사

```asm
0x555555555331 <main+100>    mov    edx, 0x1000 
```

- `edx` 레지스터에게 `0x1000`값을 복사
- `edx` 는 세 번째 인자

```asm
0x555555555336 <main+105>    mov    rsi, rax
```

- `rax` 레지스터 값을 `rsi`레지스터 에게 복사
- `rsi` 은 두 번째 인자

```asm
0x555555555339 <main+108>    mov    edi, 0
```

- `edi` 레지스터에게 정수 `0`을 복사
- `edi` 는 첫 번째 인자

```asm
0x55555555533e <main+113>    call   read@plt
```

- `read` 함수 호출
> **read(0(stdin), 0x00007ffff7fbe000, 0x1000(4096 bytes));**

```asm
0x555555555343 <main+118>    mov    rax, qword ptr [rbp - 8]
0x555555555347 <main+122>    mov    qword ptr [rbp - 0x10], rax
0x55555555534b <main+126>    mov    rdx, qword ptr [rbp - 0x10]
0x55555555534f <main+130>    mov    eax, 0
0x555555555354 <main+135>    call   rdx
```

- 이전에 저장해둔 `mmap()` 주소 (`0x7ffff7fbe000`)를 다시 꺼내어
- `rdx`에 전달하고 `call rdx`로 입력받은 쉘코드를 실행.

---

## 쉘 코드 얻기

- 지금까지 얻은 내용을 토대로 쉘 코드 얻기
  - seccomp 필터가 execve (0x3b)와 execveat (0x142)만 차단하고 있음,
  그 외의 시스템 콜 (`open(2)`, `read(0)`, `write(1)`)은 정상 작동 가능
  - `read(0, 0x00007ffff7fbe000, 0x1000)` 호출을 통해 **최대 4096 바이트**까지 shellcode 입력이 가능함.

[작성한 쉘코드 (shellcode.asm)](./shellcode.asm)
