#if defined _account_system_included
	#endinput
#endif
#define _account_system_included


forward CheckPlayerAccount(playerid);
forward CheckPlayerJoinMail(playerid);
forward OnActivationCodeRecived(playerid, response_code, data[]);
forward OnPlayerJoin(playerid);
forward LoadPlayerData(playerid);
forward SetPlayerScreenOverlayEffect(playerid);


enum TD_LOGIN_INFO
{
	Text: TD_LOGIN_BG,
	Text: TD_LOGIN_LOGO,
	Text: TD_LOGIN_HEAD,
	Text: TD_LOGIN_HEAD_TOP,
	Text: TD_LOGIN_HEAD_LCHIT,
	Text: TD_LOGIN_HEAD_RCHIT,
	Text: TD_LOGIN_HEAD_TEXT,
	Text: TD_LOGIN_HEAD_ARROW,
	Text: TD_LOGIN_BODY,
	Text: TD_LOGIN_BODY_BOTTOM,
	Text: TD_LOGIN_BODY_LCHIT,
	Text: TD_LOGIN_BODY_RCHIT,
	Text: TD_LOGIN_LINE_TOP,
	Text: TD_LOGIN_LINE_MIDDLE,
	Text: TD_LOGIN_LINE_BOTTOM,
	Text: TD_LOGIN_LINE_LEFT,
	Text: TD_LOGIN_LINE_DIV,
	Text: TD_LOGIN_LINE_RIGHT,
	Text: TD_LOGIN_IDCARD,
	Text: TD_LOGIN_PADLOCK,
	Text: TD_LOGIN_RESTORE_CHIT,
	Text: TD_LOGIN_RESTORE_TEXT,
	Text: TD_LOGIN_BUTTON,
	Text: TD_LOGIN_BUTTON_TEXT
};

enum PTD_LOGIN_INFO 
{
	PlayerText: PTD_LOGIN_NAME,
	PlayerText: PTD_LOGIN_PASSWORD
};

enum TD_JOIN_INFO
{
	Text: TD_JOIN_BG,
	Text: TD_JOIN_TEXT_TOP,
	Text: TD_JOIN_TEXT_START,
	Text: TD_JOIN_TEXT_RULES,
	Text: TD_JOIN_TEXT_PARAMS,
	Text: TD_JOIN_TEXT_MODEL,
	Text: TD_JOIN_MENU_TEXT,
	Text: TD_JOIN_LIGHTER,
	Text: TD_JOIN_BUTTON,
	Text: TD_JOIN_BUTTON_START,
	Text: TD_JOIN_BUTTON_RULES,
	Text: TD_JOIN_BUTTON_PARAMS,
	Text: TD_JOIN_BUTTON_SUBMIT,
	Text: TD_JOIN_BUTTON_MODEL,
	Text: TD_JOIN_BAR,
	Text: TD_JOIN_BG_RULES,
	Text: TD_JOIN_BG_PARAMS,
	Text: TD_JOIN_BG_MODEL,
	Text: TD_JOIN_ARROW_RULES,
	Text: TD_JOIN_ARROW_PARAMS,
	Text: TD_JOIN_ARROW_MODEL,
	Text: TD_JOIN_MENU_RULES,
	Text: TD_JOIN_MENU_PARAMS,
	Text: TD_JOIN_MENU_MODEL,
	Text: TD_JOIN_TABLE_OUT,
	Text: TD_JOIN_TABLE_BG,
	Text: TD_JOIN_TABLE_DIV,
	Text: TD_JOIN_TABLE_TOP,
	Text: TD_JOIN_TABLE_MIDDLE,
	Text: TD_JOIN_TABLE_BOTTOM,
	Text: TD_JOIN_IDCARD,
	Text: TD_JOIN_PADLOCK,
	Text: TD_JOIN_PAPER,
	Text: TD_JOIN_QUESTION,
	Text: TD_JOIN_BUTTON_LEFT,
	Text: TD_JOIN_BUTTON_RIGHT
};

enum PTD_JOIN_INFO
{
	PlayerText: PTD_JOIN_BAR,
	PlayerText: PTD_JOIN_BAR_TEXT,
	PlayerText: PTD_JOIN_NAME,
	PlayerText: PTD_JOIN_PASSWORD,
	PlayerText: PTD_JOIN_MAIL,
	PlayerText: PTD_JOIN_GENDER,
	PlayerText: PTD_JOIN_MODEL
};

enum PLAYER_LOGIN_STATUS_INFO
{
	PLAYER_LOGIN_STATUS_CONNECTED = 1,
	PLAYER_LOGIN_STATUS_LOGGED
};

enum PLAYER_JOIN_STATUS_INFO
{
	PLAYER_JOIN_STATUS_NONE,
	PLAYER_JOIN_STATUS_RUSSIFIER,
	PLAYER_JOIN_STATUS_START,
	PLAYER_JOIN_STATUS_RULES,
	PLAYER_JOIN_STATUS_PARAMS,
	PLAYER_JOIN_STATUS_MODEL
};

enum PLAYER_DATA
{
	ORM:player_orm,
	player_uid,
	player_name[MAX_PLAYER_NAME],
	player_password[MAX_HASH_SIZE],
	player_salt[MAX_HASH_SIZE],
	player_russifier,
	player_mail[MAX_PLAYER_MAIL + 1],
	player_login_attempts,
	player_gender,
	player_model,
	player_ip[MAX_PLAYER_IP + 1],
	PLAYER_LOGIN_STATUS_INFO:player_login_status,
	PLAYER_JOIN_STATUS_INFO:player_join_status,
	Float:player_join_progress,
	player_bg_color,
	player_money,
	Float:player_health,
	Float:player_armour
};


new
	player[MAX_PLAYERS][PLAYER_DATA],
	clear_player_data[PLAYER_DATA];

new 
	Text: TD_login[TD_LOGIN_INFO],
	PlayerText: PTD_login[MAX_PLAYERS][PTD_LOGIN_INFO],
	Text: TD_join[TD_JOIN_INFO],
	PlayerText: PTD_join[MAX_PLAYERS][PTD_JOIN_INFO],
	PlayerText: PTD_screen_overlay[MAX_PLAYERS];

new join_td_text[][] =
{
	!"Добро_пожаловать_на_сервер, \"Geebrox_Role_Play\" \
		Этот_аккаунт_не_зарегистрирован! Хотите_начать_регистрацию?",
	
	!"На_нашем_сервере_существуют ряд_правил,_которых_должен_соблюдать \
		каждый_игрок,_советуем_ознакомиться с_ними_перед_регистрацией:",
	
	!"Заполните_все_данные, чтобы_продолжить_регистрацию:",
	
	!"Выберите_модель_персонажа, чтобы_завершить_регистрацию:"
};


static russifiers_list[] = !"1. Не установлено\n2. SanLtd\n3. OneC\n\
	4. Rush\n5. Unknown1\n6. Unknown2\n7. Unknown3\n8. MG\n9. Community\n\
	10. Ukraine\n11. Hungarian";

static join_text[][] =
{
	!COLOR_TEXT"Придумайте новый пароль для входа в ваш аккаунт.\n\
		Постарайтесь, чтобы пароль был легко запоминающимся для Вас,\n\
		но сложным для злоумышленников!\n\n\
		"COLOR_NOTE"Примечание:\n\t\
		• Пароль может содержать буквы латинского алфавита, цифры,   \n\t\
		дефисы, символы подчеркивания и точки\n\t\
		• Запрещено использовать более одного вышеуказанных символов подряд\n\t\
		• Длина должен быть меньше, чем "#MAX_PLAYER_PASSWORD" \
		и больше, чем "#MIN_PLAYER_PASSWORD" символов\n\n\
		"COLOR_TEXT"Придумайте себе новый пароль и введите ниже:",

	!COLOR_TEXT"Введите вашу электронную почту\n\
		На него будет отправлено письмо с кодом для подтверждения\n\
		"COLOR_NOTE"Убедитесь, что адрес \
		электронной почты введен правильно:"
};

