enum TD_LOGIN_INFO
{
	Text: TD_LOGIN_BG,
	Text: TD_LOGIN_LOGO,
	Text: TD_LOGIN_HEAD,
	Text: TD_LOGIN_HEAD_TOP,
	Text: TD_LOGIN_HEAD_LCHIT,
	Text: TD_LOGIN_HEAD_RCHIT,
	Text: TD_LOGIN_HEAD_TEXT,
	Text: TD_LOGIN_HEAD_ARROW,
	Text: TD_LOGIN_BODY,
	Text: TD_LOGIN_BODY_BOTTOM,
	Text: TD_LOGIN_BODY_LCHIT,
	Text: TD_LOGIN_BODY_RCHIT,
	Text: TD_LOGIN_LINE_TOP,
	Text: TD_LOGIN_LINE_MIDDLE,
	Text: TD_LOGIN_LINE_BOTTOM,
	Text: TD_LOGIN_LINE_LEFT,
	Text: TD_LOGIN_LINE_DIV,
	Text: TD_LOGIN_LINE_RIGHT,
	Text: TD_LOGIN_IDCARD,
	Text: TD_LOGIN_PADLOCK,
	Text: TD_LOGIN_RESTORE_CHIT,
	Text: TD_LOGIN_RESTORE_TEXT,
	Text: TD_LOGIN_BUTTON,
	Text: TD_LOGIN_BUTTON_TEXT
};

enum PTD_LOGIN_INFO 
{
	PlayerText: PTD_LOGIN_NAME,
	PlayerText: PTD_LOGIN_PASSWORD
};

enum TD_JOIN_INFO
{
	Text: TD_JOIN_BG,
	Text: TD_JOIN_TEXT_TOP,
	Text: TD_JOIN_TEXT_START,
	Text: TD_JOIN_TEXT_RULES,
	Text: TD_JOIN_TEXT_PARAMS,
	Text: TD_JOIN_TEXT_MODEL,
	Text: TD_JOIN_MENU_TEXT,
	Text: TD_JOIN_LIGHTER,
	Text: TD_JOIN_BUTTON,
	Text: TD_JOIN_BUTTON_START,
	Text: TD_JOIN_BUTTON_RULES,
	Text: TD_JOIN_BUTTON_PARAMS,
	Text: TD_JOIN_BUTTON_MODEL,
	Text: TD_JOIN_BAR,
	Text: TD_JOIN_BG_RULES,
	Text: TD_JOIN_BG_PARAMS,
	Text: TD_JOIN_BG_MODEL,
	Text: TD_JOIN_ARROW_RULES,
	Text: TD_JOIN_ARROW_PARAMS,
	Text: TD_JOIN_ARROW_MODEL,
	Text: TD_JOIN_MENU_RULES,
	Text: TD_JOIN_MENU_PARAMS,
	Text: TD_JOIN_MENU_MODEL,
	Text: TD_JOIN_TABLE_OUT,
	Text: TD_JOIN_TABLE_BG,
	Text: TD_JOIN_TABLE_DIV,
	Text: TD_JOIN_TABLE_TOP,
	Text: TD_JOIN_TABLE_MIDDLE,
	Text: TD_JOIN_TABLE_BOTTOM,
	Text: TD_JOIN_IDCARD,
	Text: TD_JOIN_PADLOCK,
	Text: TD_JOIN_PAPER,
	Text: TD_JOIN_QUESTION,
	Text: TD_JOIN_BUTTON_LEFT,
	Text: TD_JOIN_BUTTON_RIGHT
};

enum PTD_JOIN_INFO
{
	PlayerText: PTD_JOIN_BAR,
	PlayerText: PTD_JOIN_BAR_TEXT,
	PlayerText: PTD_JOIN_NAME,
	PlayerText: PTD_JOIN_PASSWORD,
	PlayerText: PTD_JOIN_MAIL,
	PlayerText: PTD_JOIN_GENDER,
	PlayerText: PTD_JOIN_MODEL
};


new 
	Text: TD_login[TD_LOGIN_INFO],
	PlayerText: PTD_login[MAX_PLAYERS][PTD_LOGIN_INFO],
	Text: TD_join[TD_JOIN_INFO],
	PlayerText: PTD_join[MAX_PLAYERS][PTD_JOIN_INFO],
	PlayerText: PTD_screen_overlay[MAX_PLAYERS];


