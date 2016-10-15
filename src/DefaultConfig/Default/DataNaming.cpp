#include "Default\DataNaming.h"
#include <time.h>
#include <stdlib.h>  

DataNaming::DataNaming(void)
{
	// :TODO: need to decide if use of environment variable should be applicable to
	// NGSysTE
	char* ngSysTeLoggingPathPtr;
	ngSysTeLoggingPathPtr = getenv("NGSysTE_Logging");

	if (ngSysTeLoggingPathPtr != NULL)
	{
		myBaseDirectory = ngSysTeLoggingPathPtr;
	}
	else
	{
		//:TODO: throw exceptions
	}

	// :TODO: Temp debugging
	//myBaseDirectory = "W:\\shared_libs.vbt\\NGSysTE\Logging\\Legacy Log Files\\";
	//myBaseDirectory = "C:\\Users\\Keir\\NGSysTE\\Logging\\Legacy Log Files\\";

	//:TODO: normal call
	//setBaseFileName();
	myBaseInFileName = "301_2016_07_19_09_58_48_000_27_52_TEST"; // temp debugging
	myBaseOutFileName = "ste"; // temp debugging
}


DataNaming::~DataNaming(void)
{
}

void DataNaming::getDataLogOutFileName(std::string& fullName)
{
	fullName.clear();

	// make this more robust with booste::filesytem library
	fullName.append(myBaseDirectory);

	// :TODO: according to whatever the specified base filename format is...
	fullName.append(myBaseOutFileName);
	//fullName.append("ste");

	fullName.append(".log");
}

void DataNaming::setBaseInFileName()
{
	 time_t rawtime;
     struct tm * timeinfo;

     time (&rawtime);
     timeinfo = localtime (&rawtime);

	 // :TODO: according to whatever the specified base filename format is...
	 std::ostringstream timeBuffer;
	 timeBuffer << timeinfo->tm_year << "_" 
		        << timeinfo->tm_mon << "_"
				<<  timeinfo->tm_mday << "_"
				<<  timeinfo->tm_hour << "_"
				<<  timeinfo->tm_min << "_"
				<<  timeinfo->tm_sec;
	// based on system date
	myBaseInFileName = timeBuffer.str();
}

void DataNaming::setBaseOutFileName()
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	// :TODO: according to whatever the specified base filename format is...
	std::ostringstream timeBuffer;
	timeBuffer << timeinfo->tm_year << "_"
		<< timeinfo->tm_mon << "_"
		<< timeinfo->tm_mday << "_"
		<< timeinfo->tm_hour << "_"
		<< timeinfo->tm_min << "_"
		<< timeinfo->tm_sec;
	// based on system date
	myBaseOutFileName = timeBuffer.str();
}
void DataNaming::getDataLogInFileName(std::string& fullName)
{
	fullName.clear();

	// make this more robust with booste::filesytem library
	fullName.append(myBaseDirectory);

	// :TODO: according to whatever the specified base filename format is...
	fullName.append("301_2016_07_19_09_58_48_000_27_52_TEST"); // :TODO: temp debug

	fullName.append(".log");
}

void DataNaming::getExcelDataLogFileName(std::string& fullName)
{
	fullName.clear();

	// make this more robust with booste::filesytem library
	fullName.append(myBaseDirectory);

	// :TODO: according to whatever the specified base filename format is...
	fullName.append(myBaseOutFileName); 

	fullName.append(".csv");
}

