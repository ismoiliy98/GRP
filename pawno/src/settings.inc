#define SERVER_NAME "Geebrox" //Название сервера
#define SERVER_MODE "Role Play" //Мод сервера
#define SERVER_LANGUAGE "Russian" //Язык сервера
#define SERVER_WEBSITE "null" //Сайт/Форум сервера


#define COLOR_TITLE "{3498db}" //Цвет используемый для заголовок
#define COLOR_TEXT "{ecf0f1}" //Цвет используемый для обычных информаций
#define COLOR_NOTE "{e67e22}" //Цвет используемый для подчеркиваний важдных слов
#define COLOR_ERROR "{c0392b}" //Цвет используемый при ощибке
#define COLOR_SUCCESS "{2ecc71}" //Цвет используемый при успехе

#define HEX_COLOR_TITLE 0x3498dbFF
#define HEX_COLOR_TEXT 0xecf0f1FF
#define HEX_COLOR_NOTE 0xe67e22FF
#define HEX_COLOR_ERROR 0xc0392bFF
#define HEX_COLOR_SUCCESS 0x2ecc71FF


#define MAX_HASH_SIZE 65

//Настройка комманд
enum
{
	CMD_RTN_INVALID_COMMAND = -1,
	CMD_RTN_SUCCESS,
	CMD_RTN_ERROR,
	CMD_RTN_NO_PERMISSIONS,
	CMD_RTN_INVALID_PLAYER_ID
}