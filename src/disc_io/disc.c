/*

	disc.c

	uniformed io-interface to work with Chishm's FAT library

	Written by MightyMax, modified by Chishm
  

 Copyright (c) 2006 Michael "Chishm" Chisholm
	
 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.
  3. The name of the author may not be used to endorse or promote products derived
     from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <disc_io.h>

// Include known io-interfaces:
#include "io_mpcf.h"
#include "io_m3cf.h"
#include "io_sccf.h"
#include "io_scsd.h"
#include "io_m3sd.h"

static const DISC_INTERFACE* discInterfaces[] = {
	&_io_mpcf, &_io_m3cf, &_io_sccf, &_io_scsd, &_io_m3sd
};

const DISC_INTERFACE* discGetInterface (void)
{
	int i;

	for (i = 0; i < (sizeof(discInterfaces) / sizeof(DISC_INTERFACE*)); i++) {
		if (discInterfaces[i]->startup()) {
			return discInterfaces[i];
		}
	}
	return NULL;
}

