//## auto_generated
#include "MainLogging.h"
 
#include "Default\VirtualProxy.h"
#include "Default\TestEquipmentBroker.h"
#include "Default\DataPacket.h"
#include "Default\ObjectIdentification.h"
#include "Default\Cache.h"
#include "Default\DataNaming.h"
//======================================================================


int main(int argc, char* argv[]) {
    int status = 0;
    {

        //#[ configuration Logging::DefaultConfig 

		// COMLIB should provide a CCSDS packet in the form of a
		// unsigned char* and a buffer length. The OID is then
		// derived from the APID and from the header, the sequence
		// number in the packet set

		// test packet
		//============================================================================
		const uint16_t packetLength(20);
		unsigned char packet[packetLength];

		packet[0] = 0x1F; packet[1] = 0x0A; packet[2] = 0x00; packet[3] = 0xC0;
		packet[4] = 0x0D; packet[5] = 0x00; packet[6] = 0x01; packet[7] = 0x00;
		packet[8] = 0x00; packet[9] = 0x00; packet[10] = 0xFB; packet[11] = 0x00;
		packet[12] = 0x25; packet[13] = 0x16; packet[14] = 0x00; packet[15] = 0x00;
		packet[16] = 0x00; packet[17] = 0x00; packet[18] = 0x80; packet[19] = 0x00;
		Cache<DataPacket>* cachePtr(0);
		//============================================================================
			
		// This singleton represents file path information collected by the system
		// or LabVIEW GUI interface
		//DataNaming::instance();

		// Materialization
		//=========================================================
		{
			//:TODO: Need to determine if sequence numbers in all
			// data packets are unique, or as more likely, only
			// unique over the current log file. In which case,
			// I probabily want to utilize a Singleton to capture
			// the current data log file in effect. Associate this
			// with the Broker.

			// During debug - persistence target is 301_2016_07_19_09_58_48_000_27_52_TEST.log

			VirtualProxy<DataPacket, TestEquipmentBroker> testProxy;
			cachePtr = reinterpret_cast< Cache<DataPacket>* >(testProxy.create());

			// 21f:0
			std::string oid;
			oid.assign("21f:0");

			testProxy.create(oid);
			DataPacket dataPacket = *testProxy.getRealSubject();

			oid.assign("21f:1");
			testProxy.create(oid);
		    dataPacket = *testProxy.getRealSubject();
		}
		//=========================================================




		// Dematerialization
		//=========================================================
		// This would be the normal method to direct packets, as 
		// they come in, to persistence. However, the following loop 
		// is used since we are baseing the regenerated file on the 
		// original data
		//===========================================================
		//static long record(0);
		//
		//VirtualProxy<DataPacket, TestEquipmentBroker> testProxy;
		//
		//DataPacket dataPacket(packet);
		//
		//testProxy.create(getDataPacketOid(packet, record));
		//testProxy.putRealSubject(dataPacket);
		//record++;
		//===========================================================
		{

		    VirtualProxy<DataPacket, TestEquipmentBroker> testProxy;

			static long record(0);

			Sorting sort;
	        std::vector< std::pair<std::string, DataPacket> > sortedBuffer = cachePtr->getByValueCollection(&sort);

			// :TODO: reset the data log base filename -- would 
			// normally be initiated from the LabVIEW GUI or system
			//====================================================
			// During debug - persistence target is a time stamp uniquly named log
            DataNaming::instance().setBaseOutFileName();
			testProxy.reset();			
			//====================================================

			std::cout << "Generating persistent data..." << std::endl;

			for (std::vector<std::pair<std::string, DataPacket>>::const_iterator i = sortedBuffer.begin(); i != sortedBuffer.end(); ++i)
			{
				DataPacket packet((&*i)->second);
				
				CCSDS_PrimaryHeader_struct header = packet.getPrimaryHeader();
				testProxy.create(getDataPacketOid(reinterpret_cast<unsigned char*>(&header), record));
		        testProxy.putRealSubject(packet);

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

			//====================================================
			// Do it again
			// During debug - persistence target is a time stamp uniquly named log
			DataNaming::instance().setBaseOutFileName();
			testProxy.reset();
			//====================================================

			std::string oid;
			oid.assign("21f:0");

			testProxy.create(oid);
			DataPacket dataPacket = *testProxy.getRealSubject();
			testProxy.putRealSubject(dataPacket);

			oid.assign("21f:1");
			testProxy.create(oid);
		    dataPacket = *testProxy.getRealSubject();
			testProxy.putRealSubject(dataPacket);

		}

		//=========================================================

        //#]
    }
    return status;
}
