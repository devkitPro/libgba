/*

	libgba mappy debug print routines

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
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define __DOUTBUFSIZE 256

char __outstr[__DOUTBUFSIZE];

//---------------------------------------------------------------------------------
// VBoy and Mappy debug console output
//---------------------------------------------------------------------------------
static void dprint(const char *sz)
//---------------------------------------------------------------------------------
{
	asm volatile(
	"mov r2, %0\n"
	"ldr r0, =0xc0ded00d\n"
	"mov r1, #0\n"
	"and r0, r0, r0\n"
	:
	:
	"r" (sz) :
	"r0", "r1", "r2");
}


//---------------------------------------------------------------------------------
void mappy_dprintf(char *str, ...)
//---------------------------------------------------------------------------------
{
	va_list args;

	va_start(args, str);
	vsnprintf(__outstr,__DOUTBUFSIZE,str,args);
	va_end(args);

	dprint(__outstr);
}

//---------------------------------------------------------------------------------
void	mappy_dputchar	(int c)
//---------------------------------------------------------------------------------
{
	snprintf(__outstr,__DOUTBUFSIZE,"%c",c);
	dprint(__outstr);
}



