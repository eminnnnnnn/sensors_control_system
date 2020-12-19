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
