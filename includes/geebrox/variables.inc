#define KICK_TEXT_REASON \
	!COLOR_ERROR"Вы были отсоединены от сервера\nПричина: "COLOR_TITLE

#define KICK_TEXT_TIP \
	"\n\n"COLOR_NOTE"Чтобы выйти из игры используйте команду /q(uit)"

#define IsPVarSet(%0,%1) (GetPVarType(%0,%1) != PLAYER_VARTYPE_NONE)

#define IsPlayerSelectTextDraw(%0) IsPVarSet(%0, !"_select_td")


new
	Text: TD_death_screen,
	Iterator: Vehicle<MAX_VEHICLES>,
	Iterator: GlobalTextdraw<MAX_TEXT_DRAWS>,
	Iterator: PlayerTextdraw<MAX_PLAYER_TEXT_DRAWS>;