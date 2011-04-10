/*
 * main.cpp
 *
 */

#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>

using namespace std;


int main (int argc, int **argv){

	


	int k = 5;
	int j;

   // memPage_t::PageSize = 2;

    memPool_t p;

	cout << p << endl;

    //p.SetDefaultPageSize(1);

	p.write(k, sizeof(k));

	cout << p << endl;

	//p.GetCurrentMemPage().read(j, sizeof(j), 0);

	//cout << p.GetCurrentMemPage() << endl;

	//cout << p << endl;

	p.read(j, sizeof(j), 0);

	cout << p << endl;

	cout << "j: " << j << endl;


	return 0;

}


