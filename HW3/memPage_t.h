#ifndef MemPage_t_H_
#endif MemPage_t_H_

class memPage_t{

public:

	//CTOR & DTOR
	memPage_t();										//default CTOR
	~memPage_t();										//DTOR

	void setPosition(int newAddress);					//set current position in memory page
	memPage_t* GetPosition() const;						//get current position in memory page
	
	//page status information
	bool IsPageEmpty();									//is page empty
	bool IsPageFull();									//is page Full
	int actualSize();									//actual size of a page(how many bytes really written in page)
	int Capacity();										//capacity of a page (length)

	//TODO: add function								//read data from page
	//TODO: add function								//write data to page

	memPage_t* NextPage();								//a pointer to the next page
	memPage_t* PreviousPage();							//a pointer to the previous page
	

private:

	//Disabling copy
	memPage_t(const memPage_t &m);						//disable copy CTOR
	const memPage_t &operator=(const memPage_t &m);		//disable assignment operator



};