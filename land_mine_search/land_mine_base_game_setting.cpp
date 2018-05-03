/*******************************
* �� �� �� : �ֺ���
* �ۼ����� : 2016. 08. 11 ~ 2016. 08. 16
* ��    �� : ����ã�� ������ �⺻���� ���� ����
*******************************/

#include"fs_menu_screen_print.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"

// ���� ���̵� �� �� ������ ���� ���� �޴�
#define GAME_LEVEL_MENU			3 + 1

/* fs_menu()�Լ����� ��ȯ�Ǵ� ���� �⺻ ���� ���� ������ �ǹ� �ο� */
// ���ӷ��� ����
#define GAME_LEVEL_EASY			1
#define GAME_LEVEL_NOMAL		2
#define GAME_LEVEL_HARD			3
// ���� �޴� ȣ��
#define BEFORE_MENU_CALL		0

// ���� ���̵� ���� �� ũ�� (9 * 9), ���ڼ� 10
#define GAME_LEVEL_EASY_SET		0x00A249ul
// �븻 ���̵� ���� �� ũ�� (16 * 16), ���ڼ� 40
#define GAME_LEVEL_NOMAL_SET	0x028410ul
// �ϵ� ���̵� ���� �� ũ�� (16 * 30), ���ڼ� 99
#define GAME_LEVEL_HARD_SET		0x063790ul

// Ȥ�� �� �������� ������ �⺻���� ������������ ����
#define GAME_LEVEL_ERROR_SET	0x00A249ul

// �⺻ �� ����
int Base_Game_Set(unsigned long game_setting);

/*********************************************
* �� �� �� :	�ֺ���
* �ۼ����� :	2016. 08. 11
* �۵����� :	base ���� �������� game_setting���� �ʱ�ȭ
**********************************************/
int Base_Game_Setting(void) {
	// �޴� ������
	char base_game_menu_choice[GAME_LEVEL_MENU][22] = {	{ "1. ��г���EASY���\n" },
														{ "2. ����� NOMAL���\n" },
														{ "3. �̰Ա⺻HARD���\n" },
														{ "4. ��  ��    ��  ��\n" } };
	// �޴� ����ݳ��� ����
	int game_setting_return = 0;

	// �޴� â ������ ��ɾ� �ޱ�
	game_setting_return = fs_menu(base_game_menu_choice, GAME_LEVEL_MENU);

	// ���� ������ ���� �ʰ� �� �޴��� Ż��
	if (game_setting_return == BEFORE_MENU_CALL)
		// ���� �޴� ȣ������ ����
		return _MAIN_MENU_CALL;
	else {
		// ���������� ���� ������ ������ ���� �ޱ�
		game_setting_return = Base_Game_Set(game_setting_return);

		// ���� ���� ���� ����ҿ� ����
		land_mine_game_setting_save::game_setting_input(game_setting_return);

		// ���� ���� ȣ������ ����
		return _MAIN_GAME_START_CALL;
	}
}

// fs_menu()�Լ����� ���ϵ�
// �ܼ��� 0~4������ ��ȯ�� ���� ����
int Base_Game_Set(unsigned long game_setting) {

	// ���� (9*9), ���� 10��
	if (game_setting == GAME_LEVEL_EASY) {
		return GAME_LEVEL_EASY_SET;
	}
	// �븻 (16*16), ���� 40��
	else if (game_setting == GAME_LEVEL_NOMAL) {
		return GAME_LEVEL_NOMAL_SET;
	}
	// �ϵ� (16*30), ���� 99��
	else if (game_setting == GAME_LEVEL_HARD) {
		return GAME_LEVEL_HARD_SET;
	}

	// ���� �޴��� �̵� ���� ���� ���
	else if (game_setting == BEFORE_MENU_CALL) {
		return BEFORE_MENU_CALL;
	}
	// �߸��� �� �Է� ���� ��
	else
		return GAME_LEVEL_ERROR_SET;
}