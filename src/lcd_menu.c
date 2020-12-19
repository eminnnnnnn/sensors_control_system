#include "lcd_menu.h"

/* ------------------------ PRIVATE FUNCTION DEFINITIONS ------------------------------ */

uint8_t * get_symbol_array_for_LCD(const char symbol)
{
	switch(symbol)
	{
		case 'a': return lat_a;
		case 'b': return lat_b;
		case 'c': return lat_c;
		case 'd': return lat_d;
		case 'e': return lat_e;
		case 'f': return lat_f;
		case 'g': return lat_g;
		case 'h': return lat_h;
		case 'i': return lat_i;
		case 'j': return lat_j;
		case 'k': return lat_k;
		case 'l': return lat_l;
		case 'm': return lat_m;
		case 'n': return lat_n;
		case 'o': return lat_o;
		case 'p': return lat_p;
		case 'q': return lat_q;
		case 'r': return lat_r;
		case 's': return lat_s;
		case 't': return lat_t;
		case 'u': return lat_u;
		case 'v': return lat_v;
		case 'w': return lat_w;
		case 'x': return lat_x;
		case 'y': return lat_y;
		case 'z': return lat_z;

		case 'A': return lat_A;
		case 'B': return lat_B;
		case 'C': return lat_C;
		case 'D': return lat_D;
		case 'E': return lat_E;
		case 'F': return lat_F;
		case 'G': return lat_G;
		case 'H': return lat_H;
		case 'I': return lat_I;
		case 'J': return lat_J;
		case 'K': return lat_K;
		case 'L': return lat_L;
		case 'M': return lat_M;
		case 'N': return lat_N;
		case 'O': return lat_O;
		case 'P': return lat_P;
		case 'Q': return lat_Q;
		case 'R': return lat_R;
		case 'S': return lat_S;
		case 'T': return lat_T;
		case 'U': return lat_U;
		case 'V': return lat_V;
		case 'W': return lat_W;
		case 'X': return lat_X;
		case 'Y': return lat_Y;
		case 'Z': return lat_Z;

		case '0': return dig_0;
		case '1': return dig_1;
		case '2': return dig_2;
		case '3': return dig_3;
		case '4': return dig_4;
		case '5': return dig_5;
		case '6': return dig_6;
		case '7': return dig_7;
		case '8': return dig_8;
		case '9': return dig_9;

		case '.': return sym_pt;
		case '<': return sym_cursor;
		case '%': return sym_percent;
		case ' ': return sym_sp;

		default: return sym_sp;
	}
}

/* ----------------------- PUBLIC FUNCTION DEFINITIONS -------------------------------- */

int lcd_print_string(const char * str,
					 int y_pos,
					 lcd_output_effect_t is_smooth,
					 lcd_output_style_t is_inverted
					)
{
	if (!str || y_pos > (LCD_CHIP_PAGES - 1))
		return -1;

	const char * str_ptr = str;
	int x_pos = 0;

	// отображение на дисплей символов строки
	for (; (*(str_ptr) != 0x00) && (x_pos < LCD_MAX_STRING_SIZE); str_ptr++)
	{
		LcdPutChar(get_symbol_array_for_LCD(*str_ptr),
				   x_pos++,
				   y_pos,
				   is_smooth,
				   is_inverted
				  );
	}
	
	// рекурсивный вызов функции для переноса оставшихся символов на следующую строку
	if (*(str_ptr) != 0x00)
	{
		return lcd_print_string(str_ptr, y_pos + 1, is_smooth, is_inverted);
	}
	
	return y_pos;
}

void lcd_menu_init(void)
{
	// по умолчанию курсор на первом пункте меню, он отображается инвертированным
	lcd_print_string(MENU_ROWS_NAMES[0], 0, NOT_SMOOTH, INVERTED);
	for (int i = 1; i < MENU_ROWS_COUNT; ++i)
	{
		lcd_print_string(MENU_ROWS_NAMES[i], i, NOT_SMOOTH, NOT_INVERTED);
	}
}

void lcd_menu_handler(menu_rows_t * cursor, menu_action_t action)
{	
	if (action == MENU_SELECT)
	{
		return;
	}
	menu_rows_t prev_row = *cursor; // сохранение текущей позиции курсора
	
	// сначала проверка граничных значений
	if ((*cursor == ROW_0) && (action == MENU_UP))
	{
		*cursor = MENU_ROWS_COUNT - 1; // перемещение курсора на последний пункт
	}
	else if ((*cursor == (MENU_ROWS_COUNT - 1)) && (action == MENU_DOWN))
	{
		*cursor = ROW_0; // перемещение курсора на первый пункт
	}
	else
	{
		// перемещение курсора в соответствии с действием
		*cursor = (menu_rows_t)((int)(*cursor) + (int)(action));
	}

	lcd_print_string(MENU_ROWS_NAMES[(*cursor)], (*cursor), NOT_SMOOTH, INVERTED);
	lcd_print_string(MENU_ROWS_NAMES[prev_row], prev_row, NOT_SMOOTH, NOT_INVERTED);
}
