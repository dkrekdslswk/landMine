#pragma once

#define RANK_SAVE		9
#define SCORE_SAVE		5
#define MAX_RANK_SAVE	256

/****************************************
* 제    목 : 랭크저장 파일이 없을 때 다시 만들기
* 작성일자 : 2016. 09. 07
* 제 작 자 : 최병찬
* 목    적 : 랭크 저장의 기본 셋팅으로 파일 생성하기
*****************************************/
void score_reset(char save_name[MAX_RANK_SAVE]);