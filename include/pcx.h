#ifndef _pcx_h_
#define _pcx_h_

typedef struct{
char		manufacturer;
char		version;
char		encoding;
char		bpp;
short int	x1,y1;
short int	x2,y2;
short int	hres;
short int	vres;
char		palette[48];
char		reserved;
char		color_planes;
short int	BytesPerLine;
short int	PaletteType;
char		dummy[58];
}__attribute__ ((packed)) pcx_header;

void DecodePCX(const u8 *PCXBuffer, u16 *ScreenAddr, u16 *Palette);

#endif // _pcx_h_
