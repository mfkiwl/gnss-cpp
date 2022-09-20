#ifndef Parse_GPS_obs_from_RINEX_HPP
#define Parse_GPS_obs_from_RINEX_HPP

#include <string>
#include "../structs/RINEX_OBS.hpp"

using namespace std;

RINEX_OBS parse_GPS_obs_from_RINEX(string filename_obs, int start_time, int duration);

#endif
