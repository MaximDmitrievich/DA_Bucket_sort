#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Data *Data_create(size_t i, size_t j)
{
	Data *data = (Data *) malloc(sizeof(Data));
	if (data == NULL) {
		return NULL;
	}
	data->i = i;
	data->j = j;
	Element **elems_tmp = malloc(sizeof(Element *) * data->i + sizeof(Element) * data->j * data->i);
	if (elems_tmp == NULL) {
		free(data);
		return NULL;
	}
	
	for (size_t k = 0; k < i; k++) {
		for (size_t n = 0; n < j; n++) {
			elems_tmp[k][n].key = 0;
			elems_tmp[k][n].string = String_create();
		}
	}
	memcpy(data->elems, elems_tmp, sizeof(Element *) * data->i + sizeof(Element) * data->j * data->i);
	return data;
}
void Data_insert(Data *data, size_t i, size_t j, unsigned long long key, char *string)
{

}
unsigned long long Data_key_return(Data *data, size_t i, size_t j)
{
	return data->elems[i][j].key;
}
char *Data_string_return(Data *data, size_t i, size_t j)
{
	return String_cpy(data->elems[i][j].string);
}
void Data_print(Data *data)
{
	for (size_t i = 0; i < data->i; i++) {
		for (size_t j = 0; j < data->j; j++) {
			printf("%llu -- %s", Data_key_return(data, i, j), Data_string_return(data, i, j));
		}
	}
}
void Data_bucket_sort(Data *data)
{

}
void Data_destroy(Data *data)
{
	free(data->elems);
	free(data);
}