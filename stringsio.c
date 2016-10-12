#include "stringsio.h"
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
	memset(string, '\0', sizeof(char));
	scanf("%s", string);
	if (strlen(string) < 64) {
		for (size_t i = strlen(string); i <= 64; i++) {
			string[i] = '\0';
		}
	}
}

void StringInputTester(char *string)
{
	memset(string, '\0', sizeof(char));
	int n = 0;
	n = rand() % 64;
	for (int i = 0; i < n; i++) {
		string[i] = 33 + rand() % 93;
	}
	if (strlen(string) < 64) {
		for (size_t i = strlen(string); i <= 64; i++) {
			string[i] = '\0';
		}
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
