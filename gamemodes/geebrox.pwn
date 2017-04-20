/*
	Author: Geebrox (vk.com/geebrox | pro-pawn.ru/member.php?4482)
*/

#include "geebrox\antideamx"
#include "a_samp"
#include "a_http"
#include "geebrox\fixes"
#include "geebrox\crashdetect"
#include "geebrox\settings"
#include "geebrox\mysql_connection"
#include "geebrox\sscanf2"
#include "geebrox\Pawn.CMD"
#include "geebrox\foreach"
#include "geebrox\streamer"
#include "geebrox\rustext"
#include "geebrox\variables"
#include "geebrox\hooks"
#include "geebrox\mdialog"
#include "geebrox\functions"
#include "geebrox\account_system"


public OnGameModeInit()
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

	TD_death_screen = TextDrawCreate(961.666564, -25.877780, "usebox");
	TextDrawLetterSize(TD_death_screen, 0.000000, 67.181686);
	TextDrawTextSize(TD_death_screen, -31.333332, 0.000000);
	TextDrawAlignment(TD_death_screen, 1);
	TextDrawColor(TD_death_screen, 0);
	TextDrawUseBox(TD_death_screen, true);
	TextDrawBoxColor(TD_death_screen, 255);
	TextDrawSetShadow(TD_death_screen, 0);
	TextDrawSetOutline(TD_death_screen, 0);
	TextDrawFont(TD_death_screen, 0);
	return 1;
}


main()
{
	print(" (c) Geebrox 2017\n");
}