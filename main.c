#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

#include <stdint.h>

#include "lcd_menu.h"
#include "init_configs.h"
#include "mdr_delay.h"

int main(void)
{
	RST_CLK_DeInit();
	cpu_clock_init();
	RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA
					| RST_CLK_PCLK_PORTB
					| RST_CLK_PCLK_PORTE
					| RST_CLK_PCLK_PORTC,
					ENABLE
				   );
	
	lcd_ports_init();
	button_ports_init();

	LcdInit();
	LcdOnAndClear();
	
	uint8_t passw[4] = {1, 2, 3, 4};
	uint8_t user_passw[4] = {0, 0, 0, 0}; // 1 5 21 - сдвиги херня идея
	uint8_t is_auth = 0;
	
	while (is_auth == 0)
	{
		for (int i = 0; i < 4; ++i)
			user_passw[i] = 0;
		int i = 0;
		while (i < 4)
		{
			lcd_print_string("       ", 0, NOT_SMOOTH, NOT_INVERTED);
			if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_5) == Bit_RESET)
			{
				user_passw[i++] = 1;
				lcd_print_string("up", 0, NOT_SMOOTH, NOT_INVERTED);
			}
			else if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_6) == Bit_RESET)
			{
				user_passw[i++] = 2;
				lcd_print_string("right", 0, NOT_SMOOTH, NOT_INVERTED);
			}
			else if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_1) == Bit_RESET)
			{
				user_passw[i++] = 3;
				lcd_print_string("down", 0, NOT_SMOOTH, NOT_INVERTED);
			}
			else if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_3) == Bit_RESET)
			{
				user_passw[i++] = 4;
				lcd_print_string("left", 0, NOT_SMOOTH, NOT_INVERTED);
			}
			mdr_delay_ms(170);
		}
		for (i = 0; i < 4; ++i)
		{
			if (user_passw[i] != passw[i])
			{
				lcd_print_string("try again", 0, NOT_SMOOTH, NOT_INVERTED);
				mdr_delay_ms(5000);
				lcd_print_string("         ", 0, NOT_SMOOTH, NOT_INVERTED);
				is_auth = 0;
				break;
			}
		}
		if (i == 4)
			is_auth = 1;
	}
	lcd_print_string("success", 0, NOT_SMOOTH, NOT_INVERTED);
	mdr_delay_ms(5000);
	menu_rows_t menu_cursor = ROW_0;
	lcd_menu_init();
	while(1){
		if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_5) == Bit_RESET)
		{
			lcd_menu_handler(&menu_cursor, MENU_UP);
		}
		else if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_1) == Bit_RESET)
		{
			lcd_menu_handler(&menu_cursor, MENU_DOWN);
		}

		mdr_delay_ms(150);
	}
	return 0;
}
