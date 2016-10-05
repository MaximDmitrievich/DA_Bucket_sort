#ifndef DATA_H
#define DATA_H
#include "strings.h"

typedef struct item {
	unsigned long long key;
	char *string;
	struct item *next;
	struct item *prev;
} TItem;

typedef struct list {
	TItem *head;
	int items;
} TList;

typedef struct vector {
	TList *lists;
	int avail;
	int occup;
} TVector;

TVector *VectorCreate();
void VectorInsert(TVector *vector, int idx, unsigned long long key, char *string);
void VectorPrint(TVector *vector);
void InsertSort(TList *list);
void BucketSort(TVector *vector);
void VectorDestroy(TVector **vector);

#endif
