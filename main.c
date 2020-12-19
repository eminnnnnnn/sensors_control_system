#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

#include <stdint.h>

#include "font.h"
#include "lcd_menu.h"
#include "init_configs.h"
#include "mdr_delay.h"
#include "auth.h"

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
	
	lcd_print_string("  Press SELECT", 3, NOT_SMOOTH, NOT_INVERTED);
	lcd_print_string("   to log in", 4, NOT_SMOOTH, NOT_INVERTED);
	while (PORT_ReadInputDataBit(MDR_PORTC, PORT_Pin_2) == Bit_SET);
	lcd_print_string("              ", 3, NOT_SMOOTH, NOT_INVERTED);
	lcd_print_string("            ", 4, NOT_SMOOTH, NOT_INVERTED);
	
	auth_status_t is_auth = AUTH_FAIL;
	read_password_from_mem();
	while (is_auth == AUTH_FAIL)
	{
		lcd_show_auth_arrows();
		is_auth = authenticate();
		if (is_auth == AUTH_FAIL)
		{
			lcd_hide_auth_arrows();
			// LcdPutChar(sym_sp, UP_ARROW_X, UP_ARROW_Y, NOT_SMOOTH, NOT_INVERTED);
			lcd_print_string("   INCORRECT!", 3, NOT_SMOOTH, NOT_INVERTED);
			lcd_print_string("   TRY AGAIN", 4, NOT_SMOOTH, NOT_INVERTED);
			mdr_delay_ms(2000);
			lcd_print_string("             ", 3, NOT_SMOOTH, NOT_INVERTED);
			lcd_print_string("            ", 4, NOT_SMOOTH, NOT_INVERTED);
		}
	}
	lcd_hide_auth_arrows();
	lcd_print_string("    SUCCESS!", 3, NOT_SMOOTH, NOT_INVERTED);
	mdr_delay_ms(2000);
	lcd_print_string("            ", 3, NOT_SMOOTH, NOT_INVERTED);
	
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
