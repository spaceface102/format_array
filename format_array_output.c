#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

void clear_chars(int number);
void repeat(char c, int number);
void format_array_output(void *array, int array_size, int type_size, int max_chars, char *specifier);

int main(void)
{
	char spec[] = "%d";
	printf(spec, 42);
}

void format_array_output(void *array, int array_size, int type_size, int max_chars, char *specifier)
{
	/*void pointer for array, to accept any type of array
	array_size necessary to ONLY access memory related to
	specific array, where each element is of type_size 
	bytes, aka == sizeof(array_type), and max_chars denotes
	max_chars per line. The character specifier is a string
	directly corresponding to the built in printf specifiers
	such as %d, %c, etc.*/
	
	//initial check, since code depends heavily on value of specifier
	if (specifier[0] != '%')
	{
		printf("Please provide a standard specifier such as %%d, %%f, %%lf, etc!\n");
		return;
	}

	//------------------------------------------------------------------------
	int prev; //num of chars from last print
	int new_line; //track if new_line
	int spec_len = strlen(specifier);
	
	//second specifier check
	if (spec_len <= 1)
	{
		printf("Please make sure to provide more than just %% as specifier!!!\n");
		return;
	}
	//------------------------------------------------------------------------

	for(int i = 0, j = 0; i < array_size; i++)
	{
		//------------------------------------------------------------------------
		//derefrence pointer correctly based on the specifier!
		switch(specifier[1]) //already check specifier[0] && strlen
		{
			case 'd': case 'i':
				prev = printf(specifier, ((int *)array)[i]);
				break;
			case 'u': 
				prev = printf(specifier, ((unsigned int *)array)[i]);
				break;
			case 'o': case 'x': case 'X':
				if (type_size == 4) //4 bytes 32 bits
					prev = printf(specifier, ((uint32_t *)array)[i]);
				else if (type_size == 8) //8 bytes 64 bits
					prev = printf(specifier, ((uint64_t *)array)[i]);
				else if (type_size == 1) //1 bytes 8 bits
					prev = printf(specifier, ((uint8_t *)array)[i]);
				else if (type_size == 2) //2 bytes 16 bits
					prev = printf(specifier, ((uint16_t *)array)[i]);
				break;
			case 'f':
				prev = printf(specifier, ((float *)array)[i]);
				break;
			case 'F': //I will be treating this as double
				prev = printf(specifier, ((double *)array)[i]);
				break;
			case 'l':
				if(spec_len == 3)
				{
					switch(specifier[2])
					{
						case 'f':
							prev = printf(specifier, ((double *)array)[i]);
							break;
						case 'd': case 'i':
							prev = printf(specifier, ((long int *)array)[i]);
							break;
						case 'u': case 'o': case 'x': case 'X':
							prev = printf(specifier, ((unsigned long int*)array)[i]);
							break;
						case 'l':
							prev = printf(specifier, ((long long int *)array)[i]);
							break;
					}
				}
				else if (spec_len == 4)
				{
					switch(specifier[3])
					{
						case 'u': case 'o': case 'x': case 'X':
							prev = printf(specifier, ((unsigned long long int *)array)[i]);
							break;
					}
				}
				else //spec_len == 2
					prev = printf(specifier, ((long int *)array)[i]);
				break;
			case 'h':
				if(spec_len == 3) 
				{
					switch(specifier[2])
					{
						case 'd': case 'i':
							prev = printf(specifier, ((short int *)array)[i]);
							break;
						case 'u': case 'o': case 'x': case 'X':
							prev = printf(specifier, ((unsigned short int *)array)[i]);
							break;
					}
				}
				break;
			case 'c':
				prev = printf(specifier, ((char *)array)[i]);
				break;	
			default:
				printf("Unknown specifier: %s\n", specifier);
				return;
		}
		//------------------------------------------------------------------------

		prev += printf(", ");
		j += prev;
		new_line = 0;
		if (j > max_chars) //will only trip when extra chars are written to stdout
		{
			i--; //need to reprint current index
			j = 0; //reset char counter for next line
			clear_chars(prev);
			new_line = printf("\n"); //will cause stdout flush and also new line!
		}
	}
	//final clean up
	if(!new_line)
	{
		clear_chars(2); //remove final ", " they are extra and should be removed
		printf("\n");
	}
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
