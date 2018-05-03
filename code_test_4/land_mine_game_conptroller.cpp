/****************************************************************
* 제    목 : 지뢰찾기 컨트롤러
* 작성일자 : 2016. 08. 18
* 작 성 자 : 최병찬
* 목    적 : 사용자의 입력값을 받아서 지뢰찾기 게임을 실행
******************************************************************/



#include <stdio.h>
#include <conio.h>
#include "fs_conio_order.h"

// 키보드 방향키 값
#define _KEY_DIRECTION	-32
#define _KEY_UP			72
#define _KEY_DOWN		80
#define _KEY_LEFT		75
#define _KEY_RITE		77

#define _KEY_ESC		27

#define _KEY_Z			'z'
#define _KEY_X			'x'
#define _KEY_C			'c'

#define _STATE_BIT		5
#define _MINE_BURST		9
#define _MINE_CLEAR		0xff0000
#define _ONE_TURN_KILL	-1

// 메뉴창 오더 실행
int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x);

int land_mine_point_z_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting);
int land_mine_point_x_order(int x, int y, int* mine, int* not_fine, int max_x, unsigned char* game_setting);
int land_mine_point_c_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting);

void Fs_Goto_X_Y_Print_Bbefore_After(int* y_before, int* x_before, int y_after, int x_after);

// 사이드 창 표시
void side_print(int x); 
void mine_count_screen(int max_x, int mine);

int Land_Mine_Game_Controller(int high, int wdith, int mine, unsigned char* game_setting)
{
	// 가로_이전
	int x_before	= 0;
	// 세로_이전
	int y_before	= 0;
	// 가로_이후
	int x_after		= 0;
	// 세로_이후
	int y_after		= 0;

	// 남은 지뢰 수 저장
	int				mine_count			= mine;
	// 미확인 칸 수 저장
	int				not_find_count		= high * wdith;

	// 명령값 저장
	int order			= 0;
	
	// 스레드 헨들값 저장
	HANDLE time_thread = 0;



	// 사이드 메뉴창 출력
	side_print(wdith);

	// 지뢰 수 표시
	mine_count_screen(wdith, mine_count);

	Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);
	fs_time_count::set_up_x_y(wdith _PRINT_X + 21, 1);

	// 시간표시 스레드
	time_thread = CreateThread(NULL, 0, fs_time_count::Thread_unsigned_short_timer, 0, 0, NULL);
	
	do {

		order = Fs_Goto_X_Y_Action(_getch(), &y_after, &x_after, high, wdith);

		// 타임 스레드의 일시정지
		SuspendThread(time_thread);

		Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);


		if (order == _KEY_Z) {
			order = land_mine_point_z_order(x_before, y_before, &mine_count, &not_find_count, wdith, high, game_setting);
		}
		if (order == _KEY_X) {
			order = land_mine_point_x_order(x_before, y_before, &mine_count, &not_find_count, wdith, game_setting);
		}
		if (order == _KEY_C) {
			order = land_mine_point_c_order(x_before, y_before, &mine_count, &not_find_count, wdith, high, game_setting);
		}
		if (order == _MINE_BURST) {
			gotoxy_map(0, high _PRINT_Y + 1);
			if (not_find_count >= (int)(high * wdith * 0.9375)) {
				order = _ONE_TURN_KILL;
			}
			else if (printf("재도전 하시겠습니까(z)?"), _getch() == 'z') {
				order = _ONE_TURN_KILL;
			}
			break;
		}
		if (mine_count == not_find_count){
			gotoxy_map(0, high _PRINT_Y + 1);
			order = _MINE_CLEAR + fs_time_count::time_unsigned_short();
			break;
		}

		// 지뢰 수 표시
		mine_count_screen(wdith, mine_count);

		// 타임 스레드의 제시작
		ResumeThread(time_thread);

	} while (order != _KEY_ESC);

	// 스레드 종료
	TerminateThread(time_thread, 1);
	return order;
}

int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x)
{
	int save_return = 0;

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
		save_return = _KEY_ESC;
		break;
		// 선택
	case 'z':
	case 'Z':
		save_return = _KEY_Z;
		break;
		// 필드 확인
	case 'x':
	case 'X':
		save_return = _KEY_X;
		break;
	case 'c':
	case 'C':
		save_return = _KEY_C;
		break;
	default:
		break;
	}
	return save_return;
}


