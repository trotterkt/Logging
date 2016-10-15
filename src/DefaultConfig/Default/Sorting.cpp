#include <vector>
#include <string>
#include "Default\Sorting.h"



bool Sorting::operator()(std::pair<std::string, DataPacket>& first, std::pair<std::string, DataPacket> &second)
{
	//return (first.second < second.second);
	std::string firstOid = first.first;
	std::string secondOid = second.first;

	std::vector<std::string> firstOidParse;
	std::vector<std::string> SecondOidParse;
	
	boost::split(firstOidParse, firstOid, boost::is_any_of(":"));
	boost::split(SecondOidParse, secondOid, boost::is_any_of(":"));

	return (stoi(firstOidParse[1]) < stoi(SecondOidParse[1]));
}
