#include "gba_interrupt.h"
#include "gba_video.h"

//---------------------------------------------------------------------------------
struct IntTable IntrTable[Int_Count];
void dummy(void) {};


//---------------------------------------------------------------------------------
void InitInterrupt(void)
//---------------------------------------------------------------------------------
{
	int i;

	// Set all interrupts to dummy functions.
	for(i = 0; i < Int_Count; i ++)
	{
		IntrTable[i].handler = dummy;
		IntrTable[i].mask = 0;
	}

	INT_VECTOR = IntrMain;

}

//---------------------------------------------------------------------------------
void SetInterrupt(eINT interrupt, IntFn function)
//---------------------------------------------------------------------------------
{
	int i;
	u32 mask = BIT(interrupt);

	for	(i=0;;i++)
	{
		if	(!IntrTable[i].mask || IntrTable[i].mask == mask) break;
	}

	IntrTable[i].handler	= function;
	IntrTable[i].mask		= mask;

}

//---------------------------------------------------------------------------------
void EnableInterrupt(eINT interrupt)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;
	switch(interrupt)
	{
		case Int_Vblank:
			REG_DISPSTAT |= LCDC_VBL;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Hblank:
			REG_DISPSTAT |= LCDC_HBL;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Vcount:
			REG_DISPSTAT |= LCDC_VCNT;
			REG_IE |= BIT(interrupt);
			break;
		case Int_Timer0:
		case Int_Timer1:
		case Int_Timer2:
		case Int_Timer3:
		case Int_Serial:
		case Int_DMA0:
		case Int_DMA1:
		case Int_DMA2:
		case Int_DMA3:
		case Int_KeyPad:
		case Int_Cart:
			REG_IE |= BIT(interrupt);
			break;
	}
	REG_IME	= 1;
}

//---------------------------------------------------------------------------------
void DisableInterrupt(eINT interrupt)
//---------------------------------------------------------------------------------
{
	REG_IME	= 0;

	switch(interrupt)
	{
		case Int_Vblank:
			REG_DISPSTAT &= ~LCDC_VBL;
			REG_IE &= BIT(interrupt);
			break;
		case Int_Hblank:
			REG_DISPSTAT &= ~LCDC_HBL;
			REG_IE &= BIT(interrupt);
			break;
		case Int_Vcount:
			REG_DISPSTAT &= ~LCDC_VCNT;
			REG_IE &= ~BIT(interrupt);
			break;
		case Int_Timer0:
		case Int_Timer1:
		case Int_Timer2:
		case Int_Timer3:
		case Int_Serial:
		case Int_DMA0:
		case Int_DMA1:
		case Int_DMA2:
		case Int_DMA3:
		case Int_KeyPad:
		case Int_Cart:
			REG_IE &= ~BIT(interrupt);
			break;
		case Ints_All:
			REG_IE = 0;
			REG_DISPSTAT &= ~(LCDC_VBL | LCDC_HBL | LCDC_VCNT);
			break;
	}
	REG_IME	= 1;

}
