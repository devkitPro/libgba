/*

	libgba 256 color fade routines

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

/*---------------------------------------------------------------------------------
	Fade to black implemented as a special case
	Calling FadeToPalette with a buffer of all zeros will do the same thing

	FadeToPalette will also perform a cross fade effect

---------------------------------------------------------------------------------*/
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <fade.h>

//---------------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------------
u16 CurrentPalette[512] EWRAM_BSS;

//---------------------------------------------------------------------------------
// fade table consists of color components & offsets in 8:8 form
// Red offset, Red component ...
//---------------------------------------------------------------------------------
s16 FadeTable[512*3*2] EWRAM_BSS;

//---------------------------------------------------------------------------------
static void GetCurrentPalette() {
//---------------------------------------------------------------------------------
	int i;
	u16 * Src = BG_COLORS;
	u16 * Dest = (u16 *)CurrentPalette;
	for (i = 0; i<512; i++) {
		*(Dest++) = *(Src++);
	}
}

//---------------------------------------------------------------------------------
void SetPalette(u16 *Palette) {
//---------------------------------------------------------------------------------
	u16 *From, *To;
	From = (u16 *)Palette;
	To = (u16 *)BG_COLORS;
	int i;

	for (i = 0; i<512; i++) {
		*(To++) = *(From++);
	}
}

//---------------------------------------------------------------------------------
static void DoFade(u32 FadeCount) {
//---------------------------------------------------------------------------------
	int r,g,b,index,count,color;


	for (count=0; count<FadeCount;count++) {
		s16 *Src = FadeTable;
		u16 *Dest = CurrentPalette;

		for (index=0; index<512;index++) {
			r = *(Src++);
			r += *(Src);
			*(Src++)=r;

			g = *(Src++);
			g += *(Src);
			*(Src++)=g;

			b = *(Src++);
			b += *(Src);
			*(Src++)=b;

			color = (r>>8) | ((g>>8)<<5) | ((b>>8)<<10);
			*(Dest++) = color;
		}

		VBlankIntrWait();
		SetPalette(CurrentPalette);
	}
}

//---------------------------------------------------------------------------------
/// Fade to a shade of grey
//---------------------------------------------------------------------------------
/**	Special case function for fade to Grey
	gray = 0 - 31 - final value of all components
*/
//---------------------------------------------------------------------------------
void FadeToGrayScale(int gray, int FrameCount) {
//---------------------------------------------------------------------------------
	int index,r,g,b,color;
	u16 *Src;
	s16 *Table;

	GetCurrentPalette();
	Src = CurrentPalette;
	Table = FadeTable;

	for (index=0;index<512; index++) {

		color = *(Src++);
		r = (color & 0x1f) << 8;
		g = (color>>5 & 0x1f) << 8;
		b = (color>>10 & 0x1f) << 8;

		*Table++ = ((gray<<8)-r) / FrameCount;
		*Table++ = r;

		*Table++ = ((gray<<8)-g) / FrameCount;
		*Table++ = g;

		*Table++ = ((gray<<8)-b) / FrameCount;
		*Table++ = b;
	}

	DoFade( FrameCount);
}

//---------------------------------------------------------------------------------
/// Fade to a specific palette
//---------------------------------------------------------------------------------
void FadeToPalette(const u16 *NewPalette, int FrameCount) {
//---------------------------------------------------------------------------------
	int index;
	GetCurrentPalette();

	u16 *Src;
	u16 *Dest;
	s16 *Table;

	u16 color;
	s16 r1,r2,g1,g2,b1,b2;

	Src = CurrentPalette;
	Dest = (u16 *)NewPalette;
	Table = FadeTable;

	for (index=0;index<512; index++) {

		color = *(Src++);
		r1 = (color & 0x1f) << 8;				// get component & convert to 8:8
		g1 = (color>>5 & 0x1f) << 8;
		b1 = (color>>10 & 0x1f) << 8;

		color = *(Dest++);
		r2 = (color & 0x1f) << 8;
		g2 = (color>>5 & 0x1f) << 8;
		b2 = (color>>10 & 0x1f) << 8;

		*(Table++) = (r2 - r1) / FrameCount;	// Set component Delta
		*(Table++) = r1;						// Set component start value
		*(Table++) = (g2 - g1) / FrameCount;
		*(Table++) = g1;
		*(Table++) = (b2 - b1) / FrameCount;
		*(Table++) = b1;
	}

	DoFade(FrameCount);

}

