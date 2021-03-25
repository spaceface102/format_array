#include <stdio.h>
#include <ctype.h>
#include <string.h>

void clear_chars(int number);
void repeat(char c, int number);
void format_array_output(void *array, int array_size, int max_chars, char *specifier);

int main(void)
{
	char spec[] = "%d";
	printf(spec, 42);
}

void format_array_output(void *array, int array_size, int max_chars, char *specifier)
{
	/*void pointer for array, to accept any type of array
	array_size necessary to ONLY access memory related to
	specific array, where each element is of type_size 
	bytes, aka == sizeof(array_type), and max_chars denotes
	max_chars per line. The character specifier is a string
	directly corresponding to the built in printf specifiers
	such as %d, %c, etc.*/
	
	if (specifier[0] != '%')
	{
		printf("Please provide a standard specifier such as %%d, %%f, %%lf, etc!\n");
		return;
	}

	int prev; //num of chars from last print
	int new_line; //track if new_line
	int spec_len = strlen(specifier);

	if (spec_len <= 1)
	{
		printf("Please make sure to provide more than just %% as specifier!!!\n");
		return;
	}

	for(int i = 0, j = 0; i < array_size; i++)
	{
		//derefrence pointer correctly based on the specifier!
		switch(specifier[1]) //already check specifier[0] && strlen
		{
			case 'd': case 'i':
				prev = printf(specifier, ((int *)array)[i]);
				break;
			case 'f':
				prev = printf(specifier, ((float *)array)[i]);
				break;
			case 'l':
				if(spec_len == 3 && specifier[2] == 'f')
					prev = printf(specifier, ((double *)array)[i]);
				break;
			case 'u': 
				prev = printf(specifier, ((unsigned int *)array)[i]);
				break;
			case 'h':
				if(spec_len == 2)
					prev = printf(specifier, ((short int *)array)[i]);
				else if (spec_len == 3 && specifier[2] == 'u') 
					prev = printf(specifier, ((short int *)array)[i]);
				break;
			case 'c':
				prev = printf(specifier, ((char *)array)[i]);
				
			default:
				printf("Unknown specifier: %s\n", specifier);
				return;
		}

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
