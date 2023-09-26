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
	.file	"reduce32.c"
	.text
	.align	1
	.p2align 2,,3
	.global	reduce32
	.arch armv7e-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	reduce32, %function
reduce32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.

	add	r3, r0, #4194304
	asrs	r3, r3, #23
	rsb	r2, r3, r3, lsl #9
	add	r2, r3, r2, lsl #10
	rsb	r3, r3, r2, lsl #13

	add	r0, r0, r3
	bx	lr

	.size	reduce32, .-reduce32
	.ident	"GCC: (15:10.3-2021.07-4) 10.3.1 20210621 (release)"










