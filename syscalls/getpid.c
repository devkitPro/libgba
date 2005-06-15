#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#undef errno
extern int errno;

int _DEFUN(getpid,(),
           _NOARGS)
{
	return -1;
}
