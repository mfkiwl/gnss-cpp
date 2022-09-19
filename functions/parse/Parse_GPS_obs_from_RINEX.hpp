#ifndef Parse_GPS_obs_from_RINEX_HPP
#define Parse_GPS_obs_from_RINEX_HPP

#include <string>
#include "../structs/RINEX.hpp"

using namespace std;

RINEX parse_GPS_obs_from_RINEX(string filename_obs, int start_time, int duration);

#endif
