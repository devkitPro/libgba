/*

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


*/

//---------------------------------------------------------------------------------
#include "gba_input.h"
//---------------------------------------------------------------------------------
typedef struct{
	u16 Up,
		Down,
		Held,
		Last,
		DownRepeat;
	}__attribute__ ((packed)) KeyInput;

//---------------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------------
static KeyInput Keys = { 0,0,0,0,0 };

static u8 delay = 60, repeat = 30, count = 60;

//---------------------------------------------------------------------------------
void setRepeat( int SetDelay, int SetRepeat)
//---------------------------------------------------------------------------------
{
	delay = SetDelay;
	repeat = SetRepeat;
}

//---------------------------------------------------------------------------------
void scanKeys(void)
//---------------------------------------------------------------------------------
{
	Keys.Last = Keys.Held;
	Keys.Held = (REG_KEYINPUT & 0x03ff) ^ 0x03ff; // upper 6 bits clear on hw not emulated


	u16 pressed = Keys.Held & ( Keys.Last ^ 0x03ff);

	Keys.DownRepeat	|=	pressed;
	Keys.Down |= pressed;


	u16 released = ((Keys.Held ^ 0x03ff) & Keys.Last);

	Keys.Up		|=	released;

	Keys.Down	&= ~released;
	Keys.DownRepeat	&= ~released;

	Keys.Up &= ~pressed;

	if ( Keys.Last != Keys.Held) count = delay;


	if ( delay != 0)
	{
		count--;
		if (count == 0)
		{
			count = repeat;
			Keys.DownRepeat |= Keys.Held;
		}
	}
}

//---------------------------------------------------------------------------------
u16 keysDownRepeat(void)
//---------------------------------------------------------------------------------
{
	u16 tmp = Keys.DownRepeat;
	Keys.DownRepeat = 0;

	return tmp;
}

//---------------------------------------------------------------------------------
u16 keysDown(void)
//---------------------------------------------------------------------------------
{
	u16 tmp = Keys.Down;
	Keys.Down = 0;

	return tmp;
}

//---------------------------------------------------------------------------------
u16 keysUp(void)
//---------------------------------------------------------------------------------
{
	u16 tmp = Keys.Up;
	Keys.Up = 0;

	return tmp;
}

//---------------------------------------------------------------------------------
u16 keysHeld(void)
//---------------------------------------------------------------------------------
{
	return Keys.Held;
}

