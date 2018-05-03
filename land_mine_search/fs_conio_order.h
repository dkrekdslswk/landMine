#pragma once


void resz(short w, short h);

#define _PRINT_Y		*2+1
#define _PRINT_X		*4+2

void gotoxy_map(int x, int y);


#include<process.h>// 쓰레드의 헤더
#include<windows.h>
namespace fs_time_count {

	unsigned short time_unsigned_short();

	void set_up_x_y(int x, int y);

	DWORD WINAPI Thread_unsigned_short_timer(LPVOID lpParameter);//스레드 타이머
}