#include "sort.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <sys/time.h>
#include <cmath>

using namespace std;

void initialize(double *vet, int tam){
	for(int i = 0; i < tam; i++)
		vet[i] = 0;
}

int main(){
	//ofstream nada("nada");
	DIR *dir;
	struct dirent *entry;
	
	dir = opendir("/home/lapaq/Documentos/Ordenacao/files");
	if(dir == 0) cout<< "erro ao entrar no diretorio\n\n";


	ofstream randomTime("randomTime.txt"), semiCresTime("semiCrestime.txt"), semiDecTime("semiDecTime.txt");
		double random[5];
		initialize(random, 5);
		double semi_dec[5];
		initialize(semi_dec, 5);
		double semi_cre[5];
		initialize(semi_cre, 5);
	while((entry = readdir(dir))){ // inicio do laco principal
///**********bloco de abertura do arquivo de entrada*******///
		string filename(entry->d_name);
		filename = "/home/lapaq/Documentos/Ordenacao/files/" + filename; 
		cout<<filename<<endl;
		//ifstream fin;
		char *incstr = new char[filename.size() + 1];
		strcpy(incstr, filename.c_str());
		FILE *fin = fopen(incstr, "r");
		delete[] incstr;
		if(fin == 0) {
			cout << "\n erro no arquivo \n";
			continue;
		
		}

///********bloco de abertura do arquivo de saida**************///
		string filenameout(entry->d_name);
		filenameout += "out.txt";
		char *outcstr = new char[filenameout.size() + 1];
		strcpy(outcstr, filenameout.c_str());
		FILE *fout = fopen(outcstr, "w");
		
		if(fout == 0){
			cout <<outcstr<<endl;
			exit(1);
		}
		delete[] outcstr;
///*****************************************///
		
		string sub;
		int size = filename.size() - 2;
		int pos = 0;
		for(int i = 0; i < size; i++){
			if((filename[i] == '1') || filename[i] == '2' || filename[i] == '4' || filename[i] == '8') break;
			else pos++;
		}
		sub = filename.substr(pos, size - pos);
		
		char *cstr = new char[sub.size() + 1];
		strcpy(cstr, sub.c_str());
		int tam = atoi(cstr);
		delete[] cstr;
		
		int vet[tam];
		for(int i = 0; i < tam && !feof(fin); i++){
			fread(&vet[i], sizeof(int), 1, fin);
		}

//****************************************************//	
		struct timeval time;
		long double t1, t2, total; 
			
		gettimeofday(&time, NULL);
		t1 = (long double)(time.tv_sec + time.tv_usec/1e6);
		//quick_sort(vet, tam);
		//count_sort(vet, tam);
		//bucket_sort(vet, tam);
		radix_exc(vet, tam, 10);
		//radix_str(vet, tam, 10);
		//poliphaseMerge(fin, 1000, fout)	;	
		//balancedmergeextsort(fin, 50, fout);
		gettimeofday(&time, NULL);
		t2 = (long double)(time.tv_sec + time.tv_usec/1e6);
		total = t2 - t1;

///************************************************///

		
		int found = filename.find("random");
		if(found != string::npos){

			if(tam == 1000){
				random[0] += total;
			}
			else if(tam == 2000){
				random[1] += total;
			}
			else if(tam == 4000){
				random[2] += total;
			}
			else if(tam == 8000){
				random[3] += total;
			}
			else if(tam == 16000){
				random[4] += total;
			}
			
		}
		found = filename.find("Cres");
		if(found != string::npos){
			if(tam == 1000){
				semi_cre[0] += total;
			}
			else if(tam == 2000){
				semi_cre[1] += total;
			}
			else if(tam == 4000){
				semi_cre[2] = total; 
			}
			else if(tam == 8000){
				semi_cre[3] += total;
			}
			else if(tam == 16000){
				semi_cre[4] += total; 
			}
		}
		
		found = filename.find("Dec");
		if(found != string::npos){
			if(tam == 1000){
				semi_dec[0] += total;
			}
			else if(tam == 2000){
				semi_dec[1] += total;
			}
			else if(tam == 4000){
				semi_dec[2] = total; 
			}
			else if(tam == 8000){
				semi_dec[3] += total;
			}
			else if(tam == 16000){
				semi_dec[4] += total; 
			}
		}
		
		for(int i = 0; i < tam; i++){
			fscanf(fout, "%d\n",&vet[i]);	// saida em arquivo
			//cout<<vet[i]<<endl; // saida em terminal
		}
		total *= 1000;
		fscanf(fout,"arquivo ordenado pelo algoritmo balanced merge sort tempo da ordenação = %Lf milissegundos\n\n",&total);
		fclose(fout);
		fclose(fin);
			
	}
	
	for(int i = 0; i < 5; i++){
		random[i] *= 100; semi_cre[i] *= 200; semi_dec[i] /= 10;
		randomTime <<pow(2,i)*1000<<"   "<< random[i] << endl;
		semiCresTime << pow(2,i)*1000 <<"   "<< semi_cre[i] << endl;
		semiDecTime << pow(2,i)*1000 <<"   "<< semi_dec[i] << endl;
	}


	
}		
		

