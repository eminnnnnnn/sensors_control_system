#include "auth.h"
#include <stdint.h>
#include "lcd_menu.h"
#include "mdr_delay.h"
#include "font.h"

void read_password_from_mem(void)
{
	// заглушка
	correct_password[0] = PASSW_DOWN;
	correct_password[1] = PASSW_UP;
	correct_password[2] = PASSW_LEFT;
	correct_password[3] = PASSW_LEFT;
	correct_password[4] = PASSW_DOWN;
}

auth_status_t try_login(const passw_t * user_password)
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

auth_status_t authenticate(void)
{
	passw_t user_passw[PASSWORD_LENGTH] = {PASSW_DEFAULT};
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
	return try_login(user_passw);
}

void reset_user_password(passw_t * user_password)
{
	uint8_t i;
	for (i = 0; i < PASSWORD_LENGTH; ++i)
	{
		user_password[i] = PASSW_DEFAULT;
	}
}
