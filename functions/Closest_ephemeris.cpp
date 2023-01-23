#include "Closest_ephemeris.hpp"
#include <algorithm>

RINEX_NAV Closest_ephemeris(double iTOW, RINEX_NAV rinex_nav) {
	struct RINEX_NAV out;

 	for (int i = 0; i < 32; i++) {
		int idx_eph_SV = -1;
	    auto it = std::find(rinex_nav.eph.PRN.begin(), rinex_nav.eph.PRN.end(), i);
		if(it != rinex_nav.eph.PRN.end()) idx_eph_SV = it - rinex_nav.eph.PRN.begin();
    
		if (idx_eph_SV == -1) {
			//disp("Warning!!!!!!!!!!!!!!!!!!!!!!!!")
			//disp("Ephemeris of SV"+i+" is missing!")
			continue;
		}

		int eph_SVi = Eph_SVi_in_file(idx_eph_SV,i,eph);

    % Check whether TOW is contained in ephemeris structure
    if TOW < min(eph_SVi.iTOW) || TOW > max(eph_SVi.iTOW)
%         disp("ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
%         disp("Time of week exceed the range of the ephemeris for SV"+i)
        continue
    end

    % Get ephemeris structure
    TOW_SVi_less_than_start_TOW = eph_SVi.iTOW(eph_SVi.iTOW - TOW >= 0);
    closest_eph_SVi = min(TOW_SVi_less_than_start_TOW);
    idx_eph_SVi = find(eph_SVi.iTOW == closest_eph_SVi);
    eph_TOW = Log_closest_eph_SVi(eph_TOW,i,eph_SVi,idx_eph_SVi,TOW);
	}

eph_TOW.StatusFlag = 1;

	return out;
}

