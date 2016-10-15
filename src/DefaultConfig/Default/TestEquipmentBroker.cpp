//## auto_generated
#include "Default\TestEquipmentBroker.h"
#include "Default\Cache.h"
#include "Default\ObjectIdentification.h"

//#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/include/karma.hpp>
//#include <boost/lambda/lambda.hpp>
//#include <boost/bind.hpp>

#include <iostream>
#include <sstream>




TestEquipmentBroker::TestEquipmentBroker()
{
	// make sure at least one instance has been created
	// :TODO: might better belong in another place
	//DataNaming::instance();

	std::string fullPath;
	DataNaming::instance().getDataLogOutFileName(fullPath);
	myOutFileStreamPtr = new boost::filesystem::ofstream(fullPath.c_str(), _IOSbinary);

	DataNaming::instance().getDataLogInFileName(fullPath);
	myInFileStreamPtr = new boost::filesystem::ifstream(fullPath.c_str(), _IOSbinary); 

	//:TODO: Stub file creation
	//myOutFileStreamPtr = new boost::filesystem::ofstream("ste.log", _IOSbinary);
	//myInFileStreamPtr = new boost::filesystem::ifstream("W:\\shared_libs.vbt\\Logging\\Legacy Log Files\\301_2016_07_19_09_58_48_000_27_52_TEST.log", _IOSbinary); // :TODO: This will probabily get
	//myInFileStreamPtr = new boost::filesystem::ifstream("C:\\Users\\Keir\\NGSysTE\\Logging\\Legacy Log Files\\301_2016_07_19_09_58_48_000_27_52_TEST.log", _IOSbinary); // :TODO: This will probabily get
																																								   // defined elsewhere
	// Attach the nessassary cache(s)
	itsICache.push_back(new Cache<DataPacket>(100)); //:TODO: how big should the buffer be?
}

void TestEquipmentBroker::reset() 
{

	//DataNaming name;

	// close current, then establish new streams
	if(myOutFileStreamPtr)
	{
		myOutFileStreamPtr->close();
		delete myOutFileStreamPtr;
	}
	
	if(myInFileStreamPtr)
	{
		myInFileStreamPtr->close();
		delete myInFileStreamPtr;
	}

	delete itsICache[0];
	itsICache.clear();

	std::string fullPath;
	DataNaming::instance().getDataLogOutFileName(fullPath);
	myOutFileStreamPtr = new boost::filesystem::ofstream(fullPath.c_str(), _IOSbinary);

	DataNaming::instance().getDataLogInFileName(fullPath);
	myInFileStreamPtr = new boost::filesystem::ifstream(fullPath.c_str(), _IOSbinary); 

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
	delete itsICache[0];
	itsICache.clear();
}


void* TestEquipmentBroker::materializeWith(std::string oid)
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

	unsigned char packetBuffer[MaximumRawPacketSize] = { 0 };


    getNextPacket(packetBuffer);

	static DataPacket returnPacket(packetBuffer); // This instance is directed to the cache
								                  // the pointer should be deleted when the cache is destroyed
	
	// need to do this to update the static copy
	DataPacket packet(packetBuffer);
	returnPacket = packet;

	Cache<DataPacket>* cachePtr = reinterpret_cast<Cache<DataPacket>*>(itsICache[0]);

	cachePtr->insert(std::pair<std::string, DataPacket>(oid, returnPacket));
	
	// pull back out the same object entered into the task and
	// return it
	returnPacket = cachePtr->getSubject(oid);

	return &returnPacket;
}

