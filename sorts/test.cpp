#include "sort.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <sys/time.h>

using namespace std;

int main(){
	DIR *dir;
	struct dirent *entry;
	
	dir = opendir("G:\\Ordenação\\sorts\\files");
	if(dir == 0) cout<< "erro\n\n";
	
	while((entry = readdir(dir))){
		string filename(entry->d_name);
		filename = "G:\\Ordenação\\sorts\\files\\" + filename; 
		cout<<filename;
		ifstream fin;
		char *incstr = new char[filename.size() + 1];
		strcpy(incstr, filename.c_str());
		fin.open(incstr, ifstream::in);
		delete[] incstr;
		if(!fin.is_open()) {
			cout << "erro no arquivo\n\n";
			continue;
			//exit(1);
		}
		string filenameout(entry->d_name);
		filenameout += "out.txt";
		char *outcstr = new char[filenameout.size() + 1];
		strcpy(outcstr, filenameout.c_str());
		ofstream fout;
		fout.open(outcstr);
		delete[] outcstr;
		
		string sub;
		int size = filename.size() - 2;
		int pos = 0;
		for(int i = 0; i < size; i++){
			if((filename[i] == '1') || filename[i] == '2' || filename[i] == '4' || filename[i] == '8') break;
			else pos++;
		}
		sub = filename.substr(pos, size - pos);
		//cout<<"  "<<sub<<endl;
		char *cstr = new char[sub.size() + 1];
		strcpy(cstr, sub.c_str());
		int tam = atoi(cstr);
		delete[] cstr;
		
		int vet[tam];
		for(int i = 0; i < tam && !fin.eof(); i++){
			fin>> vet[i];
		}
		
		struct timeval time;
		double t1, t2, total = 0; 
		//int cont = 0;
		gettimeofday(&time, NULL);
		t1 = (double)(time.tv_sec + time.tv_usec/1e6);
		quick(vet, tam);
		gettimeofday(&time, NULL);
		t2 = (double)(time.tv_sec + time.tv_usec/1e6);
		total = t2 - t1;
		for(int i = 0; i < tam; i++){
			fout<<vet[i]<<endl;
			cout<<vet[i]<<endl;
		}
		fout<<"arquivo ordenado pelo algoritmo quicksort tempo da ordenação = "<< total*1000<<" milisegundos\n\n";
	}
	system("pause>0");
}
