#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

void clear_chars(int number);
void repeat(char c, int number);
int specifier_strip(char *specifier, char *base_specifier, int size_base);
void printarray(void *array, unsigned long array_size, int type_size, int max_chars_per_line, char *specifier);
/*figure out a way to add dimensionality 
maybe by asking dimension of array, can use multi level pointers 
and therefore look at value of pointer and deduce the size, using
as well the infromation ot type_size. since array is passed as pointer
array+1 will access the next address space which will be equivalent
to array+type_size. If we are using a pointer to an array, aka double
pointer, dp_array+1 != array+1 but array+array_size
I could make a recursive function that terminates when dimension == 0*/

//-----ONLY USED TO DEFINE FUNCTION POINTER IN printarray()-----//
int void_deref_int(void *array, unsigned long i);
int void_deref_uint(void *array, unsigned long i);
int void_deref_char(void *array, unsigned long i);
int void_deref_signed_char(void *array, unsigned long i);
int void_deref_unsigned_char(void *array, unsigned long i);
int void_deref_float(void *array, unsigned long i);
int void_deref_double(void *array, unsigned long i);
int void_deref_uint8(void *array, unsigned long i);
int void_deref_uint16(void *array, unsigned long i);
int void_deref_uint32(void *array, unsigned long i);
int void_deref_uint64(void *array, unsigned long i);
int void_deref_short_int(void *array, unsigned long i);
int void_deref_unsigned_short_int(void *array, unsigned long i);
int void_deref_long_int(void *array, unsigned long i);
int void_deref_unsigned_long_int(void *array, unsigned long i);
int void_deref_long_long_int(void *array, unsigned long i);
int void_deref_unsigned_long_long_int(void *array, unsigned long i);
//end of function pointer inteneded functions

int main(void)
{
	float array[1000];
	for(int i = 0; i < 1000; i++)
		array[i] = i*1e10;
	printarray(array, 1000, sizeof(float), 80, "%f");
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
	int (*deref_void)(void *array, unsigned long i);
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
		case 'f': //although will print as double, still have to derefrence correctly
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
			if(base_spec_len >= 3) //either 3 or 4 
			{
				switch(base_specifier[2])
				{
					case 'd': case 'i':
						custom_print = print_short_int;
						break;
					case 'u': case 'o': case 'x': case 'X':
						custom_print = print_unsigned_short_int;
						break; 
					case 'h':	
						if(base_spec_len == 4)
						{
							switch(base_specifier[3])
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
			if(base_spec_len >= 3) //either 3 or 4
			{
				switch(base_specifier[2])
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
						if (base_spec_len == 4)
						{
							switch(base_specifier[3])
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
			else //base_spec_len == 2
				custom_print = print_long_int;
			break;
		default:
			printf("Unknown specifier: %s\n", specifier);
			return;
	}
	//------------------------------------------------------------------------
	int curr; //num of chars from last print
	int new_line; //track if new_line
	
	for(unsigned long int i = 0, j = 0; i < array_size; i++)
	{
		curr = 0;
		if (base_specifier[1] == 'x')
			curr += printf("0x");
		else if (base_specifier[1] == 'X')
			curr += printf("0X");
		curr += custom_print(specifier, array, i);  //custom_print is func pointer
		curr += printf(", ");
		j += curr;
		new_line = 0;
		if (j > max_chars_per_line) //will only trip when extra chars are written to stdout
		{
			i--; //need to reprint current index
			j = 0; //reset char counter for next line
			clear_chars(curr); //remove extra characters to avoid copies
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
			case 'X': case 'f': case 'F': case 'e': case 'E':
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
