#ifndef DATA_H
#define DATA_H
#include "strings.h"
#include <string.h>

typedef struct elem {
	unsigned long long key;
	char *string;
} Element;

typedef struct data {
	Element **elems;
	size_t i;
	size_t j;
} Data;

Data *Data_create(size_t i, size_t j);
void Data_insert(Data *data, size_t i, size_t j, unsigned long long key, char *string);
unsigned long long Data_key_return(Data *data, size_t i, size_t j);
char *Data_string_return(Data *data, size_t i, size_t j);
void Data_print(Data *data);
void Data_bucket_sort(Data *data);
void Data_destroy(Data *data);

#endif