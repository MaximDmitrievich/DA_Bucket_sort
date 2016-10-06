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
	vector->avail = 8;
	vector->occup = 0;
	vector->lists = (TList *) malloc(sizeof(TList) * vector->avail);
	if (vector->lists == NULL) {
		free(vector);
		exit(EXIT_SUCCESS);
	}
	for (int i = 0; i < vector->avail; i++) {
		vector->lists[i].head = NULL;
		vector->lists[i].items = 0;
	}
	return vector;
}

void VectorInsert(TVector *vector, int idx, unsigned long long key, char *string)
{
	if (vector->avail == vector->occup) {
		vector->avail *= 2;
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
		for (int i = vector->occup; i < vector->avail; i++) {
			vector->lists[i].head = NULL;
			vector->lists[i].items = 0;
		}
	}
	if (vector->avail < idx) {
		while (vector->avail < idx) {
			vector->avail *= 2;
		}
		vector->lists = (TList *) realloc(vector->lists, sizeof(TList) * vector->avail);
		for (int i = vector->occup; i < vector->avail; i++) {
			vector->lists[i].head = NULL;
			vector->lists[i].items = 0;
		}
	}
	if (vector->lists[idx].head == NULL) {
		vector->lists[idx].head = (TItem *) malloc(sizeof(TItem));
		vector->lists[idx].head->key = key;
		vector->lists[idx].head->string = StringCpy(string);
		vector->lists[idx].head->next = NULL;
		vector->lists[idx].items++;
		vector->occup++;
	} else {
		TItem *tmp = vector->lists[idx].head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = (TItem *) malloc(sizeof(TItem));
		tmp->next->key = key;
		tmp->next->string = StringCpy(string);
		tmp->next->next = NULL;
		vector->lists[idx].items++;
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
				printf(" --%llu ", tmp->key);
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
	int idx = 0;
	TVector *buckets = VectorCreate();
	for (int i = 0; i < n; i++) {
		idx = (int) n * ((double)vector->lists[i].head->key / ULLONG_MAX);
		VectorInsert(buckets, idx, vector->lists[i].head->key, vector->lists[i].head->string);
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
