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
    int age;
    double height;
};

//********** variable decleration**********/

int i,j;

//********** Method decleration **********/

Person createPerson(int age, double height);
void write( memPool_t &pool );

//********** other stored type **********/

ostream &operator<<(ostream &os, Person &p){

    return os << "Age: " << p.age << '\n'
        << "Height: " << p.height << endl;

}

void read( memPool_t &pool );


int main (int argc, int **argv){

	memPool_t pool;

	while (1)
	{
		cout << "Chose type:" << endl
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
				continue;
			case 2:
				write(pool);
				continue;
		}
	}

	return 1;
}

Person createPerson(int age, double height){

	Person p;

    p.age = age;
    p.height = height;

	return p;
}

void write( memPool_t &pool )
{
	int intValue;
	int position;

	if ((i > 0)&&(5 > i)){
		switch(i){
			case 1:
				int age;
				double height;
				Person p;

				cout << "enter age:";
				cin >> age;
				cout << endl;
				cout << "enter height:";
				cin >> height;
				cout << endl;
				p = createPerson(age, height);
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

	cout << "enter position: ";
	cin >> position;
	cout <<endl;

	switch (i){
		case 1:
			Person p;
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
