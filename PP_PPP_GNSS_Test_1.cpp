#include<iostream>
#include<math.h>

#include "functions/parse/Parse_GPS_obs_from_RINEX.hpp"
#include "functions/Date_to_TOW.hpp"
#include "functions/structs/RINEX.hpp"

struct GNSS_config {
	string obs_name;
	int start_time;
	int duration;
	string nav_name;
	int nav_rinex_version;
};

struct GNSS_data {
	RINEX rinex;
	GNSS_config config;
};

int main() {

	double deg_to_rad = M_PI/180;
	double c = 299792458;

	struct GNSS_data GNSS_data;

	GNSS_data.config.obs_name = "MGLA362p.rxo";
	GNSS_data.config.start_time = Date_to_TOW(2021,12,28,15,30,00);
	GNSS_data.config.duration = 540;
	GNSS_data.rinex = parse_GPS_obs_from_RINEX(GNSS_data.config.obs_name, GNSS_data.config.start_time, GNSS_data.config.duration);
	GNSS_data.rinex.hdr.antenna_location[2] = -2295389.2475;

	GNSS_data.config.nav_name = "mgla3621.21n";
	GNSS_data.config.nav_rinex_version = 2;

	return 0;
}
