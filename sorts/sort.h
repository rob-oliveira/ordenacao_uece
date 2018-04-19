#ifndef SORT_H
#define SORT_H

void swap(int &vet, int i, int j);

void selection(int *vet, int tam);

void insertion(int *vet, int tam);

void bubble(int *vet, int tam);

void shell(int *vet, int tam);

void merge(int *vet, int tam);
void mergeSort(int *vet, int tam);

void quick(int *vet, int tam);
void quick(int *vet, int left, int right);

void heap(int *vet, int tam);

void quickBubble(int *vet, int tam);
void quickBubble(int *vet, int left, int right);

#endif // SORT_H