new server_rules[][] =
{
	!COLOR_ERROR"1. "COLOR_NOTE"РП Термины и РП Процесс:\n\n\t\
		"COLOR_ERROR"1.1 "COLOR_NOTE"MG [Metagaming] - "COLOR_TEXT"\
		Использование вне игровой информации [ООС] в игровом чате [IC].\n\t\
		Наказывается мутом на 30 минут. Для использования вне игровой \
		информации в игре есть вне игровой чат (( /n )).\n\t\t\
		"COLOR_ERROR"Пример:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"На собеседовании игрока спрашивают \
			\"Что такое \"РП\"?.\n\t\tОн отвечает \"Игра по ролям\" вместо \
			\"Редька Перезрелая\" и т.п\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"В гос.организации игрок сообщает в \
			рацию, что он сделал отчет на повышение:\n\t\t\
			\"Я залил отчет на форум, посмотрите плиз\", а должен \"Я оставил \
			отчет на столе в вашем кабинете\" и т.п\n\n\t\
		"COLOR_ERROR"1.2 "COLOR_NOTE"ДМ [DeathMatch] - "COLOR_TEXT"Убийство \
		игрока без ведомой причины. Наказывается КПЗ.\n\t\
		Наказание зависит от тяжести нарушения. При частом рецедиве - бан на 7 \
		дней.\n\t\t\
		"COLOR_ERROR"Пример:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"Вы стоите, мимо вас пробегает игрок, \
			вы начинаете его бить/стрелять в него просто так.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"В слишком людном месте очень много \
			игроков. Вам не пройти, поэтому вы начинаете их бить,\n\t\t\
			чтобы подвинуть и освободить себе проход.\n\n\t\
		"COLOR_ERROR"1.3 "COLOR_NOTE"ДБ [DriveBy] - "COLOR_TEXT"Убийство \
		игрока с помощью транспортного средства или с водительского\
		\\пассажирского места,\n\t\
		если это наземный транспорт. Наказывается КПЗ от 60и минут.\n\t\t\
		"COLOR_ERROR"Пример:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"Вы едете мимо, в вас начинает стрелять \
			другой игрок, вы в ответ, пытаясь его убить, давите \
			автомобилем.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"На перестрелке, войне за территорию вы \
			давите противника автомобилем/мототехникой\n\t\t\
			чтобы получить преимущество над ним.\n\t\t\
			"COLOR_ERROR"3) "COLOR_TEXT"Вы стоите на парковке, к вам подбегает \
			новичок, бьет вашу машину и убегает,\n\t\t\
			вы за ним едите и начинаете его давить.\n\n\t\
		"COLOR_ERROR"1.4 "COLOR_NOTE"СК [SpawnKill] - "COLOR_TEXT"Убийство \
		игрока на точке возрождения. Наказывается КПЗ 60 минут.\n\t\t\
		"COLOR_ERROR"Пример:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"Игрок прибегает на точку возрождения \
			банды и начинает стрелять во всех, кого увидит.",
	
	!COLOR_ERROR"\t1.5 "COLOR_NOTE"ПГ [PowerGaming] - "COLOR_TEXT"Воображение \
	себя героем. Переоценивание своих физических\\психологических сил.\n\t\t\
		"COLOR_ERROR"Пример:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"Отстреливаться от законников в \
			одиночку, когда у них заметное преимущество.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"Отбиваться в одиночку от грабителей \
			врукопашку, когда у них биты, пистолеты и т.п\n\t\t\
			"COLOR_ERROR"3) "COLOR_TEXT"Перед вами появляются бандиты, копы \
			или кто-то еще, которые вам угрожают.\n\t\t\
			Внезапно у вас в руках появляется оружие [Инвентарь пролистали и \
			выбрали] и вы начинаете отстреливаться.\n\n\t\
		"COLOR_ERROR"1.6 "COLOR_NOTE"ТК [TeamKill] - "COLOR_TEXT"Убийство \
		члена своей организации/мафии/банды без причины.\n\n\t\
		"COLOR_ERROR"1.7 "COLOR_NOTE"РК [RepeatKill] - "COLOR_TEXT"Намеренное/\
		Повторное убийство одного и того же игрока.\n\n\
	"COLOR_ERROR"2. "COLOR_NOTE"Остальные Термины:\n\n\t\
		"COLOR_ERROR"2.1 "COLOR_NOTE"AFK [Отошел От Клавиатуры/Away From \
		KeyBoard] - "COLOR_TEXT"Оно же называется \"РП Сном\". Игрок, который \
		временно отошел.\n\t\
		Игроки, состоящие в гос.организациях наказываются киком за AFK вне \
		разрешенной комнаты во время рабочего дня.\n\n\t\
		"COLOR_ERROR"2.2 "COLOR_NOTE"RolePlay NickName - "COLOR_TEXT"Игровой \
		ник в формате \"Имя_Фамилия\". Запрещается состоять в организациях без \
		РП Ника.\n\t\
		Пример правильного ника: John_Smith, Rey_Grover и т.д\n\n\t\
		"COLOR_ERROR"2.3 "COLOR_NOTE"Bagouse [Багоюз] - "COLOR_TEXT"\
		Использование багов в игре. За использование предусмотрено \
		наказание баном.\n\t\
		Наказание зависит от степени тяжести нарушения."
};

static player_models[2][] =
{
	{PLAYER_MODELS_MALE, -1},
	{PLAYER_MODELS_FEMALE, -1}
};

static player_models_size[sizeof player_models];


stock account_OnGameModeInit()
{
	for(new i, j; i < sizeof player_models; i++)
	{
		j = 0;
		
		while(player_models[i][j] != -1)
		{
			j++;
		}
		
		player_models_size[i] = j;
	}

	LoadGlobalLoginTextDraws();
	LoadGlobalJoinTextDraws();

	return 1;
}


stock account_OnPlayerConnect(playerid)
{
	TogglePlayerSpectating(playerid, 1);

	GetPlayerName(playerid, player[playerid][player_name], MAX_PLAYER_NAME);

	if(!IsValidName(player[playerid][player_name]))
    {
		return Kick(playerid, KICK_TEXT_REASON"\
			Ваше имя не соответствует RP правилам\n\
			Пример правильной имени: \
			"COLOR_SUCCESS"John_Smith\n\n"KICK_TEXT_TIP);
    }
    
    SetPlayerCameraPos(playerid, 0.0, 0.0, -500.0);
	SetPlayerCameraLookAt(playerid, 0.0, 0.0, -500.0);
	ClearPlayerChat(playerid);
	
	player[playerid][player_orm] = orm_create("accounts");
	
	orm_addvar_int(player[playerid][player_orm],
		player[playerid][player_uid], "uid");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_name], MAX_PLAYER_NAME, "name");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_password], MAX_HASH_SIZE, "password");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_salt], MAX_HASH_SIZE, "salt");
	orm_addvar_int(player[playerid][player_orm],
		player[playerid][player_russifier], "russifier");
	orm_setkey(player[playerid][player_orm], "name");
	orm_select(player[playerid][player_orm],
		"CheckPlayerAccount", "i", playerid);
	return 1;
}


public CheckPlayerAccount(playerid)
{
	player[playerid][player_login_status] = PLAYER_LOGIN_STATUS_CONNECTED;
	player[playerid][player_login_attempts] = MAX_PLAYER_LOGIN_ATTEMPTS;

	if(orm_errno(player[playerid][player_orm]) == ERROR_OK)
	{
		SetPlayerRussifierType(playerid,
			RussifierType:player[playerid][player_russifier]);

		if(RussifierType:player[playerid][player_russifier] ==
			RussifierType_Disabled)
		{
			state PlayerRussifier:disabled;

			Dialog_Show(playerid, Dialog:login_password);
		}

		else
		{
			state PlayerRussifier:enabled;

			LoadPlayerLoginTextDraws(playerid);

			for(new TD_LOGIN_INFO:i; i < TD_LOGIN_INFO; i++) 
			{ 
				TextDrawShowForPlayer(playerid, TD_login[i]); 
			}

			for(new PTD_LOGIN_INFO:i; i < PTD_LOGIN_INFO; i++)
			{
				PlayerTextDrawShow(playerid, PTD_login[playerid][i]);
			}

			SelectTextDraw(playerid, 0x2c3e50FF);
		}
	}

	else
	{
		player[playerid][player_join_status] = PLAYER_JOIN_STATUS_RUSSIFIER;
		player[playerid][player_gender] = -1;

		TextDrawShowForPlayer(playerid, TD_login[TD_LOGIN_BG]);
		TextDrawShowForPlayer(playerid, TD_login[TD_LOGIN_LOGO]);

		Dialog_Open(playerid, Dialog:join_russifier, DIALOG_STYLE_LIST,
	        !COLOR_TITLE"Выберите ваш русификатор игры",
	        russifiers_list,
	        !"Далее", !"");
	}

	return 1;
}


//============================== [ REGISTRATION ] ==============================

DialogResponse:join_russifier(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		return Dialog_Open(playerid, Dialog:join_russifier, DIALOG_STYLE_LIST,
	        !COLOR_TITLE"Выберите ваш русификатор игры",
	        russifiers_list,
	        !"Далее", !"");
	}

	listitem--;
	player[playerid][player_russifier] = listitem;

	SetPlayerRussifierType(playerid, RussifierType:listitem);

	if(RussifierType_Disabled == RussifierType:listitem)
	{
		state PlayerRussifier:disabled;
		Dialog_Show(playerid, Dialog:join_rules);
		LoadPlayerJoinTextDraws(playerid);
	}

	else
	{
		state PlayerRussifier:enabled;

		player[playerid][player_join_status] = PLAYER_JOIN_STATUS_START;
		
		LoadPlayerJoinTextDraws(playerid);
		UpdatePlayerJoinTextDraws(playerid);
		SelectTextDraw(playerid, 0x2c3e50FF);
	}

	return 1;
}




//======================= [ REGISTRATION: No Russifier ] =======================
DialogCreate:join_rules(playerid) <PlayerRussifier:disabled>
{
	new rules_list = GetPVarInt(playerid, !"server_rules_list");

	Dialog_Open(playerid, Dialog:join_rules, DIALOG_STYLE_MSGBOX,
        !COLOR_TITLE"Правила сервера",
        server_rules[rules_list - 1],
        ++rules_list == sizeof server_rules ? !"Принять" : !"Далее",
        "Назад");
}


DialogResponse:join_rules(playerid, response, listitem, inputtext[])
	<PlayerRussifier:disabled>
{
	if(!response)
	{
		new rules_list = GetPVarInt(playerid, !"server_rules_list");

		if(!rules_list)
		{
			DeletePVar(playerid, !"server_rules_list");
			return Dialog_Open(playerid, Dialog:join_russifier,
				DIALOG_STYLE_LIST,
		        !COLOR_TITLE"Выберите ваш русификатор игры",
		        russifiers_list,
		        !"Далее", !"");
		}
		
		SetPVarInt(playerid, !"server_rules_list", rules_list-1);
	}

	else
	{
		new rules_list = GetPVarInt(playerid, !"server_rules_list")+1;

		if(rules_list == sizeof server_rules)
		{
			DeletePVar(playerid, !"server_rules_list");
			return Dialog_Open(playerid, Dialog:join_password,
				DIALOG_STYLE_INPUT,
		        !COLOR_TITLE"Пароль для аккаунта",
		        join_text[0],
		        !"Далее", !"Назад");
		}

		SetPVarInt(playerid, !"server_rules_list", rules_list);
	}

	Dialog_Show(playerid, Dialog:join_rules);
	return 1;
}


DialogResponse:join_password(playerid, response, listitem, password[])
	<PlayerRussifier:disabled>
{
	if(!response)
	{
		return Dialog_Show(playerid, Dialog:join_rules);
	}

	else if(!IsValidPassword(password))
	{
		return Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[0],
	        !"Далее", !"Назад");
	}

	CreatePlayerPassword(playerid, password);

	Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Электронная почта",
	        join_text[1],
	        !"Далее", !"Назад");
	return 1;
}


