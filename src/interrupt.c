/*
	"$Id: interrupt.c,v 1.6 2005-12-14 14:13:12 wntrmute Exp $"

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

	$Log: not supported by cvs2svn $

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

	if (mask & IE_VBL) REG_DISPSTAT |= LCDC_VBL;
	if (mask & IE_HBL) REG_DISPSTAT |= LCDC_HBL;
	if (mask & IE_VCNT) REG_DISPSTAT |= LCDC_VCNT;
	REG_IE |= mask;
	REG_IME	= 1;
}

//---------------------------------------------------------------------------------
void DisableInterrupt(irqMASK mask)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;

	if (mask & IE_VBL) REG_DISPSTAT &= ~LCDC_VBL;
	if (mask & IE_HBL) REG_DISPSTAT &= ~LCDC_HBL;
	if (mask & IE_VCNT) REG_DISPSTAT &= ~LCDC_VCNT;
	REG_IE &= ~mask;

	REG_IME	= 1;

}
