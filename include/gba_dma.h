#ifndef _gba_dma_h_
#define _gba_dma_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"


#define REG_DMA0SAD	*(vu32*)(REG_BASE + 0x0b0)
#define REG_DMA0DAD	*(vu32*)(REG_BASE + 0x0b4)
#define REG_DMA0CNT	*(vu32*)(REG_BASE + 0x0b8)

#define REG_DMA1SAD	*(vu32*)(REG_BASE + 0x0bc)
#define REG_DMA1DAD	*(vu32*)(REG_BASE + 0x0c0)
#define REG_DMA1CNT	*(vu32*)(REG_BASE + 0x0c4)

#define REG_DMA2SAD	*(vu32*)(REG_BASE + 0x0c8)
#define REG_DMA2DAD	*(vu32*)(REG_BASE + 0x0cc)
#define REG_DMA2CNT	*(vu32*)(REG_BASE + 0x0d0)

#define REG_DMA3SAD	*(vu32*)(REG_BASE + 0x0d4)
#define REG_DMA3DAD	*(vu32*)(REG_BASE + 0x0d8)
#define REG_DMA3CNT	*(vu32*)(REG_BASE + 0x0dc)


#define DMA_DST_INC		(0<<21)
#define DMA_DST_DEC		(1<<21)
#define DMA_DST_FIXED	(2<<21)
#define DMA_DST_RELOAD	(3<<21)

#define DMA_SRC_INC		(0<<23)
#define DMA_SRC_DEC		(1<<23)
#define DMA_SRC_FIXED	(2<<23)

#define DMA_REPEAT		(1<<25)

#define DMA16			(0<<26)
#define DMA32			(1<<26)

#define	GAMEPAK_DRQ		(1<<27)

#define DMA_IMMEDIATE	(0<<28)
#define DMA_VBLANK		(1<<28)
#define DMA_HBLANK		(2<<28)
#define DMA_SPECIAL		(3<<28)

#define DMA_IRQ			(1<<30)
#define DMA_ENABLE		(1<<31)

#define	DMA0COPY( source, dest, mode) \
	REG_DMA0SAD = source;	\
	REG_DMA0DAD = dest;		\
	REG_DMA0CNT = mode;

#define	DMA1COPY( source, dest, mode) \
	REG_DMA1SAD = (source);	\
	REG_DMA1DAD = (dest); \
	REG_DMA1CNT = (mode);

#define	DMA2COPY( source, dest, mode) \
	REG_DMA2SAD = source;	\
	REG_DMA2DAD = dest;		\
	REG_DMA2CNT = mode;

#define	DMA3COPY( source, dest, mode) \
	REG_DMA3SAD = source;	\
	REG_DMA3DAD = dest;		\
	REG_DMA3CNT = mode;

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_dma_h_
