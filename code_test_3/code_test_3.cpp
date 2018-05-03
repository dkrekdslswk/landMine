/****************************************************
* 제    목 : 지뢰찾기 맵 만들기
* 작성일자 : 2016. 08. 16 ~
* 작 성 자 : 최병찬
* 목    적 : 지뢰찾기의 저장된 설정값을 받아 맵을 만들기
*****************************************************/

void Land_Mine_Map_Build();

#include"WELL512.h"
#include"land_mine_game_setting_save.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#define HIGH_	9
#define WHIGT_	9
#define MINE_	10

void save_test(unsigned int high, unsigned int width) {

	// a[high][width]
	// a[0~high-1][0~width-1] = *(b + (0~high-1)*width + 0~width-1)
	char* land_map_save = (char*)malloc(sizeof(char) * high * width);
	if (land_map_save == NULL)
	{
		puts("동적할당 실패!!!!");
	}
	for (unsigned int i = 0; i <= high - 1; i++) {
		for (unsigned int j = 0; j <= width - 1; j++)
		{
			*(land_map_save + (i*width) + j) = '0' + j;
		}
	}
	// 문장으로 볼껀데 마지막에는 끝표시를!

	printf("%x %x", *land_map_save, *(land_map_save + (2*width) + 2));

	free(land_map_save);
}
void main() {
	/*
	Land_Mine_Map_Build();
	*/
	save_test(HIGH_, WHIGT_);
}
void Land_Mine_Map_Build() {

	// 맵 크기대로 맵 만들기
	// 맵정보는 어디에 저장하고 어디에 부르지?
	// 24줄 + 30bit ....... unsigned long map_data[24]
	// 일단 여기에 저장해서
	unsigned int land_mine_map[HIGH_] = {0};

	// 랜덤값 초기화
	well_random_get::state_setting((unsigned long)time(NULL));

	// 매설할 지뢰 남은 수
	int land_mine_count = MINE_;
	// 지뢰가 설치되는 위치를 임시 저장하기
	int land_mine_point = 0;

	do {
		// 지뢰가 메설된 위치 받기
		land_mine_point = well_random_get::getint(0, ((HIGH_ * WHIGT_) - 1));

		// 위치값 / 가로길이 = 0 ~ (높이 - 1)
		// 위치값 % 가로길이 = 0 ~ (가로길이 - 1)
		if (!(land_mine_map[land_mine_point / WHIGT_] & (0x01ul << (land_mine_point % WHIGT_))))
		{
			// 지뢰사용
			land_mine_count--;
			// 매설했어!
			land_mine_map[land_mine_point / WHIGT_] += (0x01ul << land_mine_point % WHIGT_);
		}
		// 매설할 지뢰가 없어.
	} while (land_mine_count > 0);
	
	// 여기 에다가 값을 저장해서
	// 저장된 값을 리턴하자
	// 0 = 근처에 지뢰가 없음, 1 ~ 8 = 근처에 지뢰 수, 9 = 지뢰
	// 이거 한개가 4bit네
	// 확인표시는 !(지뢰 있는거 같아) ?(잘몰라) -(미확인)  총 3종류니까 2bit
	// 11(지뢰 모르겠어), 10(지뢰 있는거 같아), 01(미확인), 00(확인)으로 쓰자
	char land_mine_build[HIGH_][WHIGT_ + 1] = {0};
	
	// 이건 확인을 위해 자료에 '0'을 떄려 밖고 '\n' 뛰어쓰기도 첨가한거야!
	for (int i = 0; i <= HIGH_ - 1; i++) {
		for (int j = 0; j <= WHIGT_ - 1; j++)
		{
			land_mine_build[i][j] = '0';
		}
		land_mine_build[i][WHIGT_] = '\n';
	}
	// 문장으로 볼껀데 마지막에는 끝표시를!
	land_mine_build[HIGH_ - 1][WHIGT_] = '\0';

	// 지뢰 위치를 확인해서 
	// 근처에 지뢰 없음 0, 근처의 지뢰수 1~8, 여기엔 지뢰가 9 표기
	for (int high = 0; high <= HIGH_ - 1 ; high++) {
		for (int wight = 0 ; wight <= WHIGT_ - 1 ; wight++) {
			if ((land_mine_map[high] >> wight) & 0x01ul) {
				land_mine_build[high][wight] = '9';

				if (high != 0) {
					if (wight != 0) {
						if(land_mine_build[high - 1][wight - 1] != '9')
							land_mine_build[high - 1][wight - 1]++;
					}
					if (land_mine_build[high - 1][wight] != '9')
						land_mine_build[high - 1][wight]++;

					if (wight != WHIGT_ - 1) {
						if (land_mine_build[high - 1][wight + 1] != '9')
							land_mine_build[high - 1][wight + 1]++;
					}
				}
				if (wight != 0) {
					if (land_mine_build[high][wight - 1] != '9')
						land_mine_build[high][wight - 1]++;
				}
				if (wight != WHIGT_ - 1) {
					if (land_mine_build[high][wight + 1] != '9')
						land_mine_build[high][wight + 1]++;
				}
				if (high != HIGH_ - 1) {
					if (wight != 0) {
						if (land_mine_build[high + 1][wight - 1] != '9')
							land_mine_build[high + 1][wight - 1]++;
					}
					if (land_mine_build[high + 1][wight] != '9')
						land_mine_build[high + 1][wight]++;

					if (wight != WHIGT_ - 1) {
						if (land_mine_build[high + 1][wight + 1] != '9')
							land_mine_build[high + 1][wight + 1]++;
					}
				}
			}
		}
	}

	printf("%s", land_mine_build);
	// 게임실행?

}