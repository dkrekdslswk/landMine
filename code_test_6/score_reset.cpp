/****************************************
* 제    목 : 랭크저장 파일이 없을 때 다시 만들기
* 작성일자 : 2016. 09. 07
* 제 작 자 : 최병찬
* 목    적 : 랭크 저장의 기본 셋팅으로 파일 생성하기
*****************************************/

#include <stdio.h>
#include <stdlib.h>

#define RANK_SAVE		9
#define SCORE_SAVE		5
#define MAX_RANK_SAVE	256

void score_reset(char save_name[MAX_RANK_SAVE]) {

	// 파일의 좌표저장
	FILE*	fp								= NULL;

	// 저장전 점수를 처리하기위한 임시 저장소
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

		// 저장 위치시작 주소기록
		fputc('=', fp);
		fputc(save_name[save], fp);
		fputc('=', fp);
		fputc('\n', fp);

		// 저장소에 기본 값으로 넣기
		for (int i = 0; i < RANK_SAVE; i++) {
			// 등수를 기록
			fputc((i + '1'), fp);
			// 아무것도 아닌 이름을 기록
			fputs("NUM", fp);

			// 기본적으로 들어갈 점수를 셋팅
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