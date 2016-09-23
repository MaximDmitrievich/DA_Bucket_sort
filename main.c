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
	Data *data = Data_create(2, 1);
	Data_destroy(data);
	return 0;
}