stock LoadGlobalLoginTextDraws()
{
	TD_login[TD_LOGIN_BG] = TextDrawCreate(-159.0, -149.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BG], 1040.000122, 858.666687);
	TextDrawAlignment(TD_login[TD_LOGIN_BG], 1);
	TextDrawColor(TD_login[TD_LOGIN_BG], PLAYER_BG_COLOR);
	TextDrawSetShadow(TD_login[TD_LOGIN_BG], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BG], 0);
	TextDrawFont(TD_login[TD_LOGIN_BG], 4);

	TD_login[TD_LOGIN_LOGO] =
		TextDrawCreate(4.000000, 428.000000, !SERVER_NAME);
	TextDrawLetterSize(TD_login[TD_LOGIN_LOGO], 0.400000, 1.600000);
	TextDrawAlignment(TD_login[TD_LOGIN_LOGO], 1);
	TextDrawColor(TD_login[TD_LOGIN_LOGO], -926365441);
	TextDrawSetShadow(TD_login[TD_LOGIN_LOGO], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LOGO], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_LOGO], 51);
	TextDrawFont(TD_login[TD_LOGIN_LOGO], 1);
	TextDrawSetProportional(TD_login[TD_LOGIN_LOGO], 1);

	TD_login[TD_LOGIN_HEAD] = TextDrawCreate(220.0, 124.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD], 200.000000, 36.200000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD], 4);

	TD_login[TD_LOGIN_HEAD_TOP] =
		TextDrawCreate(224.0, 120.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_TOP], 192.999786, 4.740742);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_TOP], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_TOP], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_TOP], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_TOP], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_TOP], 4);

	TD_login[TD_LOGIN_HEAD_LCHIT] =
		TextDrawCreate(218.5, 117.9, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_LCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_LCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_LCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_LCHIT], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_LCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_LCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_LCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_LCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_LCHIT], 1);

	TD_login[TD_LOGIN_HEAD_RCHIT] =
		TextDrawCreate(411.500000, 117.900001, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_RCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_RCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_RCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_RCHIT], 673722623);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_RCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_RCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_RCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_RCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_RCHIT], 1);

	TD_login[TD_LOGIN_HEAD_TEXT] =
		TextDrawCreate(320.000000, 130.000000, !"¿‚ÚÓËÁ‡ˆËˇ");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_TEXT], 0.449999, 1.799998);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_TEXT], 2);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_TEXT], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_HEAD_TEXT], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_TEXT], 2);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_TEXT], 1);

	TD_login[TD_LOGIN_HEAD_ARROW] = TextDrawCreate(295.0, 148.0, !"arrow");
	TextDrawLetterSize(TD_login[TD_LOGIN_HEAD_ARROW], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_HEAD_ARROW], 50.000000, 50.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawColor(TD_login[TD_LOGIN_HEAD_ARROW], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_HEAD_ARROW], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_HEAD_ARROW], 0);
	TextDrawFont(TD_login[TD_LOGIN_HEAD_ARROW], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_HEAD_ARROW], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_HEAD_ARROW], 1318);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_HEAD_ARROW],
		0.000000, 180.000000, 90.000000, 1.000000);

	TD_login[TD_LOGIN_BODY] = TextDrawCreate(220.0, 160.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY], 200.000000, 115.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY], 0);
	TextDrawFont(TD_login[TD_LOGIN_BODY], 4);

	TD_login[TD_LOGIN_BODY_BOTTOM] =
		TextDrawCreate(224.0, 280.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_BOTTOM], 191.999984, -10.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_BOTTOM], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_BOTTOM], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_BOTTOM], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_BOTTOM], 0);
	TextDrawFont(TD_login[TD_LOGIN_BODY_BOTTOM], 4);

	TD_login[TD_LOGIN_BODY_LCHIT] =
		TextDrawCreate(218.500000, 269.000000, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_LCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_LCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_LCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_LCHIT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_LCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_LCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BODY_LCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BODY_LCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_BODY_LCHIT], 1);

	TD_login[TD_LOGIN_BODY_RCHIT] =
		TextDrawCreate(411.500000, 269.000000, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_BODY_RCHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_BODY_RCHIT], 10.000000, 13.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BODY_RCHIT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BODY_RCHIT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BODY_RCHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BODY_RCHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BODY_RCHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BODY_RCHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_BODY_RCHIT], 1);

	TD_login[TD_LOGIN_LINE_TOP] =
		TextDrawCreate(245.0, 175.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_TOP], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_TOP], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_TOP], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_TOP], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_TOP], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_TOP], 4);

	TD_login[TD_LOGIN_LINE_MIDDLE] =
		TextDrawCreate(245.000000, 202.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_MIDDLE], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_MIDDLE], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_MIDDLE], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_MIDDLE], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_MIDDLE], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_MIDDLE], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_MIDDLE], 4);

	TD_login[TD_LOGIN_LINE_BOTTOM] =
		TextDrawCreate(245.000000, 230.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_BOTTOM], 150.000000, 0.500000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_BOTTOM], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_BOTTOM], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_BOTTOM], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_BOTTOM], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_BOTTOM], 4);

	TD_login[TD_LOGIN_LINE_LEFT] =
		TextDrawCreate(245.000000, 175.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_LEFT], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_LEFT], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_LEFT], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_LEFT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_LEFT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_LEFT], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_LEFT], 4);

	TD_login[TD_LOGIN_LINE_DIV] =
		TextDrawCreate(270.0, 175.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_DIV], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_DIV], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_DIV], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_DIV], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_DIV], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_DIV], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_DIV], 4);

	TD_login[TD_LOGIN_LINE_RIGHT] =
		TextDrawCreate(395.000000, 175.000000, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_LINE_RIGHT], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_LINE_RIGHT], 0.500000, 55.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_LINE_RIGHT], 1);
	TextDrawColor(TD_login[TD_LOGIN_LINE_RIGHT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_LINE_RIGHT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_LINE_RIGHT], 0);
	TextDrawFont(TD_login[TD_LOGIN_LINE_RIGHT], 4);

	TD_login[TD_LOGIN_IDCARD] = TextDrawCreate(244.0, 172.0, !"_");
	TextDrawLetterSize(TD_login[TD_LOGIN_IDCARD], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_IDCARD], 27.000000, 35.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawColor(TD_login[TD_LOGIN_IDCARD], -1);
	TextDrawUseBox(TD_login[TD_LOGIN_IDCARD], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_IDCARD], 0);
	TextDrawFont(TD_login[TD_LOGIN_IDCARD], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_IDCARD], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_IDCARD], 1581);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_IDCARD],
		0.000000, 0.000000, 180.000000, 1.000000);

	TD_login[TD_LOGIN_PADLOCK] = TextDrawCreate(243.0, 201.0, !"_");
	TextDrawLetterSize(TD_login[TD_LOGIN_PADLOCK], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_PADLOCK], 30.000000, 30.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawColor(TD_login[TD_LOGIN_PADLOCK], 255);
	TextDrawUseBox(TD_login[TD_LOGIN_PADLOCK], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_PADLOCK], 0);
	TextDrawFont(TD_login[TD_LOGIN_PADLOCK], 5);
	TextDrawSetProportional(TD_login[TD_LOGIN_PADLOCK], 1);
	TextDrawSetPreviewModel(TD_login[TD_LOGIN_PADLOCK], 19804);
	TextDrawSetPreviewRot(TD_login[TD_LOGIN_PADLOCK],
		0.000000, 0.000000, 0.000000, 1.000000);

	TD_login[TD_LOGIN_RESTORE_CHIT] =
		TextDrawCreate(250.0, 247.0, !"LD_BEAT:chit");
	TextDrawLetterSize(TD_login[TD_LOGIN_RESTORE_CHIT], 0.449999, 1.600000);
	TextDrawTextSize(TD_login[TD_LOGIN_RESTORE_CHIT], 15.000000, 18.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_RESTORE_CHIT], 2);
	TextDrawColor(TD_login[TD_LOGIN_RESTORE_CHIT], -589505281);
	TextDrawSetShadow(TD_login[TD_LOGIN_RESTORE_CHIT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_RESTORE_CHIT], 1);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_RESTORE_CHIT], 51);
	TextDrawFont(TD_login[TD_LOGIN_RESTORE_CHIT], 4);
	TextDrawSetProportional(TD_login[TD_LOGIN_RESTORE_CHIT], 1);

	TD_login[TD_LOGIN_RESTORE_TEXT] =
		TextDrawCreate(256.0, 251.0, !"?__«‡·˚ÎË_Ô‡ÓÎ¸?");
	TextDrawLetterSize(TD_login[TD_LOGIN_RESTORE_TEXT], 0.250000, 1.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_RESTORE_TEXT], 327.000061, 8.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawColor(TD_login[TD_LOGIN_RESTORE_TEXT], -1768515841);
	TextDrawUseBox(TD_login[TD_LOGIN_RESTORE_TEXT], true);
	TextDrawBoxColor(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawSetShadow(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_RESTORE_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_RESTORE_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawSetProportional(TD_login[TD_LOGIN_RESTORE_TEXT], 1);
	TextDrawSetSelectable(TD_login[TD_LOGIN_RESTORE_TEXT], true);

	TD_login[TD_LOGIN_BUTTON] = TextDrawCreate(343.0, 244.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_login[TD_LOGIN_BUTTON], 0.000000, 0.000000);
	TextDrawTextSize(TD_login[TD_LOGIN_BUTTON], 52.000000, 22.000000);
	TextDrawAlignment(TD_login[TD_LOGIN_BUTTON], 1);
	TextDrawColor(TD_login[TD_LOGIN_BUTTON], 497793023);
	TextDrawSetShadow(TD_login[TD_LOGIN_BUTTON], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BUTTON], 0);
	TextDrawFont(TD_login[TD_LOGIN_BUTTON], 4);
	TextDrawSetSelectable(TD_login[TD_LOGIN_BUTTON], true);

	TD_login[TD_LOGIN_BUTTON_TEXT] = TextDrawCreate(346.0, 246.0, !"¬Œ…“»");
	TextDrawLetterSize(TD_login[TD_LOGIN_BUTTON_TEXT], 0.349999, 1.799999);
	TextDrawAlignment(TD_login[TD_LOGIN_BUTTON_TEXT], 1);
	TextDrawColor(TD_login[TD_LOGIN_BUTTON_TEXT], -1);
	TextDrawSetShadow(TD_login[TD_LOGIN_BUTTON_TEXT], 0);
	TextDrawSetOutline(TD_login[TD_LOGIN_BUTTON_TEXT], 0);
	TextDrawBackgroundColor(TD_login[TD_LOGIN_BUTTON_TEXT], 51);
	TextDrawFont(TD_login[TD_LOGIN_BUTTON_TEXT], 2);
	TextDrawSetProportional(TD_login[TD_LOGIN_BUTTON_TEXT], 1);

	TD_join[TD_JOIN_BG] = TextDrawCreate(230.0, 75.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG], 180.000000, 300.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG], 1);
	TextDrawColor(TD_join[TD_JOIN_BG], 673722623);
	TextDrawSetShadow(TD_join[TD_JOIN_BG], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG], 0);
	TextDrawFont(TD_join[TD_JOIN_BG], 4);

	TD_join[TD_JOIN_TEXT_TOP] = TextDrawCreate(320.000, 85.000, !"–≈√»—“–¿÷»ﬂ");
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_TOP], 0.500000, 2.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_TOP], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_TOP], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_TOP], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_TOP], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_TOP], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_TOP], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_TOP], 1);

	TD_join[TD_JOIN_TEXT_START] = TextDrawCreate(320.0, 150.0, join_text[0]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_START], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_START], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_START], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_START], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_START], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_START], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_START], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_START], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_START], 1);

	TD_join[TD_JOIN_TEXT_RULES] = TextDrawCreate(320.0, 150.0, join_text[1]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_RULES], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_RULES], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_RULES], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_RULES], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_RULES], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_RULES], 1);

	TD_join[TD_JOIN_TEXT_PARAMS] = TextDrawCreate(320.0, 150.0, join_text[2]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_PARAMS], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_PARAMS], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_PARAMS], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_PARAMS], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_PARAMS], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_PARAMS], 1);

	TD_join[TD_JOIN_TEXT_MODEL] = TextDrawCreate(320.0, 150.0, join_text[3]);
	TextDrawLetterSize(TD_join[TD_JOIN_TEXT_MODEL], 0.250000, 1.250000);
	TextDrawTextSize(TD_join[TD_JOIN_TEXT_MODEL], 1.000000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TEXT_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_TEXT_MODEL], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TEXT_MODEL], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TEXT_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_TEXT_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_TEXT_MODEL], 1);
	TextDrawSetProportional(TD_join[TD_JOIN_TEXT_MODEL], 1);

	TD_join[TD_JOIN_MENU_TEXT] = TextDrawCreate(320.000000, 117.000000,
		!"œ–¿¬»À¿______________ƒ¿ÕÕ€≈_____________ÃŒƒ≈À‹");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_TEXT], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_TEXT], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_TEXT], 1010582783);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_TEXT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_TEXT], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_TEXT], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_TEXT], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_TEXT], 1);

	TD_join[TD_JOIN_LIGHTER] = TextDrawCreate(230.0, 135.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_LIGHTER], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_LIGHTER], 180.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_LIGHTER], 1);
	TextDrawColor(TD_join[TD_JOIN_LIGHTER], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_LIGHTER], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_LIGHTER], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_LIGHTER], 51);
	TextDrawFont(TD_join[TD_JOIN_LIGHTER], 4);
	TextDrawSetProportional(TD_join[TD_JOIN_LIGHTER], 1);

	TD_join[TD_JOIN_BUTTON] = TextDrawCreate(250.0, 320.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON], 140.000000, 25.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON], 4);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON], true);

	TD_join[TD_JOIN_BUTTON_START] = TextDrawCreate(320.0, 322.0, !"Õ¿◊¿“‹");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_START], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_START], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_START], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_START], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_START], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_START], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_START], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_START], 1);

	TD_join[TD_JOIN_BUTTON_RULES] = TextDrawCreate(320.0, 322.0,
		!"Œ«Õ¿ ŒÃ»“‹—ﬂ");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_RULES], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_RULES], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_RULES], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_RULES], 1);

	TD_join[TD_JOIN_BUTTON_PARAMS] = TextDrawCreate(320.0, 322.0, !"—Œ’–¿Õ»“‹");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_PARAMS], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_PARAMS], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_PARAMS], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_PARAMS], 1);

	TD_join[TD_JOIN_BUTTON_MODEL] = TextDrawCreate(320.0, 322.0, !"«¿¬≈–ÿ»“‹");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_MODEL], 0.400000, 2.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_MODEL], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_MODEL], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_MODEL], 1);

	TD_join[TD_JOIN_BAR] = TextDrawCreate(230.0, 365.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BAR], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BAR], 180.000000, 10.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BAR], 1);
	TextDrawColor(TD_join[TD_JOIN_BAR], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_BAR], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BAR], 0);
	TextDrawFont(TD_join[TD_JOIN_BAR], 4);

	TD_join[TD_JOIN_BG_RULES] = TextDrawCreate(230.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_RULES], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_RULES], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_RULES], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_RULES], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_RULES], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_RULES], 4);

	TD_join[TD_JOIN_BG_PARAMS] = TextDrawCreate(290.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_PARAMS], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_PARAMS], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_PARAMS], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_PARAMS], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_PARAMS], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_PARAMS], 4);

	TD_join[TD_JOIN_BG_MODEL] = TextDrawCreate(350.0, 130.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_BG_MODEL], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_BG_MODEL], 60.000000, 5.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BG_MODEL], 1);
	TextDrawColor(TD_join[TD_JOIN_BG_MODEL], 497793023);
	TextDrawSetShadow(TD_join[TD_JOIN_BG_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BG_MODEL], 0);
	TextDrawFont(TD_join[TD_JOIN_BG_MODEL], 4);

	TD_join[TD_JOIN_ARROW_RULES] = TextDrawCreate(250.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_RULES], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_RULES], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_RULES], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_RULES], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_RULES], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_RULES], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_RULES], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_RULES], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_RULES], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_ARROW_PARAMS] = TextDrawCreate(310.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_PARAMS], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_PARAMS], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_PARAMS], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_PARAMS], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_PARAMS], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_PARAMS], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_PARAMS], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_PARAMS], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_PARAMS], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_ARROW_MODEL] = TextDrawCreate(370.0, 118.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_ARROW_MODEL], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_ARROW_MODEL], 20.000000, 20.000000);
	TextDrawAlignment(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawColor(TD_join[TD_JOIN_ARROW_MODEL], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_ARROW_MODEL], true);
	TextDrawBoxColor(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_ARROW_MODEL], 0);
	TextDrawFont(TD_join[TD_JOIN_ARROW_MODEL], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_ARROW_MODEL], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_ARROW_MODEL], 1318);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_ARROW_MODEL], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_MENU_RULES] = TextDrawCreate(260.0, 117.0, !"œ–¿¬»À¿");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_RULES], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_RULES], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_RULES], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_RULES], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_RULES], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_RULES], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_RULES], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_RULES], 1);

	TD_join[TD_JOIN_MENU_PARAMS] = TextDrawCreate(323.5, 117.0, !"ƒ¿ÕÕ€≈");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_PARAMS], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_PARAMS], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_PARAMS], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_PARAMS], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_PARAMS], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_PARAMS], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_PARAMS], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_PARAMS], 1);

	TD_join[TD_JOIN_MENU_MODEL] = TextDrawCreate(383.0, 117.0, !"ÃŒƒ≈À‹");
	TextDrawLetterSize(TD_join[TD_JOIN_MENU_MODEL], 0.200000, 1.000000);
	TextDrawAlignment(TD_join[TD_JOIN_MENU_MODEL], 2);
	TextDrawColor(TD_join[TD_JOIN_MENU_MODEL], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_MENU_MODEL], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_MENU_MODEL], 0);
	TextDrawBackgroundColor(TD_join[TD_JOIN_MENU_MODEL], 51);
	TextDrawFont(TD_join[TD_JOIN_MENU_MODEL], 2);
	TextDrawSetProportional(TD_join[TD_JOIN_MENU_MODEL], 1);

	TD_join[TD_JOIN_TABLE_OUT] = TextDrawCreate(234.5, 178.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_OUT], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_OUT], 171.000000, 136.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_OUT], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_OUT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_TABLE_OUT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_OUT], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_OUT], 4);

	TD_join[TD_JOIN_TABLE_BG] = TextDrawCreate(235.0, 178.5, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_BG], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_BG], 170.000000, 135.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_BG], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_BG], 673722623);
	TextDrawUseBox(TD_join[TD_JOIN_TABLE_BG], true);
	TextDrawBoxColor(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_BG], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_BG], 4);

	TD_join[TD_JOIN_TABLE_DIV] = TextDrawCreate(265.0, 178.5, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_DIV], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_DIV], 0.500000, 135.000000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_DIV], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_DIV], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_DIV], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_DIV], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_DIV], 4);

	TD_join[TD_JOIN_TABLE_TOP] =
		TextDrawCreate(235.0, 212.25, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_TOP], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_TOP], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_TOP], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_TOP], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_TOP], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_TOP], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_TOP], 4);

	TD_join[TD_JOIN_TABLE_MIDDLE] =
		TextDrawCreate(235.0, 246.0, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_MIDDLE], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_MIDDLE], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_MIDDLE], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_MIDDLE], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_MIDDLE], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_MIDDLE], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_MIDDLE], 4);

	TD_join[TD_JOIN_TABLE_BOTTOM] =
		TextDrawCreate(235.0, 279.75, !"LD_SPAC:white");
	TextDrawLetterSize(TD_join[TD_JOIN_TABLE_BOTTOM], 0.000000, 0.000000);
	TextDrawTextSize(TD_join[TD_JOIN_TABLE_BOTTOM], 170.000000, 0.500000);
	TextDrawAlignment(TD_join[TD_JOIN_TABLE_BOTTOM], 1);
	TextDrawColor(TD_join[TD_JOIN_TABLE_BOTTOM], -1);
	TextDrawSetShadow(TD_join[TD_JOIN_TABLE_BOTTOM], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_TABLE_BOTTOM], 0);
	TextDrawFont(TD_join[TD_JOIN_TABLE_BOTTOM], 4);

	TD_join[TD_JOIN_IDCARD] = TextDrawCreate(235.0, 175.0, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_IDCARD], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_IDCARD], 30.000000, 40.000000);
	TextDrawAlignment(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawColor(TD_join[TD_JOIN_IDCARD], -1);
	TextDrawUseBox(TD_join[TD_JOIN_IDCARD], true);
	TextDrawBoxColor(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_IDCARD], 0);
	TextDrawFont(TD_join[TD_JOIN_IDCARD], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_IDCARD], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_IDCARD], 1581);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_IDCARD], 0.0, 0.0, 180.0, 1.0);

	TD_join[TD_JOIN_PADLOCK] = TextDrawCreate(233.000000, 211.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_PADLOCK], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_PADLOCK], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawColor(TD_join[TD_JOIN_PADLOCK], -1);
	TextDrawUseBox(TD_join[TD_JOIN_PADLOCK], true);
	TextDrawBoxColor(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_PADLOCK], 0);
	TextDrawFont(TD_join[TD_JOIN_PADLOCK], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_PADLOCK], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_PADLOCK], 19804);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_PADLOCK], 0.0, 0.0, 180.0, 1.0);

	TD_join[TD_JOIN_PAPER] = TextDrawCreate(232.000000, 245.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_PAPER], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_PAPER], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_PAPER], 1);
	TextDrawColor(TD_join[TD_JOIN_PAPER], -1);
	TextDrawUseBox(TD_join[TD_JOIN_PAPER], true);
	TextDrawBoxColor(TD_join[TD_JOIN_PAPER], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_PAPER], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_PAPER], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_PAPER], 0);
	TextDrawFont(TD_join[TD_JOIN_PAPER], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_PAPER], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_PAPER], 2684);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_PAPER], 0.0, 0.0, 180.000000, 1.0);

	TD_join[TD_JOIN_QUESTION] = TextDrawCreate(233.000000, 279.000000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_QUESTION], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_QUESTION], 35.000000, 35.000000);
	TextDrawAlignment(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawColor(TD_join[TD_JOIN_QUESTION], -1);
	TextDrawUseBox(TD_join[TD_JOIN_QUESTION], true);
	TextDrawBoxColor(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_QUESTION], 0);
	TextDrawFont(TD_join[TD_JOIN_QUESTION], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_QUESTION], 1);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_QUESTION], -1);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_QUESTION], 0.0, 0.0, 0.0, 1.0);

	TD_join[TD_JOIN_BUTTON_LEFT] = TextDrawCreate(230.0000, 200.000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_LEFT], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON_LEFT], 60.000000, 65.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_LEFT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_BUTTON_LEFT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_LEFT], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_LEFT], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_LEFT], 1);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON_LEFT], true);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_BUTTON_LEFT], 19131);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_BUTTON_LEFT], 0.0, 0.0, 90.0, 1.0);

	TD_join[TD_JOIN_BUTTON_RIGHT] = TextDrawCreate(350.000, 200.000, !"_");
	TextDrawLetterSize(TD_join[TD_JOIN_BUTTON_RIGHT], 0.449999, 1.600000);
	TextDrawTextSize(TD_join[TD_JOIN_BUTTON_RIGHT], 60.000000, 65.000000);
	TextDrawAlignment(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawColor(TD_join[TD_JOIN_BUTTON_RIGHT], -1);
	TextDrawUseBox(TD_join[TD_JOIN_BUTTON_RIGHT], true);
	TextDrawBoxColor(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawSetShadow(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawSetOutline(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawBackgroundColor(TD_join[TD_JOIN_BUTTON_RIGHT], 0);
	TextDrawFont(TD_join[TD_JOIN_BUTTON_RIGHT], 5);
	TextDrawSetProportional(TD_join[TD_JOIN_BUTTON_RIGHT], 1);
	TextDrawSetSelectable(TD_join[TD_JOIN_BUTTON_RIGHT], true);
	TextDrawSetPreviewModel(TD_join[TD_JOIN_BUTTON_RIGHT], 19131);
	TextDrawSetPreviewRot(TD_join[TD_JOIN_BUTTON_RIGHT], 0.0, 0.0, -90.0, 1.0);
}


stock LoadPlayerLoginTextDraws(playerid)
{
	PTD_login[playerid][PTD_LOGIN_NAME] =
		CreatePlayerTextDraw(playerid,
			333.0, 180.5, player[playerid][player_name]);
	PlayerTextDrawLetterSize(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 2);
	PlayerTextDrawColor(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 255);
	PlayerTextDrawSetShadow(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 0);
	PlayerTextDrawSetOutline(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 51);
	PlayerTextDrawFont(playerid, PTD_login[playerid][PTD_LOGIN_NAME], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_login[playerid][PTD_LOGIN_NAME], 1);

	PTD_login[playerid][PTD_LOGIN_PASSWORD] =
		CreatePlayerTextDraw(playerid, 333.0, 209.0, !"¬‚Â‰ËÚÂ_Ô‡ÓÎ¸");
	PlayerTextDrawLetterSize(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 14.0, 120.0);
	PlayerTextDrawAlignment(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 2);
	PlayerTextDrawColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], -589505281);
	PlayerTextDrawUseBox(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], true);
	PlayerTextDrawBoxColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawSetShadow(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 51);
	PlayerTextDrawFont(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_login[playerid][PTD_LOGIN_PASSWORD], true);
}


