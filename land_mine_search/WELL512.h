#pragma once
/* WELL512 random number generator*/
namespace well_random_get {
	/* random seed setting */
	void state_setting(unsigned long seed);
	/* return 32 bit random number */
	unsigned long get(void);
	/* output int numver */
	int getint(int a, int b);
}