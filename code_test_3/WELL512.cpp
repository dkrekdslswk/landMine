namespace well_random_get{
	/* initialize state to random bite */
	static unsigned long state[16];
	/* init should also reset this to 0 */
	static unsigned int  index = 0;

	/* random setting */
	void state_setting(unsigned long seed) {
		for (int i = 0; i<16; ++i) {
			state[i] = (unsigned long)(seed * i + i * i);
		}
	}

	/* return 32 bit random number */
	unsigned long get(void) {
		unsigned long a = 0, b = 0, c = 0, d = 0;
		a = state[index];
		c = state[(index + 13) & 15];
		b = a^c ^ (a << 16) ^ (c << 15);
		c = state[(index + 9) & 15];
		c ^= (c >> 11);
		a = state[index] = b^c;
		d = a ^ ((a << 5) & 0xDA442D20UL);
		index = (index + 15) & 15;
		a = state[index];
		state[index] = a^b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);
		return state[index];
	}

	/* output int numver */
	int getint(int a, int b) {
		return int(get() % b + a);
	}
	
}


//	#include<stdio.h>
//	#include<time.h>

/*
int main(void)
{
	well_random_get::state_setting((unsigned long)time(NULL));

	for (int i = 1; i <= 100; i++) {
		printf("%4X  ", well_random_get::getint(1, 100000));
	}
	return 0;
}
*/