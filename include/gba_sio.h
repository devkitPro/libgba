//---------------------------------------------------------------------------------
#ifndef	_gba_sio_h_
#define	_gba_sio_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------
#include "gba_base.h"

#define SIO_8BIT		0x0000	// Normal 8-bit communication mode
#define SIO_32BIT		0x1000	// Normal 32-bit communication mode
#define SIO_MULTI		0x2000	// Multi-play communication mode
#define SIO_UART		0x3000	// UART communication mode

#define SIO_IRQ			0x4000	// Enable serial irq


#define SIO_9600		0
#define SIO_38400		1
#define SIO_57600		2
#define SIO_115200		3

#define SIO_CLK_INT		(1<<0)	// Select internal clock
#define SIO_2MHZ_CLK	(1<<1)	// Select 2MHz clock
#define SIO_RDY			(1<<2)	// Opponent SO state
#define SIO_SO_HIGH		(1<<3)	// Our SO state
#define SIO_START		(1<<7)

#define REG_SIOCNT		*(vu16*)(REG_BASE + 0x128)	// Serial Communication Control
#define REG_SIODATA8	*(vu16*)(REG_BASE + 0x12a)	// 8bit Serial Communication Data
#define REG_SIODATA32	*(vu32*)(REG_BASE + 0x120)	// 32bit Serial Communication Data
#define REG_SIOMLT_SEND	*(vu16*)(REG_BASE + 0x12a)	// Multi-play SIO Send Data
#define REG_SIOMLT_RECV	*(vu16*)(REG_BASE + 0x120)	// Multi-play SIO Receive Data
#define REG_SIOMULTI0	*(vu16*)(REG_BASE + 0x120)	// Master data
#define REG_SIOMULTI1	*(vu16*)(REG_BASE + 0x122)	// Slave 1 data
#define REG_SIOMULTI2	*(vu16*)(REG_BASE + 0x124)	// Slave 2 data
#define REG_SIOMULTI3	*(vu16*)(REG_BASE + 0x126)	// Slave 3 data

#define REG_RCNT		*(vu16*)(REG_BASE + 0x134)
#define REG_HS_CTRL		*(vu16*)(REG_BASE + 0x140)
#define REG_JOYRE_L		*(vu16*)(REG_BASE + 0x150)
#define REG_JOYRE_H		*(vu16*)(REG_BASE + 0x152)
#define REG_JOYRE		*(vu32*)(REG_BASE + 0x150)

#define REG_JOYTR_L		*(vu16*)(REG_BASE + 0x154)
#define REG_JOYTR_H		*(vu16*)(REG_BASE + 0x156)
#define REG_JOYTR		*(vu32*)(REG_BASE + 0x154)

#define REG_JSTAT		*(vu16*)(REG_BASE + 0x158)


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_sio_h
