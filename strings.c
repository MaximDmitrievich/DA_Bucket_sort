#include "strings.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

String *String_init()
{
    String *string = (String *) malloc(sizeof(String));
    if (string == NULL) {
        return NULL;
    }
    string->string_data = (char *) calloc(sizeof(char *), 64);
    if (string->string_data == NULL) {
        free(string);
        string = NULL;
        return NULL;
    }
    return string;
}
void String_input(String *string)
{
    char c = 0;
    if (string == NULL) {
        return;
    }
    if (string->string_data == NULL) {
        free(string);
        string = NULL;
        return;
    }
    for (int i = 0; i < 64; i++) {
        if (scanf("%c", &c) != ("\n" || " ")) {
            string->string_data[i] = c;
        }
        string->string_data[i] = 0;
    }
    string->string_data[63] = '\0';
}
char *String_return(String *string)
{
    char *string_out = (char *) malloc(sizeof(char *) * 64);
    if (string_out == NULL) {
        return NULL;
    }
    return strcpy(string->string_data, string_out);
}
void String_destroy(String *string)
{
    free(string->string_data);
    string->string_data = NULL;
    free(string);
    string = NULL;
}
