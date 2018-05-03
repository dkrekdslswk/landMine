/*****************************************
�� �� �� : �ֺ���
�ۼ����� : 2016. 08. 11
��    �� : ����ã�� �Լ� �ۼ��� �׽�Ʈ
*******************************************/


#include <stdio.h>
#include <windows.h>
#include <conio.h>


// Ű���� ����Ű ��
#define _KEY_DIRECTION	-32
#define _KEY_UP			72
#define _KEY_DOWN		80
#define _KEY_LEFT		75
#define _KEY_RITE		77

#define _KEY_ESC		27

#define _KEY_Z			'z'
#define _KEY_X			'x'

// �޴�â ���� ����
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
	// ����_����
	int x_before		= 0;
	// ����_����
	int y_before		= 0;
	// ����_����
	int x_after			= 0;
	// ����_����
	int y_after			= 0;

	int order			= 0;

	Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);

	do {
		order = Fs_Goto_X_Y_Action(_getch(), &y_after, &x_after, 24, 30);

		Fs_Goto_X_Y_Print_Bbefore_After(&y_before, &x_before, y_after, x_after);


		if (order == _KEY_Z) {
			gotoxy_map((x_before * 4 + 2), (y_before * 2 + 1));
			printf("��");
		}
		if (order == _KEY_X) {
			gotoxy_map((x_before * 4 + 2), (y_before * 2 + 1));
			printf("��");
		}

	} while (order != _KEY_ESC);

	return 0;
}

int Fs_Goto_X_Y_Action(char order, int *y, int *x, int max_y, int max_x)
{
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
		return _KEY_ESC;
		break;
		// ����
	case 'z':
	case 'Z':
		return _KEY_Z;
		break;
		// �ʵ� Ȯ��
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

	// ������ǥ 1 + 2 * high
	// ������ǥ 2 + 4 * width
	// ȭ���� ���� ���� �ִ� ������
	// ���� = 49, ���� = 122

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
	printf("��");
	gotoxy_map(x, y + 1);
	printf("��");
	gotoxy_map(x - 2, y);
	printf("��");
	gotoxy_map(x + 2, y);
	printf("��");

	*x_before = x_after;
	*y_before = y_after;
}