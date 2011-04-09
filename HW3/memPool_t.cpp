#include "memPool_t.h"
#include <list>

/*****************
 * CTORs and DTOR
 *****************/

memPool_t::memPool_t() : _size(0), _capacity(0){

	createNewMemPage();

	_currentPage = _pool.begin();

}

memPool_t::memPool_t(int pageNumber) : _size(0), _capacity(0){

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
