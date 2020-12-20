#ifndef MLT_LCD_H
#define MLT_LCD_H

#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

/*
		КРАТКОЕ ОПИСАНИЕ ДИСПЛЕЯ LCD MT-12864j И ЕГО КОНТРОЛЛЕРА

 +------------------------------------------+--------------------------+
 |        LCD MT-12864j                     |     Microcontroller      |
 +------------------------------------------+--------------------------+
 | Pin |  Name   |      Function            | Port Line  |    Pin      |
 +-----+---------+--------------------------+------------+-------------+
 |  4  |   DB0   |  Data Bus DB0            |     PA0    |     55      |
 |  5  |   DB1   |  Data Bus DB1            |     PA1    |     54      |
 |  6  |   DB2   |  Data Bus DB2            |     PA2    |     53      |
 |  7  |   DB3   |  Data Bus DB3            |     PA3    |     52      |
 |  8  |   DB4   |  Data Bus DB4            |     PA4    |     51      |
 |  9  |   DB5   |  Data Bus DB5            |     PA5    |     50      |
 |  10 |   DB6   |  Data Bus DB6            |     PF2    |     60      |
 |  11 |   DB7   |  Data Bus DB7            |     PF3    |     61      |
 |  12 |   E1    |  Chip 1 Select           |     PB7    |     44      |
 |  13 |   E2    |  Chip 2 Select           |     PB8    |     45      |
 |  14 |   RES   |  Reset (initial)         |     PB9    |     46      |
 |  15 |   R/W   |  Select: Read/Write      |     PB10   |     47      |
 |  16 |   A0    |  Select: Cmd/Data        |     PC0    |     34      |
 |  17 |   E     |  Strobing                |     PC1    |     33      |
 +-----+---------+--------------------------+------------+-------------+

 Reset: RES = 0 --> delay >= 1 microsec --> RES = 1 --> delay >= 10 microsec 
 A0: 0 - Commands, 1 - Data
 R/W: 0 - Write, 1 - Read

 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Command    | A0 | R/W | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | Description |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | On/Off     |  0 |  0  | 0  | 0  | 1  | 1  | 1  | 1  | 1  | 0/1| 1-on, 0-off |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Start Line |  0 |  0  | 1  | 1  |          (0 - 63)           | Top line LCD|
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Set Page   |  0 |  0  | 1  | 0  | 1  | 1  | 1  |   (0 - 7)    |             |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Set Address|  0 |  0  | 0  | 1  |          (0 - 63)           |             |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Status     |  0 |  1  | F1 | 0  | F2 | F3 | 0  | 0  | 0  | 0  | Flags       |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Write      |  1 |  0  |            DATA FOR OUTPUT            |             |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+
 | Read       |  1 |  1  |            DATA FOR INPUT             |             |
 +------------+----+-----+----+----+----+----+----+----+----+----+-------------+

 Flags: F1 - BUSY, F2 - On/Off, F3 - Reset.

 Chip 1(2): 8 Pages, 64 Byte each page, 1 Byte is 1 Column of Page.

		  0  1  2  3  4       62 63    -> Columns
		+--+--+--+--+--+ ... +--+--+   -+
	DB0	|  |  |  |  |  | ... |  |  |    | 
		+--+--+--+--+--+ ... +--+--+    |
	DB1	|  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+    |
	DB2	|  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+    |
	DB3 |  |  |  |  |  | ... |  |  |    |-> Page (Row)
		+--+--+--+--+--+ ... +--+--+    |
	DB4 |  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+    |
	DB5 |  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+    |
	DB6 |  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+    |
	DB7	|  |  |  |  |  | ... |  |  |    |
		+--+--+--+--+--+ ... +--+--+   -+

*/

#define LCD_SYMBOL_BYTES 8 		// 1 байт = 1 колонка, 8х8 точек на каждый символ
#define LCD_MAX_STRING_SIZE 16 	// При условии, что 8 колонок страницы на каждый символ 
#define LCD_ROW_COLUMNS 128		// Всего колонок (байтов) на два чипа
#define LCD_COLUMN_BITS 8
#define LCD_CHIP_ROW_COLUMNS (LCD_ROW_COLUMNS/2)
#define LCD_CHIP_PAGES 8 		// 1 страница это 1 строка дисплея (или половины дисплея)
#define LCD_CHIP_MAX_STRING_SIZE (LCD_MAX_STRING_SIZE/2)
#define LCD_PAGE_COLUMNS LCD_CHIP_ROW_COLUMNS

