enum PLAYER_LOGIN_STATUS_INFO
{
	PLAYER_LOGIN_STATUS_CONNECTED = 1,
	PLAYER_LOGIN_STATUS_LOGGED
};

enum PLAYER_JOIN_STATUS_INFO
{
	PLAYER_JOIN_STATUS_NONE,
	PLAYER_JOIN_STATUS_START,
	PLAYER_JOIN_STATUS_RULES,
	PLAYER_JOIN_STATUS_PARAMS,
	PLAYER_JOIN_STATUS_MODEL
};

enum PLAYER_DATA
{
	ORM: player_orm,
	player_uid,
	player_name[MAX_PLAYER_NAME],
	player_password[64 + 1],
	player_login_password[MAX_PLAYER_PASSWORD + 1],
	player_salt[64 + 1],
	player_mail[MAX_PLAYER_MAIL],
	player_login_attempts,
	player_gender,
	player_model,
	player_ip[MAX_PLAYER_IP],
	PLAYER_LOGIN_STATUS_INFO: player_login_status,
	PLAYER_JOIN_STATUS_INFO: player_join_status,
	Float: player_join_progress,
	player_bg_color
};


new
	player[MAX_PLAYERS][PLAYER_DATA],
	clear_player_data[PLAYER_DATA];

new join_text[][] =
{
	!"�����_����������_��_������, \"Geebrox_Role_Play\" \
		����_�������_��_���������������! ������_������_�����������?",
	
	!"��_�����_�������_���������� ���_������,_�������_������_��������� \
		������_�����,_��������_������������ �_����_�����_������������:",
	
	!"���������_���_������, �����_����������_�����������:",
	
	!"��������_������_���������, �����_���������_�����������:",

	!COLOR_TEXT"���������� ����� ������ ��� ����� � ��� �������.\n\
		������������, ����� ������ ��� ����� �������������� ��� ���,\n\
		�� ������� ��� ���������������!\n\n\
		"COLOR_NOTE"����������:\n\t\
		� ������ ����� ��������� ����� ���������� ��������, �����,   \n\t\
		������, ������� ������������� � �����\n\t\
		� ��������� ������������ ����� ������ ������������� �������� ������\n\t\
		� ����� ������ ���� ������, ��� "#MAX_PLAYER_PASSWORD" \
		� ������, ��� "#MIN_PLAYER_PASSWORD" ��������\n\n\
		"COLOR_TEXT"���������� ���� ����� ������ � ������� ����:",

	!COLOR_TEXT"������� ���� ����������� �����\n\
		�� ���� ����� ���������� ������ � ����� ��� �������������\n\
		"COLOR_NOTE"���������, ��� ����� \
		����������� ����� ������ ���������:",

	!COLOR_TEXT"�� ��������� ����������� ����� ��� ������ ��� \
		������������� ��������� �� 4 ����\n������ ������ �������� ���������, \
		�� �������� ��������� 5-10 �����\n\
		"COLOR_NOTE"�� �������� ��������� ����� ����\n\n\
		"COLOR_TEXT"��� ����������� ������ ��� �������������:"
};

