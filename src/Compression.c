/*

	libgba bios decompression functions

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

#include "gba_compression.h"

//---------------------------------------------------------------------------------
void BitUnPack(void  *source, void *dest, BUP* bup)
//---------------------------------------------------------------------------------
{
	SystemCall(16);
}

//---------------------------------------------------------------------------------
void LZ77UnCompWram(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(17);
}
//---------------------------------------------------------------------------------
void LZ77UnCompVram(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(18);
}
//---------------------------------------------------------------------------------
void HuffUnComp(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(19);
}
//---------------------------------------------------------------------------------
void RLUnCompWram(void *source, void *dest)
//--------------------------------------------------------------------------------
{
	SystemCall(20);
}
//---------------------------------------------------------------------------------
void RLUnCompVram(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(21);
}
//---------------------------------------------------------------------------------
void Diff8bitUnFilterWram(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(22);
}
//---------------------------------------------------------------------------------
void Diff8bitUnFilterVram(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(23);
}
//---------------------------------------------------------------------------------
void Diff16bitUnFilter(void *source, void *dest)
//---------------------------------------------------------------------------------
{
	SystemCall(24);
}
