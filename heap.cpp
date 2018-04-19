/*
 * heap.cpp
 *
 *  Created on: 16/11/2010
 *      Author: felipe



// devolve o índice do filho esquerdo no no de indice i
int filhoEsq(int i) {
  return 2*i+1;
}

// devolve o indice do filho direito do no de indice i
int filhoDir(int i) {
  return 2*i+2;
}

// efetua um push down no no de indice i
void pushDown(int i,int heap[],int tam) {
  bool ha_esq = false;
  bool ha_dir = true;

  if(filhoEsq(i) < tam) ha_esq=true;
  if(filhoDir(i) < tam) ha_dir=true;

  if ( ha_esq && !ha_dir) {
    if (heap[i] < heap[filhoEsq(i)]) {
       swap(heap, filhoEsq(i), i);
       pushDown(filhoEsq(i), heap,tam);
    }
  }
  else
  if (ha_esq&&ha_dir) {
    if ((heap[i]<heap[filhoEsq(i)])||(heap[i]<heap[filhoDir(i)])) {
      if (heap[filhoEsq(i)]>heap[filhoDir(i)]) {
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
  for (i = tam-1;i >= 0;i--){
    pushDown(i,heap,tam);
  }
}

// funcao para fazer a desmontagem da heap
void desmontaHeap(int heap[],int tam){
  int i;
  int n = tam;
  for (i = 0; i < n; i++){
    swap(heap, 0, tam - 1);
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
*/
