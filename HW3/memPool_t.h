#ifndef MemPool_t_H_ 
#define MemPool_t_H_

#include "memPage_t.h"
#include <list>

using namespace std;

class memPool_t{

public:


	//CTOR & DTOR
	memPool_t();										//default CTOR - 1 empty page
	explicit memPool_t(int pageNumber);					//CTOR from number of empty page to initialize
	~memPool_t();										//DTOR

	//public methods
	int GetCurrentPosition() const;						//get the current position in the memPool_t (how many bytes really written in memPool_t
	void SetCurrentPosition(int newPosition);			//set the current position (between 0-PageSize)

	template<class T> int read(const T &t, int size);					//read data from manager
	template<class T> int read(const T &t, int size, int pos);

	template<class T> int write(const T &t, int size);			//write data to manager
	template<class T> int write(const T &t, int size, int pos);

	void createNewMemPage();							//create memory page upon demand

	//memPool information
	bool IsEmpty() const;								//is memPool is Empty?
	int GetActualSize() const;							//actual size of the object memPool_t
	int GetCapacity() const;							//capacity of the manager (how many bytes are written in this pool)
	int GetNumberOfPages() const;						//get the number of memory pages


	//TODO: Should this be public?
	const memPage_t *GetFirstMemPage() const;				//get pointer to the first memory page
	const memPage_t *GetLastMemPgae() const;				//get pointer to the last memory page
	const memPage_t *GetCurrentMemPage() const;				//get pointer to the current memory page

	//default size of memPage
	int GetDefaultPageSize() const;							//get default memory page size
	void SetDefaultPageSize(int size) const;				//set default memory page size

private:

	//disable copy
	memPool_t(const memPool_t &m);						//disable copy CTOR
	const memPool_t &operator=(const memPool_t &m);		//disable assignment operator

	//Data Members
	int _size;
	int _capacity;
	list<memPage_t>::iterator _currentPage;

	list<memPage_t> _pool;

};

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

/**
 * Read from current position
 */
template<class T> int memPool_t::read(const T &t, int size){

	if (GetCurrentPosition() + size > GetActualSize() - 1){ //Position + size > total written bytes!
		return 0;
	}

	void *pos = (void *)&t; //Get address of object to read

	int tmp = ((memPage_t) *_currentPage).read(t, size);
	int totalRead = tmp;

	while (tmp < size){

		size -= tmp;
		pos += tmp;

		_currentPage++;
		((memPage_t) *_currentPage).setPosition(0);


		tmp = ((memPage_t) *_currentPage).read(pos, size);

		totalRead += tmp;
	}

	return totalRead;

}

/**
 * Read from pos (setPosition & then read)
 */
template<class T> int memPool_t::read(const T &t, int size, int pos){

	SetCurrentPosition(pos);

	return read(t, size);

}

template<class T> int write(const T &t, int size){

//	if (size > GetActualSize()){ //Nothing to read (Not written yet)
//		return 0;
//	}
//
//	void *pos = (void *)&t; //Get address of object to read
//
//	int tmp = ((memPage_t) *_currentPage).read(t, size);
//	int totalRead = tmp;
//
//	while (tmp < size){
//
//		size -= tmp;
//		pos += tmp;
//
//		_currentPage++;
//		((memPage_t) *_currentPage).setPosition(0);
//
//
//		tmp = ((memPage_t) *_currentPage).read(pos, size);
//
//		totalRead += tmp;
//	}
//
//	return totalRead;

}

template<class T> int memPool_t::write(const T &t, int size, int pos){

	SetCurrentPosition(pos);

	return write(t, size);

}
#endif
