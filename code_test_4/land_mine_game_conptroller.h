#pragma once


// 지뢰가 터디면 발생
#define _MINE_BURST		9
#define _KEY_ESC		27
#define _MINE_CLEAR		0xff0000
#define _ONE_TURN_KILL	-1

int Land_Mine_Game_Controller(int high, int wdith, int mine, unsigned char* game_setting);

int Land_Mine_Game_Screen(int map_data_high, int map_data_width, int map_design);

int game_start(int setting_high, int setting_width, int setting_mine, unsigned char* game_setting);

