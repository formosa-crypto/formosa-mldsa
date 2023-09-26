	.cpu cortex-m4
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"montgomery_reduce.c"
	.text
	.align	1
	.p2align 2,,3
	.global	montgomery_reduce
	.arch armv7e-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	montgomery_reduce, %function
montgomery_reduce:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	rsb	r2, r0, r0, lsl #3
	mov	r3, r0
	       push	{r4}
	add	r2, r0, r2, lsl #10
	ldr	r4, .L4
	mov	r0, r1
	add	r2, r3, r2, lsl #13
	smlal	r3, r0, r2, r4 
	        pop	{r4}
	bx	lr
.L5:
	.align	2
.L4:
	.word	-8380417
	.size	montgomery_reduce, .-montgomery_reduce
	.ident	"GCC: (15:10.3-2021.07-4) 10.3.1 20210621 (release)"
