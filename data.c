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
	for (size_t jy = 0; jy < j; jy++) {
		for (size_t ix = 0; ix < i; ix++) {
			printf("%llu -- %s\n",elems[ix][jy].key, elems[ix][jy].string);
		}
	}
}

void insert_sort(Element **elems, size_t i, size_t idx)
{
	Element temp;
	for (size_t k = 0; k < i; k++) {
		temp = elems[k][idx];
		for (size_t j = k - 1; j >= 0; j--) {
			if (elems[k][idx].key < temp.key) {
				break;
			}
			elems[j + 1][idx] = elems[j][idx];
			elems[j][idx] = temp;
		}
	}
}

void Data_bucket_sort(Element **elems, size_t i, size_t j)
{
	size_t size_of_array = i * j;
	Element **tmp = elems;
	size_t idx = 1;
	Element **buckets = Data_create(size_of_array + 1, 10);
	for (size_t k = 1; k <= size_of_array; k++) {
		Data_insert(buckets, 10 * size_of_array, (tmp[k][0].key / ULLONG_MAX) * size_of_array, tmp[k][0].key, idx++, tmp[k][0].string);
	}
	for(size_t k = 1; k <= idx; k++) {
		insert_sort(buckets, size_of_array + 1, k);
	}
	for (size_t k = 1; k <= size_of_array + 1; k++) {
		for (size_t n = 1; n <= idx; n++) {
			if (buckets[n][k].string != NULL) {
				Data_insert(elems, i * j, k, n, buckets[k][n].key, buckets[k][n].string);
			}
		}
	}
	Data_destroy(tmp, i, j);
	Data_destroy(buckets, size_of_array + 1, idx);
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