ICache* TestEquipmentBroker::materializeAll()
{
	unsigned char packetBuffer[MaximumRawPacketSize] = {0};
	Cache<DataPacket>* cachePtr = reinterpret_cast<Cache<DataPacket>*>(itsICache[0]);
	long record(0);

	while (getNextPacket(packetBuffer))
	{
		DataPacket packet(packetBuffer);
		std::string oid = getDataPacketOid(packetBuffer, record);
		
		std::cout << "Record #" << std::dec << record
			<< " APID(" << std::hex << ((packet.getPrimaryHeader().myPacketIdentification) & ApidMask)
			<< ") Sequence #" << std::dec << ((packet.getPrimaryHeader().myPacketSequenceControl) & PacketSequenceMask)
			<< " OID=" << oid.c_str() << std::endl;
		bool successFlag = cachePtr->insert(std::pair<std::string, DataPacket>(getDataPacketOid(packetBuffer, record), packet));
		record++;

		if (!successFlag)
		{
			std::cout << "bad insert" << std::endl; //:TODO: change to exception
		}
		
		//debug
		//*****************************
		//if(record > 10) break;
		//*****************************
	}

	/*
	//:TODO: This call should probabliy be launched
	// from main()
	//***********************************************

	// This becomes unnessassary, since now the OID referes
	// to the relative position
	Sorting sort;
	std::vector< std::pair<std::string, DataPacket> > sortedBuffer = cachePtr->getByValueCollection(&sort);
	record = 0;

	for (std::vector<std::pair<std::string, DataPacket>>::const_iterator i = sortedBuffer.begin(); i != sortedBuffer.end(); ++i)
	{
		DataPacket packet((&*i)->second);
	    short packetId = (packet.getPrimaryHeader().myPacketIdentification) & ApidMask;
	    short packetSeq = (packet.getPrimaryHeader().myPacketSequenceControl) & PacketSequenceMask;
		int day = packet.getTime().getDay();
		long long milliSec = packet.getTime().getMilliSeconds();
		int microSec = packet.getTime().getMicroSeconds();
		std::cout << "Record #" << std::dec << record
			      << " APID(" << std::hex << int(packetId)
			      << ") Sequence #" << std::dec << int(packetSeq) 
			      << " Time " << day << ":" << milliSec << ":" << microSec << std::endl;

		record++;
	}
	//***********************************************
	*/

	return cachePtr;
}


void* TestEquipmentBroker::objectWith(std::string oid)
{ 
	//:TODO: Implement via Boost::Qi

	// first check for instance in the cache
	if (isMaterialized(oid))
	{
		Cache<DataPacket>* cachePtr = reinterpret_cast<Cache<DataPacket>*>(itsICache[0]);

		static DataPacket returnPacket;
		returnPacket = cachePtr->getSubject(oid);

		return (&returnPacket);
	}
	else
	{
			// search persistent file representation
			return materializeWith(oid); 
	}
}



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

	if ((header.myPacketIdentification & SecondaryHeaderIndicationMask) >> SecondaryHeaderIndicationBit)
	{
		myTranslatedBuffer.write(reinterpret_cast<const char*>(&secondHeader), sizeof(CCSDS_SecondaryHeader_struct));
	}
	
	myTranslatedBuffer.write(reinterpret_cast<const char*>(subject.getDataWords()), dataWordSize);
}

bool TestEquipmentBroker::getNextPacket(unsigned char* packetBuffer)
{
	// check to see if a read would be past EOF
	// EOF is not set until we actually try
	myInFileStreamPtr->peek();  
	if(myInFileStreamPtr->eof())
	{
		return false;
	}

	boost::filesystem::ofstream::pos_type currentLocation = myInFileStreamPtr->tellg();

	
	CCSDS_PrimaryHeader_struct header;
	myInFileStreamPtr->read(reinterpret_cast<char*>(&header), sizeof(CCSDS_PrimaryHeader_struct));
	

	// return to the previous position
	myInFileStreamPtr->seekg(currentLocation);
	
	uint16_t apid = header.myPacketIdentification & ApidMask;
	unsigned int packetLength(sizeof(CCSDS_PrimaryHeader_struct));

	// Check to see that the current packet is not TimeOfDay_APID,
	// which if it is does not have associated data words
	if (apid != TimeOfDay_APID)
	{
		// Figure out the total length of the packet
		packetLength += (header.myPacketDataLength + 1);
	}
	else
	{
		packetLength += sizeof(CCSDS_SecondaryHeader_struct);
	}
		
	myInFileStreamPtr->read(reinterpret_cast<char*>(packetBuffer), packetLength);

	// as of the final call the stream should be located at the next raw packet
	return true;
}

