CREATE TABLE IF NOT EXISTS `accounts` 
(
  `uid` int(12) NOT NULL AUTO_INCREMENT,
  `name` varchar(25),
  `password` varchar(65),
  `salt` varchar(65),
  `russifier` int(2) NOT NULL DEFAULT '0',
  `mail` varchar(65),
  `gender` int(2) NOT NULL DEFAULT '0',
  `model` int(4) NOT NULL DEFAULT '0',
  `ip` varchar(17) NOT NULL,
  `money` int(12) NOT NULL DEFAULT '0',
  `health` float NOT NULL DEFAULT '100.0',
  `armour` float NOT NULL DEFAULT '0.0',
  PRIMARY KEY (`uid`)
)
ENGINE = MyISAM DEFAULT CHARSET = cp1251 AUTO_INCREMENT = 1;


CREATE TABLE IF NOT EXISTS `ip_list` 
(
	`ip` varchar(17),
  `last_connect` int(12) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ip`)
)
ENGINE = MyISAM DEFAULT CHARSET = cp1251;


CREATE TABLE IF NOT EXISTS `admins` 
(
  `uid` int(11) NOT NULL DEFAULT '0',
  `password` varchar(65),
  `salt` varchar(65),
  `level` int(5) NOT NULL DEFAULT '0',
  `bans` int(5) NOT NULL DEFAULT '0',
  `banned_ips` int(5) NOT NULL DEFAULT '0',
  `offline_bans` int(5) NOT NULL DEFAULT '0',
  `unbans` int(5) NOT NULL DEFAULT '0',
  `unbanned_ips` int(5) NOT NULL DEFAULT '0',
  `offline_unbans` int(5) NOT NULL DEFAULT '0',
  `kicks` int(5) NOT NULL DEFAULT '0',
  `given_money` int(17) NOT NULL DEFAULT '0',
  `created_vehicles` int(5) NOT NULL DEFAULT '0',
  `chat_clears` int(5) NOT NULL DEFAULT '0',
  PRIMARY KEY (`uid`)
)
ENGINE = MyISAM DEFAULT CHARSET = cp1251;


CREATE TABLE IF NOT EXISTS `ban_list` 
(
  `player_id` int(11) NOT NULL DEFAULT '0',
  `baner_id` int(11) NOT NULL DEFAULT '0',
  `ban_date` int(11) NOT NULL DEFAULT '0',
  `unban_date` int(11) NOT NULL DEFAULT '0',
  `reason` varchar(124) NOT NULL,
    PRIMARY KEY (`player_id`)
)
ENGINE = MyISAM DEFAULT CHARSET = cp1251;