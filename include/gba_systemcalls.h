//---------------------------------------------------------------------------------
#ifndef	_gba_systemcalls_h_
#define	_gba_systemcalls_h_
//---------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#include "gba_base.h"

#define SWI_BiosChecksum			13


//---------------------------------------------------------------------------------
// Reset Functions
//---------------------------------------------------------------------------------
enum	{ ROM_RESTART, RAM_RESTART };

void	SoftReset(u32 RestartFlag);

#define RESET_EWRAM		(1<<0)	// Clear 256K on-board WRAM
#define RESET_IWRAM		(1<<1)	// Clear 32K in-chip WRAM
#define RESET_PALETTE	(1<<2)	// Clear Palette
#define RESET_VRAM		(1<<3)	// Clear VRAM
#define RESET_OAM		(1<<4)	// Clear OAM. does NOT disable OBJs!
#define RESET_SIO		(1<<5)	// Switches to general purpose mode
#define RESET_SOUND		(1<<6)	// Reset Sound registers
#define RESET_OTHER		(1<<7)	// all other registers

void	RegisterRamReset(u32 ResetFlags);

//---------------------------------------------------------------------------------
// Interrupt functions
//---------------------------------------------------------------------------------

#define Halt()	SystemCall(2)
#define Stop()	SystemCall(3)


//---------------------------------------------------------------------------------
// Math functions
//---------------------------------------------------------------------------------
s32	Div(s32 Number, s32 Divisor);
s32	DivMod(s32 Number, s32 Divisor);
u32	DivAbs(s32 Number, s32 Divisor);
s32	DivArm(s32 Divisor, s32 Number);
s32	DivArmMod(s32 Divisor, s32 Number);
u32	DivArmAbs(s32 Divisor, s32 Number);

u16 Sqrt(u32 X);

s16 ArcTan(s16 Tan);
u16 ArcTan2(s16 X, s16 Y);


void CpuSet( const void *source, void *dest, u32 mode);
void CpuFastSet( const void *source, void *dest, u32 mode);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif


//---------------------------------------------------------------------------------
#endif //_gba_systemcalls_h_
