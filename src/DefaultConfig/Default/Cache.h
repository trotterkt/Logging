#ifndef Default_Cache_H
#define Default_Cache_H

#include <boost/circular_buffer.hpp>
#include <boost/regex.hpp>
#include "Default\ICache.h"


template <class Subject> 
class Cache : public ICache 
{
public:
	Cache(unsigned long bufferSize);
	
	bool insert(std::pair<boost::regex, Subject> mappedPair);

	Subject getSubject(boost::regex oid);

private:
	std::map< boost::regex, Subject > myBuffer;

	Cache();
};

template<class Subject> 	
Cache<Subject>::Cache(unsigned long bufferSize) // :TODO: is bufferSize still relevant?
{ 

}

template<class Subject> 	
bool Cache<Subject>::insert(std::pair<boost::regex, Subject> mappedPair)
{
	std::pair<std::map<boost::regex, Subject>::iterator, bool> successfullInsert;

	successfullInsert = myBuffer.insert(mappedPair);

    return successfullInsert.second;
}

template<class Subject>
Subject Cache<Subject>::getSubject(boost::regex oid)
{
	return myBuffer.at(oid);
}

#endif
