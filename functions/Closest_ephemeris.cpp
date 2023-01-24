#include "Closest_ephemeris.hpp"
#include <algorithm>
#include "Eph_SVi_in_file.hpp"
#include "Log_closest_eph_SVi.hpp"

RINEX_NAV Closest_ephemeris(double TOW, RINEX_NAV rinex_nav) {
	struct RINEX_NAV eph_TOW;
	
	eph_TOW.eph.a_f0.resize(32);
	eph_TOW.eph.a_f1.resize(32);
	eph_TOW.eph.a_f2.resize(32);
	eph_TOW.eph.IODE.resize(32);
	eph_TOW.eph.C_rs.resize(32);
	eph_TOW.eph.Delta_n.resize(32);
	eph_TOW.eph.M_0.resize(32);
	eph_TOW.eph.C_uc.resize(32);
	eph_TOW.eph.e.resize(32);
	eph_TOW.eph.C_us.resize(32);
	eph_TOW.eph.sqrtA.resize(32);
	eph_TOW.eph.t_oe.resize(32);
	eph_TOW.eph.C_ic.resize(32);
	eph_TOW.eph.Omega_0.resize(32);
	eph_TOW.eph.C_is.resize(32);
	eph_TOW.eph.i_0.resize(32);
	eph_TOW.eph.C_rc.resize(32);
	eph_TOW.eph.omega.resize(32);
	eph_TOW.eph.OmegaDot.resize(32);
	eph_TOW.eph.IDOT.resize(32);
	eph_TOW.eph.code_on_L2.resize(32);
	eph_TOW.eph.weekNo.resize(32);
	eph_TOW.eph.data_flag_on_L2.resize(32);
	eph_TOW.eph.svAccuracy.resize(32);
	eph_TOW.eph.svHealth.resize(32);
	eph_TOW.eph.T_GD.resize(32);
	eph_TOW.eph.IODC.resize(32);
	eph_TOW.eph.t_oc.resize(32);
	eph_TOW.eph.fitting_period.resize(32);
	eph_TOW.eph.latency_of_eph.resize(32);
	
 	for (int i = 1; i <= 32; i++) {
		vector<int> idx_eph_SV;
		std::vector<int>::iterator iter = rinex_nav.eph.PRN.begin();
		while ((iter = std::find(iter, rinex_nav.eph.PRN.end(), i)) != rinex_nav.eph.PRN.end()){
			idx_eph_SV.push_back(iter - rinex_nav.eph.PRN.begin());
			iter++;
		}
    
		if (idx_eph_SV.empty()) {
			//disp("Warning!!!!!!!!!!!!!!!!!!!!!!!!")
			//disp("Ephemeris of SV"+i+" is missing!")
			continue;
		}

		RINEX_NAV eph_SVi = Eph_SVi_in_file(idx_eph_SV,i,rinex_nav);

		auto it_min = std::min_element(eph_SVi.eph.iTOW.begin(), eph_SVi.eph.iTOW.end());
		auto it_max = std::max_element(eph_SVi.eph.iTOW.begin(), eph_SVi.eph.iTOW.end());
		if (TOW < *it_min || TOW > *it_max) {
			//disp("ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
			//disp("Time of week exceed the range of the ephemeris for SV"+i)
			continue;
		}

		vector<int> TOW_SVi_greater_than_start_TOW;
		for(auto it = eph_SVi.eph.iTOW.begin(); it != eph_SVi.eph.iTOW.end(); ++it) {
			if(*it - TOW >= 0) TOW_SVi_greater_than_start_TOW.push_back(*it); 
		}
		int closest_eph_SVi = *std::min_element(TOW_SVi_greater_than_start_TOW.begin(), TOW_SVi_greater_than_start_TOW.end());
		int idx_eph_SVi = std::find(eph_SVi.eph.iTOW.begin(), eph_SVi.eph.iTOW.end(), closest_eph_SVi) - eph_SVi.eph.iTOW.begin();
		eph_TOW = Log_closest_eph_SVi(eph_TOW,i-1,eph_SVi,idx_eph_SVi,TOW);
	}

	eph_TOW.eph.StatusFlag = 1;

	return eph_TOW;
}

