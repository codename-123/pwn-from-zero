# 조건에 따른 흐름 제어 요약 정리

## 개요

**Conditional Branching**은 **Unconditional Branching**과 다르게, 특정 조건이 만족될 경우에만 실행되는 명령이다.

조건 값과 관련된 **Jcc** 명령이 존재하며, `cc`는 조건 코드를 나타낸다.

| 명령 | 조건 | 설명 |
|:---|:---|:---|
| jz | Destination = 0 | Destination이 0인 경우 |
| jnz | Destination ≠ 0 | Destination이 0이 아니면 |
| js | Destination < 0 | Destination이 음수인 경우 |
| jns | Destination ≥ 0 | Destination이 0 이상인 경우 |
| jg | Destination > Source | Destination이 Source보다 크면 |
| jge | Destination ≥ Source | Destination이 Source보다 크거나 같으면 |
| jl | Destination < Source | Destination이 Source보다 작으면 |
| jle | Destination ≤ Source | Destination이 Source보다 작거나 같으면 |

---

## RFLAGS 레지스터의 플래그

**RFLAGS** 레지스터는 조건 관련 정보를 저장하는 64비트 구조의 레지스터이다.

| Bit(s) | Label (1/0) | 설명 |
|--------|----------------|------|
| 0 | CF (CY/NC) | 캐리 플래그 (Carry Flag) |
| 1 | 1 | 예약됨 (Reserved) |
| 2 | PF (PE/PO) | 패리티 플래그 (Parity Flag) |
| 3 | 0 | 예약됨 (Reserved) |
| 4 | AF (AC/NA) | 보조 캐리 플래그 (Auxiliary Carry Flag) |
| 5 | 0 | 예약됨 (Reserved) |
| 6 | ZF (ZR/NZ) | 제로 플래그 (Zero Flag) |
| 7 | SF (NC/PL) | 사인 플래그 (Sign Flag) |
| 8 | TF | 트랩 플래그 (Trap Flag) |
| 9 | IF (EL/DI) | 인터럽트 가능 여부 (Interrupt Flag) |
| 10 | DF (DN/UP) | 문자열 방향 플래그 (Direction Flag) |
| 11 | OF (OV/NV) | 오버플로우 플래그 (Overflow Flag) |
| 12-13 | IOPL | I/O 권한 레벨 (I/O Privilege Level) |
| 14 | NT | 중첩 태스크 플래그 (Nested Task) |
| 15 | 0 | 예약됨 (Reserved) |
| 16 | RF | 다시 시작 플래그 (Resume Flag) |
| 17 | VM | 8086 가상 모드 (Virtual-8086 Mode) |
| 18 | AC | 정렬 검사 (Alignment Check) |
| 19 | VIF | 가상 인터럽트 허용 (Virtual Interrupt Flag) |
| 20 | VIP | 가상 인터럽트 보류 (Virtual Interrupt Pending) |
| 21 | ID | CPUID 명령 지원 여부 (Identification Flag) |
| 22–63 | 0 | 예약됨 (Reserved) |

- 이 플래그들은 연산 결과에 따라 1 또는 0으로 설정된다.

### 주요 사용 플래그 정리

| 플래그 | 이름              | 의미 및 사용 예시                                      |
|--------|-------------------|-------------------------------------------------------|
| ZF     | Zero Flag         | 연산 결과가 0이면 1로 설정됨 → `jz`, `jnz` 등에 사용 (je, jne 와 동일) |
| SF     | Sign Flag         | 연산 결과가 음수이면 1 → `js`, `jns` 등에 사용        |
| CF     | Carry Flag        | 부호 없는 연산에서 자리올림 발생 시 1 → `jc`, `jnc`  |
| PF     | Parity Flag     | 연산 결과의 하위 8비트(1바이트)에 있는 1의 개수가 짝수면 1, 홀수면 0 → `jp`, `jnp`   |

---

## JNZ 및 Loop 구조 비교

이전에 사용한 `loop` 명령은 사실:

- `dec rcx` (rcx 값을 1 감소)
- `jnz loopFib` (rcx가 0이 아니면 루프 복귀)

의 두 명령을 합친 것이다.

`jnz`를 직접 사용하면 프로그램의 흐름을 더 자유롭게 제어할 수 있다.

```assembly
global _start

section .text
_start:
    xor rax, rax
    xor rbx, rbx
    inc rbx
    mov rcx, 10
loopFib:
    add rax, rbx
    xchg rax, rbx
    dec rcx
    jnz loopFib
```

- `rcx`가 0이 될 때까지 반복 실행된다.

---

## CMP (비교) 명령어의 활용

**cmp** 명령어는 두 피연산자의 값을 비교하고, 그 결과에 따라 플래그를 설정한다.

```assembly
cmp rbx, 10  ; rbx - 10을 계산하고 결과는 저장하지 않고 플래그만 설정
```

- 결과가 음수이면 SF(Sign Flag)가 1로 설정된다.
- 결과가 양수나 0이면 SF가 0으로 설정된다.

---

## CMP + js 활용 예제

```assembly
global _start

section .text
_start:
    xor rax, rax
    xor rbx, rbx
    inc rbx
loopFib:
    add rax, rbx
    xchg rax, rbx
    cmp rbx, 10
    js loopFib
```

- `rcx`를 사용하지 않고, rbx가 10보다 작을 때만 루프가 반복된다.
- rbx가 10 이상이 되면 루프가 종료된다.

---

## 요약

- `loop`와 `jnz`는 비슷한 기능을 하지만, `jnz`를 사용하면 보다 유연하게 프로그램 흐름을 제어할 수 있다.
- `cmp`는 연산 결과에 따라 분기 조건을 결정하는 중요한 명령어이다.

> 예를 들어, 루프 조건을 `cmp`와 `js`로 제어하면 프로그램의 흐름을 더욱 세밀하게 조정할 수 있다.

