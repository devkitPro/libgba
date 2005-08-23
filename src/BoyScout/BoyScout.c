//////////////////////////////////////////////////////////////
// File: BoyScout.c                                         //
//                                                          //
// Description: Implementations of BoyScout music playback. //
//                                                          //
// Author:     Christer Andersson (c) 2001                  //
// Additions:  Willem Kokke                                 //
//             WinterMute                                   //
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// New section of functions were written by Willem Kokke.   //
// He also fixed a silly miss in the wave RAM copy of the   //
// v.0.93 playback libraries. Thanks alot mate :O)          //
//                                                          //
// / Christer                                               //
//////////////////////////////////////////////////////////////

// INCLUDES ///////

#include "BoyScout.h"
#include "GBASoundRegs.h"

// GLOBALS ////////

unsigned char g_cSound1Patterns;		// Pattern counts
unsigned char g_cSound2Patterns;
unsigned char g_cSound3Patterns;
unsigned char g_cSound4Patterns;

unsigned short g_nSongLength;			// Song length

unsigned char g_nSequencerBeatsPerRow;	// Beats per sequencer row

unsigned char g_nBeatLength;			// Length of a beat


// WK
unsigned char g_nPlaySpeed;             // The playback speed

int g_nMuteChannel1;                    // Lets add some Mute options
int g_nMuteChannel2;
int g_nMuteChannel3;
int g_nMuteChannel4;


unsigned char g_cSound3WaveForms;		// Wave form count
unsigned int *g_pSound3WaveForms;		// Wave forms
short g_nSound3PlayWaveForm;			// Wave form in playing buffer
unsigned char g_iSound3PlayBank;		// Which buffer playing waveform resides

unsigned char *g_apSequencerParams[SOUND_CHANNEL_COUNT];	// Sequencer parameters
SRLEIterator g_aRLESequencer[SOUND_CHANNEL_COUNT];			// Sequencer iterators

SSound1Pattern *g_pSound1Patterns;					// Sound channel patterns
SSound2Pattern *g_pSound2Patterns;
SSound3Pattern *g_pSound3Patterns;
SSound4Pattern *g_pSound4Patterns;

SRLEIterator g_aRLESound1[SOUND1_PARAMETER_COUNT];	// Sound channel iterators
SRLEIterator g_aRLESound2[SOUND2_PARAMETER_COUNT];
SRLEIterator g_aRLESound3[SOUND3_PARAMETER_COUNT];
SRLEIterator g_aRLESound4[SOUND4_PARAMETER_COUNT];

unsigned char g_nPlayState;							// Current play state
int g_iTickCounter;									// Tick counterint g_iPlayPosition;								// Current play position
int g_iBeatsPerRowCounter;							// Counter for sequencer update
int g_iPlayPosition;								// Current play position
short g_aiPlayPatterns[SOUND_CHANNEL_COUNT];		// Current play patterns
int g_aiPlayPatternPositions[SOUND_CHANNEL_COUNT];	// Current play positions in patterns

short g_anSound1Params[SOUND1_PARAMETER_COUNT];		// Current channel parameters
short g_anSound2Params[SOUND2_PARAMETER_COUNT];
short g_anSound3Params[SOUND3_PARAMETER_COUNT];
short g_anSound4Params[SOUND4_PARAMETER_COUNT];

unsigned int g_nBoyScoutMemoryArea;	// Address to a free memory area which BS needs

const unsigned short canNoteFrequencies[72] = {
44,		// C3
156,
262,
363,
457,
547,
631,
710,
786,
854,
923,
986,
1046,	// C4
1102,
1155,
1205,
1253,
1297,
1339,
1379,
1417,
1452,
1486,
1517,
1546,	// C5
1575,
1602,
1627,
1650,
1673,
1694,
1714,
1732,
1750,
1767,
1783,
1798,	// C6
1812,
1825,
1837,
1849,
1860,
1871,
1881,
1890,
1899,
1907,
1915,
1923,	// C7
1930,
1936,
1943,
1949,
1954,
1959,
1964,
1969,
1974,
1978,
1982,
1985,	// C8
1988,
1992,
1995,
1998,
2001,
2004,
2006,
2009,
2011,
2015
};

// FUNCTIONS //////

/////////////////////////////////////////////////////////////////
// Function: RLEISet                                           //
//                                                             //
// Description: Sets a RLE iterator to compressed data.        //
//                                                             //
// Parameters: Pointer to compressed data and RLE iterator.    //
//                                                             //
void RLEISet(unsigned char *pData, SRLEIterator *pRLEIterator) //
{
	// Set data pointer
	pRLEIterator->pData = pData;

	// Reset iterator
	pRLEIterator->iValue = 0;
	pRLEIterator->iValuePos = 0;

	// Get mask
	pRLEIterator->mask = *pRLEIterator->pData;
	pRLEIterator->pData++;

	// If there's a run length value
	if(pRLEIterator->mask & 1)
	{
		pRLEIterator->cValue = *pRLEIterator->pData;
		pRLEIterator->pData++;
	}
	// If there is no run length value
	else
	{
		pRLEIterator->cValue = 1;
	}

	// Get value
	pRLEIterator->nValue = pRLEIterator->pData[0] | (pRLEIterator->pData[1]<<8);
	pRLEIterator->pData += 2;
}
// End of RLEISet

