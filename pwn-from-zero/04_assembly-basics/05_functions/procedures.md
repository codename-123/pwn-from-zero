# 함수(호출) 구조 요약 정리

## 개요

프로그램 코드가 복잡해질수록, 코드를 더 체계적으로 관리하고 읽기 쉽게 만들기 위해 **프로시저(Procedure)**를 사용하는 것이 중요해집니다.

프로시저란 일정한 작업을 수행하는 명령어 집합을 따로 분리해 놓은 것으로, **중복 코드를 줄이고 유지보수성을 높이는 데 필수적**입니다.

NASM(어셈블리)에서는 `call` 명령어로 특정 프로시저로 흐름을 이동하고, 작업 완료 후 `ret` 명령어를 통해 원래 위치로 복귀합니다.

---

## 코드 예시

```nasm
global _start

section .data
message db "Fibonacci Sequence:", 0x0a

section .text
_start:
    call printMessage   ; 메시지 출력
    call initFib        ; 피보나치 초기화
    call loopFib        ; 피보나치 수열 계산
    call Exit           ; 프로그램 종료

printMessage:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, 20
    syscall
    ret

initFib:
    xor rax, rax
    xor rbx, rbx
    inc rbx
    ret

loopFib:
    add rax, rbx
    xchg rax, rbx
    cmp rbx, 10
    js loopFib
    ret

Exit:
    mov rax, 60
    mov rdi, 0
    syscall
```

> 각 프로시저는 반드시 `ret` 명령어로 종료해야 함. 단, 프로그램을 종료하는 Exit 프로시저는 예외

---


## 요약

- 어셈블리에서도 **"코드를 잘게 나누고 필요할 때 호출하는"** 구조화 프로그래밍 원칙을 적용할 수 있다.
- 잘 정리된 프로시저는 **효율적인 개발**과 **유지보수**를 가능하게 만든다. 

| 명령어 | 설명 | 예시 | 느낌 |
|--------|------|------|------|
| `call` | 다음 명령어의 RIP 값을 스택에 저장하고 프로시저로 점프 | `call printMessage` | push + jmp |
| `ret`  | 스택에 저장된 RIP 값을 꺼내 복귀 | `ret` | pop + jmp |

- `Exit` 프로시저는 시스템 콜을 통해 **프로그램을 즉시 종료**를 할 수 있다.
- 프로시저를 잘게 나누어 관리하면, **코드 재사용성**과 **가독성**을 높일 수 있다.

## 추가 참고 사항

- `enter`와 `leave` 명령어는 스택 프레임을 설정 및 해제하는 데 사용됨.
- 복잡한 함수에서 지역 변수 공간을 마련할 때 유용하지만, 현재 예제에서는 사용하지 않습니다.


