# 어셈블링과 디어셈블링 (기계어 변환 / 역변환) 요약 정리

## Assembling (NASM)

어셈블리 파일 구조를 이해했다면 이제 NASM을 사용해서 코드를 실제로 어셈블링할 수 있다. NASM은 우리가 작성한 어셈블리 파일(.s 또는 .asm 확장자)을 읽어 각 섹션을 이해하고, 기계어로 변환된 오브젝트 파일(.o)을 생성한다.

### 코드 작성 (helloWorld.s)
```nasm
global _start

section .data
    message db "Hello HTB Academy!"
    length equ $-message

section .text
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, length
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
```
- `equ`를 사용해 message 문자열 길이를 동적으로 계산함 (고정값 대신)

### 어셈블 (Assemble)
```bash
nasm -f elf64 helloWorld.s
```
- `-f elf64`: 64비트 ELF 포맷으로 어셈블
- 결과: helloWorld.o 파일 생성 (아직 실행은 불가)

### 링크 (Link)
```bash
ld -o helloWorld helloWorld.o
```
- ld를 이용해 오브젝트 파일을 실행 파일로 변환
- 결과: 실행 가능한 ELF 파일 `helloWorld` 생성

### 실행 (Run)
```bash
./helloWorld
```
- 출력: `Hello HTB Academy!`

---

## 자동화 스크립트 (assembler.sh)

```bash
#!/bin/bash
fileName="${1%%.*}"
nasm -f elf64 ${fileName}.s
ld ${fileName}.o -o ${fileName}
[ "$2" == "-g" ] && gdb -q ${fileName} || ./${fileName}
```
- 어셈블 + 링크 + 실행을 한 번에 처리하는 스크립트
- 사용법: `./assembler.sh helloWorld.s`

- 출력: `Hello HTB Academy!`

---

## Disassembling (objdump)

기계어로 변환된 바이너리를 다시 어셈블리 코드로 복구하는 작업을 디스어셈블링(disassembling)이라고 한다.

### 기본 디스어셈블링
```bash
objdump -M intel -d helloWorld
```
- `-M intel`: 인텔 문법으로 출력
- `-d`: .text 섹션(코드 영역) 디스어셈블링

### 주소와 기계어 없이 디스어셈블링
```bash
objdump -M intel --no-show-raw-insn --no-addresses -d helloWorld
```
- 순수 어셈블리 명령어만 출력

### .data 섹션 덤프
```bash
objdump -sj .data helloWorld
```
- `.data` 섹션 내용을 16진수로 출력 (문자열 데이터 확인 가능)

---

## 요약

- NASM으로 어셈블링하면 `.o` 오브젝트 파일 생성
- ld로 링크하면 최종 실행 파일(ELF) 완성
- 디스어셈블링으로 바이너리 내부 코드 구조 분석 가능
- `equ`를 이용해 문자열 길이를 자동 계산하는 방식은 코드 관리에 매우 유리함

> 📌 참고: NASM은 최적화를 위해 64비트 레지스터(`rax`)를 32비트(`eax`)로 변환해 메모리 절약을 시도한다.

---

## 참고 명령어
```bash
nasm -f elf64 helloWorld.s      # 어셈블
ld -o helloWorld helloWorld.o   # 링크
./helloWorld                    # 실행
objdump -M intel -d helloWorld  # 디스어셈블링
```




