
canary:     file format elf64-x86-64


Disassembly of section .init:

00000000000006d8 <_init>:
 6d8:	48 83 ec 08          	sub    rsp,0x8
 6dc:	48 8b 05 05 09 20 00 	mov    rax,QWORD PTR [rip+0x200905]        # 200fe8 <__gmon_start__>
 6e3:	48 85 c0             	test   rax,rax
 6e6:	74 02                	je     6ea <_init+0x12>
 6e8:	ff d0                	call   rax
 6ea:	48 83 c4 08          	add    rsp,0x8
 6ee:	c3                   	ret

Disassembly of section .plt:

00000000000006f0 <.plt>:
 6f0:	ff 35 9a 08 20 00    	push   QWORD PTR [rip+0x20089a]        # 200f90 <_GLOBAL_OFFSET_TABLE_+0x8>
 6f6:	ff 25 9c 08 20 00    	jmp    QWORD PTR [rip+0x20089c]        # 200f98 <_GLOBAL_OFFSET_TABLE_+0x10>
 6fc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000000700 <puts@plt>:
 700:	ff 25 9a 08 20 00    	jmp    QWORD PTR [rip+0x20089a]        # 200fa0 <puts@GLIBC_2.2.5>
 706:	68 00 00 00 00       	push   0x0
 70b:	e9 e0 ff ff ff       	jmp    6f0 <.plt>

0000000000000710 <__stack_chk_fail@plt>:
 710:	ff 25 92 08 20 00    	jmp    QWORD PTR [rip+0x200892]        # 200fa8 <__stack_chk_fail@GLIBC_2.4>
 716:	68 01 00 00 00       	push   0x1
 71b:	e9 d0 ff ff ff       	jmp    6f0 <.plt>

0000000000000720 <printf@plt>:
 720:	ff 25 8a 08 20 00    	jmp    QWORD PTR [rip+0x20088a]        # 200fb0 <printf@GLIBC_2.2.5>
 726:	68 02 00 00 00       	push   0x2
 72b:	e9 c0 ff ff ff       	jmp    6f0 <.plt>

0000000000000730 <read@plt>:
 730:	ff 25 82 08 20 00    	jmp    QWORD PTR [rip+0x200882]        # 200fb8 <read@GLIBC_2.2.5>
 736:	68 03 00 00 00       	push   0x3
 73b:	e9 b0 ff ff ff       	jmp    6f0 <.plt>

0000000000000740 <gets@plt>:
 740:	ff 25 7a 08 20 00    	jmp    QWORD PTR [rip+0x20087a]        # 200fc0 <gets@GLIBC_2.2.5>
 746:	68 04 00 00 00       	push   0x4
 74b:	e9 a0 ff ff ff       	jmp    6f0 <.plt>

0000000000000750 <fflush@plt>:
 750:	ff 25 72 08 20 00    	jmp    QWORD PTR [rip+0x200872]        # 200fc8 <fflush@GLIBC_2.2.5>
 756:	68 05 00 00 00       	push   0x5
 75b:	e9 90 ff ff ff       	jmp    6f0 <.plt>

0000000000000760 <setvbuf@plt>:
 760:	ff 25 6a 08 20 00    	jmp    QWORD PTR [rip+0x20086a]        # 200fd0 <setvbuf@GLIBC_2.2.5>
 766:	68 06 00 00 00       	push   0x6
 76b:	e9 80 ff ff ff       	jmp    6f0 <.plt>

Disassembly of section .plt.got:

0000000000000770 <__cxa_finalize@plt>:
 770:	ff 25 82 08 20 00    	jmp    QWORD PTR [rip+0x200882]        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 776:	66 90                	xchg   ax,ax

Disassembly of section .text:

0000000000000780 <_start>:
 780:	31 ed                	xor    ebp,ebp
 782:	49 89 d1             	mov    r9,rdx
 785:	5e                   	pop    rsi
 786:	48 89 e2             	mov    rdx,rsp
 789:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
 78d:	50                   	push   rax
 78e:	54                   	push   rsp
 78f:	4c 8d 05 ba 02 00 00 	lea    r8,[rip+0x2ba]        # a50 <__libc_csu_fini>
 796:	48 8d 0d 43 02 00 00 	lea    rcx,[rip+0x243]        # 9e0 <__libc_csu_init>
 79d:	48 8d 3d 29 01 00 00 	lea    rdi,[rip+0x129]        # 8cd <main>
 7a4:	ff 15 36 08 20 00    	call   QWORD PTR [rip+0x200836]        # 200fe0 <__libc_start_main@GLIBC_2.2.5>
 7aa:	f4                   	hlt
 7ab:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

