/**************************************
�� �� �� : �ֺ���
�ۼ����� : 2016. 08. 11
��    �� : ������ �Է� �޾Ƽ� ���ϴ� ��� ����� ���� ��ȯ �� ȭ�� ��� ���α׷�
***************************************/

#include<windows.h>
#include<stdio.h>
#include<conio.h>

// ���� �� �ִ� �ִ� ������ �� ��
#define _MAX_MENU_LINE			20
// �ٴ� ���� �� �ִ� �ִ� ���ڼ�( + 2 �� ����� NULL���ڿ�)
#define _MAX_MENU_LINE_TO_WORDS	20 + 2

// ��ȯ ���  (0x100 + 0x0XX + 0x001), (0x100) : ��ȯ���, (0x0XX + 0x001) : ��ȯ ��
#define _MENU_RETURN_ORDER			0x100 + 0x001

// ���� �޴��� �̵�
#define _MENU_RETURN_END_ORDER		0x100

// Ű���� ����Ű ��
#define _KEY_DIRECTION	-32
#define _KEY_UP			72
#define _KEY_DOWN		80

#define _KEY_ENTER		13
#define _KEY_SPACE		32
#define _KEY_BACK_SPACE	8
#define _KEY_ESC		27

// �޴�â ���� ����
int Fs_Menu_Order_Action(char order, int *menu_order_p, int end_line);


/*********************************************
* �� �� �� :	�ֺ���
* �ۼ����� :	2016. 08. 09
* �۵����� :	���ڿ�(char[20][22])�� ��������(int�� 2~20)(���������� 0���� ��ȯ)�� �Է¹޾Ƽ�
				2~20 ���� �޴��� ���� �޾Ƽ� 1~19�� ���� ��ȯ(ex, ���������� 0���� ��ȯ �ϱ� ����)
*********************************************/
int fs_menu(char menu_text[_MAX_MENU_LINE][_MAX_MENU_LINE_TO_WORDS], int end_line/*������ ���� ��*/) {


	// ���� �޴� ��ɾ� ����, 0~(end_line-1)
	int fs_menu_order = 0;

	// ���� �޴� ��ɾ� ����ޱ�
	int *fs_menu_order_p = &fs_menu_order;

	// �޴� â ����
	do {
		// ȭ�� �����
		system("cls");

		// �޴�â ����Ʈ
		for (int line = 0; line < end_line; line++) {

			// ������ ��ġ
			if (fs_menu_order == line)
				printf("  ��  ");
			else
				printf("    ");

			printf("%s\n", menu_text[line]);
		}

		// �޴� �̺�Ʈ ����
		Fs_Menu_Order_Action(_getch(), fs_menu_order_p, end_line);

	} while ((fs_menu_order / 0x100) < 1);

	system("cls");
	return (fs_menu_order % 0x100);
}



int Fs_Menu_Order_Action(char order, int *menu_order_p, int end_line)
{
	switch (order) {
		// ����Ű �Է¹��� �� ������� -32 �� ����
	case _KEY_DIRECTION:
		break;

		// ����Ű upŰ
	case _KEY_UP:
		if (*menu_order_p > 0)
			*menu_order_p = *menu_order_p - 1;
		else if (*menu_order_p == 0)
			*menu_order_p = end_line - 1;
		break;
		// ����Ű downŰ
	case _KEY_DOWN:
		if (*menu_order_p < end_line - 1)
			*menu_order_p = *menu_order_p + 1;
		else if (*menu_order_p == end_line - 1)
			*menu_order_p = 0;
		break;
	case _KEY_ENTER:
	case _KEY_SPACE:
		// �޴����� - ����
		// ���� �������� �ϰ�� 0 ���Ḧ �ݳ�
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