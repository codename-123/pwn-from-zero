
./seccomp:     file format elf64-x86-64


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

0000000000001020 <seccomp_init@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   QWORD PTR [rip+0x2fca]        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    QWORD PTR [rip+0x2fcc]        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000001030 <seccomp_init@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    QWORD PTR [rip+0x2fca]        # 4000 <seccomp_init@Base>
    1036:	68 00 00 00 00       	push   0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001040 <seccomp_rule_add@plt>:
    1040:	ff 25 c2 2f 00 00    	jmp    QWORD PTR [rip+0x2fc2]        # 4008 <seccomp_rule_add@Base>
    1046:	68 01 00 00 00       	push   0x1
    104b:	e9 d0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001050 <puts@plt>:
    1050:	ff 25 ba 2f 00 00    	jmp    QWORD PTR [rip+0x2fba]        # 4010 <puts@GLIBC_2.2.5>
    1056:	68 02 00 00 00       	push   0x2
    105b:	e9 c0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001060 <seccomp_load@plt>:
    1060:	ff 25 b2 2f 00 00    	jmp    QWORD PTR [rip+0x2fb2]        # 4018 <seccomp_load@Base>
    1066:	68 03 00 00 00       	push   0x3
    106b:	e9 b0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001070 <mmap@plt>:
    1070:	ff 25 aa 2f 00 00    	jmp    QWORD PTR [rip+0x2faa]        # 4020 <mmap@GLIBC_2.2.5>
    1076:	68 04 00 00 00       	push   0x4
    107b:	e9 a0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001080 <printf@plt>:
    1080:	ff 25 a2 2f 00 00    	jmp    QWORD PTR [rip+0x2fa2]        # 4028 <printf@GLIBC_2.2.5>
    1086:	68 05 00 00 00       	push   0x5
    108b:	e9 90 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001090 <alarm@plt>:
    1090:	ff 25 9a 2f 00 00    	jmp    QWORD PTR [rip+0x2f9a]        # 4030 <alarm@GLIBC_2.2.5>
    1096:	68 06 00 00 00       	push   0x6
    109b:	e9 80 ff ff ff       	jmp    1020 <_init+0x20>

00000000000010a0 <read@plt>:
    10a0:	ff 25 92 2f 00 00    	jmp    QWORD PTR [rip+0x2f92]        # 4038 <read@GLIBC_2.2.5>
    10a6:	68 07 00 00 00       	push   0x7
    10ab:	e9 70 ff ff ff       	jmp    1020 <_init+0x20>

00000000000010b0 <signal@plt>:
    10b0:	ff 25 8a 2f 00 00    	jmp    QWORD PTR [rip+0x2f8a]        # 4040 <signal@GLIBC_2.2.5>
    10b6:	68 08 00 00 00       	push   0x8
    10bb:	e9 60 ff ff ff       	jmp    1020 <_init+0x20>

00000000000010c0 <setvbuf@plt>:
    10c0:	ff 25 82 2f 00 00    	jmp    QWORD PTR [rip+0x2f82]        # 4048 <setvbuf@GLIBC_2.2.5>
    10c6:	68 09 00 00 00       	push   0x9
    10cb:	e9 50 ff ff ff       	jmp    1020 <_init+0x20>

00000000000010d0 <exit@plt>:
    10d0:	ff 25 7a 2f 00 00    	jmp    QWORD PTR [rip+0x2f7a]        # 4050 <exit@GLIBC_2.2.5>
    10d6:	68 0a 00 00 00       	push   0xa
    10db:	e9 40 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .plt.got:

00000000000010e0 <__cxa_finalize@plt>:
    10e0:	ff 25 fa 2e 00 00    	jmp    QWORD PTR [rip+0x2efa]        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10e6:	66 90                	xchg   ax,ax

Disassembly of section .text:

