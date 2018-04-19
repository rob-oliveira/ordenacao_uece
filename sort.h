#ifndef SORT2_H
#define SORT2_H
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
using namespace std;

int binary2dec(int bin);

int dec2binary(int dec, int tam);

int max(int *vet, int tam);

void radix_exc(int *vet, int tam, int base);

void exchange(int *vet, int tam, int base, int pos);

void radix_str(int *vet, int tam, int base);

void count_sort(int *vet, int tam);

void insertion(int *vet, int tam);

void bucket_sort(int *vet, int tam);

#endif // SORT2_H
