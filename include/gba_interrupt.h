/*
	"$Id: gba_interrupt.h,v 1.2 2004-08-08 19:28:07 wntrmute Exp $"

	Header file for libgba interrupt handling

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_interrupt.h,v 1.2 2004-08-08 19:28:07 wntrmute Exp $"

*/

#ifndef _gba_interrupt_h_
#define _gba_interrupt_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

typedef void ( * IntFn)(void);

struct IntTable{IntFn handler; u32 mask;};


typedef enum {	Int_Vblank, Int_Hblank, Int_Vcount,
				Int_Timer0,	Int_Timer1, Int_Timer2, Int_Timer3,
				Int_Serial,
				Int_DMA0,	Int_DMA1,	Int_DMA2,	Int_DMA3,
				Int_KeyPad,
				Int_Cart,
				Int_Count,
				Ints_All = 0x7fff } eINT;

#define INT_VECTOR	*(IntFn *)(0x03007ffc)		// BIOS Interrupt vector
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request


#define IE_VBL		(1<<0)
#define IE_HBL		(1<<1)
#define IE_VCNT		(1<<2)
#define IE_TIMER0	(1<<3)
#define IE_TIMER1	(1<<4)
#define IE_TIMER2	(1<<5)
#define IE_TIMER3	(1<<6)
#define IE_SERIAL	(1<<7)
#define IE_DMA0		(1<<8)
#define IE_DMA1		(1<<9)
#define IE_DMA2		(1<<10)
#define IE_DMA3		(1<<11)
#define IE_KEYPAD	(1<<12)
#define IE_GAMEPAK	(1<<13)

extern struct IntTable IntrTable[];

void InitInterrupt(void);
void SetInterrupt(eINT interrupt, IntFn function);
void EnableInterrupt(eINT interrupt);
void DisableInterrupt(eINT interrupt);
void IntrMain();
void IntrWait(u32 ReturnFlag, u32 IntFlag);

#define	VBlankIntrWait()	SystemCall(5)

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_interrupt_h_
