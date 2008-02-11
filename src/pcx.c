/*

	libgba pcx decoder routines

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
#include "gba_types.h"
#include "pcx.h"
//---------------------------------------------------------------------------------

u8 Buf[240];

//---------------------------------------------------------------------------------
// Screen address must be 16 bit boundary for VRAM
// Can be RAM buffer for later copying
// Palette can be direct to hardware or RAM buffer for fading
//---------------------------------------------------------------------------------
void DecodePCX(const u8 *PCXBuffer, u16 * ScreenAddr, u16* Palette)
//---------------------------------------------------------------------------------
{
	int c,l,r,g,b;
	int i;

	u16 *Scrn = ScreenAddr;
	pcx_header *header = (pcx_header *)PCXBuffer;
	u8 *Data = (u8*)PCXBuffer + sizeof(pcx_header);

	int Width =	 (header->x2 - header->x1)+1;
	int Height = (header->y2 - header->y1)+1;

	Width = ((Width+1)>>1)<<1;			// PCX width is always even regardless of image

	if	(Width>240 || Height>160) return;	// too big for VRAM :)


	u8 *wptr = Buf;

	int j,k;
	for (j=0; j<Height; j++)
	{
		for (k=0; k<Width;)
		{
			c = *(Data++);
			if ((c & 0xC0 ) == 0xC0)	// Upper 2 bits set denotes runcount
			{
				l = c & 0x3f;		// extract run count
				c = *(Data++);

				for (i=0;i<l;i++)
				{
					*(wptr++)=c;
				}

				k += l;
			}
			else
			{
				*(wptr++) = c;
				k++;
			}
		}
		u16* ptr = (u16 *)Buf;
		for	(i=0;i<Width>>1;i++)
		{
			*(Scrn++)=*(ptr++);
		}
		wptr = Buf;
	}


	Data++;						// skip palette ID byte
	u16 * GBA_Palette = Palette;
	u16 color;

	// convert RGB triplets to GBA format 5:5:5
	for (i=0; i<256; i++)
	{
		r = *(Data++);
		g = *(Data++);
		b = *(Data++);

		color = ((r>>3)|((g>>3)<<5)|((b>>3)<<10));
		*(GBA_Palette++) = color;
	}
}

