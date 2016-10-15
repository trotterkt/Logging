#pragma once
#include "Default\Singleton.h"
#include <string>


class DataNaming : public Singleton<DataNaming>
{
public:
	DataNaming(void);
	~DataNaming(void);

	void setBaseInFileName();
	void setBaseOutFileName();

	void getDataLogInFileName(std::string& fullName);
	void getDataLogOutFileName(std::string& fullName);


	// Excel format of the log data - assumption is
	// that this will always be output to satisfy
	// Excel requirement
	void getExcelDataLogFileName(std::string& fullName);


private:
	std::string myBaseDirectory;
	std::string myBaseInFileName;
	std::string myBaseOutFileName;

};

