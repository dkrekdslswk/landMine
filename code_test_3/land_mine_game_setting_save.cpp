/**************************************************
* �� �� �� :	�ֺ���
* �������� :	2016. 08. 11 ~ 2016. 08. 16
* ��    �� :	���� ���� ���¸� �����ϴ� �Լ�
				unsaigned long�� �ϳ��� ���� ���ڰ� �� �����̸� �Ѱž� ��
				��ģ��.
***************************************************/


namespace land_mine_game_setting_save {
	// �ʱ� �� (9*9) ���ڼ� 10, ��� 1, Ȯ�μ��� 0
#define LAND_MINE_BEILD_BASE_SET		0x0080A249ul
#define LAND_MINE_GAME_SET_BIT			0x003ffffful
#define LAND_MINE_OPTION_SET_BIT		0xff800000ul

#define LAND_MINE_BEILD_HIGH_SAVE_BIT			0x0000001ful
#define LAND_MINE_BEILD_HIGH_MAX_SAVE_BIT		0x00000018ul
#define LAND_MINE_BEILD_HIGH_MIN_SAVE_BIT		0x00000009ul
#define LAND_MINE_BEILD_HIGH_MAX_SAVE			24
#define LAND_MINE_BEILD_HIGH_MIN_SAVE			9

#define LAND_MINE_BEILD_WIDTH_SAVE_BIT			0x000007c0ul
#define LAND_MINE_BEILD_WIDTH_MAX_SAVE_BIT		0x00000780ul
#define LAND_MINE_BEILD_WIDTH_MIN_SAVE_BIT		0x00000240ul
#define LAND_MINE_BEILD_WIDTH_MAX_SAVE			30
#define LAND_MINE_BEILD_WIDTH_MIN_SAVE			9

#define LAND_MINE_BEILD_MINE_SAVE_BIT			0x003ff000ul
#define LAND_MINE_BEILD_MINE_MIN_SAVE_BIT		0x0000a000ul
#define LAND_MINE_BEILD_MINE_MAX_SAVE			667
#define LAND_MINE_BEILD_MINE_MIN_SAVE			10

#define LAND_MINE_BEILD_GROUND_SAVE_BIT			0x07800000ul
#define LAND_MINE_BEILD_GROUND_MAX_SAVE_BIT		0x07800000ul
#define LAND_MINE_BEILD_GROUND_MIN_SAVE_BIT		0x00800000ul
#define LAND_MINE_BEILD_GROUND_MAX_SAVE			15
#define LAND_MINE_BEILD_GROUND_MIN_SAVE			1

#define LAND_MINE_BEILD_CHECK_SAVE_BIT			0x10000000ul
#define LAND_MINE_BEILD_CHECK_SAVE_TRUE			0x10000000ul
#define LAND_MINE_BEILD_CHECK_SAVE_FALSE		0x00000000ul

#define LAND_MINE_BEILD_HIGH_SAVE_POINT		0
#define LAND_MINE_BEILD_WIDTH_SAVE_POINT	6
#define LAND_MINE_BEILD_MINE_SAVE_POINT		12
#define LAND_MINE_BEILD_GROUND_SAVE_POINT	23
#define LAND_MINE_BEILD_CHECK_SAVE_POINT	28

	// ���� �� ���
	unsigned long	setting(void);
	unsigned long	game_setting(void);
	unsigned long	option_setting(void);
	int				high(void);
	int				width(void);
	int				mine(void);
	int				ground(void);
	bool			check(void); 
	int				max_mine(void);

	// ���� �Է� �޴� �Լ�
	void			setting_input(unsigned long input);
	void			game_setting_input(unsigned long input);
	void			option_setting_input(unsigned long input);
	void			high_input(int input);
	void			width_input(int input);
	void			mine_input(int input);
	void			ground_input(int input);
	void			check_input(bool input);

	// ���� �� �Լ�
	void			high_input(unsigned long input);
	void			width_input(unsigned long input);
	void			mine_check(void);

