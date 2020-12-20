#include "rtc.h"
#include "MDR32F9Qx_bkp.h"

#define PRESC_VALUE_LS LSE_Value
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define COUNT_VALUE 86220
#define ALARM_VALUE 86400 // = SECONDS_PER_MINUTE * MINUTES_PER_HOUR * HOURS_PER_DAY

void rtc_init(void)
{
	BKP_RTC_Reset(ENABLE); // сброс блока RTC
	BKP_RTC_Reset(DISABLE);

	// BKP_DeInit();
	// MDR_BKP->REG_0E &= ~BKP_REG_0E_JTAGB;

	// частота - до 25 МГц, значение стабилизирующей нагрузки - ~6кОм
	// эти значения должны совпадать
	MDR_BKP->REG_0E &= ~(BKP_REG_0E_LOW_Msk | BKP_REG_0E_SELECTRI_Msk); 
	BKP_RTC_WaitForUpdate(); // ожидание окончания записи в регистры RTC
	MDR_BKP->REG_0F |= BKP_REG_0F_LSE_ON; // включение генератора LSE
	BKP_RTC_WaitForUpdate();
	while ((MDR_BKP->REG_0F & BKP_REG_0F_LSE_RDY) == 0); // ожидание готовности LSE
	BKP_RTCclkSource(BKP_RTC_LSEclk); // источник тактовой синхронизации ЧРВ - LSE
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetCounter(COUNT_VALUE); // значение счетчика
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetPrescaler(PRESC_VALUE_LS); // делитель частоты (для получения частоты 1 Гц)
	BKP_RTC_WaitForUpdate();
	// BKP_RTC_SetAlarm(ALARM_VALUE);
	// BKP_RTC_WaitForUpdate();
	BKP_RTC_Enable(ENABLE);	// разрешение работы RTC
}

uint32_t get_sec(void)
{
	return (MDR_BKP->RTC_CNT % ALARM_VALUE); // секунды, прошедшие за текущий день
}
