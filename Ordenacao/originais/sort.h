#ifndef SORT_H
#define SORT_H

void swap(int &vet, int i, int j);

void selection(int *vet, int tam);

void insertion(int *vet, int tam);

void bubble(int *vet, int tam);

void shell(int *vet, int tam);

void merge(int *vet, int tam);
void mergeSort(int *vet, int tam);

//void quick(int *vet, int tam);
//void quick(int *vet, int left, int right);

void heap(int *vet, int tam);

void quickBubble(int *vet, int tam, int k);
void quickBubble(int *vet, int left, int right, int k);


// devolve o índice do filho esquerdo no no de indice i
int filhoEsq(int i);
// devolve o indice do filho direito do no de indice i
int filhoDir(int i);
// efetua um push down no no de indice i
void pushDown(int i, int heap[], int tam);
// funcao para fazer a montagem da heap
void montaHeap(int heap[],int tam);
// funcao para fazer a desmontagem da heap
void desmontaHeap(int heap[],int tam);
// heapSort: funcao que ordena uma lista dada, chamando, em ordem,
// a rotina que monta a heap e a que efetua a desmontagem
void heapSort(int lista[],int tam);

int quick_dividir(int *vet, int ini, int fim, int pivot);
void quick_call(int *vet, int ini, int fim);
void quick_sort(int *vet, int tam);


int max(int *vet, int tam);	// encontra o maior valor contido em um array

///**Ordenacoes de ordem linear**///

void radix_exc(int *vet, int tam, int base);
//ordena os dados de um vetor apartir dos digitos de cada um dos seus elementos comecando da esquerda

void exchange(int *vet, int tam, int base, int pos);

void radix_str(int *vet, int tam, int base);

void count_sort(int *vet, int tam);

void insertion(int *vet, int tam);

void bucket_sort(int *vet, int tam);


#endif // SORT_H
