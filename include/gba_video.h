/*
	"$Id: gba_video.h,v 1.2 2004-08-08 19:28:07 wntrmute Exp $"

	Header file for libgba video definitions

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_video.h,v 1.2 2004-08-08 19:28:07 wntrmute Exp $"

*/

//---------------------------------------------------------------------------------
#ifndef _gba_video_h_
#define _gba_video_h_
//---------------------------------------------------------------------------------

#include "gba_base.h"

#define BG_COLORS		((u16 *)0x05000000)	// Background color table
#define	OBJ_COLORS		((u16 *)0x05000200)	// Sprite color table

#define	REG_DISPCNT		*(vu16 *)(REG_BASE + 0x00)

#define	MODE_0	0		// BG Mode 0
#define	MODE_1	1		// BG Mode 1
#define	MODE_2	2		// BG Mode 2
#define	MODE_3	3		// BG Mode 3
#define	MODE_4	4		// BG Mode 4
#define	MODE_5	5		// BG Mode 5

//---------------------------------------------------------------------------------
// LCDC control bits
//---------------------------------------------------------------------------------
#define BACKBUFFER	(1<<4)	// buffer display select
#define OBJ_1D_MAP	(1<<6)	// sprite 1 dimensional mapping
#define	LCDC_OFF	(1<<7)	// LCDC OFF
#define	BG0_ON		(1<<8)	// enable background 0
#define	BG1_ON		(1<<9)	// enable background 1
#define	BG2_ON		(1<<10)	// enable background 2
#define	BG3_ON		(1<<11)	// enable background 3
#define	OBJ_ON		(1<<12)	// enable sprites
#define	WIN0_ON		(1<<13)	// enable window 0
#define	WIN1_ON		(1<<14)	// enable window 1
#define	OBJ_WIN_ON	(1<<15)	// enable obj window

#define BG0_ENABLE		BG0_ON
#define BG1_ENABLE		BG1_ON
#define BG2_ENABLE		BG2_ON
#define BG3_ENABLE		BG3_ON
#define OBJ_ENABLE		OBJ_ON
#define WIN0_ENABLE		WIN0_ON
#define WIN1_ENABLE		WIN1_ON
#define OBJ_WIN_ENABLE	BG0_ON

#define	BG_ALL_ON		BG0_ON | BG1_ON | BG2_ON | BG3_ON 	    // All BG ON
#define	BG_ALL_ENABLE	BG0_ON | BG1_ON | BG2_ON | BG3_ON 	    // All BG ON

#define	REG_DISPSTAT	*(vu16 *)(REG_BASE + 0x04)

//---------------------------------------------------------------------------------
// LCDC Interrupt bits
//---------------------------------------------------------------------------------
#define LCDC_VBL_FLAG	(1<<0)
#define LCDC_HBL_FLAG	(1<<1)
#define LCDC_VCNT_FLAG	(1<<2)
#define LCDC_VBL		(1<<3)
#define LCDC_HBL		(1<<4)
#define LCDC_VCNT		(1<<5)
#define VCOUNT(m)		((m)<<8)


#define	REG_VCOUNT		*(vu16 *)(REG_BASE + 0x06)
#define BGCTRL			((vu16 *)(REG_BASE + 0x08))

typedef struct
{
	vu16 x;
	vu16 y;
} bg_scroll;

#define BG_OFFSET ((bg_scroll *)(REG_BASE + 0x10))

#define	BG0HOFS		*(vu16 *)(REG_BASE + 0x10)	// BG 0 H Offset
#define	BG0VOFS		*(vu16 *)(REG_BASE + 0x12)	// BG 0 V Offset
#define	BG1HOFS		*(vu16 *)(REG_BASE + 0x14)	// BG 1 H Offset
#define	BG1VOFS		*(vu16 *)(REG_BASE + 0x16)	// BG 1 V Offset
#define	BG2HOFS		*(vu16 *)(REG_BASE + 0x18)	// BG 2 H Offset
#define	BG2VOFS		*(vu16 *)(REG_BASE + 0x1a)	// BG 2 V Offset
#define	BG3HOFS		*(vu16 *)(REG_BASE + 0x1c)	// BG 3 H Offset
#define	BG3VOFS		*(vu16 *)(REG_BASE + 0x1e)	// BG 3 V Offset


//---------------------------------------------------------------------------------
// background control bits
//---------------------------------------------------------------------------------
#define BG_MOSAIC		(1<<6)
#define BG_16_COLOR		(0<<7)
#define BG_256_COLOR	(1<<7)
#define	BG_WRAP			(1<<13)	// wrapping on

#define	BG_SIZE_0	(0<<14)	// Map Size (256x256)
#define	BG_SIZE_1	(1<<14)	// Map Size (512x256)
#define	BG_SIZE_2	(2<<14)	// Map Size (256x512)
#define	BG_SIZE_3	(3<<14)	// Map Size (512x512)


#define	CHAR_BASE(m)		((m) << 2)
#define CHAR_BASE_ADR(m)	((void *)(VRAM + ((m) << 14)))
#define MAP_BASE_ADR(m)		((void *)(VRAM + ((m) << 11)))
#define SCREEN_BASE(m)		((m) << 8)


#define BG_PRIORITY(m)		((m))
#define BG_PALETTE(m)		((m)<<12)


//---------------------------------------------------------------------------------
// Framebuffers for mode 3 and 5
//---------------------------------------------------------------------------------
typedef u16 MODE3_LINE[240];
typedef u16 MODE5_LINE[160];

#define MODE3_FB ((MODE3_LINE *)0x06000000)
#define MODE5_FB ((MODE5_LINE *)0x06000000)
#define MODE3_BB ((MODE3_LINE *)0x0600A000)
#define MODE5_BB ((MODE5_LINE *)0x0600A000)

#define	REG_WIN0H	*(vu16 *)(REG_BASE + 0x40)
#define	REG_WIN1H	*(vu16 *)(REG_BASE + 0x42)
#define	REG_WIN0V	*(vu16 *)(REG_BASE + 0x44)
#define	REG_WIN1V	*(vu16 *)(REG_BASE + 0x46)
#define	REG_WININ	*(vu16 *)(REG_BASE + 0x48)
#define	REG_WINOUT	*(vu16 *)(REG_BASE + 0x4A)

#define	REG_MOSAIC	*(vu16 *)(REG_BASE + 0x4c)

#define	REG_BLDCNT		*(vu16 *)(REG_BASE + 0x50)
#define	REG_BLDALPHA	*(vu16 *)(REG_BASE + 0x52)
#define	REG_BLDY		*(vu16 *)(REG_BASE + 0x54)

//---------------------------------------------------------------------------------
// Helper macros
//---------------------------------------------------------------------------------
#define SetMode(mode)	(REG_DISPCNT = mode)

#define RGB5(r,g,b)	((r)|((g)<<5)|((b)<<10))
#define RGB8(r,g,b)	( (((b)>>3)<<10) | (((g)>>3)<<5) | ((r)>>3) )

//---------------------------------------------------------------------------------
#endif // _gba_video_h_
//---------------------------------------------------------------------------------
