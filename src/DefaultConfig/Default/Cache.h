#ifndef Default_Cache_H
#define Default_Cache_H

#include <boost/circular_buffer.hpp>
#include "Default\ICache.h"
#include "Default\DataPacket.h"
#include "Default\Sorting.h"
#include <algorithm>
#include <string>




template <class Subject> 
class Cache : public ICache 
{
public:
	Cache(unsigned long bufferSize);
	
	bool insert(std::pair<std::string, Subject> mappedPair);

	Subject getSubject(std::string oid);

    bool isMaterialized(std::string oid);

	// This is an indirect use of function pointer to sort the collection. The caller can
	// use polymorphic behaviour to define the sorting algorithm
	std::vector< std::pair<std::string, Subject> >& getByValueCollection(Sorting* algorithm);

private:

	std::map< std::string, Subject > myBuffer;
	
	std::vector< std::pair<std::string, Subject> > myValueSortedBuffer;

	Cache();
};

template<class Subject> 	// :TODO: is bufferSize still relevant?
Cache<Subject>::Cache(unsigned long bufferSize)
{ 
}

// Although this method is slow, do not anticipate needing to 
// utilize in normal operation since packets would normally
// be logged upon receipt
template<class Subject>
std::vector< std::pair<std::string, Subject> >& Cache<Subject>::getByValueCollection(Sorting* algorithm)
{
	// first get rid of anything that might be there
	myValueSortedBuffer.clear();

	std::copy(myBuffer.begin(), myBuffer.end(), std::back_inserter(myValueSortedBuffer));

	std::sort(myValueSortedBuffer.begin(), myValueSortedBuffer.end(), *algorithm);

	return myValueSortedBuffer;
}

template<class Subject> 	
bool Cache<Subject>::insert(std::pair<std::string, Subject> mappedPair)
{
	std::pair<std::map<std::string, Subject>::iterator, bool> successfullInsert;

	successfullInsert = myBuffer.insert(mappedPair);

    return successfullInsert.second;
}

template<class Subject>
Subject Cache<Subject>::getSubject(std::string oid)
{
	return myBuffer.at(oid);
}

template<class Subject>
bool Cache<Subject>::isMaterialized(std::string oid)
{
	if(myBuffer.count(oid))
	{
			return true;
	}
	else
	{
			return false;
	}
}


#endif
