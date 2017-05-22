#if defined _reconnect_protection
	#endinput
#endif
#define _reconnect_protection

#if !defined RECONNECT_INTERVAL
	#define RECONNECT_INTERVAL 60
#endif


static rcp_player_ip[MAX_PLAYERS];


stock rcp_OnPlayerConnect(playerid)
{
    
    static query_content[] = "SELECT*FROM ip_list WHERE ip LIKE'%s'";
	new 
		query[sizeof query_content - 2 + MAX_PLAYER_IP],
		Cache:mysql_result,
		rows,
		last_connect;
	
	GetPlayerIp(playerid, rcp_player_ip[playerid], MAX_PLAYER_IP);
	
	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		rcp_player_ip[playerid]);	
	
	mysql_result = mysql_query(mysql_connection_id, query);
	
	cache_get_row_count(rows);

	if(!rows)
	{
		cache_delete(mysql_result);
	}

	else
	{
		cache_get_value_name_int(0, "last_connect", last_connect);
		cache_delete(mysql_result);
		
		if(gettime() - last_connect < RECONNECT_INTERVAL)
		{
			Kick(playerid, KICK_TEXT_REASON"\
				Переподключаться к серверу можно раз в \
				"#RECONNECT_INTERVAL" секунд"KICK_TEXT_TIP);
			return 0;
		}
	}

	return 1;
}

stock rcp_OnPlayerDisconnect(playerid)
{
	static query_content[] = "INSERT INTO ip_list(ip,last_connect)\
	VALUES('%s','%d')ON DUPLICATE KEY UPDATE last_connect='%d'";
	new query[sizeof query_content - 2 + MAX_PLAYER_IP - 2 + 10 - 2 + 10],
		time = gettime();

	mysql_format(mysql_connection_id, query, sizeof query, query_content,
		rcp_player_ip[playerid], time, time);
	mysql_tquery(mysql_connection_id, query);
	return 1;
}