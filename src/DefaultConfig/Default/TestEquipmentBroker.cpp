//## auto_generated
#include "Default\TestEquipmentBroker.h"
#include "Default\Cache.h"

//#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/include/karma.hpp>
//#include <boost/lambda/lambda.hpp>
//#include <boost/bind.hpp>

#include <iostream>
#include <sstream>


TestEquipmentBroker::TestEquipmentBroker()
{
	//:TODO: Stub file creation
	myOutFileStreamPtr = new boost::filesystem::ofstream("ste.log", _IOSbinary);
	//myInFileStreamPtr = new boost::filesystem::ifstream("W:\\shared_libs.vbt\\Logging\\Legacy Log Files\\301_2016_07_19_09_58_48_000_27_52_TEST.log", _IOSbinary); // :TODO: This will probabily get
	myInFileStreamPtr = new boost::filesystem::ifstream("C:\\Users\\Keir\\NGSysTE\\Logging\\Legacy Log Files\\301_2016_07_19_09_58_48_000_27_52_TEST.log", _IOSbinary); // :TODO: This will probabily get
																																								   // defined elsewhere
	// Attach the nessassary cache(s)
	itsICache.push_back(new Cache<DataPacket>(100)); //:TODO: how big should the buffer be?
}

TestEquipmentBroker::~TestEquipmentBroker()
{
	myOutFileStreamPtr->close();
	delete myOutFileStreamPtr;
	
	myInFileStreamPtr->close();
	delete myInFileStreamPtr;

	// destroy the cache object(s)

}

//void TestEquipmentBroker::putObject(void* subject)
//{
	//:TODO: Implement via Boost::Karma

	//myFileStreamPtr->write("test write\n", 10); //:TODO: Stub

//}

//:TODO: Try templated method
//template<class Subject>
//void TestEquipmentBroker::putObject(Subject* subject)
//{
//	myFileStreamPtr->write("test write\n", 10); //:TODO: Stub
//}

//void TestEquipmentBroker::putObject(int* subject)
//{
//	//myFileStreamPtr->write("test write\n", 10); //:TODO: Stub
//}


void* TestEquipmentBroker::materializeWith(boost::regex oid)
{
	// need to search persistence, create an instance of the Subject,
	// add this to the Cache, then return the instance from the Cache

		// Unique DataPacket types might be distinguished as follows
		/*
		switch (apid)
		{
			case HardwareError_APID:
			case CalibrationTestEquipment_APID:
			case HouskeepingEngineering_APID:
			case HotCalEngineering_APID:
			case PassiveTelemtery_APID:
			case VoltagesAndCurrents_APID:
			case SteError_APID:
			case Mark_APID:
			case TimeOfDay_APID:

				break;
		}
		*/

	boost::filesystem::ofstream::pos_type currentLocation = myInFileStreamPtr->tellg();

	CCSDS_PrimaryHeader_struct header;
	myInFileStreamPtr->read(reinterpret_cast<char*>(&header), sizeof(CCSDS_PrimaryHeader_struct));

	// return to the previous position
	myInFileStreamPtr->seekg(currentLocation);

    // Figure out the total length of the packet
	unsigned int packetLength(sizeof(CCSDS_PrimaryHeader_struct));
	packetLength += (header.myPacketDataLength + 1);

	unsigned char* packetBuffer = new unsigned char[packetLength];
	myInFileStreamPtr->read(reinterpret_cast<char*>(packetBuffer), packetLength);

	//DataPacket* packet = new DataPacket(packetBuffer); // This instance is directed to the cache
													   // the pointer should be deleted when the cache is destroyed
	static DataPacket packet(packetBuffer); // This instance is directed to the cache
								            // the pointer should be deleted when the cache is destroyed
	delete [] packetBuffer;

	Cache<DataPacket>* cachePtr = reinterpret_cast<Cache<DataPacket>*>(itsICache[0]);


	// Try out
	//*************************************
	//std::vector< DataPacket > testCache;
	//testCache.push_back(*packet);
	//DataPacket newPacket(testCache[0]);
	//*************************************

	cachePtr->insert(std::pair<boost::regex, DataPacket>(oid, packet));
	
	// pull back out the same object entered into the task and
	// return it
	packet = cachePtr->getSubject(oid); 

	return &packet;
}

/*
void* TestEquipmentBroker::objectWith(boost::regex oid)
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

		// Stub
		return 0; 
	}
}
*/


void TestEquipmentBroker::translate(int subject) 
{ 

//	using boost::spirit::karma::int_;
//    using boost::spirit::karma::generate;

	//:TODO: Implement via Boost::Karma
//    using namespace boost::spirit;

        //std::string generated;
    //std::back_insert_iterator<std::string> outiter(converted);

    //[karma_tutorial_attach_actions1
    //generate(outiter, '{' << int_[subject] << '}');
    //generate(outiter, '{' << subject << '}');
    //]

        //std::cout << "Simple function: " << generated << std::endl;


}  

void TestEquipmentBroker::translate(double subject, std::string& converted) 
{ 
	//:TODO: Implement via Boost::Karma
}  

void TestEquipmentBroker::translate(DataPacket subject)
{
	//:TODO: May investigate further - Implement via Boost::Karma

	// fill buffer contained within the abstract FileBroker.
	// when putObject() called, direct this buffer to the
	// output file. 

	CCSDS_PrimaryHeader_struct header = subject.getPrimaryHeader();
	CCSDS_SecondaryHeader_struct secondHeader = subject.getSecondaryHeader();
	size_t dataWordSize = subject.getNumberOfDataWords() * sizeof(uint16_t);
	
	myTranslatedBuffer.write(reinterpret_cast<const char*>(&header), sizeof(CCSDS_PrimaryHeader_struct));
	myTranslatedBuffer.write(reinterpret_cast<const char*>(&secondHeader), sizeof(CCSDS_SecondaryHeader_struct));
	myTranslatedBuffer.write(reinterpret_cast<const char*>(subject.getDataWords()), dataWordSize);
}
