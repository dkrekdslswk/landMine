/**************************************************
�� �� �� : �ֺ���
�������� : 2016. 08. 10
��    �� : Ű���� ���� �Է� �޾� �ƽ�Ű �ڵ� ������ ��ȯ
**************************************************/

#include<stdio.h>

#include<conio.h>
#include<Windows.h>

int main(void)
{
	char input_key = 0;

	do {
		input_key = _getch();

		printf("%d\n", input_key);

	} while (input_key != '0');


	return 0;
}

/*
int main(void)
{
	char input_key[4] = {"��\n"};


	printf("%#2X\n", input_key[0]);
	printf("%#2X\n", input_key[1]);
	printf("%#2X\n", input_key[2]);

	char input_key_1[4] = { "��\n" };


	printf("%#2X\n", input_key_1[0]);
	printf("%#2X\n", input_key_1[1]);
	printf("%#2X\n", input_key_1[2]);

	if (input_key[0] & 0x80) {
		printf(" �����ڵ�� %s ", input_key);
	}

	return 0;
}
*/