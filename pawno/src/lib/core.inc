#define IsOdd(%0)  ((%0) & 1)
#define IsEven(%0) (!IsOdd(%0))


const UNIX_MINUTE = 60;
const UNIX_HOUR = UNIX_MINUTE*60;
const UNIX_DAY = UNIX_HOUR*24;
const UNIX_MONTH = UNIX_DAY*30;
const UNIX_YEAR = UNIX_MONTH*12;




stock UnixTimeConvert(array[], timestamp, array_size = sizeof(array))
{
    if(array_size < 14)
    {
        return 0;
    }

    array[0] = EOS;
    
    new 
        compare = gettime(), 
        time = (timestamp > compare) ? 
            (timestamp - compare) : (compare - timestamp), remainder;
    
    if(time < UNIX_MINUTE)
    {
        remainder = time;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "секунда", array_size);
            }

            case 2, 3, 4:
            {
                strcat(array, "секунды", array_size);
            }

            default:
            {
                strcat(array, "секунд", array_size);
            }
        }
    }

    else if(time < UNIX_HOUR)
    {
        remainder = time = time / UNIX_MINUTE;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "минута", array_size);
            }

            case 2, 3, 4:
            {
                strcat(array, "минуты", array_size);
            }

            default:
            {
                strcat(array, "минут", array_size);
            }
        }
    }

    else if(time < UNIX_DAY)
    {
        remainder = time = time / UNIX_HOUR;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "час", array_size);
            }

            case 2, 3, 4:
            {
               strcat(array, "часа", array_size);
            }

            default:
            {
                strcat(array, "часов", array_size);
            }
        }
    }

    else if(time < UNIX_MONTH)
    {
        remainder = time = time / UNIX_DAY;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "день", array_size);
            }

            case 2, 3, 4:
            {
                strcat(array, "дня", array_size);
            }

            default:
            {
                strcat(array, "дней", array_size);
            }
        }
    }

    else if(time < UNIX_YEAR)
    {
        remainder = time = time / UNIX_MONTH;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "месяц", array_size);
            }

            case 2, 3, 4:
            {
                strcat(array, "месяца", array_size);
            }

            default:
            {
                strcat(array, "месяцев", array_size);
            }
        }
    }

    else
    {
        remainder = time = time / UNIX_YEAR;

        if((remainder %= 100) > 19)
        {
            remainder %= 10;
        }

        switch(remainder)
        {
            case 1:
            {
                strcat(array, "год", array_size);
            }

            case 2, 3, 4:
            {
                strcat(array, "года", array_size);
            }

            default:
            {
                strcat(array, "лет", array_size);
            }
        }
    }
    
    format(array, array_size, "%d %s", time, array);
    return 1;
}




#define IsPVarSet(%0,%1) (GetPVarType(%0,%1) != PLAYER_VARTYPE_NONE)
#define IsPlayerSelectTextDraw(%0) IsPVarSet(%0, !"_select_td")

#if defined _foreach_included
    static _iter_return_value;
#endif


new
    MySQL: mysql_connection_id,
    Text:TD_kick
    #if defined _foreach_included
        ,
        Iterator:Vehicle<MAX_VEHICLES>,
        Iterator:GlobalTextdraw<MAX_TEXT_DRAWS>,
        Iterator:PlayerTextdraw<MAX_PLAYER_TEXT_DRAWS>;
    #else
        ;
    #endif




stock mysql_OnGameModeInit()
{
    mysql_connection_id = mysql_connect_file();

    if(mysql_errno(mysql_connection_id))
    {
        print(!"\nMySQL\n---------------\n \
            Error: Can't connect to MySQL server.\n\n");
        return 0;
    }

    else
    {
        print(!"\nMySQL\n---------------\n \
            Connected to MySQL server.");
    }

    mysql_tquery(mysql_connection_id, "SET NAMES cp1251"); 
    mysql_tquery(mysql_connection_id, "set character_set_client='cp1251'"); 
    mysql_tquery(mysql_connection_id, "set character_set_results='cp1251'"); 
    mysql_tquery(mysql_connection_id,
        "set collation_connection='cp1251_general_ci'"); 
    mysql_set_charset("cp1251"); 
    return 1;
}




stock ClearPlayerChat(playerid)
{
	for(new i = 0; i < 100; i++)
	{
		SendClientMessage(playerid, -1, !"");
	}
}




stock ClearGlobalChat()
{
	for(new i = 0; i < 100; i++)
	{
		SendClientMessageToAll(-1, !"");
	}
}




