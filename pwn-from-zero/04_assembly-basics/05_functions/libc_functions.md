# scanf를 이용한 사용자 입력 처리 요약 정리

> 지금까지는 피보나치 수열을 10보다 작은 수까지만 출력했지만, 이는 정적인 방식이라 실행할 때마다 동일한 결과만 보여준다. 이번엔 사용자로부터 직접 최대 수를 입력받아, 입력된 수보다 작은 피보나치 수를 출력하는 **동적 프로그램**을 NASM으로 작성해보자.

---

## 함수 호출 규약 (Calling Convention) 복습

함수를 호출할 때는 다음 네 가지를 항상 고려해야 한다:

1. **레지스터 저장**: 함수 호출 전, `caller`가 사용하는 레지스터를 스택에 저장
2. **인자 전달**: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` 순으로 최대 6개까지 인자 전달
3. **스택 정렬**: 호출 시점에 `rsp % 16 == 0` 이어야 함
4. **반환값 확인**: 함수의 리턴 값은 `rax`에 저장됨

이 규칙은 `scanf`나 `printf` 같은 libc 함수 호출에도 동일하게 적용된다.

---

## 외부 함수 선언 (libc)

사용할 libc 함수는 다음과 같이 선언한다:

```nasm
extern printf, scanf
```

이 선언으로 링커가 해당 함수들을 libc에서 찾아 연결할 수 있게 된다.

---

## 입력 및 출력 포맷 준비

입출력 포맷과 사용자 입력값을 저장할 버퍼를 준비해야 한다. 입력값은 `.bss` 영역에 선언한다:

```nasm
section .data
    message db "Please input max Fn", 0x0a
    outFormat db "%d", 0x0a, 0x00   ; 출력 포맷
    inFormat db "%d", 0x00          ; 입력 포맷

section .bss
    userInput resb 1   ; 사용자 입력값을 저장할 1바이트 버퍼
```

`.bss`는 초기화되지 않은 데이터를 위한 공간이며, 실행 시 0으로 초기화된다.

---

## 사용자 입력 함수 정의 (getInput)

`scanf` 호출 시 스택 정렬을 맞추기 위해 정렬용으로 8바이트를 빼고, 호출 후 복원한다:

```nasm
getInput:
    sub rsp, 8
    mov rdi, inFormat   ; 첫 번째 인자: 입력 포맷 문자열
    mov rsi, userInput  ; 두 번째 인자: 입력 버퍼 주소
    call scanf          ; scanf("%d", userInput)
    add rsp, 8
    ret
```

이 함수는 사용자로부터 숫자 하나를 입력받아 `userInput`에 저장한다.

---

## 프로그램 시작점 (_start)

입력과 피보나치 수 계산을 연결한 전체 흐름은 다음과 같다:

```nasm
_start:
    call printMessage   ; 안내 메시지 출력
    call getInput       ; 사용자 입력값 받기
    call initFib        ; 피보나치 초기값 설정 (0, 1)
    call loopFib        ; 피보나치 수 출력 루프
    call Exit           ; 프로그램 종료
```

---

## 사용자 입력에 기반한 루프 조건 설정

기존에는 `cmp rbx, 10`처럼 상수를 사용했지만, 이제는 사용자 입력값과 비교해야 한다:

```nasm
loopFib:
    ; ...
    cmp rbx, [userInput]  ; 입력값과 비교
    js loopFib            ; 작을 경우 루프 반복
    ret
```

`[userInput]`처럼 대괄호를 써야 해당 주소의 값을 참조하게 된다.

---

## 전체 예제 코드 (최종 결과)

```nasm
global  _start
extern  printf, scanf

section .data
    message db "Please input max Fn", 0x0a
    outFormat db  "%d", 0x0a, 0x00
    inFormat db  "%d", 0x00

section .bss
    userInput resq 1

section .text
_start:
    call printMessage   ; print intro message
    call getInput       ; get max number
    call initFib        ; set initial Fib values
    call loopFib        ; calculate Fib numbers
    call Exit           ; Exit the program

printMessage:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, 20
    syscall
    ret

getInput:
    sub rsp, 8
    mov rdi, inFormat
    mov rsi, userInput
    call scanf
    add rsp, 8
    ret

initFib:
    xor rax, rax
    xor rbx, rbx
    inc rbx
    ret

printFib:
    sub rsp, 8
    push rax
    push rbx
    mov rdi, outFormat
    mov rsi, rbx
    call printf
    pop rbx
    pop rax
    add rsp, 8
    ret

loopFib:
    sub rsp, 8
    call printFib
    add rax, rbx
    xchg rax, rbx
    cmp rbx,[userInput]
    js loopFib
    add rsp, 8
    ret

Exit:
    mov rax, 60
    mov rdi, 0
    syscall
```

---

## 실행 명령어 (Dynamic Linker 사용)

```nasm
nasm -f elf64 fib.s &&  ld fib.o -o fib -lc --dynamic-linker /lib64/ld-linux-x86-64.so.2 && ./fib
```

- 실행 예시:

```nasm
Please input max Fn:
100
1
1
2
3
5
8
13
21
34
55
89
```
- 위와 같이 프로그램은 사용자 입력에 따라 피보나치 수열을 동적으로 출력한다.

---

## 요약

- `scanf`와 같은 외부 함수 호출을 위해 `extern` 선언 필수
- `.data`, `.bss` 세그먼트를 이용한 문자열과 입력 버퍼 선언 필요
- 함수 호출 시 `rdi`, `rsi` 순서로 인자 전달
- 호출 전 `sub rsp, 8`, 호출 후 `add rsp, 8`로 스택 정렬 유지
- 비교 연산 시 `[userInput]`처럼 대괄호로 값을 참조
- `printf`, `scanf` 같은 libc 함수 호출 시 반드시 **16바이트 정렬** 필요
