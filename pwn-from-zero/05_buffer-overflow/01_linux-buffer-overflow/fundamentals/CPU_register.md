# CPU 레지스터 및 스택 프레임 

## CPU 레지스터 개요

CPU의 레지스터는 데이터를 임시로 저장하는 공간이며, 목적에 따라 다음과 같이 구분된다:

### 1. 일반 레지스터

* **데이터 레지스터**

  * `eax` / `rax`: 누산기 (입출력, 산술 연산)
  * `ebx` / `rbx`: 베이스 레지스터 (인덱싱)
  * `ecx` / `rcx`: 카운터 (루프, 회전 연산)
  * `edx` / `rdx`: 데이터 처리, 곱셈/나눗셈 등에 사용

* **포인터 레지스터**

  * `eip` / `rip`: 명령어 포인터 (다음 실행할 명령어 위치)
  * `esp` / `rsp`: 스택 포인터 (스택의 최상단)
  * `ebp` / `rbp`: 베이스 포인터 (스택 프레임 시작 지점)

* **인덱스 레지스터**

  * `esi` / `rsi`: 소스 인덱스
  * `edi` / `rdi`: 목적지 인덱스

---

## 스택 프레임 구조

스택은 **높은 주소에서 낮은 주소로** 확장된다. 함수 호출 시 생성되는 스택 프레임은 다음과 같은 단계로 구성된다:

### 프롤로그 (Prologue)

```asm
push   ebp        ; 이전 ebp 저장
mov    ebp, esp   ; 현재 esp를 ebp에 복사하여 새로운 프레임 시작
sub    esp, 0x404 ; 로컬 변수 공간 확보
```

### 에필로그 (Epilogue)

```asm
leave             ; ebp → esp 복사 후 이전 ebp 복원
ret               ; 반환 주소로 복귀
```

---

## 함수 호출 분석 (32비트)

* 명령어: `call`

  * **동작**:

    1. 현재 `eip` (다음 명령어 주소)를 스택에 저장
    2. `eip`를 호출 함수 주소로 변경해 실행 시작

```asm
0x000005aa <+40>: call 0x54d <bowfunc>
```

---

## 함수 호출 흐름 예시 함수

```c
#include <stdio.h>

void greet() {
    printf("Hello from greet!\n");
}

int main() {
    greet();
    return 0;
}
```

### 해당 어셈블리 흐름 예시 (gcc -m32 -S -fno-stack-protector)

```asm
main:
    push   ebp
    mov    ebp, esp
    call   greet
    mov    eax, 0
    pop    ebp
    ret

greet:
    push   ebp
    mov    ebp, esp
    ; puts("Hello from greet!") 호출
    pop    ebp
    ret
```

---

## 32비트 vs 64비트 바이너리

### 32비트 컴파일

```bash
gcc bow.c -o bow32 -fno-stack-protector -z execstack -m32
```

* 레지스터: eax, ebx, esp 등
* 주소 길이: 4바이트

### 64비트 컴파일

```bash
gcc bow.c -o bow64 -fno-stack-protector -z execstack -m64
```

* 레지스터: rax, rbx, rsp 등
* 주소 길이: 8바이트
* 더 적은 명령어 수로 동일 작업 가능

---

## 엔디안(Endianness)

* **Big Endian**: 높은 값부터 저장 (예: `AA BB CC DD`)
* **Little Endian**: 낮은 값부터 저장 (예: `DD CC BB AA`)
* x86 CPU는 **Little Endian**을 사용

예시:

* 주소: `0xffff0000`
* 값: `\xAA\xBB\xCC\xDD`

| 주소         | 저장 바이트 (Little Endian) |
| ---------- | ---------------------- |
| 0xffff0000 | `DD`                   |
| 0xffff0001 | `CC`                   |
| 0xffff0002 | `BB`                   |
| 0xffff0003 | `AA`                   |
