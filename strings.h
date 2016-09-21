#ifndef STRING_H
#define STRING_H

typedef struct string {
    char *string_data;
} String;

String *String_init();
void String_input(String *string);
char *String_return(String *string);
void String_destroy(String *string);

#endif
