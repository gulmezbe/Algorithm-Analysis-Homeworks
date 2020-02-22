/*
* Student population: Behlül Gülmez
* Student ID : 150140113
* Date: 01/12/2017
*/

#include <ctime>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<vector>
#include <math.h>

#include"functions.h"

using namespace std;

typedef MyClass Datastructure;

Datastructure mycls;

int main(){
	clock_t begin = clock();
	int total;
	
	if(mycls.read_file1()){
		clock_t end1 = clock();
		total = end1 - begin;
		cout << endl << "DICTIONARY" << endl << "Insertion finished after " << (double)total / CLOCKS_PER_SEC << " seconds." << endl << endl;
		mycls.write_file1();
		clock_t end2 = clock();
		total = end2 - end1;
		cout << endl << endl << "Lookup finished after " << (double)total / CLOCKS_PER_SEC << " seconds." << endl << endl;
	}
	clock_t end3 = clock();
	if(mycls.read_file2()){
		clock_t end4 = clock();
		total = end4 - end3;
		cout << endl << "LIST" << endl << "Insertion finished after " << (double)total / CLOCKS_PER_SEC << " seconds." << endl << endl;
		mycls.write_file2();
		clock_t end5 = clock();
		total = end5 - end4;
		cout << endl << "Lookup finished after " << (double)total / CLOCKS_PER_SEC << " seconds." << endl << endl;
	}
	
	return 0;
}