//////////////////////////////////////////////////////
// Function: RLEINext                               //
//                                                  //
// Description: Gets next value of compressed data. //
//                                                  //
// Parameters: Pointer to RLE iterator.             //
//                                                  //
void RLEINext(SRLEIterator *pRLEIterator) ////////////
{
	// Increment run length position
	pRLEIterator->iValuePos++;

	// If run length end is reached
	if(pRLEIterator->iValuePos >= pRLEIterator->cValue)
	{
		// Reset run length position
		pRLEIterator->iValuePos = 0;

		// Increment value position
		pRLEIterator->iValue++;

		// If a new mask has to be read
		if(pRLEIterator->iValue == 8)
		{
			// Reset
			pRLEIterator->iValue = 0;

			// Read mask
			pRLEIterator->mask = *pRLEIterator->pData;
			pRLEIterator->pData++;
		}

		// If to get run length
		if(pRLEIterator->mask & (1<<pRLEIterator->iValue))
		{
			pRLEIterator->cValue = *pRLEIterator->pData;
			pRLEIterator->pData++;
		}
		else
		{
			pRLEIterator->cValue = 1;
		}

		// Get value
		pRLEIterator->nValue = pRLEIterator->pData[0] | (pRLEIterator->pData[1]<<8);
		pRLEIterator->pData += 2;
	}
}
// End of RLEINext

//////////////////////////////////////////////////////////////////////////////
// Function: DMA3Copy32                                                     //
//                                                                          //
// Description: Copies data 4-bytes of data per count.                      //
//                                                                          //
// Parameters: Source address, destination addresses and 32-bit data count. //
//                                                                          //
void DMA3Copy32(unsigned int Src, unsigned int Dst, unsigned short Count) ////
{
	DMA3DST		= Dst;
	DMA3SRC		= Src;
	DMA3COUNT	= Count;

	DMA3CNT = DMACNTDSTINC | DMACNTSRCINC | DMACNTTRANSFER32 | DMACNTSTARTIM | DMACNTENABLE;
}
// End of DMA3Copy32

///////////////////////////////////////////////////////
// Function: BoyScoutInitialize                      //
//                                                   //
// Description: Initializes all internal parameters. //
//                                                   //
void BoyScoutInitialize() /////////////////////////////
{
    // Loop variable
    int i;

    g_cSound1Patterns = 0;
    g_cSound2Patterns = 0;
    g_cSound3Patterns = 0;
    g_cSound4Patterns = 0;

    g_nSongLength = 0;
    g_nSequencerBeatsPerRow = 0;
    g_nBeatLength = 0;

    // WK Some inits
    g_nPlaySpeed = 0;
    g_nMuteChannel1 = 0;
    g_nMuteChannel2 = 0;
    g_nMuteChannel3 = 0;
    g_nMuteChannel4 = 0;

    g_cSound3WaveForms = 0;
    g_pSound3WaveForms = 0;

    g_pSound1Patterns = 0;
    g_pSound2Patterns = 0;
    g_pSound3Patterns = 0;
    g_pSound4Patterns = 0;

    g_nPlayState = PLAYSTATE_STOP;
	g_iTickCounter = 0;
    g_iPlayPosition = 0;
    g_iBeatsPerRowCounter = 0;

	// Default memory to beginning of external RAM
	g_nBoyScoutMemoryArea = 0x02000000;

	for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
	{
		g_apSequencerParams[i] = 0;
		g_aiPlayPatterns[i] = 0;
		g_aiPlayPatternPositions[i] = 0;
	}

	// Set the all sound sound operate flag with sound channels
	SGCNT1 = SGCNT1ALLSNDOPERATE | SGCNT1SND1OPERATE | SGCNT1SND2OPERATE | SGCNT1SND3OPERATE | SGCNT1SND4OPERATE;

	// Set GBA sound control registers - full volume, enable all sounds left/right
	SGCNT0L = SGCNT0LROUT(7) | SGCNT0LLOUT(7) | SGCNT0LSND1RENABLED | SGCNT0LSND1LENABLED |
		      SGCNT0LSND2RENABLED | SGCNT0LSND2LENABLED | SGCNT0LSND3RENABLED | 
			  SGCNT0LSND3LENABLED | SGCNT0LSND4RENABLED | SGCNT0LSND4LENABLED;

	// Overall output ratio - Full
	SGCNT0H = SGCNT0HSNDOUTPUT1;
}
// End of BoyScoutInitialize

