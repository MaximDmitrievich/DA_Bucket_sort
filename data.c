#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Vector *VectorCreate()
{
	Vector *vect = (Vector *) malloc(sizeof(Vector));
	if (vect == NULL) {
		exit(EXIT_SUCCESS);
	}
	vect->occup = 0;
	vect->avail = 16;
	vect->elems = (Element *) malloc(sizeof(Element) * vect->avail);
	for (int i = 0; i < vect->avail; i++) {
		vect->elems[i].string = NULL;
		vect->elems[i].key = 0;
		vect->elems[i].elementsinlist = 0;
		vect->elems[i].next = NULL;
		vect->elems[i].prev = NULL;
	}
	return vect;
}
void VectorInsert(Vector *vect, int idx, unsigned long long key, char *string)
{
	if (vect->avail == vect->occup) {
		vect->avail *= 2;
		vect->elems = (Element *) realloc(vect->elems, sizeof(Element) * vect->avail);
	}
	if (vect->avail < idx) {
		vect->avail = idx + 1;
		vect->elems = (Element *) realloc(vect->elems, sizeof(Element) * vect->avail);
	}
	if (vect->elems[idx].string == NULL) {
		vect->elems[idx].string = StringCpy(string);
		vect->elems[idx].key = key;
		vect->elems[idx].elementsinlist++;
		vect->elems[idx].next = NULL;
		vect->elems[idx].prev = NULL;
		vect->occup++;
	} else {
		if (vect->elems[idx].next == NULL) {
			vect->elems[idx].next = (Element *) malloc(sizeof(Element));
			(vect->elems[idx].next)->prev = NULL;
			(vect->elems[idx].next)->string = StringCpy(string);
			(vect->elems[idx].next)->key = key;
			vect->elems[idx].elementsinlist++;
		} else {
			Element *temp = &(vect->elems[idx]);
			Element *tempprev = NULL;
			while (temp->next != NULL) {
				tempprev = temp;
				temp = temp->next;
				temp->prev = tempprev;
			}
			temp->next = (Element *) malloc(sizeof(Element));
			temp->next->string = StringCpy(string);
			temp->next->key = key;
			temp->next->next = NULL;
			temp->prev = tempprev;
			vect->elems[idx].elementsinlist++;
		}
	}

}
int VectorSize(Vector *vect)
{
	return vect->occup;
}
int VectorListSize(Vector *vect, int idx)
{
	return vect->elems[idx].elementsinlist;
}
void VectorPrint(Vector *vect)
{
	for (int i = 0; i < vect->occup; i++) {
		printf("%llu ", vect->elems[i].key);
		printf("%s\n", vect->elems[i].string);
		if (vect->elems[i].elementsinlist > 0) {
			Element *temp = &(vect->elems[i]);
			while (temp->next != NULL) {
				temp = temp->next;
				printf(" %llu ", temp->key);
				printf("%s\n", temp->string);
			}
		}
	}
}
void InsertSort(Vector *vect, int idx)
{

}
void BucketSort(Vector *vect)
{

}
void VectorDestroy(Vector **vect)
{
	for (int i = 0; i < (*vect)->avail; i++) {
		if ((*vect)->elems[i].elementsinlist > 0) {
			Element *temp = NULL;
			while ((*vect)->elems[i].next != NULL) {
				temp = (*vect)->elems[i].next;
				(*vect)->elems[i].next = temp->next;
				free(temp);
			}
		}
		StringDestroy(&(*vect)->elems[i].string);
	}
	free((*vect)->elems);
	free(*vect);
	*vect = NULL;
}
