#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

void clear_chars(int number);
void repeat(char c, int number);
void printarray(void *array, unsigned long array_size, int type_size, int max_chars_per_line, char *specifier);

int main(void)
{
	float array[1000];
	for(int i = 0; i < 1000; i++)
		array[i] = i*1e10;
	printarray(array, 1000, sizeof(int), 80, "%f");
}

void printarray(void *array, unsigned long array_size, int type_size, int max_chars_per_line, char *specifier)
{
	/*void pointer for array, to accept any type of array
	array_size necessary to ONLY access memory related to
	specific array, where each element is of type_size 
	bytes, aka == sizeof(array_type), and max_chars denotes
	max_chars per line. The character specifier is a string
	directly corresponding to the built in printf specifiers
	such as %d, %c, etc.*/
	
	//initial check, since code depends heavily on value of specifier
	//[5] since at most %lld or something to that effect (4 chars + null char)
	char base_specifier[5], base_spec_len;
	base_spec_len = specifier_strip(specifier, base_specifier, 5); 
	if (base_specifier[0] != '%')
	{
		printf("Please provide a standard specifier such as %%d, %%f, %%lf, etc!\n");
		return;
	}

	//------------------------------------------------------------------------
	int prev; //num of chars from last print
	int new_line; //track if new_line
	int (*custom_print)(char *specifier, void *array, unsigned long i);
	//second specifier check
	if (base_spec_len <= 1) //aka < 2
	{
		printf("Please make sure to provide more than just %% as specifier!!!\n");
		return;
	}

	//derefrence pointer correctly based on the specifier!
	//https://www.cplusplus.com/reference/cstdio/printf/ 
	switch(base_specifier[1]) //already check specifier[0] && strlen
	{
		case 'd': case 'i': 
			custom_print = print_int;
			break;
		case 'u': case 'o': case 'x': case 'X':
			custom_print = print_uint; //unsigned
			break;
		case 'c': case 's': 
			/*if 'c', specifier will ensure to print 
			only one char, and will throw out error if
			each index of the array is not a character 
			but character pointer
			if 's', specifier will ensure string are printed
			therefore user passed in an array of character 
			pointers, aka array of strings (think *argv[]) */
			custom_print = print_char;
			break;
		case 'f':
			custom_print = print_float; 
			break;
		case 'F': //I will be treating this as double
			custom_print = print_double;
			break;
		case 'e': case 'E'://scientific notation
			if (type_size == 8) //double is 8 bytes
				custom_print = print_double;
			else if (type_size == 4) //float is 4 bytes
				custom_print = print_float;
			break;
		case 'p': //pointer address
			if (type_size == 8) //64 bit system
				custom_print = print_uint64;
			else if (type_size == 4) //32 bit system
				custom_print = print_uint32;
			else if (type_size == 2) //16 bit system
				custom_print = print_uint16;
			else if (type_size == 1) //8 bit system
				custom_print = print_uint8;
			break;	
		case 'h':
			if(spec_len >= 3) //either 3 or 4 
			{
				switch(specifier[2])
				{
					case 'd': case 'i':
						custom_print = print_short_int;
						break;
					case 'u': case 'o': case 'x': case 'X':
						custom_print = print_unsigned_short_int;
						break; 
					case 'h':	
						if(spec_len == 4)
						{
							switch(specifier[3])
							{
								case 'd': case 'i':
									custom_print = print_signed_char;
									break;
								case 'u': case 'o': case 'x': case 'X':
									custom_print = print_unsigned_char;
									break;
							}
						}
						break;
				}
			}
			break;
		case 'l':
			if(spec_len >= 3) //either 3 or 4
			{
				switch(specifier[2])
				{
					case 'f':
						custom_print = print_double;
						break;
					case 'd': case 'i':
						custom_print = print_long_int;
						break;
					case 'u': case 'o': case 'x': case 'X':
						custom_print = print_unsigned_long_int;
						break;
					case 'l':
						if (spec_len == 4)
						{
							switch(specifier[3])
							{
								case 'd': case 'i':
									custom_print = print_long_long_int;
									break;
								case 'u': case 'o': case 'x': case 'X':
									custom_print = print_unsigned_long_long_int;
									break;
							}
						}
						break;
				}
			}
			else //spec_len == 2
				custom_print = print_long_int;
			break;
		default:
			printf("Unknown specifier: %s\n", specifier);
			return;
	}
	//------------------------------------------------------------------------
	
	for(int i = 0, j = 0; i < array_size; i++)
	{
		prev = 0;

		prev += printf(", ");
		j += prev;
		new_line = 0;
		if (j > max_chars_per_line) //will only trip when extra chars are written to stdout
		{
			i--; //need to reprint current index
			j = 0; //reset char counter for next line
			clear_chars(prev); //remove extra characters to avoid copies
			new_line = printf("\n"); //will cause stdout flush and also new line!
		}
	}
	//final clean up, loop terminated, but didn't trip 'if (j > max_chars)'
	if(!new_line)
	{
		clear_chars(2); //remove final ", " they are extra and should be removed
		printf("\n");
	}
}

int specifier_strip(char *specifier, char *base_specifier, int size_base) 
{
	/*Ignores flags, width, and .precision specifiers
	in order to have correct classification in order
	to 'safely' convert a void pointer and derefrence it*/
	//size_base == len(base_specifier) which is usually 5
	int j = 0;
	for(int i = 0; specifier[i] != '\0' && j < size_base; i++)
	{
		switch(specifier[i])
		{
			case 'd': case 'i': case 'u': case 'o': case 'x':
			case 'X': case 'f': case 'f': case 'e': case 'E':
			case 'c': case 's': case '%': case 'h': case 'l':
				base_specifier[j++] = specifier[i];
				break;
		}
	}
	base_specifier[j + 1] = '\0';
	return j; //return len of base_specifier does the job of strlen
}

void clear_chars(int number)
{
	repeat('\b', number);
	repeat(' ', number);
	repeat('\b', number);
}

void repeat(char c, int number)
{
	for(int i = 0; i < number; i++)
		printf("%c", c);
}


//----------------LIST OF SLIGHTLY DIFFRENT FUNCS, USED FOR FUNC *-----------------
int print_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((int *)array)[i]);}

int print_uint(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((unsigned int *)array)[i]);}

int print_char(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((char *)array)[i]);}

int print_float(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((float *)array)[i]);}

int print_double(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((double *)array)[i]);}

int print_uint8(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((uint8_t *)array)[i]);}

int print_uint16(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((uint16_t *)array)[i]);}

int print_uint32(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((uint32_t *)array)[i]);}

int print_uint64(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((uint64_t *)array)[i]);}

int print_short_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((short int *)array)[i]);}

int print_unsigned_short_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((unsigned short int *)array)[i]);}

int print_signed_char(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((signed char *)array)[i]);}

int print_unsigned_char(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((unsigned char *)array)[i]);}

int print_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((long int *)array)[i]);}

int print_unsigned_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((unsigned long int *)array)[i]);}

int print_long_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((long long int *)array)[i]);}

int print_unsigned_long_long_int(char *specifier, void *array, unsigned long i /*index*/)
	{return printf(specifier, ((unsigned long long int *)array)[i]);}
