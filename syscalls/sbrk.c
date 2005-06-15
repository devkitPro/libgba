#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include <unistd.h>

extern char *fake_heap_end;
extern char *fake_heap_start;

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");

caddr_t
_sbrk (int incr)
{
  extern char   end asm ("end");	/* Defined by the linker.  */
  static char * heap_end;
  char *        prev_heap_end;
  char *		our_heap_end;

  if (heap_end == NULL)
  {
  	if (fake_heap_start == NULL)
  	{
    heap_end = & end;
    }
    else
    {
    	heap_end = fake_heap_start;
    }
  }
  
  prev_heap_end = heap_end;
  
	if (fake_heap_end == NULL)
	{
		our_heap_end = stack_ptr;
	}
	else
	{
		our_heap_end = fake_heap_end;
	}

	if (heap_end + incr > our_heap_end)
	{
		errno = ENOMEM;
		return (caddr_t) -1;
	}
  
	heap_end += incr;

	return (caddr_t) prev_heap_end;
}