/////////////////////////////////////////////////////////////////
// Function: BoyScoutOpenSong                                  //
//                                                             //
// Description: Setup the neccessary structures and parameters //
//				to allow music playback of song                //
//                                                             //
// Parameters: Pointer to exported song data.                  //
//                                                             //
void BoyScoutOpenSong(const unsigned char *pSongData) ///////////
{
	// Loop variable
	int i,j;

	// Address to memory for pattern storage
	unsigned int dwMemAddress;

	// Storage of compressed data size
	unsigned short wCompressedSize;

	// First 4 bytes is song size parameter - go past this
	pSongData += 4;

	// Get sound pattern counts - 1 byte each
	g_cSound1Patterns = *pSongData;
	pSongData++;
	g_cSound2Patterns = *pSongData;
	pSongData++;
	g_cSound3Patterns = *pSongData;
	pSongData++;
	g_cSound4Patterns = *pSongData;
	pSongData++;

	// Get song length - 2 bytes
	g_nSongLength = pSongData[0] | (pSongData[1]<<8);
	pSongData += 2;

	// Get sequencer beats per row - 1 byte
	g_nSequencerBeatsPerRow = *pSongData;
	pSongData++;

	// Get beat length - 1 byte
	g_nBeatLength = *pSongData;
    g_nPlaySpeed = g_nBeatLength;
	pSongData++;

	// Set to beginning of BoyScout memory area
	dwMemAddress = g_nBoyScoutMemoryArea;

	// "Allocate" sound 1 patterns
	g_pSound1Patterns = (SSound1Pattern*)dwMemAddress;
	dwMemAddress += sizeof(SSound1Pattern)*g_cSound1Patterns;

	// "Allocate" sound 2 patterns
	g_pSound2Patterns = (SSound2Pattern*)dwMemAddress;
	dwMemAddress += sizeof(SSound2Pattern)*g_cSound2Patterns;

	// "Allocate" sound 3 patterns
	g_pSound3Patterns = (SSound3Pattern*)dwMemAddress;
	dwMemAddress += sizeof(SSound3Pattern)*g_cSound3Patterns;

	// "Allocate" sound 4 patterns
	g_pSound4Patterns = (SSound4Pattern*)dwMemAddress;
	dwMemAddress += sizeof(SSound4Pattern)*g_cSound4Patterns;

	// Get sound 1 pattern data
	for(i = 0; i < g_cSound1Patterns; i++)
	{
		// Get pattern length - 2 bytes
		g_pSound1Patterns[i].nLength = pSongData[0] | (pSongData[1]<<8);
		pSongData += 2;

		// Get pattern parameter pointers
		for(j = 0; j < SOUND1_PARAMETER_COUNT; j++)
		{
			// Get compressed data size - 2 bytes
			wCompressedSize = pSongData[0] | (pSongData[1]<<8);
			pSongData += 2;

			// Set pointer to parameter compressed data
			g_pSound1Patterns[i].apParams[j] = (unsigned char *)pSongData;

			// Move past compressed data
			pSongData += wCompressedSize;
		}
	}

	// Get sound 2 pattern data
	for(i = 0; i < g_cSound2Patterns; i++)
	{
		// Get pattern length - 2 bytes
		g_pSound2Patterns[i].nLength = pSongData[0] | (pSongData[1]<<8);
		pSongData += 2;

		// Get pattern parameter pointers - 2 bytes
		for(j = 0; j < SOUND2_PARAMETER_COUNT; j++)
		{
			// Get compressed data size
			wCompressedSize = pSongData[0] | (pSongData[1]<<8);;
			pSongData += 2;

			// Set pointer to parameter compressed data
			g_pSound2Patterns[i].apParams[j] = (unsigned char *)pSongData;

			// Move past compressed data
			pSongData += wCompressedSize;
		}
	}

	// Get sound 3 pattern data
	for(i = 0; i < g_cSound3Patterns; i++)
	{
		// Get pattern length - 2 bytes
		g_pSound3Patterns[i].nLength = pSongData[0] | (pSongData[1]<<8);
		pSongData += 2;

		// Get pattern parameter pointers
		for(j = 0; j < SOUND3_PARAMETER_COUNT; j++)
		{
			// Get compressed data size - 2 bytes
			wCompressedSize = pSongData[0] | (pSongData[1]<<8);
			pSongData += 2;

			// Set pointer to parameter compressed data
			g_pSound3Patterns[i].apParams[j] = (unsigned char *)pSongData;

			// Move past compressed data
			pSongData += wCompressedSize;
		}
	}

	// Get sound 4 pattern data
	for(i = 0; i < g_cSound4Patterns; i++)
	{
		// Get pattern length - 2 bytes
		g_pSound4Patterns[i].nLength = pSongData[0] | (pSongData[1]<<8);
		pSongData += 2;

		// Get pattern parameter pointers
		for(j = 0; j < SOUND4_PARAMETER_COUNT; j++)
		{
			// Get compressed data size - 2 bytes
			wCompressedSize = pSongData[0] | (pSongData[1]<<8);
			pSongData += 2;

			// Set pointer to parameter compressed data
			g_pSound4Patterns[i].apParams[j] = (unsigned char *)pSongData;

			// Move past compressed data
			pSongData += wCompressedSize;
		}
	}

	// Get wave form count - 1 byte
	g_cSound3WaveForms = *pSongData;
	pSongData++;

	// If there are wave forms
	if(g_cSound3WaveForms > 0)
	{
		
		// WM - adjust pointer to waveform for alignment
 
		// Set pointers to wave form data
		pSongData = (unsigned char*)(((unsigned int)pSongData +3) & -4);
		g_pSound3WaveForms = (unsigned int *)pSongData;

		// copy bytes
		//int i;
		//unsigned char *src = (unsigned char *)pSongData, *dst = (unsigned char *)g_pSound3WaveForms;
		//for (i = 0; i < (g_cSound3WaveForms * 16); i++) {

		//	*(dst++) = *(src++);
		//}
		// Move past wave form data - 16 bytes per wave form data
		pSongData += g_cSound3WaveForms*16;
	}

	// Get sequencer parameter data
	for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
	{
		// Get compressed data size - 2 bytes
		wCompressedSize = pSongData[0] | (pSongData[1]<<8);
		pSongData += 2;

		// Set pointer to parameter compressed data
		g_apSequencerParams[i] = (unsigned char *)pSongData;

		// Move past compressed data
		pSongData += wCompressedSize;
	}
}
// End of BoyScoutOpenSong

