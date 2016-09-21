#ifndef DATA_H
#define DATA_H
#include "strings.h"
#include <string.h>

typedef struct element {
    unsigned long long key;
    String *string;
} Element;

typedef struct data {
    Element *elements;
    size_t i;
    size_t j;
    size_t occup;
    size_t avail;
} Data;

Data *Data_create(size_t i, size_t j);
void Data_insert(Data *data, size_t i, size_t j, unsigned long long key, String *string);
void Data_print(Data *data);
void Data_destroy(Data *data);

#endif
