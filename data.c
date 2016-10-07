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
			printf("%llu\t%s\n", vector->lists[i].head->key, vector->lists[i].head->string);
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
	if ((list->items < 2) && (list->head == NULL)) {
		return;
	}
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
	tmp = NULL;
	newhead = NULL;
}

void BucketSort(TVector *vector)
{
	if (vector->occup < 2) {
		return;
	}
	unsigned long long min = ULLONG_MAX;
	unsigned long long max = 0;
	for (int i = 0; i < vector->occup; i++) {
		if ((vector->lists[i].head != NULL) && (vector->lists[i].head->key < min)) {
			min = vector->lists[i].head->key;
		}
		if ((vector->lists[i].head != NULL) && (vector->lists[i].head->key > max)) {
			max = vector->lists[i].head->key;
		}
	}
	if (min == max) {
		return;
	}
	double range = max - min;
	int index = 0;
	TVector *buckets = VectorCreate();
	for (int i = 0; i < vector->occup; i++) {
		index = (int) vector->occup * (vector->lists[i].head->key / range);
		if (vector->lists[i].head != NULL) {
			VectorInsert(buckets, index, vector->lists[i].head->key, vector->lists[i].head->string);
		}
	}
	for (int i = 0; i < buckets->occup; i++) {
		if (buckets->lists[i].head != NULL) {
			InsertSort(&buckets->lists[i]);
		}
	}
	VectorDestroy(&vector);
	vector = VectorCreate();
	TItem *tmp = NULL;
	int k = 0;
	for (int i = 0; i < buckets->avail; i++) {
		tmp = buckets->lists[i].head;
		while (tmp != NULL) {
			VectorInsert(vector, k++, tmp->key, tmp->string);
			tmp = tmp->next;
		}
	}
	VectorDestroy(&buckets);
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
