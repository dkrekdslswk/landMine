/*******************************
* 작 성 자 : 최병찬
* 작성일자 : 2016. 08. 11 ~ 2016. 08. 16
* 목    적 : 지뢰찾기 게임의 기본적인 게임 셋팅
*******************************/

#include"fs_menu_screen_print.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"

// 게임 난이도 수 와 마지막 줄인 이전 메뉴
#define GAME_LEVEL_MENU			3 + 1

/* fs_menu()함수에서 반환되는 값을 기본 게임 셋팅 전용의 의미 부여 */
// 게임레벨 설정
#define GAME_LEVEL_EASY			1
#define GAME_LEVEL_NOMAL		2
#define GAME_LEVEL_HARD			3
// 이전 메뉴 호출
#define BEFORE_MENU_CALL		0

// 이지 난이도 셋팅 맵 크기 (9 * 9), 지뢰수 10
#define GAME_LEVEL_EASY_SET		0x00A249ul
// 노말 난이도 셋팅 맵 크기 (16 * 16), 지뢰수 40
#define GAME_LEVEL_NOMAL_SET	0x028410ul
// 하드 난이도 셋팅 맵 크기 (16 * 30), 지뢰수 99
#define GAME_LEVEL_HARD_SET		0x063790ul

// 혹시 모를 에러값이 나오면 기본적인 이지셋팅으로 리턴
#define GAME_LEVEL_ERROR_SET	0x00A249ul

// 기본 값 저장
int Base_Game_Set(unsigned long game_setting);

/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11
* 작동원리 :	base 적인 설정으로 game_setting값을 초기화
**********************************************/
int Base_Game_Setting(void) {
	// 메뉴 선택지
	char base_game_menu_choice[GAME_LEVEL_MENU][22] = {	{ "1. 기분나쁜EASY모드\n" },
														{ "2. 평범한 NOMAL모드\n" },
														{ "3. 이게기본HARD모드\n" },
														{ "4. 이  전    메  뉴\n" } };
	// 메뉴 실행반납값 저장
	int game_setting_return = 0;

	// 메뉴 창 실행해 명령어 받기
	game_setting_return = fs_menu(base_game_menu_choice, GAME_LEVEL_MENU);

	// 게임 설정을 하지 않고 전 메뉴로 탈출
	if (game_setting_return == BEFORE_MENU_CALL)
		// 메인 메뉴 호출명령을 리턴
		return _MAIN_MENU_CALL;
	else {
		// 최종적으로 게임 설정을 변경할 값을 받기
		game_setting_return = Base_Game_Set(game_setting_return);

		// 받은 설정 값을 저장소에 저장
		land_mine_game_setting_save::game_setting_input(game_setting_return);

		// 게임 시작 호출명령을 리턴
		return _MAIN_GAME_START_CALL;
	}
}

// fs_menu()함수에서 리턴된
// 단순한 0~4까지의 반환된 값을 변경
int Base_Game_Set(unsigned long game_setting) {

	// 이지 (9*9), 지뢰 10개
	if (game_setting == GAME_LEVEL_EASY) {
		return GAME_LEVEL_EASY_SET;
	}
	// 노말 (16*16), 지뢰 40개
	else if (game_setting == GAME_LEVEL_NOMAL) {
		return GAME_LEVEL_NOMAL_SET;
	}
	// 하드 (16*30), 지뢰 99개
	else if (game_setting == GAME_LEVEL_HARD) {
		return GAME_LEVEL_HARD_SET;
	}

	// 이전 메뉴로 이동 값이 나올 경우
	else if (game_setting == BEFORE_MENU_CALL) {
		return BEFORE_MENU_CALL;
	}
	// 잘못된 값 입력 받을 시
	else
		return GAME_LEVEL_ERROR_SET;
}