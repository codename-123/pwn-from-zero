# GNU 디버깅 도구 요약 정리

## GDB란?
- GDB는 **리눅스용 디버깅 도구**로, 주로 **C/Assembly 프로그램의 문제를 추적하고 분석**할 때 사용됨
- **개발자와 모의 해커 모두에게 필수 도구**로, 실행 중인 바이너리를 분석하며 흐름을 따라가거나 중단시킬 수 있음
- 대표적으로 사용하는 플러그인: **GEF (GDB Enhanced Features)**

---

## 설치 방법
```bash
sudo apt-get update
sudo apt-get install gdb
```

### GEF 플러그인 설치

- GDB에 GEF를 추가하려면 다음 명령을 사용.
```bash
wget -O ~/.gdbinit-gef.py -q https://gef.blah.cat/py
echo source ~/.gdbinit-gef.py >> ~/.gdbinit
```
- 설치 후 GDB를 실행하면 `gef>` 프롬프트가 뜸

---

## GDB 실행하기
```bash
gdb -q ./helloWorld
```
- `-q`: 로딩 메시지 없이 조용히 시작
- `gef>`: GEF 플러그인이 적용된 상태로 시작됨

### assembler.sh로 GDB 실행 자동화
```bash
./assembler.sh helloWorld.s -g
```
- 어셈블 + 링크 + GDB 실행까지 한 번에 처리

---

## 주요 GDB 명령어 정리

### info
- 프로그램 정보 확인
- 함수 목록 보기:
```bash
info functions
```
- 변수 목록 보기:
```bash
info variables
```

### disas (disassemble)
- 함수 내부 어셈블리 명령어 보기:
```bash
disas _start
```
- 메모리 주소와 명령어를 확인해 브레이크포인트 설정 가능

---

## 메모리 주소 형태 (PIE 관련)
- 메모리가 `0x0040xxxx`처럼 보이면 **PIE (Position-Independent Executable)** 때문
- PIE는 보안 목적 (메모리 랜덤화)을 위해 주소를 RIP 기준 상대적으로 계산함
- 디버깅을 쉽게 하려면 **PIE 비활성화**하면 절대 주소로 분석 가능

---

## 요약
- GDB는 리눅스에서 바이너리 동작을 분석하는 대표 디버깅 툴
- GEF 플러그인을 활용하면 인터페이스가 더 보기 편해짐
- `info`, `disas` 등의 명령어로 프로그램 흐름 추적


