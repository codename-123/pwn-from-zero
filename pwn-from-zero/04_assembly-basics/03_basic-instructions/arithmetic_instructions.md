# 산술 명령어 요약 정리

## 개요

Arithmetic 명령어는 레지스터나 메모리에 저장된 데이터를 기반으로 다양한 수학적 연산을 수행하는 데 사용. 이러한 연산은 CPU의 ALU(Arithmetic Logic Unit)를 비롯한 여러 컴포넌트에서 처리 됨.

Arithmetic 명령어는 다음 두 가지 유형으로 나눌 수 있음:

- 하나의 피연산자만 사용하는 연산 (Unary Instructions)
- 두 개의 피연산자를 사용하는 연산 (Binary Instructions)

---

## 단항 연산

단항 연산은 하나의 레지스터 또는 메모리 값에 대해 직접 연산을 수행. (초기 값: `rax = 1` 가정)

| 명령어 | 설명 | 예시 |
|:---|:---|:---|
| inc | 값에 1을 더함 | `inc rax` -> `rax += 1` -> `rax = 2` |
| dec | 값에서 1을 뺌 | `dec rax` -> `rax -= 1` -> `rax = 0` |

### 예제
```assembly
global _start
section .text
_start:
    mov al, 0
    mov bl, 0
    inc bl
```
💡 `al`, `bl`은 각각 `rax`, `rbx`의 하위 8비트 레지스터로, 효율적인 처리를 위해 사용 됨.

---

## 이항 연산

이항 연산은 두 개의 피연산자 간에 계산을 수행 함. (초기 상태: `rax = 1`, `rbx = 1`)

| 명령어 | 설명 | 예시 |
|:---|:---|:---|
| add | 두 값을 더함 | `add rax, rbx` -> `rax = 1 + 1 = 2` |
| sub | 첫 번째 값에서 두 번째 값을 뺌 | `sub rax, rbx` -> `rax = 1 - 1 = 0` |
| imul | 두 값을 곱함 | `imul rax, rbx` -> `rax = 1 * 1 = 1` |

### 예제 
```assembly
global _start
section .text
_start:
    mov al, 0
    mov bl, 0
    inc bl
    add rax, rbx
```
💡 결과적으로 `rax = 0 + 1 = 1`이 됨.

> Destination operand는 결과값을 저장하며, Source operand는 연산 후에도 변경되지 않음.

---

## 비트 연산

Bitwise 연산은 비트 수준에서 데이터를 조작하는 명령어임. (초기 값: `rax = 1`, `rbx = 2`)

| 명령어 | 설명 | 예시 |
|:---|:---|:---|
| not | 모든 비트를 반전 | `not rax` -> `00000001` → `11111110` |
| and | 두 비트가 모두 1일 때 1 반환 | `and rax, rbx` -> `00000001 & 00000010 = 00000000` |
| or | 둘 중 하나라도 1이면 1 반환 | `or rax, rbx` -> `00000001 or 00000010 = 00000011` |
| xor | 비트가 다르면 1, 같으면 0 반환 | `xor rax, rbx` -> `00000001 ^ 00000010 = 00000011` |

### 개념 설명 
- **not**: 각각의 비트를 반전.
- **and/or**: 두 비트에 대해 AND 또는 OR 연산을 수행.
- **xor**: 같은 비트는 0, 다른 비트는 1로 반환.

### XOR 최적화 예제
```assembly
global _start
section .text
_start:
    xor rax, rax
    xor rbx, rbx
    inc rbx
    add rax, rbx
```
- `xor rax, rax`를 사용하면 `rax`를 빠르게 0으로 초기화할 수 있음.

---

## 요약

- **Unary Instructions:** 하나의 피연산자에 대해 작용 (inc/dec)
- **Binary Instructions:** 두 피연산자 간의 연산을 수행 (add/sub/imul)
- **Bitwise Instructions:** 비트 단위로 값을 조작 (not/and/or/xor)
- **XOR 최적화:** `xor reg, reg`을 통해 레지스터를 빠르게 초기화

> 산술 연산과 비트 연산은 레지스터 및 메모리 내 데이터를 효율적으로 조작하는 데 필수적인 기술이다.

