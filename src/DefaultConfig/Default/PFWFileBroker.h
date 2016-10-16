#ifndef Default_PFWFileBroker_H
#define Default_PFWFileBroker_H
#include "Default\PFWBroker.h"
#include <iostream>
#include <sstream>
#include <boost/filesystem/fstream.hpp>


using namespace boost::filesystem;

class PFWFileBroker : public PFWBroker
{
public:
	PFWFileBroker();
	~PFWFileBroker();

	//:TODO: Try templated method (This appears to work only when implementation defined in the interface file)
	template<class Subject>
	void putObject(Subject* subject) //:TODO: ****There may no longer be a need for the subject object***
	{ 		
		
		// get the length of the buffer
		size_t length = myTranslatedBuffer.str().length();

		//myTranslatedBuffer.seekp(0, std::ios::end);
		//std::streamoff end = myTranslatedBuffer.tellp();
       
		myOutFileStreamPtr->write(myTranslatedBuffer.str().c_str(), length);

		// Write these contents to the file
		myOutFileStreamPtr->flush();

		// after object has been directed to persistence, clear
		// the buffer
		myTranslatedBuffer.str("");
	}

	//:TODO: Cannot apply templated method here as in putObject(...) method. Cannot be resolved
	// during compilation. Returned void pointer to be reinterpreted via materializeSubject()
	void* objectWith(std::string oid)
	{
		//:TODO: Implement via Boost::Qi

		// first check for instance in the cache
		if (isMaterialized(oid))
		{
			// return the cache instance

			// Stub
			return 0;
		}
		else
		{
			// search persistent file representation
			return materializeWith(oid); 
		}
	}

	virtual ICache* materializeAll() = 0;
	
	virtual void reset();


protected:
	virtual void resetCache() = 0;

	boost::filesystem::ofstream* myOutFileStreamPtr;
	boost::filesystem::ifstream* myInFileStreamPtr;
	std::ostringstream myTranslatedBuffer;
	
	void* myTranslatedObject;
	int myOpenMode;
};

#endif
