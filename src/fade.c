//---------------------------------------------------------------------------------
// GBA 256 color fade routines
// Fade to black implemented as a special case
// Calling FadeToPalette with a buffer of all zeros will do the same thing
//
// FadeToPalette will also perform a cross fade effect
//
//---------------------------------------------------------------------------------
#include "gba_video.h"
#include "gba_interrupt.h"
#include "gba_systemcalls.h"

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
void GetCurrentPalette()
//---------------------------------------------------------------------------------
{
	int i;
	u16 * Src = BG_COLORS;
	u16 * Dest = (u16 *)CurrentPalette;
	for (i = 0; i<512; i++)
	{
		*(Dest++) = *(Src++);
	}
}

//---------------------------------------------------------------------------------
void SetPalette(u16 *Palette)
//---------------------------------------------------------------------------------
{
	u16 *From, *To;
	From = (u16 *)Palette;
	To = (u16 *)BG_COLORS;
	int i;

	for (i = 0; i<512; i++)
	{
		*(To++) = *(From++);
	}
}

//---------------------------------------------------------------------------------
void DoFade(u32 FadeCount)
//---------------------------------------------------------------------------------
{
	int r,g,b,index,count,color;


	for (count=0; count<FadeCount;count++)
	{
		s16 *Src = FadeTable;
		u16 *Dest = CurrentPalette;

		for (index=0; index<512;index++)
		{
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
void FadeToGrayScale(int gray, int FrameCount)
//---------------------------------------------------------------------------------
{
	int index,r,g,b,color;
	u16 *Src;
	s16 *Table;

	GetCurrentPalette();
	Src = CurrentPalette;
	Table = FadeTable;

	for (index=0;index<512; index++)
	{
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
/**	New Palette is a pointer to an array of 512 colors
	The Sprite palette is included
*/
//---------------------------------------------------------------------------------
void FadeToPalette(const u16 *NewPalette, int FrameCount)
//---------------------------------------------------------------------------------
{
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

	for (index=0;index<512; index++)
	{

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