void Fs_Goto_X_Y_Print_Bbefore_After(int *y_before, int *x_before, int y_after, int x_after) {

	// 세로좌표 1 + 2 * high
	// 가로좌표 2 + 4 * width
	// 화면의 가로 세로 최대 사이즈
	// 세로 = 49, 가로 = 122

	int x = *x_before _PRINT_X;
	int y = *y_before _PRINT_Y;

	gotoxy_map(x, y - 1);
	printf("  ");
	gotoxy_map(x, y + 1);
	printf("  ");
	gotoxy_map(x - 2, y);
	printf("  ");
	gotoxy_map(x + 2, y);
	printf("  ");

	x = x_after _PRINT_X;
	y = y_after _PRINT_Y;


	gotoxy_map(x, y - 1);
	printf("┳");
	gotoxy_map(x, y + 1);
	printf("┻");
	gotoxy_map(x - 2, y);
	printf("┣");
	gotoxy_map(x + 2, y);
	printf("┫");
	
	gotoxy_map(x, y);
	*x_before = x_after;
	*y_before = y_after;
}

int land_mine_point_z_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting) {

	int save_return = 0;

	if (!((*(game_setting + y * max_x + x) >> _STATE_BIT) > 0x00)) {
		*not_fine = *not_fine - 1;

		int x_p = x _PRINT_X;
		int y_p = y _PRINT_Y;
		//x * 4 + 2;
		//y * 2 + 1;

		switch ((*(game_setting + y * max_x + x)) & 0x1f)
		{
		case 0:
			gotoxy_map(x_p, y_p);
			printf("  ");
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			if (y != 0) {
				if (x != 0)
					land_mine_point_z_order(x - 1, y - 1, mine, not_fine, max_x, max_y, game_setting);

				land_mine_point_z_order(x, y - 1, mine, not_fine, max_x, max_y, game_setting);
				if (x != max_x - 1)
					land_mine_point_z_order(x + 1, y - 1, mine, not_fine, max_x, max_y, game_setting);
			}

			if (x != 0)
				land_mine_point_z_order(x - 1, y, mine, not_fine, max_x, max_y, game_setting);
			if (x != max_x - 1)
				land_mine_point_z_order(x + 1, y, mine, not_fine, max_x, max_y, game_setting);

			if (y != max_y - 1) {
				if (x != 0)
					land_mine_point_z_order(x - 1, y + 1, mine, not_fine, max_x, max_y, game_setting);

				land_mine_point_z_order(x, y + 1, mine, not_fine, max_x, max_y, game_setting);
				if (x != max_x - 1)
					land_mine_point_z_order(x + 1, y + 1, mine, not_fine, max_x, max_y, game_setting);
			}
			break;

		case 1:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf9);
			printf("①");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 2:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfa);
			printf("②");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 3:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfc);
			printf("③");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 4:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf1);
			printf("④");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 5:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf4);
			printf("⑤");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 6:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf3);
			printf("⑥");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 7:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf2);
			printf("⑦");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 8:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf5);
			printf("⑧");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 9:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			printf("⑨");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			for (int i = 0; i < max_x * max_y; i++) {
				if ((*(game_setting + i) & 0x1f) == 0x09) {
					gotoxy_map(((i % max_x) _PRINT_X), ((i / max_x) _PRINT_Y));
					printf("⑨");
				}
			}
			save_return = _MINE_BURST;
			break;

		default:
			break;
		}
	}

	return save_return;
}

int land_mine_point_x_order(int x, int y, int* mine, int* not_fine, int max_x, unsigned char* game_setting) {
	
	int save_return = 0;

	if (!((*(game_setting + y * max_x + x) >> _STATE_BIT) == 0x3)) {

		int x_p = x _PRINT_X;
		int y_p = y _PRINT_Y;
		//x * 4 + 2;
		//y * 2 + 1;

		switch (*(game_setting + y * max_x + x) >> _STATE_BIT)
		{
		case 0x00:
			gotoxy_map(x_p, y_p);
			printf("★");
			*mine = *mine - 1;
			*not_fine = *not_fine - 1;
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) | 0x20;
			break;
		case 0x02:
		case 0x01:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf8);
			printf("■");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*mine = *mine + 1;
			*not_fine = *not_fine + 1;
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) & 0x1f;
			break;
		default:
			break;
		}
	}
	return save_return;
}

