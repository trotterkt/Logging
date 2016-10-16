//## auto_generated
#include "Default\PFWFileBroker.h"
 


PFWFileBroker::PFWFileBroker() : myTranslatedBuffer(std::stringstream::in | std::stringstream::out | std::stringstream::binary),
                                 myTranslatedObject(0)
{

}

PFWFileBroker::~PFWFileBroker()
{

}

void PFWFileBroker::reset()
{
	// close current, then establish new streams
	if (myOutFileStreamPtr)
	{
		myOutFileStreamPtr->close();
		delete myOutFileStreamPtr;
	}

	if (myInFileStreamPtr)
	{
		myInFileStreamPtr->close();
		delete myInFileStreamPtr;
	}

	if (itsICache.size())
	{
		delete itsICache[0];
		itsICache.clear();
	}

	std::string fullPath("");
	
	// sometimes want Excel call - call derived reset() version
	DataNaming::instance().getDataLogOutFileName(fullPath);
	myOutFileStreamPtr = new boost::filesystem::ofstream(fullPath.c_str(), myOpenMode);

			
	DataNaming::instance().getDataLogInFileName(fullPath);
	if (fullPath.length())
	{
		myInFileStreamPtr = new boost::filesystem::ifstream(fullPath.c_str(), myOpenMode);
	}

	// Attach the nessassary cache(s)
	// The derived classes will define this
	resetCache();
}