# 쉘코드 기초와 실전 활용 요약 정리

## Shellcode란?
- Shellcode는 어셈블리 명령어를 기계어로 컴파일한 뒤, 해당 기계어를 16진수(hex) 형태로 표현한 코드 조각입니다. 이 코드는 메모리에 적재되어 CPU가 직접 실행할 수 있으며, 일반적으로 공격자의 의도를 수행하는 매우 작은 크기의 바이너리입니다.

- 예를 들어 아래와 같은 NASM 코드:

```nasm
mov rsi, message
mov rdi, 1
mov rdx, 18
mov rax, 1
syscall
```

- 는 다음과 같은 shellcode로 변환됩니다:
```nasm
48be0020400000000000bf01000000ba12000000b8010000000f05b83c000000bf000000000f05
```

> 이처럼 shellcode는 기계어 레벨에서 직접 동작하기 때문에, 프로세서 아키텍처와 시스템 호출 구조를 정확히 이해하고 있어야 합니다.

---

## 침투 테스트에서의 활용
- **버퍼 오버플로우**와 같은 취약점을 이용해 shellcode를 삽입하여 공격자가 원하는 코드 실행
- 디스크에 기록 없이 **메모리 상에서 직접 실행** 가능 → 포렌식 탐지 회피
- ELF, .so, .dll 등의 실행 파일에 shellcode를 삽입해 **후킹 또는 트로이 목마화**
- Modern 시스템은 NX bit 등의 메모리 보호 기법이 있으므로, 우회 기술(예: ROP)도 함께 요구됨

---

## 어셈블리 → 기계어 변환 구조
- NASM 등의 어셈블러는 인간 친화적인 어셈블리어를 CPU가 이해 가능한 바이너리로 변환
- 예시:
  - `push rax` → `50`
  - `push rbx` → `53`

```bash
$ pwn asm 'push rax' -c amd64     # 50 출력
$ pwn disasm '50' -c amd64        # push rax 출력
```

---

## Shellcode 추출 방법

### 방법 1: Pwntools 사용
```python
from pwn import *
file = ELF('helloworld')
print(file.section(".text").hex())
```

### 방법 2: objdump + bash script
```bash
$ objdump -d binary | grep '^ ' | cut -f2 | tr -d '\n'
```

---

### Shellcode 실행 (Pwntools 사용)
```python
run_shellcode(unhex('4831db66bb...')).interactive()
```
해당 코드는 shellcode를 메모리에 로딩한 후, 직접 실행하여 결과를 확인할 수 있다.

#### 실행 스크립트 예시:
```python
#!/usr/bin/python3
import sys
from pwn import *
context(os="linux", arch="amd64", log_level="error")
run_shellcode(unhex(sys.argv[1])).interactive()
```

---

## Shellcode 디버깅 기법
### 1. 실행 중 attach
- loader.py를 실행 후, `ps aux | grep loader`를 통해 PID를 확인
- `gdb -p <PID>`로 attach

### 2. ELF 바이너리로 변환 후 GDB 디버깅
```python
from pwn import *
ELF.from_bytes(unhex(shellcode)).save('helloworld')
```

### assembler.py 예시:
```python
#!/usr/bin/python3
import sys, os, stat
from pwn import *
context(os="linux", arch="amd64", log_level="error")
ELF.from_bytes(unhex(sys.argv[1])).save(sys.argv[2])
os.chmod(sys.argv[2], stat.S_IEXEC)
```

---

## GCC를 통한 Shellcode 실행 (비추천)
```c
#include <stdio.h>

int main()
{
    int (*ret)() = (int (*)()) "\x48\x31\xdb\x66\xbb\...SNIP...\x3c\x40\x30\xff\x0f\x05";
    ret();
}
```
```bash
gcc helloworld.c -o helloworld
gdb -q helloworld
```
```bash
gcc helloworld.c -o helloworld -fno-stack-protector -z execstack -Wl,--omagic -g --static
./helloworld
```

> 단점: C 코드 내에서 여러 보안 메커니즘을 우회해야 하며, 라이브러리 로딩으로 인한 노이즈 증가

---

## 요약

| 항목 | 설명 |
|------|------|
| Shellcode | 어셈블리를 기계어로 변환한 후 hex로 표현한 코드 (실행 가능) |
| Pwntools | 바이너리 조작, Shellcode 실행, ELF 분석 등 다양한 기능 제공 |
| .text 섹션 | 실행 가능한 코드가 위치한 ELF 내부 섹션 |
| run_shellcode() | shellcode를 메모리에 적재 후 실행 |
| GCC 옵션 | `-fno-stack-protector`, `-z execstack` 등으로 보호 우회 |