00000000000010f0 <_start>:
    10f0:	31 ed                	xor    ebp,ebp
    10f2:	49 89 d1             	mov    r9,rdx
    10f5:	5e                   	pop    rsi
    10f6:	48 89 e2             	mov    rdx,rsp
    10f9:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    10fd:	50                   	push   rax
    10fe:	54                   	push   rsp
    10ff:	45 31 c0             	xor    r8d,r8d
    1102:	31 c9                	xor    ecx,ecx
    1104:	48 8d 3d c2 01 00 00 	lea    rdi,[rip+0x1c2]        # 12cd <main>
    110b:	ff 15 af 2e 00 00    	call   QWORD PTR [rip+0x2eaf]        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1111:	f4                   	hlt
    1112:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    1119:	00 00 00 
    111c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000001120 <deregister_tm_clones>:
    1120:	48 8d 3d 41 2f 00 00 	lea    rdi,[rip+0x2f41]        # 4068 <__TMC_END__>
    1127:	48 8d 05 3a 2f 00 00 	lea    rax,[rip+0x2f3a]        # 4068 <__TMC_END__>
    112e:	48 39 f8             	cmp    rax,rdi
    1131:	74 15                	je     1148 <deregister_tm_clones+0x28>
    1133:	48 8b 05 8e 2e 00 00 	mov    rax,QWORD PTR [rip+0x2e8e]        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    113a:	48 85 c0             	test   rax,rax
    113d:	74 09                	je     1148 <deregister_tm_clones+0x28>
    113f:	ff e0                	jmp    rax
    1141:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1148:	c3                   	ret
    1149:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001150 <register_tm_clones>:
    1150:	48 8d 3d 11 2f 00 00 	lea    rdi,[rip+0x2f11]        # 4068 <__TMC_END__>
    1157:	48 8d 35 0a 2f 00 00 	lea    rsi,[rip+0x2f0a]        # 4068 <__TMC_END__>
    115e:	48 29 fe             	sub    rsi,rdi
    1161:	48 89 f0             	mov    rax,rsi
    1164:	48 c1 ee 3f          	shr    rsi,0x3f
    1168:	48 c1 f8 03          	sar    rax,0x3
    116c:	48 01 c6             	add    rsi,rax
    116f:	48 d1 fe             	sar    rsi,1
    1172:	74 14                	je     1188 <register_tm_clones+0x38>
    1174:	48 8b 05 5d 2e 00 00 	mov    rax,QWORD PTR [rip+0x2e5d]        # 3fd8 <_ITM_registerTMCloneTable@Base>
    117b:	48 85 c0             	test   rax,rax
    117e:	74 08                	je     1188 <register_tm_clones+0x38>
    1180:	ff e0                	jmp    rax
    1182:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    1188:	c3                   	ret
    1189:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000001190 <__do_global_dtors_aux>:
    1190:	f3 0f 1e fa          	endbr64
    1194:	80 3d ed 2e 00 00 00 	cmp    BYTE PTR [rip+0x2eed],0x0        # 4088 <completed.0>
    119b:	75 2b                	jne    11c8 <__do_global_dtors_aux+0x38>
    119d:	55                   	push   rbp
    119e:	48 83 3d 3a 2e 00 00 	cmp    QWORD PTR [rip+0x2e3a],0x0        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    11a5:	00 
    11a6:	48 89 e5             	mov    rbp,rsp
    11a9:	74 0c                	je     11b7 <__do_global_dtors_aux+0x27>
    11ab:	48 8b 3d ae 2e 00 00 	mov    rdi,QWORD PTR [rip+0x2eae]        # 4060 <__dso_handle>
    11b2:	e8 29 ff ff ff       	call   10e0 <__cxa_finalize@plt>
    11b7:	e8 64 ff ff ff       	call   1120 <deregister_tm_clones>
    11bc:	c6 05 c5 2e 00 00 01 	mov    BYTE PTR [rip+0x2ec5],0x1        # 4088 <completed.0>
    11c3:	5d                   	pop    rbp
    11c4:	c3                   	ret
    11c5:	0f 1f 00             	nop    DWORD PTR [rax]
    11c8:	c3                   	ret
    11c9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000011d0 <frame_dummy>:
    11d0:	f3 0f 1e fa          	endbr64
    11d4:	e9 77 ff ff ff       	jmp    1150 <register_tm_clones>

00000000000011d9 <alarm_handler>:
    11d9:	55                   	push   rbp
    11da:	48 89 e5             	mov    rbp,rsp
    11dd:	48 8d 05 20 0e 00 00 	lea    rax,[rip+0xe20]        # 2004 <_IO_stdin_used+0x4>
    11e4:	48 89 c7             	mov    rdi,rax
    11e7:	e8 64 fe ff ff       	call   1050 <puts@plt>
    11ec:	bf ff ff ff ff       	mov    edi,0xffffffff
    11f1:	e8 da fe ff ff       	call   10d0 <exit@plt>

00000000000011f6 <init>:
    11f6:	55                   	push   rbp
    11f7:	48 89 e5             	mov    rbp,rsp
    11fa:	48 8b 05 7f 2e 00 00 	mov    rax,QWORD PTR [rip+0x2e7f]        # 4080 <stdin@GLIBC_2.2.5>
    1201:	b9 00 00 00 00       	mov    ecx,0x0
    1206:	ba 02 00 00 00       	mov    edx,0x2
    120b:	be 00 00 00 00       	mov    esi,0x0
    1210:	48 89 c7             	mov    rdi,rax
    1213:	e8 a8 fe ff ff       	call   10c0 <setvbuf@plt>
    1218:	48 8b 05 51 2e 00 00 	mov    rax,QWORD PTR [rip+0x2e51]        # 4070 <stdout@GLIBC_2.2.5>
    121f:	b9 00 00 00 00       	mov    ecx,0x0
    1224:	ba 02 00 00 00       	mov    edx,0x2
    1229:	be 00 00 00 00       	mov    esi,0x0
    122e:	48 89 c7             	mov    rdi,rax
    1231:	e8 8a fe ff ff       	call   10c0 <setvbuf@plt>
    1236:	48 8d 05 9c ff ff ff 	lea    rax,[rip+0xffffffffffffff9c]        # 11d9 <alarm_handler>
    123d:	48 89 c6             	mov    rsi,rax
    1240:	bf 0e 00 00 00       	mov    edi,0xe
    1245:	e8 66 fe ff ff       	call   10b0 <signal@plt>
    124a:	bf 0a 00 00 00       	mov    edi,0xa
    124f:	e8 3c fe ff ff       	call   1090 <alarm@plt>
    1254:	90                   	nop
    1255:	5d                   	pop    rbp
    1256:	c3                   	ret

