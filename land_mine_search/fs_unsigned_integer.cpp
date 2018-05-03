/*****************************************
제 작 자 : 최병찬
작성일자 : 2016. 08. 11 ~ 2016. 08. 16 ~ 2016. 08. 16
목    적 : 지뢰찾기 함수 작성전 게임 셋팅 테스트
*******************************************/

#define KEY_ENTER			13
#define KEY_BACK_SPACE		8
#define KEY_ESC				27

// 10진법
#define _TYPE_DECIMAL_KEY_1		'n'
#define _TYPE_DECIMAL_KEY_2		'N'
#define _TYPE_DECIMAL			10
// 8진법
#define _TYPE_OCTAL_KEY_1		'o'
#define _TYPE_OCTAL_KEY_2		'O'
#define _TYPE_OCTAL				8
// 16진법
#define _TYPE_HEXADECIMAL_KEY_1	'x'
#define _TYPE_HEXADECIMAL_KEY_2	'X'
#define _TYPE_HEXADECIMAL		16
// 출력
#define _TYPE_ENTER				13
#define _TYPE_ESC				27

#include<stdio.h>
#include<windows.h>
#include<conio.h>

unsigned int fs_Output_Unsigned_Integer(unsigned int min_number, unsigned int max_number, int origin_number) {

	// 오류 입력값 걸러 내기
	// 숫자 범위가 0이면 해당 숫자를 반납, 최저 숫자가 최고 숫자보다 클 때 0을 반납
	if (min_number == max_number)
		return min_number;
	else if (min_number > max_number)
		return 0;

	// 출력할 숫자 임시 저장(최저 숫자로 초기화)
	unsigned int	number_save = NULL;

	// 숫자의 형태(10진수로 초기화)
	char			type = _TYPE_DECIMAL;

	do {
		// 창 초기화
		system("cls");

		printf("%d <=   [ ", min_number);
		// 숫자의 현재 상태 출력
		switch (type) {
		default:
			printf("type 값에 이상이 있습니다. type 값을 초기화 합니다\n");
			type = _TYPE_DECIMAL;
			Sleep(150);
			system("cls");
		case _TYPE_DECIMAL:
			printf("%d", number_save);
			break;
		case _TYPE_OCTAL:
			printf("%#o", number_save);
			break;
		case _TYPE_HEXADECIMAL:
			printf("%#x", number_save);
			break;
		}
		printf(" ]   <= %d\n", max_number);
		printf("(n(16진법의 d와 중복이여서) : 10진법,\n o : 8진법, x : 16진법)\n");
		printf("(Enter : 현재값 설정, ESC : 입력 취소)\n");


		// 숫자 입력 및 명령어 입력 받기
		switch (_getch()) {
		case '0':
			number_save = number_save * type + 0;
			break;

		case '1':
			number_save = number_save * type + 1;
			break;

		case '2':
			number_save = number_save * type + 2;
			break;

		case '3':
			number_save = number_save * type + 3;
			break;

		case '4':
			number_save = number_save * type + 4;
			break;

		case '5':
			number_save = number_save * type + 5;
			break;

		case '6':
			number_save = number_save * type + 6;
			break;

		case '7':
			number_save = number_save * type + 7;
			break;

		case '8':
			if (type != _TYPE_OCTAL)
				number_save = number_save * type + 8;
			break;

		case '9':
			if (type != _TYPE_OCTAL)
				number_save = number_save * type + 9;
			break;
		case 'a':
		case 'A':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 10;
			break;
		case 'b':
		case 'B':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 11;
			break;
		case 'c':
		case 'C':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 12;
			break;
		case 'd':
		case 'D':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 13;
			break;
		case 'e':
		case 'E':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 14;
			break;
		case 'f':
		case 'F':
			if (type == _TYPE_HEXADECIMAL)
				number_save = number_save * type + 15;
			break;

			// 숫자열을 한칸 없에기
		case KEY_BACK_SPACE:
			number_save = number_save / type;
			break;

			// 10진수로 변경
		case _TYPE_DECIMAL_KEY_1:
		case _TYPE_DECIMAL_KEY_2:
			type = _TYPE_DECIMAL;
			break;

			// 8진수로 변경
		case _TYPE_OCTAL_KEY_1:
		case _TYPE_OCTAL_KEY_2:
			type = _TYPE_OCTAL;
			break;

			// 16진수로 변경
		case _TYPE_HEXADECIMAL_KEY_1:
		case _TYPE_HEXADECIMAL_KEY_2:
			type = _TYPE_HEXADECIMAL;
			break;

			// 결과 출력하기
		case KEY_ENTER:
			// 현재 숫자가 최소값을 만족하는지 확인
			if (number_save < min_number) {
				printf("숫자가 작습니다. \n");
				Sleep(300);
			}
			// 만족할경우 결과 반환
			else {
				return number_save;
			}
			break;
			// 숫자 입력 취소, 원래의 숫자를 반환
		case KEY_ESC:
			return origin_number;
			break;

			// 정해둔 명령어가 아니면 전부 무시
		default:
			printf("숫자와 정해진 명령어 외의 값은 입력하지 말아 주세요..!\n");
			Sleep(300);
			break;
		}

		// 값 범위 확인 후 범위를 벗어나면 수정
		if (number_save > max_number) {
			printf("숫자가 큼니다. \n");
			number_save = max_number;
			Sleep(300);
		}
	} while (1);


	return number_save;
}