//---------------------------------------------------------------------------------
#ifndef	_gba_multiboot_h_
#define	_gba_multiboot_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------------

#include "gba_base.h"

typedef	struct {
	u32	reserved1[5];
	u8	handshake_data;
	u8	padding;
	u16	handshake_timeout;
	u8	probe_count;
	u8	client_data[3];
	u8	palette_data;
	u8	response_bit;
	u8	client_bit;
	u8	reserved2;
	u8	*boot_srcp;
	u8	*boot_endp;
	u8	*masterp;
	u8	*reserved3[3];
	u32	system_work2[4];
	u8	sendflag;
	u8	probe_target_bit;
	u8	check_wait;
	u8	server_type;
} MultiBootParam;

enum { MODE32_NORMAL, MODE16_MULTI, MODE32_2MHZ);

u32 MultiBoot(MultiBootParam *mp, u32 mode);


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}	   // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif //_gba_multiboot_h_