//////////////////////////////////////////////////////////////
// Function: BoyScoutPlaySong                               //
//                                                          //
// Description: Starts playback of the currently open song. //
//                                                          //
// Parameters: Flag if song should loop.                    //
//                                                          //
void BoyScoutPlaySong(int nLoop) /////////////////////////////
{
	// Loop variable
	int i;

	// If playing - return
	if(g_nPlayState & PLAYSTATE_PLAY)
		return;

	// Set play state
	g_nPlayState = PLAYSTATE_PLAY;

	// If to loop
	if(nLoop)
		g_nPlayState |= PLAYSTATE_LOOP;

	// Reset play positions
	g_iPlayPosition = 0;
	g_iTickCounter = g_nBeatLength; // Make it start playback immediately next V-Blank
	g_iBeatsPerRowCounter = 0;

	for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
	{
		g_aiPlayPatternPositions[i] = 0;

		// Set sequencer iterators
		RLEISet(g_apSequencerParams[i], &g_aRLESequencer[i]);
	}

	// Get pattern indices from sequencer
	for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
		g_aiPlayPatterns[i] = g_aRLESequencer[i].nValue;

	// If a sound 1 pattern is set in sequencer
	if(g_aiPlayPatterns[0] != PATTERN_PARAMETER_EMPTY)
	{
		for(i = 0; i < SOUND1_PARAMETER_COUNT; i++)
		{
			RLEISet(g_pSound1Patterns[g_aiPlayPatterns[0]].apParams[i], &g_aRLESound1[i]);
		}
	}

	// If a sound 2 pattern is set in sequencer
	if(g_aiPlayPatterns[1] != PATTERN_PARAMETER_EMPTY)
	{
		for(i = 0; i < SOUND2_PARAMETER_COUNT; i++)
		{
			RLEISet(g_pSound2Patterns[g_aiPlayPatterns[1]].apParams[i], &g_aRLESound2[i]);
		}
	}

	// If a sound 3 pattern is set in sequencer
	if(g_aiPlayPatterns[2] != PATTERN_PARAMETER_EMPTY)
	{
		for(i = 0; i < SOUND3_PARAMETER_COUNT; i++)
		{
			RLEISet(g_pSound3Patterns[g_aiPlayPatterns[2]].apParams[i], &g_aRLESound3[i]);
		}
	}

	// If a sound 4 pattern is set in sequencer
	if(g_aiPlayPatterns[3] != PATTERN_PARAMETER_EMPTY)
	{
		for(i = 0; i < SOUND4_PARAMETER_COUNT; i++)
		{
			RLEISet(g_pSound4Patterns[g_aiPlayPatterns[3]].apParams[i], &g_aRLESound4[i]);
		}
	}

	// Reset sound channels' parameters
	for(i = 0; i < SOUND1_PARAMETER_COUNT; i++)
		g_anSound1Params[i] = 0;
	for(i = 0; i < SOUND2_PARAMETER_COUNT; i++)
		g_anSound2Params[i] = 0;
	for(i = 0; i < SOUND3_PARAMETER_COUNT; i++)
		g_anSound3Params[i] = 0;
	for(i = 0; i < SOUND4_PARAMETER_COUNT; i++)
		g_anSound4Params[i] = 0;

	// Default envelopes
	g_anSound1Params[0] = 15;
	g_anSound2Params[0] = 15;
	g_anSound3Params[0] = 4;
	g_anSound4Params[0] = 15;

	// Init wave buffers
	g_iSound3PlayBank = 1;
	g_nSound3PlayWaveForm = PATTERN_PARAMETER_EMPTY;

	// If a new waveform is set
	if(g_aRLESound3[2].nValue != PATTERN_PARAMETER_EMPTY)
	{
		// If a valid wave form
		if(g_aRLESound3[2].nValue < g_cSound3WaveForms)
		{
			
            // Set wave form
			g_nSound3PlayWaveForm = g_aRLESound3[2].nValue;

			// Copy waveform to bank 0
			SG30L = SG30LSTEP32	| SG30LSETBANK1;

            // WK add conditional define, and fix software copy

            #if(USE_DMA)

            DMA3Copy32((unsigned int)&g_pSound3WaveForms[4*g_nSound3PlayWaveForm], (unsigned int)&SGWRAM, 4);

            #else

			unsigned int *pDst, *pSrc;
			pSrc = (unsigned int*)&g_pSound3WaveForms[4*g_nSound3PlayWaveForm];
			pDst = (unsigned int*)&SGWRAM;
			pDst[0] = pSrc[0];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[2];
			pDst[3] = pSrc[3];

            #endif

				// Set to correct bank
//			if(g_iSound3PlayBank == 1)
			SG30L = SG30LSTEP32 | SG30LSETBANK0;
//				else
//					SG30L = SG30LSTEP32 | SG30LSETBANK1;


		}
	}
}
// End of BoyScoutPlaySong

