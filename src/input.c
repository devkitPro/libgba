/*
	"$Id: input.c,v 1.2 2004-08-09 17:04:51 wntrmute Exp $"

	libgba keypad input routines

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/src/input.c,v 1.2 2004-08-09 17:04:51 wntrmute Exp $"

*/

//---------------------------------------------------------------------------------
#include "gba_input.h"
//---------------------------------------------------------------------------------
typedef struct{
	u16 Up,
		Down,
		Held,
		Last;
	}__attribute__ ((packed)) KeyInput;

//---------------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------------
static KeyInput Keys = { 0,0,0.0 };

static u8 repeat = 30, count = 0;

//---------------------------------------------------------------------------------
void SetRepeat( int rpt)
//---------------------------------------------------------------------------------
{
	repeat = rpt;
}

//---------------------------------------------------------------------------------
void ScanKeys()
//---------------------------------------------------------------------------------
{
	Keys.Last = Keys.Held;
	Keys.Held = (REG_KEYINPUT & 0x03ff) ^ 0x03ff; // upper 6 bits clear on hw not emulated
	if ( (count++ > repeat) && (repeat != 0 ) )
	{
		Keys.Last = count = 0;
	}
	if ( Keys.Last != Keys.Held) count = 0;
}

//---------------------------------------------------------------------------------
u16	KeysDown()
//---------------------------------------------------------------------------------
{
	Keys.Down = Keys.Held & (Keys.Last ^ 0x03ff);

	return Keys.Down;
}

//---------------------------------------------------------------------------------
u16	KeysUp()
//---------------------------------------------------------------------------------
{
	Keys.Up = ((Keys.Held ^ 0x03ff) & Keys.Last);

	return Keys.Up;
}

//---------------------------------------------------------------------------------
u16	KeysHeld()
//---------------------------------------------------------------------------------
{
	return Keys.Held;
}

