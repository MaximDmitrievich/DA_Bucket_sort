#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *String_create()
{
	char *string = (char *) calloc(sizeof(char), 65);
	if (string == NULL) {
		return NULL;
	}
	string[64] = '\0';
	return string;
}
void String_input(char *string)
{
	char c = 0;
	int i = 0;
	while ((c = getchar()) != '\n' && i != 64) {
		string[i] = c;
		i++;
	}
}
char *String_cpy(char *string)
{
	char *tmp = (char *) calloc(sizeof(char), strlen(string) + 1);
	return strcpy(tmp, string);
}
void String_destroy(char *string)
{
	free(string);
}