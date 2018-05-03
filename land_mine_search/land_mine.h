#pragma once

/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11
* 작동원리 :	1. 기본 설정 게임시작 2. 사용자 설정 게임 시작, 3. 게임 옵션 설정, 4. 종료(0) 반환 
*********************************************/
int Main_Menu(void);

// 게임설정
// 기본설정
/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11 ~ 2016. 08. 16
* 작동원리 :	base 적인 설정으로 game_setting값을 초기화
**********************************************/
int Base_Game_Setting(void);


// 유저설정
/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11 ~ 2016. 08. 16
* 작동원리 :	base 적인 설정으로 game_setting값을 초기화
**********************************************/
int User_Game_Setting(void);

/************************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 16 ~ 2016. 08. 26
* 작동원리 :	land_mine_game_setting_save.cpp를 참조하여
				저장된 값으로 게임을 실행
**************************************************/
int Land_Mine_Map_Build(void);