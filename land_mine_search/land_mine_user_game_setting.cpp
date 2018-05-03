/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11 ~ 2016. 08. 16
* 작동원리 :	base 적인 설정으로 game_setting값을 초기화
**********************************************/

/* 인클루드 선언 부 */
#include"fs_menu_screen_print.h"
#include"fs_unsigned_integer.h"
#include"land_mine_main_menu_constant.h"
#include"land_mine_game_setting_save.h"
#include<stdio.h>
#include<windows.h>

// 유저 난이도 설정전 이지난이도로 설정
// 이지 난이도 셋팅 맵 크기 (9 * 9), 지뢰수 10
#define GAME_LEVEL_EASY_SET		0x00A249ul

/* 사용자 설정 게임의 메뉴의 수
*  fs_menu() 함수를 사용할때 사용*/
#define USER_GAME_SETTING_MENU		5

/* fs_menu()로 반환받은 값에 명령상수 의미 부여 */
// 높이 입력받기
#define USER_GAME_SETTING_HEIGHT		1
// 가로길이 입력받기
#define USER_GAME_SETTING_WIDTH			2
// 지뢰수 입력받기
#define USER_GAME_SETTING_MINE			3
// 입력 종료 및 게임 시작
#define USER_GAME_SETTING_END			4
// 입력 취소 및 이전메뉴 호출
#define USER_GAME_SETTING_OUT			0

// 높이 값의 현재상태 표시를 할 위치
#define USER_GAME_SETTING_MENU_HEIGHT		0
#define USER_GAME_SETTING_MENU_HEIGHT_10	17	
#define USER_GAME_SETTING_MENU_HEIGHT_01	18

// 가로길이 값의 현재상태 표시를 할 위치
#define USER_GAME_SETTING_MENU_WIDTH		1
#define USER_GAME_SETTING_MENU_WIDTH_10		17	
#define USER_GAME_SETTING_MENU_WIDTH_01		18

// 지뢰 수 값의 현재상태 표시를 할 위치
#define USER_GAME_SETTING_MENU_MINE			2
#define USER_GAME_SETTING_MENU_MINE_100		16	
#define USER_GAME_SETTING_MENU_MINE_010		17
#define USER_GAME_SETTING_MENU_MINE_001		18
// 현재 상태의 최대 지뢰수를 표시할 위치
#define USER_GAME_SETTING_MENU_MAX_MINE_100		10	
#define USER_GAME_SETTING_MENU_MAX_MINE_010		11
#define USER_GAME_SETTING_MENU_MAX_MINE_001		12

/* fs_Output_Unsigned_Integer() 함수에 입력될 최저값과 최고값*/
// 높이의 최저 최고값
#define LAND_MINE_BEILD_HIGH_MAX_SAVE			24
#define LAND_MINE_BEILD_HIGH_MIN_SAVE			9
// 가로길이의 최저 최고값
#define LAND_MINE_BEILD_WIDTH_MAX_SAVE			30
#define LAND_MINE_BEILD_WIDTH_MIN_SAVE			9
// 지뢰수의 최저값 (최대 지뢰수는 넓이에 때라 변동되기에 저장소에서 현재상태의 최대넓이 값을 불러서 사용)
#define LAND_MINE_BEILD_MINE_MIN_SAVE			10

int User_Game_Setting() {

	// 유저 설정 메뉴
	char user_game_setting_menu_choice[USER_GAME_SETTING_MENU][22] = {	{ "높  이(9 ~ 24):  09\n" },
																		{ "넓  이(9 ~ 30):  09\n" },
																		{ "지뢰수(10~067): 010\n" },
																		{ "설   정    완    료\n" },
																		{ "설   정    취    소\n" } };

	// 원래의 기본 설정값을 저장
	unsigned long	user_game_setting_return	= land_mine_game_setting_save::game_setting();
	// 저장소의 값을 기본 설정으로 초기화
	land_mine_game_setting_save::game_setting_input(GAME_LEVEL_EASY_SET);

	// 유저 설정 메뉴 명령값
	int				user_game_setting_order		= 0;

	// 유저 설정
	do {
		// 지뢰수에 대한 값 입력 범위를 현재 최대 넓이에 따라 변경
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_100] = land_mine_game_setting_save::max_mine() / 100 + '0';
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_010] = (land_mine_game_setting_save::max_mine() % 100) / 10 + '0';
		user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MAX_MINE_001] = land_mine_game_setting_save::max_mine() % 10 + '0';

		// 메뉴 호출
		user_game_setting_order = fs_menu(user_game_setting_menu_choice, USER_GAME_SETTING_MENU);

		// 명령값 실행
		switch (user_game_setting_order) {
			// 높이값을 변경하고 메뉴에 표시할 내용 수정
		case USER_GAME_SETTING_HEIGHT:
			land_mine_game_setting_save::high_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_HIGH_MIN_SAVE, LAND_MINE_BEILD_HIGH_MAX_SAVE, land_mine_game_setting_save::high()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_HEIGHT][USER_GAME_SETTING_MENU_HEIGHT_10] = land_mine_game_setting_save::high() / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_HEIGHT][USER_GAME_SETTING_MENU_HEIGHT_01] = land_mine_game_setting_save::high() % 10 + '0';
			break;
			// 가로길이값을 변경하고 메뉴에 표시할 내용 수정
		case USER_GAME_SETTING_WIDTH:
			land_mine_game_setting_save::width_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_WIDTH_MIN_SAVE, LAND_MINE_BEILD_WIDTH_MAX_SAVE, land_mine_game_setting_save::width()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_WIDTH][USER_GAME_SETTING_MENU_WIDTH_10] = land_mine_game_setting_save::width() / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_WIDTH][USER_GAME_SETTING_MENU_WIDTH_01] = land_mine_game_setting_save::width() % 10 + '0';
			break;
			// 지뢰수를 수정하고 메뉴에 표시할 내용 수정
		case USER_GAME_SETTING_MINE:
			land_mine_game_setting_save::mine_input(fs_Output_Unsigned_Integer(LAND_MINE_BEILD_MINE_MIN_SAVE, land_mine_game_setting_save::max_mine(), land_mine_game_setting_save::mine()));
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_100] = land_mine_game_setting_save::mine() / 100 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_010] = (land_mine_game_setting_save::mine() % 100) / 10 + '0';
			user_game_setting_menu_choice[USER_GAME_SETTING_MENU_MINE][USER_GAME_SETTING_MENU_MINE_001] = land_mine_game_setting_save::mine() % 10 + '0';
			break;
			// 밑의 값이 아닌 값은 실행하지 않음.
			//(USER_GAME_SETTING_HEIGHT, USER_GAME_SETTING_WIDTH, USER_GAME_SETTING_MINE)
		default:
			break;
		}
		
		// 화면 초기화
		system("cls");

		// 입력을 종료하거나 취소할시 반복문 탈출
	} while ((user_game_setting_order != USER_GAME_SETTING_END) && (user_game_setting_order != USER_GAME_SETTING_OUT));

	// 입력취소시 최초의 값으로 초기화하고 메인메뉴를 호출하는 명령을 반납
	if (user_game_setting_order == USER_GAME_SETTING_OUT) {
		land_mine_game_setting_save::game_setting_input(user_game_setting_return);
		return _MAIN_MENU_CALL;
	}
	// 입력취소가 아닌(입력 종료의) 명령이면 현재 입력값으로 게임을 실행
	else
		return _MAIN_GAME_START_CALL;
}