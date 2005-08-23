/////////////////////////////////////////////////////////////
// File: GBASoundRegs.h                                    //
//                                                         //
// Description: The GameBoy sound registers. Included with //
//              the BoyScout music playback code.          //
//                                                         //
// Author: Christer Andersson (c) 2001                     //
//                                                         //
/////////////////////////////////////////////////////////////

// Make sure this header is only included once
#ifndef HEADER_GBASOUNDREGS_H
#define HEADER_GBASOUNDREG_H

///////////////////////
// CONTROL REGISTERS //
///////////////////////

#define SGCNT0L		*(unsigned short*)0x04000080	// Final sound control register addresses
#define SGCNT0H		*(unsigned short*)0x04000082
#define SGCNT1		*(unsigned short*)0x04000084

#define SGCNT0LROUT(n)		n			// Right speaker output level (0-7)
#define SGCNT0LLOUT(n)		(n<<4)		// Left speaker output level (0-7)

#define SGCNT0LSND1RENABLED	(1<<8)		// Enable left & right speakers for each sound channel
#define SGCNT0LSND1LENABLED	(1<<12)
#define SGCNT0LSND2RENABLED	(1<<9)
#define SGCNT0LSND2LENABLED	(1<<13)
#define SGCNT0LSND3RENABLED	(1<<10)
#define SGCNT0LSND3LENABLED	(1<<14)
#define SGCNT0LSND4RENABLED	(1<<11)
#define SGCNT0LSND4LENABLED	(1<<15)

#define SGCNT0HSNDOUTPUT14		0		// Output ratios (1/4, 1/2 or 1/1)
#define SGCNT0HSNDOUTPUT12		1		// for sound synthesis (sound 1-4)
#define SGCNT0HSNDOUTPUT1		2

#define SGCNT0HDSAOUTPUT12		(0<<2)  // Output ratio for direct sound channel A
#define SGCNT0HDSAOUTPUT1		(1<<2)	// (1/2 or 1/1)
#define SGCNT0HDSBOUTPUT12		(0<<3)  // Output ratio for direct sound channel B
#define SGCNT0HDSBOUTPUT1		(1<<3)	// (1/2 or 1/1)

#define SGCNT0HDSARENABLED		(1<<8)	// Enable left & right speakers for 
#define SGCNT0HDSALENABLED		(1<<9)	// direct sound channel A
#define SGCNT0HDSBRENABLED		(1<<12)	// Enable left & right speakers for 
#define SGCNT0HDSBLENABLED		(1<<13)	// direct sound channel A

#define SGCNT0HDSATIMER0		(0<<10) // Timer selection 0 or 1 for each 
#define SGCNT0HDSATIMER1		(1<<10) // direct sound channel A & B
#define SGCNT0HDSBTIMER0		(0<<14)
#define SGCNT0HDSBTIMER1		(1<<14)

#define SGCNT0HDSFIFOARESET		(1<<11) // Reset FIFO and sequencer for each direct sound A & B
#define SGCNT0HDSFIFOBRESET		(1<<15)

#define SGCNT1SND1OPERATE		1		// Turn sound operation ON
#define SGCNT1SND2OPERATE		(1<<1)
#define SGCNT1SND3OPERATE		(1<<2)
#define SGCNT1SND4OPERATE		(1<<3)
#define SGCNT1ALLSNDOPERATE		(1<<7)

/////////////
// SOUND 1 //
/////////////

#define SG10L	*(unsigned short*)0x04000060		// Addresses of sound 1 registers
#define SG10H	*(unsigned short*)0x04000062
#define SG11	*(unsigned short*)0x04000064

#define SG10LSWEEPSHIFTS(n)		n		// Number of sweep shifts (0-7)
#define SG10LSWEEPSHIFTINC		(0<<3)	// Number of sweep shifts (0-7)
#define SG10LSWEEPSHIFTDEC		(1<<3)	// Number of sweep shifts (0-7)
#define SG10LSWEEPTIME(n)		(n<<4)	// Time of sweep (0-7)

#define SG10HSNDLENGTH(n)		n		// Length of sound (0-63)
#define SG10HWAVEDUTYCYCLE(n)	(n<<6)	// Waveform proportions (0-3)
#define SG10HENVELOPESTEPS(n)	(n<<8)	// Envelope steps (0-7)
#define SG10HENVELOPEINC		(1<<11)	// If to increase or decrease envelope
#define SG10HENVELOPEDEC		(0<<11)
#define SG10HENVELOPEINIT(n)	(n<<12) // Initial envelope (0-15)

#define SG11FREQUENCY(n)		n		// Frequency 11-bits
#define SG11PLAYONCE			(1<<14)	// Play sound once
#define SG11PLAYLOOP			(0<<14)	// Loop sound
#define SG11INIT				(1<<15) // Makes the sound restart

/////////////
// SOUND 2 //
/////////////

#define SG20	*(unsigned short*)0x04000068
#define SG21	*(unsigned short*)0x0400006C

