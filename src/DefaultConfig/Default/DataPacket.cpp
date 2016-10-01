//## auto_generated
#include "Default\DataPacket.h"
 
DataPacket::DataPacket(unsigned char* buffer)
{
	// assign object state, while verifying content
	if(buffer)
	{
		memcpy(&myHeader, buffer, sizeof(myHeader));

		uint16_t apid = myHeader.myPacketIdentification & ApidMask;
		uint16_t packetDataLength = myHeader.myPacketDataLength;
				

		// based on examination of example data, this is the number 
		// of data bytes
		myNumberDataWords = myHeader.myPacketDataLength + 1;

		bool secondaryHeaderFlag(false);
		if((myHeader.myPacketIdentification & SecondaryHeaderIndicationMask) >> SecondaryHeaderIndicationBit)
		{
			memcpy(&mySecondaryHeader, 
				   &buffer[sizeof(myHeader)], 
				   sizeof(mySecondaryHeader));
			myNumberDataWords -= (sizeof(mySecondaryHeader));
			secondaryHeaderFlag = true;
		}

		// change to number of words representation
		myNumberDataWords /= sizeof(uint16_t);

		if(myNumberDataWords > 0)
		{
			myDataWords = new uint16_t [myNumberDataWords];

			if(secondaryHeaderFlag)
			{
				memcpy(myDataWords, 
					   &buffer[sizeof(myHeader) + sizeof(mySecondaryHeader)], 
					   (sizeof(uint16_t)*myNumberDataWords));

				myTime = mySecondaryHeader;
			}
		}

	}

}

DataPacket::~DataPacket()
{
	if(myDataWords)
	{
		delete [] myDataWords;
	}
}

DataPacket::DataPacket(const DataPacket& right) : myTime(right.myTime), myNumberDataWords(right.myNumberDataWords)
{
	memcpy(&myHeader, &right.myHeader, sizeof(myHeader));
	memcpy(&mySecondaryHeader, &right.mySecondaryHeader, sizeof(mySecondaryHeader));	

	if(myNumberDataWords > 0)
	{
		myDataWords = new uint16_t [myNumberDataWords];
		memcpy(myDataWords, right.myDataWords, sizeof(uint16_t) * myNumberDataWords); 
	}
}

