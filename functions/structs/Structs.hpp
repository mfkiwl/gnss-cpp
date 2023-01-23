#ifndef Structs_HPP
#define Structs_HPP

#include <string>
#include "../parse/Parse_GPS_obs_from_RINEX.hpp"
#include "../parse/Parse_GPS_nav_from_RINEX.hpp"

struct WLS_config{
	double pseudo_range_SD;
	double range_rate_SD;
	int PRR_use;
};

struct GNSS_config {
	string obs_name;
	int start_time;
	int duration;
	string nav_name;
	int nav_rinex_version;
	double init_est_r_ea_e[3];
	double init_est_v_ea_e[3];
	int no_sat;
	double mask_angle;
	double car_freq_L1;
	double car_freq_L2;
	double lambda_L1;
	double lambda_L2;
	int sim_mode;
	int P1_use;
	int P2_use;
};

struct GNSS_tropo {
	int model;
	int StatusFlag;
};

struct GNSS_data {
	GNSS_config config;
	RINEX_OBS rinex_obs;
	RINEX_NAV rinex_nav;
	GNSS_tropo tropo;
};

struct eph{
	vector<double> t_oc;
	vector<double> a_f0;
	vector<double> a_f1;
	vector<double> a_f2;
	vector<double> IODE;
	vector<double> C_rs;
	vector<double> Delta_n;
	vector<double> M_0;
	vector<double> C_uc;
	vector<double> e;
	vector<double> C_us;
	vector<double> sqrtA;
	vector<double> t_oe;
	vector<double> C_ic;
	vector<double> Omega_0;
	vector<double> C_is;
	vector<double> i_0;
	vector<double> C_rc;
	vector<double> omega;
	vector<double> OmegaDot;
	vector<double> IDOT;
	vector<double> code_on_L2;
	vector<double> weekNo;
	vector<double> data_flag_on_L2;
	vector<double> svAccuracy;
	vector<double> svHealth;
	vector<double> T_GD;
	vector<double> IODC;
	vector<double> t_of_msg;
	vector<double> fitting_period;
	int StatusFlag;
};

#endif
