/*********************************************
* �� �� �� :	�ֺ���
* �ۼ����� :	2016. 08. 11 ~ 2016. 08. 16
* �۵����� :	base ���� �������� game_setting���� �ʱ�ȭ
**********************************************/

/* ��Ŭ��� ���� �� */
#include"fs_menu_screen_print.h"
#include"fs_unsigned_integer.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"
#include<stdio.h>
#include<windows.h>

// ���� ���̵� ������ �������̵��� ����
// ���� ���̵� ���� �� ũ�� (9 * 9), ���ڼ� 10
#define GAME_LEVEL_EASY_SET		0x00A249ul

/* ����� ���� ������ �޴��� ��
*  fs_menu() �Լ��� ����Ҷ� ���*/
#define USER_GAME_SETTING_MENU		5

/* fs_menu()�� ��ȯ���� ���� ��ɻ�� �ǹ� �ο� */
// ���� �Է¹ޱ�
#define USER_GAME_SETTING_HEIGHT		1
// ���α��� �Է¹ޱ�
#define USER_GAME_SETTING_WIDTH			2
// ���ڼ� �Է¹ޱ�
#define USER_GAME_SETTING_MINE			3
// �Է� ���� �� ���� ����
#define USER_GAME_SETTING_END			4
// �Է� ��� �� �����޴� ȣ��
#define USER_GAME_SETTING_OUT			0

// ���� ���� ������� ǥ�ø� �� ��ġ
#define USER_GAME_SETTING_MENU_HEIGHT		0
#define USER_GAME_SETTING_MENU_HEIGHT_10	17	
#define USER_GAME_SETTING_MENU_HEIGHT_01	18

// ���α��� ���� ������� ǥ�ø� �� ��ġ
#define USER_GAME_SETTING_MENU_WIDTH		1
#define USER_GAME_SETTING_MENU_WIDTH_10		17	
#define USER_GAME_SETTING_MENU_WIDTH_01		18

// ���� �� ���� ������� ǥ�ø� �� ��ġ
#define USER_GAME_SETTING_MENU_MINE			2
#define USER_GAME_SETTING_MENU_MINE_100		16	
#define USER_GAME_SETTING_MENU_MINE_010		17
#define USER_GAME_SETTING_MENU_MINE_001		18
// ���� ������ �ִ� ���ڼ��� ǥ���� ��ġ
#define USER_GAME_SETTING_MENU_MAX_MINE_100		10	
#define USER_GAME_SETTING_MENU_MAX_MINE_010		11
#define USER_GAME_SETTING_MENU_MAX_MINE_001		12

/* fs_Output_Unsigned_Integer() �Լ��� �Էµ� �������� �ְ�*/
// ������ ���� �ְ�
#define LAND_MINE_BEILD_HIGH_MAX_SAVE			24
#define LAND_MINE_BEILD_HIGH_MIN_SAVE			9
// ���α����� ���� �ְ�
#define LAND_MINE_BEILD_WIDTH_MAX_SAVE			30
#define LAND_MINE_BEILD_WIDTH_MIN_SAVE			9
// ���ڼ��� ������ (�ִ� ���ڼ��� ���̿� ���� �����Ǳ⿡ ����ҿ��� ��������� �ִ���� ���� �ҷ��� ���)
#define LAND_MINE_BEILD_MINE_MIN_SAVE			10

int User_Game_Setting() {

	// ���� ���� �޴�
	char user_game_setting_menu_choice[USER_GAME_SETTING_MENU][22] = {	{ "��  ��(9 ~ 24):  09\n" },
																		{ "��  ��(9 ~ 30):  09\n" },
																		{ "���ڼ�(10~067): 010\n" },
																		{ "��   ��    ��    ��\n" },
																		{ "��   ��    ��    ��\n" } };

	// ������ �⺻ �������� ����
	unsigned long	user_game_setting_return	= land_mine_game_setting_save::game_setting();
	// ������� ���� �⺻ �������� �ʱ�ȭ
	land_mine_game_setting_save::game_setting_input(GAME_LEVEL_EASY_SET);

	// ���� ���� �޴� ��ɰ�
	int				user_game_setting_order		= 0;

	// ���� ����
	do {
		// ���ڼ��� ���� �� �Է� ������ ���� �ִ� ���̿� ���� ����
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_100] = land_mine_game_setting_save::max_mine() / 100 + '0';
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_010] = (land_mine_game_setting_save::max_mine() % 100) / 10 + '0';
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_001] = land_mine_game_setting_save::max_mine() % 10 + '0';

		// �޴� ȣ��
		user_game_setting_order = fs_menu(user_game_setting_menu_choice, USER_GAME_SETTING_MENU);

		// ��ɰ� ����
		switch (user_game_setting_order) {
			// ���̰��� �����ϰ� �޴��� ǥ���� ���� ����
		case USER_GAME_SETTING_HEIGHT:
			land_mine_game_setting_save::high_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_HIGH_MIN_SAVE, LAND_MINE_BEILD_HIGH_MAX_SAVE, land_mine_game_setting_save::high()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_HEIGHT][USER_GAME_SETTING_MENU_HEIGHT_10] = land_mine_game_setting_save::high() / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_HEIGHT][USER_GAME_SETTING_MENU_HEIGHT_01] = land_mine_game_setting_save::high() % 10 + '0';
			break;
			// ���α��̰��� �����ϰ� �޴��� ǥ���� ���� ����
		case USER_GAME_SETTING_WIDTH:
			land_mine_game_setting_save::width_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_WIDTH_MIN_SAVE, LAND_MINE_BEILD_WIDTH_MAX_SAVE, land_mine_game_setting_save::width()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_WIDTH][USER_GAME_SETTING_MENU_WIDTH_10] = land_mine_game_setting_save::width() / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_WIDTH][USER_GAME_SETTING_MENU_WIDTH_01] = land_mine_game_setting_save::width() % 10 + '0';
			break;
			// ���ڼ��� �����ϰ� �޴��� ǥ���� ���� ����
		case USER_GAME_SETTING_MINE:
			land_mine_game_setting_save::mine_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_MINE_MIN_SAVE, land_mine_game_setting_save::max_mine(), land_mine_game_setting_save::mine()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_100] = land_mine_game_setting_save::mine() / 100 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_010] = (land_mine_game_setting_save::mine() % 100) / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_001] = land_mine_game_setting_save::mine() % 10 + '0';
			break;
			// ���� ���� �ƴ� ���� �������� ����.
			//(USER_GAME_SETTING_HEIGHT, USER_GAME_SETTING_WIDTH, USER_GAME_SETTING_MINE)
		default:
			break;
		}
		
		// ȭ�� �ʱ�ȭ
		system("cls");

		// �Է��� �����ϰų� ����ҽ� �ݺ��� Ż��
	} while ((user_game_setting_order != USER_GAME_SETTING_END) && (user_game_setting_order != USER_GAME_SETTING_OUT));

	// �Է���ҽ� ������ ������ �ʱ�ȭ�ϰ� ���θ޴��� ȣ���ϴ� ����� �ݳ�
	if (user_game_setting_order == USER_GAME_SETTING_OUT) {
		land_mine_game_setting_save::game_setting_input(user_game_setting_return);
		return _MAIN_MENU_CALL;
	}
	// �Է���Ұ� �ƴ�(�Է� ������) ����̸� ���� �Է°����� ������ ����
	else
		return _MAIN_GAME_START_CALL;
}