/*
 * main.cpp
 *
 */

#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>

using namespace std;


class Person {
public:
    int age;
    double height;
};

ostream &operator<<(ostream &os, Person &p){

    return os << "Age: " << p.age << '\n'
        << "Height: " << p.height << endl;

}

int main (int argc, int **argv){

	

    Person p;

    p.age = 5;
    p.height = 5.678;

	Person j, l;

    //memPage_t::PageSize = 2;

    memPool_t pool;

	cout << pool << endl;

    //p.SetDefaultPageSize(1);

	pool.write(p, sizeof(p));

    cout << pool << endl;

    pool.write(p, sizeof(p));



	//p.GetCurrentMemPage().read(j, sizeof(j), 0);

	//cout << p.GetCurrentMemPage() << endl;

	//cout << p << endl;

	pool.read(j, sizeof(j), 0);
    pool.read(l, sizeof(l), 16);

	cout << "j: " << j << endl;
    
	cout << "l: " << l << endl;

    p.age = 12;
    p.height = 123.333;

    pool.write(p, sizeof(p), 0);

    pool.read(j, sizeof(j), 0);
    pool.read(l, sizeof(l));

    cout << sizeof(p) << endl;
	
	cout << "j: " << j << endl;
    
	cout << "l: " << l << endl;





	return 0;

}


