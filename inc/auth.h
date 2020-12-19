#ifndef AUTH_H
#define AUTH_H

#define PASSWORD_LENGTH 5
// один раз считать пароль из памяти
typedef enum
{
	PASSW_DEFAULT,
	PASSW_UP,
	PASSW_RIGHT,
	PASSW_DOWN,
	PASSW_LEFT
} passw_t;

typedef enum
{
	AUTH_SUCCESS,
	AUTH_FAIL
} auth_status_t;

static passw_t correct_password[PASSWORD_LENGTH] = {PASSW_DEFAULT};

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
** Описание: проверка введенного пароля
** Параметры: user_password - введенный пароль
** Возвращаемое значение: AUTH_SUCCESS, если введенный пароль верный, иначе - AUTH_FAIL
*/
auth_status_t try_login(const passw_t * user_password);

/*
** Описание: сброс введенного пароля
** Параметры: user_password - введенный пароль
** Возвращаемое значение: none
*/
void reset_user_password(passw_t * user_password);

#endif