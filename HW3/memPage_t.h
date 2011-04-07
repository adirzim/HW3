#ifndef MemPage_t_H_
#endif MemPage_t_H_

#include "memPool_t.h"

class memPage_t{

		//TODO: make memPage internal to memPool only
public:

	//Static Member
	static int PageSize;								//Default Page Size

	//CTOR & DTOR
	memPage_t();										//default CTOR - from PageSize
	memPage_t(int size);								//CTOR from user size
	~memPage_t();										//DTOR

	void setPosition(int newAddress);					//set current position in memory page (value between 0 to _size)
	memPage_t* GetPosition() const;						//get current position in memory page
	
	//page status information
	bool IsPageEmpty();									//is page empty
	bool IsPageFull();									//is page Full
	int GetActualSize();									//actual size of a page(how many bytes really written in page)
	int GetCapacity();										//capacity of a page (length)
	
	template<class T>
	T* read(int sizeOfT);								//read data from page
	void write(const T &t, int sizeOfT);				//write data to page

	memPage_t* NextPage();								//a pointer to the next page
	memPage_t* PreviousPage();							//a pointer to the previous page
	
private:

	//Disabling copy
	memPage_t(const memPage_t &m);						//disable copy CTOR
	const memPage_t &operator=(const memPage_t &m);		//disable assignment operator

	//Page properties
	int _size;											//how many bytes really written in page
	int _capacity;										//capacity of a page in bytes
	int position;										//current position in memory page

	//TODO: choose STL to implement memPage


};