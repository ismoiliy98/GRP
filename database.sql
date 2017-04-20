CREATE TABLE IF NOT EXISTS `accounts` 
(
  `uid` int(12) NOT NULL AUTO_INCREMENT,
  `name` varchar(25),
  `password` varchar(65),
  `salt` varchar(65),
  `mail` varchar(65),
  `gender` int(2) NOT NULL DEFAULT '0',
  `model` int(4) NOT NULL DEFAULT '0',
  `ip` varchar(17) NOT NULL,
  PRIMARY KEY (`uid`)
)

ENGINE=MyISAM DEFAULT CHARSET = utf8 AUTO_INCREMENT = 1;

CREATE TABLE IF NOT EXISTS `ip_list` 
(
	`ip` varchar(17),
  `last_connect` int(12) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ip`)
)

ENGINE=MyISAM DEFAULT CHARSET = utf8 AUTO_INCREMENT = 1;