00000000000007b0 <deregister_tm_clones>:
 7b0:	48 8d 3d 59 08 20 00 	lea    rdi,[rip+0x200859]        # 201010 <stdout@GLIBC_2.2.5>
 7b7:	55                   	push   rbp
 7b8:	48 8d 05 51 08 20 00 	lea    rax,[rip+0x200851]        # 201010 <stdout@GLIBC_2.2.5>
 7bf:	48 39 f8             	cmp    rax,rdi
 7c2:	48 89 e5             	mov    rbp,rsp
 7c5:	74 19                	je     7e0 <deregister_tm_clones+0x30>
 7c7:	48 8b 05 0a 08 20 00 	mov    rax,QWORD PTR [rip+0x20080a]        # 200fd8 <_ITM_deregisterTMCloneTable>
 7ce:	48 85 c0             	test   rax,rax
 7d1:	74 0d                	je     7e0 <deregister_tm_clones+0x30>
 7d3:	5d                   	pop    rbp
 7d4:	ff e0                	jmp    rax
 7d6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
 7dd:	00 00 00 
 7e0:	5d                   	pop    rbp
 7e1:	c3                   	ret
 7e2:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 7e6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
 7ed:	00 00 00 

00000000000007f0 <register_tm_clones>:
 7f0:	48 8d 3d 19 08 20 00 	lea    rdi,[rip+0x200819]        # 201010 <stdout@GLIBC_2.2.5>
 7f7:	48 8d 35 12 08 20 00 	lea    rsi,[rip+0x200812]        # 201010 <stdout@GLIBC_2.2.5>
 7fe:	55                   	push   rbp
 7ff:	48 29 fe             	sub    rsi,rdi
 802:	48 89 e5             	mov    rbp,rsp
 805:	48 c1 fe 03          	sar    rsi,0x3
 809:	48 89 f0             	mov    rax,rsi
 80c:	48 c1 e8 3f          	shr    rax,0x3f
 810:	48 01 c6             	add    rsi,rax
 813:	48 d1 fe             	sar    rsi,1
 816:	74 18                	je     830 <register_tm_clones+0x40>
 818:	48 8b 05 d1 07 20 00 	mov    rax,QWORD PTR [rip+0x2007d1]        # 200ff0 <_ITM_registerTMCloneTable>
 81f:	48 85 c0             	test   rax,rax
 822:	74 0c                	je     830 <register_tm_clones+0x40>
 824:	5d                   	pop    rbp
 825:	ff e0                	jmp    rax
 827:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 82e:	00 00 
 830:	5d                   	pop    rbp
 831:	c3                   	ret
 832:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 836:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
 83d:	00 00 00 

0000000000000840 <__do_global_dtors_aux>:
 840:	80 3d e1 07 20 00 00 	cmp    BYTE PTR [rip+0x2007e1],0x0        # 201028 <completed.7698>
 847:	75 2f                	jne    878 <__do_global_dtors_aux+0x38>
 849:	48 83 3d a7 07 20 00 	cmp    QWORD PTR [rip+0x2007a7],0x0        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 850:	00 
 851:	55                   	push   rbp
 852:	48 89 e5             	mov    rbp,rsp
 855:	74 0c                	je     863 <__do_global_dtors_aux+0x23>
 857:	48 8b 3d aa 07 20 00 	mov    rdi,QWORD PTR [rip+0x2007aa]        # 201008 <__dso_handle>
 85e:	e8 0d ff ff ff       	call   770 <__cxa_finalize@plt>
 863:	e8 48 ff ff ff       	call   7b0 <deregister_tm_clones>
 868:	c6 05 b9 07 20 00 01 	mov    BYTE PTR [rip+0x2007b9],0x1        # 201028 <completed.7698>
 86f:	5d                   	pop    rbp
 870:	c3                   	ret
 871:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 878:	f3 c3                	repz ret
 87a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000000880 <frame_dummy>:
 880:	55                   	push   rbp
 881:	48 89 e5             	mov    rbp,rsp
 884:	5d                   	pop    rbp
 885:	e9 66 ff ff ff       	jmp    7f0 <register_tm_clones>

