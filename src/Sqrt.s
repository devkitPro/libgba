	.text
	.code 16

	.global	Sqrt
	.thumb_func
Sqrt:
	swi		8
	bx		lr
