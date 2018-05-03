/****************************************
* ��    �� : ��ũ���� ������ ���� �� �ٽ� �����
* �ۼ����� : 2016. 09. 07
* �� �� �� : �ֺ���
* ��    �� : ��ũ ������ �⺻ �������� ���� �����ϱ�
*****************************************/

#include <stdio.h>
#include <stdlib.h>

#define RANK_SAVE		9
#define SCORE_SAVE		5
#define MAX_RANK_SAVE	256

void score_reset(char save_name[MAX_RANK_SAVE]) {

	// ������ ��ǥ����
	FILE*	fp								= NULL;

	// ������ ������ ó���ϱ����� �ӽ� �����
	short	save_base_score							= 0;
	char	temp_save_base_score[SCORE_SAVE + 1]	= { 0 };

	fopen_s(&fp, "code_test_6.txt", "w+");
	if (fp == NULL) {
		printf("FILE OPEN ERROR!!");
		exit(0);
	}

	for (int save = 0 ; save < MAX_RANK_SAVE ; save++) {

		if (save_name[save] == '\0') {
			break;
		}

		// ���� ��ġ���� �ּұ��
		fputc('=', fp);
		fputc(save_name[save], fp);
		fputc('=', fp);
		fputc('\n', fp);

		// ����ҿ� �⺻ ������ �ֱ�
		for (int i = 0; i < RANK_SAVE; i++) {
			// ����� ���
			fputc((i + '1'), fp);
			// �ƹ��͵� �ƴ� �̸��� ���
			fputs("NUM", fp);

			// �⺻������ �� ������ ����
			save_base_score = 60 * (i + 1);
			for (int j = 0 ; j < SCORE_SAVE ; j++) {
				temp_save_base_score[SCORE_SAVE - 1 - j] = save_base_score % 10 + '0';
				save_base_score /= 10;
			}
			fputs(temp_save_base_score, fp);
			fputc('\n', fp);
		}
		fputc('\n', fp);
	}
	fclose(fp);
}