# 스택 기반 버퍼 오버플로우

## 개요

버퍼 오버플로우는 C/C++과 같은 저수준 언어에서 메모리 경계를 검사하지 않고 데이터를 복사할 때 발생하는 취약점이다. 공격자는 이를 통해 반환 주소를 덮어쓰고 코드 실행 흐름을 조작할 수 있다. 현대 운영체제는 이를 막기 위해 DEP, ASLR, Stack Canary 등의 보호 기법을 사용하지만, 학습 목적을 위해 이러한 보호를 꺼두고 실습하는 경우가 많다.

---

## 메모리 구조

프로그램이 메모리에 적재될 때 일반적으로 다음과 같은 구조로 나뉜다:

- **Buffer**
![이미지](./buffer_overflow_1.png)
- **.text**: 코드(명령어)가 저장됨 (읽기 전용)
- **.data**: 초기화된 전역/정적 변수 저장
- **.bss**: 초기화되지 않은 전역/정적 변수 저장
- **Heap**: 동적 메모리(예: malloc). 주소가 증가하는 방향으로 확장됨
- **Stack**: 지역 변수, 반환 주소. 주소가 감소하는 방향으로 확장됨

---

## 취약한 프로그램 예시

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bowfunc(char *string) {
    char buffer[1024];
    strcpy(buffer, string);
    return 1;
}

int main(int argc, char *argv[]) {
    bowfunc(argv[1]);
    printf("Done.\n");
    return 1;
}
```


### ASLR 비활성화

```bash
sudo su
echo 0 > /proc/sys/kernel/randomize_va_space
cat /proc/sys/kernel/randomize_va_space  # 결과: 0
```

* 다음으로, C 코드를 32비트 ELF 바이너리로 컴파일합니다.

### 컴파일 (32비트, 보호 기능 제거)

```bash
sudo apt install gcc-multilib
gcc bow.c -o bow32 -fno-stack-protector -z execstack -m32
file bow32 | tr "," "\n"

bow: ELF 32-bit LSB shared object
 Intel 80386
 version 1 (SYSV)
 dynamically linked
 interpreter /lib/ld-linux.so.2
 for GNU/Linux 3.2.0
 BuildID[sha1]=93dda6b77131deecaadf9d207fdd2e70f47e1071
 not stripped
```

---

## 취약한 C 함수 예시

다음 함수들은 입력 길이 제한이 없어 메모리 침범 가능성이 있음:

* strcpy
* gets
* sprintf
* scanf
* strcat

---

## GDB 사용법 요약

GDB(GNU Debugger)는 프로그램을 어셈블리 수준에서 분석할 수 있는 도구다.

### 기본 실행

```bash
gdb -q bow32
disassemble main
```

### 어셈블리 구문 차이

#### AT\&T 구문 (기본)

* `%` : 레지스터
* `$` : 상수
* **소스 → 목적지 순서**

```asm
mov %esp, %ebp
```

#### Intel 구문 (가독성 좋음)

* **목적지 ← 소스 순서**

```asm
mov ebp, esp
```

#### GDB에서 Intel 구문 설정

```bash
(gdb) set disassembly-flavor intel
```

#### 영구 적용

```bash
echo 'set disassembly-flavor intel' > ~/.gdbinit
```

