		.text
		.code 16

		.global	MultiBoot
		.thumb_func
MultiBoot:
		swi		37
		bx		lr
