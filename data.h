#ifndef DATA_H
#define DATA_H
#include "strings.h"
#include <string.h>

typedef struct elem {
	unsigned long long key;
	char *string;
} Element;


Element **Data_create(size_t i, size_t j);
void Data_insert(Element **elems, size_t size, size_t i, size_t j, unsigned long long key, char *string);
unsigned long long Data_key_return(Element **elems, size_t i, size_t j);
char *Data_string_return(Element **elems, size_t i, size_t j);
void Data_print(Element **elems, size_t i, size_t j);
void Data_bucket_sort(Element **elems, size_t i, size_t j);
void Data_destroy(Element **elems, size_t i, size_t j);

#endif
