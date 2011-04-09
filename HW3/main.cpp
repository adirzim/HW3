/*
 * main.cpp
 *
 */
#include "memPage_t.h"
#include <iostream>

using namespace std;


int main (int argc, int **argv){

	memPage_t p;

	int k = 5;
	int j;

	cout << p << endl;

	p.write(k, sizeof(k));

	cout << p << endl;


	p.read(j, sizeof(j), 0);

	cout << p << endl;

	cout << "j: " << j;




}


