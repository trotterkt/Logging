/*
 * VirtualProxy.h
 *
 *  Created on: Sep 15, 2016
 *      Author: trottke1
 */

#ifndef DEFAULTCONFIG_DEFAULT_VIRTUALPROXY_H_
#define DEFAULTCONFIG_DEFAULT_VIRTUALPROXY_H_

#include <string>
#include <Default\ICache.h>

	
template<class Subject, class Broker> class VirtualProxy
{
	public:
		VirtualProxy() { }

		ICache* create(std::string oid = std::string(""));

		Subject* getRealSubject();
		void putRealSubject(Subject subject);

		Subject* operator->();

		// this resets by closing all files and caches defined
		// by the concrete Broker. Esentially restarting with
		// what would be performed on Broker construction since
		// they are singletons
		void reset() { 	myPFWBroker = &createBroker(); // this resets the templated pointer for the broker
                        myPFWBroker->reset(); 
		             }

	private:
		std::string myOid;
		Broker* myPFWBroker;

		Broker& createBroker()
		{
			return Broker::instance();
		}

		Subject* materializeSubject();

		void dematerializeSubject(Subject subject);

};


template<class Subject, class Broker>
ICache* VirtualProxy<Subject, Broker>::create(std::string oid)
{

	myOid = oid;
	myPFWBroker = &createBroker();

	ICache* cachePtr(0);
	
	// if a specific oid is not specified,
	// materilize all objects
	if (oid == std::string(""))
	{
		cachePtr = myPFWBroker->materializeAll();
	}

	return cachePtr;
}

	
template<class Subject, class Broker>
Subject* VirtualProxy<Subject, Broker>::getRealSubject()
{
	return materializeSubject();
}

	
template<class Subject, class Broker>
Subject* VirtualProxy<Subject, Broker>::materializeSubject()
{
	Subject* subject = reinterpret_cast<Subject*>(myPFWBroker->objectWith(myOid));
	return subject;
}

	
template<class Subject, class Broker>
void VirtualProxy<Subject, Broker>::putRealSubject(Subject subject)
{
	dematerializeSubject(subject);
}

	
template<class Subject, class Broker>
void VirtualProxy<Subject, Broker>::dematerializeSubject(Subject subject)
{
	myPFWBroker->translate(subject); // specific call here is not ideal 
	                                 // (would prefer virtual template method, based on subject type within putObject() -
	                                 // however this is not possible)
    myPFWBroker->putObject(&subject);
}


template<class Subject, class Broker>
Subject* VirtualProxy<Subject, Broker>::operator->()
{

	return getRealSubject();
}



#endif /* DEFAULTCONFIG_DEFAULT_VIRTUALPROXY_H_ */
