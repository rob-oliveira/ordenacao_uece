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

void heap(int *vet, int tam){//a implementar...
	
}

void quickBubble(int *vet, int tam){
	quickBubble(vet, 0, tam);
}
void quickBubble(int *vet, int left, int right){
	if(left - right < 10){
		bubble(&vet[left], right);
	}
	else{
		quick(vet, left, right);
	}
}