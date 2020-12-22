#include "init_configs.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_port.h"

init_status_t cpu_clock_init(void)
{
    // Необходимая пауза для работы Flash-памяти программ
    MDR_EEPROM->CMD |= (0 << 3);

    MDR_RST_CLK->HS_CONTROL = 0x01; // вкл. HSE осцилятора (частота кварца 8 МГц)
    // ожидание выхода HSE в рабочий режим
    while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00);

    MDR_RST_CLK->CPU_CLOCK = ((2 << 0)      // источник для CPU_C1 - HSE
                            | (0 << 2)      // источник для CPU_C2 - CPU_C1
                            | (0 << 4)      // предделитель для CPU_C3 равен 1
                            | (1 << 8));    // источник для HCLK - CPU_C3

    // CPU_C1 = CPU_C2 = CPU_C3 = HCLK = 8 MHz
    return INIT_SUCCESS;
}

init_status_t lcd_ports_init(void)
{
	// Начальная конфигурация структуры для инициализации портов
	
    PORT_InitTypeDef PORT_InitStructure;
    PORT_StructInit(&PORT_InitStructure); // заполнение структуры значениями по умолчанию
	
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;    // режим работы - порт IO
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL; // тип сигнала - цифровой
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;   // скорость - быстрый фронт (~20нс)
	
	// Конфигурация выводов для управляющих сигналов
	
	/*
	** Порт: PORTB
    ** Выводы: PB7 - Chip 1 Select (E1), PB8 - Chip 2 Select (E2), PB9 - Reset (RES),
	**         PB10 - Read/Write (R/~W)
	** Направление сигнала: Все выводы на выход
    */
    PORT_InitStructure.PORT_Pin = (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10);
    PORT_InitStructure.PORT_OE  = PORT_OE_OUT;
    PORT_Init(MDR_PORTB, &PORT_InitStructure);

    /*
	** Порт: PORTC
	** Выводы: PC0 - Command/Data Select (A0), PC1 - Strobing (E)
    ** Направление сигнала: Все выводы на выход
	*/
    PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1);
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

	// Конфигурация выводов для обмена данными
	
    /* 
	** Порт: PORTA
	** Выводы: PA0 - PA5 -- Data Bus (DB0 - DB5)
    ** Направление сигнала: Двунаправленный, начальная конфигурация - на вход.
	**                      Направление будет меняться программно при чтении/записи
	**                      макросами в модуле mlt_lcd
	*/
    PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 \
                                   | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5);
    PORT_InitStructure.PORT_OE  = PORT_OE_IN;
    PORT_Init(MDR_PORTA, &PORT_InitStructure);
	
	/* 
	** Порт: PORTF
	** Выводы: PF2, PF3 - Data Bus(DB6, DB7)
    ** Направление сигнала: Двунаправленный, начальная конфигурация - на вход.
	**                      Направление будет меняться программно при чтении/записи
	**                      макросами в модуле mlt_lcd
	*/
    PORT_InitStructure.PORT_Pin = (PORT_Pin_2 | PORT_Pin_3);
    PORT_Init(MDR_PORTF, &PORT_InitStructure);
	
	return INIT_SUCCESS;
}

init_status_t button_ports_init(void)
{
	// Начальная конфигурация структуры для инициализации портов
	
    PORT_InitTypeDef PORT_InitStructure;
    PORT_StructInit(&PORT_InitStructure); // заполнение структуры значениями по умолчанию
	
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;    // режим работы - порт IO
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL; // тип сигнала - цифровой
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;   // скорость - быстрый фронт (~20нс)
	PORT_InitStructure.PORT_OE    = PORT_OE_IN;        // направление сигнала - на вход
	
	// Конфигурация выводов для кнопок
	
	/* 
	** Порт: PORTC
	** Выводы: PC2 - "SELECT" Button
	*/
	PORT_InitStructure.PORT_Pin = (PORT_Pin_2);
	PORT_Init(MDR_PORTC, &PORT_InitStructure);

	/* 
	** Порт: PORTB
	** Выводы: PB5 - "UP" Button, PB6 - "RIGHT" Button
	*/
	PORT_InitStructure.PORT_Pin = (PORT_Pin_5 | PORT_Pin_6);
	PORT_Init(MDR_PORTB, &PORT_InitStructure);

	/* 
	** Порт: PORTE
	** Выводы: PE1 - "DOWN" Button, PE3 - "LEFT" Button
	*/
	PORT_InitStructure.PORT_Pin = (PORT_Pin_1 | PORT_Pin_3);
	PORT_Init(MDR_PORTE, &PORT_InitStructure);
	
	return INIT_SUCCESS;
}

init_status_t dht_ports_init(void)
{
	// Начальная конфигурация структуры для инициализации портов

    PORT_InitTypeDef PORT_InitStructure;
    PORT_StructInit(&PORT_InitStructure); // заполнение структуры значениями по умолчанию

    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;    // режим работы - порт IO
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL; // тип сигнала - цифровой
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;   // скорость - быстрый фронт (~20нс)
	PORT_InitStructure.PORT_OE    = PORT_OE_OUT;       // направление сигнала - 
	                                                   // двунаправленный, начальная
	                                                   // конфигурация - на выход.
	PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_ON; // подтяжка вывода к питанию

	/*
	** Порт: PORTA
	** Выводы: PA6 - Data
	*/
	PORT_InitStructure.PORT_Pin = PORT_Pin_6;
	PORT_Init(MDR_PORTA, &PORT_InitStructure);
	PORT_SetBits(MDR_PORTA, PORT_Pin_6);
	return INIT_SUCCESS;
}