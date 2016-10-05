#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
	TVector *vector = VectorCreate();
	char *string = StringCreate();
	unsigned long long key = 0;
	int idx = 0;
	while (scanf("%llu", &key) != EOF) {
		StringInput(string);
		VectorInsert(vector, idx++, key, string);
	}
	VectorInsert(vector, 3, 54, "string");
	VectorInsert(vector, 3, 36, "string");
	VectorInsert(vector, 3, 0, "string");
	VectorPrint(vector);
	InsertSort(&(vector->lists[3]));
	VectorPrint(vector);
	printf("\n");
	BucketSort(vector);
	VectorPrint(vector);
	VectorDestroy(&vector);
	StringDestroy(&string);
	return 0;
}
