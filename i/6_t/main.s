	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Enter distance %d in km (integer): "
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"%d"
	.text
	.p2align 4
	.globl	ReadDistances
	.type	ReadDistances, @function
ReadDistances:
.LFB24:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L6
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	.LC0(%rip), %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebx, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	.p2align 4,,10
	.p2align 3
.L3:
	addl	$1, %ebx
	movq	%r13, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	movl	%ebx, %edx
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	leaq	.LC1(%rip), %rdi
	xorl	%eax, %eax
	call	__isoc99_scanf@PLT
	addq	$4, %rbp
	cmpl	%r12d, %ebx
	jne	.L3
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE24:
	.size	ReadDistances, .-ReadDistances
	.p2align 4
	.globl	ConvertArrToMiles
	.type	ConvertArrToMiles, @function
ConvertArrToMiles:
.LFB25:
	.cfi_startproc
	endbr64
	testl	%edx, %edx
	jle	.L10
	leal	-1(%rdx), %eax
	cmpl	$2, %eax
	jbe	.L15
	movl	%edx, %ecx
	movaps	.LC2(%rip), %xmm1
	xorl	%eax, %eax
	shrl	$2, %ecx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L13:
	movdqu	(%rdi,%rax), %xmm2
	cvtdq2ps	%xmm2, %xmm0
	divps	%xmm1, %xmm0
	movups	%xmm0, (%rsi,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L13
	movl	%edx, %eax
	andl	$-4, %eax
	testb	$3, %dl
	je	.L17
.L12:
	movslq	%eax, %rcx
	pxor	%xmm0, %xmm0
	movss	.LC3(%rip), %xmm1
	cvtsi2ssl	(%rdi,%rcx,4), %xmm0
	divss	%xmm1, %xmm0
	movss	%xmm0, (%rsi,%rcx,4)
	leal	1(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L10
	movslq	%ecx, %rcx
	pxor	%xmm0, %xmm0
	addl	$2, %eax
	cvtsi2ssl	(%rdi,%rcx,4), %xmm0
	divss	%xmm1, %xmm0
	movss	%xmm0, (%rsi,%rcx,4)
	cmpl	%eax, %edx
	jle	.L10
	cltq
	pxor	%xmm0, %xmm0
	cvtsi2ssl	(%rdi,%rax,4), %xmm0
	divss	%xmm1, %xmm0
	movss	%xmm0, (%rsi,%rax,4)
.L10:
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	ret
.L15:
	xorl	%eax, %eax
	jmp	.L12
	.cfi_endproc
.LFE25:
	.size	ConvertArrToMiles, .-ConvertArrToMiles
	.section	.rodata.str1.1
.LC4:
	.string	"The converted distances are: "
.LC5:
	.string	"%.2f "
	.text
	.p2align 4
	.globl	PrintDistances
	.type	PrintDistances, @function
PrintDistances:
.LFB26:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%eax, %eax
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%esi, %ebp
	leaq	.LC4(%rip), %rsi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	$1, %edi
	call	__printf_chk@PLT
	testl	%ebp, %ebp
	jle	.L19
	leal	-1(%rbp), %eax
	leaq	.LC5(%rip), %rbp
	leaq	4(%rbx,%rax,4), %r12
	.p2align 4,,10
	.p2align 3
.L20:
	pxor	%xmm0, %xmm0
	movq	%rbp, %rsi
	movl	$1, %edi
	addq	$4, %rbx
	movl	$1, %eax
	cvtss2sd	-4(%rbx), %xmm0
	call	__printf_chk@PLT
	cmpq	%rbx, %r12
	jne	.L20
.L19:
	popq	%rbx
	.cfi_def_cfa_offset 24
	movl	$10, %edi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	putchar@PLT
	.cfi_endproc
.LFE26:
	.size	PrintDistances, .-PrintDistances
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"The sum of all distances is %.2f miles!\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	endbr64
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
	movl	$4, %esi
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	ReadDistances
	leaq	16(%rsp), %rdi
	movl	$4, %esi
	cvtdq2ps	(%rsp), %xmm0
	divps	.LC2(%rip), %xmm0
	movaps	%xmm0, 16(%rsp)
	call	PrintDistances
	pxor	%xmm0, %xmm0
	addss	16(%rsp), %xmm0
	addss	20(%rsp), %xmm0
	addss	24(%rsp), %xmm0
	addss	28(%rsp), %xmm0
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC7(%rip), %rsi
	cvtss2sd	%xmm0, %xmm0
	call	__printf_chk@PLT
	movq	40(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L26
	xorl	%eax, %eax
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.text
	.p2align 4
	.globl	SumOfAllDist
	.type	SumOfAllDist, @function
SumOfAllDist:
.LFB27:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L33
	leal	-1(%rsi), %eax
	cmpl	$2, %eax
	jbe	.L34
	movl	%esi, %edx
	movq	%rdi, %rax
	pxor	%xmm0, %xmm0
	shrl	$2, %edx
	salq	$4, %rdx
	addq	%rdi, %rdx
	.p2align 4,,10
	.p2align 3
.L30:
	movups	(%rax), %xmm1
	addq	$16, %rax
	addss	%xmm1, %xmm0
	movaps	%xmm1, %xmm2
	shufps	$85, %xmm1, %xmm2
	addss	%xmm2, %xmm0
	movaps	%xmm1, %xmm2
	unpckhps	%xmm1, %xmm2
	shufps	$255, %xmm1, %xmm1
	addss	%xmm0, %xmm2
	movaps	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	cmpq	%rdx, %rax
	jne	.L30
	movl	%esi, %eax
	andl	$-4, %eax
	testb	$3, %sil
	je	.L36
.L29:
	movslq	%eax, %rdx
	addss	(%rdi,%rdx,4), %xmm0
	leal	1(%rax), %edx
	cmpl	%edx, %esi
	jle	.L27
	movslq	%edx, %rdx
	addl	$2, %eax
	addss	(%rdi,%rdx,4), %xmm0
	cmpl	%eax, %esi
	jle	.L27
	cltq
	addss	(%rdi,%rax,4), %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L33:
	pxor	%xmm0, %xmm0
.L27:
	ret
	.p2align 4,,10
	.p2align 3
.L36:
	ret
.L34:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	jmp	.L29
	.cfi_endproc
.LFE27:
	.size	SumOfAllDist, .-SumOfAllDist
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC2:
	.long	1070461878
	.long	1070461878
	.long	1070461878
	.long	1070461878
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1070461878
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
