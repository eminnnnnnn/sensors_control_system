#include "sensors.h"
#include "mdr_delay.h"
#include "MDR32F9Qx_port.h"

#define START_CONDITION_MS 18
#define RESPONSE_WAIT_US 40 // 20 - 40 мкс
#define RESPONSE_LOW_US 80
#define RESPONSE_HIGH_US 80
#define DATA_BIT_START_US 50
#define ZERO_BIT_US 28 // 26 - 28 мкс
#define ONE_BIT_US 70

dht11_status_t dht11_send_start(void)
{
	uint8_t retries;
	
	mdr_delay_ms(1000);
	PORT_ResetBits(DHT11_DATA_PORT, DHT11_DATA_PIN);
	mdr_delay_ms(START_CONDITION_MS);
	PORT_SetBits(DHT11_DATA_PORT, DHT11_DATA_PIN);
	
	DHT11_DATA_PORT->OE &= ~DHT11_DATA_PIN;
	
	retries = 0;
	while(PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_SET)
	{
		if (retries > (RESPONSE_WAIT_US / 2))
		{
			return DHT11_TIMEOUT;
		}
		mdr_delay_us(2);
		retries += 2;
	}
	
	retries = 0;
	while(PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_RESET)
	{
		if (retries > (RESPONSE_LOW_US / 2))
		{
			return DHT11_TIMEOUT;
		}
		mdr_delay_us(2);
		retries += 2;
	}
	retries = 0;
	while(PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_SET)
	{
		if (retries > (RESPONSE_HIGH_US / 2))
		{
			return DHT11_TIMEOUT;
		}
		mdr_delay_us(2);
		retries += 2;
	}
	return DHT11_SUCCESS;
}

dht11_status_t dht11_read_data(uint8_t * out_data)
{
	uint8_t buff[DHT11_DATA_BYTES_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t retries = 0;
	uint8_t i;
	int8_t j;
	for (i = 0; i < DHT11_DATA_BYTES_SIZE; ++i)
	{
		for (j = 7; j >= 0; j--)
		{
			retries = 0;
			while(PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_RESET)
			{
				if (retries > (DATA_BIT_START_US / 2))
				{
					return DHT11_TIMEOUT;
				}
				mdr_delay_us(2);
				retries += 2;
			}
			
			mdr_delay_us(ZERO_BIT_US + 3);
			if (PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_SET)
				buff[i] |= (1 << j);
			
			retries = 0;
			while(PORT_ReadInputDataBit(DHT11_DATA_PORT, DHT11_DATA_PIN) == Bit_SET)
			{
				if (retries > ((ONE_BIT_US - 3)/2))
				{
					return DHT11_TIMEOUT;
				}
				mdr_delay_us(2);
				retries += 2;
			}
		}
	}
	DHT11_DATA_PORT->OE |= DHT11_DATA_PIN;
	if ((uint8_t)(buff[0] + buff[1] + buff[2] + buff[3]) != buff[4])
	{
		return DHT11_INCORRECT_DATA;
	}
	else
	{
		for (i = 0; i < (DHT11_DATA_BYTES_SIZE - 1); ++i)
			out_data[i] = buff[i];
		return DHT11_SUCCESS;
	}
}