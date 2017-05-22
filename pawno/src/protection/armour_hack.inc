#if defined _armour_hack_protection
	#endinput
#endif
#define _armour_hack_protection

#if !defined ARMOUR_HACK_UPDATE_INTERVAL
	#define ARMOUR_HACK_UPDATE_INTERVAL 1000
#endif


forward ahp_CheckPlayer(playerid);


static ahp_timer[MAX_PLAYERS];


stock ahp_OnPlayerLogin(playerid)
{
	ahp_timer[playerid] = SetTimerEx(!"ahp_CheckPlayer",
		ARMOUR_HACK_UPDATE_INTERVAL, 0, !"i", playerid);

	return 1;
}


public ahp_CheckPlayer(playerid)
{
	new
		Float:player_armour,
		Float:account_armour;

	GetPlayerArmour(playerid, player_armour);
	GetAccountArmour(playerid, account_armour);

	if(player_armour > account_armour)
	{
		Kick(playerid, KICK_TEXT_REASON"\
			Подозрение в читерстве, код: #ahp_CP"KICK_TEXT_TIP);
		return 0;
	}

	else if(player_armour < account_armour)
	{
		SetAccountArmour(playerid, player_armour);
	}

	ahp_timer[playerid] = SetTimerEx(!"ahp_CheckPlayer",
		ARMOUR_HACK_UPDATE_INTERVAL, 0, !"i", playerid);

	return 1;
}


stock ahp_GetPlayerArmour(playerid, &Float:armour)
{
	return GetAccountArmour(playerid, armour);
}
#if defined _ALS_GetPlayerArmour
	#undef GetPlayerArmour
#else
	#define _ALS_GetPlayerArmour
#endif
#define GetPlayerArmour ahp_GetPlayerArmour


stock ahp_SetPlayerArmour(playerid, Float:armour)
{
	new result = 1;

	KillTimer(ahp_timer[playerid]);
	SetAccountArmour(playerid, armour);
	result = SetPlayerArmour(playerid, armour);
	ahp_timer[playerid] = SetTimerEx(!"ahp_CheckPlayer",
		ARMOUR_HACK_UPDATE_INTERVAL, 0, !"i", playerid);
	return result;
}
#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour ahp_SetPlayerArmour


stock ahp_OnPlayerDisconnect(playerid)
{
	KillTimer(ahp_timer[playerid]);
	return 1;
}