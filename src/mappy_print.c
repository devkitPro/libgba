#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define __DOUTBUFSIZE 256

unsigned char __outstr[__DOUTBUFSIZE];

//---------------------------------------------------------------------------------
// VBoy and Mappy debug console output
//---------------------------------------------------------------------------------
static void dprint(const char *sz)
//---------------------------------------------------------------------------------
{
	asm volatile(
	"mov r2, %0\n"
	"ldr r0, =0xc0ded00d\n"
	"mov r1, #0\n"
	"and r0, r0, r0\n"
	:
	:
	"r" (sz) :
	"r0", "r1", "r2");
}


//---------------------------------------------------------------------------------
void mappy_dprintf(char *str, ...)
//---------------------------------------------------------------------------------
{
	va_list args;

	va_start(args, str);
	vsnprintf(__outstr,__DOUTBUFSIZE,str,args);
	va_end(args);

	dprint(__outstr);
}

//---------------------------------------------------------------------------------
void	mappy_dputchar	(int c)
//---------------------------------------------------------------------------------
{
	snprintf(__outstr,__DOUTBUFSIZE,"%c",c);
	dprint(__outstr);
}



