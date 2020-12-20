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
	BKP_RTC_Reset(ENABLE);
	BKP_RTC_Reset(DISABLE);

	// BKP_DeInit();
	// MDR_BKP->REG_0E &= ~BKP_REG_0E_JTAGB;
	MDR_BKP->REG_0E &= ~(BKP_REG_0E_LOW_Msk | BKP_REG_0E_SELECTRI_Msk);
	BKP_RTC_WaitForUpdate();
	MDR_BKP->REG_0F |= BKP_REG_0F_LSE_ON;
	BKP_RTC_WaitForUpdate();
	while ((MDR_BKP->REG_0F & BKP_REG_0F_LSE_RDY) == 0);
	BKP_RTCclkSource(BKP_RTC_LSEclk);
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetCounter(COUNT_VALUE);
	BKP_RTC_WaitForUpdate();
	BKP_RTC_SetPrescaler(PRESC_VALUE_LS);
	BKP_RTC_WaitForUpdate();
	// BKP_RTC_SetAlarm(ALARM_VALUE);
	// BKP_RTC_WaitForUpdate();
	BKP_RTC_Enable(ENABLE);
}

uint32_t get_sec(void)
{
	return (MDR_BKP->RTC_CNT % ALARM_VALUE);
}
