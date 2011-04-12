/*
 * main.cpp
 *
 */

#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>

using namespace std;

//********** Class Person**********/

class Person {
public:

    Person ();
    Person (int age, double height);

    int age;
    double height;
};

Person::Person(int age, double height) {
    this->age = age;
    this->height = height;
}

Person::Person() : age(0), height(0){
    
}

//********** variable decleration**********/

int i,j,k,l,m;

//********** Method decleration **********/

void write( memPool_t &pool );

//********** other stored type **********/

ostream &operator<<(ostream &os, Person &p){

    return os << "Age: " << p.age << '\n'
        << "Height: " << p.height << endl;

}

void read( memPool_t &pool );

void GetInformation( memPool_t &pool );

void DoOtherActions( memPool_t &pool );


int main (int argc, int **argv){
    
   	memPool_t pool;

	while (1)
	{
		cout << "Choose action:" << endl
			<< "*************" << endl
			<< "1- read/write		2 - information" << endl
			<< "3- other action		4 - exit" <<endl;
		cin >> k;
		cout << endl;

		switch(k){
			case 1:
				cout << "Choose type:" << endl
					<< "***********" << endl
					<< "1 - Person			2 - int" << endl
					<< "3 - double			4 - char" << endl;
				cin >> i;
				cout << endl;

				cout << "Choose action:" <<endl
					<< "**************" << endl
					<< "1- read				2 - write" <<endl;
				cin >> j;

				switch(j){
					case 1:
						read(pool);
						break;
					case 2:
						write(pool);
						break;
						}
				continue;
			case 2:
				GetInformation(pool);
				continue;
			case 3:
				DoOtherActions(pool);
				continue;
			case 4:
				exit(1);
		}
		cout << endl;
	}

	return 1;
}


void write( memPool_t &pool )
{
	int intValue;
	int position;
    Person p;

	if ((i > 0)&&(5 > i)){
		switch(i){
			case 1:
				int age;
				double height;
                
				
				cout << "enter age:";
				cin >> age;
				cout << endl;
				cout << "enter height:";
				cin >> height;
				cout << endl;
                p.age = age; p.height = height;
				position = pool.GetCurrentPosition();
				pool.write<Person> (p, sizeof(p));

				cout << "new Person with the age of " << p.age << " and height of " << p.height << " was written to position: " << position << endl;
				break;
			case 2:
				cout << "enter value of int:";
				cin >> intValue;
				cout << endl;

				position = pool.GetCurrentPosition();
				pool.write<int> (intValue,sizeof(intValue));

				cout << "int with the value of: " << intValue << " was written to position: " << position << endl;
				break;
			case 3:
				double doubleValue;
				cout << "enter value of double:";
				cin >> doubleValue;
				cout << endl;

				position = pool.GetCurrentPosition();
				pool.write<double> (doubleValue,sizeof(doubleValue));

				cout << "double with the value of: " << doubleValue << " was written to position: " << position << endl;
				break;
			case 4:
				char charValue;
				cout << "enter value of char:";
				cin >> charValue;
				cout << endl;

				position = pool.GetCurrentPosition();
				pool.write<char> (charValue,sizeof(charValue));

				cout << "char with the value of: " << charValue << " was written to position: " << position << endl;
				break;
		}
	}
	cout << endl;
}

void read( memPool_t &pool )
{
	int position;
    Person p;

	cout << "enter position: ";
	cin >> position;
	cout <<endl;

	switch (i){
		case 1:
			
			pool.read<Person> (p, sizeof(p),position);
			cout << "Person with age: " << p.age << " and height: " << p.height << " was read from position: " << position << endl;
			break;
		case 2:	
			int intValue;
			pool.read(intValue,sizeof(intValue),position);
			cout << "int with value of " << intValue << " was read from position: " << position << endl;
			break;
		case 3:
			double doubleValue;
			pool.read(doubleValue,sizeof(doubleValue),position);
			cout << "double with value of " << doubleValue << " was read from position: " << position << endl;
			break;
		case 4:
			char charValue;
			pool.read(charValue,sizeof(charValue),position);
			cout << "char with value of " << charValue << " was read from position: " << position << endl;
			break;
	}
	cout << endl;
}

void GetInformation( memPool_t &pool )
{
	cout << "Choose action:" << endl
		<<"***************"<< endl
		<< "1- Is Empty?		2- actual size of poll" << endl
		<< "3- capacity		4- number of pages" << endl
		<< "5- get 1st page		6- get last page" << endl
		<< "7- get current page	8- get current position" << endl
		<< "9- get default page size" << endl;
	cin >> l;
	switch (l)
	{
	case 1:
		cout << (pool.IsEmpty() ? "yes" : "no") << endl;
		break;
	case 2:
		cout << pool.GetActualSize() << endl;
		break;
	case 3:
		cout << pool.GetCapacity()<< endl;
		break;
	case 4:
		cout << pool.GetNumberOfPages()<< endl;
		break;
	case 5:
		cout << pool.GetFirstMemPage()<< endl;
		break;
	case 6:
		cout << pool.GetLastMemPage()<< endl;
		break;
	case 7:
		cout << pool.GetCurrentMemPage()<< endl;
		break;
	case 8:
		cout << pool.GetCurrentPosition()<<endl;
		break;
	case 9:
		cout << pool.GetDefaultPageSize()<<endl;
		break;
	}
}

void DoOtherActions( memPool_t &pool )
{
	cout << "Choose action:"
		<<"***************" <<endl
		<<"1- set default page size" << endl
		<<"2- set current position" << endl
		<<"3- create new page" << endl;
	cin >> m;
	switch (m)
	{
	case 1:
		int size;
		cout << "enter size:";
		cin >> size;
		cout << endl;
		pool.SetDefaultPageSize(size);
		break;
	case 2:
		int pos;
		cout << "enter position:";
		cin >> pos;
		cout << endl;
		pool.SetCurrentPosition(pos);
		break;
	case 3:
		pool.createNewMemPage();
		cout << " new page has been created" << endl;
		break;
	}
}
