/*****************************************
제 작 자 : 최병찬
작성일자 : 2016. 08. 11
목    적 : 지뢰찾기 함수 작성전 테스트
*******************************************/


#include <stdio.h>
#include <windows.h>
#include <conio.h>


// 키보드 방향키 값
#define _KEY_DIRECTION	-32
#define _KEY_UP			72
#define _KEY_DOWN		80
#define _KEY_LEFT		75
#define _KEY_RITE		77

#define _KEY_ESC		27

#define _KEY_Z			'z'
#define _KEY_X			'x'

// 메뉴창 오더 실행
int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x);

void gotoxy_map(int x, int y)
{
	COORD map;
	map.X = x;
	map.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map);
}

void Fs_Goto_X_Y_Print_Bbefore_After(int* y_before, int* x_before, int y_after, int x_after);

int Land_Mine_Game_Controller()
{
	// 가로_이전
	int x_before		= 0;
	// 세로_이전
	int y_before		= 0;
	// 가로_이후
	int x_after			= 0;
	// 세로_이후
	int y_after			= 0;

	int order			= 0;

	Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);

	do {
		order = Fs_Goto_X_Y_Action(_getch(), &y_after, &x_after, 24, 30);

		Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);


		if (order == _KEY_Z) {
			gotoxy_map((x_before * 4 + 2), (y_before * 2 + 1));
			printf("ⓩ");
		}
		if (order == _KEY_X) {
			gotoxy_map((x_before * 4 + 2), (y_before * 2 + 1));
			printf("ⓧ");
		}

	} while (order != _KEY_ESC);

	return 0;
}

int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x)
{
	switch (order) {
		// 방향키 입력받을 시 쓸모없는 -32 값 제거
	case _KEY_DIRECTION:
		break;
		// 방향키 up키
	case _KEY_UP:
		if (*y > 0) {
			*y = *y - 1;
		}
		break;
		// 방향키 down키
	case _KEY_DOWN:
		if (*y < (max_y - 1)) {
			*y = *y + 1;
		}
		break;
		// 방향키 left키
	case _KEY_LEFT:
		if (*x > 0) {
			*x = *x - 1;
		}
		break;
		// 방향키 rite키
	case _KEY_RITE:
		if (*x < (max_x - 1)) {
			*x = *x + 1;
		}
		break;
		// 게임 실행 취소
	case _KEY_ESC:
		return _KEY_ESC;
		break;
		// 선택
	case 'z':
	case 'Z':
		return _KEY_Z;
		break;
		// 필드 확인
	case 'x':
	case 'X':
		return _KEY_X;
		break;
	default:
		break;
	}
	return 0;
}


void Fs_Goto_X_Y_Print_Bbefore_After(int *y_before, int *x_before, int y_after, int x_after) {

	// 세로좌표 1 + 2 * high
	// 가로좌표 2 + 4 * width
	// 화면의 가로 세로 최대 사이즈
	// 세로 = 49, 가로 = 122

	int x = *x_before * 4 + 2;
	int y = *y_before * 2 + 1;

	gotoxy_map(x, y - 1);
	printf("  ");
	gotoxy_map(x, y + 1);
	printf("  ");
	gotoxy_map(x - 2, y);
	printf("  ");
	gotoxy_map(x + 2, y);
	printf("  ");

	x = x_after * 4 + 2;
	y = y_after * 2 + 1;

	gotoxy_map(x, y - 1);
	printf("─");
	gotoxy_map(x, y + 1);
	printf("─");
	gotoxy_map(x - 2, y);
	printf("│");
	gotoxy_map(x + 2, y);
	printf("│");

	*x_before = x_after;
	*y_before = y_after;
}