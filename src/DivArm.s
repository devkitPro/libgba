		.text
		.code 16


		.global	DivArm
		.thumb_func
DivArm:	swi	7
		bx	lr

		.global	DivArmMod
		.thumb_func
DivArmMod:
		swi	7
		mov	r0, r1
		bx	lr

		.global	DivArmAbs
		.thumb_func
DivArmAbs:
		swi	7
		mov	r0, r3
		bx	lr
