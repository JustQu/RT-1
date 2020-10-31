	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.section	__TEXT,__literal4,4byte_literals
	.p2align	2               ## -- Begin function read_vec
LCPI0_0:
	.long	1077936128              ## float 3
LCPI0_1:
	.long	1073741824              ## float 2
LCPI0_2:
	.long	1065353216              ## float 1
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_read_vec
	.p2align	4, 0x90
_read_vec:                              ## @read_vec
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movss	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero,zero,zero
	movss	LCPI0_1(%rip), %xmm1    ## xmm1 = mem[0],zero,zero,zero
	movss	LCPI0_2(%rip), %xmm2    ## xmm2 = mem[0],zero,zero,zero
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdx
	movslq	-12(%rbp), %rdi
	addq	%rdi, %rdx
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movq	-32(%rbp), %rdx
	movss	%xmm2, (%rdx)
	movq	-32(%rbp), %rdx
	movss	%xmm1, 4(%rdx)
	movq	-32(%rbp), %rdx
	movss	%xmm0, 8(%rdx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$320, %rsp              ## imm = 0x140
	leaq	-272(%rbp), %rdi
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -276(%rbp)
	leaq	L_.str(%rip), %rsi
	movl	$256, %edx              ## imm = 0x100
	callq	___strcpy_chk
	movl	$0, -280(%rbp)
	movq	%rax, -312(%rbp)        ## 8-byte Spill
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-280(%rbp), %eax
	cmpl	_g_array_size(%rip), %eax
	jge	LBB1_5
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	leaq	-272(%rbp), %rdi
	movslq	-280(%rbp), %rax
	imulq	$48, %rax, %rax
	leaq	_g_array(%rip), %rcx
	addq	%rax, %rcx
	movq	%rcx, %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB1_4
## %bb.3:
	xorl	%eax, %eax
	movl	%eax, %edi
	movslq	-280(%rbp), %rcx
	imulq	$48, %rcx, %rcx
	leaq	_g_array(%rip), %rdx
	movq	%rdx, %rsi
	addq	%rcx, %rsi
	movq	40(%rsi), %rcx
	movslq	-280(%rbp), %rsi
	imulq	$48, %rsi, %rsi
	addq	%rsi, %rdx
	movl	32(%rdx), %esi
	leaq	-304(%rbp), %rdx
	movb	$0, %al
	callq	*%rcx
	movss	-292(%rbp), %xmm0       ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movss	-288(%rbp), %xmm1       ## xmm1 = mem[0],zero,zero,zero
	cvtss2sd	%xmm1, %xmm1
	movss	-284(%rbp), %xmm2       ## xmm2 = mem[0],zero,zero,zero
	cvtss2sd	%xmm2, %xmm2
	leaq	L_.str.1(%rip), %rdi
	movb	$3, %al
	callq	_printf
	movl	$0, -276(%rbp)
	movl	%eax, -316(%rbp)        ## 4-byte Spill
	jmp	LBB1_5
LBB1_4:                                 ##   in Loop: Header=BB1_1 Depth=1
	movl	-280(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -280(%rbp)
	jmp	LBB1_1
LBB1_5:
	movl	-276(%rbp), %eax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -320(%rbp)        ## 4-byte Spill
	jne	LBB1_7
## %bb.6:
	movl	-320(%rbp), %eax        ## 4-byte Reload
	addq	$320, %rsp              ## imm = 0x140
	popq	%rbp
	retq
LBB1_7:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_g_array                ## @g_array
	.p2align	4
_g_array:
	.asciz	"origin\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.long	0                       ## 0x0
	.space	4
	.quad	_read_vec
	.asciz	"rotation\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.long	12                      ## 0xc
	.space	4
	.quad	_read_vec

	.globl	_g_array_size           ## @g_array_size
	.p2align	2
_g_array_size:
	.long	2                       ## 0x2

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"rotation"

L_.str.1:                               ## @.str.1
	.asciz	"%f %f %f\n"


.subsections_via_symbols
