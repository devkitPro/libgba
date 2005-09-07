/*
	"$Id: fade.h,v 1.3 2005-09-07 23:09:44 wntrmute Exp $"

	Header file for libgba palette fade routines

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/fade.h,v 1.3 2005-09-07 23:09:44 wntrmute Exp $"

*/

//---------------------------------------------------------------------------------
#ifndef _fade_h_
#define _fade_h_
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------
void	FadeToPalette(const u16 *NewPalette, int FrameCount);
void	FadeToGrayScale(int gray, int FrameCount);
void	SetPalette(u16 *Palette);

#define FadeToBlack(frames) FadeToGrayScale(0,frames)
//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
#endif // _fade_h_
//---------------------------------------------------------------------------------
