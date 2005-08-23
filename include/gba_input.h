/*
	"$Id: gba_input.h,v 1.4 2005-08-23 17:02:06 wntrmute Exp $"

	Header file for libgba input functions

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_input.h,v 1.4 2005-08-23 17:02:06 wntrmute Exp $"

*/

//---------------------------------------------------------------------------------
#ifndef _gba_input_h_
#define _gba_input_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------
#include "gba_base.h"

#define KEY_A		(1<<0)
#define KEY_B		(1<<1)
#define KEY_SELECT	(1<<2)
#define KEY_START	(1<<3)
#define KEY_RIGHT	(1<<4)
#define KEY_LEFT	(1<<5)
#define KEY_UP		(1<<6)
#define KEY_DOWN	(1<<7)
#define KEY_R		(1<<8)
#define KEY_L		(1<<9)

#define DPAD 	(KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT)

void	ScanKeys(void);
u16		KeysDown(void);
u16		KeysDownRepeat(void);
u16		KeysUp(void);
u16		KeysHeld(void);
void	SetRepeat( int SetDelay, int SetRepeat);


#define REG_KEYINPUT	*(vu16*)(REG_BASE + 0x130)  // Key Input
#define REG_KEYCNT		*(vu16*)(REG_BASE + 0x132)  // Key Control


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_input_h_
//---------------------------------------------------------------------------------
