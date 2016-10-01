#ifndef Default_ObjectIdentification_H
#define Default_ObjectIdentification_H

#include <boost/regex.hpp>
#include <ostream>
#include "Default\CCSDS_struct.h"

// Propose that establishing the appropriate OID should be
// performed outside of the associated Subject object. Intent
// is to not pollute subject classes with concepts of a OID.
// Inline functions will define these which may make
// unique assuptions about OID format


inline boost::regex getDataPacketOid(unsigned char* packetBuffer)
{
	CCSDS_PrimaryHeader_struct header;
	memcpy(&header, packetBuffer, sizeof(header));
	uint16_t apid = header.myPacketIdentification & ApidMask;
	uint16_t packetDataLength = header.myPacketDataLength;
	uint16_t packetSequence = header.myPacketSequenceControl & PacketSequenceMask;

	std::ostringstream buffer;
	buffer << std::hex << apid << ":" << packetSequence << std::endl;

	boost::regex oid(buffer.str().c_str());

	return oid;
}


#endif
