#define CheckAdminLevel(%0,%1) \
	if(0 < admin[%0][admin_level] < %1) return CMD_RTN_NO_PERMISSIONS;\
	else if(!admin[%0][admin_level]) return CMD_RTN_INVALID_COMMAND


CMD:admin(adminid, params[])
{
	CheckAdminLevel(adminid, CMD_admin);
	if(isnull(params))
	{
		return SendClientMessage(adminid, HEX_COLOR_ERROR,
			!"Используйте: /a(dmin) [сообщение]");
	}

	new string[128 + MAX_ADMIN_RANK_LENGTH + MAX_PLAYER_NAME];

	format(string, sizeof string, COLOR_ADMIN_CHAT"[A] %s "COLOR_SUCCESS"%s\
		"COLOR_ADMIN_CHAT": %s",  admin_ranks[admin[adminid][admin_level]],
		player[adminid][player_name], params);
	SendAdminMessage(string);
	return CMD_RTN_SUCCESS;
}
alias:admin("a");


CMD:clearchat(adminid)
{
	CheckAdminLevel(adminid, CMD_clearchat);
	
	ClearGlobalChat();

	static const string_content[] =
		!COLOR_NOTE" произвел очистку чата!";
	new string[sizeof string_content + MAX_PLAYER_NAME +
		MAX_ADMIN_RANK_LENGTH + 1 + 24];

	strcat(string, admin_ranks[admin[adminid][admin_level]]);
	strcat(string, !" "COLOR_ERROR);
	strcat(string, player[adminid][player_name]);
	strcat(string, string_content);

	SendClientMessageToAll(HEX_COLOR_NOTE, string);

	admin[adminid][admin_chat_clears]++;
	return CMD_RTN_SUCCESS;
}
alias:clearchat("cc");


CMD:kick(adminid, params[])
{
	CheckAdminLevel(adminid, CMD_kick);
	
	extract params -> new playerid, string:reason[32]; else
	{
		return SendClientMessage(adminid, HEX_COLOR_ERROR,
			!"Используйте: /kick [id] [причина]");
	}

	else if(!IsPlayerConnected(playerid) || playerid == adminid)
	{
		return CMD_RTN_INVALID_PLAYER_ID;
	}

	else if(admin[playerid][admin_level] > admin[adminid][admin_level])
	{
		return CMD_RTN_NO_PERMISSIONS;
	}

	else
	{
		static const string_content[] = "%s "COLOR_ERROR"%s \
			"COLOR_NOTE"кикнул игрока "COLOR_ERROR"%s";

		new string[sizeof string_content -2 + MAX_ADMIN_RANK_LENGTH -
			2 - 2 + MAX_PLAYER_NAME*2],
			p_name[MAX_PLAYER_NAME];

		GetPlayerName(playerid, p_name, MAX_PLAYER_NAME);

		format(string, sizeof string, string_content,
			admin_ranks[admin[adminid][admin_level]],
			player[adminid][player_name], p_name);
		SendClientMessageToAll(-1, !"");
		SendClientMessageToAll(HEX_COLOR_NOTE, string);

		format(string, sizeof string, "Причина: "COLOR_ERROR"%s", reason);
		SendClientMessageToAll(HEX_COLOR_NOTE, string);
		SendClientMessageToAll(-1, !"");

		Kick(playerid);

		admin[adminid][admin_kicks]++;
	}

	return CMD_RTN_SUCCESS;
}


CMD:vehicle(adminid, params[])
{
	CheckAdminLevel(adminid, CMD_vehicle);

	new
		vehicletype,
		color1,
		color2;

	if(sscanf(params, "iI(1)I(1)", vehicletype, color1, color2))
	{
		return SendClientMessage(adminid, HEX_COLOR_ERROR, "Используйте: \
			/veh(icle) [id] [цвет1 опционально] [цвет2 опционально]");
	}

	new
		Float:x,
		Float:y,
		Float:z,
		Float:a,
		vehicleid;

	GetPlayerPos(adminid, x, y, z);
	GetPlayerFacingAngle(adminid, a);

	x += 4*floatsin(-a, degrees);
	y += 4*floatcos(-a, degrees);

	vehicleid = CreateVehicle(vehicletype, x, y, z, a, color1, color2, -1);
	SetVehicleParamsEx(vehicleid, 1, 1, 0, 0, 0, 0, 0);

	SendClientMessage(adminid, HEX_COLOR_SUCCESS, !"Транспорт создан!");

	admin[adminid][admin_created_vehicles]++;

	return CMD_RTN_SUCCESS;
}
alias:vehicle("veh");


CMD:ban(adminid, params[])
{
	CheckAdminLevel(adminid, CMD_ban);

	extract params -> new playerid, days, string:reason[128]; else
	{
		return SendClientMessage(adminid, HEX_COLOR_ERROR, "Используйте: \
			/ban [id] [дни от 1 до 365 | 0 = на вечно] [причина]");
	}

	else if(!IsPlayerConnected(playerid)/* || playerid == adminid*/)
	{
		return CMD_RTN_INVALID_PLAYER_ID;
	}

	else if(admin[adminid][admin_level] != admin[playerid][admin_level])
	{
		return CMD_RTN_NO_PERMISSIONS;
	}

	else if(!(-1 < days < 366))
	{
		return SendClientMessage(adminid, HEX_COLOR_ERROR, "Используйте: \
			/ban [id] [дни от 1 до 365 | 0 = на вечно] [причина]");
	}

	new
		string[30 + MAX_PLAYER_NAME*2 + MAX_ADMIN_RANK_LENGTH + 8*5],
		current_time = gettime();

	format(string, sizeof string, "%s "COLOR_ERROR" %s "COLOR_NOTE"дал бан \
		игроку "COLOR_ERROR"%s "COLOR_NOTE"на "COLOR_ERROR,
		admin_ranks[admin[adminid][admin_level]],
		player[adminid][player_name],
		player[playerid][player_name]);

	if(0 == days)
	{
		strcat(string, "вечно");
	}

	else
	{
		format(string, sizeof string, "%s%d дней", string, days);
	}

	SendClientMessageToAll(-1, !"");
	SendClientMessageToAll(HEX_COLOR_NOTE, string);

	string[0] = EOS;
	strcat(string, "Причина: "COLOR_ERROR);
	strcat(string, reason);

	SendClientMessageToAll(HEX_COLOR_NOTE, string);
	SendClientMessageToAll(-1, !"");

	Kick(playerid);

	mysql_format(mysql_connection_id, string, sizeof string,
		"INSERT INTO ban_list(player_id,baner_id,ban_date,unban_date,\
		reason)VALUES('%d','%d','%d','%d','%s')",
		GetPlayerUniqueId(playerid),
		GetPlayerUniqueId(adminid),
		current_time,
		(0 == days) ? (-1) : (current_time+(days*UNIX_DAY)),
		reason);

	mysql_tquery(mysql_connection_id, string);

	admin[adminid][admin_bans]++;

	return CMD_RTN_SUCCESS;
}