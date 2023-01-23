#include <algorithm>
#include <iostream>
#include <iterator>
#include <math.h>

#include "functions/Date_to_TOW.hpp"
#include "functions/structs/RINEX_OBS.hpp"
#include "functions/structs/RINEX_NAV.hpp"
#include "functions/pv_ECEF_to_NED.hpp"
#include "functions/structs/Structs.hpp"
#include "functions/GNSS_WLS_PR_PRR_innov_test.hpp"

int main() {

	double deg_to_rad = M_PI/180;
	double c = 299792458;

	struct GNSS_data GNSS_data;
	struct WLS_config WLS_config;

	GNSS_data.config.obs_name = "MGLA362p.rxo";
	GNSS_data.config.start_time = Date_to_TOW(2021,12,28,15,30,00);
	GNSS_data.config.duration = 540;
	GNSS_data.rinex_obs = parse_GPS_obs_from_RINEX(GNSS_data.config.obs_name, GNSS_data.config.start_time, GNSS_data.config.duration);
	GNSS_data.rinex_obs.hdr.antenna_location[2] = -2295389.2475;

	GNSS_data.config.nav_name = "mgla3621.21n";
	GNSS_data.config.nav_rinex_version = 2;
	GNSS_data.rinex_nav = parse_GPS_nav_from_RINEX(GNSS_data.config.nav_name, GNSS_data.config.nav_rinex_version);

	GNSS_data.rinex_nav.iono.model = 1;
	GNSS_data.rinex_nav.iono.alpha_0 = 0.1211e-07;
	GNSS_data.rinex_nav.iono.alpha_1 = -0.7451e-08;
	GNSS_data.rinex_nav.iono.alpha_2 = -0.1192e-06;
	GNSS_data.rinex_nav.iono.alpha_3 = 0.5960e-07;
	GNSS_data.rinex_nav.iono.beta_0 = 0.9830e+05;
	GNSS_data.rinex_nav.iono.beta_1 = -0.8192e+05;
	GNSS_data.rinex_nav.iono.beta_2 = -0.1966e+06;
	GNSS_data.rinex_nav.iono.beta_3 = 0.4588e+06;
	GNSS_data.rinex_nav.iono.StatusFlag = 1;

	GNSS_data.tropo.model = 3;
	GNSS_data.tropo.StatusFlag = 1;

	//GNSS_data.config.init_est_r_ea_e = [0;0;0];
	GNSS_data.config.init_est_r_ea_e[0] = GNSS_data.rinex_obs.hdr.antenna_location[0];
	GNSS_data.config.init_est_r_ea_e[1] = GNSS_data.rinex_obs.hdr.antenna_location[1];
	GNSS_data.config.init_est_r_ea_e[2] = GNSS_data.rinex_obs.hdr.antenna_location[2];

	GNSS_data.config.init_est_v_ea_e[0] = 0;
	GNSS_data.config.init_est_v_ea_e[1] = 0;
	GNSS_data.config.init_est_v_ea_e[2] = 0;

	GNSS_data.config.no_sat = 32;
	GNSS_data.config.mask_angle = 15 * deg_to_rad;
	GNSS_data.config.car_freq_L1 = 1575.42e6;
	GNSS_data.config.car_freq_L2 = 1227.60e6;
	GNSS_data.config.lambda_L1 = c/GNSS_data.config.car_freq_L1;
	GNSS_data.config.lambda_L2 = c/GNSS_data.config.car_freq_L2;
	GNSS_data.config.sim_mode = 0;
	GNSS_data.config.P1_use = 0;
	GNSS_data.config.P2_use = 1;

	WLS_config.pseudo_range_SD = 2.5;
	WLS_config.range_rate_SD = 0.05;
	WLS_config.PRR_use = 0;

	struct NED ned_r_v;
	ned_r_v = pv_ECEF_to_NED(GNSS_data.config.init_est_r_ea_e, GNSS_data.config.init_est_v_ea_e);;

	int no_epochs = GNSS_data.rinex_obs.obs.iTOW.size();
	double in_profile[no_epochs][10];
	for(int i = 0; i < no_epochs; i++) {
		in_profile[i][0] = GNSS_data.rinex_obs.obs.iTOW[i];
		in_profile[i][1] = ned_r_v.L_b;
		in_profile[i][2] = ned_r_v.lambda_b;
		in_profile[i][3] = ned_r_v.h_b;
		in_profile[i][4] = 0;
		in_profile[i][5] = 0;
		in_profile[i][6] = 0;
		in_profile[i][7] = 0;
		in_profile[i][8] = 0;
		in_profile[i][9] = 0;
	}

	struct GNSS_WLS GNSS_WLS;
	GNSS_WLS = GNSS_WLS_PR_PRR_innov_test(in_profile, no_epochs, GNSS_data, WLS_config);

	return 0;
}
