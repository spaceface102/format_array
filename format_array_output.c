#include <stdio.h>
#include <ctype.h>

void format_array_output(void *array, int array_size, int type_size, int max_chars, char *specifier);

int main(void)
{
	char spec[] = "%d";
	printf("%s\n", spec);
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

}