// Выводы портов для управляющих сигналов

#define RES_PIN_PORT 	MDR_PORTB
#define RES_PIN 		PORT_Pin_9

#define STB_PIN_PORT 	MDR_PORTA
#define STB_PIN 		PORT_Pin_7

#define RW_PIN_PORT 	MDR_PORTB
#define RW_PIN 			PORT_Pin_10

#define A0_PIN_PORT		MDR_PORTA
#define A0_PIN			PORT_Pin_6

#define E1_PIN_PORT		MDR_PORTB
#define E1_PIN			PORT_Pin_7

#define E2_PIN_PORT		MDR_PORTB
#define E2_PIN			PORT_Pin_8

// Макросы для установки и сброса управляющих сигналов

#define	Set_Res_Pin()	PORT_SetBits  (RES_PIN_PORT, RES_PIN)
#define	Clr_Res_Pin()	PORT_ResetBits(RES_PIN_PORT, RES_PIN)

#define	Set_Stb_Pin()	PORT_SetBits  (STB_PIN_PORT, STB_PIN)
#define	Clr_Stb_Pin()	PORT_ResetBits(STB_PIN_PORT, STB_PIN)

#define	Set_RW_Pin()	PORT_SetBits  (RW_PIN_PORT, RW_PIN)
#define	Clr_RW_Pin()	PORT_ResetBits(RW_PIN_PORT, RW_PIN)

#define	Set_A0_Pin()	PORT_SetBits  (A0_PIN_PORT, A0_PIN)
#define	Clr_A0_Pin()	PORT_ResetBits(A0_PIN_PORT, A0_PIN)

#define	Set_E1_Pin()	PORT_SetBits  (E1_PIN_PORT, E1_PIN)
#define	Clr_E1_Pin()	PORT_ResetBits(E1_PIN_PORT, E1_PIN)

#define	Set_E2_Pin()	PORT_SetBits  (E2_PIN_PORT, E2_PIN)
#define	Clr_E2_Pin()	PORT_ResetBits(E2_PIN_PORT, E2_PIN)

// Макросы для изменения направления передачи по шине данных

#define Data_Dir_InputPA()  MDR_PORTA->OE &= 0xFFC0
#define Data_Dir_OutputPA() MDR_PORTA->OE |= 0x003F
#define Data_Dir_InputPB()  MDR_PORTB->OE &= 0xFFF3
#define Data_Dir_OutputPB() MDR_PORTB->OE |= 0x000C

// Получение данных с шины
#define OutputData (uint8_t)(MDR_PORTA->RXTX & 0x3F) \
				   | (uint8_t)((MDR_PORTB->RXTX << 4) & 0xC0)

typedef enum
{
  NOT_SMOOTH,
  SMOOTH
} lcd_output_effect_t;

typedef enum
{
	NOT_INVERTED,
	INVERTED
} lcd_output_style_t;

void SetDataBits (uint8_t value);

void MltDelay (uint32_t value);
uint8_t ReadStatus (uint8_t Chip);

void DispOn (uint8_t Chip);
void DispOff (uint8_t Chip);
void LcdInit(void);


void SetPage (uint8_t Chip, uint8_t page);
void SetAddress (uint8_t Chip, uint8_t address);
void WriteData (uint8_t Chip, uint8_t data);
uint8_t ReadData (uint8_t Chip);

void LcdClearPage (uint8_t Chip, uint8_t Page);
void LcdClearChip (uint8_t Chip);

void LcdFullClear(void);
void LcdOnAndClear(void);

/*
** Описание: отображение символа на дисплей
** Параметры: array - представление символа в виде массива байтов
**			  Xpos - позиция символа на странице дисплея (надо учитывать размеры символов)
**			  Ypos - страница (строка) дисплея, куда надо вывести символ
**			  is_smooth - задает плавное отображение символа (слева направо)
**			  is_inverted - задает инвертированное отображение символа
** Возвращаемое значение: none
*/
void LcdPutChar (uint8_t* array,
				 int Xpos,
				 int Ypos,
				 lcd_output_effect_t is_smooth,
				 lcd_output_style_t is_inverted);
/*
** Описание: отображение строки на дисплей
** Параметры: array - указатели на массивы байтов (один указатель - один символ)
**			  Ypos - страница дисплея, куда надо вывести строку
** Возвращаемое значение: none
*/				 
void LcdPutString (uint8_t** array, int Ypos);

#endif