int land_mine_point_c_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting) {

	int save_return = 0;

	if ((*(game_setting + y * max_x + x) & 0x60) == 0x60) {

		// 폭탄이 터졌을 경우 _MINE_BURST를 반납
		int return_order = 0;


		int save_now_point = *(game_setting + y * max_x + x) & 0x0f;
		int check_point = 0;
		//
		if (y != 0) {
			if (x != 0)
				if ((*(game_setting + (y - 1) * max_x + x - 1) & 0x60) == 0x20)
					check_point++;

			if ((*(game_setting + (y - 1) * max_x + x) & 0x60) == 0x20)
				check_point++;
			if (x != max_x - 1)
				if ((*(game_setting + (y - 1) * max_x + x + 1) & 0x60) == 0x20)
					check_point++;
		}

		if (x != 0)
			if ((*(game_setting + y * max_x + x - 1) & 0x60) == 0x20)
				check_point++;
		if (x != max_x - 1)
			if ((*(game_setting + y * max_x + x + 1) & 0x60) == 0x20)
				check_point++;

		if (y != max_y - 1) {
			if (x != 0)
				if ((*(game_setting + (y + 1) * max_x + x - 1) & 0x60) == 0x20)
					check_point++;

			if ((*(game_setting + (y + 1) * max_x + x) & 0x60) == 0x20)
				check_point++;
			if (x != max_x - 1)
				if ((*(game_setting + (y + 1) * max_x + x + 1) & 0x60) == 0x20)
					check_point++;
		}

		//
		if (save_now_point == check_point) {
			if (y != 0) {
				if (x != 0)
					return_order += land_mine_point_z_order(x - 1, y - 1, mine, not_fine, max_x, max_y, game_setting);

				return_order += land_mine_point_z_order(x, y - 1, mine, not_fine, max_x, max_y, game_setting);
				if (x != max_x - 1)
					return_order += land_mine_point_z_order(x + 1, y - 1, mine, not_fine, max_x, max_y, game_setting);
			}

			if (x != 0)
				return_order += land_mine_point_z_order(x - 1, y, mine, not_fine, max_x, max_y, game_setting);
			if (x != max_x - 1)
				return_order += land_mine_point_z_order(x + 1, y, mine, not_fine, max_x, max_y, game_setting);

			if (y != max_y - 1) {
				if (x != 0)
					return_order += land_mine_point_z_order(x - 1, y + 1, mine, not_fine, max_x, max_y, game_setting);

				return_order += land_mine_point_z_order(x, y + 1, mine, not_fine, max_x, max_y, game_setting);
				if (x != max_x - 1)
					return_order += land_mine_point_z_order(x + 1, y + 1, mine, not_fine, max_x, max_y, game_setting);
			}
			if (return_order >= 9)
				save_return = _MINE_BURST;
		}
	}

	return save_return;
}

void mine_count_screen(int max_x, int mine) {
	gotoxy_map(max_x _PRINT_X + 23, 3);
	printf("%3d", mine);
}

void side_print(int x) {
	// unssigned short 형으로 해서 65535 가 되면 over로 변경
	// 21, 22, 23, 24, 25
	// %5d로 프린트
	gotoxy_map(x _PRINT_X + 3, 1);
	printf("현재 진행 시간  : 00000");
	// unssigned short 형으로 해서 남은 칸수가 현재 남은 지뢰 수 가 되면 승리
	// 23, 24, 25
	// %3d로 프린트
	gotoxy_map(x _PRINT_X + 3, 3);
	printf("남은 지뢰의 수  :   000");

	// 키 설명
	gotoxy_map(x _PRINT_X + 3, 5);
	printf("이동  : 상하좌우 방향키");
	gotoxy_map(x _PRINT_X + 3, 7);
	printf("Z     : 선  택");
	gotoxy_map(x _PRINT_X + 3, 8);
	printf("X     : 표  시(★=지뢰)");
	gotoxy_map(x _PRINT_X + 3, 9);
	printf("C     : 주위 확인");

	// 종료키 설명
	gotoxy_map(x _PRINT_X + 3, 11);
	printf("ESC   :    게임    종료");

}

// 사이드 창을 하나 만들어야하네....
// 좌표만 저장할까.

// 조작키 설명도 필요함

// 남은 깃발의 수를 표기하는 함수

// 전체 지뢰수와 확인하지 않은 블록을 비교 확인 후 클리어 반납 함수

// 지속적으로 시간을 확인하는 함수
// 이건 화면에 띄워야 하니까..... 좌표값 설정도 필요하네

// sonnabakayaro