stock itos(num, buffer[], size=sizeof(buffer))
{ // by Daniel_Cortez \\pro-pawn.ru
    new fix_cellmin = (num == cellmin) ? ++num : 0;
    new pos = 0;
    if(num < 0)
        buffer[0] = '-', pos++, num = -num;
    {
        new x = num;
        do{
            x /= 10;
            pos++;
        }while(x);
    }
    buffer[(--size<pos) ? size : pos] = EOS;
    new len = (size>pos) ? pos : size;
    new mod;
    do{
        /*if(--pos < size)
            buffer[pos] = '0'+num%10;
        num /= 10;*/
        // make 1 "sdiv" operation instead of 2
        #emit    load.s.pri    num
        #emit    const.alt    10
        #emit    sdiv
        #emit    stor.s.pri    num
        #emit    stor.s.alt    mod
        if(--pos < size)
            buffer[pos] = '0'+mod;
    }while(num);
    if(fix_cellmin)
        buffer[10]++;
    return len;
}




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



#if defined _foreach_included
    stock g_CreateVehicle(vehicletype,
        Float:x, Float:y, Float:z, Float:rotation,
        color1, color2, respawn_delay, addsiren = 0)
    {
        if(INVALID_VEHICLE_ID !=
            (_iter_return_value = CreateVehicle(vehicletype, x, y, z, rotation,
                color1, color2, respawn_delay, addsiren)))
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
        Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle,
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
        Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle,
        color1, color2, respawn_delay, addsiren = 0)
    {
        if(INVALID_VEHICLE_ID !=
            (_iter_return_value = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
                spawn_z, z_angle, color1, color2, respawn_delay, addsiren)))
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




    stock Text:g_TextDrawCreate(Float:x, Float:y, text[])
    {
        if(INVALID_TEXT_DRAW !=
            (_iter_return_value = _:TextDrawCreate(x, y, text)))
        {
            Iter_Add(GlobalTextdraw, _iter_return_value);
        }

        return Text:_iter_return_value;
    }

    #if defined _ALS_TextDrawCreate
        #undef TextDrawCreate
    #else
        #define _ALS_TextDrawCreate
    #endif
    #define TextDrawCreate g_TextDrawCreate




    stock g_TextDrawDestroy(Text:text)
    {
        Iter_SafeRemove(GlobalTextdraw, _:text, _:text);
        return TextDrawDestroy(text);
    }

    #if defined _ALS_TextDrawDestroy
        #undef TextDrawDestroy
    #else
        #define _ALS_TextDrawDestroy
    #endif
    #define TextDrawDestroy g_TextDrawDestroy




    stock PlayerText:g_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[])
    {
        if(INVALID_TEXT_DRAW !=
            (_iter_return_value = _:CreatePlayerTextDraw(playerid, x, y, text)))
        {
            Iter_Add(PlayerTextdraw, _iter_return_value);
        }

        return PlayerText:_iter_return_value;
    }

    #if defined _ALS_CreatePlayerTextDraw
        #undef CreatePlayerTextDraw
    #else
        #define _ALS_CreatePlayerTextDraw
    #endif
    #define CreatePlayerTextDraw g_CreatePlayerTextDraw




    stock g_PlayerTextDrawDestroy(playerid, PlayerText:text)
    {
        Iter_SafeRemove(PlayerTextdraw, _:text, _:text);
        return PlayerTextDrawDestroy(playerid, text);
    }

    #if defined _ALS_PlayerTextDrawDestroy
        #undef PlayerTextDrawDestroy
    #else
        #define _ALS_PlayerTextDrawDestroy
    #endif
    #define PlayerTextDrawDestroy g_PlayerTextDrawDestroy
#endif




public OnGameModeInit()
{
    TD_kick = TextDrawCreate(961.666564, -25.877780, !"_");
    TextDrawLetterSize(TD_kick, 0.000000, 67.181686);
    TextDrawTextSize(TD_kick, -31.333332, 0.000000);
    TextDrawAlignment(TD_kick, 1);
    TextDrawColor(TD_kick, 0);
    TextDrawUseBox(TD_kick, true);
    TextDrawBoxColor(TD_kick, 255);
    TextDrawSetShadow(TD_kick, 0);
    TextDrawSetOutline(TD_kick, 0);
    TextDrawFont(TD_kick, 0);

    #if defined g_OnGameModeInit
        return g_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit g_OnGameModeInit
#if defined g_OnGameModeInit
    forward g_OnGameModeInit();
#endif




@Kick(playerid);
@Kick(playerid)
{
    return Kick(playerid);
}




stock g_Kick(playerid, reason[] = !"")
{
    #if defined _foreach_included
        foreach(GlobalTextdraw, i)
        {
            TextDrawHideForPlayer(playerid, Text:i);
        }

        foreach(PlayerTextdraw, i)
        {
            PlayerTextDrawHide(playerid, PlayerText:i);
        }
    #endif
    
    TextDrawShowForPlayer(playerid, TD_kick);
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
#define KICK_TEXT_REASON \
    !COLOR_ERROR"Вы были отсоединены от сервера\nПричина: "COLOR_TITLE
#define KICK_TEXT_TIP \
    "\n\n"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)"