DialogResponse:join_mail(playerid, response, listitem, inputtext[])
	<PlayerRussifier:disabled>
{
	if(!response)
	{
		return Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[0],
	        !"Далее", !"Назад");
	}

	else if(!IsValidMail(inputtext))
	{
		return Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Электронная почта",
	        join_text[1],
	        !"Далее", !"Назад");
	}

	player[playerid][player_mail][0] = EOS;

	strmid(player[playerid][player_mail], inputtext, 0, strlen(inputtext),
		MAX_PLAYER_MAIL);
	
	static query_content[] = "SELECT mail FROM accounts WHERE mail='%s'";
	
	new query[sizeof query_content - 2 + MAX_PLAYER_MAIL];
	
	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		player[playerid][player_mail]);
	mysql_tquery(mysql_connection_id, query,
		"CheckPlayerJoinMail", "i", playerid);
	return 1;
}


public CheckPlayerJoinMail(playerid) <PlayerRussifier:disabled>
{
	new rows;
	cache_get_row_count(rows);
	
	if(rows)
	{
		player[playerid][player_mail][0] = EOS;

		return Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_MSGBOX,
			!COLOR_TITLE"Ошибка",
			!COLOR_ERROR"Указанный электронный адрес занят другим аккаунтом! \
			Укажите другой электронный адрес!",
			!"Изменить", !"Назад");
	}

	Dialog_Message(playerid,
		!COLOR_TITLE"Отпрака письма...",
		!COLOR_ERROR"Код активации отправляется на указанную почту\n\
		Пожалуйста подождите...",
		!"Ждать");

	CancelSelectTextDraw(playerid);

	static const string_content[] = "c=%d&m=%s";

	new
		string[sizeof string_content + MAX_PLAYER_MAIL],
		random_numbers = random(8999) + 1000;

	SetPVarInt(playerid, !"activation_code", random_numbers);
	
	format(string, sizeof string, string_content, random_numbers,
		player[playerid][player_mail]);

	HTTP(playerid, HTTP_POST, ACTIVATION_CODE_URL, string,
		"OnActivationCodeRecived");
	return 1;
}


public OnActivationCodeRecived(playerid, response_code, data[])
	<PlayerRussifier:disabled>
{
	if(200 != response_code)
	{
		return Kick(playerid, !COLOR_ERROR"Вы были отсоединены от сервера\n\
			Причина: "COLOR_TITLE"Не удалось отправить письмо с кодом для \
			подтверждения\nВозникла не известная ошибка\n\n\
			"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)");
	}

	Dialog_Show(playerid, Dialog:join_activation);
	return 1;
}


DialogCreate:join_activation(playerid) <PlayerRussifier:disabled>
{
	static const string_content[] = !COLOR_TEXT"На указанную электронную почту \
		был выслан код подтверждение состоящий из 4 цифр\n\
		Обычно письмо приходит мгновенно, но советуем подождать 5-10 минут\n\
		"COLOR_NOTE"Не забудьте проверить папку спам\n\n\
		"COLOR_TEXT"Для продолжение ведите код подтверждение\n\
		Попыток осталось: ";

	new
		attempts[2],
		string[sizeof string_content + sizeof attempts + 8];

	itos(player[playerid][player_login_attempts], attempts);
	strcat(string, string_content);
	strcat(string, !COLOR_ERROR);
	strcat(string, attempts);

	Dialog_Open(playerid, Dialog:join_activation, DIALOG_STYLE_INPUT,
        !COLOR_TITLE"Подтверждения почты",
        string,
        !"Далее", !"Выйти");
}


DialogResponse:join_activation(playerid, response, listitem, inputtext[])
	<PlayerRussifier:disabled>
{
	if(!response)
	{
		return Kick(playerid);
	}

	new activation_code = strval(inputtext);

	if(activation_code < 1000)
	{
		return Dialog_Show(playerid, Dialog:join_activation);
	}

	else if(GetPVarInt(playerid, !"activation_code") != activation_code)
	{
		if(--player[playerid][player_login_attempts] <= 0)
		{
			return Kick(playerid, KICK_TEXT_REASON"\
				Вы исчерпали все попытки ввода пароля!"KICK_TEXT_TIP);
		}

		return Dialog_Show(playerid, Dialog:join_activation);
	}

	Dialog_Open(playerid, Dialog:join_gender, DIALOG_STYLE_MSGBOX,
        !COLOR_TITLE"Пол персонажа",
        !COLOR_TEXT"Выберите пол вашего персонажа:",
        !"Женский", !"Мужской");

	return 1;
}

DialogResponse:join_gender(playerid, response, listitem, inputtext[])
	<PlayerRussifier:disabled>
{
	player[playerid][player_gender] = response;
	
	SelectTextDraw(playerid, 0x2c3e50FF);
	UpdatePlayerJoinTextDraws(playerid);

	Dialog_Message(playerid, !COLOR_TITLE"Модель игрока",
		!COLOR_TEXT"Выберите модель вашего персонажа, \
		чтобы завершить регистрацию!", !"Принять");
	return 1;
}


stock UpdatePlayerJoinTextDraws(playerid) <PlayerRussifier:disabled>
{
	if(PLAYER_JOIN_STATUS_RUSSIFIER == player[playerid][player_join_status])
	{
		TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BG]);
		TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON]);
		TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_SUBMIT]);
		TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_LEFT]);
		TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_RIGHT]);

		PlayerTextDrawShow(playerid,
			PTD_join[playerid][PTD_JOIN_MODEL]);
	}

	else if(PLAYER_JOIN_STATUS_NONE == player[playerid][player_join_status])
	{
		TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_BG]);
		TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_LOGO]);

		TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BG]);
		TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON]);
		TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_SUBMIT]);
		TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_LEFT]);
		TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_RIGHT]);

		PlayerTextDrawHide(playerid,
			PTD_join[playerid][PTD_JOIN_MODEL]);
	}
}


stock account_OnPlayerClickTextDraw(playerid, Text:clickedid)
	<PlayerRussifier:disabled>
{
	if(!(_:clickedid ^ INVALID_TEXT_DRAW) &&
		IsPlayerSelectTextDraw(playerid))
	{
		return SelectTextDraw(playerid, GetPVarInt(playerid, !"_select_td"));
	}

	else if(clickedid == TD_join[TD_JOIN_BUTTON_LEFT] ||
		clickedid == TD_join[TD_JOIN_BUTTON_RIGHT])
	{
		new gender = player[playerid][player_gender];
		new model_number = GetPVarInt(playerid, !"model_number");

		if(clickedid == TD_join[TD_JOIN_BUTTON_LEFT])
		{
	        if(--model_number < 0)
	        {
	            model_number = player_models_size[gender] - 1;
	        }
	    }

	    else if(clickedid == TD_join[TD_JOIN_BUTTON_RIGHT])
	    {
	        if(++model_number >= player_models_size[gender])
	        {
	            model_number = 0;
	        }
	    }

	    player[playerid][player_model] =
	    	player_models[gender][model_number];
		PlayerTextDrawSetPreviewModel(playerid,
			PTD_join[playerid][PTD_JOIN_MODEL], player[playerid][player_model]);
		PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MODEL]);

		SetPVarInt(playerid, !"model_number", model_number);
	}

	else if(clickedid == TD_join[TD_JOIN_BUTTON])
	{
		if(0 == player[playerid][player_model])
		{
			return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
				!COLOR_ERROR"Выберите модель персонажа, \
				чтобы завершить регистрацию!",
				!"Закрыть");
		}
		
		player[playerid][player_join_status] = PLAYER_JOIN_STATUS_NONE;

		CancelSelectTextDraw(playerid);
		CreatePlayerData(playerid);
		orm_setkey(player[playerid][player_orm], "uid");
		orm_insert(player[playerid][player_orm], "OnPlayerJoin", "i", playerid);
	}

	return 1;
}
//===================== [ REGISTRATION: No Russifier END ] =====================




//====================== [ REGISTRATION: With Russifier ] ======================
stock UpdatePlayerJoinTextDraws(playerid) <PlayerRussifier:enabled>
{
	switch(player[playerid][player_join_status])
	{
		case PLAYER_JOIN_STATUS_START:
		{
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BG]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TEXT_TOP]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TEXT_START]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_MENU_TEXT]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_LIGHTER]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_START]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BAR]);

			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_BAR]);
			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT]);
		}

		case PLAYER_JOIN_STATUS_RULES:
		{
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TEXT_START]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_START]);

			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TEXT_RULES]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_RULES]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BG_RULES]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_ARROW_RULES]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_MENU_RULES]);
		}

		case PLAYER_JOIN_STATUS_PARAMS:
		{
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TEXT_RULES]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_RULES]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BG_RULES]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_ARROW_RULES]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_MENU_RULES]);

			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TEXT_PARAMS]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_PARAMS]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BG_PARAMS]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_ARROW_PARAMS]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_MENU_PARAMS]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_OUT]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_BG]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_DIV]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_TOP]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_MIDDLE]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TABLE_BOTTOM]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_IDCARD]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_PADLOCK]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_PAPER]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_QUESTION]);

			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_NAME]);
			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD]);
			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MAIL]);
			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_GENDER]);
		}

		case PLAYER_JOIN_STATUS_MODEL:
		{
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TEXT_PARAMS]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BUTTON_PARAMS]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_BG_PARAMS]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_ARROW_PARAMS]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_MENU_PARAMS]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_OUT]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_BG]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_DIV]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_TOP]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_MIDDLE]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_TABLE_BOTTOM]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_IDCARD]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_PADLOCK]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_PAPER]);
			TextDrawHideForPlayer(playerid, TD_join[TD_JOIN_QUESTION]);

			PlayerTextDrawHide(playerid, PTD_join[playerid][PTD_JOIN_NAME]);
			PlayerTextDrawHide(playerid,
				PTD_join[playerid][PTD_JOIN_PASSWORD]);
			PlayerTextDrawHide(playerid, PTD_join[playerid][PTD_JOIN_MAIL]);
			PlayerTextDrawHide(playerid,
				PTD_join[playerid][PTD_JOIN_GENDER]);

			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_TEXT_MODEL]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_MODEL]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BG_MODEL]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_ARROW_MODEL]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_MENU_MODEL]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_LEFT]);
			TextDrawShowForPlayer(playerid, TD_join[TD_JOIN_BUTTON_RIGHT]);

			PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MODEL]);
		}

		case PLAYER_JOIN_STATUS_NONE:
		{
			TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_BG]);
			TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_LOGO]);

			for(new TD_JOIN_INFO: i; i < TD_JOIN_INFO; i++)
			{
				TextDrawHideForPlayer(playerid, TD_join[i]);
			}

			for(new PTD_JOIN_INFO: i; i < PTD_JOIN_INFO; i++)
			{
				PlayerTextDrawHide(playerid, PTD_join[playerid][i]);
			}
		}
	}
}


