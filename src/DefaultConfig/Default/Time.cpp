#include "Default\Time.h"



Time::Time()
{
}


Time::~Time()
{
}

Time::Time(const Time& right)
{

}

void Time::operator=(const CCSDS_SecondaryHeader_struct& right)
{
	myDay = right.myDay;
	myMilliSeconds = (right.myMilliSeconds_word1 << 16);
	myMilliSeconds = myMilliSeconds | right.myMilliSeconds_word2;
	myMicroSeconds = right.myMicroSeconds;
}

void Time::operator=(const Time& right)
{

}

bool Time::operator<(const Time& right)
{
	if (this->myDay < right.myDay)
	{
		return true;
	}
	else if (this->myDay > right.myDay)
	{
		return false;
	}
	
	// must be the same day

	if (this->myMilliSeconds < right.myMilliSeconds)
	{
		return true;
	}
	else if (this->myMilliSeconds > right.myMilliSeconds)
	{
		return false;
	}
	
	// must be the same millisecond

	
	if (this->myMicroSeconds < right.myMicroSeconds)
	{
		return true;
	}
	else if (this->myMicroSeconds > right.myMicroSeconds)
	{
		return false;
	}

	// all 3 fields must be the same
	return false;
}

bool Time::operator>(const Time& right)
{

	if (this->myDay > right.myDay)
	{
		return true;
	}
	else if (this->myDay < right.myDay)
	{
		return false;
	}

	// must be the same day

	if (this->myMilliSeconds < right.myMilliSeconds)
	{
		return true;
	}
	else if (this->myMilliSeconds > right.myMilliSeconds)
	{
		return false;
	}

	// must be the same millisecond


	if (this->myMicroSeconds < right.myMicroSeconds)
	{
		return true;
	}
	else if (this->myMicroSeconds > right.myMicroSeconds)
	{
		return false;
	}

	// all 3 fields must be the same
	return false;
}

bool Time::operator==(const Time& right)
{
	if (!(*this < right) && !(*this > right))
	{
		return true;
	}

	return false;
}

