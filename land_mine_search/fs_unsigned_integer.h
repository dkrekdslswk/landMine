#pragma once

/*******************************************
* 작 성 자 :	최병찬
* 작성일자 :	2016. 08. 11 ~ 2016. 08. 16
* 사 용 법 :	(최저값, 최고값)을 입력 받아 범위 안의 unsigned int형을 반납하는 함수
				최저값 == 최고값 이면 최소값을 반환, 최저값 > 최고값 이면 0을 반환
				10진수, 8진수, 16진수 제공
				취소시 입력된 원본값을 반환
********************************************/
unsigned int fs_Output_Unsigned_Integer(unsigned int min_number, unsigned int max_number, int origin_number);