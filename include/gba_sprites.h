//---------------------------------------------------------------------------------
#ifndef _gba_sprites_h_
#define _gba_sprites_h_
//---------------------------------------------------------------------------------

#include "gba_base.h"

typedef struct
{
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 dummy;
} OBJATTR;

typedef struct
{
	u16 dummy0[3];
	s16 pa;
	u16 dummy1[3];
	s16 pb;
	u16 dummy2[3];
	s16 pc;
	u16 dummy3[3];
	s16 pd;
} OBJAFFINE;


#define	OAM				((OBJATTR *)0x07000000)
#define OBJ_BASE_ADR	((void *)(VRAM + 0x10000))
#define BITMAP_OBJ_BASE_ADR	((void *)(VRAM + 0x14000))

// Sprite Attribute 0
#define OBJ_Y(m)			((m)&0x00ff)
#define OBJ_ROT_SCALE_ON	(1<<8)
#define OBJ_DISABLE			(1<<9)
#define OBJ_DOUBLE			(1<<9)
#define OBJ_MODE(m)			((m)<<10)
#define OBJ_MOSAIC			(1<<12)
#define	OBJ_256_COLOR		(1<<13)
#define	OBJ_16_COLOR		(0<<13)
#define OBJ_SHAPE(m)		((m)<<14)

// Sprite Attribute 1
#define OBJ_X(m)			((m)&0x01ff)
#define OBJ_ROT_SCALE(m)	((m)<<9)
#define OBJ_HFLIP			(1<<12)
#define OBJ_VFLIP			(1<<13)
#define OBJ_SIZE(m)			((m)<<14)

// Sprite Attribute 2
#define OBJ_CHAR(m)			((m)&0x03ff)
#define OBJ_PRIORITY(m)		((m)<<10)
#define OBJ_PALETTE(m)		((m)<<12)

//---------------------------------------------------------------------------------
#endif // _gba_sprites_h_
//---------------------------------------------------------------------------------
