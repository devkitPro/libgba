/*
	$Id: gba_sound.h,v 1.8 2005-11-29 17:02:38 wntrmute Exp $

	Header file for libgba bios sound functions

	Copyright (C) 2003-2005 by Dave Murphy.

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

	$Log: not supported by cvs2svn $

*/
//---------------------------------------------------------------------------------
#ifndef	_gba_sound_h_
#define	_gba_sound_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

typedef struct {
	u16 type;
	u16 stat;
	u32 freq;
	u32 loop;
	u32 size;
	s8 data[1];
} WaveData;

typedef struct {
	u8 Status;
	u8 reserved1;
	u8 RightVol;
	u8 LeftVol;
	u8 Attack;
	u8 Decay;
	u8 Sustain;
	u8 Release;
	u8 reserved2[24];
	u32 fr;
	WaveData *wp;
	u32 reserved3[6];
} SoundChannel;

#define PCM_DMA_BUF 1584
#define MAX_DIRECTSOUND_CHANNELS 12

typedef struct {
	u32 ident;
	vu8 DmaCount;
	u8 reverb;
	u8 maxchn;
	u8 masvol;
	u8 freq;
	u8 mode;
	u8 r2[6];
	u32 r3[16];
	SoundChannel vchn[MAX_DIRECTSOUND_CHANNELS];
	s8 pcmbuf[PCM_DMA_BUF*2];
} SoundArea;

/*---------------------------------------------------------------------------------
	Control Registers
---------------------------------------------------------------------------------*/
#define	REG_SOUNDCNT_L	(*((u16 volatile *) REG_BASE + 0x080))

#define SND1_R_ENABLE	(1<<8)		// Enable left & right speakers for each sound channel
#define SND1_L_ENABLE	(1<<12)
#define SND2_R_ENABLE	(1<<9)
#define SND2_L_ENABLE	(1<<13)
#define SND3_R_ENABLE	(1<<10)
#define SND3_L_ENABLE	(1<<14)
#define SND4_R_ENABLE	(1<<11)
#define SND4_L_ENABLE	(1<<15)

#define SNDA_VOL_50     (0<<2)
#define SNDA_VOL_100    (1<<2)
#define SNDB_VOL_50     (0<<3)
#define SNDB_VOL_100    (1<<3)
#define SNDA_R_ENABLE   (1<<8)
#define SNDA_L_ENABLE   (1<<9)
#define SNDA_RESET_FIFO (1<<11)
#define SNDB_R_ENABLE   (1<<12)
#define SNDB_L_ENABLE   (1<<13)
#define SNDB_RESET_FIFO (1<<15)


#define	REG_SOUNDCNT_H	(*((u16 volatile *) (REG_BASE + 0x082)))
#define	REG_SOUNDCNT_X	(*((u16 volatile *) (REG_BASE + 0x084)))


#define	REG_SOUND1CNT_L	(*((u16 volatile *) (REG_BASE + 0x060)))
#define	REG_SOUND1CNT_H	(*((u16 volatile *) (REG_BASE + 0x062)))
#define	REG_SOUND1CNT_X	(*((u16 volatile *) (REG_BASE + 0x064)))

#define	REG_SOUND2CNT_L	(*((u16 volatile *) (REG_BASE + 0x068)))
#define	REG_SOUND2CNT_H	(*((u16 volatile *) (REG_BASE + 0x06C)))

#define	REG_SOUND3CNT_L	(*((u16 volatile *) (REG_BASE + 0x070)))
#define	REG_SOUND3CNT_H	(*((u16 volatile *) (REG_BASE + 0x072)))
#define	REG_SOUND3CNT_X	(*((u16 volatile *) (REG_BASE + 0x074)))

#define	REG_SOUND4CNT_L	(*((u16 volatile *) (REG_BASE + 0x078)))
#define	REG_SOUND4CNT_H	(*((u16 volatile *) (REG_BASE + 0x07C)))

#define	REG_SOUNDBIAS	(*((u16 volatile *) (REG_BASE + 0x088)))

#define	REG_FIFO_A		(*((u32 volatile *) (REG_BASE + 0x0A0)))
#define	REG_FIFO_B		(*((u32 volatile *) (REG_BASE + 0x0A4)))

#define	WAVE_RAM	((u16 volatile *)	(REG_BASE + 0x090))

#define	SOUND3_STEP32		(0<<5)	// Use two banks of 32 steps each
#define SOUND3_STEP64		(1<<5)	// Use one bank of 64 steps
#define SOUND3_SETBANK(n)	(n<<6)	// Bank to play 0 or 1 (non set bank is written to)
#define SOUND3_PLAY			(1<<7)	// Output sound
#define SOUND3_STOP			(0<<7)	// Stop sound output


static inline void SoundDriverMain()		{ SystemCall(28); }
static inline void SoundDriverVsync()	{ SystemCall(29); }
static inline void SoundChannelClear()	{ SystemCall(30); }
static inline void SoundDriverVsyncOff()	{ SystemCall(40); }
static inline void SoundDriverVsyncOn()	{ SystemCall(41); }

void SoundDriverInit(SoundArea *sa);
void SoundDriverMode(u32 mode);

u32  MidiKey2Freq(WaveData *wa, u8 mk, u8 fp);


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif //_gba_sound_h_
