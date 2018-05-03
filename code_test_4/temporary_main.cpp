
#include"land_mine_game_conptroller.h"
#include"land_mine_game_setting_save.h"

int game_start(int setting_high, int setting_width, int setting_mine, unsigned char* game_setting) {
	// 게임 실행 명령어 인식
	int game_order = 0;
	do {
		Land_Mine_Game_Screen(setting_high, setting_width, land_mine_game_setting_save::ground());
		game_order = Land_Mine_Game_Controller(setting_high, setting_width, setting_mine, game_setting);

		if (game_order == _MINE_BURST) {
			break;
		}
		if (game_order == _KEY_ESC) {
			break;
		}
		if (game_order == _ONE_TURN_KILL) {
			break;
		}
		if ((game_order & _MINE_CLEAR) == _MINE_CLEAR) {
			break;
		}
	} while (1);
	return game_order;
}