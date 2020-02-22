/*
* Student population: Behlül Gülmez
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

typedef MyClass Datastructure;
int total;

Datastructure mycls;

int main(int argc, char *argv[]){
	char* coming_data = new char [strlen(argv[1]) + 1];
	strcpy(coming_data, argv[1]);
	
	int n = atoi(coming_data);
	
	if(mycls.read_file(n)){

		clock_t begin = clock();
		
		mycls.quickSort(0, n - 1);
		
		clock_t end = clock();
		total = end - begin;

		mycls.write_file();
	}

	cout << "Time elapsed: " << (double)total / CLOCKS_PER_SEC << " seconds" <<endl;
	
	return 0;
}
