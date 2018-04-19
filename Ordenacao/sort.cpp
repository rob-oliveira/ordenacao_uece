#include "sort.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>
int binary2dec(int bin){ //converte de binario pra decimal
	int i = 0;
	int value = 0;
	while(bin != 0){ //o laco continua ate o numero em binario zerar
		value += (int) (bin%10) * pow(2, i);
		bin/=10;
		i++;
	}
	return value;
}

int dec2binary(int dec){
	int bin = 0;
	int tam = floor(log(dec)/log(2)); // tamanho mede quantas casa o numero em binario vai ter
	int i = 1;
	while(tam >= 0){ //o laco ocorre ate percorrer todas as casas do numero em binário
		bin += (dec % 2) * i;
		dec = floor(dec / 2);
		i*=10;
		tam--;
	}
	return bin;

}

void radix_exc_10(int *vet, int tam){ // chama o radix exchange com a base 10, sem converter os numeros do vetor
	radix_exc(vet, tam, 10); 
}

void radix_exc_2(int *vet, int tam){ // converte o vetor inteiro para binario, chama o radix exchange na base 2 e converte de volta
	for(int i = 0; i < tam; i++){
		vet[i] = dec2binary(vet[i]);
	}
	radix_exc(vet, tam, 2);
	for(int i = 0; i < tam; i++){
		vet[i] = binary2dec(vet[i]);
	}
}

void radix_str_10(int *vet, int tam){ // chama o radix straight com a base 10, sem converter os numeros do vetor
	radix_exc(vet, tam, 10);
}

void radix_str_2(int *vet, int tam){ // converte o vetor inteiro para binario, chama o radix straight na base 2 e converte de volta
	for(int i = 0; i < tam; i++){
		vet[i] = dec2binary(vet[i]);
	}
	radix_str(vet, tam, 2);
	for(int i = 0; i < tam; i++){
		vet[i] = binary2dec(vet[i]);
	}
}

int max(int *vet, int tam){ // retorna o maior valor do vetor
	int max = 0;
	for(int i = 0; i<tam; i++){
		if(vet[i] > max) max = vet[i];
	}
	return max;
}

void radix_exc(int *vet, int tam, int base){ //chama o primeiro radix exchange, ja que este eh recursivo
	int pos, m;
	m = max(vet, tam); // descobre o maior valor do vetor
	pos = floor(log(m)/log(base)); // mete o tamanho do maior valor do vetor
	exchange(vet, tam, base, pos); 
}

void exchange(int *vet, int tam, int base, int pos){// pos se refere a posicao de algorismos verificada na rodada 
	if(pos >= 0 && tam > 1){ //mede se a posicao no numero binario chegou a zero e tambem se ha mais de um valor para ser ordenado 
		int *count;
		int *tmp;	
		count = new int[base]; // contador que mede ate onde vai cada intervalo
		tmp = new int[tam]; // vetor temporario
		int m, k, i, a;
		for(i = 0; i < base; i++) count[i] = 0; // zera todo o vetor contador
		for(i = 0; i < tam; i++){ //faz com que cada celula do contador guarde a quantidade de valores daquele intervalo 
			a = ((int)(vet[i]/pow(base,pos))) % base; // pega o vet[i] e descobre em qual posição do contador ele deve ficar
			count[a]++; // faz com que o contador guarde que tem mais um valor ali 
		}
		for(i = 1; i < base; i++) count[i] += count[i-1]; // os indices do contador acumulam os valores anteriores
		for(i = tam-1; i >= 0; i--){
			a = ((int)(vet[i]/pow(base,pos))) % base;// pega o vet[i] e descobre em qual posição do contador ele deve ficar
			count[a]--;// diminui um valor naquela posição do contador
			tmp[count[a]] = vet[i]; // agora tmp[count[a]] é um local onde esse numero pode ficar
		} //quando esse laco termina todos os valores estao ordenados da esquerda ate pos no vetor temporario
		for(i = 0; i < tam; i++) vet[i] = tmp[i]; // copia de volta para o vetor original
		for(i = 0; i < base ; i++){ // chama o exchange base vezes para ordenar a direita de pos 
			if(i < base - 1) exchange( vet+count[i], count[i+1] - count[i], base, pos-1);
			else exchange( vet+count[i], tam - count[i], base, pos-1); // ocorre separado das outras do laco pare evitar o erro
		}//observe que a quantidade de vezes que o excharge ehh chamado eh igual a base, se por exemplo for binario ele é chamado so 2 vezes 
		delete[] count;
		delete[] tmp; // libera as alocacoes

	}

	
}

