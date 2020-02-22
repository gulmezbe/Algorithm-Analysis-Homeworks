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
		string population;
		string minimum_age;
		string maximum_age;
		string gender;
		string zipcode;
		string geo_id;
		node();
		~node();
		//node& operator=(const node&);		//vectorun içinde zaten = operatoru tanýmlýymýþ öðrenince yoru msatýrý yaptým
};

class MyClass{
	public:
		vector<node*> new_vector;
		int line_number;		//dosyanýn satýr uzunluðunu tutuyor
		MyClass();
		~MyClass();
		int read_file(int);		//dosya okuma fonksiyonu
		int write_file();		//dosyaya yazma fonksiyonu
		void quickSort(int, int);	
		int quick(int, int);		
};

node::node(){
	
}

node::~node(){
	
}

MyClass::MyClass(){
	line_number = 0;
}

MyClass::~MyClass(){
	
}

int MyClass::read_file(int n){
	ifstream file("population_by_zip_2010.csv");
	//ifstream file("10k-sorted.csv");
	//ifstream file("100k-sorted.csv");
	//ifstream file("1M-sorted.csv");

	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string line;		//satýrlarý bu stringe okuyorum
		
		getline(file, line);
		
		while(getline(file, line)){		//satýrý alýyorum
			if(line_number == n)
				break;
			stringstream stream(line);
			string word;
			node* temp = new node;
			while(1){
				if(word_number == 1){
					getline(stream, word, ',');		//alýnan satýrdan virgüle kadar kelimeyi alýp geçici node u ma kaydediyorum
					temp->population = word;
				}
				else if(word_number == 2){
					getline(stream, word, ',');
					temp->minimum_age = word;
				}
				else if(word_number == 3){
					getline(stream, word, ',');
					temp->maximum_age = word;
				}
				else if(word_number == 4){
					getline(stream, word, ',');
					temp->gender = word;
				}
				else if(word_number == 5){
					getline(stream, word, ',');
					temp->zipcode = word;
				}
				else{
					getline(stream, word, '\n');
					temp->geo_id = word;
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

int MyClass::write_file(){
	ofstream output("output.csv");
	if(!output){
		cout << "File Writing Error" << endl;		//dosya açýlmama hatasý
		return 0;
	}
	else{
		output << "population,minimum_age,maximum_age,gender,zipcode,geo_id" << endl;
		for(int i = 0; i < line_number; i++){		//her özelliði tek tek yazýyorum ve satýr atlýyorum
			output << new_vector[i]->population << ',' << new_vector[i]->minimum_age << ',' << new_vector[i]->maximum_age << ',' << new_vector[i]->gender << ',' << new_vector[i]->zipcode << ',' << new_vector[i]->geo_id << endl;
		}
	}
	output.close();
}

void MyClass::quickSort(int first, int last){
    if (first < last){
        int midPoint = quick(first, last);
 
        quickSort(first, midPoint - 1);
        quickSort(midPoint + 1, last);
    }
}

int MyClass::quick(int first, int last){
	node* temp_array;
    node* pivot = new_vector[last];
    int i = (first); 
    for (int j = first; j <= last- 1; j++){
        if (strcmp(new_vector[j]->population.c_str(), pivot->population.c_str()) < 0){
            temp_array = new_vector[i];
            new_vector[i] = new_vector[j];
            new_vector[j] = temp_array;
            i++;
        }
        else if((strcmp(new_vector[j]->population.c_str(), pivot->population.c_str()) == 0) && (strcmp(new_vector[j]->geo_id.c_str(), pivot->geo_id.c_str()) <= 0)){
        	temp_array = new_vector[i];
            new_vector[i] = new_vector[j];
            new_vector[j] = temp_array;
            i++;
		}
    }
    temp_array = new_vector[i];
    new_vector[i] = new_vector[last];
    new_vector[last] = temp_array;
    return (i);
}









#endif
