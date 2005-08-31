/*
	$Id: InterruptDispatcher.s,v 1.2 2005-08-31 23:17:30 wntrmute Exp $

	libgba interrupt dispatcher routines

	Copyright 2003-2005 by Dave Murphy.

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

	$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/src/InterruptDispatcher.s,v 1.2 2005-08-31 23:17:30 wntrmute Exp $

	$Log: not supported by cvs2svn $
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
	mov	r3, #0x4000000			@ REG_BASE
	ldr	r2, [r3,#0x200]			@ Read	REG_IE

	ldrh	r1, [r3, #0x8]			@ r1 = IME
	mrs	r0, spsr
	stmfd	sp!, {r0-r1,r3,lr}		@ {spsr, IME, REG_BASE, lr}

	and	r1, r2,	r2, lsr #16		@ r1 =	IE & IF

	ldrh	r2, [r3, #-8]			@\mix up with BIOS irq flags at 3007FF8h,
	orr	r2, r2, r1			@ aka mirrored at 3FFFFF8h, this is required
	strh	r2, [r3, #-8]			@/when using the (VBlank)IntrWait functions

	add	r3,r3,#0x200
	ldr	r2,=IntrTable

@---------------------------------------------------------------------------------
findIRQ:
@---------------------------------------------------------------------------------
	ldr	r0, [r2, #4]
	cmp	r0,#0
	beq	no_handler
	ands	r0, r0, r1
	bne	jump_intr
	add	r2, r2, #8
	b	findIRQ

@---------------------------------------------------------------------------------
no_handler:
@---------------------------------------------------------------------------------
	strh	r1, [r3, #2]			@ IF Clear
        ldmfd   sp!, {r0-r1,r3,lr}		@ {spsr, IME, REG_BASE, lr}
	mov	pc,lr

@---------------------------------------------------------------------------------
jump_intr:
@---------------------------------------------------------------------------------
	strh	r0, [r3, #2]			@ IF Clear
	ldr	r0, [r2]			@ Jump to user IRQ process

	mrs	r2, cpsr
	bic	r2, r2, #0xdf			@ \__
	orr	r2, r2, #0x1f			@ /  --> Enable IRQ & FIQ. Set CPU mode to System.
	msr	cpsr,r2

	stmfd	sp!, {lr}
	adr	lr, IntrRet
	bx	r0

@---------------------------------------------------------------------------------
IntrRet:
@---------------------------------------------------------------------------------
	ldmfd	sp!, {lr}

	mrs	r3, cpsr
	bic	r3, r3, #0xdf			@ \__
	orr	r3, r3, #0x92			@ /  --> Disable IRQ. Enable FIQ. Set CPU mode to IRQ.
	msr	cpsr, r3

        ldmfd   sp!, {r0-r1,r3,lr}		@ {spsr, IME, REG_BASE, lr}
	strh	r1, [r3, #0x8]			@ restore REG_IME
	msr	spsr, r0			@ restore spsr
	mov	pc,lr

	.pool
	.end
