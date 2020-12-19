#ifndef LCD_MENU_H
#define LCD_MENU_H

/*
** В этом модуле описан интерфейс для взаимодействия с меню на дисплее
*/

#include <stdint.h>

#include "mlt_lcd.h"
#include "font.h"

typedef enum
{
	ROW_0,
	ROW_1,
	ROW_2,
	ROW_3,
	MENU_ROWS_COUNT
} menu_rows_t;

typedef enum
{
	MENU_UP = -1,
	MENU_DOWN = 1,
	MENU_SELECT = 2
} menu_action_t;

typedef enum
{
	CURSOR_UP,
	CURSOR_RIGHT,
	CURSOR_DOWN,
	CURSOR_LEFT
} cursor_action_t;

/* ----------------------------- PRIVATE VARIABLES -------------------------------------*/

// Названия пунктов меню
static const char * MENU_ROWS_NAMES[] = {"Temperat", "Humidity", "Block", "New Code"};

/* ------------------------ PRIVATE FUNCTION PROTOTYPES ------------------------------- */

// static uint8_t * get_symbol_array_for_LCD(const char * );

/* ------------------------ PUBLIC FUNCTION PROTOTYPES -------------------------------- */

/*
** Описание: Получение массива байтов для отображения символа на дисплей
** Параметры: symb - символ, который нужно отобразить на LCD
** Возвращаемое значение: массив байтов (если для символа нет соответствующего массива,
**					      то вернется массив для символа "пробел")
*/
uint8_t * get_symbol_array_for_LCD(const char symb);

/*
** Описание: Отображение строки на дисплей
** Параметры: str - указатель на строку,
** 			  y_pos - номер строки (страницы) дисплея, в которую надо отобразить символы,
**		      is_smooth - задает плавное отображение символов,
**			  is_inverted - задает инвертированное отображение символов (черный на белый
**			  			    и наоборот) для пункта меню
** Возвращаемое значение: в случае корректного выполнения - последняя строка (страница) 
**						  дисплея, куда вывелись символы,
**                        иначе вернется -1
*/
int lcd_print_string(const char * str,
					 int y_pos,
					 lcd_output_effect_t is_smooth,
					 lcd_output_style_t is_inverted
					);

/*
** Описание: отображение меню на дисплей
** Параметры: none
** Возвращаемое значение: none
*/
void lcd_menu_init(void);

/*
** Описание: обработчик курсора меню
** Параметры: cursor - указатель на курсор,
**			  action - действие, которое необходимо обработать (вверх, вниз, выбор)
** Возвращаемое значение: none 
*/
void lcd_menu_handler(menu_rows_t * cursor, menu_action_t action);

#endif