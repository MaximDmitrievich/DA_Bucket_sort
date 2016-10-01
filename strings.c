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
	for (int i = 0; i < 64; i++) {
		string[i] = 0;
	}
	char c = 0;
	int i = 0;
	while ((c = getchar()) != '\n' && i != 64) {
		string[i] = c;
		i++;
	}
}

char *StringCpy(char *string)
{
	char *tmp = (char *) calloc(sizeof(char), strlen(string) + 1);
	return strcpy(tmp, string);
}
void StringDestroy(char **string)
{
	free(*string);
	string = NULL;
}
