# orw 시스템 콜 분석 (open → read → write)

## 원본 C코드 요약

```c
int fd = open("/tmp/flag", O_RDONLY);
read(fd, buf, 48);
write(1, buf, len);
```

---

## 어셈블리 해석

### 함수 진입부

```asm
0x55555555516d <main+4>     sub    rsp, 0x40 
```
- `rsp`에서 64바이트(0x40)만큼 스택 공간 확보

---

### open


```asm
0x555555555171 <main+8>     mov    esi, 0 
```

- syscall 두번 째 인자 **0** `esi`에게 전달, syscall 규약에 따라 `rsi`로 전달

```asm 
0x555555555176 <main+13>    lea    rax, [rip + 0xe87]
```

- **rax = 0x55555555517d + 0xe87 = 0x555555556004**
- `0x555555556004` 메모리에 있는 문자열을 `rax`에게 전달
- `0x555555556004` 메모리 안에 `'/tmp/flag'` 존재

```asm 
0x55555555517d <main+20>    mov    rdi, rax
```

- `rax`의 값: '/tmp/flag'
- `rdi`에게 전달 → `rdi` = `'/tmp/flag'`
- syscall 첫번 째 인자 **/tmp/flag**

```asm
0x555555555180 <main+23>    mov    eax, 0
```

- `eax`의 값 **0** 저장. (컴파일러가 함수 호출 전에 쓰는 더미 초기화)

```asm
0x555555555185 <main+28>    call   open@plt                  
    file: 0x555555556004 ◂— '/tmp/flag'
    oflag: 0
    vararg: 0x7fffffffde88 —▸ 0x7fffffffe212 ◂— 'COLORFGBG=15;0'
```
- `call open@plt` → glibc open() 함수 → 내부에서 `syscall(2, ...)` → syscall **2** 호출

최종 `open` syscall 호출 → **open("/tmp/flag", 0);**

---

### open-if 문

```asm
0x55555555518a <main+33>    mov    dword ptr [rbp - 4], eax
```

- 현재 `rbp`의 값 = `0x7fffffffdd60`
- `rbp`에서 4를 뺀 위치 → `0x7fffffffdd5c`
- 이 위치에 `eax` 값인 `0xffffffff`를 저장함
- `dword`는 4바이트 단위 저장을 의미 (eax가 4바이트이기 때문)

```asm
0x55555555518a <main+33>    cmp    dword ptr [rbp - 4], 0 
```

- `rbp`에서 4를 뺀 위치 → `0x7fffffffdd5c` 안에 들어있는 값 = `0xffffffff`

- `[rbp - 4]의 값: 0xffffffff` → 이진수: 11111111 11111111 11111111 11111111
- 부호 있는 해석 기준: -1
- 연산 수행: -1 - 0 = -1
- 결과는 음수이므로 **Sign Flag(SF) = 1**

```asm
0x555555555191 <main+40>  ✘ jns    main+67
```

- `jns` = **Sign Flag(SF) 영향**
- 앞선 `cmp` 결과, SF = 1 (음수) → 조건 불충족
- 따라서 점프하지 않고 아래 에러 처리 루틴으로 흐름 진행됨 (→ `perror("open"); return 1;`)

---

### perror

```asm
0x555555555193 <main+42>     lea    rax, [rip + 0xe74]
```

- 현재 `rip` 주소 = `0x555555555193`
- `0x0e74`를 더한 주소 = `0x555555555193 + 0xe74 = 0x555555556007`
- `0x555555556007` 이 주소에 들어있는 값: `0x616572006e65706 (리틀 엔디안 저장)` 
- 실제 메모리: **70 65 6e 00 72 65 61 00** → ASCII = `"pen\0rea\0"`
- 실제 값: pwndbg> x/s 0x55555555600e → `0x55555555600e: "open"`

```asm
0x55555555519a <main+49>     mov    rdi, rax
```

- `rax`에 저장된 값 (**문자열 `"open"`의 주소**): `0x55555555600e`
- `rdi`에게 복사 → `rdi`에 저장된 값: `0x55555555600e`
- 이는 `perror("open")` 호출을 위한 첫 번째 인자 세팅

```asm
0x55555555519d <main+52>     call   perror@plt
```

- `rdi`에 "open" 문자열 주소 (`0x55555555600e`)가 세팅되어 있음
- `perror("open")` 함수 호출을 수행

```asm
0x5555555551a2 <main+57>     mov    eax, 1
```
- `eax`에 1을 저장 (하위 32비트 레지스터)
- 리눅스 x86-64에서 `main()` 함수의 반환값은 `eax`로 전달됨
- 따라서 이는 `return 1;`을 의미함

```asm
0x5555555551a7 <main+62>: jmp main+196
```

- 정상 실행 흐름인 경우, 종료 루틴으로 점프
- 이후 `leave` → `ret` 를 통해 함수 종료 수행

---

### read

```asm
0x5555555551ac <main+67>     mov    qword ptr [rbp - 0x40], 0     
0x5555555551b4 <main+75>     mov    qword ptr [rbp - 0x38], 0      
0x5555555551bc <main+83>     mov    qword ptr [rbp - 0x30], 0
0x5555555551c4 <main+91>     mov    qword ptr [rbp - 0x28], 0    
0x5555555551cc <main+99>     mov    qword ptr [rbp - 0x20], 0    
0x5555555551d4 <main+107>    mov    qword ptr [rbp - 0x18], 0     
```
- `buf[48] = { 0 };` 에 해당하는 어셈블리
- 8바이트 단위(qword)로 **총 6번 메모리를 0으로 초기화**
- 스택 상의 버퍼 초기화를 최적화된 방식으로 처리함

