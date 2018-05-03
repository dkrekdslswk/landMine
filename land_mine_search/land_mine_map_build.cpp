/*********************************************
* 제    목 : 지뢰찾기 게임 맵 만들기
* 작성일자 : 2016. 08. 18
* 작 성 자 : 최병찬
* 목    적 : 쓸대없는 메모리 낭비를 줄이고 
			 효율적으로 지뢰찾기 게임을 준비하기 위한 작업
**********************************************/

#include<stdlib.h>
#include<time.h>
#include"land_mine_game_setting_save.h"
#include"land_mine_game_conptroller.h"
#include"WELL512.h"

// 사용전 char* save를 반드시 0으로 초기화 시켜서 넣어 주셔야 합니다.
void Land_Mine_Mine_Initialize(unsigned char* save, int save_high, int save_width, int mine_count);

int Land_Mine_Map_Build(void) {
	// 셋팅된 높이 값을 받기
	int setting_high		= land_mine_game_setting_save::high();
	// 셋팅된 가로길이 값을 받기
	int setting_width		= land_mine_game_setting_save::width();
	// 게임 결과 출력
	int return_game_result	= 0;

	// 설정된 높이와 가로길이로 알맞은 크기의 맵을 설정
	unsigned char* land_mine_map_save = (unsigned char*)malloc(sizeof(unsigned char) * setting_high * setting_width);
	// 맵을 저장할 공간을 할당 받기 실패
	if (land_mine_map_save == NULL) {
		return false;
	}
	do {
		// 할당된 맵을 0으로 초기화
		for (int Initialize = 0; Initialize <= (setting_high * setting_width - 1); Initialize++) {
			*(land_mine_map_save + Initialize) = 0;
		}

		// 맵에 지뢰와 근처 지뢰 수를 입력
		Land_Mine_Mine_Initialize(land_mine_map_save, setting_high, setting_width, land_mine_game_setting_save::mine());

		// 게임 실행.
		return_game_result = game_start(setting_high, setting_width, land_mine_game_setting_save::mine(), land_mine_map_save);
	
	} while (return_game_result == _ONE_TURN_KILL);

	// 맵을 저장한 저장소 풀어주기
	free(land_mine_map_save);
	return return_game_result;
}

// 사용전 save를 반드시 0으로 초기화 시켜서 넣어 주셔야 합니다.
void Land_Mine_Mine_Initialize(unsigned char* save, int save_high, int save_width, int mine_count) {

	// 랜덤값 초기화
	well_random_get::state_setting((unsigned long)time(NULL));

	// 매설할 지뢰 남은 수
	int land_mine_count = mine_count;
	// 지뢰가 설치되는 위치를 임시 저장하기
	int land_mine_point = 0;

	do {
		// 지뢰가 메설된 위치 받기
		land_mine_point = well_random_get::getint(0, ((save_high * save_width) - 1));

		// 맵의 해당 좌표에 지롸가 없으면(0이 있을 때) 1(지뢰있음)을 입력
		if ((*(save + land_mine_point)) == 0)
		{
			// 지뢰사용
			land_mine_count--;
			// 매설했어!
			*(save + land_mine_point) = 9;
		}
		// 매설할 지뢰가 없어.
	} while (land_mine_count > 0);
	
	// 지뢰 위치를 확인해서 
	// 근처에 지뢰 없음 0, 근처의 지뢰수 1~8, 여기엔 지뢰가 9 표기
	for (int high = 0; high <= save_high - 1; high++) {
		for (int wight = 0; wight <= save_width - 1; wight++) {
			if (*(save + high * save_width + wight) == 9) {
				if (high != 0) {
					if (wight != 0) {
						if (*(save + (high - 1) * save_width + (wight - 1)) != 9)
							*(save + (high - 1) * save_width + (wight - 1)) = *(save + (high - 1) * save_width + (wight - 1)) + 1;
					}
					if (*(save + (high - 1) * save_width + (wight)) != 9)
						*(save + (high - 1) * save_width + (wight)) = *(save + (high - 1) * save_width + (wight)) + 1;

					if (wight != save_width - 1) {
						if (*(save + (high - 1) * save_width + (wight + 1)) != 9)
							*(save + (high - 1) * save_width + (wight + 1)) = *(save + (high - 1) * save_width + (wight + 1)) + 1;
					}
				}
				if (wight != 0) {
					if (*(save + (high) * save_width + (wight - 1)) != 9)
						*(save + (high) * save_width + (wight - 1)) = *(save + (high) * save_width + (wight - 1)) + 1;
				}
				if (wight != save_width - 1) {
					if (*(save + (high)* save_width + (wight + 1)) != 9)
						*(save + (high)* save_width + (wight + 1)) = *(save + (high)* save_width + (wight + 1)) + 1;
				}
				if (high != save_high - 1) {
					if (wight != 0) {
						if (*(save + (high + 1) * save_width + (wight - 1)) != 9)
							*(save + (high + 1) * save_width + (wight - 1)) = *(save + (high + 1) * save_width + (wight - 1)) + 1;
					}
					if (*(save + (high + 1) * save_width + (wight)) != 9)
						*(save + (high + 1) * save_width + (wight)) = *(save + (high + 1) * save_width + (wight)) + 1;

					if (wight != save_width - 1) {
						if (*(save + (high + 1) * save_width + (wight + 1)) != 9)
							*(save + (high + 1) * save_width + (wight + 1)) = *(save + (high + 1) * save_width + (wight + 1)) + 1;
					}
				}
			}
		}
	}
}