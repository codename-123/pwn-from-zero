# 어셈블리 소스 코드의 기본 구성 요약 정리

## 개요
어셈블리 코드를 작성하려면 기본 구조를 알아야 합니다. 어셈블리 파일은 크게 다음과 같은 요소들로 구성:

- **지시어 (Directives)**: 실행 시작 위치나 섹션 구분 등을 지정
- **섹션 (Sections)**: `.data`, `.text` 등으로 변수나 실행 코드 저장 위치를 구분
- **레이블 (Labels)**: 위치 지정용으로 jump 등에서 참조됨
- **명령어 (Instructions)**: 실제 수행할 어셈블리 명령어
- **피연산자 (Operands)**: 명령어가 작동할 대상 (레지스터, 주소 등)

---

## 코드 구성 예시

```nasm
global  _start

section .data
message: db "Hello HTB Academy!"

section .text
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, 18
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
```

이 코드는 'Hello HTB Academy!'를 출력하고 종료하는 간단한 Hello World 예제입니다.

---

## 어셈블리 파일 구조

![Assembly Structure Diagram](../images/nasm_structure.jpg)


---

## 주요 구성 요소 설명

### 1. Directives (지시어)
- `global _start`: 프로그램이 시작될 위치를 지정하는 지시어
- `section .data`: 변수 저장용 메모리 영역
- `section .text`: 실행 코드 저장용 메모리 영역

### 2. Labels (레이블)
- `message:`: 변수 이름 지정
- `_start:`: 코드 시작 위치 (엔트리 포인트)

레이블은 점프하거나 값을 참조할 때 사용됩니다.

### 3. Instructions & Operands (명령어와 피연산자)
- 예: `mov rax, 1`
- `mov`는 명령어 (Instruction), `rax`, `1`은 피연산자 (Operands)

---

## 변수 정의 (Variables)
- `.data` 섹션에 변수 정의 가능
지시어 | 의미 | 크기
db | Define Byte | 1바이트
dw | Define Word | 2바이트
dd | Define Doubleword | 4바이트

```nasm
message db "Hello World!", 0x0a
length  equ $-message
```
### 이 코드가 하는 일:
1. "Hello World!\n"는 총 13바이트
→ message부터 메모리에 차례대로 들어감

2. $는 현재 주소 = 즉, "Hello World!\n" 다 저장된 다음 위치

3. $ - message
→ 끝 주소 - 시작 주소
→ 13 (문자열의 바이트 수!)

4. length equ 13
→ length라는 상수에 13을 저장한 것이야
→ 컴파일 타임에 "얘는 13이야!" 라고 결정되는 고정 숫자

---

## 코드 섹션 (.text)
- 실제 실행될 명령어들이 위치
- `_start`는 프로그램 시작 위치로, 이 아래의 명령어부터 실행
- `.text`는 읽기 전용 메모리 영역 → 변수 저장 불가
- `.data`는 실행 불가한 메모리 영역 → 코드 실행 불가

> 메모리 보호 관점에서 코드와 데이터를 분리함 (버퍼 오버플로우 방지 목적)

---

## 꿀팁
- `;` 세미콜론을 사용하여 주석 작성 가능

```nasm
mov rax, 1      ; 시스템 호출 번호: write
```

---

## 요약

| 구성 요소    | 설명                                  |
|-----------|-------------------------------------|
| Directives | global, section 등 지시어                     |
| Sections   | .data (변수), .text (코드)                  |
| Labels     | message:, _start: 등 위치 지정용             |
| Instructions | mov, syscall 등 어셈블리 명령어             |
| Operands   | 명령어가 동작할 대상 (예: 레지스터, 상수, 주소 등) |



