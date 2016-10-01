#ifndef Default_Time_H
#define Default_Time_H

#include "Default\CCSDS_struct.h"

// Realization of time from the header information. As logging is
// currently defined, Time abstraction is not applicable, but
// may well be appropriate for analysis or Instrument time on
// capture
class Time
{
public:
	Time();
	~Time();
	Time(const Time& right);
	void operator=(const CCSDS_SecondaryHeader_struct& right);
	void operator=(const Time& right);

private:

};

#endif