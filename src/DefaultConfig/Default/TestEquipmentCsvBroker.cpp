//## auto_generated
#include "Default\TestEquipmentCsvBroker.h"
#include "Default\Cache.h"
#include "Default\ObjectIdentification.h"

#include <iostream>
#include <sstream>




TestEquipmentCsvBroker::TestEquipmentCsvBroker()
{
	myOpenMode = 0;

	std::string fullPath;
	DataNaming::instance().getExcelDataLogFileName(fullPath);
	myOutFileStreamPtr = new boost::filesystem::ofstream(fullPath.c_str(), myOpenMode);

	// Do not anticiplate reading from persistence for this broker
	myInFileStreamPtr = NULL;

	// No cache is established for this broker
}


TestEquipmentCsvBroker::~TestEquipmentCsvBroker()
{
	if (myOutFileStreamPtr)
	{
		myOutFileStreamPtr->close();
		delete myOutFileStreamPtr;
	}

}


void* TestEquipmentCsvBroker::materializeWith(std::string oid)
{
	// materialization is not applicable for this broker
	// so throw exception if called

	//:TODO: implement execeptions

	return NULL;
}

ICache* TestEquipmentCsvBroker::materializeAll()
{
	// materialization is not applicable for this broker
	// so throw exception if called

	//:TODO: implement execeptions

	return NULL;
}


void* TestEquipmentCsvBroker::objectWith(std::string oid)
{
	// materialization is not applicable for this broker
	// so throw exception if called

	//:TODO: implement execeptions

	return NULL;
}




void TestEquipmentCsvBroker::translate(double subject, std::string& converted)
{
	//:TODO: Implement via Boost::Karma
}

void TestEquipmentCsvBroker::translate(DataPacket subject)
{
	std::ostringstream csvRecordBuffer;
	// fill buffer contained within the abstract FileBroker.
	// when putObject() called, direct this buffer to the
	// output file. 

	CCSDS_PrimaryHeader_struct header = subject.getPrimaryHeader();
	CCSDS_SecondaryHeader_struct secondHeader = subject.getSecondaryHeader();
	int dataWordSize = subject.getNumberOfDataWords();

	csvRecordBuffer << std::hex << header.myPacketIdentification << ","
		            << header.myPacketSequenceControl << ","
					<< std::dec << header.myPacketDataLength << ",";
	
	if ((header.myPacketIdentification & SecondaryHeaderIndicationMask) >> SecondaryHeaderIndicationBit)
	{
		csvRecordBuffer << subject.getTime().getDay() <<  "," << int(subject.getTime().getMilliSeconds()) << "," << int(subject.getTime().getMicroSeconds());
	}
	else
	{
		csvRecordBuffer << ",,,";
	}

	for (int index = 0; index < dataWordSize; index++)
	{
		uint16_t* dataWord = subject.getDataWords();
		csvRecordBuffer << std::dec << "," << int(dataWord[index]);
	}

	csvRecordBuffer << std::endl;

	myTranslatedBuffer.write(csvRecordBuffer.str().c_str(), csvRecordBuffer.str().length());
}

void TestEquipmentCsvBroker::reset()
{
	// close current, then establish new streams
	if (myOutFileStreamPtr)
	{
		myOutFileStreamPtr->close();
		delete myOutFileStreamPtr;
	}

	std::string fullPath("");

	DataNaming::instance().getExcelDataLogFileName(fullPath);
	myOutFileStreamPtr = new boost::filesystem::ofstream(fullPath.c_str(), myOpenMode);
}




