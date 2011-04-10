#ifndef MemPage_t_H_
#define MemPage_t_H_

#include <ostream>
using namespace std;

class memPage_t{

	//TODO: make memPage internal to memPool only

public:

	//Static Member
	static int PageSize;								//Default Page Size

	//CTOR & DTOR
	memPage_t();										//default CTOR - from PageSize
	explicit memPage_t(int size);								//CTOR from user size
	~memPage_t();										//DTOR
	memPage_t(const memPage_t &m);						//Copy CTOR for STL implementation //TODO: make memPool_t Friend?

	void setPosition(int position);						//set current position in memory page (value between 0 to _size)
	int GetPosition() const;							//get current position in memory page
	
	//page status information
	bool IsPageEmpty() const;							//is page empty
	bool IsPageFull() const;							//is page Full
	int GetActualSize() const;							//actual size of a page(how many bytes really written in page)
	int GetCapacity() const;							//capacity of a page (length)
	
	int read(char *t, int size, int pos);		//read data from page, return number of bytes read
	int write(char *t, int size, int pos);		//write data to page, return number of bytes written

	int write(char *t, int size);
	int read(char *t, int size);


	friend ostream &operator<<(ostream &os, memPage_t &p);

	//memPage_t* NextPage();								//a pointer to the next page
	//memPage_t* PreviousPage();							//a pointer to the previous page
	
private:

	//Disabling copy of memPage_t
							//disable copy CTOR NOTE: Not Implemented!
	//const memPage_t &operator=(const memPage_t &m);		//disable assignment operator NOTE: Note Implemented!



	void _allocateBuffer(); 							//Init memPage members

	//TODO: Use Template? User void *?
	int _write(char *t, int size, int pos); 			//Perform actual write
	int _read(char *t, int size, int pos); 				//Perform actual read

	//Page data members
	const int _capacity;								//capacity of a page in bytes
	int _position;										//current position in memory page (range: 0 .. _capacity - 1)
	int _size;											//how many bytes really written in page
	char *buffer;										//Memory buffer of page


};


inline bool memPage_t::IsPageEmpty() const{
	return (_size == 0);
}

inline bool memPage_t::IsPageFull() const{
	return (_size == _capacity - 1);
}

inline int memPage_t::GetActualSize() const{
	return _size;
}

inline int memPage_t::GetCapacity() const{
	return _capacity;
}

inline void memPage_t::setPosition(int position){
	_position = position;
}
inline int memPage_t::GetPosition() const{
	return _position;
}




#endif
