/*! \file gba_types.h
    The basic types for GBA development.

*/
//---------------------------------------------------------------------------------
#ifndef	_gba_types_h_
#define	_gba_types_h_
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// Data	types
//---------------------------------------------------------------------------------
/** Unsigned 8 bit value

*/
typedef	unsigned char			u8;
/** Unsigned 16 bit value

*/
typedef	unsigned short int		u16;
/** Unsigned 32 bit value

*/
typedef	unsigned int			u32;

/** signed 8 bit value

*/
typedef	signed char				s8;
/** Signed 16 bit value

*/
typedef	signed short int		s16;
/** Signed 32 bit value

*/
typedef	signed int				s32;

/** Unsigned volatile 8 bit value

*/
typedef	volatile u8				vu8;
/** Unsigned volatile 16 bit value

*/
typedef	volatile u16			vu16;
/** Unsigned volatile 32 bit value

*/
typedef	volatile u32			vu32;

/** Unsigned volatile 8 bit value

*/
typedef	volatile s8				vs8;
/** Signed volatile 16 bit value

*/
typedef	volatile s16			vs16;
/** Signed volatile 32 bit value

*/
typedef	volatile s32			vs32;

#ifndef __cplusplus
/** C++ compatible bool for C

*/
typedef enum { false, true } bool;
#endif

//---------------------------------------------------------------------------------
#endif // _gba_types_h_
//---------------------------------------------------------------------------------

