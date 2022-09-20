#ifndef Parse_GPS_nav_from_RINEX_HPP
#define Parse_GPS_nav_from_RINEX_HPP

#include <string>
#include "../structs/RINEX_NAV.hpp"

using namespace std;

RINEX_NAV parse_GPS_nav_from_RINEX(string filename_nav, int nav_rinex_version);

#endif
