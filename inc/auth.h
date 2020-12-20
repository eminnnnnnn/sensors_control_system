#ifndef AUTH_H
#define AUTH_H

#include <stdint.h>

#define PASSWORD_LENGTH 5

typedef enum
{
	PASSW_DEFAULT,
	PASSW_UP,
	PASSW_RIGHT,
	PASSW_DOWN,
	PASSW_LEFT,
	PASSW_DIRECTIONS_COUNT
} passw_t;

typedef enum
{
	AUTH_SUCCESS,
	AUTH_FAIL
} auth_status_t;

typedef enum
{
	PASSWORD_DEFINED,
	PASSWORD_UNDEFINED
} passw_state_t;

//////////////////////////////////////////////////////////////////////////////////////////
/* ----------------------------- PRIVATE VARIABLES -------------------------------------*/
//////////////////////////////////////////////////////////////////////////////////////////

static passw_t correct_password[PASSWORD_LENGTH] = {PASSW_DEFAULT};

//////////////////////////////////////////////////////////////////////////////////////////
/* ------------------------ PRIVATE FUNCTION PROTOTYPES ------------------------------- */
//////////////////////////////////////////////////////////////////////////////////////////

/*
** Описание: проверка комбинации на отсутствие недопустимых значений
** Параметры: combination - массив чисел для проверки
** Возвращаемое значение: 1, если комбинация корректная, иначе 0
*/
static uint8_t is_password_combination(uint32_t * combination);

/*
** Описание: проверка числа на возможность преобразования в тип passw_t
** Параметры: symbol - число
** Возвращаемое значение: 1, если преобразование возможно, иначе 0
*/
static uint8_t is_password_symbol(uint32_t symbol);

/*
** Описание: проверка введенного пароля
** Параметры: user_password - введенный пароль
** Возвращаемое значение: AUTH_SUCCESS, если введенный пароль верный, иначе - AUTH_FAIL
*/
static auth_status_t try_login(const passw_t * user_password);

/*
** Описание: изменение пароля
** Параметры: user_password - новый пароль
** Возвращаемое значение: none
*/
static void change_password(const passw_t * user_password);

/*
** Описание: сброс введенного пароля
** Параметры: user_password - введенный пароль
** Возвращаемое значение: none
*/
// static void reset_user_password(passw_t * user_password);

//////////////////////////////////////////////////////////////////////////////////////////
/* ------------------------ PUBLIC FUNCTION PROTOTYPES -------------------------------- */
//////////////////////////////////////////////////////////////////////////////////////////

/*
** Описание: чтение пароля из памяти и запись в correct_password
** Параметры: none
** Возвращаемое значение: none
*/
void read_password_from_mem(void);

/*
** Описание: ввод пароля с кнопок и проверка
** Параметры: none
** Возвращаемое значение: AUTH_SUCCESS, если введенный пароль верный, иначе - AUTH_FAIL
*/
auth_status_t authenticate(void);

/*
** Описание: проверка считанного из памяти пароля
** Параметры: none
** Возвращаемое значение: PASSWORD_DEFINE, если пароль задан, иначе PASSWORD_UNDEFINED
*/
passw_state_t is_password_defined(void);

/*
** Описание: ввод нового пароля
** Параметры: none
** Возвращаемое значение: none
*/
void input_new_password(void);

#endif