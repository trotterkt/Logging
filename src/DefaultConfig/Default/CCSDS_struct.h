#ifndef Default_CCSDS_struct_H
#define Default_CCSDS_struct_H

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

#include <stdint.h>
 

static const uint16_t PacketLengthMask(0x0FFFF);
static const uint16_t PacketSequenceMask(0x03FFF);
static const uint16_t ApidMask(0x03FF);
static const uint16_t SecondaryHeaderIndicationMask(0x0800);
static const uint16_t SecondaryHeaderIndicationBit(11);

struct CCSDS_PrimaryHeader_struct
{
	// Primary Header
	uint16_t myPacketIdentification;
	uint16_t myPacketSequenceControl;
	uint16_t myPacketDataLength;
};

struct CCSDS_SecondaryHeader_struct
{
	// Secondary Header
	uint16_t myDay;
	uint16_t myMilliSeconds_word1;
	uint16_t myMilliSeconds_word2;
	uint16_t myMicroSeconds;
};

#endif
