#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;

class node{		//vectorun eleman tipi
	public:
		string Name;
		string Class;
		string Rarity;
		string Set;
		string Type;
		int Cost;
		node();
		~node();
		//node& operator=(const node&);		//vectorun i�inde zaten = operatoru tan�ml�ym�� ��renince yoru msat�r� yapt�m
};

class CardManager{
	public:
		vector<node*> new_vector;
		int line_number;		//dosyan�n sat�r uzunlu�unu tutuyor
		int fullorfilter;		//full m� filter m� istendi�ine g�re int de�er tutuyor 1 veya 2
		int iorm;		//bir �st sat�r gibi ayn� �ekilde insertion sort mu merge sortmu istendi�ine g�re int de�er tutuyor
		CardManager();
		~CardManager();
		int read_file(char**);		//dosya okuma fonksiyonu
		int write_file(char**);		//dosyaya yazma fonksiyonu
		void fullSort();
		void filterSort();
		void insertionSort();
		void mergeSort(int, int);	
		void merge(int, int, int);		
};

/*node& node::operator=(const node& z){		//vector i�in = overload� ama zaten vectorun kendisinin varm��
	Name = z.Name;
	Class = z.Class;
	Rarity = z.Rarity;
	Set = z.Set;
	Type = z.Type;
	Cost = z.Cost;
}*/

node::node(){
	
}

node::~node(){
	
}

CardManager::CardManager(){
	line_number = 0;
}

CardManager::~CardManager(){
	
}

int CardManager::read_file(char** filename){
	ifstream file(*filename);

	if (file.is_open() == false){		//dosya a��lmama hatas�
		cout << "File Error" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number say�s� sat�rdaki ka��nc� kelimede oldu�umuzu tutuyor ve buna g�re o stringi do�ru yere kaydediyorum
		string line;		//sat�rlar� bu stringe okuyorum
	
		while(getline(file, line)){		//sat�r� al�yorum
			stringstream stream(line);
			string word;
			node* temp = new node;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		//al�nan sat�rdan taba kadar kelimeyi al�p ge�ici node u ma kaydediyorum
					temp->Name = word;
				}
				else if(word_number == 2){
					getline(stream, word, '\t');
					temp->Class = word;
				}
				else if(word_number == 3){
					getline(stream, word, '\t');
					temp->Rarity = word;
				}
				else if(word_number == 4){
					getline(stream, word, '\t');
					temp->Set = word;
				}
				else if(word_number == 5){
					getline(stream, word, '\t');
					temp->Type = word;
				}
				else{
					getline(stream, word);
					temp->Cost = atoi(word.c_str());		//cost verisini int haline �evirip kaydediyorum
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					new_vector.push_back(temp);		//node lar tamamland�k�a vector ume pushluyorum
					break;
				}
			}		
			line_number++;
		}
		file.close();
		return 1;
	}
}

int CardManager::write_file(char** filename){
	ofstream output(*filename);
	if(!output){
		cout << "File Writing Error" << endl;		//dosya a��lmama hatas�
		return 0;
	}
	else{
		for(int i = 0; i < line_number; i++){		//her �zelli�i tek tek yaz�yorum ve sat�r atl�yorum
			output << new_vector[i]->Name << '\t' << new_vector[i]->Class << '\t' << new_vector[i]->Rarity << '\t' << new_vector[i]->Set << '\t' << new_vector[i]->Type << '\t' << new_vector[i]->Cost << endl;
		}
	}
	output.close();
}

void CardManager::fullSort(){
	if(iorm == 1)		//istenenin insertion sort mu merge sort mu oldu�unu tutan veriye g�re do�ru fonksiyonu �a��r�yorum
		insertionSort();
	else if(iorm == 2)
		mergeSort(0, line_number-1);
}

void CardManager::filterSort(){
	if(iorm == 1)		//yukar�daki fullsort da yap�lan�n ayn�s� yap�lmakta
		insertionSort();
	else if(iorm == 2)
		mergeSort(0, line_number-1);
}

