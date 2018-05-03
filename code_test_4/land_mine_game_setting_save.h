#pragma once

/***********************************************
* �� �� �� :	�ֺ���
* �������� :	2016. 08. 11 ~ 2016. 08. 16
* �� �� �� :	�������� ���� ������ unsigned long�� �ϳ��� ���� ���� �� �� �ִ� ���� ������ ���� ���� �Լ� �׷�				
************************************************/

namespace land_mine_game_setting_save {

	// ��ü ���� �� ���
	unsigned long	setting(void);
	// ���� ���� �� ���
	unsigned long	game_setting(void);
	// �ɼ� ���� �� ���
	unsigned long	option_setting(void);
	// ���� ���� �� ���
	int				high(void);
	// ���� ���� �� ���
	int				width(void);
	// ���� �� ���� �� ���
	int				mine(void);
	// ��� ���� �� ���
	int				ground(void);
	// Ȯ�� ���� �� ���
	bool			check(void);
	// ���� ������ �ִ� ���ڼ��� �� ���
	int				max_mine(void);

	// ��ü ���ð��� �ѹ��� �����ϴ� �Լ� (���� ���� ��Ұ� ������ ����� �ڵ� ���� �Է���.)
	void			setting_input(unsigned long input);
	// ���� ���ð��� �ѹ��� �����ϴ� �Լ� (���� ���� ��Ұ� ������ ����� �ڵ� ���� �Է���.)
	void			game_setting_input(unsigned long input);
	// �ɼ� ���ð��� �ѹ��� �����ϴ� �Լ� (���� ���� ��Ұ� ������ ����� �ڵ� ���� �Է���.)
	void			option_setting_input(unsigned long input);
	// ���� ���ð��� �����ϴ� �Լ� (9~24)
	void			high_input(int input);
	// ���� ���ð��� �����ϴ� �Լ� (9~30)
	void			width_input(int input);
	// ���ڼ� ���ð��� �����ϴ� �Լ� (10 ~ [���� * 0.94 - 9(�Ҽ��� �Ʒ� ����)(�ִ���̿��� �ִ밪�� 667)])
	void			mine_input(int input);
	// ��� ���ð��� �����ϴ� �Լ� (1~15)
	void			ground_input(int input);
	// Ȯ�� ���ð��� �����ϴ� �Լ� (true or false)
	void			check_input(bool input);
}