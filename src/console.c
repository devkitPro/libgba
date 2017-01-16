/*
	Copyright 2003-2007 by Dave Murphy.

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

*/

#include <sys/iosupport.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_console.h>

#include <stdio.h>

void consolePrintChar(char c);

//---------------------------------------------------------------------------------
ssize_t con_read(struct _reent *r,void *fileStruct,char *ptr,size_t len) {
//---------------------------------------------------------------------------------
	return -1;
}

//---------------------------------------------------------------------------------
int con_close(struct _reent *r,void *fileStruct) {
//---------------------------------------------------------------------------------
	return -1;
}

static bool consoleInitialised = false;

//---------------------------------------------------------------------------------
int con_open(struct _reent *r, void *fileStruct, const char *path, int flags, int mode) {
//---------------------------------------------------------------------------------
	if (consoleInitialised) return 0;
	return -1;
}
/*
       ESC code sequence                  Function
       -------------------         ---------------------------
Cursor Controls:
         ESC[#;#H or ESC[#;#f      Moves cusor to line #, column #
         ESC[#A                    Moves cursor up # lines
         ESC[#B                    Moves cursor down # lines
         ESC[#C                    Moves cursor forward # spaces
         ESC[#D                    Moves cursor back # spaces
         ESC[s                     Saves cursor position for recall later
         ESC[u                     Return to saved cursor position

Erase Functions:
         ESC[2J                    Clear screen and home cursor
         ESC[K                     Clear to end of line

Set Graphics Rendition:
         ESC[#;#;....;#m           not implemented
*/


static int consoleX, consoleY;
static int savedX, savedY;
static int consoleMap, consolePalette;

#define CONSOLE_WIDTH	30
#define CONSOLE_HEIGHT	20

//---------------------------------------------------------------------------------
void consoleCls() {
//---------------------------------------------------------------------------------

	*((u32 *)MAP_BASE_ADR(consoleMap)) = 0x00200020;
	CpuFastSet( MAP_BASE_ADR(consoleMap), MAP_BASE_ADR(consoleMap), FILL | (0x800/4));
}

//---------------------------------------------------------------------------------
ssize_t con_write(struct _reent *r,void *fileStruct ,const char *ptr,size_t len) {
//---------------------------------------------------------------------------------
	char chr;

	if (!consoleInitialised) return -1;

	int i, count = 0;
	char *tmp = (char*)ptr;

	if(!tmp || len<=0) return -1;

	i = 0;
	while(*tmp!='\0' && i<len) {

		chr = *(tmp++);
		i++; count++;

		if ( chr == 0x1b && *tmp == '[' ) {
			bool escaping = true;
			char *escapeseq	= tmp;
			int escapelen = 0;

			do {
				chr = *(tmp++);
				i++; count++; escapelen++;
				int parameter;
				switch (chr) {
					case 'H':
						siscanf(escapeseq,"[%d;%dH", &consoleY, &consoleX);
						escaping = false;
						break;
					case 'f':
						siscanf(escapeseq,"[%d;%df", &consoleY, &consoleX);
						escaping = false;
						break;
					case 'A':
						siscanf(escapeseq,"[%dA", &parameter);
						consoleY =  (consoleY - parameter) < 0 ? 0 : consoleY - parameter;
						escaping = false;
						break;
					case 'B':
						siscanf(escapeseq,"[%dB", &parameter);
						consoleY =  (consoleY + parameter) > CONSOLE_HEIGHT - 1 ? CONSOLE_HEIGHT - 1 : consoleY + parameter;
						escaping = false;
						break;
					case 'C':
						siscanf(escapeseq,"[%dC", &parameter);
						consoleX =  (consoleX + parameter) > CONSOLE_WIDTH - 1 ? CONSOLE_WIDTH - 1 : consoleX + parameter;
						escaping = false;
						break;
					case 'D':
						siscanf(escapeseq,"[%dC", &parameter);
						consoleX =  (consoleX - parameter) < 0 ? 0 : consoleX - parameter;
						escaping = false;
						break;
					case 'K':
						escaping = false;
						break;
					case 's':
						savedX = consoleX;
						savedY = consoleY;
						escaping = false;
						break;
					case 'u':
						consoleX = savedX;
						consoleY = savedY;
						escaping = false;
						break;
					case 'J':
						if ( escapeseq[escapelen-2] == '2') {
							consoleCls();
							consoleX = 0;
							consoleY = 0;
						}
						escaping = false;
					break;
				}
			} while (escaping);
		continue;
		}

		consolePrintChar(chr);
	}

	return count;
}


