#include "Get_GNSS_data.hpp"
#include <algorithm>
#include "Closest_ephemeris.hpp"

GNSS_data Get_GNSS_data(GNSS_data GNSS_data, int epoch) {
	struct GNSS_data out;

	out.rinex_obs.obs.sv_L1 = new vector<int>[1];                   
	out.rinex_obs.obs.pr_L1 = new vector<double>[1];  
	out.rinex_obs.obs.precise_pr_L1 = new vector<double>[1];                                 
	out.rinex_obs.obs.cp_L1 = new vector<double>[1];  
	out.rinex_obs.obs.do_L1 = new vector<double>[1];        
	out.rinex_obs.obs.snr_L1 = new vector<double>[1];                                       
	out.rinex_obs.obs.lli_L1 = new vector<double>[1];                               
	out.rinex_obs.obs.ssi_L1 = new vector<double>[1];                               

	out.rinex_obs.obs.sv_L2 = new vector<int>[1];                                 
	out.rinex_obs.obs.pr_L2 = new vector<double>[1];                                 
	out.rinex_obs.obs.precise_pr_L2 = new vector<double>[1];    
	out.rinex_obs.obs.do_L2 = new vector<double>[1];                                
	out.rinex_obs.obs.cp_L2 = new vector<double>[1];                                
	out.rinex_obs.obs.snr_L2 = new vector<double>[1];                                       
	out.rinex_obs.obs.lli_L2 = new vector<double>[1];                               
	out.rinex_obs.obs.ssi_L2 = new vector<double>[1];                               

	out.rinex_obs.obs.sv_L5 = new vector<int>[1];                                 
	out.rinex_obs.obs.pr_L5 = new vector<double>[1];                                 
	out.rinex_obs.obs.do_L5 = new vector<double>[1];                
	out.rinex_obs.obs.cp_L5 = new vector<double>[1];                                
	out.rinex_obs.obs.snr_L5 = new vector<double>[1];                               
	out.rinex_obs.obs.lli_L5 = new vector<double>[1];                               
	out.rinex_obs.obs.ssi_L5 = new vector<double>[1];

	out.config = GNSS_data.config;

	out.rinex_obs.hdr = GNSS_data.rinex_obs.hdr;
	out.rinex_obs.obs.year.push_back(GNSS_data.rinex_obs.obs.year[epoch]);
	out.rinex_obs.obs.month.push_back(GNSS_data.rinex_obs.obs.month[epoch]);
	out.rinex_obs.obs.day.push_back(GNSS_data.rinex_obs.obs.day[epoch]);
	out.rinex_obs.obs.hour.push_back(GNSS_data.rinex_obs.obs.hour[epoch]);
	out.rinex_obs.obs.min.push_back(GNSS_data.rinex_obs.obs.min[epoch]);
	out.rinex_obs.obs.sec.push_back(GNSS_data.rinex_obs.obs.sec[epoch]);
	out.rinex_obs.obs.iTOW.push_back(GNSS_data.rinex_obs.obs.iTOW[epoch]);

	out.rinex_obs.obs.numSV_L1.push_back(GNSS_data.rinex_obs.obs.numSV_L1[epoch]);
	out.rinex_obs.obs.sv_L1 = new vector<int>[1];
	out.rinex_obs.obs.sv_L1[0] = GNSS_data.rinex_obs.obs.sv_L1[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "C1") != GNSS_data.rinex_obs.hdr.type->end())
		out.rinex_obs.obs.pr_L1[0] = GNSS_data.rinex_obs.obs.pr_L1[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "P1") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.precise_pr_L1[0] = GNSS_data.rinex_obs.obs.precise_pr_L1[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "L1") != GNSS_data.rinex_obs.hdr.type->end()) {
		out.rinex_obs.obs.cp_L1[0] = GNSS_data.rinex_obs.obs.cp_L1[epoch];
		out.rinex_obs.obs.lli_L1[0] = GNSS_data.rinex_obs.obs.lli_L1[epoch];
		out.rinex_obs.obs.ssi_L1[0] = GNSS_data.rinex_obs.obs.ssi_L1[epoch];
	}
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "D1") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.do_L1[0] = GNSS_data.rinex_obs.obs.do_L1[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "S1") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.snr_L1[0] = GNSS_data.rinex_obs.obs.snr_L1[epoch];

	out.rinex_obs.obs.numSV_L2.push_back(GNSS_data.rinex_obs.obs.numSV_L2[epoch]);
	out.rinex_obs.obs.sv_L2[0] = GNSS_data.rinex_obs.obs.sv_L2[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "C2") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.pr_L2[0] = GNSS_data.rinex_obs.obs.pr_L2[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "P2") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.precise_pr_L2[0] = GNSS_data.rinex_obs.obs.precise_pr_L2[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "L2") != GNSS_data.rinex_obs.hdr.type->end()) {
		out.rinex_obs.obs.cp_L2[0] = GNSS_data.rinex_obs.obs.cp_L2[epoch];
		out.rinex_obs.obs.lli_L2[0] = GNSS_data.rinex_obs.obs.lli_L2[epoch];
		out.rinex_obs.obs.ssi_L2[0] = GNSS_data.rinex_obs.obs.ssi_L2[epoch];
	}
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "D2") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.do_L2[0] = GNSS_data.rinex_obs.obs.do_L2[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "S2") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.snr_L2[0] = GNSS_data.rinex_obs.obs.snr_L2[epoch];

	out.rinex_obs.obs.numSV_L5.push_back(GNSS_data.rinex_obs.obs.numSV_L5[epoch]);
	out.rinex_obs.obs.sv_L5[0] = GNSS_data.rinex_obs.obs.sv_L5[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "C5") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.pr_L5[0] = GNSS_data.rinex_obs.obs.pr_L5[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "L5") != GNSS_data.rinex_obs.hdr.type->end()) {
		out.rinex_obs.obs.cp_L5[0] = GNSS_data.rinex_obs.obs.cp_L5[epoch];
		out.rinex_obs.obs.lli_L5[0] = GNSS_data.rinex_obs.obs.lli_L5[epoch];
		out.rinex_obs.obs.ssi_L5[0] = GNSS_data.rinex_obs.obs.ssi_L5[epoch];
	}
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "D5") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.do_L5[0] = GNSS_data.rinex_obs.obs.do_L5[epoch];
	if (std::find(GNSS_data.rinex_obs.hdr.type->begin(), GNSS_data.rinex_obs.hdr.type->end(), "S5") != GNSS_data.rinex_obs.hdr.type->end()) 
		out.rinex_obs.obs.snr_L5[0] = GNSS_data.rinex_obs.obs.snr_L5[epoch];

	struct RINEX_NAV rinex_nav = Closest_ephemeris(out.rinex_obs.obs.iTOW[0], GNSS_data.rinex_nav);

	out.rinex_nav.iono = GNSS_data.rinex_nav.iono;

	out.tropo = GNSS_data.tropo;

	return out;
}

