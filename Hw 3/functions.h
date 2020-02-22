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
#include <math.h>

using namespace std;

class Book_Character{
	public:
		int page;
		int line;
		int index;
		string character;
		Book_Character();
		~Book_Character();
		Book_Character& operator=(const Book_Character&);
};

class MyClass{
	public:
		int total_collision;
		Book_Character* Dictionary[131071];
		vector<Book_Character*> List;
		MyClass();
		~MyClass();
		int read_file1();
		int write_file1();
		int read_file2();
		int write_file2();
		unsigned long hash(int, int, int);
		unsigned long probing(unsigned long, int);
};

Book_Character::Book_Character(){
	page = 0;
	line = 0;
	index = 0;
}

Book_Character::~Book_Character(){
	
}

MyClass::MyClass(){
	total_collision = 0;
}

MyClass::~MyClass(){
	
}

Book_Character& Book_Character::operator=(const Book_Character& z){			// book türündeki verileri eþittir iþaretiyle kopyalayabilmek için operatör tanýmý
	page = z.page;
	line = z.line;
	index = z.index;
	character = z.character;
}

int MyClass::read_file1(){
	unsigned long h;		//keyin atanacaðý sayý
	int collision = 1;
	ifstream file("ds-set-input.txt");
	int line_number = 0;
	
	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error ds-set-input.txt" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string Line;		//satýrlarý bu stringe okuyorum
		while(getline(file, Line)){		//satýrý alýyorum
			stringstream stream(Line);
			string word;
			Book_Character* temp = new Book_Character;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		//alýnan satýrdan virgüle kadar kelimeyi alýp geçici node u ma kaydediyorum
					temp->page = atoi(word.c_str());
				}
				else if(word_number == 2){
					getline(stream, word, '\t');
					temp->line = atoi(word.c_str());
				}
				else if(word_number == 3){
					getline(stream, word, '\t');
					temp->index = atoi(word.c_str());
				}
				else{
					getline(stream, word, '\n');
					temp->character = word;
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					h = hash(temp->page, temp->line, temp->index);
					if(Dictionary[h] == NULL){
						Dictionary[h] = temp;
					}
					else{
						while(Dictionary[h] != NULL){
							h = probing(h, collision);
							collision++;
						}
						Dictionary[h] = temp;
						total_collision += (collision - 1);
						collision = 1;
					}
							
					break;
				}
			}		
			line_number++;
			if(line_number == 1000){
				cout << "Average number of collisions (first 1,000) |" << total_collision / 1000.0 << endl;
			}			
			if(line_number == 10000){
				cout << "Average number of collisions (first 10,000) |" << total_collision / 10000.0 << endl;
			}				
			if(line_number == 100000){
				cout << "Average number of collisions (first 100,000) |" << total_collision / 100000.0 << endl;
			}				
		}
		
		cout << "Average number of collisions (overall) |" << total_collision / 131071 << endl;			
		file.close();
		return 1;
	}
}

int MyClass::write_file1(){
	unsigned long h;
	int a, b, c;
	int line_number = 0;
	int collision = 1;
	
	ofstream output("ds-set-output-dict.txt");
	if(!output){
		cout << "File Writing Error ds-set-output-dict.txt" << endl;		//dosya açýlmama hatasý
		return 0;
	}
	
	ifstream file("ds-set-lookup.txt");
	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error ds-set-lookup.txt" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string Line;		//satýrlarý bu stringe okuyorum
		while(getline(file, Line)){		//satýrý alýyorum
			stringstream stream(Line);
			string word;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		
					a = atoi(word.c_str());
				}
				else if(word_number == 2){
					getline(stream, word, '\t');
					b = atoi(word.c_str());
				}
				else{
					getline(stream, word, '\n');
					c = atoi(word.c_str());
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					h = hash(a, b, c);
					
					if(Dictionary[h]->page == a && Dictionary[h]->line == b && Dictionary[h]->index == c && h < 131071){
						output << a << '\t' << b << '\t' << c << '\t' << Dictionary[h]->character << '\n';
					}
					else{
						while(Dictionary[h]->page != a || Dictionary[h]->line != b || Dictionary[h]->index != c || h >= 131071){
							h = probing(h, collision);
							collision++;
						}
						output << a << '\t' << b << '\t' << c << '\t' << Dictionary[h]->character << '\n';
						collision = 1;
					}
							
					break;
				}
			}		
			line_number++;
		}
		file.close();
		output.close();
		return 1;
	}
}

int MyClass::read_file2(){
	ifstream file("ds-set-input.txt");
	int line_number = 0;
	
	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error ds-set-input.txt" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string Line;		//satýrlarý bu stringe okuyorum
		while(getline(file, Line)){		//satýrý alýyorum
			stringstream stream(Line);
			string word;
			Book_Character* temp = new Book_Character;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		
					temp->page = atoi(word.c_str());
				}
				else if(word_number == 2){
					getline(stream, word, '\t');
					temp->line = atoi(word.c_str());
				}
				else if(word_number == 3){
					getline(stream, word, '\t');
					temp->index = atoi(word.c_str());
				}
				else{
					getline(stream, word, '\n');
					temp->character = word;
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					List.push_back(temp);		//node lar tamamlandýkça vector ume pushluyorum
					break;
				}
			}		
			line_number++;
		}
		file.close();
		return 1;
	}
}

int MyClass::write_file2(){
	unsigned long h;
	int a, b, c;
	int line_number = 0;
	
	ofstream output("ds-set-output-list.txt");		//yazýlacak dosya açýlýyor
	if(!output){
		cout << "File Writing Error ds-set-output-list.txt" << endl;		//dosya açýlmama hatasý
		return 0;
	}
	
	ifstream file("ds-set-lookup.txt");
	if (file.is_open() == false){		//dosya açýlmama hatasý
		cout << "File Error ds-set-lookup.txt" << endl;
		return 0;
	}
	else{
		int word_number = 1;		//word_number sayýsý satýrdaki kaçýncý kelimede olduðumuzu tutuyor ve buna göre o stringi doðru yere kaydediyorum
		string Line;		//satýrlarý bu stringe okuyorum
		while(getline(file, Line)){		//satýrý alýyorum
			stringstream stream(Line);
			string word;
			while(1){
				if(word_number == 1){
					getline(stream, word, '\t');		//alýnan satýrdan virgüle kadar kelimeyi alýp geçici node u ma kaydediyorum
					a = atoi(word.c_str());
				}
				else if(word_number == 2){
					getline(stream, word, '\t');
					b = atoi(word.c_str());
				}
				else{
					getline(stream, word, '\n');
					c = atoi(word.c_str());
					word_number = 0;
				}
				word_number++;
				if( word_number == 1){
					for(int i = 0;i < List.size(); i++){
						if(a == List[i]->page){
							if(b == List[i]->line){
								if(c == List[i]->index){
									output << a << '\t' << b << '\t' << c << '\t' << List[i]->character << '\n';
									break;
								}
							}
						}
					}	
					break;
				}
			}		
			line_number++;
		}
		file.close();
		output.close();
		return 1;
	}
}

unsigned long MyClass::hash(int a, int b, int c){
	unsigned long M = 131071;
	unsigned long A = 0.618;
	unsigned long k = a * 10000.0 + b * 100.0 + c;
	return floor(M * fmod(k*A , 1.000));
}

unsigned long MyClass::probing(unsigned long h, int i){
	unsigned long M = 131071.0;
	int x = fmod(i, M);
	//return fmod(fmod(h, M) + fmod(7*x, M) + fmod(3*fmod(x * x, M), M), M);
	return fmod(h + 7*i + 3*i*i, M);
}

#endif
