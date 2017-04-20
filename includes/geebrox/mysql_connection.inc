#if !defined mysql_included
	#include "a_mysql"
#endif

new MySQL: mysql_connection_id;


public OnGameModeInit()
{
	{
		new MySQLOpt: mysql_options = mysql_init_options();
		mysql_set_option(mysql_options, AUTO_RECONNECT, false);
		mysql_set_option(mysql_options, POOL_SIZE, 0);
		
		mysql_connection_id =
			mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_BASE,
				mysql_options);

		if(mysql_errno(mysql_connection_id))
		{
			return printf("\nMySQL\n---------------\n \
				Error: Can't connect to MySQL server on '%s'\n", MYSQL_HOST);
		}

		else
		{
			printf("\nMySQL\n---------------\n \
				Connected to MySQL server on '%s'\n", MYSQL_HOST);
		}

		mysql_tquery(mysql_connection_id, !"SET CHARACTER SET'utf8'");
		mysql_tquery(mysql_connection_id, !"SET NAMES'utf8'");
		mysql_tquery(mysql_connection_id, !"SET character_set_client='cp1251'");
		mysql_tquery(mysql_connection_id,
			!"SET character_set_connection='cp1251'");
		mysql_tquery(mysql_connection_id,
			!"SET character_set_results='cp1251'");
		mysql_tquery(mysql_connection_id,
			!"SET SESSION collation_connection='utf8_general_ci'");
	}

	#if defined mysql_OnGameModeInit
		return mysql_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit mysql_OnGameModeInit
#if defined mysql_OnGameModeInit
	forward mysql_OnGameModeInit();
#endif