stock LoadPlayerJoinTextDraws(playerid)
{
	PTD_join[playerid][PTD_JOIN_BAR] =
		CreatePlayerTextDraw(playerid, 230.0, 365.0, !"LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR], 0.0, 0.0);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR], 0.0, 10.0);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_BAR], 1);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_BAR], 497793023);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_BAR], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_BAR], 0);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_BAR], 4);

	PTD_join[playerid][PTD_JOIN_BAR_TEXT] =
		CreatePlayerTextDraw(playerid, 320.0, 365.0, !#«‡‚Â¯ÂÌÓ:_0%);
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0.250, 1.00);
	PlayerTextDrawAlignment(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 673722623);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_BAR_TEXT], 3);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_BAR_TEXT], 1);

	PTD_join[playerid][PTD_JOIN_NAME] =
		CreatePlayerTextDraw(playerid, 335.5, 185.0,
			player[playerid][player_name]);
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 0.300000, 2.000000);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_NAME], 2);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_NAME], -1);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_NAME], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_NAME], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_NAME], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_NAME], 1);

	PTD_join[playerid][PTD_JOIN_PASSWORD] =
		CreatePlayerTextDraw(playerid, 335.5, 218.75, !"œ‡ÓÎ¸_ÌÂ_ÛÍ‡Á‡Ì");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 0.300000, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 20.00, 133.155563);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 1010582783);
	PlayerTextDrawUseBox(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawSetOutline(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_PASSWORD], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_PASSWORD], true);

	PTD_join[playerid][PTD_JOIN_MAIL] =
		CreatePlayerTextDraw(playerid, 335.5, 252.5, !"œÓ˜Ú‡_ÌÂ_ÛÍ‡Á‡Ì‡");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 0.30, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 20.0, 132.740753);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 1010582783);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_MAIL], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_MAIL], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_MAIL], true);

	PTD_join[playerid][PTD_JOIN_GENDER] =
		CreatePlayerTextDraw(playerid, 335.5, 286.25, !"œÓÎ_ÌÂ_‚˚·‡Ì");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 0.300000, 2.000000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 20.0, 132.740737);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 2);
	PlayerTextDrawColor(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 1010582783);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_GENDER], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 0);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 51);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_GENDER], 1);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], 1);
	PlayerTextDrawSetSelectable(playerid,
		PTD_join[playerid][PTD_JOIN_GENDER], true);

	PTD_join[playerid][PTD_JOIN_MODEL] =
		CreatePlayerTextDraw(playerid, 245.000000, 167.000000, !"_");
	PlayerTextDrawLetterSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 150.000000, 150.000000);
	PlayerTextDrawAlignment(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawUseBox(playerid, PTD_join[playerid][PTD_JOIN_MODEL], true);
	PlayerTextDrawBoxColor(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetShadow(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawSetOutline(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawBackgroundColor(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0);
	PlayerTextDrawFont(playerid, PTD_join[playerid][PTD_JOIN_MODEL], 5);
	PlayerTextDrawSetProportional(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 1);
	PlayerTextDrawSetPreviewModel(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], -1);
	PlayerTextDrawSetPreviewRot(playerid,
		PTD_join[playerid][PTD_JOIN_MODEL], 0.0, 0.0, 0.0, 1.0);
}