#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Element **Data_create(size_t i, size_t j)
{
	Element **elems = malloc(sizeof(Element *) * i);
	if (elems == NULL) {
		return NULL;
	}
	for (size_t k = 0; k < i; k++) {
		elems[k] = malloc(sizeof(Element) * j);
	}
	for (size_t k = 0; k < i; k++) {
		for (size_t n = 0; n < j; n++) {
			elems[k][n].key = 0;
			elems[k][n].string = NULL;
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
			printf("%llu -- %s\n", Data_key_return(elems, ix, jy), elems[ix][jy].string);
		}
	}
}

void Data_bucket_sort(Element **elems, size_t i, size_t j)
{
	if (i <= 2) {
		return;
	}
	unsigned long long max = 0;
	unsigned long long min = ULLONG_MAX;

	for (size_t ix = 0; ix < i; ix++) {
		for (size_t jy = 0; jy < j; jy++) {
			if (max < elems[ix][jy].key) {
				max = elems[ix][jy].key;
			}
		}
	}
	for (size_t ix = 0; ix < i; ix++) {
		for (size_t jy = 0; jy  j; jy++) {
			if (min > elems[ix][jy].key) {
				min = elems[ix][jy].key;
			}
		}
	}
	Element **bucket = Data_create(,);
	unsigned long long idx = 0;
	for (size_t ix = 0; ix < i; ix++) {
		for (size_t jy; jy < j; jy++) {
			index = (elems[ix][jy].key)
		}
	}
	Data_destroy(bucket, ,)


}
void Data_destroy(Element **elems, size_t i, size_t j)
{
	for (size_t ix = 0; ix < i; ix++) {
		for (size_t jy = 0; jy < j; jy++) {
			String_destroy(elems[ix][jy].string);
		}
	}
	for (size_t ix = 0; ix < i; ix++) {
		free(elems[ix]);
	}
	free(elems);
}
