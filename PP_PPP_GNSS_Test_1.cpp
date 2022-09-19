#include<iostream>

#include "functions/parse/Parse_GPS_obs_from_RINEX.hpp"
#include "functions/Date_to_TOW.hpp"

int main() {
	string obs_name = "MGLA362p.rxo";
	int start_time = Date_to_TOW(2021,12,28,15,30,00);
	int duration = 540;
	parse_GPS_obs_from_RINEX(obs_name, start_time, duration);

	return 0;
}