#define SG20SNDLENGTH(n)		n		// Length of sound (0-63)
#define SG20WAVEDUTYCYCLE(n)	(n<<6)	// Waveform proportions (0-3)
#define SG20ENVELOPESTEPS(n)	(n<<8)	// Envelope steps (0-7)
#define SG20ENVELOPEINC			(1<<11)	// If to increase or decrease envelope
#define SG20ENVELOPEDEC			(0<<11)
#define SG20ENVELOPEINIT(n)		(n<<12)	// Initial envelope (0-15)

#define SG21FREQUENCY(n)		n		// Frequency 11-bits
#define SG21PLAYONCE			(1<<14)	// Play sound once
#define SG21PLAYLOOP			(0<<14)	// Loop sound
#define SG21INIT				(1<<15) // Makes the sound restart

/////////////
// SOUND 3 //
/////////////

#define SG30L	*(volatile unsigned short* volatile)0x04000070	// Addresses to sound 3 registers
#define SG30H	*(volatile unsigned short* volatile)0x04000072
#define SG31	*(volatile unsigned short* volatile)0x04000074

#define SGWRAM	*(unsigned short*)0x04000090	// Address of sound 3 wave RAM (16 bytes 4bit/step)

#define SG30LSTEP32		(0<<5)	// Use two banks of 32 steps each
#define SG30LSTEP64		(1<<5)	// Use one bank of 64 steps
#define SG30LSETBANK0	(0<<6)	// Bank to play 0 or 1 (non set bank is written to)
#define SG30LSETBANK1	(1<<6)
#define SG30LPLAY		(1<<7)	// Output sound
#define SG30LSTOP		(0<<7)	// Stop sound output

#define SG30HSNDLENGTH(n)	n		// Length of sound playback (0-255)
#define SG30HOUTPUTMUTE		(0<<13)	// Mute output
#define SG30HOUTPUT1		(1<<13)	// Output unmodified
#define SG30HOUTPUT12		(2<<13)	// Output 1/2 (right shift of 1)
#define SG30HOUTPUT14		(3<<13)	// Output 1/4 (right shift of 2)
#define SG30HOUTPUT34		(1<<15) // Output 3/4

#define SG31FREQUENCY(n)	n		// 11-bit frequency data
#define SG31PLAYONCE		(1<<14)	// Play sound once
#define SG31PLAYLOOP		(0<<14)	// Play sound looped
#define SG31INIT			(1<<15)	// Makes the sound restart

/////////////
// SOUND 4 //
/////////////

#define SG40	*(unsigned short*)0x04000078		// Addresses to sound 4 registers
#define SG41	*(unsigned short*)0x0400007C

#define SG40SNDLENGTH(n)		n		// Sound length (0-63)
#define SG40ENVELOPESTEPS(n)	(n<<8)	// Envelope steps (0-7)
#define SG40ENVELOPEINC			(1<<11)	// Increase or decrease envelope
#define SG40ENVELOPEDEC			(0<<11)	
#define SG40ENVELOPEINIT(n)		(n<<12)	// Initial envelope value

#define SG41DIVRATIOFREQSEL(n)	n		// (0-7)
#define SG41STEPS7				(1<<3)
#define SG41STEPS15				(0<<3)
#define SG41SHIFTFREQ(n)		(n<<4)	// (0-15)
#define SG41PLAYONCE			(1<<14)
#define SG41PLAYLOOP			(0<<14)
#define SG41INIT				(1<<15)

////////////////////
// DMA3 Registers //
////////////////////

#define DMA3SRC		*(volatile unsigned int*)0x040000D4   // Source address of transfer (27-bit)
#define DMA3DST		*(volatile unsigned int*)0x040000D8   // Destination address of transfer (27-bit) 
#define DMA3COUNT	*(volatile unsigned short*)0x040000DC // Count of characters that should be transferred (14-bit)
#define DMA3CNT		*(volatile unsigned short*)0x040000DE // DMA3 transfer control register

// Control of destination address for transfer
#define DMACNTDSTINC		(0<<5)	// Increment
#define DMACNTDSTDEC		(1<<5)	// Decrement
#define DMACNTDSTFIX		(2<<5)	// Stay fixed
#define DMACNTDSTINCRELOAD	(3<<5)	// Address is incremented but reset after transfer

// Control of source address for transfer
#define DMACNTSRCINC		(0<<7)	// Increment
#define DMACNTSRCDEC		(1<<7)	// Decrement
#define DMACNTSRCFIX		(2<<7)	// Stay fixed

// If time of transfer is the next VB or HB, DMA transfer
// happens every VB/HB
#define DMACNTREPEAT		(1<<9)

// Tranfer mode
#define DMACNTTRANSFER16	(0<<10)		// Transfer in 16-bit units
#define DMACNTTRANSFER32	(1<<10)		// Transfer in 32-bit units

// Time of transfer
#define DMACNTSTARTIM		(0<<12)		// Immediately
#define DMACNTSTARTVB		(1<<12)		// Next vertical blank
#define DMACNTSTARTHB		(2<<12)		// Next horizontal blank

// Enable interrupt request when transfer is done
#define DMACNTINTENABLE		(1<<14)

// Enable DMA transfer
#define DMACNTENABLE		(1<<15)


#endif



