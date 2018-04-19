/*
 * quick.cpp
 *
 *  Created on: 16/11/2010
 *      Author: felipe

int quickDividir(int *vet, int ini, int fim, int pivot){
	int i = ini;
	int j = fim;
	while(i < j){
		while(vet[i] < pivot){
			i++;
		}
		while(vet[j] > pivot){
			j--;
		}
		//swap(vet, i, j);
		bool teste = (i < j) && (pivot == vet[i]) && (pivot == vet[j]);
		if(teste){
			i++;
		}
	}
	return i;
}

void quichCall(int *vet, int ini, int fim){
	int pv = vet[ini];
	int pi;
	if(ini < fim){
		pi = quickDividir(vet, ini , fim, pv);
		//quickCall(vet, ini, pi-1);
		//quickCall(vet, pi+1, fim);
	}
}

void quickSort(int *vet, int tam){

	//quickCall(vet, 0, tam-1);
}
*/
