#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void Bucket_sort(Data *data)
{
    if (data->occup <= 2) {
        return;
    }
    int idx = 0;
    unsigned long long dig = 0;
    size_t n = data->occup;
    Data *bucket = Data_create(10, n + 1);
    for (size_t i = 1; i <= 10000000000000000000; i *= 10) {
        for (size_t j = 0; j < n + 1; j++) {
            dig = (data->elements[i].key / i) % 10;
            Data_insert(bucket, dig, bucket->elements[dig + n].key++, data->elements[i].key, data->elements[i].string);
        }
        for (size_t k = 0; k < 10; k++) {
            for (size_t m = 0; m < bucket->elements[k + n].key; m++) {
                Data_insert(data, idx++, 1, bucket->elements[k + m].key, bucket->elements[k + m].string);
            }
        }
    }
    Data_destroy(bucket);
}

int main(void)
{
    unsigned long long key = 0;
    String *string = String_init();
    Data *data = Data_create(16, 1);
    while (scanf("%d", key) != 0) {
        size_t k = 0;
        String_input(string);
        Data_insert(data, k, 1, key, string);
        k++;
    }
    Bucket_sort(data);
    Data_print(data);
    Data_destroy(data);
    String_destroy(string);
    return 0;
}
