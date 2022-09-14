#include <ctime>
#include "Date_to_TOW.hpp"


int Date_to_TOW(int y, int m, int d, int h, int min, int s) {

	std::tm time_in = { s, min, h, d, m-1, y - 1900 }; 
	std::time_t time_temp = std::mktime(&time_in);
	const std::tm * time_out = std::localtime(&time_temp);

	int dayNum = time_out->tm_wday;

	return dayNum*24*3600 + h*3600 + min*60 + s;
}