000000000000088a <init>:
 88a:	55                   	push   rbp
 88b:	48 89 e5             	mov    rbp,rsp
 88e:	48 8b 05 8b 07 20 00 	mov    rax,QWORD PTR [rip+0x20078b]        # 201020 <stdin@GLIBC_2.2.5>
 895:	b9 00 00 00 00       	mov    ecx,0x0
 89a:	ba 02 00 00 00       	mov    edx,0x2
 89f:	be 00 00 00 00       	mov    esi,0x0
 8a4:	48 89 c7             	mov    rdi,rax
 8a7:	e8 b4 fe ff ff       	call   760 <setvbuf@plt>
 8ac:	48 8b 05 5d 07 20 00 	mov    rax,QWORD PTR [rip+0x20075d]        # 201010 <stdout@GLIBC_2.2.5>
 8b3:	b9 00 00 00 00       	mov    ecx,0x0
 8b8:	ba 02 00 00 00       	mov    edx,0x2
 8bd:	be 00 00 00 00       	mov    esi,0x0
 8c2:	48 89 c7             	mov    rdi,rax
 8c5:	e8 96 fe ff ff       	call   760 <setvbuf@plt>
 8ca:	90                   	nop
 8cb:	5d                   	pop    rbp
 8cc:	c3                   	ret

