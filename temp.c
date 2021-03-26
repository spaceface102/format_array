
int print_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((int *)array)[i];}

int print_uint(char *specifier, void *array, unsigned long i /*index*/)
	{return ((unsigned int *)array)[i];}

int print_char(char *specifier, void *array, unsigned long i /*index*/)
	{return ((char *)array)[i];}

int print_float(char *specifier, void *array, unsigned long i /*index*/)
	{return ((float *)array)[i];}

int print_double(char *specifier, void *array, unsigned long i /*index*/)
	{return ((double *)array)[i];}

int print_uint8(char *specifier, void *array, unsigned long i /*index*/)
	{return ((uint8_t *)array)[i];}

int print_uint16(char *specifier, void *array, unsigned long i /*index*/)
	{return ((uint16_t *)array)[i];}

int print_uint32(char *specifier, void *array, unsigned long i /*index*/)
	{return ((uint32_t *)array)[i];}

int print_uint64(char *specifier, void *array, unsigned long i /*index*/)
	{return ((uint64_t *)array)[i];}

int print_short_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((short int *)array)[i];}

int print_unsigned_short_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((unsigned short int *)array)[i];}

int print_signed_char(char *specifier, void *array, unsigned long i /*index*/)
	{return ((signed char *)array)[i];}

int print_unsigned_char(char *specifier, void *array, unsigned long i /*index*/)
	{return ((unsigned char *)array)[i];}

int print_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((long int *)array)[i];}

int print_unsigned_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((unsigned long int *)array)[i];}

int print_long_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((long long int *)array)[i];}

int print_unsigned_long_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return ((unsigned long long int *)array)[i];}
