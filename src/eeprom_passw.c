#include "eeprom_passw.h"
#include "MDR32F9Qx_eeprom.h"           // Keil::Drivers:EEPROM

#define EEPROM_PAGE_SIZE (4*1024)
#define INFO_MEM_BASE_ADDRESS 0x08000000

void read_password_from_flash(unsigned int * password, unsigned int passw_length)
{
	unsigned int address = INFO_MEM_BASE_ADDRESS;
	unsigned int word_offset = 0;
	for (unsigned i = 0; i < passw_length; ++i)
	{
		password[i] = EEPROM_ReadWord(address + word_offset, EEPROM_Info_Bank_Select);
		word_offset += 4;
	}
}

void write_password_to_flash(unsigned int * password, unsigned int passw_length)
{
	unsigned int address = INFO_MEM_BASE_ADDRESS;
	// стирание страницы перед записью в сектор - обязательно
	EEPROM_ErasePage(address, EEPROM_Info_Bank_Select);
	
	unsigned int word_offset = 0;
	for (unsigned i = 0; i < passw_length; ++i)
	{
		// запись значений в сектор
		EEPROM_ProgramWord(address + word_offset, EEPROM_Info_Bank_Select, password[i]);
		word_offset += 4;
	}
}
