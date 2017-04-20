forward CheckPlayerIp(playerid);
forward CheckPlayerAccount(playerid);
forward CheckPlayerJoinMail(playerid);
forward OnActivationCodeRecived(playerid, response_code, data[]);
forward OnPlayerJoin(playerid);
forward OnPlayerLogin(playerid);
forward SetPlayerScreenOverlayEffect(playerid);

public CheckPlayerIp(playerid)
{
	new rows;

	cache_get_row_count(rows);
	
	if(rows)
	{
		new last_connect;
		cache_get_value_name_int(0, "last_connect", last_connect);
		
		if(gettime() - last_connect < RECONNECT_INTERVAL)
		{
			return Kick(playerid, KICK_TEXT_REASON"\
				Переподключаться к серверу можно раз в \
				"#RECONNECT_INTERVAL" секунд"KICK_TEXT_TIP);
		}
	}

	SetPlayerCameraPos(playerid, 2126.858886, 1927.597412, 27.284200);
	SetPlayerCameraLookAt(playerid, 2122.229492, 1925.711791, 27.170928);
	ClearPlayerChat(playerid);
	OnPlayerConnected(playerid);
	return 1;
}


public CheckPlayerAccount(playerid)
{
	player[playerid][player_login_status] = PLAYER_LOGIN_STATUS_CONNECTED;

	SelectTextDraw(playerid, 0x2c3e50FF);

	if(orm_errno(player[playerid][player_orm]) == ERROR_OK)
	{
		LoadPlayerLoginTextDraws(playerid);

		for(new TD_LOGIN_INFO: i; i < TD_LOGIN_INFO; i++) 
		{ 
			TextDrawShowForPlayer(playerid, TD_login[i]); 
		}

		for(new PTD_LOGIN_INFO: i; i < PTD_LOGIN_INFO; i++)
		{
			PlayerTextDrawShow(playerid, PTD_login[playerid][i]);
		}
	}

	else
	{
		player[playerid][player_join_status] = PLAYER_JOIN_STATUS_START;
		player[playerid][player_gender] = -1;

		LoadPlayerJoinTextDraws(playerid);
		UpdatePlayerJoinTextDraws(playerid);
	}

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


stock OnPlayerConnected(playerid)
{
	player[playerid][player_orm] = orm_create("accounts");
	
	orm_addvar_int(player[playerid][player_orm],
		player[playerid][player_uid], "uid");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_name], MAX_PLAYER_NAME, "name");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_password], 65, "password");
	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_salt], 65, "salt");
 	orm_addvar_string(player[playerid][player_orm],
		player[playerid][player_ip], MAX_PLAYER_IP, "ip");
	orm_setkey(player[playerid][player_orm], "name");
	orm_select(player[playerid][player_orm],
		"CheckPlayerAccount", "i", playerid);
}


stock UpdatePlayerLastConnection(playerid)
{
	static query_content[] = "INSERT INTO`ip_list`(`ip`,`last_connect`)\
		VALUES('%s','%d')ON DUPLICATE KEY UPDATE`last_connect`='%d'";
	new query[sizeof query_content - 2 + MAX_PLAYER_IP - 2 + 10 - 2 + 10],
		time = gettime();

	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		player[playerid][player_ip], time, time);
	mysql_tquery(mysql_connection_id, query);
}


stock SavePlayerData(playerid)
{
	if(player[playerid][player_login_status] == PLAYER_LOGIN_STATUS_LOGGED)
	{
		orm_save(player[playerid][player_orm]);
		orm_destroy(player[playerid][player_orm]);
	}
}


stock UpdatePlayerJoinTextDraws(playerid)
{
	switch(player[playerid][player_join_status])
	{
		case PLAYER_JOIN_STATUS_START:
		{
			TextDrawShowForPlayer(playerid, TD_login[TD_LOGIN_BG]);
			TextDrawShowForPlayer(playerid, TD_login[TD_LOGIN_LOGO]);

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
			PlayerTextDrawHide(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD]);
			PlayerTextDrawHide(playerid, PTD_join[playerid][PTD_JOIN_MAIL]);
			PlayerTextDrawHide(playerid, PTD_join[playerid][PTD_JOIN_GENDER]);

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


stock IsValidPassword(password[])
{
	new i = strlen(password)-1, symbol;

	if(MIN_PLAYER_PASSWORD < i < MAX_PLAYER_PASSWORD)
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
		player[playerid][player_password], 65);
	return 1;
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


public CheckPlayerJoinMail(playerid)
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
{
	if(200 != response_code)
	{
		return Kick(playerid, !COLOR_ERROR"Вы были отсоединены от сервера\n\
			Причина: "COLOR_TITLE"Не удалось отправить письмо с кодом для \
			подтверждения\nВозникла не известная ошибка\n\n\
			"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)");
	}

	Dialog_Open(playerid, Dialog:join_activation, DIALOG_STYLE_INPUT,
        !COLOR_TITLE"Подтверждения почты",
        join_text[6],
        !"Принять", !"Отмена");
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
		orm_load(player[playerid][player_orm], "OnPlayerLogin", "i", playerid);
	}

	else
	{
		Kick(playerid, KICK_TEXT_REASON"Не удалось создать новый аккаунт в \
			базе данных.\nПроизошла неизвестная ошибка!"KICK_TEXT_TIP);
	}

	return 1;
}


public OnPlayerLogin(playerid)
{
	if(orm_errno(player[playerid][player_orm]) == ERROR_OK)
	{
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
			PLAYER_SPAWN_COORDINATES, 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, 0);
	}

	else
	{
		Kick(playerid, KICK_TEXT_REASON"Не удалось загрузить Ваш аккаунт.\
			\nПроизошла неизвестная ошибка!"KICK_TEXT_TIP);
	}

	return 1;
}


stock CheckPassword(password[], expected_hash[], salt[])
{
    new hash[64 + 1];

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