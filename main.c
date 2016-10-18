#include "stringsio.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
	TVector *vector = VectorCreate(0);
	char *string = StringCreate();
	unsigned long long key = 0;
	int idx = 0;
	while (scanf("%llu", &key) != EOF) {
		StringInput(string);
		VectorInsert(vector, idx, key, string);
		idx++;
	}
	BucketSort(vector);
	VectorPrint(vector);
	VectorDestroy(&vector);
	StringDestroy(&string);
	return 0;
}
