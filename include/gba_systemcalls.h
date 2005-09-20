/*
	"$Id: gba_systemcalls.h,v 1.3 2005-09-20 23:19:05 wntrmute Exp $"

	Header file for libgba bios systemcalls

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_systemcalls.h,v 1.3 2005-09-20 23:19:05 wntrmute Exp $"

*/

/*! \file gba_systemcalls.h
    \brief gba bios support.

*/

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
typedef enum RESTART_FLAG {
	ROM_RESTART,	/**< Restart from RAM entry point. */
	RAM_RESTART		/**< restart from ROM entry point */
} RESTART_FLAG;


/*! \fn void SoftReset(RESTART_FLAG RestartFlag)
    \brief reset the GBA.
    \param RestartFlag Mask
*/
void	SoftReset(RESTART_FLAG RestartFlag);

enum RESET_FLAG {
	RESET_EWRAM		=	(1<<0),	/**< Clear 256K on-board WRAM			*/
	RESET_IWRAM		=	(1<<1),	/**< Clear 32K in-chip WRAM				*/
	RESET_PALETTE	=	(1<<2),	/**< Clear Palette						*/
	RESET_VRAM		=	(1<<3),	/**< Clear VRAM							*/
	RESET_OAM		=	(1<<4),	/**< Clear OAM							*/
	RESET_SIO		=	(1<<5),	/**< Switches to general purpose mode	*/
	RESET_SOUND		=	(1<<6),	/**< Reset Sound registers				*/
	RESET_OTHER		=	(1<<7)	/**< all other registers				*/
};

typedef enum RESET_FLAG RESET_FLAGS;

/*! \fn void RegisterRamReset(RESET_FLAGS ResetFlags)
    \brief reset the GBA registers and RAM.
    \param ResetFlags Mask
*/
void RegisterRamReset(RESET_FLAGS ResetFlags);

//---------------------------------------------------------------------------------
// Interrupt functions
//---------------------------------------------------------------------------------

static inline void Halt()	{ SystemCall(2); }
static inline void Stop()	{ SystemCall(3); }


//---------------------------------------------------------------------------------
// Math functions
//---------------------------------------------------------------------------------
/*! \fn s32 Div(s32 Number, s32 Divisor)
	\param Number
	\param Divisor
*/
s32	Div(s32 Number, s32 Divisor);
/*! \fn s32 DivMod(s32 Number, s32 Divisor)
	\param Number
	\param Divisor

*/
s32	DivMod(s32 Number, s32 Divisor);
/*! \fn u32 DivAbs(s32 Number, s32 Divisor)
	\param Number
	\param Divisor
*/
u32	DivAbs(s32 Number, s32 Divisor);
/*! \fn s32 DivArm(s32 Number, s32 Divisor)
	\param Number
	\param Divisor
*/
s32	DivArm(s32 Divisor, s32 Number);
/*! \fn s32 DivArmMod(s32 Number, s32 Divisor)
	\param Number
	\param Divisor
*/
s32	DivArmMod(s32 Divisor, s32 Number);
/*! \fn u32 DivArmAbs(s32 Number, s32 Divisor)
	\param Number
	\param Divisor
*/
u32	DivArmAbs(s32 Divisor, s32 Number);
/*! \fn u16 Sqrt(u32 X)
	\param X
*/
u16 Sqrt(u32 X);

/*! \fn s16 ArcTan(s16 Tan)
	\param Tan
*/
s16 ArcTan(s16 Tan);
/*! \fn s16 ArcTan2(s16 X, s16 Y)
	\param X
	\param Y
*/
u16 ArcTan2(s16 X, s16 Y);

/*! \fn CpuSet( const void *source, void *dest, u32 mode)
	\param source
	\param dest
	\param mode
*/
void CpuSet( const void *source, void *dest, u32 mode);
/*! \fn CpuFastSet( const void *source, void *dest, u32 mode)
	\param source
	\param dest
	\param mode
*/
void CpuFastSet( const void *source, void *dest, u32 mode);

/*! \fn void IntrWait(u32 ReturnFlag, u32 IntFlag)
    \brief waits for an interrupt to occur.
	\param ReturnFlag
	\param IntFlag
*/
void IntrWait(u32 ReturnFlag, u32 IntFlag);

/*! \fn void VBlankIntrWait()
    \brief waits for a vertical blank interrupt to occur.

*/
static inline
void VBlankIntrWait()	{ SystemCall(5); }

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif


//---------------------------------------------------------------------------------
#endif //_gba_systemcalls_h_
