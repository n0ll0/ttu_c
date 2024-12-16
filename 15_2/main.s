	.file	"main.c"
	.text
	.globl	fine_per_kmh
	.data
	.align 4
	.type	fine_per_kmh, @object
	.size	fine_per_kmh, 4
fine_per_kmh:
	.long	5
	.globl	max_fine
	.align 4
	.type	max_fine, @object
	.size	max_fine, 4
max_fine:
	.long	300
	.globl	general_proceeding_threshold
	.align 4
	.type	general_proceeding_threshold, @object
	.size	general_proceeding_threshold, 4
general_proceeding_threshold:
	.long	50
	.text
	.globl	calculate_fine
	.type	calculate_fine, @function
calculate_fine:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %eax
	subl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
	cmpl	$2, -8(%rbp)
	jg	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	fine_per_kmh(%rip), %eax
	movl	-8(%rbp), %edx
	imull	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	max_fine(%rip), %edx
	movl	-4(%rbp), %eax
	cmpl	%eax, %edx
	cmovle	%edx, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	calculate_fine, .-calculate_fine
	.section	.rodata
.LC0:
	.string	"Usage: %s [options]\n"
.LC1:
	.string	"Options:"
	.align 8
.LC2:
	.string	"  -f <fine_per_kmh>          Set fine per km/h (default: 5)"
	.align 8
.LC3:
	.string	"  -m <max_fine>              Set maximum fine (default: 300)"
	.align 8
.LC4:
	.string	"  -t <general_threshold>     Set general proceeding threshold (default: 50)"
	.text
	.globl	print_usage
	.type	print_usage, @function
print_usage:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	print_usage, .-print_usage
	.section	.rodata
.LC5:
	.string	"14_2_speeds.txt"
.LC6:
	.string	"hoiatustrahvid.txt"
.LC7:
	.string	"uldmenetluse_teated.txt"
.LC8:
	.string	"-f"
.LC9:
	.string	"-m"
.LC10:
	.string	"-t"
.LC11:
	.string	"r"
.LC12:
	.string	"w"
.LC13:
	.string	"Error opening file\n"
.LC14:
	.string	"%s %d %d"
.LC15:
	.string	"%s\n"
.LC16:
	.string	"Piirkiirus: %d km/h\n"
.LC17:
	.string	"M\303\265\303\265detud kiirus: %d km/h\n"
.LC18:
	.string	"\303\234letus: %d km/h\n\n"
.LC19:
	.string	"%s %d km/h %.2f EUR\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movl	%edi, -212(%rbp)
	movq	%rsi, -224(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC5(%rip), %rax
	movq	%rax, -176(%rbp)
	leaq	.LC6(%rip), %rax
	movq	%rax, -168(%rbp)
	leaq	.LC7(%rip), %rax
	movq	%rax, -160(%rbp)
	movl	$1, -192(%rbp)
	jmp	.L6
.L12:
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC8(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L7
	movl	-192(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -212(%rbp)
	jle	.L7
	addl	$1, -192(%rbp)
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, fine_per_kmh(%rip)
	jmp	.L8
.L7:
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC9(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L9
	movl	-192(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -212(%rbp)
	jle	.L9
	addl	$1, -192(%rbp)
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, max_fine(%rip)
	jmp	.L8
.L9:
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC10(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L10
	movl	-192(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -212(%rbp)
	jle	.L10
	addl	$1, -192(%rbp)
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, general_proceeding_threshold(%rip)
	jmp	.L8
.L10:
	movq	-224(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	print_usage
	movl	$1, %eax
	jmp	.L20
.L8:
	addl	$1, -192(%rbp)
.L6:
	movl	-192(%rbp), %eax
	cmpl	-212(%rbp), %eax
	jl	.L12
	movq	-176(%rbp), %rax
	leaq	.LC11(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -152(%rbp)
	movq	-168(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -144(%rbp)
	movq	-160(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -136(%rbp)
	cmpq	$0, -152(%rbp)
	je	.L13
	cmpq	$0, -144(%rbp)
	je	.L13
	cmpq	$0, -136(%rbp)
	jne	.L15
.L13:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$19, %edx
	movl	$1, %esi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L20
.L19:
	leaq	-196(%rbp), %rsi
	leaq	-200(%rbp), %rcx
	leaq	-122(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rsi, %r8
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	cmpl	$3, %eax
	je	.L16
	jmp	.L15
.L16:
	movl	-200(%rbp), %eax
	subl	$4, %eax
	movl	%eax, -188(%rbp)
	movl	-196(%rbp), %edx
	movl	-188(%rbp), %eax
	subl	%edx, %eax
	movl	%eax, -184(%rbp)
	movl	general_proceeding_threshold(%rip), %eax
	cmpl	%eax, -184(%rbp)
	jl	.L17
	leaq	-122(%rbp), %rdx
	movq	-136(%rbp), %rax
	leaq	.LC15(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	-196(%rbp), %edx
	movq	-136(%rbp), %rax
	leaq	.LC16(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	-200(%rbp), %edx
	movq	-136(%rbp), %rax
	leaq	.LC17(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	-184(%rbp), %edx
	movq	-136(%rbp), %rax
	leaq	.LC18(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L15
.L17:
	cmpl	$2, -184(%rbp)
	jle	.L15
	movl	-196(%rbp), %edx
	movl	-188(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	calculate_fine
	movl	%eax, -180(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-180(%rbp), %xmm1
	movq	%xmm1, %rsi
	movl	-184(%rbp), %ecx
	leaq	-122(%rbp), %rdx
	movq	-144(%rbp), %rax
	movq	%rsi, %xmm0
	leaq	.LC19(%rip), %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
.L15:
	movq	-152(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movl	$100, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	testq	%rax, %rax
	jne	.L19
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-136(%rbp), %rax
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
.LFE8:
	.size	main, .-main
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
