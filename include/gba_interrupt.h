/*
	"$Id: gba_interrupt.h,v 1.5 2005-09-27 00:37:17 wntrmute Exp $"

	Header file for libgba interrupt handling

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

	"$Header: /lvm/shared/ds/ds/cvs/devkitpro-cvsbackup/libgba/include/gba_interrupt.h,v 1.5 2005-09-27 00:37:17 wntrmute Exp $"

*/

/*! \file gba_interrupt.h
    \brief gba interrupt support.

*/

#ifndef _gba_interrupt_h_
#define _gba_interrupt_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

/*! \var typedef void ( * IntFn)(void)
    \brief A type definition for an interrupt function pointer
*/
typedef void ( * IntFn)(void);

struct IntTable{IntFn handler; u32 mask;};

typedef enum {
	Int_Vblank, 	/*!< Vblank interrupt index. */
	Int_Hblank,		/*!< Hblank interrupt index. */
	Int_Vcount,		/*!< Vcount interrupt index. */
	Int_Timer0,		/*!< Timer 0 interrupt index. */
	Int_Timer1,		/*!< Timer 1 interrupt index. */
	Int_Timer2,		/*!< Timer 2 interrupt index. */
	Int_Timer3,		/*!< Timer 3 interrupt index. */
	Int_Serial,		/*!< Serial interrupt index. */
	Int_DMA0,		/*!< DMA 0 interrupt index. */
	Int_DMA1,		/*!< DMA 1 interrupt index. */
	Int_DMA2,		/*!< DMA 2 interrupt index. */
	Int_DMA3,		/*!< DMA 3 interrupt index. */
	Int_KeyPad,		/*!< Keypad interrupt index. */
	Int_GamePak,	/*!< Cartridge interrupt index. */
	Int_Count,		/*!< Maximum number of interrupt handlers. */
	Ints_All = 0x7fff	/*!< All interrupts. */
} eINT;

#define INT_VECTOR	*(IntFn *)(0x03007ffc)		// BIOS Interrupt vector
/*! \def REG_IME

    \brief Interrupt Master Enable Register.

	When bit 0 is clear, all interrupts are masked.  When it is 1,
	interrupts will occur if not masked out in REG_IE.

*/
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
/*! \def REG_IE

    \brief Interrupt Enable Register.

	This is the activation mask for the internal interrupts.  Unless
	the corresponding bit is set, the IRQ will be masked out.
*/
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
/*! \def REG_IF

    \brief Interrupt Flag Register.

	Since there is only one hardware interrupt vector, the IF register
	contains flags to indicate when a particular of interrupt has occured.
	To acknowledge processing interrupts, set IF to the value of the
	interrupt handled.

*/
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request

//!  interrupt masks.
/*!
  These masks are used in conjuction with REG_IE to enable specific interrupts
  and with REG_IF to acknowledge interrupts have been serviced.
*/
enum irqMASKS {
	IE_VBL		=	(1<<0),		/*!< vertical blank interrupt mask */
	IE_HBL		=	(1<<1),		/*!< horizontal blank interrupt mask */
	IE_VCNT		=	(1<<2),		/*!< vcount match interrupt mask */
	IE_TIMER0	=	(1<<3),		/*!< timer 0 interrupt mask */
	IE_TIMER1	=	(1<<4),		/*!< timer 1 interrupt mask */
	IE_TIMER2	=	(1<<5),		/*!< timer 2 interrupt mask */
	IE_TIMER3	=	(1<<6),		/*!< timer 3 interrupt mask */
	IE_SERIAL	=	(1<<7),		/*!< serial interrupt mask */
	IE_DMA0		=	(1<<8),		/*!< DMA 0 interrupt mask */
	IE_DMA1		=	(1<<9),		/*!< DMA 1 interrupt mask */
	IE_DMA2		=	(1<<10),	/*!< DMA 2 interrupt mask */
	IE_DMA3		=	(1<<11),	/*!< DMA 3 interrupt mask */
	IE_KEYPAD	=	(1<<12),	/*!< Keypad interrupt mask */
	IE_GAMEPAK	=	(1<<13)		/*!< horizontal blank interrupt mask */
};

extern struct IntTable IntrTable[];

/*! \fn void InitInterrupt(void)
    \brief initialises the gba interrupt code.

*/
void InitInterrupt(void);

/*! \fn void SetInterrupt(eINT interrupt, IntFn function)
    \brief sets the interrupt handler for a particular interrupt.

	\param interrupt
	\param function
*/
void SetInterrupt(eINT interrupt, IntFn function);

/*! \fn void EnableInterrupt(eINT interrupt)
    \brief allows an interrupt to occur.

	\param interrupt
*/
void EnableInterrupt(eINT interrupt);

/*! \fn void DisableInterrupt(eINT interrupt)
    \brief prevents an interrupt occuring.

	\param interrupt
*/
void DisableInterrupt(eINT interrupt);

void IntrMain();



//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_interrupt_h_
