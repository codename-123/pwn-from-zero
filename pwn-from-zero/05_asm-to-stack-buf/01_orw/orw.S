
./orw:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	48 83 ec 08          	sub    rsp,0x8
    1004:	48 8b 05 c5 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fc5]        # 3fd0 <__gmon_start__@Base>
    100b:	48 85 c0             	test   rax,rax
    100e:	74 02                	je     1012 <_init+0x12>
    1010:	ff d0                	call   rax
    1012:	48 83 c4 08          	add    rsp,0x8
    1016:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <write@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   QWORD PTR [rip+0x2fca]        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    QWORD PTR [rip+0x2fcc]        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000001030 <write@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    QWORD PTR [rip+0x2fca]        # 4000 <write@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	push   0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001040 <read@plt>:
    1040:	ff 25 c2 2f 00 00    	jmp    QWORD PTR [rip+0x2fc2]        # 4008 <read@GLIBC_2.2.5>
    1046:	68 01 00 00 00       	push   0x1
    104b:	e9 d0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001050 <open@plt>:
    1050:	ff 25 ba 2f 00 00    	jmp    QWORD PTR [rip+0x2fba]        # 4010 <open@GLIBC_2.2.5>
    1056:	68 02 00 00 00       	push   0x2
    105b:	e9 c0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001060 <perror@plt>:
    1060:	ff 25 b2 2f 00 00    	jmp    QWORD PTR [rip+0x2fb2]        # 4018 <perror@GLIBC_2.2.5>
    1066:	68 03 00 00 00       	push   0x3
    106b:	e9 b0 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .plt.got:

0000000000001070 <__cxa_finalize@plt>:
    1070:	ff 25 6a 2f 00 00    	jmp    QWORD PTR [rip+0x2f6a]        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1076:	66 90                	xchg   ax,ax

Disassembly of section .text:

0000000000001080 <_start>:
    1080:	31 ed                	xor    ebp,ebp
    1082:	49 89 d1             	mov    r9,rdx
    1085:	5e                   	pop    rsi
    1086:	48 89 e2             	mov    rdx,rsp
    1089:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    108d:	50                   	push   rax
    108e:	54                   	push   rsp
    108f:	45 31 c0             	xor    r8d,r8d
    1092:	31 c9                	xor    ecx,ecx
    1094:	48 8d 3d ce 00 00 00 	lea    rdi,[rip+0xce]        # 1169 <main>
    109b:	ff 15 1f 2f 00 00    	call   QWORD PTR [rip+0x2f1f]        # 3fc0 <__libc_start_main@GLIBC_2.34>
    10a1:	f4                   	hlt
    10a2:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    10a9:	00 00 00 
    10ac:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000000010b0 <deregister_tm_clones>:
    10b0:	48 8d 3d 79 2f 00 00 	lea    rdi,[rip+0x2f79]        # 4030 <__TMC_END__>
    10b7:	48 8d 05 72 2f 00 00 	lea    rax,[rip+0x2f72]        # 4030 <__TMC_END__>
    10be:	48 39 f8             	cmp    rax,rdi
    10c1:	74 15                	je     10d8 <deregister_tm_clones+0x28>
    10c3:	48 8b 05 fe 2e 00 00 	mov    rax,QWORD PTR [rip+0x2efe]        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    10ca:	48 85 c0             	test   rax,rax
    10cd:	74 09                	je     10d8 <deregister_tm_clones+0x28>
    10cf:	ff e0                	jmp    rax
    10d1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10d8:	c3                   	ret
    10d9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000010e0 <register_tm_clones>:
    10e0:	48 8d 3d 49 2f 00 00 	lea    rdi,[rip+0x2f49]        # 4030 <__TMC_END__>
    10e7:	48 8d 35 42 2f 00 00 	lea    rsi,[rip+0x2f42]        # 4030 <__TMC_END__>
    10ee:	48 29 fe             	sub    rsi,rdi
    10f1:	48 89 f0             	mov    rax,rsi
    10f4:	48 c1 ee 3f          	shr    rsi,0x3f
    10f8:	48 c1 f8 03          	sar    rax,0x3
    10fc:	48 01 c6             	add    rsi,rax
    10ff:	48 d1 fe             	sar    rsi,1
    1102:	74 14                	je     1118 <register_tm_clones+0x38>
    1104:	48 8b 05 cd 2e 00 00 	mov    rax,QWORD PTR [rip+0x2ecd]        # 3fd8 <_ITM_registerTMCloneTable@Base>
    110b:	48 85 c0             	test   rax,rax
    110e:	74 08                	je     1118 <register_tm_clones+0x38>
    1110:	ff e0                	jmp    rax
    1112:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    1118:	c3                   	ret
    1119:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001120 <__do_global_dtors_aux>:
    1120:	f3 0f 1e fa          	endbr64
    1124:	80 3d 05 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f05],0x0        # 4030 <__TMC_END__>
    112b:	75 2b                	jne    1158 <__do_global_dtors_aux+0x38>
    112d:	55                   	push   rbp
    112e:	48 83 3d aa 2e 00 00 	cmp    QWORD PTR [rip+0x2eaa],0x0        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1135:	00 
    1136:	48 89 e5             	mov    rbp,rsp
    1139:	74 0c                	je     1147 <__do_global_dtors_aux+0x27>
    113b:	48 8b 3d e6 2e 00 00 	mov    rdi,QWORD PTR [rip+0x2ee6]        # 4028 <__dso_handle>
    1142:	e8 29 ff ff ff       	call   1070 <__cxa_finalize@plt>
    1147:	e8 64 ff ff ff       	call   10b0 <deregister_tm_clones>
    114c:	c6 05 dd 2e 00 00 01 	mov    BYTE PTR [rip+0x2edd],0x1        # 4030 <__TMC_END__>
    1153:	5d                   	pop    rbp
    1154:	c3                   	ret
    1155:	0f 1f 00             	nop    DWORD PTR [rax]
    1158:	c3                   	ret
    1159:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001160 <frame_dummy>:
    1160:	f3 0f 1e fa          	endbr64
    1164:	e9 77 ff ff ff       	jmp    10e0 <register_tm_clones>

