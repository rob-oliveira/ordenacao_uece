#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

char merge(FILE * input1, FILE * input2, FILE * output) {
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

char sortBlock(int * vet, int N, FILE * input, FILE * output) {
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

void swap(int * vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

void heapInsertInEnd(int * vet, int * size, int x) {
	int i;
	i = *size;
	vet[i]=x;
	while (i > 0) {
		if (vet[i] < vet[(i - 1) / 2]) {
			swap(vet, i, (i - 1) / 2);
			i = (i - 1) / 2;
		} else
			break;
	}
	(*size)++;
}

void heapReplaceTop(int * vet, int size, int x) {
	int i = 0;
	vet[0] = x;
	while (i * 2 + 1 < size) {
		if (i * 2 + 2 < size) {
			if (vet[i * 2 + 2] < vet[i] && vet[i * 2 + 2] <= vet[i * 2 + 1]) {
				swap(vet, i, i * 2 + 2);
				i = i * 2 + 2;
			} else if (vet[i * 2 + 1] < vet[i] && vet[i * 2 + 1] < vet[i * 2+ 2]) {
				swap(vet, i, i * 2 + 1);
				i = i * 2 + 1;
			} else
				break;
		} else {
			if (vet[i * 2 + 1] < vet[i]) {
				swap(vet, i, i * 2 + 1);
				i = i * 2 + 1;
			} else
				break;
		}
	}
}
/*heap sort*/
char replacementSelection(int * vet, int N, FILE * input, FILE * output) {
	static int size = 0;
	int aux = -1, x=-1;
	while (size < N && fscanf(input, "%d", &x) != EOF) {//fill heap
		heapInsertInEnd(vet, &size,x);
	}

	while (size > 0) {
		x = -1;
		if (fscanf(input, "%d", &x) == EOF)
			break;
		if (x > vet[0]) {//replace
			fwrite(vet, sizeof(int), 1, output);
			heapReplaceTop(vet, size, x);
		} else
			break;

	}
	while (size > 0) {//empty heap
		fwrite(vet, sizeof(int), 1, output);
		size--;
		heapReplaceTop(vet, size, vet[size]);
	}

	fwrite(&aux, sizeof(int), 1, output);

	if (x == -1)
		return 0;
	else{
		size = 1;
		vet[0]= x;
		return 1;
	}
}

void writeOutput(FILE * file) {
	FILE *output;
	int x;
	printf("Escrevendo a saida.\n");
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	rewind(file);
	while (fread(&x, sizeof(int), 1, file))
		fprintf(output, "%d\n", x);
	fclose(output);
}

void balancedMultwayMerge(FILE * input, int N) {
	FILE * a1, *a2, *b1, *b2;
	int cont = 1;
	int * vet = (int *) malloc(sizeof(int) * N);

	if ((a1 = fopen("a1.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	if ((a2 = fopen("a2.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	if ((b1 = fopen("b1.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	if ((b2 = fopen("b2.dat", "w+b")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}

	printf("criando blocos em A ...  ");
	cont = 0;
	if (1)//usar fila de prioridades
		while (1) {
			if (replacementSelection(vet, N, input, a1) == 0)
				break;
			cont++;
			if (replacementSelection(vet, N, input, a2) == 0)
				break;
			cont++;
		}
	else//usar quicksort
		while (1) {
			if (sortBlock(vet, N, input, a1) == 0)
				break;
			cont++;
			if (sortBlock(vet, N, input, a2) == 0)
				break;
			cont++;
		}
	printf("%d blocos criados.\n", cont);
	free(vet);
	while (1) {
		cont = 0;
		rewind(a1);
		rewind(a2);
		while (1) {
			if (merge(a1, a2, b1) == 0)
				break;
			cont++;
			if (merge(a1, a2, b2) == 0)
				break;
			cont++;
		}
		printf("merge A -> B ; blocos: %d\n", cont);
		a1 = freopen("a1.dat", "w+b", a1);
		a2 = freopen("a2.dat", "w+b", a2);
		if (cont == 1) {
			writeOutput(b1);
			b1 = freopen("b1.dat", "w+b", b1);
			break;
		}
		cont = 0;
		rewind(b1);
		rewind(b2);
		while (1) {
			if (merge(b1, b2, a1) == 0)
				break;
			cont++;
			if (merge(b1, b2, a2) == 0)
				break;
			cont++;
		}
		printf("merge B -> A ; blocos: %d\n", cont);
		b1 = freopen("b1.dat", "w+b", b1);
		b2 = freopen("b2.dat", "w+b", b2);
		if (cont == 1) {
			writeOutput(a1);
			a1 = freopen("a1.dat", "w+b", a1);
			break;
		}
	}
	fclose(a1);
	fclose(a2);
	fclose(b1);
	fclose(b2);
}

int main() {
	FILE *input;
	int i;

	if ((input = fopen("toy.txt", "r")) == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	//for(i=0; i < 100000000;i++) fprintf(pa,"%d\n",rand()%INT_MAX);
	balancedMultwayMerge(input, 2);

	fclose(input);
	return 0;
}
