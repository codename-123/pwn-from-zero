# 함수 호출 요약 정리

> 이제 어셈블리에서 조건 분기와 프로시저 호출(call/ret 등)에 익숙해졌다면, 다음으로 중요한 개념은 "함수 호출"이다. 특히 C 표준 라이브러리 함수(예: `printf`)처럼 외부 함수를 NASM에서 호출하려면 **함수 호출 규약 (Calling Convention)** 에 대한 이해가 필요하다.

---

## 함수 호출 규약

함수는 일반적인 프로시저보다 복잡한 구조를 가지고 있어, 호출 전에 다음과 같은 준비가 필요하다:

### 호출자(Caller)가 해야 할 일
1. **사용 중인 레지스터 백업**: `rax`, `rbx` 등 현재 쓰는 값은 `push`로 스택에 저장
2. **인자 전달**: 함수 인자는 순서대로 `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`에 저장
3. **스택 정렬**: `rsp`는 항상 16바이트 정렬 상태여야 함 (성능과 안정성)
4. **반환값 받기**: 대부분의 함수는 결과를 `rax`에 반환함

> 시스템 호출(`syscall`)과 매우 유사하지만, `syscall`은 `rax`에 syscall 번호를 넣고 `rsp` 정렬을 신경 안 써도 된다.

---

## 함수 내부 (callee)의 규칙

직접 함수를 작성할 경우, 다음 규칙을 따라야 한다:
- **보존해야 할 레지스터 백업**: `rbx`, `rbp` 등은 callee가 책임지고 저장해야 함
- **인자는 정해진 레지스터에서 받음**: `rdi`, `rsi`, `rdx`, ...
- **반환값은 `rax`에 넣기**

> 함수의 시작과 끝에서 이 작업을 수행하는 코드를 각각 "프로로그(prologue)" / "에필로그(epilogue)" 라고 부른다.

---

## 외부 함수 `printf` 사용하기

Fibonacci 수열을 계산하는 루프 안에서 매번 숫자를 출력하려면, `printf`를 사용하면 된다. 기존의 `write syscall`은 문자열만 출력 가능해서 정수는 ASCII로 변환해야 했지만, `printf`는 이를 자동으로 처리해 준다.

### 1. 외부 함수 선언
```nasm
extern printf
```

### 2. printf의 함수 원형
```c
int printf(const char *format, ...);
```
> 첫 번째 인자는 포맷 문자열 (예: "%d\n"), 이후 인자들은 그 포맷에 따라 값으로 대입됨

### 3. 포맷 문자열 정의
```nasm
outFormat db "%d", 0x0a, 0x00  ; 정수 출력 후 줄바꿈 + 널 종료 문자
```

---

## printFib 함수 정의
```nasm
printFib:
    push rax
    push rbx
    mov rdi, outFormat   ; 첫 번째 인자: 포맷 문자열
    mov rsi, rbx         ; 두 번째 인자: 출력할 Fibonacci 수
    call printf          ; printf("%d", rbx)
    pop rbx
    pop rax
    ret
```

### 스택 정렬이 필요한 경우:
함수 호출 전의 `rsp`는 반드시 16바이트 정렬 상태여야 한다. 만약 안 맞는다면:
```nasm
sub rsp, 8   ; 정렬 보정
call printf
add rsp, 8
```

> 대부분의 경우는 이미 정렬된 상태지만, 루프 안에서 여러 `push`/`call`이 겹치면 확인해볼 필요가 있다.

---

## Fibonacci 루프에 출력 함수 추가하기
```nasm
loopFib:
    call printFib
    add rax, rbx
    xchg rax, rbx
    cmp rbx, 10
    js loopFib
    ret
```

---

## 컴파일 및 실행 방법
```bash
nasm -f elf64 fib.s &&  ld fib.o -o fib -lc --dynamic-linker /lib64/ld-linux-x86-64.so.2 && ./fib
```

### 결과 출력:
```
1
1
2
3
5
8
```

- printf 덕분에 정수 변환 없이 간단하게 출력할 수 있다.

---

## 요약
- 함수 호출은 syscall처럼 인자를 레지스터에 넣고 `call` 사용
- 인자 순서는 `rdi` → `rsi` → `rdx` → `rcx` → `r8` → `r9`
- 호출 전에는 사용하는 레지스터를 저장하고, 스택을 16바이트 단위로 정렬
- 외부 함수는 `extern`으로 선언하고, `ld`로 libc 동적 링크 필요

> printf를 사용하면 정수 출력도 쉽게 가능하다.
