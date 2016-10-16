//## auto_generated
#include "Default\DataPacket.h"
 
DataPacket::DataPacket(unsigned char* buffer) : myDataWords(0)
{
	// assign object state, while verifying content
	if(buffer)
	{
		memcpy(&myHeader, buffer, sizeof(myHeader));

		uint16_t apid = myHeader.myPacketIdentification & ApidMask;				

		// based on examination of example data, this is the number 
		// of data bytes
		// data words are not applicable for TOD
		if (apid != TimeOfDay_APID)
		{
			myNumberDataWords = myHeader.myPacketDataLength + 1;
		}
		else
		{
			myNumberDataWords = 0; // This data found to be incorrectly filled for TimeOfDay_APID
			myHeader.myPacketDataLength = 0;
		}

		bool secondaryHeaderFlag(false);
		if((myHeader.myPacketIdentification & SecondaryHeaderIndicationMask) >> SecondaryHeaderIndicationBit)
		{
			memcpy(&mySecondaryHeader, 
				   &buffer[sizeof(myHeader)], 
				   sizeof(mySecondaryHeader));
			
			secondaryHeaderFlag = true;

			// data words are not applicable for TOD
			if (apid != TimeOfDay_APID)
			{
				myNumberDataWords -= (sizeof(mySecondaryHeader));
			}
		}
		else
		{
			memset(&mySecondaryHeader, 0, sizeof(mySecondaryHeader));
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
			else
			{
				memcpy(myDataWords,
					&buffer[sizeof(myHeader)],
					(sizeof(uint16_t)*myNumberDataWords));

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
	myNumberDataWords = right.myNumberDataWords;
	myDataWords = 0;

	// convert 2nd header to a time
	myTime = mySecondaryHeader;

	if(myNumberDataWords > 0)
	{
		myDataWords = new uint16_t [myNumberDataWords];
		memcpy(myDataWords, right.myDataWords, sizeof(uint16_t) * myNumberDataWords); 
	}
}

DataPacket& DataPacket::operator=(const DataPacket& right)
{
	memcpy(&myHeader, &right.myHeader, sizeof(myHeader));
	memcpy(&mySecondaryHeader, &right.mySecondaryHeader, sizeof(mySecondaryHeader));
	myNumberDataWords = right.myNumberDataWords;
	myDataWords = 0;

	if (myNumberDataWords > 0)
	{
		myDataWords = new uint16_t[myNumberDataWords];
		memcpy(myDataWords, right.myDataWords, sizeof(uint16_t) * myNumberDataWords);
	}

	return *this;
}

DataPacket::DataPacket() : myDataWords(0)
{

}

