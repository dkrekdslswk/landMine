/******************************************
�� �� �� : �ֺ���
�������� : 2016. 08. 10 ~
��    �� : ����ã�� �ܼ� ���α׷� ����
*******************************************/

// ���θ޴� �����
#include"land_mine.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"
#include"fs_conio_order.h"

#include<stdio.h>
#include<windows.h>

int main(void) {

	system("COLOR f0");

	// �����Լ� Ʈ���ſ� ���
	int main_order = _MAIN_MENU_CALL;
	// game setting �� ����
	unsigned long game_setting_save = 0x00800000ul;
	// game setting �� �ޱ�
	unsigned long *game_setting = &game_setting_save;

	resz(40, 20);
	do {
		switch (main_order) {
		// ���� �޴� ȣ��
		case _MAIN_MENU_CALL:
			main_order = Main_Menu();
			break;
		// ���� ����
		// �⺻ ����(���̵� ����)
		case _MAIN_BASE_LEVEL_CALL:
			main_order = Base_Game_Setting();
			break;

		// ���� ����(���̵� ����)
		case _MAIN_USER_LEVEL_CALL:
			main_order = User_Game_Setting();
			break;

			/*
		// �ɼ� ���� �ޱ� (�̱���)
		case _MAIN_OPTION_CALL:
			break;
			*/
			
		// ������ �޾Ƽ� ������ ����
		case _MAIN_GAME_START_CALL:
			main_order = Land_Mine_Map_Build();
			break;

		default:
			main_order = 0;
			break;
		}
	} while (main_order != _MAIN_END);

	return 0;
}