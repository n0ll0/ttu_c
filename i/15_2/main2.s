	.file	"main2.c"
	.text
	.section	.rodata
.LC4:
	.string	"r"
.LC5:
	.string	"14_2_speeds.txt"
.LC6:
	.string	"w"
.LC7:
	.string	"trahvid"
.LC8:
	.string	"menetlused"
.LC9:
	.string	"config.toml"
.LC10:
	.string	"general_proceeding_threshold"
.LC11:
	.string	"%f"
.LC12:
	.string	"fine_threshold"
.LC13:
	.string	"max_fine"
.LC14:
	.string	"fine_per_kmph"
.LC15:
	.string	"%s = "
	.align 8
.LC17:
	.string	"%s\nPiirkiirus: %.0f\nM66detud kiirus: %.0f\nYletus: %.0f\n\n"
.LC18:
	.string	"%s %.1f km/h %.2f EUR\n"
.LC19:
	.string	"%s %f %f"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movl	%edi, -100(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movss	.LC0(%rip), %xmm0
	movss	%xmm0, -84(%rbp)
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, -80(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -76(%rbp)
	movss	.LC3(%rip), %xmm0
	movss	%xmm0, -72(%rbp)
	leaq	.LC4(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L2
	movl	$1, %eax
	jmp	.L20
.L2:
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	.L4
	movl	$1, %eax
	jmp	.L20
.L4:
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L5
	movl	$1, %eax
	jmp	.L20
.L5:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L6
	movl	$1, %eax
	jmp	.L20
.L6:
	movl	$1, %esi
	movl	$40, %edi
	call	calloc@PLT
	movq	%rax, -24(%rbp)
	jmp	.L7
.L11:
	movq	-24(%rbp), %rax
	leaq	.LC10(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L8
	leaq	-76(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	jmp	.L7
.L8:
	movq	-24(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L9
	leaq	-72(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	jmp	.L7
.L9:
	movq	-24(%rbp), %rax
	leaq	.LC13(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L10
	leaq	-80(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	jmp	.L7
.L10:
	movq	-24(%rbp), %rax
	leaq	.LC14(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L7
	leaq	-84(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	nop
.L7:
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$1, %eax
	je	.L11
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$1, %esi
	movl	$100, %edi
	call	calloc@PLT
	movq	%rax, -16(%rbp)
	jmp	.L12
.L19:
	movss	-68(%rbp), %xmm0
	movss	-64(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC16(%rip), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -60(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-60(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jb	.L25
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movss	-68(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-64(%rbp), %xmm2
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm2, %xmm3
	movq	%xmm3, %rcx
	movq	-16(%rbp), %rdx
	movq	-40(%rbp), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rcx, %xmm0
	leaq	.LC17(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$3, %eax
	call	fprintf@PLT
	jmp	.L12
.L25:
	movss	-72(%rbp), %xmm1
	movss	-60(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jnb	.L23
	jmp	.L12
.L23:
	movss	-84(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-60(%rbp), %xmm1
	movss	-80(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jb	.L26
	movss	-84(%rbp), %xmm0
	mulss	-60(%rbp), %xmm0
	jmp	.L18
.L26:
	movss	-80(%rbp), %xmm0
.L18:
	cvtss2sd	%xmm0, %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	-60(%rbp), %xmm4
	movq	%xmm4, %rcx
	movq	-16(%rbp), %rdx
	movq	-48(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rcx, %xmm0
	leaq	.LC18(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
.L12:
	leaq	-64(%rbp), %rsi
	leaq	-68(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rsi, %r8
	leaq	.LC19(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	cmpl	$3, %eax
	je	.L19
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
.L20:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1084227584
	.align 4
.LC1:
	.long	1133903872
	.align 4
.LC2:
	.long	1112014848
	.align 4
.LC3:
	.long	1077936128
	.align 4
.LC16:
	.long	1082130432
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
