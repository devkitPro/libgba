	.text
	.code 16

	.global	ArcTan
	.thumb_func
ArcTan:
	swi		9
	bx		lr

	.global	ArcTan2
	.thumb_func
ArcTan2:
	swi		10
	bx		lr

