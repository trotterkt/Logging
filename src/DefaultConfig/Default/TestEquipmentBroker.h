#ifndef Default_TestEquipmentBroker_H
#define Default_TestEquipmentBroker_H

#include "Default\PFWFileBroker.h"
#include "Default\Singleton.h"
#include "Default\DataPacket.h"

class TestEquipmentBroker : public PFWFileBroker, public Singleton<TestEquipmentBroker>
{
public:
	TestEquipmentBroker();
	~TestEquipmentBroker();

	void* materializeWith(boost::regex oid);

	//void* objectWith(boost::regex oid);

//protected:
	void translate(int subject); 
	void translate(double subject, std::string& converted); 
	void translate(DataPacket subject);

};

#endif
