#include "memPage_t.h"
#include <ostream>
using namespace std;


int memPage_t::PageSize = 1024;	//Defualt page size

/*****************
 * CTORs and DTOR
 ****************/

memPage_t::memPage_t() : _capacity(PageSize), _position(0), _size(0){
	_allocateBuffer();
}


memPage_t::memPage_t(int size) : _capacity(size), _position(0), _size(0){
	_allocateBuffer();
}

memPage_t::~memPage_t(){
	delete[] buffer;
}

memPage_t::memPage_t(const memPage_t &m) : _capacity(m._capacity), _position(m._position), _size(m._size){

	_allocateBuffer();

	memcpy(buffer, m.buffer, _size);

}

/*****************
 * Public Methods
 *****************/




/*****************
 * Private Methods
 *****************/
void memPage_t::_allocateBuffer(){

	buffer = new char[_capacity];

}

int memPage_t::_write(void *t, int size, int pos){

	//Do not allow "Holes" in mem page
	if (pos > size){
		return 0;
	}

	//Make sure we do not overflow buffer.
	//Write only avialable number of bytes
	if ((pos + size) > _capacity){
		size = _capacity - pos;
	}

	//Perform write to memory
	memcpy(&buffer[pos], t, size);

	//Update size & pos
	_position = pos + size;

//	if (_position > _size - 1){
//		_size = _position + 1;
//	}
	_size += size;



	return size;

}

int memPage_t::_read(void *t, int size, int pos){

	//Do not allow reading more than size
	if (pos > size - 1){
		return 0;
	}

	//Do not allow reading more than buffer size
	if (pos + size > _size){
		size = _size - pos;
	}

	//Perform read
	memcpy(t, &buffer[pos], size);

	//Update pos
	_position = pos + size;

	return size;


}

ostream &operator<<(ostream &os, memPage_t &p){

	return os << "Defualt Page size: " << p.PageSize << '\n'
				<< "Page capacity: " << p._capacity << '\n'
				<< "Page size: " << p._size << '\n'
				<< "Cursor Location: " << p._position;

}
