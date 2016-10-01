#ifndef Default_DataPacket_H
#define Default_DataPacket_H

#include "Default\Time.h"

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## auto_generated
#include <string>
//## auto_generated
#include <algorithm>
 
#include "Default\CCSDS_struct.h"
#include "Default\Time.h"

const uint16_t HardwareError_APID(0x21F);
const uint16_t CalibrationTestEquipment_APID(0x21C);
const uint16_t HouskeepingEngineering_APID(0x207);
const uint16_t HotCalEngineering_APID(0x208);
const uint16_t PassiveTelemtery_APID(0x214);
const uint16_t VoltagesAndCurrents_APID(0x219);
const uint16_t SteError_APID(0x21E);
const uint16_t Mark_APID(0x21A);
const uint16_t TimeOfDay_APID(0x100);

class DataPacket 
{
public:
	DataPacket(unsigned char* buffer);
	~DataPacket();
	DataPacket(const DataPacket& right);

	CCSDS_PrimaryHeader_struct getPrimaryHeader() { return myHeader; }
	CCSDS_SecondaryHeader_struct getSecondaryHeader() { return mySecondaryHeader; }
	uint16_t getNumberOfDataWords() { return myNumberDataWords;  }
	uint16_t* getDataWords() { return myDataWords;  }

private :
	DataPacket();
	CCSDS_PrimaryHeader_struct myHeader;
	CCSDS_SecondaryHeader_struct mySecondaryHeader;
	uint16_t myNumberDataWords;
	uint16_t* myDataWords; // array of data elements - at this time do not care about specific elements

protected:
	Time myTime;

};

#endif
