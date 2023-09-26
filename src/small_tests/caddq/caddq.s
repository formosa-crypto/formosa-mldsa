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
	.file	"caddq.c"
	.text
	.align	1
	.p2align 2,,3
	.global	caddq
	.arch armv7e-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	caddq, %function
caddq:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L3
	and	r3, r3, r0, asr #31
	add	r0, r0, r3
	bx	lr
.L4:
	.align	2
.L3:
	.word	8380417
	.size	caddq, .-caddq
	.ident	"GCC: (15:10.3-2021.07-4) 10.3.1 20210621 (release)"
