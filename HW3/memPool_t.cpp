#include "memPool_t.h"
#include "memPage_t.h"
#include <list>

using namespace std;

/*****************
 * CTORs and DTOR
 *****************/

memPool_t::memPool_t() : _size(0), _capacity(0), _position(0){

	createNewMemPage();

	_currentPage = _pool.begin();

}

memPool_t::memPool_t(int pageNumber) : _size(0), _capacity(0), _position(0){

	for (int i = 0; i < pageNumber; i++){

		createNewMemPage();
	}

	_currentPage = _pool.begin();


}

memPool_t::~memPool_t(){

}



/*****************
 * Public Methods
 ****************/

void memPool_t::createNewMemPage(){

	memPage_t page;

	_capacity += page.GetCapacity();

	_pool.push_back(page);
}

//int memPool_t::GetCurrentPosition() const{
//
//	//TODO: Implement in LOG(n)
//
//	int pos = 0;
//
//
//	for (list<memPage_t>::const_iterator it = _pool.begin(); it != _currentPage; it++){
//		pos += ((memPage_t) *it).GetCapacity();
//	}
//
//	pos += ((memPage_t)*_currentPage).GetPosition();
//
//	return pos;
//
//}

void memPool_t::SetCurrentPosition(int newPosition){

	//TODO: Implement in LOG(n)

	if (newPosition > GetActualSize()){ //Invalid position
		return;
	}

	_position = 0;

	list<memPage_t>::iterator it = _pool.begin();

	//Find relevant page
	while (newPosition >= ((memPage_t &) *it).GetCapacity()){
		newPosition -= ((memPage_t &) *it).GetCapacity();
		_position += ((memPage_t &) *it).GetCapacity();
		it++;
	}

	//Set Current page
	_currentPage = it;

	_position += newPosition;

	//Set Position in page
	((memPage_t &) *it).setPosition(newPosition);


}

/*****************
 * Private methods
 *****************/

ostream &operator<< (ostream &os, memPool_t &p){

	return os << "Pool size: " << p.GetActualSize() << '\n'
			<< "Pool capacity: " << p.GetCapacity() << '\n'
			<< "Number of pages: " << p.GetNumberOfPages() << '\n'
			<< "Position: " << p.GetCurrentPosition() << '\n';

}