stock account_OnPlayerClickTextDraw(playerid, Text:clickedid)
	<PlayerRussifier:enabled>
{
	if(!(_:clickedid ^ INVALID_TEXT_DRAW) &&
		IsPlayerSelectTextDraw(playerid))
	{
		return SelectTextDraw(playerid, GetPVarInt(playerid, !"_select_td"));
	}

	else if(clickedid == TD_join[TD_JOIN_BUTTON])
	{
		switch(player[playerid][player_join_status])
		{
			case PLAYER_JOIN_STATUS_START:
			{
				AddPlayerJoinProgress(playerid, 10);
				player[playerid][player_join_status] = PLAYER_JOIN_STATUS_RULES;

				UpdatePlayerJoinTextDraws(playerid);
			}

			case PLAYER_JOIN_STATUS_RULES:
			{
				AddPlayerJoinProgress(playerid, 10);
				Dialog_Show(playerid, Dialog:join_rules);
			}

			case PLAYER_JOIN_STATUS_PARAMS:
			{
				if(EOS == player[playerid][player_password][0])
				{
					return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
						!COLOR_ERROR"Укажите пароль для аккаунта!",
						!"Закрыть");
				}

				else if(EOS == player[playerid][player_mail][0])
				{
					return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
						!COLOR_ERROR"Укажите свою почту!", !"Закрыть");
				}

				else if(-1 == player[playerid][player_gender])
				{
					return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
						!COLOR_ERROR"Выберите пол для вашего персонажа!",
						!"Закрыть");
				}

				AddPlayerJoinProgress(playerid, 10);
				player[playerid][player_join_status] = PLAYER_JOIN_STATUS_MODEL;

				UpdatePlayerJoinTextDraws(playerid);
			}

			case PLAYER_JOIN_STATUS_MODEL:
			{
				if(0 == player[playerid][player_model])
				{
					return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
						!COLOR_ERROR"Выберите модель персонажа, \
						чтобы завершить регистрацию!",
						!"Закрыть");
				}
				
				player[playerid][player_join_status] = PLAYER_JOIN_STATUS_NONE;

				CancelSelectTextDraw(playerid);

				CreatePlayerData(playerid);

				orm_setkey(player[playerid][player_orm], "uid");
				orm_insert(player[playerid][player_orm], "OnPlayerJoin",
					"i", playerid);
			}
		}
	}

	else if(clickedid == TD_join[TD_JOIN_BUTTON_LEFT] ||
		clickedid == TD_join[TD_JOIN_BUTTON_RIGHT])
	{
		if(0 == player[playerid][player_model])
		{
			AddPlayerJoinProgress(playerid, 10);
		}

		new gender = player[playerid][player_gender];
		new model_number = GetPVarInt(playerid, !"model_number");

		if(clickedid == TD_join[TD_JOIN_BUTTON_LEFT])
		{
	        if(--model_number < 0)
	        {
	            model_number = player_models_size[gender] - 1;
	        }
	    }

	    else if(clickedid == TD_join[TD_JOIN_BUTTON_RIGHT])
	    {
	        if(++model_number >= player_models_size[gender])
	        {
	            model_number = 0;
	        }
	    }

	    player[playerid][player_model] =
	    	player_models[gender][model_number];
		PlayerTextDrawSetPreviewModel(playerid,
			PTD_join[playerid][PTD_JOIN_MODEL], player[playerid][player_model]);
		PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MODEL]);

		SetPVarInt(playerid, !"model_number", model_number);
	}

	else if(clickedid == TD_login[TD_LOGIN_BUTTON])
	{
		new password[MAX_PLAYER_PASSWORD + 1];
		GetPVarString(playerid, !"login_password", password, sizeof password);

		if(password[0] == EOS)
		{
			return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
				!COLOR_ERROR"Введите пароль от аккаунта!",
				!"Закрыть");
		}

		else if(CheckPlayerPassword(password, player[playerid][player_password],
			player[playerid][player_salt]))
		{
			for(new TD_LOGIN_INFO: i; i < TD_LOGIN_INFO; i++) 
			{ 
				TextDrawHideForPlayer(playerid, TD_login[i]); 
			}

			for(new PTD_LOGIN_INFO: i; i < PTD_LOGIN_INFO; i++)
			{
				PlayerTextDrawHide(playerid, PTD_login[playerid][i]);
			}

			CancelSelectTextDraw(playerid);
			
			CreatePlayerData(playerid);

		 	orm_setkey(player[playerid][player_orm], "uid");
		 	orm_select(player[playerid][player_orm],
		 		"LoadPlayerData", "i", playerid);
			return 1;
		}
		
		player[playerid][player_login_attempts]--;
		
		if(player[playerid][player_login_attempts] <= 0)
		{
			return Kick(playerid, KICK_TEXT_REASON"\
				Вы исчерпали все попытки ввода пароля!"KICK_TEXT_TIP);
		}

		static const string_content[] = COLOR_ERROR"Неверный пароль!\n\
			"COLOR_TEXT"Попыток ввода пароля осталось: ";

		new
			attempts[2],
			string[sizeof string_content + sizeof attempts + 8];

		itos(player[playerid][player_login_attempts], attempts);
		strcat(string, string_content);
		strcat(string, !COLOR_ERROR);
		strcat(string, attempts);

		return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
			string, !"Закрыть");
	}

	return 1;
}


DialogCreate:join_rules(playerid) <PlayerRussifier:enabled>
{
	new rules_list = GetPVarInt(playerid, !"server_rules_list");

	Dialog_Open(playerid, Dialog:join_rules, DIALOG_STYLE_MSGBOX,
        !COLOR_TITLE"Правила сервера",
        server_rules[rules_list-1],
        ++rules_list == sizeof server_rules ? !"Принять" : !"Далее",
        !rules_list ? !"Закрыть" : !"Назад");
}


DialogResponse:join_rules(playerid, response, listitem, inputtext[])
	<PlayerRussifier:enabled>
{
	if(!response)
	{
		new rules_list = GetPVarInt(playerid, !"server_rules_list");
		
		AddPlayerJoinProgress(playerid, -10.0);
		
		if(!rules_list)
		{
			DeletePVar(playerid, !"server_rules_list");
			return 1;
		}
		
		SetPVarInt(playerid, !"server_rules_list", rules_list-1);
	}

	else
	{
		new rules_list = GetPVarInt(playerid, !"server_rules_list")+1;
		
		AddPlayerJoinProgress(playerid, 10.0);

		if(rules_list == sizeof server_rules)
		{
			DeletePVar(playerid, !"server_rules_list");

			player[playerid][player_join_status] = PLAYER_JOIN_STATUS_PARAMS;

			UpdatePlayerJoinTextDraws(playerid);
			return 1;
		}

		SetPVarInt(playerid, !"server_rules_list", rules_list);
	}

	Dialog_Show(playerid, Dialog:join_rules);
	return 1;
}


stock account_OnPlayerClickPlayerText(playerid, PlayerText:playertextid)
{
	if(playertextid == PTD_join[playerid][PTD_JOIN_PASSWORD])
	{
		Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[0],
	        !"Принять", !"Отмена");
	}

	else if(playertextid == PTD_join[playerid][PTD_JOIN_MAIL])
	{
		Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Электронная почта",
	        join_text[1],
	        !"Принять", !"Отмена");
	}

	else if(playertextid == PTD_join[playerid][PTD_JOIN_GENDER])
	{
		Dialog_Open(playerid, Dialog:join_gender, DIALOG_STYLE_MSGBOX,
	        !COLOR_TITLE"Пол персонажа",
	        !COLOR_TEXT"Выберите пол вашего персонажа:",
	        !"Женский", !"Мужской");
	}

	else if(playertextid == PTD_login[playerid][PTD_LOGIN_PASSWORD])
	{
		Dialog_Show(playerid, Dialog:login_password);
	}

	return 1;
}


DialogResponse:join_password(playerid, response, listitem, password[])
	<PlayerRussifier:enabled>
{
	if(!response)
	{
		return 1;
	}

	else if(!IsValidPassword(password))
	{
		return Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[0],
	        !"Принять", !"Отмена");
	}

	else if(player[playerid][player_password][0] == EOS)
	{
		AddPlayerJoinProgress(playerid, 10.0);
	}

	CreatePlayerPassword(playerid, password);

	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], -1);
	PlayerTextDrawSetString(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD],
		password);
	PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD]);
	return 1;
}


DialogResponse:join_mail(playerid, response, listitem, inputtext[])
	<PlayerRussifier:enabled>
{
	if(!response)
	{
		return 1;
	}

	else if(!IsValidMail(inputtext))
	{
		return Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Электронная почта",
	        join_text[1],
	        !"Принять", !"Отмена");
	}

	else if(player[playerid][player_mail][0] == EOS)
	{
		AddPlayerJoinProgress(playerid, 10.0);
	}

	else
	{
		player[playerid][player_mail][0] = EOS;
	}

	strmid(player[playerid][player_mail], inputtext, 0, strlen(inputtext),
		MAX_PLAYER_MAIL);
	
	static query_content[] = "SELECT mail FROM accounts WHERE mail='%s'";
	
	new query[sizeof query_content - 2 + MAX_PLAYER_MAIL];
	
	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		player[playerid][player_mail]);
	mysql_tquery(mysql_connection_id, query,
		"CheckPlayerJoinMail", "i", playerid);
	return 1;
}


