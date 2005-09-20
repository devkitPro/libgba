/*
	"$Id: interrupt.c,v 1.4 2005-09-20 23:19:05 wntrmute Exp $"

	libgba interrupt support routines

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/src/interrupt.c,v 1.4 2005-09-20 23:19:05 wntrmute Exp $"

*/
#include "gba_interrupt.h"
#include "gba_video.h"

//---------------------------------------------------------------------------------
struct IntTable IntrTable[Int_Count];
void dummy(void) {};


//---------------------------------------------------------------------------------
void InitInterrupt(void)
//---------------------------------------------------------------------------------
{
	int i;

	// Set all interrupts to dummy functions.
	for(i = 0; i < Int_Count; i ++)
	{
		IntrTable[i].handler = dummy;
		IntrTable[i].mask = 0;
	}

	INT_VECTOR = IntrMain;

}

//---------------------------------------------------------------------------------
void SetInterrupt(eINT interrupt, IntFn function)
//---------------------------------------------------------------------------------
{
	int i;
	u32 mask = BIT(interrupt);

	for	(i=0;;i++)
	{
		if	(!IntrTable[i].mask || IntrTable[i].mask == mask) break;
	}

	IntrTable[i].handler	= function;
	IntrTable[i].mask		= mask;

}

//---------------------------------------------------------------------------------
void EnableInterrupt(eINT interrupt)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;
	switch(interrupt)
	{
		case Int_Vblank:
			REG_DISPSTAT |= LCDC_VBL;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Hblank:
			REG_DISPSTAT |= LCDC_HBL;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Vcount:
			REG_DISPSTAT |= LCDC_VCNT;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Timer0:
		case Int_Timer1:
		case Int_Timer2:
		case Int_Timer3:
		case Int_Serial:
		case Int_DMA0:
		case Int_DMA1:
		case Int_DMA2:
		case Int_DMA3:
		case Int_KeyPad:
		case Int_GamePak:
			REG_IE |= BIT(interrupt);
			break;
	}
	REG_IME	= 1;
}

//---------------------------------------------------------------------------------
void DisableInterrupt(eINT interrupt)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;

	switch(interrupt)
	{
		case Int_Vblank:
			REG_DISPSTAT &= ~LCDC_VBL;
			REG_IE &= BIT(interrupt);
			break;
		case Int_Hblank:
			REG_DISPSTAT &= ~LCDC_HBL;
			REG_IE &= BIT(interrupt);
			break;
		case Int_Vcount:
			REG_DISPSTAT &= ~LCDC_VCNT;
			REG_IE &= ~BIT(interrupt);
			break;
		case Int_Timer0:
		case Int_Timer1:
		case Int_Timer2:
		case Int_Timer3:
		case Int_Serial:
		case Int_DMA0:
		case Int_DMA1:
		case Int_DMA2:
		case Int_DMA3:
		case Int_KeyPad:
		case Int_GamePak:
			REG_IE &= ~BIT(interrupt);
			break;
		case Ints_All:
			REG_IE = 0;
			REG_DISPSTAT &= ~(LCDC_VBL | LCDC_HBL | LCDC_VCNT);
			break;
	}
	REG_IME	= 1;

}
