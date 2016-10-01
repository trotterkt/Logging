#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
#ifndef Default_PFWBroker_H
#define Default_PFWBroker_H
 
#include <boost/regex.hpp>
//## auto_generated
#include <string>
//## auto_generated
#include <algorithm>
//## auto_generated
#include <vector>
//## auto_generated
#include <iterator>

#include "Default\ICache.h"

class PFWBroker
{
public :

    PFWBroker();
    
    ~PFWBroker();
    
    virtual bool isMaterialized();
    
    virtual void materializeAll();
    
    virtual void* materializeWith(boost::regex oid) = 0;
    
	template<class Subject>
	void putObject(Subject* subject) = 0;
	
	// Cannot apply templated method as with putObject
	virtual void* objectWith(boost::regex oid) = 0;

    template<class Subject>
	void setCacheType(Subject type, unsigned long bufferSize=50) 
	{
	   // :TODO: Check the current collection of cache for one
	   // which is consistent with the desired type (parsing the OID might work)

	   // :TODO: the buffer size also needs to be determined

		// = new Cache<type, bufferSize>
	} 

	template<class Subject>
	void translate(Subject subject) = 0; 

protected :
	//:TODO: is this relevent?
    unsigned long myRecordsMaterialized;

	// there might be different cache objects to handle different types
    std::vector<ICache*> itsICache;

};

#endif
