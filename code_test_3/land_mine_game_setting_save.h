#pragma once

/***********************************************
* 제 작 자 :	최병찬
* 제작일자 :	2016. 08. 11 ~ 2016. 08. 16
* 사 용 법 :	지뢰찻기 게임 설정을 unsigned long형 하나에 전부 저장 할 수 있는 아주 위대한 병신 같은 함수 그룹				
************************************************/

namespace land_mine_game_setting_save {

	// 전체 세팅 값 출력
	unsigned long	setting(void);
	// 게임 세팅 값 출력
	unsigned long	game_setting(void);
	// 옵션 세팅 값 출력
	unsigned long	option_setting(void);
	// 높이 세팅 값 출력
	int				high(void);
	// 길이 세팅 값 출력
	int				width(void);
	// 지뢰 수 세팅 값 출력
	int				mine(void);
	// 배경 세팅 값 출력
	int				ground(void);
	// 확인 세팅 값 출력
	bool			check(void);
	// 현재 상태의 최대 지뢰수의 값 출력
	int				max_mine(void);

	// 전체 세팅값을 한번에 저장하는 함수 (각각 설정 요소가 범위를 벗어나면 자동 수정 입력함.)
	void			setting_input(unsigned long input);
	// 게임 세팅값을 한번에 저장하는 함수 (각각 설정 요소가 범위를 벗어나면 자동 수정 입력함.)
	void			game_setting_input(unsigned long input);
	// 옵션 세팅값을 한번에 저장하는 함수 (각각 설정 요소가 범위를 벗어나면 자동 수정 입력함.)
	void			option_setting_input(unsigned long input);
	// 높이 세팅값을 저장하는 함수 (9~24)
	void			high_input(int input);
	// 길이 세팅값을 저장하는 함수 (9~30)
	void			width_input(int input);
	// 지뢰수 세팅값을 저장하는 함수 (10 ~ [넓이 * 0.94 - 9(소숫점 아래 버림)(최대넓이에서 최대값은 667)])
	void			mine_input(int input);
	// 배경 세팅값을 저장하는 함수 (1~15)
	void			ground_input(int input);
	// 확인 세팅값을 저장하는 함수 (true or false)
	void			check_input(bool input);
}