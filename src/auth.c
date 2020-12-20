#include "auth.h"
#include "lcd_menu.h"
#include "mdr_delay.h"
#include "font.h"
#include "eeprom_passw.h"

//////////////////////////////////////////////////////////////////////////////////////////
/* ------------------------ PRIVATE FUNCTION DEFINITIONS ------------------------------ */
//////////////////////////////////////////////////////////////////////////////////////////

static uint8_t is_password_combination(uint32_t * combination)
{
	for (uint8_t i = 0; i < PASSWORD_LENGTH; ++i)
	{
		if ((combination[i] > (PASSW_DIRECTIONS_COUNT - 1))
			||((passw_t)combination[i] == PASSW_DEFAULT)) // ?
		{
			return 0;
		}
	}
	return 1;
}

static uint8_t is_password_symbol(uint32_t symbol)
{
	return (symbol < (PASSW_DIRECTIONS_COUNT - 1))? 1 : 0;
}

static auth_status_t try_login(const passw_t * user_password)
{
	if (user_password == 0)
		return AUTH_FAIL;
	
	uint8_t i;
	for (i = 0; i < PASSWORD_LENGTH; ++i)
	{
		if (user_password[i] != correct_password[i])
		{
			return AUTH_FAIL;
		}
	}
	return AUTH_SUCCESS;
}

static void change_password(const passw_t * user_password)
{
	uint32_t tmp[PASSWORD_LENGTH] = {0};
	for (uint8_t i = 0; i < PASSWORD_LENGTH; ++i)
	{
		correct_password[i] = user_password[i];
		tmp[i] = (uint32_t)user_password[i];
	}
	write_password_to_flash(tmp, PASSWORD_LENGTH);
}

/*
void reset_user_password(passw_t * user_password)
{
	uint8_t i;
	for (i = 0; i < PASSWORD_LENGTH; ++i)
	{
		user_password[i] = PASSW_DEFAULT;
	}
}
*/

//////////////////////////////////////////////////////////////////////////////////////////
/* ----------------------- PUBLIC FUNCTION DEFINITIONS -------------------------------- */
//////////////////////////////////////////////////////////////////////////////////////////

void run_login(void)
{
	lcd_print_string("  Press SELECT", 3, NOT_SMOOTH, NOT_INVERTED);
	lcd_print_string("   to log in", 4, NOT_SMOOTH, NOT_INVERTED);
	while (PORT_ReadInputDataBit(MDR_PORTC, PORT_Pin_2) == Bit_SET);
	lcd_print_string("              ", 3, NOT_SMOOTH, NOT_INVERTED);
	lcd_print_string("            ", 4, NOT_SMOOTH, NOT_INVERTED);

	auth_status_t is_auth = AUTH_FAIL;
	if (is_password_defined() == PASSWORD_UNDEFINED)
	{
		lcd_print_string("DEFINE PASSWORD", 3, NOT_SMOOTH, NOT_INVERTED);
		mdr_delay_ms(2000);
		lcd_print_string("               ", 3, NOT_SMOOTH, NOT_INVERTED);
		lcd_show_auth_arrows();
		input_new_password();
	}
	else
	{
		while (is_auth == AUTH_FAIL)
		{
			lcd_show_auth_arrows();
			is_auth = authenticate();
			if (is_auth == AUTH_FAIL)
			{
				lcd_hide_auth_arrows();
				lcd_print_string("   INCORRECT!", 3, NOT_SMOOTH, NOT_INVERTED);
				lcd_print_string("   TRY AGAIN", 4, NOT_SMOOTH, NOT_INVERTED);
				mdr_delay_ms(2000);
				lcd_print_string("             ", 3, NOT_SMOOTH, NOT_INVERTED);
				lcd_print_string("            ", 4, NOT_SMOOTH, NOT_INVERTED);
			}
		}
	}
	lcd_hide_auth_arrows();
	lcd_print_string("    SUCCESS!", 3, NOT_SMOOTH, NOT_INVERTED);
	mdr_delay_ms(2000);
	lcd_print_string("            ", 3, NOT_SMOOTH, NOT_INVERTED);
}

void read_password_from_mem(void)
{
	uint32_t tmp[PASSWORD_LENGTH] = {0};
	read_password_from_flash(tmp, PASSWORD_LENGTH);

	if (is_password_combination(tmp))
	{
		for (uint8_t i = 0; i < PASSWORD_LENGTH; ++i)
		{
			correct_password[i] = (passw_t)tmp[i];
		}
	}
}


auth_status_t authenticate(void)
{
	passw_t user_passw[PASSWORD_LENGTH] = {PASSW_DEFAULT};
	input_password(user_passw);
	return try_login(user_passw);
}

passw_state_t is_password_defined(void)
{
	return (correct_password[0] == PASSW_DEFAULT)? PASSWORD_UNDEFINED : PASSWORD_DEFINED;
}

void input_new_password(void)
{
	passw_t user_passw[PASSWORD_LENGTH] = {PASSW_DEFAULT};
	input_password(user_passw);
	change_password(user_passw);
}

void input_password(passw_t * user_passw)
{
	uint8_t i = 0;

	while (i < PASSWORD_LENGTH)
	{
		mdr_delay_ms(170);
		if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_5) == Bit_RESET)
		{
			user_passw[i++] = PASSW_UP;
			LcdPutChar(sym_arrow_up, UP_ARROW_X, UP_ARROW_Y, NOT_SMOOTH, INVERTED);
			mdr_delay_ms(170);
			LcdPutChar(sym_arrow_up, UP_ARROW_X, UP_ARROW_Y, NOT_SMOOTH, NOT_INVERTED);
		}
		else if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_6) == Bit_RESET)
		{
			user_passw[i++] = PASSW_RIGHT;
			LcdPutChar(sym_arrow_right, RIGHT_ARROW_X, RIGHT_ARROW_Y, NOT_SMOOTH, INVERTED);
			mdr_delay_ms(170);
			LcdPutChar(sym_arrow_right, RIGHT_ARROW_X, RIGHT_ARROW_Y, NOT_SMOOTH, NOT_INVERTED);
		}
		else if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_1) == Bit_RESET)
		{
			user_passw[i++] = PASSW_DOWN;
			LcdPutChar(sym_arrow_down, DOWN_ARROW_X, DOWN_ARROW_Y, NOT_SMOOTH, INVERTED);
			mdr_delay_ms(170);
			LcdPutChar(sym_arrow_down, DOWN_ARROW_X, DOWN_ARROW_Y, NOT_SMOOTH, NOT_INVERTED);
		}
		else if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_3) == Bit_RESET)
		{
			user_passw[i++] = PASSW_LEFT;
			LcdPutChar(sym_arrow_left, LEFT_ARROW_X, LEFT_ARROW_Y, NOT_SMOOTH, INVERTED);
			mdr_delay_ms(170);
			LcdPutChar(sym_arrow_left, LEFT_ARROW_X, LEFT_ARROW_Y, NOT_SMOOTH, NOT_INVERTED);
		}
	}
}