00000000000008cd <main>:
 8cd:	55                   	push   rbp
 8ce:	48 89 e5             	mov    rbp,rsp
 8d1:	48 83 ec 60          	sub    rsp,0x60
 8d5:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
 8dc:	00 00 
 8de:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
 8e2:	31 c0                	xor    eax,eax
 8e4:	b8 00 00 00 00       	mov    eax,0x0
 8e9:	e8 9c ff ff ff       	call   88a <init>
 8ee:	48 8d 45 a0          	lea    rax,[rbp-0x60]
 8f2:	48 89 c6             	mov    rsi,rax
 8f5:	48 8d 3d 6c 01 00 00 	lea    rdi,[rip+0x16c]        # a68 <_IO_stdin_used+0x8>
 8fc:	b8 00 00 00 00       	mov    eax,0x0
 901:	e8 1a fe ff ff       	call   720 <printf@plt>
 906:	48 89 e8             	mov    rax,rbp
 909:	48 89 c2             	mov    rdx,rax
 90c:	48 8d 45 a0          	lea    rax,[rbp-0x60]
 910:	48 29 c2             	sub    rdx,rax
 913:	48 89 d0             	mov    rax,rdx
 916:	48 89 c6             	mov    rsi,rax
 919:	48 8d 3d 60 01 00 00 	lea    rdi,[rip+0x160]        # a80 <_IO_stdin_used+0x20>
 920:	b8 00 00 00 00       	mov    eax,0x0
 925:	e8 f6 fd ff ff       	call   720 <printf@plt>
 92a:	48 8d 3d 73 01 00 00 	lea    rdi,[rip+0x173]        # aa4 <_IO_stdin_used+0x44>
 931:	e8 ca fd ff ff       	call   700 <puts@plt>
 936:	48 8d 3d 7b 01 00 00 	lea    rdi,[rip+0x17b]        # ab8 <_IO_stdin_used+0x58>
 93d:	b8 00 00 00 00       	mov    eax,0x0
 942:	e8 d9 fd ff ff       	call   720 <printf@plt>
 947:	48 8b 05 c2 06 20 00 	mov    rax,QWORD PTR [rip+0x2006c2]        # 201010 <stdout@GLIBC_2.2.5>
 94e:	48 89 c7             	mov    rdi,rax
 951:	e8 fa fd ff ff       	call   750 <fflush@plt>
 956:	48 8d 45 a0          	lea    rax,[rbp-0x60]
 95a:	ba 00 01 00 00       	mov    edx,0x100
 95f:	48 89 c6             	mov    rsi,rax
 962:	bf 00 00 00 00       	mov    edi,0x0
 967:	e8 c4 fd ff ff       	call   730 <read@plt>
 96c:	48 8d 45 a0          	lea    rax,[rbp-0x60]
 970:	48 89 c6             	mov    rsi,rax
 973:	48 8d 3d 46 01 00 00 	lea    rdi,[rip+0x146]        # ac0 <_IO_stdin_used+0x60>
 97a:	b8 00 00 00 00       	mov    eax,0x0
 97f:	e8 9c fd ff ff       	call   720 <printf@plt>
 984:	48 8d 3d 4d 01 00 00 	lea    rdi,[rip+0x14d]        # ad8 <_IO_stdin_used+0x78>
 98b:	e8 70 fd ff ff       	call   700 <puts@plt>
 990:	48 8d 3d 21 01 00 00 	lea    rdi,[rip+0x121]        # ab8 <_IO_stdin_used+0x58>
 997:	b8 00 00 00 00       	mov    eax,0x0
 99c:	e8 7f fd ff ff       	call   720 <printf@plt>
 9a1:	48 8b 05 68 06 20 00 	mov    rax,QWORD PTR [rip+0x200668]        # 201010 <stdout@GLIBC_2.2.5>
 9a8:	48 89 c7             	mov    rdi,rax
 9ab:	e8 a0 fd ff ff       	call   750 <fflush@plt>
 9b0:	48 8d 45 a0          	lea    rax,[rbp-0x60]
 9b4:	48 89 c7             	mov    rdi,rax
 9b7:	b8 00 00 00 00       	mov    eax,0x0
 9bc:	e8 7f fd ff ff       	call   740 <gets@plt>
 9c1:	b8 00 00 00 00       	mov    eax,0x0
 9c6:	48 8b 4d f8          	mov    rcx,QWORD PTR [rbp-0x8]
 9ca:	64 48 33 0c 25 28 00 	xor    rcx,QWORD PTR fs:0x28
 9d1:	00 00 
 9d3:	74 05                	je     9da <main+0x10d>
 9d5:	e8 36 fd ff ff       	call   710 <__stack_chk_fail@plt>
 9da:	c9                   	leave
 9db:	c3                   	ret
 9dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000000009e0 <__libc_csu_init>:
 9e0:	41 57                	push   r15
 9e2:	41 56                	push   r14
 9e4:	49 89 d7             	mov    r15,rdx
 9e7:	41 55                	push   r13
 9e9:	41 54                	push   r12
 9eb:	4c 8d 25 96 03 20 00 	lea    r12,[rip+0x200396]        # 200d88 <__frame_dummy_init_array_entry>
 9f2:	55                   	push   rbp
 9f3:	48 8d 2d 96 03 20 00 	lea    rbp,[rip+0x200396]        # 200d90 <__do_global_dtors_aux_fini_array_entry>
 9fa:	53                   	push   rbx
 9fb:	41 89 fd             	mov    r13d,edi
 9fe:	49 89 f6             	mov    r14,rsi
 a01:	4c 29 e5             	sub    rbp,r12
 a04:	48 83 ec 08          	sub    rsp,0x8
 a08:	48 c1 fd 03          	sar    rbp,0x3
 a0c:	e8 c7 fc ff ff       	call   6d8 <_init>
 a11:	48 85 ed             	test   rbp,rbp
 a14:	74 20                	je     a36 <__libc_csu_init+0x56>
 a16:	31 db                	xor    ebx,ebx
 a18:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
 a1f:	00 
 a20:	4c 89 fa             	mov    rdx,r15
 a23:	4c 89 f6             	mov    rsi,r14
 a26:	44 89 ef             	mov    edi,r13d
 a29:	41 ff 14 dc          	call   QWORD PTR [r12+rbx*8]
 a2d:	48 83 c3 01          	add    rbx,0x1
 a31:	48 39 dd             	cmp    rbp,rbx
 a34:	75 ea                	jne    a20 <__libc_csu_init+0x40>
 a36:	48 83 c4 08          	add    rsp,0x8
 a3a:	5b                   	pop    rbx
 a3b:	5d                   	pop    rbp
 a3c:	41 5c                	pop    r12
 a3e:	41 5d                	pop    r13
 a40:	41 5e                	pop    r14
 a42:	41 5f                	pop    r15
 a44:	c3                   	ret
 a45:	90                   	nop
 a46:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
 a4d:	00 00 00 

0000000000000a50 <__libc_csu_fini>:
 a50:	f3 c3                	repz ret

Disassembly of section .fini:

0000000000000a54 <_fini>:
 a54:	48 83 ec 08          	sub    rsp,0x8
 a58:	48 83 c4 08          	add    rsp,0x8
 a5c:	c3                   	ret
