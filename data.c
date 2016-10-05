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
		printf("\n------avail:%d\n", vector->avail);
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
	}
	if (vector->avail < idx) {
		vector->avail = idx;
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
	}
	if (vector->lists[idx].head == NULL) {
		vector->lists[idx].head = (TItem *) calloc(sizeof(TItem), 1);
		vector->lists[idx].head->key = key;
		vector->lists[idx].head->string = StringCpy(string);
		vector->lists[idx].head->next = NULL;
		printf("\n------Items:%d\n", vector->lists[idx].items);
		printf("\n------occup:%d\n", vector->occup);
		vector->lists[idx].items++;
		printf("\n------Items:%d\n", vector->lists[idx].items);
		vector->occup++;
		printf("\n------occup:%d\n", vector->occup);
	} else {
		TItem *tmp = vector->lists[idx].head;
		while (tmp != NULL) {
			tmp = tmp->next;
		}
		tmp = (TItem *) calloc(sizeof(TItem), 1);
		tmp->key = key;
		tmp->string = StringCpy(string);
		tmp->next = NULL;
		printf("\n------Items:%d\n", vector->lists[idx].items);
		vector->lists[idx].items++;
		printf("\n------Items:%d\n", vector->lists[idx].items);
	}
}

void VectorPrint(TVector *vector)
{
	for (int i = 0; i < vector->occup; i++) {
		if (vector->lists[i].head != NULL) {
			printf("%llu ", vector->lists[i].head->key);
			printf("%s\n", vector->lists[i].head->string);
			TItem *tmp = vector->lists[i].head;
			while (tmp->next != NULL) {
				tmp = tmp->next;
				printf("--%llu ", tmp->key);
				printf("%s\n", tmp->string);
			}
		}
	}
}

void InsertSort(TList *list)
{
	TItem *tmp = list->head;
	TItem *newhead = NULL;
	while (tmp != NULL) {
		TItem *node = tmp;
		tmp = tmp->next;
		if (newhead == NULL || node->key < newhead->key) {
			node->next = newhead;
			newhead = node;
		} else {
			TItem *current = newhead;
			while (current->next != NULL && !(node->key < current->next->key)) {
				current = current->next;
			}
			node->next = current->next;
			current->next = node;
		}
	}
	list->head = newhead;
}

void BucketSort(TVector *vector)
{
	int n = vector->occup;
	TVector *buckets = VectorCreate();
	for (int i = 0; i <= n; i++) {
		VectorInsert(buckets, (double) n * (vector->lists[i].head->key / ULLONG_MAX), vector->lists[i].head->key, vector->lists[i].head->string);
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
	for (int i = 0; i < (*vector)->occup; i++) {
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
