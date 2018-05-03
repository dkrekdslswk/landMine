/*****************************************************
* 제    목 : 설정된 맵정보를 받아서 화면에 출력
* 작성일자 : 2016. 08. 18
* 작 성 자 : 최병찬
* 목    적 :
				입력된 값으로 지뢰찾기에 대한 값을 넣고
				화면을 기본 셋팅으로 출력한다음에
				gotoxy를 이용하여 화면을 프레임을 좋게 하기
				+ 동시실행창을 이용해서 플래이타임을 
				  실시간으로 표현하는 것도 시도
				  + 기왕이면 배경음 실행창도 있으면 좋을듯.?
*******************************************************/

#include<stdio.h>
#include "fs_conio_order.h"
#include<windows.h>

#define NOMAL_DESIGN	0x1

// 기본적인 스타일의 맵 표시
void nomal_map_design(int map_data_high, int map_data_width);

// 몇초만에 승리했는 지 리턴시킬까?
// 저장받아서 기록하는건 어떨까?
// .txt 파일 같은거로?
int Land_Mine_Game_Screen(int map_data_high, int map_data_width, int map_design) {

	system("cls");
	resz((map_data_width * 4 + 2 + 1 + 30), (map_data_high * 2 + 3));
	switch (map_design)
	{
	case NOMAL_DESIGN:
		nomal_map_design(map_data_high, map_data_width);
		break;
	default:
		break;
		return 0;
	}
	return 0;
}

// 세로좌표 1 + 2 * high
// 가로좌표 2 + 4 * width
// 화면의 가로 세로 최대 사이즈
// 세로 = , 가로 = 
void nomal_map_design(int map_data_high, int map_data_width) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf8);
	printf("┏");
	for (int width = 0; width <= map_data_width - 2; width++) {
		printf("  ┳");
	}
	printf("  ┓\n");

	for (int high = 1; high <= 2 * map_data_high - 1 ; high++) {
		if (high % 2) {
			printf("  ");
			for (int width = 0; width <= map_data_width - 1 ; width++) {
				printf("■  ");
			}
		}
		else {
			printf("┣");
			for (int width = 1; width <= map_data_width - 1; width++) {
				printf("  ╋");
			}
			printf("  ┫");
		}
		printf("\n");
	}

	printf("┗");
	for (int width = 1; width <= map_data_width - 1; width++) {
		printf("  ┻");
	}
	printf("  ┛");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
}