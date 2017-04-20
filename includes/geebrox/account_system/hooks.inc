public OnGameModeInit()
{
	new result = 1;

	#if defined account_OnGameModeInit
		result = account_OnGameModeInit();
	#endif

	LoadGlobalLoginTextDraws();

	for(new i, j; i < sizeof player_models; i++)
	{
		j = 0;
		
		while(player_models[i][j] != -1)
		{
			j++;
		}
		
		player_models_size[i] = j;
	}

	return result;
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit account_OnGameModeInit
#if defined account_OnGameModeInit
	forward account_OnGameModeInit();
#endif


public OnPlayerConnect(playerid)
{
    TogglePlayerSpectating(playerid, 1);

	new result = 1;

	#if defined account_OnPlayerConnect
		result = account_OnPlayerConnect(playerid);
	#endif

	player[playerid] = clear_player_data;

	GetPlayerName(playerid, player[playerid][player_name], MAX_PLAYER_NAME);

	if(!IsValidName(player[playerid][player_name]))
    {
		return Kick(playerid, KICK_TEXT_REASON"\
			Ваше имя не соответствует RP правилам\n\
			Пример правильной имени: \
			"COLOR_SUCCESS"John_Smith\n\n"KICK_TEXT_TIP);
    }

    GetPlayerIp(playerid, player[playerid][player_ip], MAX_PLAYER_IP);
    
    static query_content[] = "SELECT*FROM`ip_list`WHERE`ip`LIKE'%s'";
	new query[sizeof query_content - 2 + MAX_PLAYER_IP];
	
	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		player[playerid][player_ip]);
	mysql_tquery(mysql_connection_id, query, "CheckPlayerIp", "i", playerid);

	return result;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect account_OnPlayerConnect
#if defined account_OnPlayerConnect
	forward account_OnPlayerConnect(playerid);
#endif


public OnPlayerDisconnect(playerid, reason)
{
	new result = 1;

	#if defined account_OnPlayerDisconnect
		result = account_OnPlayerDisconnect(playerid, reason);
	#endif

	if(player[playerid][player_login_status] >= PLAYER_LOGIN_STATUS_CONNECTED)
	{
		UpdatePlayerLastConnection(playerid);
		SavePlayerData(playerid);
	}

	return result;
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect account_OnPlayerDisconnect
#if defined account_OnPlayerDisconnect
	forward account_OnPlayerDisconnect(playerid, reason);
#endif


public OnPlayerClickTextDraw(playerid, Text:clickedid)
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
		if(player[playerid][player_login_password][0] == EOS)
		{
			return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
				!COLOR_ERROR"Введите пароль от аккаунта!",
				!"Закрыть");
		}

		else if(CheckPassword(player[playerid][player_login_password],
			player[playerid][player_password], player[playerid][player_salt]))
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
		 		"OnPlayerLogin", "i", playerid);
			return 1;
		}

		if(++player[playerid][player_login_attempts] > 4)
		{
			return Kick(playerid, KICK_TEXT_REASON"\
				Вы исчерпали все попытки ввода пароля!"KICK_TEXT_TIP);
		}

		static const
			attempt_color[][] =
			{
				COLOR_ERROR,
				COLOR_NOTE,
				COLOR_SUCCESS
				
			},

			string_content[] = COLOR_ERROR"Неверный пароль!\n\
				"COLOR_TEXT"Попыток ввода пароля осталось: %s%d";

		new string[sizeof string_content - 2 + sizeof attempt_color[] - 2 + 1];

		format(string, sizeof string, string_content,
			attempt_color[sizeof attempt_color -
				player[playerid][player_login_attempts]],
			4 - player[playerid][player_login_attempts]);

		return Dialog_Message(playerid, !COLOR_TITLE"Ошибка",
			string, !"Закрыть");
	}

	#if defined account_OnPlayerClickTextdraw
		return account_OnPlayerClickTextdraw(playerid, Text:clickedid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextdraw
	#undef OnPlayerClickTextdraw
#else
	#define _ALS_OnPlayerClickTextdraw
#endif
#define OnPlayerClickTextdraw account_OnPlayerClickTextdraw
#if defined account_OnPlayerClickTextdraw
	forward account_OnPlayerClickTextdraw(playerid, Text:clickedid);
#endif


public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(playertextid == PTD_join[playerid][PTD_JOIN_PASSWORD])
	{
		Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[4],
	        !"Принять", !"Отмена");
	}

	else if(playertextid == PTD_join[playerid][PTD_JOIN_MAIL])
	{
		Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[5],
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
		Dialog_Open(playerid, Dialog:login_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Авторизация | Пароль",
	        !COLOR_TEXT"Введите пароль от вашего аккаунта",
	        !"Принять",
	        !"Отмена");
	}

	#if defined account_OnPlayerClickPlayerText
		return account_OnPlayerClickPlayerText(playerid, playertextid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTextDra
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTextDra
#endif
#define OnPlayerClickPlayerTextDraw account_OnPlayerClickPlayerText
#if defined account_OnPlayerClickPlayerText
	forward account_OnPlayerClickPlayerText(playerid,
		PlayerText:playertextid);
#endif


public OnPlayerSpawn(playerid)
{
	if(player[playerid][player_login_status] != PLAYER_LOGIN_STATUS_LOGGED)
	{
		return Kick(playerid, KICK_TEXT_REASON"\
			Необходимо авторизоваться!"KICK_TEXT_TIP);
	}

	#if defined account_OnPlayerSpawn
		return account_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn account_OnPlayerSpawn
#if defined account_OnPlayerSpawn
	forward account_OnPlayerSpawn(playerid);
#endif