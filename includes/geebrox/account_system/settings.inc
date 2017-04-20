#define MAX_PLAYER_IP 16 + 1 //Максимальная длина IP игрока
#define MAX_PLAYER_PASSWORD 20 //Максимальная длина пароля от аккаунта
#define MIN_PLAYER_PASSWORD 6 //Минимальная длина пароля от аккаунта
#define MAX_PLAYER_MAIL 64 + 1

#define RECONNECT_INTERVAL 60 //Максимальный допустимые секунды между переподключением игрока


#define PLAYER_MODELS_MALE 60, 7, 20, 44, 101, 170, 184, 188 //Мужские скины при регистрации, добавлять через запятую!
#define PLAYER_MODELS_FEMALE 9, 31, 40, 41, 53, 54, 69, 151, 190 //Женские скины при регистрации, добавлять через запятую!


#define ACTIVATION_CODE_URL "geebrox.esy.es/uworld/code_sender.php" //Место хранение php кода для отправки письма на почту игрока


#define PLAYER_SPAWN_COORDINATES 1128.8514, -1465.4487, 15.7623, 0.0 //Место появление игрока, когда авторизовался на сервере


#define PLAYER_BG_COLOR -505290241 //Цвет фона игрока при регистрации/авторизации