	// �ʱ� �� (9*9) ���ڼ� 10, ��� 1, Ȯ�μ��� 0
	static unsigned long land_mine_setting = LAND_MINE_BEILD_BASE_SET;
	// ��ü ������ ����
	unsigned long setting(void) {
		return land_mine_setting;
	}

	// ���� ���� ����
	unsigned long	game_setting(void) {
		return land_mine_setting & LAND_MINE_GAME_SET_BIT;
	}

	// �ɼ� ������ ����
	unsigned long	option_setting(void) {
		return land_mine_setting & LAND_MINE_OPTION_SET_BIT;
	}


	/*********************************************
	* �ڷᰪ�� ���� �ޱ�
	**********************************************/
	// 0000,0000,0000,0000,0000,0000,0001,1111
	// 0x0000001ful
	// (9)0x00000009~(24)0x00000018
	int high(void) {
		return ((land_mine_setting & LAND_MINE_BEILD_HIGH_SAVE_BIT) >> LAND_MINE_BEILD_HIGH_SAVE_POINT);
	}

	// 0000,0000,0000,0000,0000,0111,1100,0000
	// 0x000007e0ul
	// (9)0x00000240~(30)0x00000780
	int width(void) {
		return ((land_mine_setting & LAND_MINE_BEILD_WIDTH_SAVE_BIT) >> LAND_MINE_BEILD_WIDTH_SAVE_POINT);
	}

	// 0000,0000,0011,1111,1111,0000,0000,0000
	// 0x003ff000ul
	// (10)0x0000a000~(668)0x0029c000
	// �ִ� �� = ���� * 0.94 - 9
	int mine(void) {
		return ((land_mine_setting & LAND_MINE_BEILD_MINE_SAVE_BIT) >> LAND_MINE_BEILD_MINE_SAVE_POINT);
	}
	int max_mine(void) {
		return (int)(high() * width() * 0.94 - 9);
	}

	// 0000,0111,1000,0000,0000,0000,0000,0000
	// 0x07800000ul
	// (1)0x00800000~(15)0x07800000
	int ground(void) {
		return ((land_mine_setting & LAND_MINE_BEILD_GROUND_SAVE_BIT) >> LAND_MINE_BEILD_GROUND_SAVE_POINT);
	}

	// 0001,0000,0000,0000,0000,0000,0000,0000
	// 0x10000000ul
	// (true)0x10000000~(false)0x00000000
	bool check(void) {
		return ((land_mine_setting & LAND_MINE_BEILD_CHECK_SAVE_BIT) != 0);
	}


	/*****************************************************
	* �ڷ� ���� ���� �ϱ�
	******************************************************/
	void setting_input(unsigned long input) {
		high_input((input & LAND_MINE_BEILD_HIGH_SAVE_BIT)>>LAND_MINE_BEILD_HIGH_SAVE_POINT);
		width_input((input & LAND_MINE_BEILD_WIDTH_SAVE_BIT)>>LAND_MINE_BEILD_WIDTH_SAVE_POINT);
		mine_input((input & LAND_MINE_BEILD_MINE_SAVE_BIT)>>LAND_MINE_BEILD_MINE_SAVE_POINT);
		ground_input((int)((input & LAND_MINE_BEILD_GROUND_SAVE_BIT) >> LAND_MINE_BEILD_GROUND_SAVE_POINT));
		check_input((bool)((input & LAND_MINE_BEILD_CHECK_SAVE_BIT) != 0));
	}

	void game_setting_input(unsigned long input) {
		high_input((input & LAND_MINE_BEILD_HIGH_SAVE_BIT) >> LAND_MINE_BEILD_HIGH_SAVE_POINT);
		width_input((input & LAND_MINE_BEILD_WIDTH_SAVE_BIT) >> LAND_MINE_BEILD_WIDTH_SAVE_POINT);
		mine_input((input & LAND_MINE_BEILD_MINE_SAVE_BIT) >> LAND_MINE_BEILD_MINE_SAVE_POINT);
	}

