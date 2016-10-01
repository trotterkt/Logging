//## auto_generated
#include "Default\PFWFileBroker.h"
 
//:TODO: Try templated method
//template<class Subject>
//void PFWFileBroker::putObject(Subject* subject)
//{
//	myFileStreamPtr->write("test write\n", 10); //:TODO: Stub
//}

//void PFWFileBroker::putObject(void* subject)
//{
	//myFileStreamPtr->write("test write\n", 10); //:TODO: Stub
//}

PFWFileBroker::PFWFileBroker() : myTranslatedBuffer(std::stringstream::in | std::stringstream::out | std::stringstream::binary),
                                 myTranslatedObject(0)
{

}

PFWFileBroker::~PFWFileBroker()
{

}

void PFWFileBroker::materializeAll()
{

}



