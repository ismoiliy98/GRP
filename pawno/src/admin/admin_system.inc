#if defined _admin_system_included
	#endinput
#endif
#define _admin_system_included


forward CheckPlayerForAdmin(playerid);
forward LoadAdminData(playerid);


enum ADMIN_DATA
{
	ORM:admin_orm,
	admin_uid,
	admin_password[MAX_HASH_SIZE],
	admin_salt[MAX_HASH_SIZE],
	admin_login_attempts,
	admin_level,
	admin_bans,
	admin_banned_ips,
	admin_offline_bans,
	admin_unbans,
	admin_unbanned_ips,
	admin_offline_unbans,
	admin_kicks,
	admin_given_money,
	admin_created_vehicles,
	admin_chat_clears,
	bool:admin_logged
};


new 
	admin[MAX_PLAYERS][ADMIN_DATA],
	clear_admin_data[ADMIN_DATA]
	#if defined _foreach_included
		,
		Iterator:Admin<MAX_PLAYERS>;
	#else
		;
	#endif

new admin_ranks[][] =
{
	"",
	"Мл. Модератор",
	"Модератор",
	"Мл. Администратор",
	"Администратор",
	"Гл. Администратор",
	"Зам. Основателя",
	"Основатель"
};


stock admin_OnPlayerLogin(playerid)
{
	admin[playerid][admin_uid] = GetPlayerUniqueId(playerid);

	admin[playerid][admin_orm] = orm_create("admins");
	
	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_uid], "uid");

	orm_addvar_string(admin[playerid][admin_orm],
		admin[playerid][admin_password], MAX_HASH_SIZE, "password");

	orm_addvar_string(admin[playerid][admin_orm],
		admin[playerid][admin_salt], MAX_HASH_SIZE, "salt");

	orm_setkey(admin[playerid][admin_orm], "uid");

	orm_select(admin[playerid][admin_orm],
		"CheckPlayerForAdmin", "i", playerid);

	return 1;
}


public CheckPlayerForAdmin(playerid)
{
	if(orm_errno(admin[playerid][admin_orm]) == ERROR_OK)
	{
		admin[playerid][admin_login_attempts] = MAX_ADMIN_LOGIN_ATTEMPTS;
		Dialog_Show(playerid, Dialog:admin_login);
	}

	return 1;
}


DialogCreate:admin_login(playerid)
{
	static const string_content[] = !COLOR_TEXT"Введите ваш административный \
		пароль\nПопыток ввода пароля осталось: ";

	new
		attempts[2],
		string[sizeof string_content + sizeof attempts + 8];

	itos(admin[playerid][admin_login_attempts], attempts);
	strcat(string, string_content);
	strcat(string, !COLOR_ERROR);
	strcat(string, attempts);

	Dialog_Open(playerid, Dialog:admin_login, DIALOG_STYLE_PASSWORD,
        !COLOR_TITLE"Администратирование | Авторизация",
        string,
        !"Принять", !"Выйти");
}


DialogResponse:admin_login(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		return Kick(playerid);
	}

	else if(!strlen(inputtext))
	{
		return Dialog_Show(playerid, Dialog:admin_login);
	}

	else if(!CheckAdminPassword(inputtext,
		admin[playerid][admin_password], admin[playerid][admin_salt]))
	{
		admin[playerid][admin_login_attempts]--;

		if(admin[playerid][admin_login_attempts] <= 0)
		{
			return Kick(playerid, KICK_TEXT_REASON"Вы исчерпали все попытки \
				ввода пароля!"KICK_TEXT_TIP);
		}

		return Dialog_Show(playerid, Dialog:admin_login);
	}

	CreateAdminData(playerid);
 	orm_select(admin[playerid][admin_orm], "LoadAdminData", "i", playerid);
	return 1;
}


stock CheckAdminPassword(password[], expected_hash[], salt[])
{
    new hash[MAX_HASH_SIZE];

    SHA256_PassHash(password, salt, hash, sizeof hash);
    return (strcmp(hash, expected_hash) == 0);
}


stock CreateAdminData(playerid)
{
	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_level], "level");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_bans], "bans");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_banned_ips], "banned_ips");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_offline_bans], "offline_bans");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_unbans], "unbans");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_unbanned_ips], "unbanned_ips");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_offline_unbans], "offline_unbans");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_kicks], "kicks");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_given_money], "given_money");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_created_vehicles], "created_vehicles");

	orm_addvar_int(admin[playerid][admin_orm],
		admin[playerid][admin_chat_clears], "chat_clears");
}


public LoadAdminData(playerid)
{
	if(orm_errno(admin[playerid][admin_orm]) == ERROR_OK)
	{
		static const string_content[] =
			!COLOR_ADMIN_NOTE" авторизовался!";
		new string[sizeof string_content + MAX_PLAYER_NAME +
			MAX_ADMIN_RANK_LENGTH + 1 + 24];

		strcat(string, admin_ranks[admin[playerid][admin_level]]);
		strcat(string, !" "COLOR_ERROR);
		strcat(string, player[playerid][player_name]);
		strcat(string, string_content);

		SendAdminMessage(string);
		SendClientMessage(playerid, HEX_COLOR_SUCCESS, !"Авторизация прошла \
			успешно!");

		#if defined _foreach_included
			Iter_Add(Admin, playerid);
		#endif
		admin[playerid][admin_logged] = true;
	}

	else
	{
		return Kick(playerid, KICK_TEXT_REASON"Не удалось \
			загрузить данные из базы.\n\
			Произошла неизвестная ошибка!"KICK_TEXT_TIP);
	}

	return 1;
}


stock SendAdminMessage(message[])
{

#if defined _foreach_included	
	foreach(Admin, i)
	{
		SendClientMessage(i, HEX_COLOR_ADMIN_NOTE, message);
	}
#else
	for(new i = 0; i < GetPlayerPoolSize(); i++)
	{
		if(admin[i][admin_logged])
		{
			SendClientMessage(i, HEX_COLOR_ADMIN_NOTE, message);
		}
	}
#endif

}


stock admin_OnPlayerDisconnect(playerid)
{
	#if defined _foreach_included
		Iter_Remove(Admin, playerid);
	#endif

	static const string_content[] =
		!COLOR_ADMIN_NOTE" деавторизовался!";
	new string[sizeof string_content + MAX_PLAYER_NAME +
		MAX_ADMIN_RANK_LENGTH + 1 + 24];

	strcat(string, admin_ranks[admin[playerid][admin_level]]);
	strcat(string, !" "COLOR_ERROR);
	strcat(string, player[playerid][player_name]);
	strcat(string, string_content);
	SendAdminMessage(string);

	if(admin[playerid][admin_orm])
	{
		if(admin[playerid][admin_logged])
		{
			orm_update(admin[playerid][admin_orm]);
		}

		orm_destroy(admin[playerid][admin_orm]);
	}

	admin[playerid] = clear_admin_data;
	return 1;
}