	void option_setting_input(unsigned long input) {
		ground_input((int)((input & LAND_MINE_BEILD_GROUND_SAVE_BIT) >> LAND_MINE_BEILD_GROUND_SAVE_POINT));
		check_input((bool)((input & LAND_MINE_BEILD_CHECK_SAVE_BIT) != 0));
	}

	void high_input(int input) {
		land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_HIGH_SAVE_BIT);
		if (input <= LAND_MINE_BEILD_HIGH_MIN_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_HIGH_MIN_SAVE_BIT;
			mine_check();
		}
		else if (input >= LAND_MINE_BEILD_HIGH_MAX_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_HIGH_MAX_SAVE_BIT;
		}
		else {
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_HIGH_SAVE_POINT);
			mine_check();
		}
	}
	void high_input(unsigned long input) {
		land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_HIGH_SAVE_BIT);
		if (input <= LAND_MINE_BEILD_HIGH_MIN_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_HIGH_MIN_SAVE_BIT;
		}
		else if (input >= LAND_MINE_BEILD_HIGH_MAX_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_HIGH_MAX_SAVE_BIT;
		}
		else {
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_HIGH_SAVE_POINT);
		}
	}

	void width_input(int input) {
		land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_WIDTH_SAVE_BIT);
		if (input <= LAND_MINE_BEILD_WIDTH_MIN_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_WIDTH_MIN_SAVE_BIT;
			mine_check();
		}
		else if (input >= LAND_MINE_BEILD_WIDTH_MAX_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_WIDTH_MAX_SAVE_BIT;
		}
		else {
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_WIDTH_SAVE_POINT);
			mine_check();
		}
	}
	void width_input(unsigned long input) {
		land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_WIDTH_SAVE_BIT);
		if (input <= LAND_MINE_BEILD_WIDTH_MIN_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_WIDTH_MIN_SAVE_BIT;
		}
		else if (input >= LAND_MINE_BEILD_WIDTH_MAX_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_WIDTH_MAX_SAVE_BIT;
		}
		else {
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_WIDTH_SAVE_POINT);
		}
	}

	void mine_input(int input) {
		land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_MINE_SAVE_BIT);
		if ((input) >= max_mine()) {
			land_mine_setting = land_mine_setting + (((unsigned long)(high() * width() * 0.94 - 9)) << LAND_MINE_BEILD_MINE_SAVE_POINT);
		}
		else if (input <= LAND_MINE_BEILD_MINE_MIN_SAVE) {
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_MINE_MIN_SAVE_BIT;
		}
		else {
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_MINE_SAVE_POINT);
		}
	}
	void mine_check(void) {
		if (mine() >= max_mine()) {
			land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_MINE_SAVE_BIT);
			land_mine_setting = land_mine_setting + (((unsigned long)(high() * width() * 0.94 - 9)) << LAND_MINE_BEILD_MINE_SAVE_POINT);
		}
	}

	void ground_input(int input) {
		if (input <= LAND_MINE_BEILD_GROUND_MAX_SAVE && input >= LAND_MINE_BEILD_GROUND_MIN_SAVE) {
			land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_GROUND_SAVE_BIT);
			land_mine_setting = land_mine_setting + (input << LAND_MINE_BEILD_GROUND_SAVE_POINT);
		}
		else {
			land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_GROUND_SAVE_BIT);
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_GROUND_MIN_SAVE_BIT;
		}
	}

	void check_input(bool input) {
		if (input == true)
		{
			land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_CHECK_SAVE_BIT);
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_CHECK_SAVE_TRUE;
		}
		else {
			land_mine_setting = land_mine_setting & (~LAND_MINE_BEILD_CHECK_SAVE_BIT);
			land_mine_setting = land_mine_setting + LAND_MINE_BEILD_CHECK_SAVE_FALSE;
		}
	}
}