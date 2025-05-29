# 반복문 요약 정리

## 개요

Assembly 연산은 기본적으로 행 단위에서 순차적으로 처리되지만, 프로그램의 가능성을 높이기 위해서는 관리 명령의 이해가 필요함.

**Program Control Instructions**는 프로그램의 진행 건설을 제어하고, 특정 위치로 돌아가거나 다른 건설으로 이동할 수 있게 해줌.

분류:
- Loops (루프)
- Branching (분기)
- Function Calls (함수 호출)

---

## 루프 구조

Assembly에서 루프는 `rcx`가 0이 될 때까지 진행.

### 개념 구조

```assembly
exampleLoop:
    instruction 1
    instruction 2
    instruction 3
    instruction 4
    instruction 5
    loop exampleLoop
```

- `mov rcx, x`를 통해 루프 회수 값을 설정.
- `loop label`은 `rcx`를 1 감소한 후, `rcx ≠ 0`일 경우 지정된 레이블로 돌아가는 기능을 함.

### 명령어 정보

| 명령어 | 설명 | 예시 |
|:---|:---|:---|
| `mov rcx, x` | 루프 반복 회수 x 설정 | `mov rcx, 3` |
| `loop label` | `rcx`를 1 감소하고 0이 아닌 경우 label로 이동 | `loop exampleLoop` |

---

## 피보나치 수열을 루프로 구현하기

피보나치 수열을 Assembly로 구현하면 다음과 같다.

### 초기 상태:
- `rax`: 현재 값 (Fn)
- `rbx`: 다음 값 (Fn+1)

### Assembly 코드 예시

```assembly
global _start

section .text
_start:
    xor rax, rax    ; rax = 0 초기화
    xor rbx, rbx    ; rbx = 0 초기화
    inc rbx         ; rbx = 1 설정
    mov rcx, 10     ; 10번 반복

loopFib:
    add rax, rbx    ; 현재 rax와 rbx 더하기
    xchg rax, rbx   ; rax와 rbx 값 교환
    loop loopFib
```

### gdb 실행 결과

- 가장 처음: rax = 0, rbx = 1, rcx = 10
- 1회 반복: rax = 1, rbx = 1
- 2회 반복: rax = 1, rbx = 2
- 3회 반복: rax = 2, rbx = 3
- 4회 반복: rax = 3, rbx = 5
- ...
- 마지막: rbx = 55 (10번째 피보나치 수)

---

## 요약

- **loop**는 `rcx`를 감소시키며, 0이 될 때까지 계속 회수를 반복.
- **xchg**는 `rax`와 `rbx`의 값을 서로 교환.
- **add**는 현재 수열을 계산하는 구조.

> 루프를 시작하기 전에 반드시 rcx에 반복 회수를 설정해야 한다.

