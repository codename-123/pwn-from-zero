	.file	"nx.c"
	.text
	.globl	binsh
	.section	.rodata
.LC0:
	.string	"/bin/sh"
	.data
	.align 8
	.type	binsh, @object
	.size	binsh, 8
binsh:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"echo 'system@plt'"
.LC2:
	.string	"[1] Leak Canary"
.LC3:
	.string	"Buf: "
.LC4:
	.string	"Buf: %s\n"
.LC5:
	.string	"[2] Overwrite return address"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	stdin(%rip), %rax
	movl	$0, %ecx
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	setvbuf
	movq	stdout(%rip), %rax
	movl	$0, %ecx
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	setvbuf
	movl	$.LC1, %edi
	call	system
	movl	$.LC2, %edi
	call	puts
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-48(%rbp), %rax
	movl	$256, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	read
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC5, %edi
	call	puts
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-48(%rbp), %rax
	movl	$256, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	read
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
