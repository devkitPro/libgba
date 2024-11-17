/*

	libgba mbv2 support routines

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
#include "mbv2.h"

char __outstr[__DOUTBUFSIZE];

//---------------------------------------------------------------------------------
void mbv2_dprintf(char *str, ...)
//---------------------------------------------------------------------------------
{
	va_list args;
	char *string = __outstr;

	va_start(args, str);
	vsprintf(__outstr,str,args);
	va_end(args);

	while (*string)
		mbv2_dputchar(*string++);
}

//---------------------------------------------------------------------------------
void mbv2_dfprintf(int fp, char *str, ...)
//---------------------------------------------------------------------------------
{
	va_list args;
	char *string = __outstr;

	va_start(args, str);
	vsprintf(__outstr,str,args);
	va_end(args);


	while (*string)
	{
		__dputchar(__ESCCHR);
		__dputchar(__ESC_FPUTC_PROCESSED);

		mbv2_dputchar(*string++);
	}

}
