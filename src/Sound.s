	.text
	.code 16


	.global	SoundDriverMode
	.thumb_func
SoundDriverMode:
	swi		27
	bx		lr

	.global	SoundDriverInit
	.thumb_func
SoundDriverInit:
	swi		26
	bx		lr
