#include "sort.h"

int binary2dec(int bin){ 
	int tam;
	int i = 0;
	int value = 0;
	while(bin != 0){
		value += (int) (bin%10) * pow(2, i);
		bin/=10;
		i++;
		tam--;
	}
	return value;
}

int dec2binary(int dec, int tam){ //tam é o tamanho de string, que sera determinado de acordo com o maior entre os numeros
	int bin = 0;
	//bin[tam] = '\0';
	int i = 1;
	while(tam >= 0){
		bin += (dec % 2) * i;
		dec = floor(dec / 2);
		i*=10;
		tam--;
	}
	return bin;

}

int max(int *vet, int tam){
	int max = 0;
	for(int i = 0; i<tam; i++){
		if(vet[i] > max) max = vet[i];
	}
	return max;
}

void radix_exc(int *vet, int tam, int base){
	int pos, m;
	m = max(vet, tam);
	pos = floor(log(m)/log(base));
	exchange(vet, tam, base, pos); 
}

void exchange(int *vet, int tam, int base, int pos){
	if(pos >= 0 && tam > 0){
		int *count;
		int *tmp;	
		count = new int[base];
		tmp = new int[tam];
		int m, k, i, a;
		for(i = 0; i < base; i++) count[i] = 0;
		for(i = 0; i < tam; i++){
			a = ((int)(vet[i]/pow(base,pos))) % base;
			count[a]++;
		}
		for(i = 1; i < base; i++) count[i] += count[i-1];
		for(i = tam-1; i >= 0; i--){
			a = ((int)(vet[i]/pow(base,pos))) % base;
			count[a]--;
			tmp[count[a]] = vet[i];
		}
		for(i = 0; i<tam; i++) vet[i] = tmp[i];
		for(i = 0; i < base ; i++){
			if(i < base - 1) exchange( vet+count[i], count[i+1] - count[i], base, pos-1);
			else exchange( vet+count[i], tam - count[i], base, pos-1);
		}
		delete[] count;
		delete[] tmp;

	}

	
}

void radix_str(int *vet, int tam, int base){
	int *tmp;
	int *count;
	int i, m, npass, b, k, a;
	count = new int[base];
	tmp = new int[tam];
	m = max(vet,tam);
	npass = floor(log (m)/ log(base)) + 1;
	b = 1;
	k = 1;
	while(k <= npass){
		for(i = 0; i < base; i++) count[i] = 0;
		for(i = 0; i < tam; i++){
			a = (vet[i]/b) % base;
			count[a]++;
		}
		for(i = 1; i < base; i++) count[i] += count[i-1];
		for(i = tam-1; i >= 0; i--){
			a = (vet[i]/b) % base;
			count[a]--;
			tmp[count[a]] = vet[i];
		}
		for(i = 0; i<tam; i++) vet[i] = tmp[i];
		b*=base;
		k++;
	}
	delete[] tmp;
	delete[] count;
}

void count_sort(int *vet, int tam){
	int m, i, j, *count, *tmp, a;
	m = max(vet, tam);
	count = new int[m+1];
	tmp = new int[tam];
	for(i = 0; i <= m; i++) count[i] = 0;
	for(i = 0; i < tam; i++) count[vet[i]]++;
	for(i = 1; i <= m; i++) count[i]+=count[i-1];
	for(i = 0; i < tam; i++){
		a = vet[i];
		count[a]--;
		tmp[count[a]] = vet[i];
	}
	for(i = 0; i < tam; i++){
		vet[i] = tmp[i];
	}
	delete[] count;
	delete[] tmp;
	
	
}

void insertion(int *vet, int tam){
	if(tam > 0){	
		int i, j, comp;
		for(i = 1; i < tam; i++){//esse primeiro laco marca o elemento que sera inserido na parde ordenada
			comp = vet[i];	//o elemento é escolhido
			for(j = i - 1; j >= 0 && comp < vet[j]; j--){ //em seguida o elemento escolhido vai trocando de posicao con seu antecessores ate atingir a posicao correta
			    vet[j + 1] = vet[j];
			}
			vet[j + 1] = comp;
		 }
	}
}

void bucket_sort(int *vet, int tam){
	int m, i, j, k, *count, *tmp, a;
	m = max(vet, tam);
	k = floor(m/(tam-1))+1;
	count = new int[tam];
	tmp = new int[tam];
	for(i = 0; i < tam; i++) count[i] = 0;
	for(i = 0; i < tam; i++) count[vet[i]/k ]++;
	for(i = 1; i < tam; i++) count[i]+=count[i-1];
	for(i = 0; i < tam; i++){
		a = vet[i]/k;
		count[a]--;
		tmp[count[a]] = vet[i];
	}
	for(i = 0; i<tam; i++){
		if(i < tam - 1) insertion( tmp+count[i], count[i+1] - count[i]);
		else insertion( tmp+count[i], tam - count[i]);
	}
	for(i = 0; i < tam; i++){
		vet[i] = tmp[i];
	}
	delete[] count;
	delete[] tmp;
}























