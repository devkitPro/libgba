#ifndef _gba_timers_h_
#define _gba_timers_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

#define REG_TM0CNT_L	*(vu16*)(REG_BASE + 0x100)
#define REG_TM0CNT_H	*(vu16*)(REG_BASE + 0x102)
#define REG_TM1CNT_L	*(vu16*)(REG_BASE + 0x104)
#define REG_TM1CNT_H	*(vu16*)(REG_BASE + 0x106)
#define REG_TM2CNT_L	*(vu16*)(REG_BASE + 0x108)
#define REG_TM2CNT_H	*(vu16*)(REG_BASE + 0x10a)
#define REG_TM3CNT_L	*(vu16*)(REG_BASE + 0x10c)
#define REG_TM3CNT_H	*(vu16*)(REG_BASE + 0x10e)

#define	TIMER_COUNT	BIT(2)
#define	TIMER_IRQ	BIT(6)
#define	TIMER_START	BIT(7)


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_timers_h_
