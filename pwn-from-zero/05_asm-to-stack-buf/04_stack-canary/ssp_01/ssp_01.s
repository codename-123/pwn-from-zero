	.file	"ssp_01.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"TIME OUT"
	.text
	.globl	alarm_handler
	.type	alarm_handler, @function
alarm_handler:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	lea	rax, .LC0[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, -1
	call	exit@PLT
	.cfi_endproc
.LFE6:
	.size	alarm_handler, .-alarm_handler
	.globl	initialize
	.type	initialize, @function
initialize:
.LFB7:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	rax, QWORD PTR stdin[rip]
	mov	ecx, 0
	mov	edx, 2
	mov	esi, 0
	mov	rdi, rax
	call	setvbuf@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	ecx, 0
	mov	edx, 2
	mov	esi, 0
	mov	rdi, rax
	call	setvbuf@PLT
	lea	rax, alarm_handler[rip]
	mov	rsi, rax
	mov	edi, 14
	call	signal@PLT
	mov	edi, 30
	call	alarm@PLT
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	initialize, .-initialize
	.section	.rodata
.LC1:
	.string	"/bin/sh"
	.text
	.globl	get_shell
	.type	get_shell, @function
get_shell:
.LFB8:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	system@PLT
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	get_shell, .-get_shell
	.section	.rodata
	.align 8
.LC2:
	.string	"Element of index %d is : %02x\n"
	.text
	.globl	print_box
	.type	print_box, @function
print_box:
.LFB9:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	DWORD PTR -12[rbp], esi
	mov	eax, DWORD PTR -12[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -8[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movzx	edx, al
	mov	eax, DWORD PTR -12[rbp]
	mov	esi, eax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	print_box, .-print_box
	.section	.rodata
.LC3:
	.string	"[F]ill the box"
.LC4:
	.string	"[P]rint the box"
.LC5:
	.string	"[E]xit"
.LC6:
	.string	"> "
	.text
	.globl	menu
	.type	menu, @function
menu:
.LFB10:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	lea	rax, .LC3[rip]
	mov	rdi, rax
	call	puts@PLT
	lea	rax, .LC4[rip]
	mov	rdi, rax
	call	puts@PLT
	lea	rax, .LC5[rip]
	mov	rdi, rax
	call	puts@PLT
	lea	rax, .LC6[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	menu, .-menu
	.section	.rodata
.LC7:
	.string	"box input : "
.LC8:
	.string	"Element index : "
.LC9:
	.string	"%d"
.LC10:
	.string	"Name Size : "
.LC11:
	.string	"Name : "
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 160
	mov	DWORD PTR -148[rbp], edi
	mov	QWORD PTR -160[rbp], rsi
	mov	QWORD PTR -64[rbp], 0
	mov	QWORD PTR -56[rbp], 0
	mov	QWORD PTR -48[rbp], 0
	mov	QWORD PTR -40[rbp], 0
	mov	QWORD PTR -32[rbp], 0
	mov	QWORD PTR -24[rbp], 0
	mov	QWORD PTR -16[rbp], 0
	mov	QWORD PTR -8[rbp], 0
	mov	QWORD PTR -128[rbp], 0
	mov	QWORD PTR -120[rbp], 0
	mov	QWORD PTR -112[rbp], 0
	mov	QWORD PTR -104[rbp], 0
	mov	QWORD PTR -96[rbp], 0
	mov	QWORD PTR -88[rbp], 0
	mov	QWORD PTR -80[rbp], 0
	mov	QWORD PTR -72[rbp], 0
	mov	WORD PTR -130[rbp], 0
	mov	DWORD PTR -136[rbp], 0
	mov	DWORD PTR -140[rbp], 0
	mov	eax, 0
	call	initialize
.L12:
	mov	eax, 0
	call	menu
	lea	rax, -130[rbp]
	mov	edx, 2
	mov	rsi, rax
	mov	edi, 0
	call	read@PLT
	movzx	eax, BYTE PTR -130[rbp]
	movsx	eax, al
	cmp	eax, 80
	je	.L7
	cmp	eax, 80
	jg	.L14
	cmp	eax, 69
	je	.L9
	cmp	eax, 70
	jne	.L14
	lea	rax, .LC7[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, -64[rbp]
	mov	edx, 64
	mov	rsi, rax
	mov	edi, 0
	call	read@PLT
	jmp	.L10
.L7:
	lea	rax, .LC8[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, -136[rbp]
	mov	rsi, rax
	lea	rax, .LC9[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	mov	edx, DWORD PTR -136[rbp]
	lea	rax, -64[rbp]
	mov	esi, edx
	mov	rdi, rax
	call	print_box
	jmp	.L10
.L9:
	lea	rax, .LC10[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, -140[rbp]
	mov	rsi, rax
	lea	rax, .LC9[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	lea	rax, .LC11[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	eax, DWORD PTR -140[rbp]
	movsx	rdx, eax
	lea	rax, -128[rbp]
	mov	rsi, rax
	mov	edi, 0
	call	read@PLT
	mov	eax, 0
	jmp	.L13
.L14:
	nop
.L10:
	jmp	.L12
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Debian 14.2.0-16) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
