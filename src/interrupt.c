/*
	"$Id: interrupt.c,v 1.5 2005-10-05 12:08:49 wntrmute Exp $"

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/src/interrupt.c,v 1.5 2005-10-05 12:08:49 wntrmute Exp $"

*/
#include "gba_interrupt.h"
#include "gba_video.h"

//---------------------------------------------------------------------------------
struct IntTable IntrTable[MAX_INTS];
void dummy(void) {};


//---------------------------------------------------------------------------------
void InitInterrupt(void)
//---------------------------------------------------------------------------------
{
	int i;

	// Set all interrupts to dummy functions.
	for(i = 0; i < MAX_INTS; i ++)
	{
		IntrTable[i].handler = dummy;
		IntrTable[i].mask = 0;
	}

	INT_VECTOR = IntrMain;

}

//---------------------------------------------------------------------------------
IntFn* SetInterrupt(irqMASK mask, IntFn function)
//---------------------------------------------------------------------------------
{
	int i;

	for	(i=0;;i++) {
		if	(!IntrTable[i].mask || IntrTable[i].mask == mask) break;
	}

	if ( i >= MAX_INTS) return NULL;

	IntrTable[i].handler	= function;
	IntrTable[i].mask		= mask;
	
	return &IntrTable[i].handler;

}

//---------------------------------------------------------------------------------
void EnableInterrupt(irqMASK mask)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;
	switch(mask)
	{
		case IE_VBL:
			REG_DISPSTAT |= LCDC_VBL;
			REG_IE |= mask;
			break;
		case IE_HBL:
			REG_DISPSTAT |= LCDC_HBL;
			REG_IE |= mask;
			break;
		case IE_VCNT:
			REG_DISPSTAT |= LCDC_VCNT;
			REG_IE |= mask;
			break;
		case IE_TIMER0:    
		case IE_TIMER1:    
		case IE_TIMER2:
		case IE_TIMER3:
		case IE_SERIAL:
		case IE_DMA0:
		case IE_DMA1:
		case IE_DMA2:		
		case IE_DMA3:		
		case IE_KEYPAD:	    
		case IE_GAMEPAK:	    
			REG_IE |= mask;
			break;
	}
	REG_IME	= 1;
}

//---------------------------------------------------------------------------------
void DisableInterrupt(irqMASK mask)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;

	switch(mask)
	{
		case IE_VBL:
			REG_DISPSTAT &= ~LCDC_VBL;
			REG_IE &= ~mask;
			break;
		case IE_HBL:
			REG_DISPSTAT &= ~LCDC_HBL;
			REG_IE &= ~mask;
			break;
		case IE_VCNT:
			REG_DISPSTAT &= ~LCDC_VCNT;
			REG_IE &= ~mask;
			break;
		case IE_TIMER0:    
		case IE_TIMER1:    
		case IE_TIMER2:
		case IE_TIMER3:
		case IE_SERIAL:
		case IE_DMA0:
		case IE_DMA1:
		case IE_DMA2:		
		case IE_DMA3:		
		case IE_KEYPAD:	    
		case IE_GAMEPAK:	    
			REG_IE &= ~mask;
			break;
	}
	REG_IME	= 1;

}
