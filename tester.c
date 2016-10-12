#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc < 2) {
        fprintf(stderr, "BAD USAGE:NO INPUT FILE!\n");
        exit(EXIT_SUCCESS);
    }
    unsigned long long key = 1;
    char *string = StringCreate();
    FILE *output = fopen(argv[1], "w");
    if (output == NULL) {
        fprintf(stderr, "FILE DIDN'T OPEN!\n");
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < 500; i++) {
        key = rand();
        StringInputTester(string);
        fprintf(output, "%llu\t%s\r\n", key, string);
    }
    fclose(output);
    StringDestroy(&string);
    return 0;
}
