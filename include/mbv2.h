//---------------------------------------------------------------------------------
#ifndef	_mbv2_h_
#define	_mbv2_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// Don't Use these function names
//---------------------------------------------------------------------------------
void	mbv2_dprintf	(char *str, ...);
void	mbv2_dfprintf	(int fp, char *str, ...);
int		mbv2_dputchar	(int c);
int		mbv2_dgetch		(void);
int		mbv2_dkbhit		(void);

int		mbv2_dfopen		(const char *file, const char *type);
int		mbv2_dfclose	(int fp);
int		mbv2_dfgetc		(int fp);
int		mbv2_dfputc		(int ch, int fp);
void	mbv2_drewind	(int fp);

//---------------------------------------------------------------------------------
// Use these function names instead
// these will be repeated for VBA & Xcomms
//---------------------------------------------------------------------------------
#define dprintf		mbv2_dprintf
#define dfprintf	mbv2_dfprintf
#define dputchar	mbv2_dputchar
#define dgetch		mbv2_dgetch
#define dkbhit		mbv2_dkbhit

#define dfopen		mbv2_dfopen
#define dfclose		mbv2_dfclose
#define dfgetc		mbv2_dfgetc
#define dfputc		mbv2_dfputc
#define drewind		mbv2_drewind

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _mbv2_h
