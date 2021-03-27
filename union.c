#include <stdio.h>
#include <stdint.h>

typedef union alltypes{
	int i;
	unsigned int ui;
	char c; //covers signed char too
	char *cp; //char pointer for string handeling
	unsigned char uc;
	float f;
	double d;
	long double ld; //largest type (16 bytes in my system)
	uint8_t u1; //influenced by numpy
	uint16_t u2; //u# where # == num bytes
	uint32_t u4;
	uint64_t u8;
	short h;
	unsigned short uh;
	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;
} alltypes;

int main(void)
{	

	alltypes x;
	printf("%ld\n", sizeof(alltypes));
	x.i = 100;
	printf("%f\n", x.f);
	printf("%d\n", x.i);
	return 0;
}

