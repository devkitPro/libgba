//---------------------------------------------------------------------------------
#ifndef _gba_base_h_
#define _gba_base_h_
//---------------------------------------------------------------------------------

#include "gba_types.h"

#define	VRAM		0x06000000
#define	IWRAM		0x03000000
#define	EWRAM		0x02000000
#define	EWRAM_END	0x02040000
#define	SRAM		0x0E000000
#define	REG_BASE	0x04000000

#ifndef	NULL
#define	NULL	0
#endif

//---------------------------------------------------------------------------------
#if	defined	( __thumb__ )
#define	SystemCall(Number)	 asm ("SWI	  "#Number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	SystemCall(Number)	 asm ("SWI	  "#Number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif

#define BIT(number) (1<<(number))

#define IWRAM_CODE __attribute__((section(".iwram"), long_call))
#define EWRAM_CODE __attribute__((section(".ewram"), long_call))

#define IWRAM_DATA	__attribute__((section(".iwram")))
#define EWRAM_DATA	__attribute__((section(".ewram")))
#define EWRAM_BSS	__attribute__((section(".sbss")))


//---------------------------------------------------------------------------------
// modes for DMA and CPU(Fast)Set
//---------------------------------------------------------------------------------
#define FILL	(1<<24)
#define COPY16	(0<<26)
#define COPY32	(1<<26)


//---------------------------------------------------------------------------------
#endif //_gba_base_h
//---------------------------------------------------------------------------------
