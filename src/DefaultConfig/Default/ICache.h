#ifndef Default_ICache_H
#define Default_ICache_H

#include <string>


class ICache 
{
public:
	template<class Subject>
	void insert(Subject subject);

	virtual bool isMaterialized(std::string oid) = 0;
	
};


template<class Subject>
void ICache::insert(Subject subject)
{

}


#endif
