#ifndef MemPool_t_H_ 
#endif MemPool_t_H_

class memPool_t{

public:

	//Static Member
	static int PageSize;

	//CTOR & DTOR
	memPool_t();										//default CTOR - 1 empty page
	memPool_t(int pageNumber);							//CTOR from number of empty page to initialize
	~memPool_t();										//DTOR

	//public methods
	int GetCurrentPosition();							//get the current position in the memPool_t (how many bytes really written in memPool_t
	void SetCurrentPosition(int newPosition);			//set the current position (between 0-PageSize)
	//TODO: T& read(T &t, int sizeOfT);					//read data from manager
	//TODO: void write(T &t, int sizeOfT);				//write data to manager
	void CreateMemPage();								//create memory page upon demand

	//memPool information
	bool IsEmpty();										//is memPool is Empty?
	int GetActualSize();								//actual size of the object memPool_t
	int GetCapacity();									//capacity of the manager
	int GetNumberOfPages();								//get the number of memory page
	memPage_t* GetFirstMemPage();						//get pointer to the first memory page
	memPage_t* GetLastMemPgae();						//get pointer to the last memory page
	memPage_t* GetCurrentMemPage();						//get pointer to the current memory page

	//default size of memPage
	int GetDefaultPageSize();							//get default memory page size
	void SetDefaultPageSize();							//set default memory page size

private:

	//disable copy
	memPool_t(const memPool_t &m);						//disable copy CTOR
	const memPool_t &operator=(const memPool_t &m);		//disable assignment operator

};