#ifndef EEPROM_PASSW_H
#define EEPROM_PASSW_H

/*
** В этом модуле описаны подпрограммы для чтения и записи памяти EEPROM
*/

/*
** Описание: чтение пароля из информационной области данных памяти EEPROM
** Параметры: password - массив для записи считанных данных,
**            passw_length - длина пароля
** Возвращаемое значение: none
*/
void read_password_from_flash(unsigned int * password, unsigned int passw_length);

/*
** Описание: запись пароля в информационную область данных памяти EEPROM
** Параметры: password - пароль (массив),
**            passw_length - длина пароля
** Возвращаемое значение: none
*/
void write_password_to_flash(unsigned int * password, unsigned int passw_length);

#endif