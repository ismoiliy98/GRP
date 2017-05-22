/*
	Author: 		Geebrox (vk.com/geebrox | pro-pawn.ru/member.php?4482)
	License: 		https://github.com/Geebrox/GRP
	Releases: 		https://github.com/Geebrox/GRP/releases
	Source code: 	https://github.com/Geebrox/GRP

		(c) Geebrox 2017.
*/

#include "../src/lib/antideamx.inc"
#include "a_samp.inc"
#include "a_http.inc"
#include "../src/lib/fixes.inc"
#include "../src/lib/crashdetect.inc"
#include "../src/settings.inc"
#include "../src/lib/a_mysql.inc"
#include "../src/lib/sscanf2.inc"
#include "../src/lib/foreach.inc"
#include "../src/lib/rustext.inc"
#include "../src/lib/core.inc"
#include "../src/lib/mdialog.inc"
#include "../src/lib/Pawn.CMD.inc"
#include "../src/protection/settings.inc"
#include "../src/player/account/settings.inc"
#include "../src/admin/settings.inc"
#include "../src/protection/money_hack.inc"
#include "../src/protection/health_hack"
#include "../src/protection/armour_hack"
#include "../src/protection/reconnect.inc"
#include "../src/player/account/account_system.inc"
#include "../src/admin/admin_system.inc"
#include "../src/admin/commands.inc"
#include "../src/player/account/ban_system.inc"


forward OnPlayerLogin(playerid);


public OnGameModeInit()
{
	new result = mysql_OnGameModeInit();

	if(result)
	{
		print("\nGamemode\n---------------");
		SendRconCommand("hostname " SERVER_NAME);
		SetGameModeText(SERVER_MODE);
		SendRconCommand("language " SERVER_LANGUAGE);
		SendRconCommand("weburl " SERVER_WEBSITE);
		AddPlayerClass(0, -100.0, -100.0, -100.0, -100.0, 0, 0, 0, 0, 0, 0);
		ShowNameTags(true);
		ShowPlayerMarkers(false);
		EnableStuntBonusForAll(false);
		DisableNameTagLOS();
		DisableInteriorEnterExits();
		ManualVehicleEngineAndLights();

		account_OnGameModeInit();
	}
	
	return result;
}


public OnPlayerConnect(playerid)
{
	new result = rcp_OnPlayerConnect(playerid);

	if(result)
	{
		result = account_OnPlayerConnect(playerid);
	}
	
	return result;
}


public OnPlayerDisconnect(playerid, reason)
{
	hhp_OnPlayerDisconnect(playerid);
	ahp_OnPlayerDisconnect(playerid);
	rcp_OnPlayerDisconnect(playerid);
	account_OnPlayerDisconnect(playerid);
	admin_OnPlayerDisconnect(playerid);

	return 1;
}


public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	account_OnPlayerClickTextDraw(playerid, clickedid);
	
	return 1;
}


public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	account_OnPlayerClickPlayerText(playerid, playertextid);
	
	return 1;
}


public OnPlayerRequestClass(playerid, classid)
{
	account_OnPlayerRequestClass(playerid);

	return 1;
}


public OnPlayerRequestSpawn(playerid)
{
	return 0;
}


public OnPlayerLogin(playerid)
{
	new result = ban_OnPlayerLogin(playerid);

	if(result)
	{
		hhp_OnPlayerLogin(playerid);
		ahp_OnPlayerLogin(playerid);
		admin_OnPlayerLogin(playerid);
	}
	
	return 1;
}


public OnPlayerSpawn(playerid)
{
	account_OnPlayerSpawn(playerid);

	return 1;
}


public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if(Dialog_IsOpen(playerid))
	{
		SendClientMessage(playerid, HEX_COLOR_ERROR, !"Нельзя пользоваться \
			командами при открытом диалоге!");
		return 0;
	}

	return 1;
}


public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	switch(result)
	{
		case CMD_RTN_SUCCESS:
		{
			return 1;
		}

		case CMD_RTN_INVALID_COMMAND:
		{
			SendClientMessage(playerid, HEX_COLOR_ERROR,
				!"Неизвестная команда!");
		}

		case CMD_RTN_NO_PERMISSIONS:
		{
			SendClientMessage(playerid, HEX_COLOR_ERROR,
				!"Не достаточно полномочий!");
		}

		case CMD_RTN_INVALID_PLAYER_ID:
		{
			SendClientMessage(playerid, HEX_COLOR_ERROR,
				!"Не валидный ID игрока!");
		}
	}

	return 0;
}


public OnPlayerText(playerid, text[])
{
	if(!IsPlayerLogged(playerid))
	{
		return 0;
	}

	return 1;
}


main()
{
	print(" (c) Geebrox 2017.\n");
}