//---------------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_types.h"
#include "libgba_log.h"

//---------------------------------------------------------------------------------
// Don't Use these function names
//---------------------------------------------------------------------------------
void mgba_dputchar    (int c);
void mgba_log         (int level, const char* str, ...);
bool mgba_open        (void);
void mgba_close       (void);
bool mgba_console_open(void);
//---------------------------------------------------------------------------------
// Use these function names instead
// these will be repeated for Xcomms & MBV2
//---------------------------------------------------------------------------------
#define dprintf(...)    mgba_log(LIBGBA_LOG_DEBUG, __VA_ARGS__)
#define dputchar   mgba_dputchar
#define LIBGBA_LOG mgba_log

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