void radix_str(int *vet, int tam, int base){
	int *tmp;
	int *count;
	int i, m, npass, b, k, a;
	count = new int[base]; // contador que mede ate onde vai cada intervalo
	tmp = new int[tam]; // vetor temporario
	m = max(vet,tam); // descobre o maior valor do vetor
	npass = floor(log (m)/ log(base)) + 1; // mede a quantidade de algorismos do maior
	b = 1;
	k = 1;
	while(k <= npass){ // o laco ocorre a mesma quantidade de vezes do maior numero
		for(i = 0; i < base; i++) count[i] = 0; // zera todo o vetor contador
		for(i = 0; i < tam; i++){ // faz com que cada celula do contador guarde a quantidade de valores daquele intervalo 
			a = (vet[i]/b) % base; // pega o vet[i] e descobre em qual posição do contador ele deve ficar
			count[a]++; // faz com que o contador guarde que tem mais um valor ali 
		}
		for(i = 1; i < base; i++) count[i] += count[i-1]; // os indices do contador acumulam os valores anteriores
		for(i = tam-1; i >= 0; i--){
			a = (vet[i]/b) % base; // pega o vet[i] e descobre em qual posição do contador ele deve ficar
			count[a]--; // diminui um valor naquela posição do contador
			tmp[count[a]] = vet[i]; // agora tmp[count[a]] é um local onde esse numero pode ficar
		} // quando esse laco termina todos os valores estao ordenados da direita ate pos no vetor temporario
		for(i = 0; i<tam; i++) vet[i] = tmp[i]; // copia de volta para o vetor original
		b*=base; // b guarda o valor para ser usado na hora de descubrir aposicao de vet[i]
		k++; // avanca o algorismo, da esquesda pra direita
	}
	delete[] tmp;
	delete[] count;
}


void insertion(int *vet, int tam){ //usado pra ordenar os valores dentro de cada bucket
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
	m = max(vet, tam); // descobre o maior valor do vetor
	k = floor(m/(tam-1))+1; // k guarda o valor usado para descobir em que bucket vet[i] sera guardado
	count = new int[tam]; // a quantidade de buckets eh igual ao valor total do vetor
	tmp = new int[tam];
	for(i = 0; i < tam; i++) count[i] = 0; // zera todo o vetor contador
	for(i = 0; i < tam; i++) count[vet[i]/k ]++; // pega o vet[i] e descobre em qual posição do contador ele deve ficar e faz com que o contador guarde que tem mais um valor ali 
	for(i = 1; i < tam; i++) count[i]+=count[i-1]; // os indices do contador acumulam os valores anteriores
	for(i = 0; i < tam; i++){
		a = vet[i]/k; // pega o vet[i] e descobre em qual posição do contador ele deve ficar
		count[a]--; // diminui um valor naquela posição do contador
		tmp[count[a]] = vet[i]; // agora tmp[count[a]] é um local onde esse numero pode ficar
	} // agora no tmp, cada bucket quardas os valores referentes ao seu intervalo
	for(i = 0; i<tam; i++){
		if(i < tam - 1) insertion( tmp+count[i], count[i+1] - count[i]); // ordena os valores dentro do bucket
		else insertion( tmp+count[i], tam - count[i]); // ocorre separado das outras do laco pare evitar o erro
	}
	for(i = 0; i < tam; i++){ // copia do tmp para o original
		vet[i] = tmp[i];
	}
	delete[] count;
	delete[] tmp;
}

