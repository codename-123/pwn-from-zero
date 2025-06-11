# seccomp-shellcode-analysis

이 리포지토리는 seccomp 필터링이 적용된 바이너리 환경에서 execve가 차단된 조건을 우회하여 쉘코드를 실행하고, 플래그 파일을 읽는 과정을 분석 및 구현한 실습 결과입니다.

---

## 개요

`execve`, `execveat` 시스템 콜이 seccomp 필터에 의해 차단된 상태에서, shellcode를 직접 입력받아 `mmap`된 메모리 영역에서 실행하는 구조를 분석하고, 이를 기반으로 `open`, `read`, `write`를 이용하여 우회하는 쉘코드를 작성했습니다.

---

## 파일 구성

`seccomp.c` → 원본 C 코드 (execve 필터 적용 및 shellcode 입력 구조) 
`seccomp.S` →  바이너리 디스어셈블 결과 
`seccomp.md` → 전체 분석 문서 (어셈블리 해석 및 시스템콜 흐름 포함) 
`shellcode.asm` → 직접 작성한 어셈블리 쉘코드 (open-read-write 기반 플래그 출력) 