///////////////////////////////////////////////////////////////
// Function: BoyScoutStopSong                                //
//                                                           //
// Description: Stops playback of the currently played song. //
//                                                           //
void BoyScoutStopSong() ///////////////////////////////////////
{
	// Set stop
	g_nPlayState = PLAYSTATE_STOP;
}
// End of BoyScoutStopSong


/////////////////////////////////////////////////////////////////////////////////
// Function: BoyScoutUpdateSong                                                //
//                                                                             //
// Description: Updates the song playback states, should be called first thing //
//				at the beginning of the vertical blank interval to ensure      //
//				proper syncronization. Not calling UpdateSong will cause the   //
//              playback to be paused.                                         //
//                                                                             //
// Returns: If not set to looping, returns 0 when finished playback of song.   //
//                                                                             //
int BoyScoutUpdateSong() ////////////////////////////////////////////////////////
{
	// Loop variable
	int i;

	// If not playing
	if(g_nPlayState & PLAYSTATE_STOP)
		return(0);

	// Update tick counter
	g_iTickCounter++;

    // WK add time influencing

	// If song shouldn't be updated yet
	if(g_iTickCounter < g_nPlaySpeed)
	{
		return(1);
	}
	// If song should be updated
	else
	{
		// Reset tick counter
		g_iTickCounter = 0;
	}

	// PLAY SONG FROM CURRENT STEP ////

	// If a sound 1 pattern is playing
	if( g_aiPlayPatterns[0] != PATTERN_PARAMETER_EMPTY )
	{
		// If a note is struck
		if(g_aRLESound1[SOUND1_PARAMETER_COUNT-1].nValue != PATTERN_PARAMETER_EMPTY )
		{
			if(g_nMuteChannel1 == 0)
			{
				// Set sound channel 1 to ON
//				SGCNT1 |= SGCNT1SND1OPERATE;
				SG11 |= SG11INIT;

				// Get parameters
				for(i = 0; i < SOUND1_PARAMETER_COUNT; i++)
				{
					if(g_aRLESound1[i].nValue != PATTERN_PARAMETER_EMPTY)
						g_anSound1Params[i] = g_aRLESound1[i].nValue;
				}

				// If envelope steps is negative
				if(g_anSound1Params[1] <= 0)
				{
					SG10H = SG10HSNDLENGTH(g_anSound1Params[2]) | SG10HWAVEDUTYCYCLE(g_anSound1Params[3]) | SG10HENVELOPESTEPS(-g_anSound1Params[1]) | 
							SG10HENVELOPEDEC | SG10HENVELOPEINIT(g_anSound1Params[0]);
				}
				else
				{
					SG10H = SG10HSNDLENGTH(g_anSound1Params[2]) | SG10HWAVEDUTYCYCLE(g_anSound1Params[3]) | SG10HENVELOPESTEPS(g_anSound1Params[1]) | 
							SG10HENVELOPEINC | SG10HENVELOPEINIT(g_anSound1Params[0]);
				}
		
				// If sweep shifts is negative
				if(g_anSound1Params[4] <= 0)
				{
					SG10L = SG10LSWEEPSHIFTS(-g_anSound1Params[4]) | SG10LSWEEPSHIFTDEC | SG10LSWEEPTIME(g_anSound1Params[5]);
				}
				else
				{
					SG10L = SG10LSWEEPSHIFTS(g_anSound1Params[4]) | SG10LSWEEPSHIFTINC | SG10LSWEEPTIME(g_anSound1Params[5]);
				}

				SG11  = SG11FREQUENCY(canNoteFrequencies[g_anSound1Params[6]-36]) | SG11PLAYONCE;	
				SG11 |= SG11INIT;
			}
			else
			{
			}
		}

		// Increment pattern position
		g_aiPlayPatternPositions[0]++;

		// If past end
		if(g_aiPlayPatternPositions[0] >= g_pSound1Patterns[g_aiPlayPatterns[0]].nLength)
		{
			// Set to no pattern
			g_aiPlayPatterns[0] = PATTERN_PARAMETER_EMPTY;
		}
		// If still in pattern
		else
		{
			// Increment pattern parameter iterators
			for(i = 0; i < SOUND1_PARAMETER_COUNT; i++)
			{
				RLEINext(&g_aRLESound1[i]);
			}
		}
	}

	// If a sound 2 pattern is playing
	if( g_aiPlayPatterns[1] != PATTERN_PARAMETER_EMPTY )
	{
		// If a note is struck
		if(g_aRLESound2[SOUND2_PARAMETER_COUNT-1].nValue != PATTERN_PARAMETER_EMPTY)
		{
			if(g_nMuteChannel2 == 0)
			{
				// Set sound channel 2 to ON
//				SGCNT1 |= SGCNT1SND2OPERATE;

				// Get parameters
				for(i = 0; i < SOUND2_PARAMETER_COUNT; i++)
				{
					if(g_aRLESound2[i].nValue != PATTERN_PARAMETER_EMPTY)
						g_anSound2Params[i] = g_aRLESound2[i].nValue;
				}
			
				// If envelope steps is negative
				if(g_anSound2Params[1] <= 0)
				{
					SG20 = SG20SNDLENGTH(g_anSound2Params[2]) | SG20WAVEDUTYCYCLE(g_anSound2Params[3]) | SG20ENVELOPESTEPS(-g_anSound2Params[1]) | 
							SG20ENVELOPEDEC | SG20ENVELOPEINIT(g_anSound2Params[0]);
				}
				else
				{
					SG20 = SG20SNDLENGTH(g_anSound2Params[2]) | SG20WAVEDUTYCYCLE(g_anSound2Params[3]) | SG20ENVELOPESTEPS(g_anSound2Params[1]) | 
							SG20ENVELOPEINC | SG20ENVELOPEINIT(g_anSound2Params[0]);
				}
		
				SG21  = SG21FREQUENCY(canNoteFrequencies[g_anSound2Params[4]-36]) | SG21PLAYONCE | SG21INIT;

				if(canNoteFrequencies[g_anSound2Params[4]-36] == 1985)
					*(unsigned int*)0x04000000 = 1;
			}
			else
			{
			}
		}

		// Increment pattern position
		g_aiPlayPatternPositions[1]++;

		// If past end
		if(g_aiPlayPatternPositions[1] >= g_pSound2Patterns[g_aiPlayPatterns[1]].nLength)
		{
			// Set to no pattern
			g_aiPlayPatterns[1] = PATTERN_PARAMETER_EMPTY;
		}
		// If still in pattern
		else
		{
			// Increment pattern parameter iterators
			for(i = 0; i < SOUND2_PARAMETER_COUNT; i++)
			{
				RLEINext(&g_aRLESound2[i]);
			}
		}
	}

	// If a sound 3 pattern is playing
	if( g_aiPlayPatterns[2] != PATTERN_PARAMETER_EMPTY )
	{
		// If a note is struck
		if(g_aRLESound3[SOUND3_PARAMETER_COUNT-1].nValue != PATTERN_PARAMETER_EMPTY)
		{
			if(g_nMuteChannel3 == 0)
			{
//				// Set sound channel 3 to ON
//				SGCNT1 |= SGCNT1SND3OPERATE;

				// Get parameters
				for(i = 0; i < SOUND3_PARAMETER_COUNT; i++)
				{
					if(g_aRLESound3[i].nValue != PATTERN_PARAMETER_EMPTY)
						g_anSound3Params[i] = g_aRLESound3[i].nValue;
				}

				// Set to correct bank
				if(g_iSound3PlayBank == 1)
					SG30L = SG30LSTEP32 | SG30LSETBANK0;
				else
					SG30L = SG30LSTEP32 | SG30LSETBANK1;
		
		// WM reordered to work on hardware
				SG30L	|=	SG30LPLAY;

				SG30H = SG30HSNDLENGTH(g_anSound3Params[1]);
			

				// Envelope
				switch(g_anSound3Params[0])
				{
				case 0:
					{
						SG30H |= SG30HOUTPUTMUTE;
					}break;
				case 1:
					{
						SG30H |= SG30HOUTPUT14;
					}break;
				case 2:
					{
						SG30H |= SG30HOUTPUT12;
					}break;
				case 3:
					{
						SG30H |= SG30HOUTPUT34;
					}break;
				case 4:
					{
						SG30H |= SG30HOUTPUT1;
					}break;
				default:break;
				}

		
				SG31  = SG31FREQUENCY(canNoteFrequencies[g_anSound3Params[3]-36]) | SG31PLAYONCE | SG31INIT;
			}
			else
			{
			}
		}

		// Increment pattern position
		g_aiPlayPatternPositions[2]++;

		// If past end
		if(g_aiPlayPatternPositions[2] >= g_pSound3Patterns[g_aiPlayPatterns[2]].nLength)
		{
			// Set to no pattern
			g_aiPlayPatterns[2] = PATTERN_PARAMETER_EMPTY;
		}
		// If still in pattern
		else
		{
			// Increment pattern parameter iterators
			for(i = 0; i < SOUND3_PARAMETER_COUNT; i++)
			{
				RLEINext(&g_aRLESound3[i]);
			}
		}
	}

	// If a sound 4 pattern is playing
	if( g_aiPlayPatterns[3] != PATTERN_PARAMETER_EMPTY )
	{
		// If a note is struck
		if(g_aRLESound4[SOUND4_PARAMETER_COUNT-1].nValue != PATTERN_PARAMETER_EMPTY)
		{
			if(g_nMuteChannel4 == 0)
			{
				// Set sound channel 4 to ON
//				SGCNT1 |= SGCNT1SND4OPERATE;

				// Get parameters
				for(i = 0; i < SOUND4_PARAMETER_COUNT; i++)
				{
					if(g_aRLESound4[i].nValue != PATTERN_PARAMETER_EMPTY)
						g_anSound4Params[i] = g_aRLESound4[i].nValue;
				}
		
				// Envelope steps
				if(g_anSound4Params[1] <= 0)
				{
					SG40 = SG40SNDLENGTH(g_anSound4Params[2]) | SG40ENVELOPESTEPS(-g_anSound4Params[1]) | SG40ENVELOPEDEC | SG40ENVELOPEINIT(g_anSound4Params[0]);
				}
				else
				{
					SG40 = SG40SNDLENGTH(g_anSound4Params[2]) | SG40ENVELOPESTEPS(g_anSound4Params[1]) | SG40ENVELOPEINC | SG40ENVELOPEINIT(g_anSound4Params[0]);
				}
		
				// Poly steps
				if(g_anSound4Params[5])
				{
					SG41 = SG41DIVRATIOFREQSEL(g_anSound4Params[3]) | SG41STEPS7 | SG41SHIFTFREQ(g_anSound4Params[4]) | SG41PLAYONCE | SG41INIT;
				}
				else
				{
					SG41 = SG41DIVRATIOFREQSEL(g_anSound4Params[3]) | SG41STEPS15 | SG41SHIFTFREQ(g_anSound4Params[4]) | SG41PLAYONCE | SG41INIT;
				}
			}
			else
			{
			}
		}

		// Increment pattern position
		g_aiPlayPatternPositions[3]++;

		// If past end
		if(g_aiPlayPatternPositions[3] >= g_pSound4Patterns[g_aiPlayPatterns[3]].nLength)
		{
			// Set to no pattern
			g_aiPlayPatterns[3] = PATTERN_PARAMETER_EMPTY;
		}
		// If still in pattern
		else
		{
			// Increment pattern parameter iterators
			for(i = 0; i < SOUND4_PARAMETER_COUNT; i++)
			{
				RLEINext(&g_aRLESound4[i]);
			}
		}
	}

	// UPDATE SONG POSITION ///////////

	// Update beats per row counter
	g_iBeatsPerRowCounter++;

	// Update play position
	g_iPlayPosition++;

	// If past end
	if(g_iPlayPosition >= g_nSongLength)
	{
		// If to loop
		if(g_nPlayState & PLAYSTATE_LOOP)
		{
			// Reset to beginning
			g_iPlayPosition = 0;

			// Set beats per row counter to update pattern
			g_iBeatsPerRowCounter = g_nSequencerBeatsPerRow;

			// Reset sequencer iterators
			for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
			{
				g_aiPlayPatternPositions[i] = 0;
				g_aiPlayPatterns[i] = PATTERN_PARAMETER_EMPTY;

				// Set sequencer iterators
				RLEISet(g_apSequencerParams[i], &g_aRLESequencer[i]);
			}
		}
		// If to stop
		else
		{
			BoyScoutStopSong();
			return(0);
		}
	}
	// If still in sequencer pattern
	else
	{
		// If sequencer parameters should be updated
		if(g_iBeatsPerRowCounter >= g_nSequencerBeatsPerRow)
		{
			// Increment sequencer parameter iterators
			for(i = 0; i < SOUND_CHANNEL_COUNT; i++)
			{
				// Get next sequencer step
				RLEINext(&g_aRLESequencer[i]);
			}
		}
	}

	// If to update patterns
	if(g_iBeatsPerRowCounter >= g_nSequencerBeatsPerRow)
	{
		// Reset counter
		g_iBeatsPerRowCounter = 0;

		// If a sound 1 pattern is set in sequencer
		if(g_aRLESequencer[0].nValue != PATTERN_PARAMETER_EMPTY)
		{
			g_aiPlayPatternPositions[0] = 0;
			g_aiPlayPatterns[0] = g_aRLESequencer[0].nValue;
			for(i = 0; i < SOUND1_PARAMETER_COUNT; i++)
			{
				RLEISet(g_pSound1Patterns[g_aiPlayPatterns[0]].apParams[i], &g_aRLESound1[i]);
			}
		}
	
		// If a sound 2 pattern is set in sequencer
		if(g_aRLESequencer[1].nValue != PATTERN_PARAMETER_EMPTY)
		{
			g_aiPlayPatternPositions[1] = 0;
			g_aiPlayPatterns[1] = g_aRLESequencer[1].nValue;
			for(i = 0; i < SOUND2_PARAMETER_COUNT; i++)
			{
				RLEISet(g_pSound2Patterns[g_aiPlayPatterns[1]].apParams[i], &g_aRLESound2[i]);
			}
		}

		// If a sound 3 pattern is set in sequencer
		if(g_aRLESequencer[2].nValue != PATTERN_PARAMETER_EMPTY)
		{
			g_aiPlayPatternPositions[2] = 0;
			g_aiPlayPatterns[2] = g_aRLESequencer[2].nValue;
			for(i = 0; i < SOUND3_PARAMETER_COUNT; i++)
			{
				RLEISet(g_pSound3Patterns[g_aiPlayPatterns[2]].apParams[i], &g_aRLESound3[i]);
			}
		}

		// If a sound 4 pattern is set in sequencer
		if(g_aRLESequencer[3].nValue != PATTERN_PARAMETER_EMPTY)
		{
			g_aiPlayPatternPositions[3] = 0;
			g_aiPlayPatterns[3] = g_aRLESequencer[3].nValue;
			for(i = 0; i < SOUND4_PARAMETER_COUNT; i++)
			{
				RLEISet(g_pSound4Patterns[g_aiPlayPatterns[3]].apParams[i], &g_aRLESound4[i]);
			}
		}
	}

	// UPDATE SOUND3 WAVE FORM DATA //

	// If a new waveform is set
	if(g_aRLESound3[2].nValue != g_nSound3PlayWaveForm && g_aRLESound3[2].nValue != PATTERN_PARAMETER_EMPTY)
	{
		// If a valid wave form
		if(g_aRLESound3[2].nValue < g_cSound3WaveForms)
		{
			// Set wave form
			g_nSound3PlayWaveForm = g_aRLESound3[2].nValue;


            // WK add conditional define, and fix software copy

			// Copy wave form to WRAM
            #if(USE_DMA)
            
			DMA3Copy32((unsigned int)&g_pSound3WaveForms[4*g_nSound3PlayWaveForm], (unsigned int)&SGWRAM, 4);

            #else

			unsigned int *pDst, *pSrc;
			pSrc = (unsigned int*)&g_pSound3WaveForms[4*g_nSound3PlayWaveForm];
			pDst = (unsigned int*)&SGWRAM;
			pDst[0] = pSrc[0];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[2];
			pDst[3] = pSrc[3];

            #endif

			g_iSound3PlayBank ^= 1;
/*			// Set to correct bank
			if(g_iSound3PlayBank == 1)
				SG30L = SG30LSTEP32 | SG30LSETBANK0;
			else
				SG30L = SG30LSTEP32 | SG30LSETBANK1;
*/	
		}
	}

	// Success
	return(1);
}
// End of BoyScoutUpdateSong

