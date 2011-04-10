/*
 * main.cpp
 *
 */

#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>

using namespace std;


int main (int argc, int **argv){

	memPool_t p;


	int k = 5;
	int j;

	cout << p << endl;

	p.write(k, sizeof(k));

	cout << p << endl;

	//p.GetCurrentMemPage().read(j, sizeof(j), 0);

	cout << p.GetCurrentMemPage() << endl;

	//cout << p << endl;

	p.read(j, sizeof(j), 0);

	cout << p << endl;

	cout << "j: " << j << endl;


	return 0;

}