void CardManager::insertionSort(){
	node* temp;
	if(fullorfilter == 1){		//full mu filter m� istendi�ini tutan veriye g�re bu if e veya altta else ine giriyoruz ve buras� fullsort k�sm�
		for(int i = 0; i < line_number; i++){
			int j = i;
			for(; j >= 1; j--){		//i sat�r say�s�na kadar ilerliyor ve j de i den ba�lay�p geri gelerek gerekirse yer de�i�tiriyor
				if (strcmp(new_vector[j]->Class.c_str(), new_vector[j-1]->Class.c_str()) < 0){
					temp = new_vector[j];
					new_vector[j] = new_vector[j-1];
					new_vector[j-1] = temp;
				}
				else if (strcmp(new_vector[j]->Class.c_str(), new_vector[j-1]->Class.c_str()) == 0){		//class k�sm� ayn�sa costa bak�yoruz
					if (new_vector[j]->Cost < new_vector[j - 1]->Cost){
						temp = new_vector[j];
						new_vector[j] = new_vector[j-1];
						new_vector[j-1] = temp;
					}
					else if (new_vector[j]->Cost == new_vector[j - 1]->Cost){		//cost k�sm� da ayn�ysa name e bak�yoruz
						if (strcmp(new_vector[j]->Name.c_str(), new_vector[j-1]->Name.c_str()) < 0){
							temp = new_vector[j];
							new_vector[j] = new_vector[j-1];
							new_vector[j-1] = temp;
						}
						else j = 0;
					}
					else j = 0;
				}
				else j = 0;
			}
		}
	}
	else{
		for(int i = 0; i < line_number; i++){
			int j = i;
			for(; j >= 1; j--){
				if (strcmp(new_vector[j]->Type.c_str(), new_vector[j-1]->Type.c_str()) < 0){		//buras� da filtersort k�zm� sadece type bak�yoruz
					temp = new_vector[j];
					new_vector[j] = new_vector[j-1];
					new_vector[j-1] = temp;
				}
			}
		}
	}	
}

void CardManager::mergeSort(int first, int last){
	int middle = (first + last)/2; 
	if(first < last){
		mergeSort(first, middle);		//tek eleman kalana kadar recursive olarak yar�ya b�l�p b�l�p yeniden �a��r�yoruz
		mergeSort(middle+1, last);		//yar�ya b�lerken yeni array olu�turmay�p yer israf� yapmay�p sadece indisleri yolluyoruz vectoru yollamasakda eri�imimiz oldu�u i�in sadece indisler yeterli
		merge(first, middle, last);		//elimizdeki par�alar� birle�tirmek i�in bu fonksiyona yolluyoruz
	}
}

void CardManager::merge(int first, int middle, int last){
	node* temp_array[last-first+1];		//s�ralanm�� halini tutmak i�in ge�ici node tipinde array olu�turuyoruz.
	int i = first;
	int j = middle + 1;		//i ilk yar�n�n ba�lang�c� j de ikinci yar�n�n ba�lang�c�
	int k = 0;		//k ge�ici arrayin iteratoru
	if(fullorfilter == 1){		//fullsort k�sm�
		while(i <= middle && j <= last){		//birinci veya ikinci yar� sona ula�ana kadar devam edecek
			if (strcmp(new_vector[i]->Class.c_str(), new_vector[j]->Class.c_str()) < 0){		//fullsortun gerektirdi�i gibi s�ral�yoruz burda insertion sorttaki gibi
				temp_array[k] = new_vector[i];
				k++;
				i++;
			}
			else if (strcmp(new_vector[i]->Class.c_str(), new_vector[j]->Class.c_str()) == 0){
				if (new_vector[i]->Cost < new_vector[j]->Cost){
					temp_array[k] = new_vector[i];
					k++;
					i++;
				}
				else if (new_vector[i]->Cost == new_vector[j]->Cost){
					if (strcmp(new_vector[i]->Name.c_str(), new_vector[j]->Name.c_str()) < 0){
						temp_array[k] = new_vector[i];
						k++;
						i++;
					}
					else{
						temp_array[k] = new_vector[j];
						k++;
						j++;
					}
				}
				else{
					temp_array[k] = new_vector[j];
					k++;
					j++;
				}
			}
			else{
				temp_array[k] = new_vector[j];
				k++;
				j++;
			}
		}
	}
	else{
		while(i <= middle && j <= last){		//buras� da filter sort k�sm�
			if (strcmp(new_vector[i]->Type.c_str(), new_vector[j]->Type.c_str()) < 0){
				temp_array[k] = new_vector[i];
				k++;
				i++;
			}
			else{
				temp_array[k] = new_vector[j];
				k++;
				j++;
			}
		}
	}
	
	if(i > middle){		//full yada filter sorttaki herhangi birinin while � bitti�inde yani 1. veya 2. yar� bitti�inde kalan k�sm� direk burada kopyal�yoruz
		for(;j <= last; j++){
			temp_array[k] = new_vector[j];
			k++;
		}
	}
	else{
		for(;i <= middle; i++){
			temp_array[k] = new_vector[i];
			k++;
		}
	}
		
	k = 0;
	for(i = first; i <= last; i++){		//ge�ici arrayimizi vectorun ayn� b�lgesine kopyal�yoruz
		new_vector[i] = temp_array[k];
		k++;
	}
}

#endif