```asm
0x5555555551dc <main+115>    lea    rcx, [rbp - 0x40] 
```

- 현재 `rbp`의 값: `0x7fffffffdd60`
- `rbp` - `0x40` = `0x7fffffffdd20`
- `lea` 명령어로 `rcx` 레지스터에 `0x7fffffffdd20` 이 주소값을 저장

```asm
0x5555555551e0 <main+119>    mov    eax, dword ptr [rbp - 4]
```

- `dword ptr [rbp - 4]` → `0x7fffffffdd60` - `0x4` = `0x7fffffffdd5c`
- `0x7fffffffdd5c` 주소에 저장된 4바이트 값을 `eax` 레지스터 에게 전달
- 해당 메모리 주소의 값이 0이라면, `eax` = 0

```asm
0x5555555551e3 <main+122>    mov    edx, 0x30
```

- `edx` 레지스터 에게 0x30(48)의 값을 전달
- libc read 함수 호출 세 번째 인자

```asm
0x5555555551e8 <main+127>    mov    rsi, rcx
```

- 현재 `rcx`의 값: `0x7fffffffdd20`
- `rcx`의 값 을 `rsi` 레지스터 에게 전달
- `rsi` = `0x7fffffffdd20` 
- `rsi`는 libc read 함수 호출 두 번째 인자로 사용. 

```asm
0x5555555551eb <main+130>    mov    edi, eax
```

- 현재 `eax`의 값: `0`
- `eax`의 값 을 `edi` 레지스터 에게 전달
- `edi` = 0
- `edi`는 libc read 함수 호출 첫 번째 인자로 사용.

- 최종 인자 상태:
    - `edi` = 0               → 첫 번째 인자 = file descriptor (stdin)
    - `rsi` = 0x7fffffffdd20  → 두 번째 인자 = 버퍼 주소
    - `edx` = 0x30            → 세 번째 인자 = 바이트 수 (48)

```asm
0x5555555551ed <main+132>    call   read@plt                    <read@plt>
        fd: 0 (/dev/pts/0)
        buf: 0x7fffffffdd20 ◂— 0
        nbytes: 0x30
```

> **read(0, 0x7fffffffdd20, 0x30(48))**

---

### read-if문

```asm
0x5555555551f2 <main+137>    mov    qword ptr [rbp - 0x10], rax
```

- 현재 `rbp`의 값: `0x7fffffffdd60`
- `qword ptr [rbp - 0x10]` 연산 → `0x7fffffffdd60` - `0x10` = `0x7fffffffdd50`
- 현재 `rax`의 값: `1`
- `0x7fffffffdd50` 이 주소에 `rax` 레지스터의 값 `1` 삽입
- 따라서 [0x7fffffffdd50] 에 8바이트(qword) 크기로 값 `1`이 저장됨

```asm
0x5555555551f6 <main+141>    cmp    qword ptr [rbp - 0x10], 0
```

- `qword ptr [rbp - 0x10]`에 저장되있는 값 `1`
- `cmp` 명령어를 통하여 연산 수행 (결과는 플래그 레지스터에 저장)
- `1`-`0` 현재 양수의 값. **(Sign Flag (SF) 비활성화)**

```asm
0x5555555551fb <main+146>  ✔ jns    main+170
``` 

- Sign Flag (SF)은 비활성화 상태
- 따라서 `jns` 조건 만족 → 점프 수행됨

---

### write

```asm
mov    rdx, qword ptr [rbp - 0x10]
```

- `qword ptr [rbp - 0x10]`에 저장되있는 값 `1`
- `rdx` 레지스터 에게 qword(8바이트 값) `1`의 값을 복사
- `rdx` 값: `1`
- libc write 함수의 세 번째 인자

```asm
0x555555555217 <main+174>    lea    rax, [rbp - 0x40]
```

- 현재 `rbp`값: `0x7fffffffdd60`
- `[rbp - 0x40]` 연산 수행 → `0x7fffffffdd60` - `0x40` = `0x7fffffffdd20`
- `0x7fffffffdd20` 해당 주소값을 `rax` 레지스터에 로드

```asm
0x55555555521b <main+178>    mov    rsi, rax
```

- 현재 `rax`의 값: `0x7fffffffdd20`
- `0x7fffffffdd20` 값을 `rsi` 레지스터 에게 복사
- `rsi`의 값: `0x7fffffffdd20`
- libc write 함수의 두 번째 인자

```asm
0x55555555521e <main+181>    mov    edi, 1 
```

- `1`의 값을 하위 32비트 레지스터 `edi` 에게 복사
- `edi`의 값: `1`
-  libc write 함수의 첫 번째 인자

```asm
0x555555555223 <main+186>    call   write@plt
```

> **write(1, 0x7fffffffdd20, 1)**

```asm
0x555555555228 <main+191>    mov    eax, 0
```
- 반환값 설정 (`return 0`)
- `eax`는 함수 반환값을 담는 레지스터

- 이후 `leave` → `ret` 를 통해 함수 종료 수행