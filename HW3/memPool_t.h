#ifndef MemPool_t_H_ 
#define MemPool_t_H_

#include "memPage_t.h"
#include <list>

using namespace std;

class memPool_t{

public:

	//CTORs & DTOR
	memPool_t();										//default CTOR - 1 empty page
	explicit memPool_t(int pageNumber);					//CTOR from number of empty page to initialize
	~memPool_t();										//DTOR

	//public methods
	int GetCurrentPosition() const;						//get the current position in the memPool_t (how many bytes really written in memPool_t
	void SetCurrentPosition(int newPosition);			//set the current position (between 0-PageSize)

	template<class T> int read(T &t, int size);					//read data from manager (from current position)
	template<class T> int read(T &t, int size, int pos);        //read data from manager (from pos)

	template<class T> int write(const T &t, int size);			//write data to manager (from current position)
	template<class T> int write(const T &t, int size, int pos); //write data to manage (from pos)

	void createNewMemPage();							//create memory page upon demand

	//memPool information
	bool IsEmpty() const;								//is memPool is Empty?
	int GetActualSize() const;							//actual size of the object memPool_t
	int GetCapacity() const;							//capacity of the manager (how many bytes are written in this pool)
	int GetNumberOfPages() const;						//get the number of memory pages


	//TODO: Should this be public? Should it be const?
	memPage_t &GetFirstMemPage();        		       	//get ref to the first memory page
	memPage_t &GetLastMemPage();			            //get ref to the last memory page
	memPage_t &GetCurrentMemPage();					    //get ref to the current memory page

	//default size of memPage
	int GetDefaultPageSize() const;							//get default memory page size
	void SetDefaultPageSize(int size) const;				//set default memory page size

	friend ostream &operator<< (ostream &os, memPool_t &p);

private:

	//disable copy
	memPool_t(const memPool_t &m);						//disable copy CTOR             //Note: Not Implemented
	const memPool_t &operator=(const memPool_t &m);		//disable assignment operator   //Note: Not Implemented

    int _read(char *buffer, int size);                  //Read from pool size bytes into buffer. Return total read bytes
    int _write(char *buffer, int size);                 //Write to pool size bytes from buffer. Return total written bytes

	//Data Members
	int _size;                                          //Total number of written bytes
	int _capacity;                                      //Capacity of manager
	list<memPage_t>::iterator _currentPage;             //Current memPage_t
	int _position;                                      //Position (in bytes) from begining of manager

	list<memPage_t> _pool;                              //List (pool) of memPage_t in manager

};

/*******************
 * Inline functions
 *******************/
inline bool memPool_t::IsEmpty() const{
	return _size == 0;
}

inline int memPool_t::GetActualSize() const{
	return _size;
}

inline int memPool_t::GetCapacity() const{
	return _capacity;
}

inline int memPool_t::GetNumberOfPages() const{
	return _pool.size();
}

inline 	int memPool_t::GetDefaultPageSize() const{
	return memPage_t::PageSize;
}

inline void memPool_t::SetDefaultPageSize(int size) const{

	memPage_t::PageSize = size;

}

inline int memPool_t::GetCurrentPosition() const{
	return _position;
}

inline memPage_t &memPool_t::GetCurrentMemPage(){
	return ((memPage_t &) *_currentPage);
}

inline memPage_t &memPool_t::GetFirstMemPage(){
    return (memPage_t &) *_pool.begin();
}

inline memPage_t &memPool_t::GetLastMemPage(){
    return (memPage_t &) *(--_pool.end());
}


/*********************
 * Template functions
 *********************/

template<class T> int memPool_t::read(T &t, int size){

    return _read((char *)&t, size);
}

template<class T> int memPool_t::read(T &t, int size, int pos){

	SetCurrentPosition(pos);

	return _read((char *)&t, size);
}

template<class T> int memPool_t::write(const T &t, int size){

	return _write((char *)&t, size);
}

template<class T> int memPool_t::write(const T &t, int size, int pos){

	SetCurrentPosition(pos);

	return _write((char *)&t, size);
}

#endif
