# 시스템 호출 요약 정리

## 개요

- Assembly로 CPU에게 직접 명령을 내릴 수 있지만, 복잡한 작업(예: 파일 입출력, 화면 출력 등)을 매번 세부적으로 제어하는 것은 비효율적이다. 이를 해결하기 위해 운영체제 커널은 **시스템 호출(Syscall)** 이라는 기능을 제공한다.

- 시스템 호출은 운영체제가 제공하는 함수처럼 동작하며, 레지스터를 통해 인자를 전달하고 `syscall` 명령어로 호출한다.

---

## Syscall 특징

- 각 Syscall은 고유한 **번호**를 가진다.
- 호출 시 필요한 인자들은 레지스터에 저장된다.
- 호출 규약(Call Convention)에 따라 레지스터에 인자와 번호를 설정해야 한다.
- 결과(Return Value)는 보통 **rax** 레지스터에 저장된다.

| 역할         | 레지스터                         |
| ---------- | ---------------------------- |
| Syscall 번호 | rax                          |
| 1번째 인자     | rdi                          |
| 2번째 인자     | rsi                          |
| 3번째 인자     | rdx                          |
| 4번째 인자     | r10 (Linux에서는 rcx 대신 r10 사용) |
| 5번째 인자     | r8                           |
| 6번째 인자     | r9                           |

---

## write 및 exit Syscall 사용 예시

### write(Syscall 번호 1)

```assembly
section .data
message db "Fibonacci Sequence:", 0x0a

section .text
global _start

_start:
    mov rax, 1          ; write syscall
    mov rdi, 1          ; 파일 디스크립터 1(stdout)
    mov rsi, message    ; 출력할 문자열 주소
    mov rdx, 20         ; 출력할 길이 (20 bytes)
    syscall
```

- **message**는 `.data` 섹션에 저장된 문자열이다.
- **stdout**에 문자열을 출력한다.

### exit(Syscall 번호 60)

```assembly
    mov rax, 60         ; exit syscall
    mov rdi, 0          ; 정상 종료(exit code 0)
    syscall
```

- 프로그램을 정상적으로 종료시킨다.

---

## Syscall 호출 흐름 요약

1. 필요한 레지스터에 인자값 설정
2. `rax`에 호출할 Syscall 번호 저장
3. `syscall` 명령어 실행
4. 반환값은 `rax`에 저장됨

> 참고: 함수나 Syscall 호출 전에는 레지스터 값을 스택에 저장(push)하고, 호출 후 복원(pop)하는 것이 일반적이다.

---

## 요약

- **Syscall**은 OS 커널이 제공하는 공식 인터페이스다.
- 직접 하드웨어를 제어할 필요 없이 고수준 기능을 사용할 수 있다.
- 호출 규약과 레지스터 관리가 정확해야 정상적으로 작동한다.
- 프로그램 종료 시에는 반드시 `exit` syscall을 호출하여 정상 종료해야 한다.

