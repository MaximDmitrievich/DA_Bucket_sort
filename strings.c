#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *StringCreate()
{
	char *string = (char *) calloc(sizeof(char), 65);
	if (string == NULL) {
		return NULL;
	}
	string[64] = '\0';
	return string;
}
void StringInput(char *string)
{
	scanf("%s", string);
	if (strlen(string) < 64) {
		for (size_t i = strlen(string); i <= 64; i++) {
			string[i] = '\0';
		}
	}
}

char *StringCpy(char *string)
{
	char *tmp = (char *) calloc(sizeof(char), strlen(string));
	return strcpy(tmp, string);
}
void StringDestroy(char **string)
{
	free(*string);
	string = NULL;
}
