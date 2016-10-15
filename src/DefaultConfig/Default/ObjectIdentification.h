#ifndef Default_ObjectIdentification_H
#define Default_ObjectIdentification_H


#include <ostream>
#include "Default\CCSDS_struct.h"

// Propose that establishing the appropriate OID should be
// performed outside of the associated Subject object. Intent
// is to not pollute subject classes with concepts of a OID.
// Inline functions will define these which may make
// unique assuptions about OID format


inline std::string getDataPacketOid(unsigned char* packetBuffer, long index)
{
	// There are several approches to forming the OID, but in since
	// there is a desire to keep track of the order of when a packet
	// arrived, a static index was used outside of the call


	CCSDS_PrimaryHeader_struct header;
	memcpy(&header, packetBuffer, sizeof(header));
	uint16_t apid = header.myPacketIdentification & ApidMask;

	// Optional OID contents
	//============================================================================
	//uint16_t packetDataLength = header.myPacketDataLength;
	//uint16_t packetSequence = header.myPacketSequenceControl & PacketSequenceMask;

	//bool secondaryHeaderFlag(false);
	//if ((header.myPacketIdentification & SecondaryHeaderIndicationMask) >> SecondaryHeaderIndicationBit)
	//{
	//	secondaryHeaderFlag = true;
	//}
	//============================================================================
	std::ostringstream buffer;

	buffer << std::hex << apid << ":" << std::dec << index;

	// Optional OID contents
	//============================================================================

	// For certain APID (207, 208, 209 and 210) that do not appear to have
	// a unique sequence number yet there is a secondary header
	// we will use the time as part of the OID
	//if (((apid == HouskeepingEngineering_APID) ||
	//	(apid == HotCalEngineering_APID) ||
	//	(apid == Unknown1_APID) ||
	//	(apid == Unknown2_APID)) &&
	//	secondaryHeaderFlag)
	//{
	//	buffer.str("");
	//
	//	CCSDS_SecondaryHeader_struct secHeader;
	//	memcpy(&secHeader, &packetBuffer[sizeof(CCSDS_PrimaryHeader_struct)], sizeof(secHeader));
	//
	//	Time oidTime;
	//	oidTime = secHeader;
	//
	//	int day = oidTime.getDay();
	//	long long mSec = oidTime.getMilliSeconds();
	//	int uSec = oidTime.getMicroSeconds();
	//
	//	buffer << std::hex << apid << ":" << std::dec << day << ":" << mSec << ":" << uSec;
	//}
	//============================================================================
	
	std::string oid(buffer.str().c_str());

	return oid;
}


#endif
