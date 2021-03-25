#include <stdio.h>
#include <ctype.h>

void clear_chars(int number)
void repeat(char c, int number)
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

	int prev; //num of chars from last print
	for(int i = 0, j = 0; i < array_size; i++)
	{
		prev = printf(specifier, *(array+(i*type_size))) + printf(", ");
		j += prev;
		if (j > max_chars)
		{
			i--; //need to reprint current index
			j = 0; //reset char counter for next line
			clear_chars(prev);
			printf("\n");
		}
	}
	clear_chars(2); //remove final ", "
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
