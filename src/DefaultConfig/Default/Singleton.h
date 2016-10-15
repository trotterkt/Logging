#ifndef Default_Singleton_H
#define Default_Singleton_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>


template <typename T> class Singleton 
{
public:
	// To actually get the singleton, derived
	// classes must use this static method. Otherwise,
	// a normal local instanciation is created
	static T& instance()
	{
		// Make sure only one instance at a timecontinues

		if (theSingleton.get() == 0)
		{
			// Since this is an auto_ptr, it will be destroyed once
			// out of scope
			theSingleton.reset(new T);
		}
		return *theSingleton;
	}

	static const T& const_instance()
	{
		return instance();
	}

protected:
	// The constructor is protected so that no instances
	// created except through instance()
	Singleton() {}

	// Destructor protected so that no one deletes the singleton
	virtual ~Singleton() { theSingleton.release(); }

private:
	static std::auto_ptr<T> theSingleton;

	static boost::mutex myMutex;

	// Singleton objects should not be copy constructed or assigned.
	// Therefore, copy constructor and assignment operator made
	// private so that clients dont cannot iinvoke them and the
	// the compiler doesnt create them
	Singleton(const Singleton&);

	Singleton& operator=(const Singleton&);

};

template<typename T>
std::auto_ptr<T> Singleton<T>::theSingleton;

template<typename T>
boost::mutex Singleton<T>::myMutex;

#endif
