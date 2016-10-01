#ifndef DATA_H
#define DATA_H
#include "strings.h"

typedef struct elem{
	unsigned long long key;
	char *string;
	struct elem *next;
	struct elem *prev;
	int elementsinlist;
} Element;

typedef struct vector{
	Element *elems;
	int occup;
	int avail;
} Vector;

Vector *VectorCreate();
void VectorInsert(Vector *vect, int idx, unsigned long long key, char *string);
int VectorSize(Vector *vect);
int VectorListSize(Vector *vect, int idx);
void VectorPrint(Vector *vect);
void InsertSort(Vector *vect, int idx);
void BucketSort(Vector *vect);
void VectorDestroy(Vector **vect);

#endif
