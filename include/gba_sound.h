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


#define SoundDriverMain()		SystemCall(28)
#define SoundDriverVsync()		SystemCall(29)
#define SoundChannelClear()		SystemCall(30)
#define SoundDriverVsyncOff()	SystemCall(40)
#define SoundDriverVsyncOn()	SystemCall(41)

void SoundDriverInit(SoundArea *sa);
void SoundDriverMode(u32 mode);

u32  MidiKey2Freq(WaveData *wa, u8 mk, u8 fp);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif //_gba_sound_h_
