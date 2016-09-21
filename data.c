#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "strings.h"

Data *Data_create(size_t i, size_t j)
{
    Data *data = (Data *) malloc(sizeof(Data));
    if (data == NULL) {
        return NULL;
    }
    data->elements = (Element *) malloc(sizeof(Element) * i * j);
    data->i = i;
    data->j = j;
    if (data->elements == NULL) {
        free(data);
        data = NULL;
        return NULL;
    }
    for (size_t x = 0; x < i; x++) {
        for (size_t y = 0; y < j; y++) {
            data->elements[x + y].string = NULL;
            data->elements[x + y].key = 0;
        }
    }
    data->avail = i * j;
    data->occup = 0;
    return data;
}
void Data_insert(Data *data, size_t i, size_t j, unsigned long long key, String *string)
{
    if (data->avail == data->occup || i > data->i || j > data->j) {
        data->elements = (Element *) realloc(data->elements, i * j);
        data->avail = i * j;
        data->i = i;
        data->j = j;
    }
    data->elements[i + j].key = key;
    data->elements[i + j].string->string_data = String_return(string);
}
void Data_print(Data *data)
{
    for (size_t x = 0; x < data->i; x++) {
        for (size_t y = 0; y < data->j; y++) {
            printf("%llu %s", data->elements[x + y].key, data->elements[x + y].string->string_data);
        }
    }
}
void Data_destroy(Data *data)
{
    for (size_t x = 0; x < data->i; x++) {
        for (size_t y = 0; y < data->j; y++) {
            String_destroy(data->elements[x + y].string);
            data->elements[x + y].string = NULL;
        }
    }
    free(data->elements);
    data->elements = NULL;
    free(data);
    data = NULL;
}