void count_sort(int *vet, int tam){ // o count eh parecido com o bucket, porem nesse caso o intervalo do bucket eh um
	int m, i, j, *count, *tmp, a;
	m = max(vet, tam);
	count = new int[m+1]; // o vetor count eh do tamanho do maior numero do vetor
	tmp = new int[tam];
	for(i = 0; i <= m; i++) count[i] = 0; // zera todo o vetor contador
	for(i = 0; i < tam; i++) count[vet[i]]++; // pega o vet[i] e descobre em qual posição do contador ele deve ficar e faz com que o contador guarde que tem mais um valor ali 
	for(i = 1; i <= m; i++) count[i]+=count[i-1]; // os indices do contador acumulam os valores anteriores
	for(i = 0; i < tam; i++){
		a = vet[i]; // pega o vet[i] e descobre em qual posição do contador ele deve ficar
		count[a]--; // diminui um valor naquela posição do contador
		tmp[count[a]] = vet[i];// agora tmp[count[a]] é um local onde esse numero pode ficar
	}
	for(i = 0; i < tam; i++){
		vet[i] = tmp[i]; //copia de volta pro original
	}
	delete[] count;
	delete[] tmp;
	
	
}

///////////////////////////////////////////////// inicio da  ordenação externa:

int compare(const void *a, const void *b){ // função usada no qsort
	return( *(int*)a - *(int*)b );
}

/*heap sort*/

void swap(int * vet, int i, int j) { //função de troca
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}


int sortBlock(int * vet, int N, FILE * input, FILE * output) { // essa funçao ordena um bloco do input e joga no output usando o qsort
	int i = 0, aux = -1;
	while (i < N && fscanf(input, "%d", &vet[i]) != EOF) {
		i++;
	}

	if (i > 0) {
		qsort(vet, i, sizeof(int), compare);
		fwrite(vet, sizeof(int), i, output);
		fwrite(&aux, sizeof(int), 1, output);
	}
	if (i < N)
		return 0;
	else
		return 1;
}


void writeOutput(FILE *file, FILE *output){
	int x;
	printf("Escrevendo a saida.\n");
	rewind(file);
	while (fread(&x, sizeof(int), 1, file))
		if(x!=-1)
			fprintf(output, "%d\n", x);
}


int merge(FILE * input1, FILE * input2, FILE * output) {
	int x1 = -1, x2 = -1, aux = -1;
	fread(&x1, sizeof(int), 1, input1);
	fread(&x2, sizeof(int), 1, input2);
	if (x1 == -1 && x2 == -1)
		return 0;// fim dos dois arquivos
	while (x1 != -1 || x2 != -1) {
		if (x1 < x2) {
			if (x1 != -1)
				fwrite(&x1, sizeof(int), 1, output);
			if (fread(&x1, sizeof(int), 1, input1) == EOF || x1 == -1) {//fim do bloco 1
				do {
					fwrite(&x2, sizeof(int), 1, output);
					if (x2 == -1)
						break;
				} while (fread(&x2, sizeof(int), 1, input2) != EOF);
			}
		} else {
			if (x2 != -1)
				fwrite(&x2, sizeof(int), 1, output);
			if (fread(&x2, sizeof(int), 1, input2) == EOF || x2 == -1) {//fim do bloco 2
				do {
					fwrite(&x1, sizeof(int), 1, output);
					if (x1 == -1)
						break;
				} while (fread(&x1, sizeof(int), 1, input1) != EOF);
			}
		}
	}
	return 1;
}

void balancedmergeextsort(FILE *input, int tam, FILE *output){
	FILE *a1, *a2, *b1, *b2;
	int count =  0;
	int *vet = (int*) malloc(sizeof(int) * tam);
	a1 = fopen("a1.dat", "w+b");
	a2 = fopen("a2.dat", "w+b");
	b1 = fopen("b1.dat", "w+b");
	b2 = fopen("b2.dat", "w+b");
	printf("aki!!");
	while(1){
		if(sortBlock(vet, tam, input, a1) == 0) break;
		count++;
		if(sortBlock(vet, tam, input, a2) == 0) break;
		count++;
	}
	free(vet);
	while(1){
		count = 0;
		rewind(a1);
		rewind(a2);
		while(1){
			if(merge(a1,a2,b1) == 0) break;
			count++;
			if(merge(a1,a2,b2) == 0) break;
			count++;
		}
		a1 = freopen("a1.dat", "w+b", a1);
		a2 = freopen("a2.dat", "w+b", a2);
		if(count == 1){
			writeOutput(b1, output);
			b1 = freopen("b1.dat", "w+b", b1);
			break;
		}
		count = 0;
		rewind(b1);
		rewind(b2);
		while(1){
			if(merge(b1, b2, a1) == 0) break;
			count++;
			if(merge(b1, b2, a2) == 0) break;
			count++;
		}
		b1 = freopen("b1.dat", "w+b", b1);
		b2 = freopen("b2.dat", "w+b", b2);
		if(count == 1){
			writeOutput(a1, output);
			a1 = freopen("a1.dat", "w+b", a1);
			break;
		}
	}
	fclose(a1);
	fclose(a2);
	fclose(b1);
	fclose(b2);
}

