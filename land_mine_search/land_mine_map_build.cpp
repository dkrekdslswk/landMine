/*********************************************
* ��    �� : ����ã�� ���� �� �����
* �ۼ����� : 2016. 08. 18
* �� �� �� : �ֺ���
* ��    �� : ������� �޸� ���� ���̰� 
			 ȿ�������� ����ã�� ������ �غ��ϱ� ���� �۾�
**********************************************/

#include<stdlib.h>
#include<time.h>
#include"land_mine_game_setting_save.h"
#include"land_mine_game_conptroller.h"
#include"WELL512.h"

// ����� char* save�� �ݵ�� 0���� �ʱ�ȭ ���Ѽ� �־� �ּž� �մϴ�.
void Land_Mine_Mine_Initialize(unsigned char* save, int save_high, int save_width, int mine_count);

int Land_Mine_Map_Build(void) {
	// ���õ� ���� ���� �ޱ�
	int setting_high		= land_mine_game_setting_save::high();
	// ���õ� ���α��� ���� �ޱ�
	int setting_width		= land_mine_game_setting_save::width();
	// ���� ��� ���
	int return_game_result	= 0;

	// ������ ���̿� ���α��̷� �˸��� ũ���� ���� ����
	unsigned char* land_mine_map_save = (unsigned char*)malloc(sizeof(unsigned char) * setting_high * setting_width);
	// ���� ������ ������ �Ҵ� �ޱ� ����
	if (land_mine_map_save == NULL) {
		return false;
	}
	do {
		// �Ҵ�� ���� 0���� �ʱ�ȭ
		for (int Initialize = 0; Initialize <= (setting_high * setting_width - 1); Initialize++) {
			*(land_mine_map_save + Initialize) = 0;
		}

		// �ʿ� ���ڿ� ��ó ���� ���� �Է�
		Land_Mine_Mine_Initialize(land_mine_map_save, setting_high, setting_width, land_mine_game_setting_save::mine());

		// ���� ����.
		return_game_result = game_start(setting_high, setting_width, land_mine_game_setting_save::mine(), land_mine_map_save);
	
	} while (return_game_result == _ONE_TURN_KILL);

	// ���� ������ ����� Ǯ���ֱ�
	free(land_mine_map_save);
	return return_game_result;
}

// ����� save�� �ݵ�� 0���� �ʱ�ȭ ���Ѽ� �־� �ּž� �մϴ�.
void Land_Mine_Mine_Initialize(unsigned char* save, int save_high, int save_width, int mine_count) {

	// ������ �ʱ�ȭ
	well_random_get::state_setting((unsigned long)time(NULL));

	// �ż��� ���� ���� ��
	int land_mine_count = mine_count;
	// ���ڰ� ��ġ�Ǵ� ��ġ�� �ӽ� �����ϱ�
	int land_mine_point = 0;

	do {
		// ���ڰ� �޼��� ��ġ �ޱ�
		land_mine_point = well_random_get::getint(0, ((save_high * save_width) - 1));

		// ���� �ش� ��ǥ�� ���ְ� ������(0�� ���� ��) 1(��������)�� �Է�
		if ((*(save + land_mine_point)) == 0)
		{
			// ���ڻ��
			land_mine_count--;
			// �ż��߾�!
			*(save + land_mine_point) = 9;
		}
		// �ż��� ���ڰ� ����.
	} while (land_mine_count > 0);
	
	// ���� ��ġ�� Ȯ���ؼ� 
	// ��ó�� ���� ���� 0, ��ó�� ���ڼ� 1~8, ���⿣ ���ڰ� 9 ǥ��
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