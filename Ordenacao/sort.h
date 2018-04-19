#ifndef SORT2_H
#define SORT2_H
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

int binary2dec(int bin);

int dec2binary(int dec);

void radix_exc_10(int *vet, int tam);

void radix_exc_2(int *vet, int tam);

void radix_str_10(int *vet, int tam);

void radix_str_2(int *vet, int tam);

int max(int *vet, int tam);

void radix_exc(int *vet, int tam, int base);

void exchange(int *vet, int tam, int base, int pos);

void radix_str(int *vet, int tam, int base);

void insertion(int *vet, int tam);

void bucket_sort(int *vet, int tam);

void count_sort(int *vet, int tam);

void swap(int * vet, int i, int j);

int compare(const void *a, const void *b);

void heapInsertInEnd(int * vet, int * size, int x);

void heapReplaceTop(int * vet, int size, int x);

int replacementSelection(int * vet, int N, FILE * input, FILE * output);

int sortBlock(int *vet, int tam, FILE *input, FILE *output);

void writeOutput(FILE *file);

int merge(FILE *input1, FILE *input2, FILE *output);

void balancedmergeextsort(FILE *input, int tam, FILE *output);

void mergePoliphase(FILE * input1, FILE * input2, FILE * output);

void poliphaseMerge(FILE * input, int N, FILE *output);

#endif // SORT2_H
