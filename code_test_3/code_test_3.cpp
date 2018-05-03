/****************************************************
* ��    �� : ����ã�� �� �����
* �ۼ����� : 2016. 08. 16 ~
* �� �� �� : �ֺ���
* ��    �� : ����ã���� ����� �������� �޾� ���� �����
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
		puts("�����Ҵ� ����!!!!");
	}
	for (unsigned int i = 0; i <= high - 1; i++) {
		for (unsigned int j = 0; j <= width - 1; j++)
		{
			*(land_map_save + (i*width) + j) = '0' + j;
		}
	}
	// �������� ������ ���������� ��ǥ�ø�!

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

	// �� ũ���� �� �����
	// �������� ��� �����ϰ� ��� �θ���?
	// 24�� + 30bit ....... unsigned long map_data[24]
	// �ϴ� ���⿡ �����ؼ�
	unsigned int land_mine_map[HIGH_] = {0};

	// ������ �ʱ�ȭ
	well_random_get::state_setting((unsigned long)time(NULL));

	// �ż��� ���� ���� ��
	int land_mine_count = MINE_;
	// ���ڰ� ��ġ�Ǵ� ��ġ�� �ӽ� �����ϱ�
	int land_mine_point = 0;

	do {
		// ���ڰ� �޼��� ��ġ �ޱ�
		land_mine_point = well_random_get::getint(0, ((HIGH_ * WHIGT_) - 1));

		// ��ġ�� / ���α��� = 0 ~ (���� - 1)
		// ��ġ�� % ���α��� = 0 ~ (���α��� - 1)
		if (!(land_mine_map[land_mine_point / WHIGT_] & (0x01ul << (land_mine_point % WHIGT_))))
		{
			// ���ڻ��
			land_mine_count--;
			// �ż��߾�!
			land_mine_map[land_mine_point / WHIGT_] += (0x01ul << land_mine_point % WHIGT_);
		}
		// �ż��� ���ڰ� ����.
	} while (land_mine_count > 0);
	
	// ���� ���ٰ� ���� �����ؼ�
	// ����� ���� ��������
	// 0 = ��ó�� ���ڰ� ����, 1 ~ 8 = ��ó�� ���� ��, 9 = ����
	// �̰� �Ѱ��� 4bit��
	// Ȯ��ǥ�ô� !(���� �ִ°� ����) ?(�߸���) -(��Ȯ��)  �� 3�����ϱ� 2bit
	// 11(���� �𸣰ھ�), 10(���� �ִ°� ����), 01(��Ȯ��), 00(Ȯ��)���� ����
	char land_mine_build[HIGH_][WHIGT_ + 1] = {0};
	
	// �̰� Ȯ���� ���� �ڷῡ '0'�� ���� �۰� '\n' �پ�⵵ ÷���Ѱž�!
	for (int i = 0; i <= HIGH_ - 1; i++) {
		for (int j = 0; j <= WHIGT_ - 1; j++)
		{
			land_mine_build[i][j] = '0';
		}
		land_mine_build[i][WHIGT_] = '\n';
	}
	// �������� ������ ���������� ��ǥ�ø�!
	land_mine_build[HIGH_ - 1][WHIGT_] = '\0';

	// ���� ��ġ�� Ȯ���ؼ� 
	// ��ó�� ���� ���� 0, ��ó�� ���ڼ� 1~8, ���⿣ ���ڰ� 9 ǥ��
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
	// ���ӽ���?

}