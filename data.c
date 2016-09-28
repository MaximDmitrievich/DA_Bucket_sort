#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Element **Data_create(int i, int j)
{
	Element **elems = malloc(sizeof(Element *) * i);
	if (elems == NULL) {
		return NULL;
	}
	for (int k = 0; k < i; k++) {
		elems[k] = malloc(sizeof(Element) * j);
	}
	for (int k = 0; k < i; k++) {
		for (int n = 0; n < j; n++) {
			elems[k][n].key = 0;
			elems[k][n].string = NULL;
		}
	}
	return elems;
}
void Data_insert(Element **elems, int size, int i, int j, unsigned long long key, char *string)
{
	if (sizeof(Element) * size < sizeof(Element) * i * j) {
		elems = realloc(elems, sizeof(Element *) * i);
		for (int k = 0; k < i; k++) {
			elems[k] = realloc(elems[k], sizeof(Element) * j);
		}
	}
	elems[i - 1][j - 1].key = key;
	elems[i - 1][j - 1].string = String_cpy(string);

}
unsigned long long Data_key_return(Element **elems, int i, int j)
{
	return elems[i][j].key;
}
char *Data_string_return(Element **elems, int i, int j)
{
	return String_cpy(elems[i][j].string);
}
void Data_print(Element **elems, int i, int j)
{
	for (int jy = 0; jy < j; jy++) {
		for (int ix = 0; ix < i; ix++) {
			printf("%llu -- %s\n",elems[ix][jy].key, elems[ix][jy].string);
		}
	}
}

void insert_sort(Element **elems, int i, int idx)
{
	Element temp;
	for (int k = 0; k < i; k++) {
		temp = elems[k][idx];
		for (int j = k - 1; j >= 0; j--) {
			if (elems[j][idx].key < temp.key) {
				break;
			}
			elems[j + 1][idx] = elems[j][idx];
			elems[j][idx] = temp;
		}
	}
}

void Data_bucket_sort(Element **elems, int i, int j)
{
	int size_of_array = i * j;
	Element **tmp = elems;
	int idx = 1;
	Element **buckets = Data_create(size_of_array + 1, 10);
	for (int k = 1; k <= size_of_array; k++) {
		Data_insert(buckets, 10 * size_of_array, (tmp[k][0].key / ULLONG_MAX) * size_of_array, tmp[k][0].key, idx++, tmp[k][0].string);
	}
	for(int k = 1; k <= idx; k++) {
		insert_sort(buckets, size_of_array + 1, k);
	}
	for (int k = 1; k <= size_of_array + 1; k++) {
		for (int n = 1; n <= idx; n++) {
			if (buckets[n][k].string != NULL) {
				Data_insert(elems, i * j, k, n, buckets[k][n].key, buckets[k][n].string);
			}
		}
	}
	Data_destroy(tmp, i, j);
	Data_destroy(buckets, size_of_array + 1, idx);
}

void Data_destroy(Element **elems, int i, int j)
{
	for (int ix = 0; ix < i; ix++) {
		for (int jy = 0; jy < j; jy++) {
			String_destroy(elems[ix][jy].string);
		}
	}
	for (int ix = 0; ix < i; ix++) {
		free(elems[ix]);
	}
	free(elems);
}