0000000000001257 <banned_execve>:
    1257:	55                   	push   rbp
    1258:	48 89 e5             	mov    rbp,rsp
    125b:	48 83 ec 10          	sub    rsp,0x10
    125f:	bf 00 00 ff 7f       	mov    edi,0x7fff0000
    1264:	e8 c7 fd ff ff       	call   1030 <seccomp_init@plt>
    1269:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
    126d:	48 83 7d f8 00       	cmp    QWORD PTR [rbp-0x8],0x0
    1272:	75 0a                	jne    127e <banned_execve+0x27>
    1274:	bf 00 00 00 00       	mov    edi,0x0
    1279:	e8 52 fe ff ff       	call   10d0 <exit@plt>
    127e:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    1282:	b9 00 00 00 00       	mov    ecx,0x0
    1287:	ba 3b 00 00 00       	mov    edx,0x3b
    128c:	be 00 00 00 00       	mov    esi,0x0
    1291:	48 89 c7             	mov    rdi,rax
    1294:	b8 00 00 00 00       	mov    eax,0x0
    1299:	e8 a2 fd ff ff       	call   1040 <seccomp_rule_add@plt>
    129e:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    12a2:	b9 00 00 00 00       	mov    ecx,0x0
    12a7:	ba 42 01 00 00       	mov    edx,0x142
    12ac:	be 00 00 00 00       	mov    esi,0x0
    12b1:	48 89 c7             	mov    rdi,rax
    12b4:	b8 00 00 00 00       	mov    eax,0x0
    12b9:	e8 82 fd ff ff       	call   1040 <seccomp_rule_add@plt>
    12be:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    12c2:	48 89 c7             	mov    rdi,rax
    12c5:	e8 96 fd ff ff       	call   1060 <seccomp_load@plt>
    12ca:	90                   	nop
    12cb:	c9                   	leave
    12cc:	c3                   	ret

00000000000012cd <main>:
    12cd:	55                   	push   rbp
    12ce:	48 89 e5             	mov    rbp,rsp
    12d1:	48 83 ec 20          	sub    rsp,0x20
    12d5:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    12d8:	48 89 75 e0          	mov    QWORD PTR [rbp-0x20],rsi
    12dc:	41 b9 00 00 00 00    	mov    r9d,0x0
    12e2:	41 b8 ff ff ff ff    	mov    r8d,0xffffffff
    12e8:	b9 22 00 00 00       	mov    ecx,0x22
    12ed:	ba 07 00 00 00       	mov    edx,0x7
    12f2:	be 00 10 00 00       	mov    esi,0x1000
    12f7:	bf 00 00 00 00       	mov    edi,0x0
    12fc:	e8 6f fd ff ff       	call   1070 <mmap@plt>
    1301:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
    1305:	b8 00 00 00 00       	mov    eax,0x0
    130a:	e8 e7 fe ff ff       	call   11f6 <init>
    130f:	b8 00 00 00 00       	mov    eax,0x0
    1314:	e8 3e ff ff ff       	call   1257 <banned_execve>
    1319:	48 8d 05 ed 0c 00 00 	lea    rax,[rip+0xced]        # 200d <_IO_stdin_used+0xd>
    1320:	48 89 c7             	mov    rdi,rax
    1323:	b8 00 00 00 00       	mov    eax,0x0
    1328:	e8 53 fd ff ff       	call   1080 <printf@plt>
    132d:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    1331:	ba 00 10 00 00       	mov    edx,0x1000
    1336:	48 89 c6             	mov    rsi,rax
    1339:	bf 00 00 00 00       	mov    edi,0x0
    133e:	e8 5d fd ff ff       	call   10a0 <read@plt>
    1343:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    1347:	48 89 45 f0          	mov    QWORD PTR [rbp-0x10],rax
    134b:	48 8b 55 f0          	mov    rdx,QWORD PTR [rbp-0x10]
    134f:	b8 00 00 00 00       	mov    eax,0x0
    1354:	ff d2                	call   rdx
    1356:	90                   	nop
    1357:	c9                   	leave
    1358:	c3                   	ret

Disassembly of section .fini:

000000000000135c <_fini>:
    135c:	48 83 ec 08          	sub    rsp,0x8
    1360:	48 83 c4 08          	add    rsp,0x8
    1364:	c3                   	ret
