#include "sort.h"

int main(){
	/*
	int valor;
	//valor = "hello world!!";
	int b;
	cin>>b;
	int tam = floor(log (b)/ log(2)) + 1;
	valor = dec2binary(b, 8);
	cout << valor << endl;
	int dec = binary2dec(valor);
	cout<< dec<<endl;
	*/
	int teste[5];
	for(int i = 0; i<5; i++){
	cin>>teste[i];
	}
	count_sort(teste, 5);
	for(int i = 0; i<5; i++){
		cout<<endl<<teste[i]<<endl;
	}
	return 0;
}
