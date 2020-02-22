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
		//node& operator=(const node&);		//vectorun içinde zaten = operatoru tanýmlýymýþ öðrenince yoru msatýrý yaptým
};

class CardManager{
	public:
		vector<node*> new_vector;
		int line_number;		//dosyanýn satýr uzunluðunu tutuyor
		int fullorfilter;		//full mü filter mý istendiðine göre int deðer tutuyor 1 veya 2
		int iorm;		//bir üst satýr gibi ayný þekilde insertion sort mu merge sortmu istendiðine göre int deðer tutuyor
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

/*node& node::operator=(const node& z){		//vector için = overloadý ama zaten vectorun kendisinin varmýþ
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

	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string line;		//satýrlarý bu stringe okuyorum
	
		while(getline(file, line)){		//satýrý alýyorum
			stringstream stream(line);
			string word;
			node* temp = new node;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		//alýnan satýrdan taba kadar kelimeyi alýp geçici node u ma kaydediyorum
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
					temp->Cost = atoi(word.c_str());		//cost verisini int haline çevirip kaydediyorum
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					new_vector.push_back(temp);		//node lar tamamlandýkça vector ume pushluyorum
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
		cout << "File Writing Error" << endl;		//dosya açýlmama hatasý
		return 0;
	}
	else{
		for(int i = 0; i < line_number; i++){		//her özelliði tek tek yazýyorum ve satýr atlýyorum
			output << new_vector[i]->Name << '\t' << new_vector[i]->Class << '\t' << new_vector[i]->Rarity << '\t' << new_vector[i]->Set << '\t' << new_vector[i]->Type << '\t' << new_vector[i]->Cost << endl;
		}
	}
	output.close();
}

void CardManager::fullSort(){
	if(iorm == 1)		//istenenin insertion sort mu merge sort mu olduðunu tutan veriye göre doðru fonksiyonu çaðýrýyorum
		insertionSort();
	else if(iorm == 2)
		mergeSort(0, line_number-1);
}

void CardManager::filterSort(){
	if(iorm == 1)		//yukarýdaki fullsort da yapýlanýn aynýsý yapýlmakta
		insertionSort();
	else if(iorm == 2)
		mergeSort(0, line_number-1);
}

void CardManager::insertionSort(){
	node* temp;
	if(fullorfilter == 1){		//full mu filter mý istendiðini tutan veriye göre bu if e veya altta else ine giriyoruz ve burasý fullsort kýsmý
		for(int i = 0; i < line_number; i++){
			int j = i;
			for(; j >= 1; j--){		//i satýr sayýsýna kadar ilerliyor ve j de i den baþlayýp geri gelerek gerekirse yer deðiþtiriyor
				if (strcmp(new_vector[j]->Class.c_str(), new_vector[j-1]->Class.c_str()) < 0){
					temp = new_vector[j];
					new_vector[j] = new_vector[j-1];
					new_vector[j-1] = temp;
				}
				else if (strcmp(new_vector[j]->Class.c_str(), new_vector[j-1]->Class.c_str()) == 0){		//class kýsmý aynýsa costa bakýyoruz
					if (new_vector[j]->Cost < new_vector[j - 1]->Cost){
						temp = new_vector[j];
						new_vector[j] = new_vector[j-1];
						new_vector[j-1] = temp;
					}
					else if (new_vector[j]->Cost == new_vector[j - 1]->Cost){		//cost kýsmý da aynýysa name e bakýyoruz
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
				if (strcmp(new_vector[j]->Type.c_str(), new_vector[j-1]->Type.c_str()) < 0){		//burasý da filtersort kýzmý sadece type bakýyoruz
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
		mergeSort(first, middle);		//tek eleman kalana kadar recursive olarak yarýya bölüp bölüp yeniden çaðýrýyoruz
		mergeSort(middle+1, last);		//yarýya bölerken yeni array oluþturmayýp yer israfý yapmayýp sadece indisleri yolluyoruz vectoru yollamasakda eriþimimiz olduðu için sadece indisler yeterli
		merge(first, middle, last);		//elimizdeki parçalarý birleþtirmek için bu fonksiyona yolluyoruz
	}
}

void CardManager::merge(int first, int middle, int last){
	node* temp_array[last-first+1];		//sýralanmýþ halini tutmak için geçici node tipinde array oluþturuyoruz.
	int i = first;
	int j = middle + 1;		//i ilk yarýnýn baþlangýcý j de ikinci yarýnýn baþlangýcý
	int k = 0;		//k geçici arrayin iteratoru
	if(fullorfilter == 1){		//fullsort kýsmý
		while(i <= middle && j <= last){		//birinci veya ikinci yarý sona ulaþana kadar devam edecek
			if (strcmp(new_vector[i]->Class.c_str(), new_vector[j]->Class.c_str()) < 0){		//fullsortun gerektirdiði gibi sýralýyoruz burda insertion sorttaki gibi
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
		while(i <= middle && j <= last){		//burasý da filter sort kýsmý
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
	
	if(i > middle){		//full yada filter sorttaki herhangi birinin while ý bittiðinde yani 1. veya 2. yarý bittiðinde kalan kýsmý direk burada kopyalýyoruz
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
	for(i = first; i <= last; i++){		//geçici arrayimizi vectorun ayný bölgesine kopyalýyoruz
		new_vector[i] = temp_array[k];
		k++;
	}
}

#endif