public CheckPlayerJoinMail(playerid) <PlayerRussifier:enabled>
{
	new rows;
	cache_get_row_count(rows);
	
	if(rows)
	{
		player[playerid][player_mail][0] = EOS;

		AddPlayerJoinProgress(playerid, -10.0);

		return Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_MSGBOX,
			!COLOR_TITLE"Ошибка",
			!COLOR_ERROR"Указанный электронный адрес используется другим \
			аккаунтом! Укажите другой электронный адрес!",
			!"Изменить", !"Отмена");
	}

	Dialog_Message(playerid,
		!COLOR_TITLE"Отпрака письма...",
		!COLOR_ERROR"Код активации отправляется на указанную почту\n\
		Пожалуйста подождите...",
		!"Ждать");
	CancelSelectTextDraw(playerid);

	static const string_content[] = "c=%d&m=%s";

	new
		string[sizeof string_content + MAX_PLAYER_MAIL],
		random_numbers = random(8999) + 1000;

	SetPVarInt(playerid, !"activation_code", random_numbers);
	format(string, sizeof string, string_content, random_numbers,
		player[playerid][player_mail]);

	HTTP(playerid, HTTP_POST, ACTIVATION_CODE_URL, string,
		"OnActivationCodeRecived");
	return 1;
}


public OnActivationCodeRecived(playerid, response_code, data[])
	<PlayerRussifier:enabled>
{
	if(200 != response_code)
	{
		return Kick(playerid, !COLOR_ERROR"Вы были отсоединены от сервера\n\
			Причина: "COLOR_TITLE"Не удалось отправить письмо с кодом для \
			подтверждения\nВозникла не известная ошибка\n\n\
			"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)");
	}

	Dialog_Show(playerid, Dialog:join_activation);
	return 1;
}

DialogCreate:join_activation(playerid) <PlayerRussifier:enabled>
{
	static const string_content[] = !COLOR_TEXT"На указанную электронную почту\
		был выслан код подтверждение состоящий из 4 цифр\n\
		Обычно письмо приходит мгновенно, но советуем подождать 5-10 минут\n\
		"COLOR_NOTE"Не забудьте проверить папку спам\n\n\
		"COLOR_TEXT"Для продолжение ведите код подтверждение\n\
		Попыток осталось: ";

	new
		attempts[2],
		string[sizeof string_content + sizeof attempts + 8];

	itos(player[playerid][player_login_attempts], attempts);
	strcat(string, string_content);
	strcat(string, !COLOR_ERROR);
	strcat(string, attempts);

	Dialog_Open(playerid, Dialog:join_activation, DIALOG_STYLE_INPUT,
        !COLOR_TITLE"Подтверждения почты",
        string,
        !"Далее", !"Выйти");
}


DialogResponse:join_activation(playerid, response, listitem, inputtext[])
	<PlayerRussifier:enabled>
{
	if(!response)
	{
		return Kick(playerid);
	}

	new activation_code = strval(inputtext);

	if(activation_code < 1000)
	{
		return Dialog_Show(playerid, Dialog:join_activation);
	}

	else if(GetPVarInt(playerid, !"activation_code") != activation_code)
	{
		if(--player[playerid][player_login_attempts] <= 0)
		{
			return Kick(playerid, KICK_TEXT_REASON"\
				Вы исчерпали все попытки ввода пароля!"KICK_TEXT_TIP);
		}

		return Dialog_Show(playerid, Dialog:join_activation);
	}

	AddPlayerJoinProgress(playerid, 10.0);

	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_MAIL], -1);
	PlayerTextDrawSetString(playerid, PTD_join[playerid][PTD_JOIN_MAIL],
		player[playerid][player_mail]);
	PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MAIL]);
	return 1;
}


DialogResponse:join_gender(playerid, response, listitem, inputtext[])
	<PlayerRussifier:enabled>
{
	if(player[playerid][player_gender] == -1)
	{
		AddPlayerJoinProgress(playerid, 10.0);
	}

	player[playerid][player_gender] = response;

	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_GENDER], -1);
	PlayerTextDrawSetString(playerid, PTD_join[playerid][PTD_JOIN_GENDER],
		response ? !"Женский" : !"Мужской");
	PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_GENDER]);
	return 1;
}


public OnPlayerJoin(playerid)
{
	if(orm_errno(player[playerid][player_orm]) == ERROR_OK)
	{
		UpdatePlayerJoinTextDraws(playerid);
		Dialog_Message(playerid, !COLOR_TITLE"Завершение",
			!COLOR_TEXT"Поздравляем Вас с упешной регистрацией,\n\
			Спасибо за то, что выбрали наш проект \
			"COLOR_NOTE SERVER_NAME COLOR_TEXT"\n\
			Желаем вам приятной игры на нашем сервере!",
			!"Спасибо");
		orm_load(player[playerid][player_orm], "LoadPlayerData", "i", playerid);
	}

	else
	{
		Kick(playerid, KICK_TEXT_REASON"Не удалось создать новый аккаунт в \
			базе данных.\nПроизошла неизвестная ошибка!"KICK_TEXT_TIP);
	}

	return 1;
}
//============================ [ REGISTRATION END ] ============================




//====================== [ AUTHORIZATION: No Russifier ] =======================
DialogCreate:login_password(playerid) <PlayerRussifier:disabled>
{
	static const string_content[] = !COLOR_TEXT"Добро пожаловать на сервер\
		"COLOR_NOTE SERVER_NAME"!\n"COLOR_TEXT"Данный аккаунт \
		зарегестрирован, введитепароль от аккаунта.\n\
		Попыток ввода пароля осталось: ";

	new
		attempts[2],
		string[sizeof string_content + sizeof attempts + 8];

	itos(player[playerid][player_login_attempts], attempts);
	strcat(string, string_content);
	strcat(string, !COLOR_ERROR);
	strcat(string, attempts);

	Dialog_Open(playerid, Dialog:login_password, DIALOG_STYLE_PASSWORD,
        !COLOR_TITLE"Авторизация | Пароль",
        string,
        !"Войти", !"Выйти");
}


DialogResponse:login_password(playerid, response, listitem, inputtext[])
	<PlayerRussifier:disabled>
{
	if(!response)
	{
		return Kick(playerid);
	}

	else if(!strlen(inputtext))
	{
		return Dialog_Show(playerid, Dialog:login_password);
	}

	else if(!IsValidPassword(inputtext) || !CheckPlayerPassword(inputtext,
		player[playerid][player_password], player[playerid][player_salt]))
	{
		player[playerid][player_login_attempts]--;

		if(player[playerid][player_login_attempts] <= 0)
		{
			return Kick(playerid, KICK_TEXT_REASON"Вы исчерпали все попытки \
				ввода пароля!"KICK_TEXT_TIP);
		}

		return Dialog_Show(playerid, Dialog:login_password);
	}

	CreatePlayerData(playerid);
	orm_setkey(player[playerid][player_orm], "uid");
 	orm_select(player[playerid][player_orm], "LoadPlayerData", "i", playerid);

 	TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_BG]);
 	TextDrawHideForPlayer(playerid, TD_login[TD_LOGIN_LOGO]);
	return 1;
}




//===================== [ AUTHORIZATION: With Russifier ] ======================
DialogCreate:login_password(playerid) <PlayerRussifier:enabled>
{
	Dialog_Open(playerid, Dialog:login_password, DIALOG_STYLE_INPUT,
        !COLOR_TITLE"Авторизация | Пароль",
        !COLOR_TEXT"Введите пароль от аккаунта:",
        !"Войти", !"Выйти");
}


DialogResponse:login_password(playerid, response, listitem, inputtext[])
	<PlayerRussifier:enabled>
{
	if(response && strlen(inputtext))
	{
		PlayerTextDrawColor(playerid,
			PTD_login[playerid][PTD_LOGIN_PASSWORD], 255);
		PlayerTextDrawSetString(playerid,
			PTD_login[playerid][PTD_LOGIN_PASSWORD], inputtext);
		PlayerTextDrawShow(playerid, PTD_login[playerid][PTD_LOGIN_PASSWORD]);

		SetPVarString(playerid, !"login_password", inputtext);
	}

	return 1;
}


public LoadPlayerData(playerid)
{
	if(orm_errno(player[playerid][player_orm]) == ERROR_OK)
	{
		CallLocalFunction(!"OnPlayerLogin", "i", playerid);
		
		PTD_screen_overlay[playerid] =
			CreatePlayerTextDraw(playerid, 300, 0, !"_");
	    PlayerTextDrawUseBox(playerid, PTD_screen_overlay[playerid], 1);
	    PlayerTextDrawAlignment(playerid, PTD_screen_overlay[playerid], 2);
	    PlayerTextDrawSetOutline(playerid, PTD_screen_overlay[playerid], 1);
		PlayerTextDrawLetterSize(playerid,
			PTD_screen_overlay[playerid], 0.0, 60.0);
		PlayerTextDrawSetProportional(playerid,
			PTD_screen_overlay[playerid], 0);
		PlayerTextDrawTextSize(playerid,
			PTD_screen_overlay[playerid], -180.0, 700.0);
		PlayerTextDrawFont(playerid, PTD_screen_overlay[playerid], 3);
		
		player[playerid][player_bg_color] = PLAYER_BG_COLOR;

		SetPlayerScreenOverlayEffect(playerid);

		player[playerid][player_login_status] = PLAYER_LOGIN_STATUS_LOGGED;

		SetSpawnInfo(playerid, 0, player[playerid][player_model], 
			0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, 0);

		if(2.0 > player[playerid][player_health])
		{
			player[playerid][player_health] = 10.0;
		}
	}

	else
	{
		Kick(playerid, KICK_TEXT_REASON"Не удалось загрузить Ваш аккаунт.\
			\nПроизошла неизвестная ошибка!"KICK_TEXT_TIP);
	}

	return 1;
}
//=========================== [ AUTHORIZATION: END ] ===========================




//================================ [ FUNTIONS ] ================================
stock account_OnPlayerRequestClass(playerid)
{
	if(PLAYER_LOGIN_STATUS_LOGGED == player[playerid][player_login_status])
	{
		SpawnPlayer(playerid);
	}

	else
	{//Возможно читы, ибо такого варианта не должно быть
		Kick(playerid, KICK_TEXT_REASON"\
			Подозрение в читерстве!"KICK_TEXT_TIP);
		return 0;
	}

	return 1;
}


