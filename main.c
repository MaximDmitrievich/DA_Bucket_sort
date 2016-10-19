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
	TVector *out = BucketSort(vector);
	if (out == NULL) {
	    VectorPrint(vector);
	    VectorDestroy(&vector);
    } else {
        VectorPrint(out);
	    VectorDestroy(&out);
    }
	StringDestroy(&string);
	return 0;
}