//////////////////////////////////////////////////////////////////////
// Function: BoyScoutGetNeededSongMemory                            //
//                                                                  //
// Description: Calculates the needed memory area size needed by a  //
//              certain BoyScout song.                              //
//                                                                  //
// Parameters: Pointer to song data.                                //
//                                                                  //
// Returns: The needed memory area size in bytes.                   //
//                                                                  //
unsigned short BoyScoutGetNeededSongMemory(const unsigned char *pSongData)//
{
	unsigned short nSize;

	// Go past file size - 4 bytes
	pSongData += 4;

	// Calculate memory needed by pattern structures
	nSize = (*pSongData)*sizeof(SSound1Pattern);
	pSongData++;

	nSize += (*pSongData)*sizeof(SSound2Pattern);
	pSongData++;

	nSize += (*pSongData)*sizeof(SSound3Pattern);
	pSongData++;

	nSize += (*pSongData)*sizeof(SSound4Pattern);
	pSongData++;

	return(nSize);
}
// End of BoyScoutGetNeededSongMemory

///////////////////////////////////////////////////////////////////////
// Function: BoyScoutSetMemoryArea                                   //
//                                                                   //
// Description: Sets the address to the beginning of a memory area   //
//				that BoyScout may use. This is basically for storing //
//				pattern description for faster access times.         //
//                                                                   //
// Parameters: Address to the memory area beginning.                 //
//                                                                   //
void BoyScoutSetMemoryArea(unsigned int nMemoryAddress) ///////////////
{
	// Set it
	g_nBoyScoutMemoryArea = nMemoryAddress;
}
// End of BoyScoutSetMemoryArea

