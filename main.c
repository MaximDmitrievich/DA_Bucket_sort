#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *string = String_create();
	String_input(string);
	printf("%s\n", string);
	char *tmp = String_cpy(string);


	printf("%s\n", tmp);
	String_destroy(tmp);
	String_destroy(string);

	Element **array = Data_create(1, 1);
	Data_insert(array, 1 * 1, 1, 1, 12, "ddd");
	Data_print(array, 1, 1);
	Data_destroy(array);
	return 0;
}
