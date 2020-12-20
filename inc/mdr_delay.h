#ifndef MDR_DELAY_H
#define MDR_DELAY_H

/*
** В этом модуле описаны подпрограммы задержки
*/

#include <stdint.h>

/*
** Описание: Задержка в миллисекундах
** Параметры: delay_time - время задержки в миллисекундах
** Возвращаемое значение: none
*/
void mdr_delay_ms(uint32_t delay_time);

/*
** Описание: Задержка в микросекундах
** Параметры: delay_time - время задержки в микросекундах
** Возвращаемое значение: none
*/
void mdr_delay_us(uint32_t delay_time);

#endif