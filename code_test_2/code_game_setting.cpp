/*****************************************
�� �� �� : �ֺ���
�ۼ����� : 2016. 08. 11
��    �� : ����ã�� �Լ� �ۼ��� ���� ���� �׽�Ʈ
*******************************************/

#define KEY_ENTER			13
#define KEY_BACK_SPACE		8
#define KEY_ESC				27

// 10����
#define _TYPE_DECIMAL_KEY_1		'n'
#define _TYPE_DECIMAL_KEY_2		'N'
#define _TYPE_DECIMAL			10
// 8����
#define _TYPE_OCTAL_KEY_1		'o'
#define _TYPE_OCTAL_KEY_2		'O'
#define _TYPE_OCTAL				8
// 16����
#define _TYPE_HEXADECIMAL_KEY_1	'x'
#define _TYPE_HEXADECIMAL_KEY_2	'X'
#define _TYPE_HEXADECIMAL		16
// ���
#define _TYPE_ENTER				13

#include<stdio.h>
#include<windows.h>
#include<conio.h>

/*
void main(void) {
	Output_Unsigned_Integer(5,5000);
}
*/

unsigned int Output_Unsigned_Integer (unsigned int min_number, unsigned int max_number) {

	// ���� ������ 0�̸� �ش� ���ڸ� �ݳ�, ���� ���ڰ� �ְ� ���ں��� Ŭ �� 0�� �ݳ�
	if (min_number == max_number)
		return min_number;
	else if (min_number > max_number)
		return 0;

	// ���� �ӽ� ����(���� ���ڷ� �ʱ�ȭ)
	unsigned int	number_save		= min_number;

	// ������ ����(10������ �ʱ�ȭ)
	char			type			= _TYPE_DECIMAL;

	do{
		// â �ʱ�ȭ
		system("cls");

		// ������ ���� ���� ���
		switch (type) {
		default:
			printf("type ���� �̻��� �ֽ��ϴ�. type ���� �ʱ�ȭ �մϴ�\n");
			type = _TYPE_DECIMAL;
			Sleep(150);
			system("cls");
		case _TYPE_DECIMAL:
			printf("%d\n", number_save);
			break;
		case _TYPE_OCTAL:
			printf("%#o\n", number_save);
			break;
		case _TYPE_HEXADECIMAL:
			printf("%#x\n", number_save);
			break;
		}
		printf("(n(16������ d�� �ߺ��̿���) : 10����, o : 8����, x : 16����)\n");


		// ���� �Է� �� ��ɾ� �Է� �ޱ�
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
			if(type != _TYPE_OCTAL)
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

			// ���ڿ��� ��ĭ ������
		case KEY_BACK_SPACE:
			number_save = number_save / type;
			break;

			// ��� ����ϱ�
		case KEY_ENTER:
			// ���� �Է� ���, �����·� ���
		case KEY_ESC:
			type = _TYPE_ENTER;
			break;

			// 10������ ����
		case _TYPE_DECIMAL_KEY_1:
		case _TYPE_DECIMAL_KEY_2:
			type = _TYPE_DECIMAL;
			break;

			// 8������ ����
		case _TYPE_OCTAL_KEY_1:
		case _TYPE_OCTAL_KEY_2:
			type = _TYPE_OCTAL;
			break;

			// 16������ ����
		case _TYPE_HEXADECIMAL_KEY_1:
		case _TYPE_HEXADECIMAL_KEY_2:
			type = _TYPE_HEXADECIMAL;
			break;
			// ���ص� ��ɾ �ƴϸ� ���� ����
		default:
			printf("���ڿ� ������ ��ɾ� ���� ���� �Է����� ���� �ּ���..!\n");
			Sleep(300);
			break;
		}

		// �� ���� Ȯ�� �� ������ ����� ����
		if (number_save > max_number) {
			printf("���ڰ� ŭ�ϴ�. \n");
			number_save = max_number;
			Sleep(150);
		}

		// ��� ���
		if (type == _TYPE_ENTER)
		{
			if (number_save < min_number) {
				printf("���ڰ� �۽��ϴ�. \n");
				Sleep(150);
			}
			else {
				printf("����� ��� �մϴ�. \n");
				break;
			}
		}
	} while (1);


	return number_save;
}