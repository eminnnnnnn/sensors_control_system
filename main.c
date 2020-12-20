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
	cpu_clock_init(); // инициализация тактовой частоты для CPU
	// SystemCoreClockUpdate();
	RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK, ENABLE);	// разрешение тактирования RST_CLK
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA				// разрешение тактирования порта А
					| RST_CLK_PCLK_PORTB			//  порта B
					| RST_CLK_PCLK_PORTE			//   порта Е
					| RST_CLK_PCLK_PORTC,			//    порта С
					ENABLE
				   );
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE); // разрешение тактирования блока EEPROM
	
	lcd_ports_init();		// настройка выводов портов для LCD
	button_ports_init();	// настройка выводов портов для кнопок
	dht_ports_init();		// настройка выводов портов для датчика DHT11
	
	/*
	** RTC initialization in main function in first programming of memory,
	** in second programming initialization should be removed (temporary solution)
	*/
	// rtc_init();
	
	LcdInit();			// инициализация LCD
	LcdOnAndClear();	// включение дисплея и "очистка"
	
	read_password_from_mem();	// чтение правильного пароля из памяти (однократно)
	run_login();				// процедура авторизации

	menu_rows_t menu_cursor = ROW_0; // курсор для навигации в меню
	lcd_menu_init();				 // отображение меню
	// цикл опроса кнопок "вверх", "вниз" и "выбрать" и обработки нажатий
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

		mdr_delay_ms(150); // задержка для подавления дребезга
	}
	return 0;
}
