/*
* Student Name: Behlül Gülmez
* Student ID : 150140113
* Date: 11/10/2017
*/

#include <ctime>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<vector>

#include"functions.h"

using namespace std;

typedef CardManager Datastructure;
int total;

Datastructure mng;

int main(int argc, char *argv[]){
	char* InputFileName = new char [strlen(argv[3]) + 1];
	strcpy(InputFileName, argv[3]);
		
	char* OutputFileName = new char [strlen(argv[4]) + 1];
	strcpy(OutputFileName, argv[4]);
	
	if(strcmp(argv[1],"-full") == 0)		//full mu filtermý istendiðini kaydediyoruz
		mng.fullorfilter = 1;
	else if(strcmp(argv[1],"-filter") == 0)
		mng.fullorfilter = 2;
	else
		mng.fullorfilter = 0;
	
	if(strcmp(argv[2],"-i") == 0)		//insertion mu merge mi istendiðini kaydediyoruz
		mng.iorm = 1;
	else if(strcmp(argv[2],"-m") == 0)
		mng.iorm = 2;
	else
		mng.iorm = 0;
	
	if(mng.read_file(&InputFileName)){

		clock_t begin = clock();

		if(mng.fullorfilter == 1)		//fullsort mu filtersort mu istendiðine göre gereken fonksiyonu çalýþtýrýyoruz
			mng.fullSort();
		else if(mng.fullorfilter == 2)
			mng.filterSort();
		
		clock_t end = clock();
		total = end - begin;

		mng.write_file(&OutputFileName);
	}

	cout << "Time elapsed: " << (double)total / CLOCKS_PER_SEC << " seconds" <<endl;
	
	return 0;
}