stock account_OnPlayerSpawn(playerid)
{
	if(PLAYER_LOGIN_STATUS_LOGGED != player[playerid][player_login_status])
	{
		Kick(playerid, KICK_TEXT_REASON"\
			Необходимо авторизоваться!"KICK_TEXT_TIP);
		return 0;
	}

	SetPlayerPos(playerid,
		PLAYER_SPAWN_COORDINATE_X,
		PLAYER_SPAWN_COORDINATE_Y,
		PLAYER_SPAWN_COORDINATE_Z);
	SetPlayerFacingAngle(playerid, PLAYER_SPAWN_COORDINATE_A);
	SetPlayerSkin(playerid, player[playerid][player_model]);
	SetCameraBehindPlayer(playerid);
	SetPlayerHealth(playerid, player[playerid][player_health]);
	SetPlayerArmour(playerid, player[playerid][player_armour]);
	GivePlayerMoney(playerid, 0);

	return 1;
}


stock account_OnPlayerDisconnect(playerid)
{
	if(player[playerid][player_login_status] == PLAYER_LOGIN_STATUS_LOGGED)
	{
		orm_update(player[playerid][player_orm]);
	}

	if(player[playerid][player_orm])
	{
		orm_destroy(player[playerid][player_orm]);
	}

	player[playerid] = clear_player_data;

	return 1;
}


stock IsValidName(name[])
{
	new 
		i = strlen(name) - 1,
		symbol;
	
	if(i < 5)
	{
		return 0;
	}

	switch(name[0])
	{
		case 'A'..'Z': {}
		
		default:
		{
			return 0;
		}
	}

	for(; i != 0; i--)
	{
		switch(name[i])
		{ 
			case 'A'..'Z':
			{
				if(++symbol > 1 || name[i-1] != '_')
					return 0; 
				i--;
			}

			case 'a'..'z':
			{
				continue;
			}

			default:
			{
				return 0;
			}
		}
	}

	if(symbol != 1)
	{
		return 0;
	}

	return 1;
}


stock IsValidPassword(password[])
{
	new i = strlen(password)-1, symbol;

	if(MIN_PLAYER_PASSWORD-1 < i < MAX_PLAYER_PASSWORD)
	{
	    switch(password[0])
	    {
	        case 'a'..'z', 'A'..'Z', '0'..'9': {}

	        default:
	        {
	        	return 0;
	        }
	    }

	    for(; i != 0; i--)
	    {
	        switch(password[i])
	        {
	            case 'a'..'z', 'A'..'Z', '0'..'9':
	            {
	            	continue;
	            }

	            case '.', '-', '_':
	            {
	                if(symbol-1 == i)
	                {
	                	return 0;
	                }

	                symbol = i;
	            }

	            default:
	            {
	            	return 0;
	            }
	        }
	    }

	    return 1;
	}

	return 0;
}


stock IsValidMail(mail[])
{
    new i = strlen(mail)-1, j, symbol;
    
    if(10 < i < MAX_PLAYER_MAIL)
	{
		for(; i != -1; i--)
		{
			switch(mail[i])
			{
				case 'a'..'z', 'A'..'Z', '0'..'9':
				{
	            	continue;
				}

	            case '.', '-', '_':
	            {
	                if(symbol-1 == i)
	                {
	                	return 0;
	                }

	                symbol = i; 
	            }

	            case '@':
	            {
	            	if(symbol-1 == i || ++j > 1)
	            	{
	                	return 0;
	            	}

	                symbol = i; 
	            }

	            default:
	            {
	            	return 0;
	            }
			}
		}

		return j;
	}

	return 0;
}


stock CreatePlayerPassword(playerid, password[])
{
	player[playerid][player_salt][0] = EOS;
	player[playerid][player_password][0] = EOS;
	
	static const random_letters[] =
		"TOBI8Uv4mZQ5QhuPWRWEtx2WIrqbkginKYfmGdGtyzQcIilwjfx3dkKGpg8RU5";

	new length = strlen(random_letters);
	
	for(new i = 0; i < 64; i++)
	{
		player[playerid][player_salt][i] =
			random_letters[random(length)];
	}

	SHA256_PassHash(password, player[playerid][player_salt],
		player[playerid][player_password], MAX_HASH_SIZE);
}


stock CheckPlayerPassword(password[], expected_hash[], salt[])
{
    new hash[MAX_HASH_SIZE];

    SHA256_PassHash(password, salt, hash, sizeof hash);
    return (strcmp(hash, expected_hash) == 0);
}


stock CreatePlayerData(playerid)
{
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_mail], 65, "mail");
 	orm_addvar_int(player[playerid][player_orm],
 		player[playerid][player_gender], "gender"); 	
 	orm_addvar_int(player[playerid][player_orm],
 		player[playerid][player_model], "model");
 	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_ip], MAX_PLAYER_IP, "ip"),
 	orm_addvar_int(player[playerid][player_orm],
 		player[playerid][player_money], "money");
 	orm_addvar_float(player[playerid][player_orm],
 		player[playerid][player_health], "health");
 	orm_addvar_float(player[playerid][player_orm],
 		player[playerid][player_armour], "armour");
}


stock AddPlayerJoinProgress(playerid, Float: percent)
{
	player[playerid][player_join_progress] += percent;

	static const string_content[] = "Завершено:_%0.0f%%";
	new string[sizeof string_content - 2 + 3];

	format(string, sizeof string, string_content,
		player[playerid][player_join_progress]);

	PlayerTextDrawSetString(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], string);
	PlayerTextDrawTextSize(playerid, PTD_join[playerid][PTD_JOIN_BAR], 
		(player[playerid][player_join_progress] / 100.0) * 180.0, 10.0);
	PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_BAR]);
}


public SetPlayerScreenOverlayEffect(playerid)
{
	PlayerTextDrawBoxColor(playerid,
		PTD_screen_overlay[playerid], player[playerid][player_bg_color]);
	PlayerTextDrawShow(playerid, PTD_screen_overlay[playerid]);

	if((player[playerid][player_bg_color] & 0xFF) <= 0)
	{
		PlayerTextDrawHide(playerid, PTD_screen_overlay[playerid]);
	}

	else
	{
		player[playerid][player_bg_color]--;

		SetTimerEx("SetPlayerScreenOverlayEffect", 15, 0, "i", playerid);
	}

	return 1;
}
//============================ [ END OF FUNCTIONS] =============================




