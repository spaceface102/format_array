#include <stdio.h>
#include <stdint.h>

typedef union alltypes{
	int i;
	unsigned int ui;
	char c;
	char *cp; //char pointer
	unsigned char uc;
	float f;
	double d;
	uint8_t u1; //influenced by numpy
	uint16_t u2; //u# where # == num bytes
	uint32_t u4;
	uint64_t u8;
	short h;
	unsigned short uh;
	long int l;
	unsigned long int ul;
	long long int ll;
	unsigned long long int ull;
} alltypes;

int main(void)
{	
	alltypes x;
	x.f = 83e3;
	printf("%f\n", x.f);
	printf("%d\n", x.i);
	return 0;
}

