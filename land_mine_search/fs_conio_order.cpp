
#include<windows.h>
#include<time.h>

#include<stdio.h>


void resz(short w, short h) { // 열, 행 
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD temp = { 999, 999 };
	COORD siz = { w,h };
	SMALL_RECT sr;
	// 좌측 상단 
	sr.Left = 0;
	sr.Top = 0;
	// 우측 하단 (1을 빼주는 이유는 우측 하단의 위치이기 때문) 
	sr.Right = w - 1;
	sr.Bottom = h - 1;
	SetConsoleScreenBufferSize(hout, temp); // 999x999 (최대한) 버퍼 크기를 잡아 준 후 
	SetConsoleWindowInfo(hout, TRUE, &sr); // 창의 크기를 정한다. 
	SetConsoleScreenBufferSize(hout, siz);
}

void gotoxy_map(int x, int y)
{
	COORD map;
	map.X = x;
	map.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map);
}

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
	clock_t start = 0, finish = 0; // 시간표현 전역변수 지정

	// 스레드 내부에서 프린트할 좌표 설정
	static int x_point = 0;
	static int y_point = 0;

	// 시간 값 저장
	unsigned long duration = 0;

	void set_up_x_y(int x, int y) {
		x_point = x;
		y_point = y;
	}

	unsigned short time_unsigned_short() {
		return (unsigned short)duration;
	}


	DWORD WINAPI Thread_unsigned_short_timer(LPVOID lpParameter)//스레드 타이머
	{
		duration = 0;

		unsigned short count_time = 0;

		start = clock();

		while (1)
		{
			if (count_time < duration) {
				count_time = (unsigned short)duration;
				time_unsigned_short_screen(x_point, y_point, count_time);
			}

			if (duration >= 65535) // 65535초가 경과되면 스레드는 리턴되어 cpu 사용을 중지하게 된다.
			{
				time_unsigned_short_screen(x_point, y_point, count_time);
				break;
			}

			finish = clock() - start;
			duration = (unsigned long)(finish / CLOCKS_PER_SEC);
			Sleep(50);
		}
		return 0;
	}
}
/*
void textcolor(int color_number) {
	SetConsole
}
*/