0000000000001169 <main>:
    1169:	55                   	push   rbp
    116a:	48 89 e5             	mov    rbp,rsp
    116d:	48 83 ec 40          	sub    rsp,0x40
    1171:	be 00 00 00 00       	mov    esi,0x0
    1176:	48 8d 05 87 0e 00 00 	lea    rax,[rip+0xe87]        # 2004 <_IO_stdin_used+0x4>
    117d:	48 89 c7             	mov    rdi,rax
    1180:	b8 00 00 00 00       	mov    eax,0x0
    1185:	e8 c6 fe ff ff       	call   1050 <open@plt>
    118a:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
    118d:	83 7d fc 00          	cmp    DWORD PTR [rbp-0x4],0x0
    1191:	79 19                	jns    11ac <main+0x43>
    1193:	48 8d 05 74 0e 00 00 	lea    rax,[rip+0xe74]        # 200e <_IO_stdin_used+0xe>
    119a:	48 89 c7             	mov    rdi,rax
    119d:	e8 be fe ff ff       	call   1060 <perror@plt>
    11a2:	b8 01 00 00 00       	mov    eax,0x1
    11a7:	e9 81 00 00 00       	jmp    122d <main+0xc4>
    11ac:	48 c7 45 c0 00 00 00 	mov    QWORD PTR [rbp-0x40],0x0
    11b3:	00 
    11b4:	48 c7 45 c8 00 00 00 	mov    QWORD PTR [rbp-0x38],0x0
    11bb:	00 
    11bc:	48 c7 45 d0 00 00 00 	mov    QWORD PTR [rbp-0x30],0x0
    11c3:	00 
    11c4:	48 c7 45 d8 00 00 00 	mov    QWORD PTR [rbp-0x28],0x0
    11cb:	00 
    11cc:	48 c7 45 e0 00 00 00 	mov    QWORD PTR [rbp-0x20],0x0
    11d3:	00 
    11d4:	48 c7 45 e8 00 00 00 	mov    QWORD PTR [rbp-0x18],0x0
    11db:	00 
    11dc:	48 8d 4d c0          	lea    rcx,[rbp-0x40]
    11e0:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    11e3:	ba 30 00 00 00       	mov    edx,0x30
    11e8:	48 89 ce             	mov    rsi,rcx
    11eb:	89 c7                	mov    edi,eax
    11ed:	e8 4e fe ff ff       	call   1040 <read@plt>
    11f2:	48 89 45 f0          	mov    QWORD PTR [rbp-0x10],rax
    11f6:	48 83 7d f0 00       	cmp    QWORD PTR [rbp-0x10],0x0
    11fb:	79 16                	jns    1213 <main+0xaa>
    11fd:	48 8d 05 0f 0e 00 00 	lea    rax,[rip+0xe0f]        # 2013 <_IO_stdin_used+0x13>
    1204:	48 89 c7             	mov    rdi,rax
    1207:	e8 54 fe ff ff       	call   1060 <perror@plt>
    120c:	b8 01 00 00 00       	mov    eax,0x1
    1211:	eb 1a                	jmp    122d <main+0xc4>
    1213:	48 8b 55 f0          	mov    rdx,QWORD PTR [rbp-0x10]
    1217:	48 8d 45 c0          	lea    rax,[rbp-0x40]
    121b:	48 89 c6             	mov    rsi,rax
    121e:	bf 01 00 00 00       	mov    edi,0x1
    1223:	e8 08 fe ff ff       	call   1030 <write@plt>
    1228:	b8 00 00 00 00       	mov    eax,0x0
    122d:	c9                   	leave
    122e:	c3                   	ret

Disassembly of section .fini:

0000000000001230 <_fini>:
    1230:	48 83 ec 08          	sub    rsp,0x8
    1234:	48 83 c4 08          	add    rsp,0x8
    1238:	c3                   	ret
