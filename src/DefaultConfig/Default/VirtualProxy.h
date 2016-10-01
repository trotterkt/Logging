/*
 * VirtualProxy.h
 *
 *  Created on: Sep 15, 2016
 *      Author: trottke1
 */

#ifndef DEFAULTCONFIG_DEFAULT_VIRTUALPROXY_H_
#define DEFAULTCONFIG_DEFAULT_VIRTUALPROXY_H_

#include <boost/regex.hpp>

	
template<class Subject, class Broker> class VirtualProxy
{
	public:
		VirtualProxy() { }

		void create(boost::regex oid = boost::regex(""));

		//void create();

		Subject* getRealSubject();
		void putRealSubject(Subject subject);

		Subject* operator->();


	private:
		boost::regex myOid;
		Broker* myPFWBroker;

		Broker& createBroker()
		{
			return Broker::instance();
		}

		Subject* materializeSubject();

		void dematerializeSubject(Subject subject);

};

//template<class Subject, class Broker>
//void VirtualProxy<Subject, Broker>::create()
//{
//
//}

template<class Subject, class Broker>
void VirtualProxy<Subject, Broker>::create(boost::regex oid)
{

	myOid = oid;
	myPFWBroker = &createBroker();
	
	// if a specific oid is not specified,
	// materilize all objects
	if (oid == boost::regex(""))
	{
		myPFWBroker->materializeAll();
	}

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
