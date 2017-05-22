stock ban_OnPlayerLogin(playerid)
{
	static query_content[] = "SELECT*FROM ban_list WHERE player_id='%d'";
	new 
		query[sizeof query_content - 2 + 12],
		Cache:mysql_result,
		rows,
		baner_id,
		ban_date,
		unban_date,
		reason[128],
		current_time = gettime();

	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		GetPlayerUniqueId(playerid));	
	
	mysql_result = mysql_query(mysql_connection_id, query);
	
	cache_get_row_count(rows);

	if(!rows)
	{
		cache_delete(mysql_result);
	}

	else
	{
		cache_get_value_name_int(0, "baner_id", baner_id);
		cache_get_value_name_int(0, "ban_date", ban_date);
		cache_get_value_name_int(0, "unban_date", unban_date);
		cache_get_value_name(0, "reason", reason);
		cache_delete(mysql_result);
		
		if(-1 == unban_date || unban_date > current_time)
		{
			new
				string[7*8 + MAX_PLAYER_NAME + sizeof reason*2],
				baner_name[MAX_PLAYER_NAME];

			mysql_format(mysql_connection_id, string, sizeof string, 
				"SELECT name FROM accounts WHERE uid='%d'", baner_id);
			mysql_result = mysql_query(mysql_connection_id, string);

			cache_get_row_count(rows);

			if(!rows)
			{
				strcat(baner_name, "Неизвестно");
			}

			else
			{
				cache_get_value_name(0, "name", baner_name);
			}

			cache_delete(mysql_result);

			UnixTimeConvert(string, ban_date);

			if(-1 == unban_date)
			{
				format(string, sizeof string, COLOR_NOTE"\
					Ваш аккаунт заблокирован админом: "COLOR_ERROR"%s!\n\
					"COLOR_NOTE"Причина: "COLOR_ERROR"%s\n\
					"COLOR_NOTE"Ваш аккаунт заблокирован "COLOR_ERROR"\
					%s"COLOR_NOTE" назад, "COLOR_ERROR"на вечно!!"KICK_TEXT_TIP,
					baner_name, reason, string);
			}

			else
			{
				new str_unban_date[14];

				UnixTimeConvert(str_unban_date, unban_date);

				format(string, sizeof string, COLOR_NOTE"\
					Ваш аккаунт заблокирован админом: "COLOR_ERROR"%s!\n\
					"COLOR_NOTE"Причина: "COLOR_ERROR"%s\n\
					"COLOR_NOTE"Ваш аккаунт заблокирован "COLOR_ERROR"\
					%s"COLOR_NOTE" назад!\nБудет разблокирован через \
					"COLOR_ERROR"%s"KICK_TEXT_TIP,
					baner_name, reason, string, str_unban_date);
			}

			Kick(playerid, string);
			return 0;
		}

		else
		{
			mysql_format(mysql_connection_id, reason, sizeof reason,
				"DELETE FROM ban_list WHERE player_id='%d'",
				GetPlayerUniqueId(playerid));
			mysql_tquery(mysql_connection_id, reason);
		}
	}

	return 1;
}