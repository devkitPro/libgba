//---------------------------------------------------------------------------------
#ifndef	_mappy_h_
#define	_mappy_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_types.h"

//---------------------------------------------------------------------------------
// Don't Use these function names
//---------------------------------------------------------------------------------
void	mappy_dprintf	(char *str, ...);
void	mappy_dputchar	(int c);

//---------------------------------------------------------------------------------
// Use these function names instead
// these will be repeated for Xcomms & MBV2
//---------------------------------------------------------------------------------
#define dprintf		mappy_dprintf
#define dputchar	mappy_dputchar

//---------------------------------------------------------------------------------
// Sorry no file stuff
//---------------------------------------------------------------------------------
#define dfprintf
#define dfopen
#define dfseek
#define dfread
#define dfwrite
#define dftell
#define dfclose
#define dfgetc
#define dfputc
#define drewind


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _mappy_h
