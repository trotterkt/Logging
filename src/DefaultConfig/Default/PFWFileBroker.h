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
	
		//std::ostringstream message;
		//message << "test write from abstract broker ==> " << *subject << std::endl;
		//myFileStreamPtr->write(message.str().c_str(), message.str().size()); //:TODO: Stub

		// get the length of the buffer
		myTranslatedBuffer.seekp(0, std::ios::end);
		std::streamoff end = myTranslatedBuffer.tellp();
       
		myOutFileStreamPtr->write(myTranslatedBuffer.str().c_str(), end);

		// Write these contents to the file
		myOutFileStreamPtr->flush();

		// after object has been directed to persistence, clear
		// the buffer
		myTranslatedBuffer.clear();
	}

	//:TODO: Cannot apply templated method here as in putObject(...) method. Cannot be resolved
	// during compilation. Returned void pointer to be reinterpreted via materializeSubject()
	void* objectWith(boost::regex oid)
	{
		//:TODO: Implement via Boost::Qi

		// first check for instance in the cache
		if (isMaterialized())
		{

			// Stub
			return 0;
		}
		else
		{
			// search persistent file representation
			return materializeWith(oid); 
		}
	}

	virtual void materializeAll();

protected:
	boost::filesystem::ofstream* myOutFileStreamPtr;
	boost::filesystem::ifstream* myInFileStreamPtr;
	std::ostringstream myTranslatedBuffer;
	
	void* myTranslatedObject;


};

#endif
