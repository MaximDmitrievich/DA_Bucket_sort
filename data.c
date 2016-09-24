#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Element **Data_create(size_t i, size_t j)
{
	Element **elems = malloc(sizeof(Element *) * i);
	if (elems == NULL) {
		return NULL;
	}
	for (size_t k = 0; k < j; k++) {
		elems[k] = malloc(sizeof(Element) * j);
	}
	for (size_t k = 0; k < i; k++) {
		for (size_t n = 0; n < j; n++) {
			elems[k][n].key = 0;
			elems[k][n].string = String_create();
		}
	}
	return elems;
}
void Data_insert(Element **elems, size_t size, size_t i, size_t j, unsigned long long key, char *string)
{
	if (sizeof(Element) * size < sizeof(Element) * i * j) {
		elems = realloc(elems, sizeof(Element *) * i);
		for (size_t k = 0; k < i; k++) {
			elems[k] = realloc(elems[k], sizeof(Element) * j);
		}
	}
	elems[i - 1][j - 1].key = key;
	elems[i - 1][j - 1].string = String_cpy(string);

}
unsigned long long Data_key_return(Element **elems, size_t i, size_t j)
{
	return elems[i][j].key;
}
char *Data_string_return(Element **elems, size_t i, size_t j)
{
	return String_cpy(elems[i][j].string);
}
void Data_print(Element **elems, size_t i, size_t j)
{
	for (size_t ix = 0; ix < i; ix++) {
		for (size_t jy = 0; jy < j; jy++) {
			printf("%llu -- %s\n", Data_key_return(elems, ix, jy), Data_string_return(elems, ix, jy));
		}
	}
}
void Data_bucket_sort(Element **elems)
{

}
void Data_destroy(Element **elems)
{
	free(elems);
}