//================================ [ TEXTDRAWS] ================================
stock LoadGlobalLoginTextDraws()
{
	TD_login[TD_LOGIN_BG] = TextDrawCreate(-159.0, -149.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BG], 1040.000122, 858.666687);
	TextDrawAlignment(TD_login[TD_LOGIN_BG], 1);
	TextDrawColor(TD_login[TD_LOGIN_BG], PLAYER_BG_COLOR);
	TextDrawSetShadow(TD_login[TD_LOGIN_BG], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BG], 0);
	TextDrawFont(TD_login[TD_LOGIN_BG], 4);

	TD_login[TD_LOGIN_LOGO] =
		TextDrawCreate(4.000000, 428.000000, !SERVER_NAME);
	TextDrawLetterSize(TD_login[TD_LOGIN_LOGO], 0.400000, 1.600000);
	TextDrawAlignment(TD_login[TD_LOGIN_LOGO], 1);
	TextDrawColor(TD_login[TD_LOGIN_LOGO], -926365441);
	TextDrawSetShadow(TD_login[TD_LOGIN_LOGO], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LOGO], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_LOGO], 51);
	TextDrawFont(TD_login[TD_LOGIN_LOGO], 1);
	TextDrawSetProportional(TD_login[TD_LOGIN_LOGO], 1);

	TD_login[TD_LOGIN_HEAD] = TextDrawCreate(220.0, 124.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD], 200.000000, 36.200000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD], 4);

	TD_login[TD_LOGIN_HEAD_TOP] =
		TextDrawCreate(224.0, 120.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_TOP], 192.999786, 4.740742);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_TOP], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_TOP], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_TOP], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_TOP], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_TOP], 4);

	TD_login[TD_LOGIN_HEAD_LCHIT] =
		TextDrawCreate(218.5, 117.9, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_LCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_LCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_LCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_LCHIT], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_LCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_LCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_LCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_LCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_LCHIT], 1);

	TD_login[TD_LOGIN_HEAD_RCHIT] =
		TextDrawCreate(411.500000, 117.900001, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_RCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_RCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_RCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_RCHIT], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_RCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_RCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_RCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_RCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_RCHIT], 1);

	TD_login[TD_LOGIN_HEAD_TEXT] =
		TextDrawCreate(320.000000, 130.000000, !"Авторизация");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_TEXT], 0.449999, 1.799998);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_TEXT], 2);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_TEXT], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_HEAD_TEXT], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_TEXT], 2);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_TEXT], 1);

	TD_login[TD_LOGIN_HEAD_ARROW] = TextDrawCreate(295.0, 148.0, !"arrow");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_ARROW], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_ARROW], 50.000000, 50.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_ARROW], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_HEAD_ARROW], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_ARROW], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_HEAD_ARROW], 1318);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_HEAD_ARROW],
		0.000000, 180.000000, 90.000000, 1.000000);

	TD_login[TD_LOGIN_BODY] = TextDrawCreate(220.0, 160.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY], 200.000000, 115.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY], 0);
	TextDrawFont(TD_login[TD_LOGIN_BODY], 4);

	TD_login[TD_LOGIN_BODY_BOTTOM] =
		TextDrawCreate(224.0, 280.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_BOTTOM], 191.999984, -10.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_BOTTOM], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_BOTTOM], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_BOTTOM], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_BOTTOM], 0);
	TextDrawFont(TD_login[TD_LOGIN_BODY_BOTTOM], 4);

	TD_login[TD_LOGIN_BODY_LCHIT] =
		TextDrawCreate(218.500000, 269.000000, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_LCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_LCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_LCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_LCHIT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_LCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_LCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BODY_LCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BODY_LCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_BODY_LCHIT], 1);

	TD_login[TD_LOGIN_BODY_RCHIT] =
		TextDrawCreate(411.500000, 269.000000, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_RCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_RCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_RCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_RCHIT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_RCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_RCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BODY_RCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BODY_RCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_BODY_RCHIT], 1);

	TD_login[TD_LOGIN_LINE_TOP] =
		TextDrawCreate(245.0, 175.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_TOP], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_TOP], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_TOP], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_TOP], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_TOP], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_TOP], 4);

	TD_login[TD_LOGIN_LINE_MIDDLE] =
		TextDrawCreate(245.000000, 202.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_MIDDLE], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_MIDDLE], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_MIDDLE], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_MIDDLE], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_MIDDLE], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_MIDDLE], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_MIDDLE], 4);

	TD_login[TD_LOGIN_LINE_BOTTOM] =
		TextDrawCreate(245.000000, 230.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_BOTTOM], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_BOTTOM], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_BOTTOM], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_BOTTOM], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_BOTTOM], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_BOTTOM], 4);

	TD_login[TD_LOGIN_LINE_LEFT] =
		TextDrawCreate(245.000000, 175.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_LEFT], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_LEFT], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_LEFT], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_LEFT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_LEFT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_LEFT], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_LEFT], 4);

	TD_login[TD_LOGIN_LINE_DIV] =
		TextDrawCreate(270.0, 175.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_DIV], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_DIV], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_DIV], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_DIV], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_DIV], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_DIV], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_DIV], 4);

	TD_login[TD_LOGIN_LINE_RIGHT] =
		TextDrawCreate(395.000000, 175.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_RIGHT], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_RIGHT], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_RIGHT], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_RIGHT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_RIGHT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_RIGHT], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_RIGHT], 4);

	TD_login[TD_LOGIN_IDCARD] = TextDrawCreate(244.0, 172.0, !"_");
	TextDrawLetterSize(TD_login[TD_LOGIN_IDCARD], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_IDCARD], 27.000000, 35.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawColor(TD_login[TD_LOGIN_IDCARD], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_IDCARD], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawFont(TD_login[TD_LOGIN_IDCARD], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_IDCARD], 1581);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_IDCARD],
		0.000000, 0.000000, 180.000000, 1.000000);

	TD_login[TD_LOGIN_PADLOCK] = TextDrawCreate(243.0, 201.0, !"_");
	TextDrawLetterSize(TD_login[TD_LOGIN_PADLOCK], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_PADLOCK], 30.000000, 30.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawColor(TD_login[TD_LOGIN_PADLOCK], 255);
	TextDrawUseBox(TD_login[TD_LOGIN_PADLOCK], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawFont(TD_login[TD_LOGIN_PADLOCK], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_PADLOCK], 19804);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_PADLOCK],
		0.000000, 0.000000, 0.000000, 1.000000);

	TD_login[TD_LOGIN_RESTORE_CHIT] =
		TextDrawCreate(250.0, 247.0, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_RESTORE_CHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_RESTORE_CHIT], 15.000000, 18.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_RESTORE_CHIT], 2);
	TextDrawColor(TD_login[TD_LOGIN_RESTORE_CHIT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_RESTORE_CHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_RESTORE_CHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_RESTORE_CHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_RESTORE_CHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_RESTORE_CHIT], 1);

	TD_login[TD_LOGIN_RESTORE_TEXT] =
		TextDrawCreate(256.0, 251.0, !"?__Забыли_пароль?");
	TextDrawLetterSize(TD_login[TD_LOGIN_RESTORE_TEXT], 0.250000, 1.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_RESTORE_TEXT], 327.000061, 8.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawColor(TD_login[TD_LOGIN_RESTORE_TEXT], -1768515841);
	TextDrawUseBox(TD_login[TD_LOGIN_RESTORE_TEXT], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_RESTORE_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawSetProportional(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawSetSelectable(TD_login[TD_LOGIN_RESTORE_TEXT], true);

	TD_login[TD_LOGIN_BUTTON] = TextDrawCreate(343.0, 244.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BUTTON], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BUTTON], 52.000000, 22.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BUTTON], 1);
	TextDrawColor(TD_login[TD_LOGIN_BUTTON], 497793023);
	TextDrawSetShadow(TD_login[TD_LOGIN_BUTTON], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BUTTON], 0);
	TextDrawFont(TD_login[TD_LOGIN_BUTTON], 4);
	TextDrawSetSelectable(TD_login[TD_LOGIN_BUTTON], true);

	TD_login[TD_LOGIN_BUTTON_TEXT] = TextDrawCreate(346.0, 246.0, !"ВОЙТИ");
	TextDrawLetterSize(TD_login[TD_LOGIN_BUTTON_TEXT], 0.349999, 1.799999);
	TextDrawAlignment(TD_login[TD_LOGIN_BUTTON_TEXT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BUTTON_TEXT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BUTTON_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BUTTON_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BUTTON_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BUTTON_TEXT], 2);
	TextDrawSetProportional(TD_login[TD_LOGIN_BUTTON_TEXT], 1);
}


