//---------------------------------------------------------------------------------
#ifndef	_gba_compression_h_
#define	_gba_compression_h_
//---------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#include "gba_base.h"

typedef struct {
	u16 SrcNum;				// Source Data Byte Size
	u8  SrcBitNum;			// 1 Source Data Bit Number
	u8  DestBitNum;			// 1 Destination Data Bit Number
	u32 DestOffset:31;		// Number added to Source Data
	u32 DestOffset0_On:1;	// Flag to add/not add Offset to 0 Data
} BUP;


//---------------------------------------------------------------------------------
// Decompression functions
//---------------------------------------------------------------------------------
void BitUnPack(void  *source, void *dest, BUP* bup);
void LZ77UnCompWram(void *source, void *dest);
void LZ77UnCompVram(void *source, void *dest);
void HuffUnComp(void *source, void *dest);
void RLUnCompWram(void *source, void *dest);
void RLUnCompVram(void *source, void *dest);
void Diff8bitUnFilterWram(void *source, void *dest);
void Diff8bitUnFilterVram(void *source, void *dest);
void Diff16bitUnFilter(void *source, void *dest);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif

//---------------------------------------------------------------------------------
#endif //_gba_compression_h_
