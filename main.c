#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

#include <stdint.h>

#include "font.h"
#include "lcd_menu.h"
#include "init_configs.h"
#include "mdr_delay.h"
#include "auth.h"
#include "rtc.h"

int main(void)
{
	// RST_CLK_DeInit(); // функция меняет регистры батарейного домена BKP!!!
	cpu_clock_init();
	// SystemCoreClockUpdate();
	RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA
					| RST_CLK_PCLK_PORTB
					| RST_CLK_PCLK_PORTE
					| RST_CLK_PCLK_PORTC,
					ENABLE
				   );
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
	
	lcd_ports_init();
	button_ports_init();
	dht_ports_init();
	
	/*
	** RTC initialization in main function in first programming of memory,
	** in second programming initialization should be removed (temporary solution)
	*/
	// rtc_init();
	
	LcdInit();
	LcdOnAndClear();
	
	read_password_from_mem();
	run_login();

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
		else if (PORT_ReadInputDataBit(MDR_PORTC, PORT_Pin_2) == Bit_RESET)
		{
			lcd_menu_handler(&menu_cursor, MENU_SELECT);
		}

		mdr_delay_ms(150);
	}
	return 0;
}
