DialogCreate:join_rules(playerid)
{
	new rules_list = GetPVarInt(playerid, !"server_rules_list");

	Dialog_Open(playerid, Dialog:join_rules, DIALOG_STYLE_MSGBOX,
        !COLOR_TITLE"Правила сервера",
        server_rules[rules_list-1],
        ++rules_list == sizeof server_rules ? !"Принять" : !"Далее",
        !rules_list ? !"Закрыть" : !"Назад");
}


DialogResponse:join_rules(playerid, response, listitem, inputtext[])
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


DialogResponse:join_password(playerid, response, listitem, password[])
{
	if(!response)
	{
		return 1;
	}

	else if(!IsValidPassword(password))
	{
		return Dialog_Open(playerid, Dialog:join_password, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Пароль для аккаунта",
	        join_text[4],
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
{
	if(!response)
	{
		return 1;
	}

	else if(!IsValidMail(inputtext))
	{
		return Dialog_Open(playerid, Dialog:join_mail, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Электронная почта",
	        join_text[5],
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
	
	static query_content[] = "SELECT`mail`FROM`accounts`WHERE`mail`='%s'";
	
	new query[sizeof query_content - 2 + MAX_PLAYER_MAIL];
	
	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		player[playerid][player_mail]);
	mysql_tquery(mysql_connection_id, query,
		"CheckPlayerJoinMail", "i", playerid);
	return 1;
}


DialogResponse:join_activation(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		reset_player_join_mail:
		AddPlayerJoinProgress(playerid, -10.0);
		player[playerid][player_mail][0] = EOS;
		return 1;
	}

	new activation_code = strval(inputtext);

	if(activation_code < 1000)
	{
		return Dialog_Open(playerid, Dialog:join_activation, DIALOG_STYLE_INPUT,
	        !COLOR_TITLE"Подтверждения почты",
	        join_text[6],
	        !"Принять", !"Отмена");
	}

	else if(activation_code != GetPVarInt(playerid, !"activation_code"))
	{
		Dialog_Message(playerid,
			!COLOR_TITLE"Ошибка",
			!COLOR_ERROR"Неверный код подтверждения!",
			!"Закрыть");
		goto reset_player_join_mail;
	}

	AddPlayerJoinProgress(playerid, 10.0);

	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_MAIL], -1);
	PlayerTextDrawSetString(playerid, PTD_join[playerid][PTD_JOIN_MAIL],
		player[playerid][player_mail]);
	PlayerTextDrawShow(playerid, PTD_join[playerid][PTD_JOIN_MAIL]);
	return 1;
}


DialogResponse:join_gender(playerid, response, listitem, inputtext[])
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


DialogResponse:login_password(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		PlayerTextDrawColor(playerid,
			PTD_login[playerid][PTD_LOGIN_PASSWORD], 255);
		PlayerTextDrawSetString(playerid,
			PTD_login[playerid][PTD_LOGIN_PASSWORD], inputtext);
		PlayerTextDrawShow(playerid, PTD_login[playerid][PTD_LOGIN_PASSWORD]);

		strmid(player[playerid][player_login_password], inputtext,
			0, strlen(inputtext), MAX_PLAYER_PASSWORD);
	}

	return 1;
}