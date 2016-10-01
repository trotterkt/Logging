//## auto_generated
#include "MainLogging.h"
 
#include "Default\VirtualProxy.h"
#include "Default\TestEquipmentBroker.h"
#include "Default\DataPacket.h"
#include "Default\ObjectIdentification.h"

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
		//============================================================================
		
		// Materialization
		//=========================================================
		{
			//:TODO: Need to determine if sequence numbers in all
			// data packets are unique, or as more likely, only
			// unique over the current log file. In which case,
			// I probabily want to utilize a Singleton to capture
			// the current data log file in effect. Associate this
			// with the Broker.

			VirtualProxy<DataPacket, TestEquipmentBroker> testProxy;
			testProxy.create();

			// 21f:0
			boost::regex oid;
			oid.assign("21f:0");

			testProxy.create(oid);
			DataPacket dataPacket = *testProxy.getRealSubject();
		}
		//=========================================================




		// Dematerialization
		//=========================================================
		{
			DataPacket dataPacket(packet);

			VirtualProxy<DataPacket, TestEquipmentBroker> testProxy;
			testProxy.create(getDataPacketOid(packet));
			testProxy.putRealSubject(dataPacket);
		}
		//=========================================================

        //#]
    }
    return status;
}
