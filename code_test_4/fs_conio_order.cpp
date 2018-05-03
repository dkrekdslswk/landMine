
#include<windows.h>
#include<time.h>

#include<stdio.h>

// �ܼ�â�� ũ�⸦ ����
void resz(short w, short h) { // ��, �� 
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD temp = { 999, 999 };
	COORD siz = { w,h };
	SMALL_RECT sr;
	// ���� ��� 
	sr.Left = 0;
	sr.Top = 0;
	// ���� �ϴ� (1�� ���ִ� ������ ���� �ϴ��� ��ġ�̱� ����) 
	sr.Right = w - 1;
	sr.Bottom = h - 1;
	SetConsoleScreenBufferSize(hout, temp); // 999x999 (�ִ���) ���� ũ�⸦ ��� �� �� 
	SetConsoleWindowInfo(hout, TRUE, &sr); // â�� ũ�⸦ ���Ѵ�. 
	SetConsoleScreenBufferSize(hout, siz);
}

// ����Ʈ ������ġ�� �ش���ġ�� �̵�
void gotoxy_map(int x, int y)
{
	COORD map;
	map.X = x;
	map.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map);
}

// �ð��� ���� ��ġ���� ����ϱ�
void time_unsigned_short_screen(int x, int y, unsigned short time) {
	gotoxy_map(x, y);
	if (time == 65535) {
		printf("tover");
	}
	else {
		printf("%5d", time);
	}
}

namespace fs_time_count {
	clock_t start = 0, finish = 0; // �ð�ǥ�� �������� ����

	// ������ ���ο��� ����Ʈ�� ��ǥ ����
	static int x_point = 0;
	static int y_point = 0;

	// �ð� �� ����
	unsigned long duration = 0;

	// �ܺο��� ����� ��ġ ����
	void set_up_x_y(int x, int y) {
		x_point = x;
		y_point = y;
	}

	// �ܺο��� �ð��ݳ��� �ݳ�
	unsigned short time_unsigned_short() {
		return (unsigned short)duration;
	}

	// �ð��� ���ϴ� ��ġ�� ����ϴ� ������
	// 0~65535��
	DWORD WINAPI Thread_unsigned_short_timer(LPVOID lpParameter)//������ Ÿ�̸�
	{
		duration = 0;


		start = clock();

		while (1)
		{
			time_unsigned_short_screen(x_point, y_point, (unsigned short)duration);
			

			if (duration >= 65535) // 65535�ʰ� ����Ǹ� ������� ���ϵǾ� cpu ����� �����ϰ� �ȴ�.
			{
				time_unsigned_short_screen(x_point, y_point, 65535);
				break;
			}

			finish = clock() - start;
			duration = (unsigned long)(finish / CLOCKS_PER_SEC);
			Sleep(450);
		}
		return 0;
	}
}
/*
void textcolor(int color_number) {
	SetConsole
}
*/