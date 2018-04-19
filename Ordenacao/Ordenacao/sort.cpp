#include "sort.h"
//#include <iostream>


void swap(int *vet, int i, int j){
    int aux;
    aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void selection(int *vet, int tam){
    int i, j;
    for(i = 0; i < tam - 1; i++){
        for(j = i; j < tam; j++){
            if(vet[i] > vet[j])
                swap(vet, i, j);
        }
    }
}

void insertion(int *vet, int tam){
    int i, j, comp;
    for(i = 1; i < tam; i++){
        comp = vet[i];
        for(j = i - 1; j >= 0 && comp < vet[j]; j--){
            vet[j + 1] = vet[j];
        }
        vet[j + 1] = comp;
    }
}

void bubble(int *vet, int tam){
    int i, j;
    for(i = 0; i < tam - 1; i++){
        for(j = i; j < tam; j++){
            if(vet[i] > vet[j]){
                swap(vet, i, j);
            }
        }
    }
}

void shell(int *vet, int tam){
    int gap = 1;
    do{
        gap = 3*gap + 1;
    }while(gap < tam);
    do{
        gap /= 3;
        for(int i = gap; i < tam; i++){
            int value = vet[i];
            int j = i - gap;
            while(j >= 0 && value < vet[j]){
                vet[j + gap] = vet[j];
                j -= gap;
            }
            vet[j + gap] = value;
        }
    }while(gap > 1);
}

void merge(int *vet, int tam){
	int temp[tam];
	int meio = tam/2;
	int i =0, k = 0, j = meio;
	while(i < meio && j < tam){
		if(vet[i] < vet[j]){
			temp[k] = vet[i];
			i++;
		}
		else{
			temp[k] = vet[j];
			j++;
		}
		k++;
	}
	if(i == meio){
		while(j < tam){
			temp[k]= vet[j];
			j++; k++;
		}
	}
	else{
		while(i < meio){
			temp[k] = vet[i];
			i++; k++;
		}
	}
	for(i = 0; i < tam; i++){
		vet[i] = temp[i];
	}
	
}

void mergeSort(int *vet, int tam){
	if(tam > 1){
		int mid = tam/2;
		mergeSort(vet, mid);
		mergeSort(vet + mid, tam - mid);
		merge(vet, tam);
	}
}
/*
void quick(int *vet, int left, int right){
	int media = (left + right)/2;		// uma aproxiamção do elemento intermediario do vetor
	int l = left, r = right;
	do{
		while(vet[l] < vet[media] && l < right) l++;
		while(vet[r] > vet[media] && r > left) r--;
		
		if(l <= r){
			swap(vet, l, r);
			l++; r--;
		}
	}while(l <= r);
	if(left < r)	quick(vet, left, r);
	if(right > l)	quick(vet, l, right);
}

void quick(int *vet, int tam){
	quick(vet, 0, tam);
}
*/
void heap(int *vet, int tam){//a implementar...
	
}

void quickBubble(int *vet, int tam, int k){
	quickBubble(vet, 0, tam, k);
}
void quickBubble(int *vet, int left, int right, int k){
	if(left - right < k){
		bubble(&vet[left], right);
	}
	else{
		//quick(vet, left, right);
	}
}



// devolve o índice do filho esquerdo no no de indice i
int filhoEsq(int i) {
  return 2*i+1;
}

// devolve o indice do filho direito do no de indice i
int filhoDir(int i) {
  return 2*i+2;
}

// efetua um push down no no de indice i
void pushDown(int i, int heap[], int tam) {
  bool ha_esq = false;
  bool ha_dir = false;

  if(filhoEsq(i) < tam) ha_esq=true;
  if(filhoDir(i) < tam) ha_dir=true;

  if ( ha_esq && !ha_dir) {
    if (heap[i] < heap[filhoEsq(i)]) {
       swap(heap, filhoEsq(i), i);
       pushDown(filhoEsq(i), heap,tam);
    }
  }
  else
  if (ha_esq && ha_dir) {
    if ((heap[i] < heap[filhoEsq(i)]) || (heap[i] < heap[filhoDir(i)])) {
      if (heap[filhoEsq(i)] > heap[filhoDir(i)]) {
		swap(heap, filhoEsq(i), i);
		i = filhoEsq(i);
      }
      else {
		swap(heap, filhoDir(i), i);
		i = filhoDir(i);
      }
      pushDown(i,heap,tam);
    }
  }
}

// funcao para fazer a montagem da heap
void montaHeap(int heap[],int tam) {
  int i;
  for (i=tam-1; i >= 0; i--) {
    pushDown(i, heap, tam);
  }
}

// funcao para fazer a desmontagem da heap
void desmontaHeap(int heap[],int tam) {
  int i;
  int n = tam;
  for (i=0; i < n; i++) {
    swap(heap, 0, tam-1);
    tam--;
    pushDown(0,heap,tam);
  }
}

// heapSort: funcao que ordena uma lista dada, chamando, em ordem,
// a rotina que monta a heap e a que efetua a desmontagem
void heapSort(int lista[],int tam) {
  montaHeap(lista,tam);
  desmontaHeap(lista,tam);
}
int quick_dividir(int *vet, int ini, int fim, int pivot){
	int aux;
	int i = ini;
	int j = fim;
	while(i < j){
		while(vet[i] < pivot){
			i++;
		}
		while(vet[j] > pivot){
			j--;
		}
		aux = vet[i];
		vet[i] = vet[j];
		vet[j] = aux;
		bool teste = (i < j) && (pivot == vet[i]) && (pivot == vet[j]);
		if(teste){
			i++;
		}
	}
	return i;
}

void quick_call(int *vet, int ini, int fim){
	int pv = vet[ini];
	int pi;
	if(ini < fim){
		pi = quick_dividir(vet, ini , fim, pv);
		quick_call(vet, ini, pi-1);
		quick_call(vet, pi+1, fim);
	}
}

void quick_sort(int *vet, int tam){

	quick_call(vet, 0, tam-1);
}
