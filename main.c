#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
	char *string = StringCreate();
	Vector *vector = VectorCreate();
	unsigned long long key = 0;
	for (int i = 0; i < 5; i++) {
		scanf("%llu", &key);
		StringInput(string);
		VectorInsert(vector, i, key, string);
	}
	VectorInsert(vector, 1, key, string);
	printf("%d\n", VectorSize(vector));
	printf("%d\n", VectorListSize(vector, 1));
	StringDestroy(&string);
	VectorPrint(vector);
	VectorDestroy(&vector);
	return 0;
}