void mergePoliphase(FILE * input1, FILE * input2, FILE * output) {
	int x1 = -1, x2 = -1, aux = -1;
	fread(&x1, sizeof(int), 1, input1);
	fread(&x2, sizeof(int), 1, input2);
	while (x1 != -1 || x2 != -1) {
		if (x1 < x2) {
			if (x1 != -1)
				fwrite(&x1, sizeof(int), 1, output);
			if (fread(&x1, sizeof(int), 1, input1) == EOF || x1 == -1) {//fim do bloco 1
				do {
					fwrite(&x2, sizeof(int), 1, output);
					if (x2 == -1)
						break;
				} while (fread(&x2, sizeof(int), 1, input2) != EOF);
				break;
			}
		} else {
			if (x2 != -1)
				fwrite(&x2, sizeof(int), 1, output);
			if (fread(&x2, sizeof(int), 1, input2) == EOF || x2 == -1) {//fim do bloco 2
				do {
					fwrite(&x1, sizeof(int), 1, output);
					if (x1 == -1)
						break;
				} while (fread(&x1, sizeof(int), 1, input1) != EOF);
				break;
			}
		}
	}
}

void poliphaseMerge(FILE * input, int N,  FILE *output) {
	FILE * a, *b, *c;
	int contA = 0, contB = 0, contC = 0, i;
	int fib1, fib2;
	int * vet = (int *) malloc(sizeof(int) * N);
	if ((a = fopen("a.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	if ((b = fopen("b.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	if ((c = fopen("c.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	printf("criando blocos em A ...  ");
	while (1) {
		contA++;
		if (sortBlock(vet, N, input, a) == 0)
			break;

		contB++;
		if (sortBlock(vet, N, input, b) == 0)
			break;
	}
	free(vet);
	rewind(a);
	rewind(b);
	printf("%d blocos criados.%d em A e %d em B\n", contA + contB, contA, contB);
	while (contA + contB + contC > 1) {
		if (contA == 0) {
			printf("B:%d + C:%d -> A...\n", contB, contC);
			do {
				mergePoliphase(b, c, a);
				contA++;
				if (contB > 0)
					contB--;
				if (contC > 0)
					contC--;
			} while (contB > 0 && contC > 0);
			rewind(a);
			if (contB == 0)
				b = freopen("b.dat", "w+b", b);
			if (contC == 0)
				c = freopen("c.dat", "w+b", c);
		}

		if (contB == 0) {
			printf("A:%d + C:%d -> B...\n", contA, contC);
			do {
				mergePoliphase(a, c, b);
				contB++;
				if (contA > 0)
					contA--;
				if (contC > 0)
					contC--;
			} while (contA > 0 && contC > 0);
			rewind(b);
			if (contA == 0)
				a = freopen("a.dat", "w+b", a);
			if (contC == 0)
				c = freopen("c.dat", "w+b", c);
		}

		if (contC == 0) {
			printf("A:%d + B:%d -> C...\n", contA, contB);
			do {
				mergePoliphase(a, b, c);
				contC++;
				if (contB > 0)
					contB--;
				if (contA > 0)
					contA--;
			} while (contA > 0 && contB > 0);
			rewind(c);
			if (contA == 0)
				a = freopen("a.dat", "w+b", a);
			if (contB == 0)
				b = freopen("b.dat", "w+b", b);
		}

	}
	if (contA == 1) {
		writeOutput(a, output);
		a = freopen("a.dat", "w+b", a);
	} else if (contB == 1) {
		writeOutput(b, output);
		b = freopen("b.dat", "w+b", b);
	} else if (contC == 1) {
		writeOutput(c, output);
		c = freopen("c.dat", "w+b", c);
	}

	fclose(a);
	fclose(b);
	fclose(c);
}

////////////////////////////////////////////////////////////////////////////



