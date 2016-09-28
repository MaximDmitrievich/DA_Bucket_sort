#ifndef DATA_H
#define DATA_H
#include "strings.h"
#include <string.h>

typedef struct elem {
	unsigned long long key;
	char *string;
} Element;


Element **Data_create(int i, int j);
void Data_insert(Element **elems, int size, int i, int j, unsigned long long key, char *string);
unsigned long long Data_key_return(Element **elems, int i, int j);
char *Data_string_return(Element **elems, int i, int j);
void Data_print(Element **elems, int i, int j);
void Data_bucket_sort(Element **elems, int i, int j);
void insert_sort(Element **elems, int i, int idx);
void Data_destroy(Element **elems, int i, int j);

#endif
