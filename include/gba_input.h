//---------------------------------------------------------------------------------
#ifndef _gba_input_h_
#define _gba_input_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------
#include "gba_base.h"

#define KEY_A		(1<<0)
#define KEY_B		(1<<1)
#define KEY_SELECT	(1<<2)
#define KEY_START	(1<<3)
#define KEY_RIGHT	(1<<4)
#define KEY_LEFT	(1<<5)
#define KEY_UP		(1<<6)
#define KEY_DOWN	(1<<7)
#define KEY_R		(1<<8)
#define KEY_L		(1<<9)

#define DPAD 	(KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT)

void	InitKeys();
void	ScanKeys();
u16		KeysDown();
u16		KeysUp();
u16		KeysHeld();
void	SetRepeat( int rpt);


#define REG_KEYINPUT	*(vu16*)(REG_BASE + 0x130)  // Key Input
#define REG_KEYCNT		*(vu16*)(REG_BASE + 0x132)  // Key Control


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_input_h_
//---------------------------------------------------------------------------------
