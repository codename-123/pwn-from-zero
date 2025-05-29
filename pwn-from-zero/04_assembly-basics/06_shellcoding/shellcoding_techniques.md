# 쉘코딩 기법 요약 정리

## Shellcode가 만족해야 할 조건
쉘코드는 단순히 어셈블리를 기계어로 바꾼다고 완성되지 않으며, 다음 세 가지 조건을 반드시 만족해야 합니다:

1. **변수를 사용하지 않아야 함**: `.data`, `.bss` 세그먼트는 사용 불가
2. **직접 메모리 주소 참조 금지**: 예측 가능한 상대 주소 또는 레이블만 허용
3. **NULL 바이트(0x00) 포함 금지**: 셸코드 삽입시 조기 종료 유발

---

## 코드 예시
```nasm
section .data
    message db "Hello HTB Academy!"

section .text
_start:
    mov rsi, message
    mov rdi, 1
    mov rdx, 18
    mov rax, 1
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
```

이 코드는 shellcode로 쓰기엔 다음과 같은 문제가 있음:
- 변수(message) 사용
- 직접 주소 참조
- NULL 바이트 다수 포함

---

### 방법 1: 변수 제거
변수 없이 문자열을 Stack에 역순으로 저장 후 `rsp`를 문자열 주소로 사용한다.
```nasm
    xor rbx, rbx
    mov rbx, 'y!'
    push rbx
    mov rbx, 'B Academ'
    push rbx
    mov rbx, 'Hello HT'
    push rbx
    mov rsi, rsp
```

---

### 방법 2: 메모리 주소 참조 제거
직접 주소 참조 대신 **label(call)** 또는 **rip-relative 주소** 사용.
```nasm
; call printf  ← OK
; mov rsi, message ← [X] (직접 주소)
```

---

### 방법 3: NULL 바이트 제거
0을 채우기 위해 전체 레지스터에 작은 값을 이동하면 NULL 바이트가 삽입될 수 있음. 이를 방지하기 위해:
```nasm
xor rax, rax
mov al, 1
```

---

### 최종 shellcode 어셈블리 코드
```nasm
global _start

section .text
_start:
    xor rbx, rbx
    mov bx, 'y!'
    push rbx
    mov rbx, 'B Academ'
    push rbx
    mov rbx, 'Hello HT'
    push rbx
    mov rsi, rsp

    xor rax, rax
    mov al, 1
    xor rdi, rdi
    mov dil, 1
    xor rdx, rdx
    mov dl, 18
    syscall

    xor rax, rax
    add al, 60
    xor dil, dil
    syscall
```

---

## 디버깅 & 확인
```bash
$ ./assembler.sh helloworld.s
Hello HTB Academy!
```

또는 pwntools로 shellcode 확인:
```bash
$ python3 shellcoder.py helloworld
4831db66bb79215348bb422041636164656d5348bb48656c6c6f204854534889e64831c0b0014831ff40b7014831d2b2120f054831c0043c4030ff0f05
```

---

## NULL 바이트 검사 스크립트 추가
```python
print("%d bytes - Found NULL byte" % len(shellcode)) if [i for i in shellcode if i == 0] else print("%d bytes - No NULL bytes" % len(shellcode))
```
결과:
```bash
61 bytes - No NULL bytes
```

---

### 최종 실행 테스트
```bash
$ python3 loader.py '4831db66bb79215348bb422041636164656d5348bb48656c6c6f204854534889e64831c0b0014831ff40b7014831d2b2120f054831c0043c4030ff0f05'
Hello HTB Academy!
```

---

## 요약

- 쉘코드는 메모리에 로드되어 즉시 실행 가능한 코드여야 하며, 이를 위해 철저한 최적화가 필요
- 변수 제거, 주소 참조 제한, NULL 제거는 **실행 가능하고 안정적인 Shellcode 제작의 핵심**
- 이 과정을 통해 실전에 사용할 수 있는 고품질의 Shellcode를 구성할 수 있음