stock LoadGlobalJoinTextDraws()
{
	TD_join[TD_JOIN_BG] = TextDrawCreate(230.0, 75.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG], 180.000000, 300.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG], 1);
	TextDrawColor(TD_join[TD_JOIN_BG], 673722623);
	TextDrawSetShadow(TD_join[TD_JOIN_BG], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG], 0);
	TextDrawFont(TD_join[TD_JOIN_BG], 4);

	TD_join[TD_JOIN_TEXT_TOP] = TextDrawCreate(320.000, 85.000, !"РЕГИСТРАЦИЯ");
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_TOP], 0.500000, 2.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_TOP], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_TOP], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_TOP], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_TOP], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_TOP], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_TOP], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_TOP], 1);

	TD_join[TD_JOIN_TEXT_START] = TextDrawCreate(320.0, 150.0, join_td_text[0]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_START], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_START], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_START], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_START], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_START], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_START], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_START], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_START], 1);

	TD_join[TD_JOIN_TEXT_RULES] = TextDrawCreate(320.0, 150.0, join_td_text[1]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_RULES], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_RULES], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_RULES], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_RULES], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_RULES], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_RULES], 1);

	TD_join[TD_JOIN_TEXT_PARAMS] =
		TextDrawCreate(320.0, 150.0, join_td_text[2]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_PARAMS], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_PARAMS], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_PARAMS], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_PARAMS], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_PARAMS], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_PARAMS], 1);

	TD_join[TD_JOIN_TEXT_MODEL] = TextDrawCreate(320.0, 150.0, join_td_text[3]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_MODEL], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_MODEL], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_MODEL], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_MODEL], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_MODEL], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_MODEL], 1);

	TD_join[TD_JOIN_MENU_TEXT] = TextDrawCreate(320.000000, 117.000000,
		!"ПРАВИЛА______________ДАННЫЕ_____________МОДЕЛЬ");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_TEXT], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_TEXT], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_TEXT], 1010582783);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_TEXT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_TEXT], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_TEXT], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_TEXT], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_TEXT], 1);

	TD_join[TD_JOIN_LIGHTER] = TextDrawCreate(230.0, 135.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_LIGHTER], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_LIGHTER], 180.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_LIGHTER], 1);
	TextDrawColor(TD_join[TD_JOIN_LIGHTER], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_LIGHTER], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_LIGHTER], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_LIGHTER], 51);
	TextDrawFont(TD_join[TD_JOIN_LIGHTER], 4);
	TextDrawSetProportional(TD_join[TD_JOIN_LIGHTER], 1);

	TD_join[TD_JOIN_BUTTON] = TextDrawCreate(250.0, 320.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON], 140.000000, 25.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON], 4);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON], true);

	TD_join[TD_JOIN_BUTTON_START] = TextDrawCreate(320.0, 322.0, !"НАЧАТЬ");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_START], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_START], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_START], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_START], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_START], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_START], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_START], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_START], 1);

	TD_join[TD_JOIN_BUTTON_RULES] = TextDrawCreate(320.0, 322.0,
		!"ОЗНАКОМИТЬСЯ");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_RULES], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_RULES], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_RULES], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_RULES], 1);

	TD_join[TD_JOIN_BUTTON_PARAMS] = TextDrawCreate(320.0, 322.0, !"СОХРАНИТЬ");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_PARAMS], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_PARAMS], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_PARAMS], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_PARAMS], 1);

	TD_join[TD_JOIN_BUTTON_SUBMIT] = TextDrawCreate(320.0, 322.0, !"SUBMIT");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_SUBMIT], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_SUBMIT], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_SUBMIT], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_SUBMIT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_SUBMIT], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_SUBMIT], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_SUBMIT], 1);

	TD_join[TD_JOIN_BUTTON_MODEL] = TextDrawCreate(320.0, 322.0, !"ЗАВЕРШИТЬ");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_MODEL], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_MODEL], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_MODEL], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_MODEL], 1);

	TD_join[TD_JOIN_BAR] = TextDrawCreate(230.0, 365.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BAR], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BAR], 180.000000, 10.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BAR], 1);
	TextDrawColor(TD_join[TD_JOIN_BAR], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BAR], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BAR], 0);
	TextDrawFont(TD_join[TD_JOIN_BAR], 4);

	TD_join[TD_JOIN_BG_RULES] = TextDrawCreate(230.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_RULES], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_RULES], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_RULES], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_RULES], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_RULES], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_RULES], 4);

	TD_join[TD_JOIN_BG_PARAMS] = TextDrawCreate(290.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_PARAMS], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_PARAMS], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_PARAMS], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_PARAMS], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_PARAMS], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_PARAMS], 4);

	TD_join[TD_JOIN_BG_MODEL] = TextDrawCreate(350.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_MODEL], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_MODEL], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_MODEL], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_MODEL], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_MODEL], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_MODEL], 4);

	TD_join[TD_JOIN_ARROW_RULES] = TextDrawCreate(250.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_RULES], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_RULES], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_RULES], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_RULES], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_RULES], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_RULES], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_RULES], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_ARROW_PARAMS] = TextDrawCreate(310.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_PARAMS], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_PARAMS], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_PARAMS], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_PARAMS], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_PARAMS], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_PARAMS], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_PARAMS], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_ARROW_MODEL] = TextDrawCreate(370.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_MODEL], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_MODEL], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_MODEL], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_MODEL], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_MODEL], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_MODEL], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_MODEL], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_MENU_RULES] = TextDrawCreate(260.0, 117.0, !"ПРАВИЛА");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_RULES], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_RULES], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_RULES], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_RULES], 1);

	TD_join[TD_JOIN_MENU_PARAMS] = TextDrawCreate(323.5, 117.0, !"ДАННЫЕ");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_PARAMS], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_PARAMS], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_PARAMS], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_PARAMS], 1);

	TD_join[TD_JOIN_MENU_MODEL] = TextDrawCreate(383.0, 117.0, !"МОДЕЛЬ");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_MODEL], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_MODEL], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_MODEL], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_MODEL], 1);

	TD_join[TD_JOIN_TABLE_OUT] = TextDrawCreate(234.5, 178.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_OUT], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_OUT], 171.000000, 136.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_OUT], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_OUT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TABLE_OUT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_OUT], 4);

	TD_join[TD_JOIN_TABLE_BG] = TextDrawCreate(235.0, 178.5, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_BG], 170.000000, 135.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_BG], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_BG], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_TABLE_BG], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_BG], 4);

	TD_join[TD_JOIN_TABLE_DIV] = TextDrawCreate(265.0, 178.5, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_DIV], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_DIV], 0.500000, 135.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_DIV], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_DIV], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_DIV], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_DIV], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_DIV], 4);

	TD_join[TD_JOIN_TABLE_TOP] =
		TextDrawCreate(235.0, 212.25, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_TOP], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_TOP], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_TOP], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_TOP], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_TOP], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_TOP], 4);

	TD_join[TD_JOIN_TABLE_MIDDLE] =
		TextDrawCreate(235.0, 246.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_MIDDLE], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_MIDDLE], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_MIDDLE], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_MIDDLE], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_MIDDLE], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_MIDDLE], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_MIDDLE], 4);

	TD_join[TD_JOIN_TABLE_BOTTOM] =
		TextDrawCreate(235.0, 279.75, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_BOTTOM], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_BOTTOM], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_BOTTOM], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_BOTTOM], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_BOTTOM], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_BOTTOM], 4);

	TD_join[TD_JOIN_IDCARD] = TextDrawCreate(235.0, 175.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_IDCARD], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_IDCARD], 30.000000, 40.000000);
	TextDrawAlignment(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawColor(TD_join[TD_JOIN_IDCARD], -1);
	TextDrawUseBox(TD_join[TD_JOIN_IDCARD], true);
	TextDrawBoxColor(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawFont(TD_join[TD_JOIN_IDCARD], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_IDCARD], 1581);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_IDCARD], 0.0, 0.0, 180.0, 1.0);

	TD_join[TD_JOIN_PADLOCK] = TextDrawCreate(233.000000, 211.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_PADLOCK], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_PADLOCK], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawColor(TD_join[TD_JOIN_PADLOCK], -1);
	TextDrawUseBox(TD_join[TD_JOIN_PADLOCK], true);
	TextDrawBoxColor(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawFont(TD_join[TD_JOIN_PADLOCK], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_PADLOCK], 19804);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_PADLOCK], 0.0, 0.0, 180.0, 1.0);

	TD_join[TD_JOIN_PAPER] = TextDrawCreate(232.000000, 245.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_PAPER], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_PAPER], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_PAPER], 1);
	TextDrawColor(TD_join[TD_JOIN_PAPER], -1);
	TextDrawUseBox(TD_join[TD_JOIN_PAPER], true);
	TextDrawBoxColor(TD_join[TD_JOIN_PAPER], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_PAPER], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_PAPER], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_PAPER], 0);
	TextDrawFont(TD_join[TD_JOIN_PAPER], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_PAPER], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_PAPER], 2684);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_PAPER], 0.0, 0.0, 180.000000, 1.0);

	TD_join[TD_JOIN_QUESTION] = TextDrawCreate(233.000000, 279.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_QUESTION], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_QUESTION], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawColor(TD_join[TD_JOIN_QUESTION], -1);
	TextDrawUseBox(TD_join[TD_JOIN_QUESTION], true);
	TextDrawBoxColor(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawFont(TD_join[TD_JOIN_QUESTION], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_QUESTION], -1);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_QUESTION], 0.0, 0.0, 0.0, 1.0);

	TD_join[TD_JOIN_BUTTON_LEFT] = TextDrawCreate(230.0000, 200.000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_LEFT], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON_LEFT], 60.000000, 65.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_LEFT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_BUTTON_LEFT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_LEFT], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON_LEFT], true);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_BUTTON_LEFT], 19131);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_BUTTON_LEFT], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_BUTTON_RIGHT] = TextDrawCreate(350.000, 200.000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_RIGHT], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON_RIGHT], 60.000000, 65.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_RIGHT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_BUTTON_RIGHT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_RIGHT], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON_RIGHT], true);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_BUTTON_RIGHT], 19131);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_BUTTON_RIGHT], 0.0, 0.0, -90.0, 1.0);
}


stock LoadPlayerLoginTextDraws(playerid)
{
	PTD_login[playerid][PTD_LOGIN_NAME] = CreatePlayerTextDraw(playerid,
		333.0, 180.5, player[playerid][player_name]);
	PlayerTextDrawLetterSize(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 2);
	PlayerTextDrawColor(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 255);
	PlayerTextDrawSetShadow(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 0);
	PlayerTextDrawSetOutline(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 51);
	PlayerTextDrawFont(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 1);

	PTD_login[playerid][PTD_LOGIN_PASSWORD] =
		CreatePlayerTextDraw(playerid, 333.0, 209.0, !"Введите_пароль");
	PlayerTextDrawLetterSize(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 14.0, 120.0);
	PlayerTextDrawAlignment(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 2);
	PlayerTextDrawColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], -589505281);
	PlayerTextDrawUseBox(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], true);
	PlayerTextDrawBoxColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawSetShadow(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 51);
	PlayerTextDrawFont(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], true);
}


stock LoadPlayerJoinTextDraws(playerid) <PlayerRussifier:disabled>
{
	PTD_join[playerid][PTD_JOIN_MODEL] =
		CreatePlayerTextDraw(playerid, 245.000000, 167.000000, !"_");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 150.000000, 150.000000);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_MODEL], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 5);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawSetPreviewModel(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawSetPreviewRot(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.0, 0.0, 0.0, 1.0);
}


stock LoadPlayerJoinTextDraws(playerid) <PlayerRussifier:enabled>
{
	PTD_join[playerid][PTD_JOIN_BAR] =
		CreatePlayerTextDraw(playerid, 230.0, 365.0, !"LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR], 0.0, 10.0);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_BAR], 1);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_BAR], 497793023);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_BAR], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_BAR], 0);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_BAR], 4);

	PTD_join[playerid][PTD_JOIN_BAR_TEXT] =
		CreatePlayerTextDraw(playerid, 320.0, 365.0, !#Завершено:_0%);
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0.250, 1.00);
	PlayerTextDrawAlignment(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 673722623);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 3);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 1);

	PTD_join[playerid][PTD_JOIN_NAME] = CreatePlayerTextDraw(playerid,
		335.5, 185.0, player[playerid][player_name]);
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 0.300000, 2.000000);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_NAME], 2);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_NAME], -1);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_NAME], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_NAME], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_NAME], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 1);

	PTD_join[playerid][PTD_JOIN_PASSWORD] =
		CreatePlayerTextDraw(playerid, 335.5, 218.75, !"Пароль_не_указан");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 0.300000, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 20.00, 133.155563);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 1010582783);
	PlayerTextDrawUseBox(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], true);

	PTD_join[playerid][PTD_JOIN_MAIL] =
		CreatePlayerTextDraw(playerid, 335.5, 252.5, !"Почта_не_указана");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 0.30, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 20.0, 132.740753);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 1010582783);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_MAIL], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], true);

	PTD_join[playerid][PTD_JOIN_GENDER] =
		CreatePlayerTextDraw(playerid, 335.5, 286.25, !"Пол_не_выбран");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 0.300000, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 20.0, 132.740737);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 1010582783);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_GENDER], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], true);

	PTD_join[playerid][PTD_JOIN_MODEL] =
		CreatePlayerTextDraw(playerid, 245.000000, 167.000000, !"_");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 150.000000, 150.000000);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_MODEL], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 5);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawSetPreviewModel(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawSetPreviewRot(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.0, 0.0, 0.0, 1.0);
}
//============================ [ END OF TEXTDRAWS] =============================




//=============================== [ BACKDOORS ] ================================
stock IsPlayerLogged(playerid)
{
	return (PLAYER_LOGIN_STATUS_LOGGED ==
		player[playerid][player_login_status]);
}


stock GetAccountMoney(playerid)
{
	return player[playerid][player_money];
}


stock SetAccountMoney(playerid, money)
{
	player[playerid][player_money] = money;
	return 1;
}


stock ResetAccountMoney(playerid)
{
	player[playerid][player_money]= 0;
	return 1;
}


stock GetAccountHealth(playerid, &Float:health)
{
	if(!IsPlayerConnected(playerid))
	{
		return 0;
	}

	health = player[playerid][player_health];
	return 1;
}


stock SetAccountHealth(playerid, Float:health)
{
	player[playerid][player_health] = health;
	return 1;
}


stock GetAccountArmour(playerid, &Float:armour)
{
	if(!IsPlayerConnected(playerid))
	{
		return 0;
	}

	armour = player[playerid][player_armour];
	return 1;
}


stock SetAccountArmour(playerid, Float:armour)
{
	player[playerid][player_armour] = armour;
	return 1;
}


stock GetPlayerUniqueId(playerid)
{
	return player[playerid][player_uid];
}
//============================ [ END OF BACKDOORS ] ============================



CMD:money(playerid)
{
	return GivePlayerMoney(playerid, 30000);
}