/*

	Header file for libgba PCX decoder

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
#ifndef _pcx_h_
#define _pcx_h_
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

typedef struct{
char		manufacturer;
char		version;
char		encoding;
char		bpp;
short int	x1,y1;
short int	x2,y2;
short int	hres;
short int	vres;
char		palette[48];
char		reserved;
char		color_planes;
short int	BytesPerLine;
short int	PaletteType;
char		dummy[58];
}__attribute__ ((packed)) pcx_header;

void DecodePCX(const u8 *PCXBuffer, u16 *ScreenAddr, u16 *Palette);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
#endif // _pcx_h_
//---------------------------------------------------------------------------------
