#include <_ansi.h>
#include <_syslist.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#undef errno
extern int errno;


int _DEFUN (open, (file, flags, mode),
        char *file  _AND
        int   flags _AND
        int   mode)
{
	return -1;
}
