#if defined _money_hack_protection
	#endinput
#endif
#define _money_hack_protection


stock mhp_GivePlayerMoney(playerid, money)
{
	ResetPlayerMoney(playerid);
	SetAccountMoney(playerid, GetAccountMoney(playerid) + money);
	return GivePlayerMoney(playerid, GetAccountMoney(playerid));
}
#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif
#define GivePlayerMoney mhp_GivePlayerMoney


stock mhp_GetPlayerMoney(playerid)
{
	return GetAccountMoney(playerid);
}
#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif
#define GetPlayerMoney mhp_GetPlayerMoney


stock mhp_ResetPlayerMoney(playerid)
{
	ResetAccountMoney(playerid);
	return ResetPlayerMoney(playerid);
}
#if defined _ALS_ResetPlayerMoney
	#undef ResetPlayerMoney
#else
	#define _ALS_ResetPlayerMoney
#endif
#define ResetPlayerMoney mhp_ResetPlayerMoney