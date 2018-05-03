/******************************************
작 성 자 : 최병찬
작정일자 : 2016. 08. 10 ~
제    목 : 지뢰찾기 콘솔 프로그램 게임
*******************************************/

// 메인메뉴 선언부
#include"land_mine.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"
#include"fs_conio_order.h"

#include<stdio.h>
#include<windows.h>

int main(void) {

	system("COLOR f0");

	// 메인함수 트리거용 명령
	int main_order = _MAIN_MENU_CALL;
	// game setting 값 저장
	unsigned long game_setting_save = 0x00800000ul;
	// game setting 값 받기
	unsigned long *game_setting = &game_setting_save;

	resz(40, 20);
	do {
		switch (main_order) {
		// 메인 메뉴 호출
		case _MAIN_MENU_CALL:
			main_order = Main_Menu();
			break;
		// 게임 시작
		// 기본 설정(난이도 설정)
		case _MAIN_BASE_LEVEL_CALL:
			main_order = Base_Game_Setting();
			break;

		// 유저 설정(난이도 설정)
		case _MAIN_USER_LEVEL_CALL:
			main_order = User_Game_Setting();
			break;

			/*
		// 옵션 설정 받기 (미구현)
		case _MAIN_OPTION_CALL:
			break;
			*/
			
		// 설정을 받아서 게임을 시작
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