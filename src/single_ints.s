/*
	"$Id: single_ints.s,v 1.3 2005-08-23 17:02:06 wntrmute Exp $"

	libgba interrupt dispatcher routines

	Copyright 2003-2004 by Dave Murphy.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA.

	Please report all bugs and problems through the bug tracker at
	"http://sourceforge.net/tracker/?group_id=114505&atid=668551".

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/src/single_ints.s,v 1.3 2005-08-23 17:02:06 wntrmute Exp $"

*/

@---------------------------------------------------------------------------------
	.section	.iwram,"ax",%progbits
	.extern	IntrTable
	.code 32

	.global	IntrMain
@---------------------------------------------------------------------------------
IntrMain:
@---------------------------------------------------------------------------------
									@ Single interrupts support
	mov		r3,	#0x4000000			@ REG_BASE
	ldr		r2,	[r3,#0x200]			@ Read	REG_IE
	and		r1,	r2,	r2,	lsr	#16		@ r1 =	IE & IF

	ldrh	r2, [r3, #-8]			@\mix up with BIOS irq flags at 3007FF8h,
	orr		r2, r2, r1				@ aka mirrored at 3FFFFF8h, this is required
	strh	r2, [r3, #-8]			@/when using the (VBlank)IntrWait functions

	add		r3,r3,#0x200
	ldr		r2,=IntrTable

@---------------------------------------------------------------------------------
findIRQ:
@---------------------------------------------------------------------------------
	ldr		r0, [r2, #4]
	cmp		r0,#0
	beq		no_handler
	ands	r0,	r0,	r1
	bne		jump_intr
	add		r2, r2, #8
	b		findIRQ

@---------------------------------------------------------------------------------
no_handler:
@---------------------------------------------------------------------------------
	strh	r1,	[r3, #2]			@ IF Clear
	mov		pc,lr

@---------------------------------------------------------------------------------
jump_intr:
@---------------------------------------------------------------------------------
	strh	r0,	[r3, #2]			@ IF Clear

	mov		r0,lr

	ldr		r0,	[r2]				@ Jump	to user	IRQ	process
	bx		r0

	.pool
	.end
