/*****************************************************
* 제    목 : TXT저장 방법 연습
* 작성일자 : 2016. 08. 29
* 작 성 자 : 최병찬
* 목    적 : 데이터를 파일에 저장하고 불러오는 것을 연습
******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "score_reset.h"

#define RANK_SAVE	9
#define SCORE_SAVE	5
#define NAME_SAVE	3

// 랭킹을 기록할 저장소
typedef struct rank
{
	char	name[NAME_SAVE + 1];
	short	score;
}Rank;

int main()
{
	// 랭킹을 저장하는 공간
	Rank score_rank[RANK_SAVE]	= { 0 };

	// 파일의 헤더를 저장
	FILE* fp			= NULL;

	fopen_s(&fp, "code_test_6.txt", "r+");
	if (fp == NULL) {
		// 이지E, 노말N, 하드H의 좌표로 랭크세이브 텍스트 파일을 생성하는 함수
		score_reset("ENH");

		fopen_s(&fp, "code_test_6.txt", "r+");
		if (fp == NULL) {
			printf("FILE OPEN ERROR!!");
			exit(0);
		}
	}

	// 원하는 save_point 시작지점을 찾기
	{
		int temp_save[3] = { 0 };
		do {
			temp_save[0] = temp_save[1];
			temp_save[1] = temp_save[2];
			temp_save[2] = fgetc(fp);

			if ((temp_save[0] == '=') && (temp_save[2] == '=')) {
				if (temp_save[1] == 'E') {
					// '\n'제거
					fgetc(fp);
					break;
				}
			}
		} while (1);
	}

	for (int i = 0 ; i < RANK_SAVE ; i++) {
		// 등수 제거
		fgetc(fp);

		// 이름 받기
		for (int j = 0 ; j < NAME_SAVE ; j++) {
			score_rank[i].name[j] = fgetc(fp);
		}

		// 점수 받기
		for (int j = 0 ; j < SCORE_SAVE ; j++) {
			score_rank[i].score = score_rank[i].score * 10 + (fgetc(fp) - '0');
		}


		// 줄구분 제거
		fgetc(fp);
	}
	for (int i = 0 ; i < RANK_SAVE ; i++) {
		printf("%d) %s : %5d\n\n", (i + 1), score_rank[i].name, score_rank[i].score);
	}

	fclose(fp); 
	return 0;

}