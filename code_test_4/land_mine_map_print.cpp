/*****************************************************
* ��    �� : ������ �������� �޾Ƽ� ȭ�鿡 ���
* �ۼ����� : 2016. 08. 18
* �� �� �� : �ֺ���
* ��    �� :
				�Էµ� ������ ����ã�⿡ ���� ���� �ְ�
				ȭ���� �⺻ �������� ����Ѵ�����
				gotoxy�� �̿��Ͽ� ȭ���� �������� ���� �ϱ�
				+ ���ý���â�� �̿��ؼ� �÷���Ÿ���� 
				  �ǽð����� ǥ���ϴ� �͵� �õ�
				  + ����̸� ����� ����â�� ������ ������.?
*******************************************************/

#include<stdio.h>
#include "fs_conio_order.h"
#include<windows.h>

#define NOMAL_DESIGN	0x1

// �⺻���� ��Ÿ���� �� ǥ��
void nomal_map_design(int map_data_high, int map_data_width);

// ���ʸ��� �¸��ߴ� �� ���Ͻ�ų��?
// ����޾Ƽ� ����ϴ°� ���?
// .txt ���� �����ŷ�?
int Land_Mine_Game_Screen(int map_data_high, int map_data_width, int map_design) {

	system("cls");
	resz((map_data_width * 4 + 2 + 1 + 30), (map_data_high * 2 + 3));
	switch (map_design)
	{
	case NOMAL_DESIGN:
		nomal_map_design(map_data_high, map_data_width);
		break;
	default:
		break;
		return 0;
	}
	return 0;
}

// ������ǥ 1 + 2 * high
// ������ǥ 2 + 4 * width
// ȭ���� ���� ���� �ִ� ������
// ���� = , ���� = 
void nomal_map_design(int map_data_high, int map_data_width) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf8);
	printf("��");
	for (int width = 0; width <= map_data_width - 2; width++) {
		printf("  ��");
	}
	printf("  ��\n");

	for (int high = 1; high <= 2 * map_data_high - 1 ; high++) {
		if (high % 2) {
			printf("  ");
			for (int width = 0; width <= map_data_width - 1 ; width++) {
				printf("��  ");
			}
		}
		else {
			printf("��");
			for (int width = 1; width <= map_data_width - 1; width++) {
				printf("  ��");
			}
			printf("  ��");
		}
		printf("\n");
	}

	printf("��");
	for (int width = 1; width <= map_data_width - 1; width++) {
		printf("  ��");
	}
	printf("  ��");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
}