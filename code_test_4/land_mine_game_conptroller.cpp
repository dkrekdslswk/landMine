/****************************************************************
* ��    �� : ����ã�� ��Ʈ�ѷ�
* �ۼ����� : 2016. 08. 18
* �� �� �� : �ֺ���
* ��    �� : ������� �Է°��� �޾Ƽ� ����ã�� ������ ����
******************************************************************/



#include <stdio.h>
#include <conio.h>
#include "fs_conio_order.h"

// Ű���� ����Ű ��
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

// �޴�â ���� ����
int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x);

int land_mine_point_z_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting);
int land_mine_point_x_order(int x, int y, int* mine, int* not_fine, int max_x, unsigned char* game_setting);
int land_mine_point_c_order(int x, int y, int* mine, int* not_fine, int max_x, int max_y, unsigned char* game_setting);

void Fs_Goto_X_Y_Print_Bbefore_After(int* y_before, int* x_before, int y_after, int x_after);

// ���̵� â ǥ��
void side_print(int x); 
void mine_count_screen(int max_x, int mine);

int Land_Mine_Game_Controller(int high, int wdith, int mine, unsigned char* game_setting)
{
	// ����_����
	int x_before	= 0;
	// ����_����
	int y_before	= 0;
	// ����_����
	int x_after		= 0;
	// ����_����
	int y_after		= 0;

	// ���� ���� �� ����
	int				mine_count			= mine;
	// ��Ȯ�� ĭ �� ����
	int				not_find_count		= high * wdith;

	// ��ɰ� ����
	int order			= 0;
	
	// ������ ��鰪 ����
	HANDLE time_thread = 0;



	// ���̵� �޴�â ���
	side_print(wdith);

	// ���� �� ǥ��
	mine_count_screen(wdith, mine_count);

	Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);
	fs_time_count::set_up_x_y(wdith _PRINT_X + 21, 1);

	// �ð�ǥ�� ������
	time_thread = CreateThread(NULL, 0, fs_time_count::Thread_unsigned_short_timer, 0, 0, NULL);
	
	do {

		order = Fs_Goto_X_Y_Action(_getch(), &y_after, &x_after, high, wdith);

		// Ÿ�� �������� �Ͻ�����
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
			else if (printf("�絵�� �Ͻðڽ��ϱ�(z)?"), _getch() == 'z') {
				order = _ONE_TURN_KILL;
			}
			break;
		}
		if (mine_count == not_find_count){
			gotoxy_map(0, high _PRINT_Y + 1);
			order = _MINE_CLEAR + fs_time_count::time_unsigned_short();
			break;
		}

		// ���� �� ǥ��
		mine_count_screen(wdith, mine_count);

		// Ÿ�� �������� ������
		ResumeThread(time_thread);

	} while (order != _KEY_ESC);

	// ������ ����
	TerminateThread(time_thread, 1);
	return order;
}

int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x)
{
	int save_return = 0;

	switch (order) {
		// ����Ű �Է¹��� �� ������� -32 �� ����
	case _KEY_DIRECTION:
		break;
		// ����Ű upŰ
	case _KEY_UP:
		if (*y > 0) {
			*y = *y - 1;
		}
		break;
		// ����Ű downŰ
	case _KEY_DOWN:
		if (*y < (max_y - 1)) {
			*y = *y + 1;
		}
		break;
		// ����Ű leftŰ
	case _KEY_LEFT:
		if (*x > 0) {
			*x = *x - 1;
		}
		break;
		// ����Ű riteŰ
	case _KEY_RITE:
		if (*x < (max_x - 1)) {
			*x = *x + 1;
		}
		break;
		// ���� ���� ���
	case _KEY_ESC:
		save_return = _KEY_ESC;
		break;
		// ����
	case 'z':
	case 'Z':
		save_return = _KEY_Z;
		break;
		// �ʵ� Ȯ��
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

	// ������ǥ 1 + 2 * high
	// ������ǥ 2 + 4 * width
	// ȭ���� ���� ���� �ִ� ������
	// ���� = 49, ���� = 122

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
	printf("��");
	gotoxy_map(x, y + 1);
	printf("��");
	gotoxy_map(x - 2, y);
	printf("��");
	gotoxy_map(x + 2, y);
	printf("��");
	
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
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 2:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfa);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 3:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfc);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 4:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf1);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 5:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf4);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 6:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf3);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 7:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf2);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 8:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf5);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) + 0x60;
			break;
		case 9:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
			for (int i = 0; i < max_x * max_y; i++) {
				if ((*(game_setting + i) & 0x1f) == 0x09) {
					gotoxy_map(((i % max_x) _PRINT_X), ((i / max_x) _PRINT_Y));
					printf("��");
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
			printf("��");
			*mine = *mine - 1;
			*not_fine = *not_fine - 1;
			*(game_setting + y * max_x + x) = *(game_setting + y * max_x + x) | 0x20;
			break;
		case 0x02:
		case 0x01:
			gotoxy_map(x_p, y_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf8);
			printf("��");
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

		// ��ź�� ������ ��� _MINE_BURST�� �ݳ�
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
	// unssigned short ������ �ؼ� 65535 �� �Ǹ� over�� ����
	// 21, 22, 23, 24, 25
	// %5d�� ����Ʈ
	gotoxy_map(x _PRINT_X + 3, 1);
	printf("���� ���� �ð�  : 00000");
	// unssigned short ������ �ؼ� ���� ĭ���� ���� ���� ���� �� �� �Ǹ� �¸�
	// 23, 24, 25
	// %3d�� ����Ʈ
	gotoxy_map(x _PRINT_X + 3, 3);
	printf("���� ������ ��  :   000");

	// Ű ����
	gotoxy_map(x _PRINT_X + 3, 5);
	printf("�̵�  : �����¿� ����Ű");
	gotoxy_map(x _PRINT_X + 3, 7);
	printf("Z     : ��  ��");
	gotoxy_map(x _PRINT_X + 3, 8);
	printf("X     : ǥ  ��(��=����)");
	gotoxy_map(x _PRINT_X + 3, 9);
	printf("C     : ���� Ȯ��");

	// ����Ű ����
	gotoxy_map(x _PRINT_X + 3, 11);
	printf("ESC   :    ����    ����");

}

// ���̵� â�� �ϳ� �������ϳ�....
// ��ǥ�� �����ұ�.

// ����Ű ���� �ʿ���

// ���� ����� ���� ǥ���ϴ� �Լ�

// ��ü ���ڼ��� Ȯ������ ���� ����� �� Ȯ�� �� Ŭ���� �ݳ� �Լ�

// ���������� �ð��� Ȯ���ϴ� �Լ�
// �̰� ȭ�鿡 ����� �ϴϱ�..... ��ǥ�� ������ �ʿ��ϳ�

// sonnabakayaro