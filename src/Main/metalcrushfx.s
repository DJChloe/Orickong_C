metalcrushfxtable
	.byt 32,134,250,96,0,0,0,0,0,0,31,7,16,16

_metalcrushfx	
	ldx #<metalcrushfxtable
	ldy #>metalcrushfxtable
	jmp $FA86
	