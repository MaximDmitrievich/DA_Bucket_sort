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

	Element **array = Data_create(5, 2);
	Data_insert(array, 10 * 1, 1, 1, 12, "ddd");
	Data_insert(array, 10 * 1, 2, 1, 120, "ddd");
	Data_insert(array, 10 * 1, 3, 1, 1238475478, "ddd");
	Data_insert(array, 10 * 1, 4, 1, 122309, "ddd");
	Data_insert(array, 10 * 1, 5, 1, 12238293, "ddd");
	Data_insert(array, 10 * 1, 1, 2, 12339239, "ddd");
	Data_insert(array, 10 * 1, 2, 2, 12233, "ddd");
	Data_insert(array, 10 * 1, 3, 2, 4829839, "ddd");
	Data_insert(array, 10 * 1, 4, 2, 99177748388, "ddd");
	Data_insert(array, 10 * 1, 5, 2, 474, "ddd");
	insert_sort(array, 5, 2);
	Data_print(array, 5, 2);
	Data_bucket_sort(array, 5, 1);
	Data_bucket_sort(array, 5, 2);
	Data_print(array, 5, 2);
	Data_destroy(array, 5, 2);
	return 0;
}
