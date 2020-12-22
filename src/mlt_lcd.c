#include "mlt_lcd.h"

void SetDataBits (uint8_t value)
{
	MDR_PORTA->RXTX &= 0xFFC0;
	MDR_PORTA->RXTX |= (value & 0x3F); 
	MDR_PORTF->RXTX &= 0xFFF3;
	MDR_PORTF->RXTX |= ((value >> 4) & 0x0c);
}

void MltDelay (uint32_t value)
{
	while ((value--)!=0) { __NOP(); }
}

uint8_t ReadStatus (uint8_t Chip)
{
uint8_t data;

	Data_Dir_InputPA();
	Data_Dir_InputPB();
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Clr_A0_Pin();
	Set_RW_Pin();
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	data = OutputData;
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Clr_A0_Pin();
	Clr_RW_Pin();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}

	return data;
}

void DispOn (uint8_t Chip)
{
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Clr_A0_Pin();
	Clr_RW_Pin();
	MltDelay(5);
	Data_Dir_OutputPA();
	Data_Dir_OutputPB();
	SetDataBits (0x3F);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Clr_A0_Pin();
	Clr_RW_Pin();
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
}

void DispOff (uint8_t Chip)
{
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Clr_A0_Pin();
	Clr_RW_Pin();
	MltDelay(5);
	Data_Dir_OutputPA();
	Data_Dir_OutputPB();
	SetDataBits (0x3E);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Clr_A0_Pin();
	Clr_RW_Pin();
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
}

void SetPage (uint8_t Chip, uint8_t page)
{
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Clr_A0_Pin();
	Clr_RW_Pin();
	MltDelay(5);
	Data_Dir_OutputPA();
	Data_Dir_OutputPB();
	SetDataBits (0xB8 | page);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	Clr_A0_Pin();
	Clr_RW_Pin();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
}

void SetAddress (uint8_t Chip, uint8_t address)
{
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Clr_A0_Pin();
	Clr_RW_Pin();
	MltDelay(5);
	Data_Dir_OutputPA();
	Data_Dir_OutputPB();
	SetDataBits (0x40 | address);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	Clr_A0_Pin();
	Clr_RW_Pin();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
}

void WriteData (uint8_t Chip, uint8_t data)
{
	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Set_A0_Pin();
	Clr_RW_Pin();
	MltDelay(5);
	Data_Dir_OutputPA();
	Data_Dir_OutputPB();
	SetDataBits (data);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	Clr_A0_Pin();
	Clr_RW_Pin();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
}

uint8_t ReadData (uint8_t Chip)
{
	uint8_t data = 0;

	if (Chip == 1) {Set_E1_Pin();}
	else {Set_E2_Pin();}
	Set_A0_Pin();
	Set_RW_Pin();
	MltDelay(5);
	Data_Dir_InputPA();
	Data_Dir_InputPB();
	SetDataBits(data);
	MltDelay(5);
	Set_Stb_Pin();
	MltDelay(5);
	data = OutputData;
	MltDelay(5);
	Clr_Stb_Pin();
	MltDelay(5);
	Clr_A0_Pin();
	Clr_RW_Pin();
	if (Chip == 1) {Clr_E1_Pin();}
	else {Clr_E2_Pin();}
	
	return (data);
}

void LcdInit(void)
{
	uint8_t s1,s2;
 
	Clr_Res_Pin();
	MltDelay (200);
	Set_Res_Pin();
	do
	{
		s1 = ReadStatus(1) & 0x90;
		s2 = ReadStatus(2) & 0x90;
	}
	while (s1 != 0x00 && s2 != 0x00);
}

void LcdClearPage (uint8_t Chip, uint8_t Page)
{
	int i;
	uint8_t s1;

	SetPage (Chip, Page);
	SetAddress (Chip, 0x00);

	for (i = 0; i < LCD_PAGE_COLUMNS; i++)
	{	
		do
		{
			s1 = ReadStatus(Chip);
		} while ((s1 & 0x80) != 0x00);
		WriteData (Chip, 0x00);
	}
}

void LcdClearChip (uint8_t Chip)
{
	uint8_t i;

	for (i = 0; i < LCD_CHIP_PAGES; i++)
	{
		LcdClearPage (Chip, i);
	}
}

void LcdOnAndClear(void)
{
	uint8_t s;
	do
	{
		s = ReadStatus(1);
	} while ((s & 0x80) != 0x00); 
	DispOn(1);
	
	do
	{
		s = ReadStatus(2);
	} while ((s & 0x80) != 0x00);
	DispOn(2);
}

void LcdFullClear(void)
{
	LcdClearChip(1);
	LcdClearChip(2);
}

void LcdPutChar (uint8_t* array,
				 int Xpos,
				 int Ypos,
				 lcd_output_effect_t is_smooth,
				 lcd_output_style_t is_inverted
				)
{
	uint8_t chp, page, adr;
	int i;
	uint8_t s1;

	chp  = (uint8_t)(Xpos/LCD_CHIP_MAX_STRING_SIZE) + 1;
	page = (uint8_t)Ypos;
	adr  = (uint8_t)((Xpos % LCD_CHIP_MAX_STRING_SIZE) * LCD_SYMBOL_BYTES);	

	SetPage (chp, page);
	SetAddress (chp, adr);

	for (i = 0; i < LCD_SYMBOL_BYTES; i++)
	{	
		do
		{
			s1 = ReadStatus(chp);
		} while ((s1 & 0x80) != 0x00);
		
		if (is_inverted)
		{
			WriteData (chp, ~(array[i]));
		}
		else
		{
			WriteData (chp, array[i]);
		}
		
		if (is_smooth)
			MltDelay(0x00030000);
	}
}

void LcdPutString (uint8_t** array, int Ypos)
{
	int i,j;
	uint8_t s1;

	
	SetPage (1, (uint8_t)Ypos);
	SetAddress (1, 0);

	for (i = 0 ; i < LCD_CHIP_PAGES; i++)
	{
		for (j = 0; j < LCD_SYMBOL_BYTES; j++)
		{
			do
			{
				s1 = ReadStatus(1);
			} while ((s1 & 0x80) != 0x00);
			WriteData (1, array[i][j]);
		}
	}
	
	// next actions aren't correct!!! String length may be less than chip length
	SetPage (2, (uint8_t)Ypos);
	SetAddress (2, 0);

	for (i = 0; i < LCD_CHIP_PAGES; i++)
	{
		for (j = 0; j < LCD_SYMBOL_BYTES; j++)
		{
			do
			{
				s1 = ReadStatus(2);
			} while ((s1 & 0x80) != 0x00);
			WriteData (2,array[i+8][j]);
		}
	}

}
