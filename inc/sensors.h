#ifndef SENSORS_H
#define SENSORS_H

/*
** В этом модуле описаны интерфейсы для связи с датчиками
*/

#include <stdint.h>

/*
**                 ПРОТОКОЛ ПЕРЕДАЧИ ДАННЫХ ДЛЯ ДАТЧИКА DHT11
**
**               20-49us         80us     "0"(26-28us)  "1"(70us)
** ---+          +-----+       +-------+     +----+     +-------+
**    +----------+     +-------+       +-----+    +-----+       +--- ....
**        18ms            80us           50us       50us
** |-------------------|---------------|---------------------------------|
**    МК инициирует     DHT11 отвечает  DHT11 передает 40 битов данных
**    чтение (Start)     (Acknowledge)           (Data Transfer)
**
** Формат данных:  8 бит целая часть значения влажности +
**               + 8 бит десятичная часть значения влажности +
**               + 8 бит целая часть значения температуры +
**               + 8 бит десятичная часть значения температуры +
**               + 8 бит контрольная сумма
*/

#define DHT11_DATA_PORT MDR_PORTC
#define DHT11_DATA_PIN PORT_Pin_0
#define DHT11_DATA_BYTES_SIZE 5
#define DHT11_HUM_INT_BYTE 0
#define DHT11_HUM_DEC_BYTE 1
#define DHT11_TEMP_INT_BYTE 2
#define DHT11_TEMP_DEC_BYTE 3

typedef enum
{
	DHT11_SUCCESS,
	DHT11_TIMEOUT,
	DHT11_INCORRECT_DATA
} dht11_status_t;


/*
** Описание: уведомление о начале передачи данных
** Параметры: none
** Возвращаемое значение: DHT11_SUCCESS, если ответ получен, иначе DHT11_TIMEOUT 
*/
dht11_status_t dht11_send_start(void);

/*
** Описание: чтение данных с датчика
** Параметры: out_data - массив для заполнения
** Возвращаемое значение: DHT11_SUCCESS, если ответ получен, иначе DHT11_TIMEOUT  
*/
dht11_status_t dht11_read_data(uint8_t * out_data);

#endif