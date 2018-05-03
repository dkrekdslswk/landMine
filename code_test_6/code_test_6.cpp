/*****************************************************
* ��    �� : TXT���� ��� ����
* �ۼ����� : 2016. 08. 29
* �� �� �� : �ֺ���
* ��    �� : �����͸� ���Ͽ� �����ϰ� �ҷ����� ���� ����
******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "score_reset.h"

#define RANK_SAVE	9
#define SCORE_SAVE	5
#define NAME_SAVE	3

// ��ŷ�� ����� �����
typedef struct rank
{
	char	name[NAME_SAVE + 1];
	short	score;
}Rank;

int main()
{
	// ��ŷ�� �����ϴ� ����
	Rank score_rank[RANK_SAVE]	= { 0 };

	// ������ ����� ����
	FILE* fp			= NULL;

	fopen_s(&fp, "code_test_6.txt", "r+");
	if (fp == NULL) {
		// ����E, �븻N, �ϵ�H�� ��ǥ�� ��ũ���̺� �ؽ�Ʈ ������ �����ϴ� �Լ�
		score_reset("ENH");

		fopen_s(&fp, "code_test_6.txt", "r+");
		if (fp == NULL) {
			printf("FILE OPEN ERROR!!");
			exit(0);
		}
	}

	// ���ϴ� save_point ���������� ã��
	{
		int temp_save[3] = { 0 };
		do {
			temp_save[0] = temp_save[1];
			temp_save[1] = temp_save[2];
			temp_save[2] = fgetc(fp);

			if ((temp_save[0] == '=') && (temp_save[2] == '=')) {
				if (temp_save[1] == 'E') {
					// '\n'����
					fgetc(fp);
					break;
				}
			}
		} while (1);
	}

	for (int i = 0 ; i < RANK_SAVE ; i++) {
		// ��� ����
		fgetc(fp);

		// �̸� �ޱ�
		for (int j = 0 ; j < NAME_SAVE ; j++) {
			score_rank[i].name[j] = fgetc(fp);
		}

		// ���� �ޱ�
		for (int j = 0 ; j < SCORE_SAVE ; j++) {
			score_rank[i].score = score_rank[i].score * 10 + (fgetc(fp) - '0');
		}


		// �ٱ��� ����
		fgetc(fp);
	}
	for (int i = 0 ; i < RANK_SAVE ; i++) {
		printf("%d) %s : %5d\n\n", (i + 1), score_rank[i].name, score_rank[i].score);
	}

	fclose(fp); 
	return 0;

}