const devoptab_t dotab_stdout = {
	"con",
	0,
	con_open,
	con_close,
	con_write,
	con_read,
	NULL,
	NULL
};

const devoptab_t dotab_stderr = {
	"con",
	0,
	con_open,
	con_close,
	con_write,
	con_read,
	NULL,
	NULL
};


//---------------------------------------------------------------------------------
// upcvt_4bit()
// Convert a 1-bit font to GBA 4-bit format.
//---------------------------------------------------------------------------------
void upcvt_4bit(void *dst, const u8 *src, u32 len) {
//---------------------------------------------------------------------------------
	u32 *out = dst;

	for(; len > 0; len--) {
		u32 dst_bits = 0;
		u32 src_bits = *src++;
		u32 x;

		for(x = 0; x < 8; x++) {
			dst_bits <<= 4;
			dst_bits |= src_bits & 1;
			src_bits >>= 1;
		}
	*out++ = dst_bits;
	}
}

#include <amiga_fnt.h>

//---------------------------------------------------------------------------------
void consoleInit(	int charBase, int mapBase, int background,
					const u8* font, int fontsize, int palette) {
//---------------------------------------------------------------------------------

	BGCTRL[background] = BG_SIZE_0 | CHAR_BASE(charBase) | SCREEN_BASE(mapBase);

	if (font == NULL || fontsize == 0) {
		font = amiga_fnt;
		fontsize = amiga_fnt_size;
	}

	upcvt_4bit(CHAR_BASE_ADR(charBase), font, fontsize);

	consoleMap = mapBase;
	consolePalette = palette;

	devoptab_list[STD_OUT] = &dotab_stdout;
	devoptab_list[STD_ERR] = &dotab_stderr;
	setvbuf(stderr, NULL , _IONBF, 0);
	setvbuf(stdout, NULL , _IONBF, 0);
	consoleCls();
	consoleInitialised = true;

}

//---------------------------------------------------------------------------------
void consoleDemoInit() {
//---------------------------------------------------------------------------------
	// initialise the console
	// setting NULL & 0 for the font address & size uses the default font
	// The font should be a complete 1bit 8x8 ASCII font
	consoleInit(	0,		// charbase
					4,		// mapbase
					0,		// background number
					NULL,	// font
					0, 		// font size
					15		// 16 color palette
	);

	// set the screen colors, color 0 is the background color
	// the foreground color is index 1 of the selected 16 color palette
	BG_COLORS[0]=RGB8(58,110,165);
	BG_COLORS[241]=RGB5(31,31,31);

	SetMode(MODE_0 | BG0_ON);

}

//---------------------------------------------------------------------------------
static void newRow() {
//---------------------------------------------------------------------------------
	consoleY++;

	if(consoleY >= CONSOLE_HEIGHT) {
		consoleY--;

		u16 * dst = (u16 *)(VRAM + (SCREEN_BASE(consoleMap)<<3));
		u16 * src = (u16 *)(VRAM + (SCREEN_BASE(consoleMap)<<3) + (1 << 6));

		int i;
		for ( i = 0; i < CONSOLE_HEIGHT; i++ ) {
			CpuFastSet( src, dst, COPY32 | (CONSOLE_WIDTH/2) );
			dst += (1<<5);
			src += (1<<5);
		}
	}
}

//---------------------------------------------------------------------------------
void consolePrintChar(char c) {
//---------------------------------------------------------------------------------

	if(consoleX >= CONSOLE_WIDTH) {
		consoleX = 0;
		newRow();
	}

	u16*	ScreenBase = (u16 *)(VRAM + (SCREEN_BASE(consoleMap)<<3) + (consoleX<<1) + (consoleY<<6) );

	switch(c) {

		case 10:
		case 11:
		case 12:
		case 13:
			newRow();
			consoleX = 0;
			break;
		default:
			*(ScreenBase) = CHAR_PALETTE(consolePalette) | (u8)c;
		consoleX++;

	}
}