new const server_rules[][] =
{
	!COLOR_ERROR"1. "COLOR_NOTE"�� ������� � �� �������:\n\n\t\
		"COLOR_ERROR"1.1 "COLOR_NOTE"MG [Metagaming] - "COLOR_TEXT"\
		������������� ��� ������� ���������� [���] � ������� ���� [IC].\n\t\
		������������ ����� �� 30 �����. ��� ������������� ��� ������� \
		���������� � ���� ���� ��� ������� ��� (( /n )).\n\t\t\
		"COLOR_ERROR"������:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"�� ������������� ������ ���������� \
			\"��� ����� \"��\"?.\n\t\t�� �������� \"���� �� �����\" ������ \
			\"������ ����������\" � �.�\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"� ���.����������� ����� �������� � \
			�����, ��� �� ������ ����� �� ���������:\n\t\t\
			\"� ����� ����� �� �����, ���������� ����\", � ������ \"� ������� \
			����� �� ����� � ����� ��������\" � �.�\n\n\t\
		"COLOR_ERROR"1.2 "COLOR_NOTE"�� [DeathMatch] - "COLOR_TEXT"�������� \
		������ ��� ������� �������. ������������ ���.\n\t\
		��������� ������� �� ������� ���������. ��� ������ �������� - ��� �� 7 \
		����.\n\t\t\
		"COLOR_ERROR"������:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"�� ������, ���� ��� ��������� �����, \
			�� ��������� ��� ����/�������� � ���� ������ ���.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"� ������� ������ ����� ����� ����� \
			�������. ��� �� ������, ������� �� ��������� �� ����,\n\t\t\
			����� ��������� � ���������� ���� ������.\n\n\t\
		"COLOR_ERROR"1.3 "COLOR_NOTE"�� [DriveBy] - "COLOR_TEXT"�������� \
		������ � ������� ������������� �������� ��� � �������������\
		\\������������� �����,\n\t\
		���� ��� �������� ���������. ������������ ��� �� 60� �����.\n\t\t\
		"COLOR_ERROR"������:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"�� ����� ����, � ��� �������� �������� \
			������ �����, �� � �����, ������� ��� �����, ������ \
			�����������.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"�� �����������, ����� �� ���������� �� \
			������ ���������� �����������/������������\n\t\t\
			����� �������� ������������ ��� ���.\n\t\t\
			"COLOR_ERROR"3) "COLOR_TEXT"�� ������ �� ��������, � ��� ��������� \
			�������, ���� ���� ������ � �������,\n\t\t\
			�� �� ��� ����� � ��������� ��� ������.\n\n\t\
		"COLOR_ERROR"1.4 "COLOR_NOTE"�� [SpawnKill] - "COLOR_TEXT"�������� \
		������ �� ����� �����������. ������������ ��� 60 �����.\n\t\t\
		"COLOR_ERROR"������:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"����� ��������� �� ����� ����������� \
			����� � �������� �������� �� ����, ���� ������.",
	
	!COLOR_ERROR"\t1.5 "COLOR_NOTE"�� [PowerGaming] - "COLOR_TEXT"����������� \
	���� ������. �������������� ����� ����������\\��������������� ���.\n\t\t\
		"COLOR_ERROR"������:\n\t\t\
			"COLOR_ERROR"1) "COLOR_TEXT"�������������� �� ���������� � \
			��������, ����� � ��� �������� ������������.\n\t\t\
			"COLOR_ERROR"2) "COLOR_TEXT"���������� � �������� �� ���������� \
			����������, ����� � ��� ����, ��������� � �.�\n\t\t\
			"COLOR_ERROR"3) "COLOR_TEXT"����� ���� ���������� �������, ���� \
			��� ���-�� ���, ������� ��� ��������.\n\t\t\
			�������� � ��� � ����� ���������� ������ [��������� ���������� � \
			�������] � �� ��������� ��������������.\n\n\t\
		"COLOR_ERROR"1.6 "COLOR_NOTE"�� [TeamKill] - "COLOR_TEXT"�������� \
		����� ����� �����������/�����/����� ��� �������.\n\n\t\
		"COLOR_ERROR"1.7 "COLOR_NOTE"�� [RepeatKill] - "COLOR_TEXT"����������/\
		��������� �������� ������ � ���� �� ������.\n\n\
	"COLOR_ERROR"2. "COLOR_NOTE"��������� �������:\n\n\t\
		"COLOR_ERROR"2.1 "COLOR_NOTE"AFK [������ �� ����������/Away From \
		KeyBoard] - "COLOR_TEXT"��� �� ���������� \"�� ����\". �����, ������� \
		�������� ������.\n\t\
		������, ��������� � ���.������������ ������������ ����� �� AFK ��� \
		����������� ������� �� ����� �������� ���.\n\n\t\
		"COLOR_ERROR"2.2 "COLOR_NOTE"RolePlay NickName - "COLOR_TEXT"������� \
		��� � ������� \"���_�������\". ����������� �������� � ������������ ��� \
		�� ����.\n\t\
		������ ����������� ����: John_Smith, Rey_Grover � �.�\n\n\t\
		"COLOR_ERROR"2.3 "COLOR_NOTE"Bagouse [������] - "COLOR_TEXT"\
		������������� ����� � ����. �� ������������� ������������� \
		��������� �����.\n\t\
		��������� ������� �� ������� ������� ���������."
};

new
	player_models[2][] =
	{
		{PLAYER_MODELS_MALE, -1},
		{PLAYER_MODELS_FEMALE, -1}
	},

	player_models_size[sizeof player_models];