#include "mdr_delay.h"
#include "MDR32Fx.h"

// #define CPU_FREQUENCY_HZ SystemCoreClock
#define CPU_FREQUENCY_HZ 8000000 // => Время такта равно 1/8МГц = 0.125 мкс
#define CLOCK_CYCLES_PER_WHILE_CYCLE 3 // Число тактов на один while цикл

#define CLOCK_CYCLES_PER_ONE_MS 8000 // Число тактов за 1 мс при частоте 8 МГц: Fcpu*1ms
// #define MS_MULTIPLIER (CLOCK_CYCLES_PER_ONE_MS/CLOCK_CYCLES_PER_WHILE_CYCLE + 1)
#define MS_MULTIPLIER 2667 // Число тактов за 1 мс для цикла while
#define MAX_VALUE_FOR_MS_DELAY 1610400 // = UINT32_MAX / MS_MULTIPLIER

#define CLOCK_CYCLES_PER_ONE_US 8 // Число тактов за 1 мкс при частоте 8 МГц: Fcpu*1us
#define US_MULTIPLIER 3 // Число тактов за 1 мкс для цикла while
#define MAX_VALUE_FOR_US_DELAY 1431655765 // = UINT32_MAX / US_MULTIPLIER

void mdr_delay_ms(uint32_t delay_time)
{
	if (delay_time > MAX_VALUE_FOR_MS_DELAY)
		return;

	delay_time *= MS_MULTIPLIER;
	while (delay_time--){ __NOP(); }
}

void mdr_delay_us(uint32_t delay_time)
{
	if (delay_time > MAX_VALUE_FOR_US_DELAY)
		return;
	delay_time *= US_MULTIPLIER;
	while (delay_time--){ __NOP(); }
}
