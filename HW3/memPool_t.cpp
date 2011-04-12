#include "memPool_t.h"

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

/************
 * Operators
 ************/

ostream &operator<< (ostream &os, memPool_t &p){

	return os << "Pool size: " << p.GetActualSize() << '\n'
			<< "Pool capacity: " << p.GetCapacity() << '\n'
			<< "Number of pages: " << p.GetNumberOfPages() << '\n'
			<< "Position: " << p.GetCurrentPosition() << '\n';

}

/*****************
 * Public Methods
 ****************/

void memPool_t::createNewMemPage(){

	memPage_t page;

	_capacity += page.GetCapacity();

	_pool.push_back(page);
}


void memPool_t::SetCurrentPosition(int newPosition){


	if (newPosition > _size){ //Invalid position
		return;
	}

	_position = 0;

	list<memPage_t>::iterator it = _pool.begin();

	//Find relevant page
    while (newPosition >= ((memPage_t &) *it).GetCapacity()){

        //Subtract from position capacity of current page
		newPosition -= ((memPage_t &) *it).GetCapacity();

        //Update _position
		_position += ((memPage_t &) *it).GetCapacity();

        //Advance to next page
		it++;

	}

	//Set Current page
	_currentPage = it;

    //Update position
	_position += newPosition;

	//Set Position in page
	((memPage_t &) *it).setPosition(newPosition);
}

/*****************
 * Private methods
 *****************/

/*
 * Read size bytes from pool into buffer
 * Return number of bytes read
 */
int memPool_t::_read(char *buffer, int size){

    //Do not allow reading empty memory
    if (_position + size > _size){ 
		return 0;
	}

	//Try reading from current page
    int tmp = GetCurrentMemPage().read(buffer, size);

    //Save total read bytes
	int totalRead = tmp;
    
    //While we have not read size bytes, continue reading from next pages
	while (tmp < size){

        //Update size left to read
		size -= tmp;

        //Update buffer position
		buffer += tmp;

        //Advance page iterator
		_currentPage++;

        //Set 0 position in next page
        GetCurrentMemPage().setPosition(0);
        
        //Read next chunk of bytes
        tmp = GetCurrentMemPage().read(buffer, size);

        //Update total read bytes
		totalRead += tmp;

        //If error occured (could not read anymore, break)
        if (tmp == 0){
            break;
        }
	}

	//Update position
	_position += totalRead;

	return totalRead;

}

/*
 * Write size bytes to pool. 
 * Return total number of bytes written
 */
int memPool_t::_write(char *buffer, int size){

    //Don't allow "Holes" in memory
    if (_position  > _size){ 
		return 0;
	}
    	

    //Write first chunk of bytes to current page
    int tmp = GetCurrentMemPage().write(buffer, size);

	int totalWrote = tmp;

    //While we have not finshed writing
	while (tmp < size){

        //Subtract written bytes from size
		size -= tmp;

        //Advance buffer
		buffer += tmp;

        //Get next page
	    _currentPage++;

        //If we have reached end of pool, create a new page
        if (_currentPage == _pool.end()){
            //Move iterator back
            _currentPage--;

            //Create new page
            createNewMemPage();
            
            //Advance to new page
            _currentPage++;
        }

        //Set position 0 in current page
        GetCurrentMemPage().setPosition(0);

        //Write next chunk of bytes
		tmp = ((memPage_t &) *_currentPage).write(buffer, size);

        //Update total bytes written
		totalWrote += tmp;

        //If we could not write - break
        if (tmp == 0){
            break;
        }
	}
    

    

    //Update _position & size
	_position += totalWrote;

    if (_position > _size){
        _size = _position;
    }

	//_size += totalWrote;

	return totalWrote;
}


