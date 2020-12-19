#ifndef INIT_CONFIGS_H
#define INIT_CONFIGS_H

/*
typedef struct
{
    MDR_PORT_TypeDef * port_name;
    uint16_t port_pins;
} mdr_port;
*/

typedef enum
{
    INIT_SUCCESS,
    INIT_ERROR
} init_status_t;

/*
enum CPU_CLOCK_SRC
{
    HSE_SRC,
    LSE_SRC,
    LSI_SRC,
    HSI_SRC
}
*/

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*
** Описание: Начальная конфигурация частоты процессора. Источник сигнала: HSE
** Параметры: none
** Возвращаемое значение: результат настройки INIT_SUCCESS или INIT_ERROR
*/
init_status_t cpu_clock_init(void);

/*
** Описание: Начальная конфигурация портов для LCD дисплея
** // Параметры: ports - конфигурируемые порты, ports_count - количество портов
** Параметры: none
** Возвращаемое значение: результат настройки INIT_SUCCESS или INIT_ERROR
*/
// init_status_t lcd_ports_init(const mdr_port * ports, const uint8_t ports_count);
init_status_t lcd_ports_init(void);

/*
** Описание: Начальная конфигурация портов для 
** Параметры: none
** Возвращаемое значение: результат настройки INIT_SUCCESS или INIT_ERROR
*/
// init_status_t button_ports_init(const mdr_port * ports, uint8_t ports_count);
init_status_t button_ports_init(void);


#endif