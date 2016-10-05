#include "strings.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


TVector *VectorCreate()
{
	TVector *vector = (TVector *) malloc(sizeof(TVector));
	if (vector == NULL) {
		exit(EXIT_SUCCESS);
	}
	vector->avail = 4;
	vector->occup = 0;
	vector->lists = (TList *) calloc(sizeof(TList), vector->avail);
	if (vector->lists == NULL) {
		free(vector);
		exit(EXIT_SUCCESS);
	}
	return vector;
}

void VectorInsert(TVector *vector, int idx, unsigned long long key, char *string)
{
	if (vector->avail == vector->occup) {
		vector->avail *= 2;
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
	}
	if (vector->avail < idx) {
		vector->avail *= idx;
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
	}
	if (vector->lists[idx].head == NULL) {
		vector->lists[idx].head = (TItem *) calloc(sizeof(TItem), 1);
		vector->lists[idx].head->key = key;
		vector->lists[idx].head->string = StringCpy(string);
		vector->lists[idx].head->next = NULL;
		vector->lists[idx].head->prev = NULL;
		vector->lists[idx].items = 1;
		vector->occup++;
	} else {
		TItem *tmp = vector->lists[idx].head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = (TItem *) calloc(sizeof(TItem), 1);
		tmp->next->key = key;
		tmp->next->string = StringCpy(string);
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
		vector->lists[idx].items++;
	}
}

void VectorPrint(TVector *vector)
{
	for (int i = 0; i < vector->avail; i++) {
		if (vector->lists[i].head != NULL) {
			printf("%llu ", vector->lists[i].head->key);
			printf("%s\n", vector->lists[i].head->string);
			if (vector->lists[i].items > 0) {
				TItem *tmp = vector->lists[i].head;
				while (tmp->next != NULL) {
					tmp = tmp->next;
					printf(" -- %llu", tmp->key);
					printf(" %s\n",tmp->string);
				}
			}
		}
	}
}

void LstInsrt(TItem *a, TItem *b)
{
	b->prev = a->prev;
	b->next = a;
	a->prev = b;
	if (b->prev != NULL) {
		b->prev->next = b;
	}
}

TItem *Get(TItem *item)
{
	TItem *tmp = item;
	if (item->next != NULL) {
		item->next->prev = item->prev;
	}
	if(tmp->prev != NULL) {
		item->prev->next = item->next;
	}
	return tmp;
}

void InsertSort(TList *list)
{
	printf("GG\n");
	while (list->head->next != NULL) {
		if (list->head->next->key < list->head->key) {
			TItem *tmp = Get(list->head->next);
			while ((list->head->prev != NULL) && (tmp->key < list->head->key)) {
				list->head = list->head->prev;
			}
			LstInsrt(list->head, tmp);
		} else {
			list->head = list->head->next;
		}
	}
}

void BucketSort(TVector *vector)
{
	int n = vector->occup;
	TVector *buckets = VectorCreate();
	for (int i = 0; i <= n; i++) {
		VectorInsert(buckets, (vector->lists[i].head->key * n) / ULLONG_MAX, vector->lists[i].head->key, vector->lists[i].head->string);
	}
	for (int i = 0; i < n; i++) {
		if (buckets->lists[i].items > 1) {
			InsertSort(&(buckets->lists[i]));
		}
	}
	int k = 0;
	TVector *out = VectorCreate();
	for (int i = 0; i < n; i++) {
		TItem *tmp = buckets->lists[i].head;
		while (tmp != NULL) {
			VectorInsert(out, k++, tmp->key, tmp->string);
			tmp = tmp->next;
		}
	}
	VectorDestroy(&vector);
	vector = out;
	out = NULL;
}
void VectorDestroy(TVector **vector)
{
	TItem *tmp = NULL;
	for (int i = 0; i < (*vector)->avail; i++) {
		while ((*vector)->lists[i].head != NULL) {
			StringDestroy(&(*vector)->lists[i].head->string);
			tmp = (*vector)->lists[i].head;
			(*vector)->lists[i].head = tmp->next;
			free(tmp);
		}
	}
	free((*vector)->lists);
	free(*vector);
	*vector = NULL;
}
