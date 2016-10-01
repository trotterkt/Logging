#ifndef Default_ICache_H
#define Default_ICache_H

#include <boost/regex.hpp>

 
class ICache 
{
public:
	template<class Subject>
	void insert(Subject subject);
	
};


template<class Subject>
void ICache::insert(Subject subject)
{

}

#endif
