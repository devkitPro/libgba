//---------------------------------------------------------------------------------
#ifndef	_xcomms_h_
#define	_xcomms_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_types.h"

//---------------------------------------------------------------------------------
// Don't Use these function names
//---------------------------------------------------------------------------------
void	xcomms_dprintf	(char *str, ...);
void	xcomms_dfprintf	(int handle, char *str, ...);
void	xcomms_dputchar	(int c);

u8		xcomms_dfopen	(const char *file, const char *type);
void	xcomms_dfclose	(int handle);
u8		xcomms_dfgetc	(int handle);
void	xcomms_dfputc	(int ch, int handle);

void	xcomms_fread	( void *buffer, u32 size, u32 count, int handle );
void	xcomms_fwrite	( void *buffer, u32 size, u32 count, int handle );
void	xcomms_drewind	(int handle);

void 	xcomms_fseek	( int handle, u32 offset, int origin );
u32		xcomms_ftell	( int handle );


void	xcomms_send(u32 data);
void	xcomms_sendblock(const void *block, int len);

void	xcomms_init();

//---------------------------------------------------------------------------------
// Use these function names instead
// these will be repeated for VBA & MBV2
//---------------------------------------------------------------------------------
#define dprintf		xcomms_dprintf
#define dfprintf	xcomms_dfprintf
#define dputchar	xcomms_dputchar

#define dfopen		xcomms_dfopen
#define dfseek		xcomms_fseek
#define dfread		xcomms_fread
#define dfwrite		xcomms_fwrite
#define dftell		xcomms_ftell
#define dfclose		xcomms_dfclose
#define dfgetc		xcomms_dfgetc
#define dfputc		xcomms_dfputc
#define drewind		xcomms_drewind

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _xcomms_h
