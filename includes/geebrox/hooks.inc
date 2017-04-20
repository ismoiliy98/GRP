static _iter_return_value;


stock g_SelectTextDraw(playerid, hovercolor)
{
	SetPVarInt(playerid, !"_select_td", hovercolor);
	return SelectTextDraw(playerid, hovercolor);
}
#if defined _ALS_SelectTextDraw
	#undef SelectTextDraw
#else
	#define _ALS_SelectTextDraw
#endif
#define SelectTextDraw g_SelectTextDraw


stock g_CancelSelectTextDraw(playerid)
{
	if(IsPlayerSelectTextDraw(playerid))
	{
		DeletePVar(playerid, !"_select_td");
	}
	return CancelSelectTextDraw(playerid);
}
#if defined _ALS_CancelSelectTextDraw
	#undef CancelSelectTextDraw
#else
	#define _ALS_CancelSelectTextDraw
#endif
#define CancelSelectTextDraw g_CancelSelectTextDraw


stock g_ShowPlayerDialog(playerid, dialogid, style, caption[], info[],
	button1[], button2[])
{
	if(IsPlayerSelectTextDraw(playerid))
	{
		SetPVarInt(playerid, !"_select_td_dialog",
			GetPVarInt(playerid, !"_select_td"));
		CancelSelectTextDraw(playerid);
	}

	return ShowPlayerDialog(playerid, dialogid, style, caption, info,
		button1, button2);
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog g_ShowPlayerDialog


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(IsPVarSet(playerid, !"_select_td_dialog"))
	{
		SelectTextDraw(playerid, GetPVarInt(playerid, !"_select_td_dialog"));
		DeletePVar(playerid, !"_select_td_dialog");
	}

	#if defined g_OnDialogResponse
		return g_OnDialogResponse(playerid, dialogid, response, listitem,
			inputtext);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse g_OnDialogResponse
#if defined g_OnDialogResponse
	forward g_OnDialogResponse(playerid, dialogid, response, listitem,
		inputtext[]);
#endif


stock g_CreateVehicle(vehicletype,
	Float: x, Float: y, Float: z, Float: rotation,
	color1, color2, respawn_delay, addsiren = 0)
{
	if(INVALID_VEHICLE_ID != (_iter_return_value = CreateVehicle(vehicletype,
		x, y, z, rotation, color1, color2, respawn_delay, addsiren)))
	{
		Iter_Add(Vehicle, _iter_return_value);
	}

	return _iter_return_value;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle g_CreateVehicle


stock g_AddStaticVehicle(modelid,
	Float: spawn_x, Float: spawn_y, Float: spawn_z, Float: z_angle,
	color1, color2)
{
	if(INVALID_VEHICLE_ID != (_iter_return_value = AddStaticVehicle(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2)))
	{
		Iter_Add(Vehicle, _iter_return_value);
	}

	return _iter_return_value;
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle g_AddStaticVehicle


stock g_AddStaticVehicleEx(modelid,
	Float: spawn_x, Float: spawn_y, Float: spawn_z, Float: z_angle,
	color1, color2, respawn_delay, addsiren=0)
{
	if(INVALID_VEHICLE_ID != (_iter_return_value = AddStaticVehicleEx(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay,
		addsiren)))
	{
		Iter_Add(Vehicle, _iter_return_value);
	}

	return _iter_return_value;
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx g_AddStaticVehicleEx


stock g_DestroyVehicle(vehicleid)
{
	Iter_SafeRemove(Vehicle, vehicleid, vehicleid);
	return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle g_DestroyVehicle


stock Text: g_TextDrawCreate(Float: x, Float: y, text[])
{
	if(INVALID_TEXT_DRAW !=
		(_iter_return_value = _: TextDrawCreate(x, y, text)))
	{
		Iter_Add(GlobalTextdraw, _iter_return_value);
	}

	return Text: _iter_return_value;
}
#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate g_TextDrawCreate


stock g_TextDrawDestroy(Text: text)
{
	Iter_SafeRemove(GlobalTextdraw, _: text, _: text);
	return TextDrawDestroy(text);
}
#if defined _ALS_TextDrawDestroy
	#undef TextDrawDestroy
#else
	#define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy g_TextDrawDestroy


stock PlayerText: g_CreatePlayerTextDraw(playerid, Float: x, Float: y, text[])
{
	if(INVALID_TEXT_DRAW !=
		(_iter_return_value = _: CreatePlayerTextDraw(playerid, x, y, text)))
	{
		Iter_Add(PlayerTextdraw, _iter_return_value);
	}

	return PlayerText: _iter_return_value;
}
#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw g_CreatePlayerTextDraw


stock g_PlayerTextDrawDestroy(playerid, PlayerText: text)
{
	Iter_SafeRemove(PlayerTextdraw, _: text, _: text);
	return PlayerTextDrawDestroy(playerid, text);
}
#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy g_PlayerTextDrawDestroy



@Kick(playerid);
@Kick(playerid)
{
	return Kick(playerid);
}


stock g_Kick(playerid, reason[] = !#)
{
	foreach(GlobalTextdraw, i)
	{
		TextDrawHideForPlayer(playerid, Text: i);
	}

	foreach(PlayerTextdraw, i)
	{
		PlayerTextDrawHide(playerid, PlayerText: i);
	}
	
	TextDrawShowForPlayer(playerid, TD_death_screen);
	SetTimerEx("@Kick", 200, 0, "i", playerid);
	Dialog_Message(playerid,
		!COLOR_TITLE"Отсоединение", (strlen(reason)) ? (reason) :
		(!COLOR_ERROR"Вы были отсоединены от сервера\n\
		"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)"),
		!"Закрыть");
	return 1;
}
#if defined _ALS_Kick
	#undef Kick
#else
	#define _ALS_Kick
#endif
#define Kick g_Kick