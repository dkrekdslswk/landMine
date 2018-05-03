/**************************************
작 성 자 : 최병찬
작성일자 : 2016. 08. 11
목    적 : 문장을 입력 받아서 원하는 기능 실행용 숫자 반환 및 화면 출력 프로그램
***************************************/

#include<windows.h>
#include<stdio.h>
#include<conio.h>

// 받을 수 있는 최대 문장의 줄 수
#define _MAX_MENU_LINE			20
// 줄당 받을 수 있는 최대 문자수( + 2 는 띄어쓰기와 NULL문자용)
#define _MAX_MENU_LINE_TO_WORDS	20 + 2

// 반환 명령  (0x100 + 0x0XX + 0x001), (0x100) : 반환명령, (0x0XX + 0x001) : 반환 값
#define _MENU_RETURN_ORDER			0x100 + 0x001

// 이전 메뉴로 이동
#define _MENU_RETURN_END_ORDER		0x100

// 키보드 방향키 값
#define _KEY_DIRECTION	-32
#define _KEY_UP			72
#define _KEY_DOWN		80

#define _KEY_ENTER		13
#define _KEY_SPACE		32
#define _KEY_BACK_SPACE	8
#define _KEY_ESC		27

// 메뉴창 오더 실행
int Fs_Menu_Order_Action(char order, int *menu_order_p, int end_line);


/*********************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 09
* 작동원리 :	문자열(char[20][22])와 마지막열(int형 2~20)(마지막열은 0으로 반환)을 입력받아서
				2~20 줄의 메뉴를 지정 받아서 1~19의 값을 반환(ex, 마지막열은 0으로 반환 하기 때문)
*********************************************/
int fs_menu(char menu_text[_MAX_MENU_LINE][_MAX_MENU_LINE_TO_WORDS], int end_line/*문장의 라인 수*/) {


	// 메인 메뉴 명령어 저장, 0~(end_line-1)
	int fs_menu_order = 0;

	// 메인 메뉴 명령어 변경받기
	int *fs_menu_order_p = &fs_menu_order;

	// 메뉴 창 실행
	do {
		// 화면 지우기
		system("cls");

		// 메뉴창 프린트
		for (int line = 0; line < end_line; line++) {

			// 포인터 위치
			if (fs_menu_order == line)
				printf("  ▶  ");
			else
				printf("    ");

			printf("%s\n", menu_text[line]);
		}

		// 메뉴 이벤트 실행
		Fs_Menu_Order_Action(_getch(), fs_menu_order_p, end_line);

	} while ((fs_menu_order / 0x100) < 1);

	system("cls");
	return (fs_menu_order % 0x100);
}



int Fs_Menu_Order_Action(char order, int *menu_order_p, int end_line)
{
	switch (order) {
		// 방향키 입력받을 시 쓸모없는 -32 값 제거
	case _KEY_DIRECTION:
		break;

		// 방향키 up키
	case _KEY_UP:
		if (*menu_order_p > 0)
			*menu_order_p = *menu_order_p - 1;
		else if (*menu_order_p == 0)
			*menu_order_p = end_line - 1;
		break;
		// 방향키 down키
	case _KEY_DOWN:
		if (*menu_order_p < end_line - 1)
			*menu_order_p = *menu_order_p + 1;
		else if (*menu_order_p == end_line - 1)
			*menu_order_p = 0;
		break;
	case _KEY_ENTER:
	case _KEY_SPACE:
		// 메뉴선택 - 실행
		// 만약 마지막열 일경우 0 종료를 반납
		if (*menu_order_p == end_line - 1)
		{
			*menu_order_p = _MENU_RETURN_END_ORDER;
			return 0;
		}
		else {
			*menu_order_p = *menu_order_p + _MENU_RETURN_ORDER;
		}
		break;
	case _KEY_BACK_SPACE:
	case _KEY_ESC:
		*menu_order_p = _MENU_RETURN_END_ORDER;
		break;
	default:
		break;
	}
	return 0;
}