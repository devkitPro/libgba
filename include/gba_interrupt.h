#ifndef _gba_interrupt_h_
#define _gba_interrupt_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

typedef void ( * IntFn)(void);

struct IntTable{IntFn handler; u32 mask;};


typedef enum {	Int_Vblank, Int_Hblank, Int_Vcount,
				Int_Timer0,	Int_Timer1, Int_Timer2, Int_Timer3,
				Int_Serial,
				Int_DMA0,	Int_DMA1,	Int_DMA2,	Int_DMA3,
				Int_KeyPad,
				Int_Cart,
				Int_Count,
				Ints_All = 0x7fff } eINT;

#define INT_VECTOR	*(IntFn *)(0x03007ffc)		// BIOS Interrupt vector
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request


#define IE_VBL		(1<<0)
#define IE_HBL		(1<<1)
#define IE_VCNT		(1<<2)
#define IE_TIMER0	(1<<3)
#define IE_TIMER1	(1<<4)
#define IE_TIMER2	(1<<5)
#define IE_TIMER3	(1<<6)
#define IE_SERIAL	(1<<7)
#define IE_DMA0		(1<<8)
#define IE_DMA1		(1<<9)
#define IE_DMA2		(1<<10)
#define IE_DMA3		(1<<11)
#define IE_KEYPAD	(1<<12)
#define IE_GAMEPAK	(1<<13)

extern struct IntTable IntrTable[];

void InitInterrupt(void);
void SetInterrupt(eINT interrupt, IntFn function);
void EnableInterrupt(eINT interrupt);
void DisableInterrupt(eINT interrupt);
void IntrMain();
void IntrWait(u32 ReturnFlag, u32 IntFlag);

#define	VBlankIntrWait()	SystemCall(5)

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_interrupt_h_
