#if defined _health_hack_protection
	#endinput
#endif
#define _health_hack_protection

#if !defined HEALTH_HACK_UPDATE_INTERVAL
	#define HEALTH_HACK_UPDATE_INTERVAL 1000
#endif


forward hhp_CheckPlayer(playerid);


static hhp_timer[MAX_PLAYERS];


stock hhp_OnPlayerLogin(playerid)
{
	hhp_timer[playerid] = SetTimerEx(!"hhp_CheckPlayer",
		HEALTH_HACK_UPDATE_INTERVAL, 0, !"i", playerid);

	return 1;
}


public hhp_CheckPlayer(playerid)
{
	new
		Float:player_health,
		Float:account_health;

	GetPlayerHealth(playerid, player_health);
	GetAccountHealth(playerid, account_health);

	if(player_health > account_health)
	{
		Kick(playerid, KICK_TEXT_REASON"\
			Подозрение в читерстве, код: #hhp_CP"KICK_TEXT_TIP);
		return 0;
	}

	else if(player_health < account_health)
	{
		SetAccountHealth(playerid, player_health);
	}

	hhp_timer[playerid] = SetTimerEx(!"hhp_CheckPlayer",
		HEALTH_HACK_UPDATE_INTERVAL, 0, !"i", playerid);

	return 1;
}


stock hhp_GetPlayerHealth(playerid, &Float:health)
{
	return GetAccountHealth(playerid, health);
}
#if defined _ALS_GetPlayerHealth
	#undef GetPlayerHealth
#else
	#define _ALS_GetPlayerHealth
#endif
#define GetPlayerHealth hhp_GetPlayerHealth


stock hhp_SetPlayerHealth(playerid, Float:health)
{
	new result = 1;

	KillTimer(hhp_timer[playerid]);
	SetAccountHealth(playerid, health);
	result = SetPlayerHealth(playerid, health);
	hhp_timer[playerid] = SetTimerEx(!"hhp_CheckPlayer",
		HEALTH_HACK_UPDATE_INTERVAL, 0, !"i", playerid);
	return result;
}
#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth hhp_SetPlayerHealth


stock hhp_OnPlayerDisconnect(playerid)
{
	KillTimer(hhp_timer[playerid]);
	return 1;
}