///////////////////////////////////////////////////////////////////////
// Function: BoyScoutGetMemoryArea                                   //
//                                                                   //
// Description: Gets the address to the BoyScout memory area.        //
//                                                                   //
// Returns: Address to the beginning of the memory area.             //
//                                                                   //
unsigned int BoyScoutGetMemoryArea() //////////////////////////////////
{
	// Return it
	return(g_nBoyScoutMemoryArea);
}
// End of BoyScoutGetMemoryArea

// WK increase the speed by a value, on overflow, do nothing
void BoyScoutIncSpeed(unsigned char speed)
{
    BoyScoutSetSpeed( g_nPlaySpeed - speed);
}

void BoyScoutDecSpeed(unsigned char speed)
{
    BoyScoutSetSpeed( g_nPlaySpeed + speed);
}

void BoyScoutSetSpeed(unsigned char speed)
{
    if(speed < 30)
        g_nPlaySpeed = speed;
}

unsigned char BoyScoutGetNormalSpeed()
{
    return g_nBeatLength;
}

unsigned char BoyScoutGetSpeed()
{
    return g_nPlaySpeed;
}


// WK mute seprate channels
void BoyScoutMuteChannel1(int mute)
{
    g_nMuteChannel1 = mute;
}

void BoyScoutMuteChannel2(int mute)
{
    g_nMuteChannel2 = mute;
}

void BoyScoutMuteChannel3(int mute)
{
    g_nMuteChannel3 = mute;
}

void BoyScoutMuteChannel4(int mute)
{
    g_nMuteChannel4 = mute;
}

