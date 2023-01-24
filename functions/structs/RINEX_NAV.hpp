#ifndef RINEX_NAV_HPP
#define RINEX_NAV_HPP

#include <vector>
#include <string>

using namespace std;

class RINEX_NAV {
	public:
		struct {
			int model;
			double alpha_0;
			double alpha_1;
			double alpha_2;
			double alpha_3;
			double beta_0;
			double beta_1;
			double beta_2;
			double beta_3;
			int StatusFlag;
		} iono;

		struct {
			vector<int> PRN; 
			vector<int> year; 
			vector<int> month;
			vector<int> day;
			vector<int> hour; 
			vector<int> min;
			vector<int> sec;
			vector<int> iTOW;

			vector<vector<double>> t_oc;
			vector<vector<double>> a_f0;
			vector<vector<double>> a_f1;
			vector<vector<double>> a_f2;
			vector<vector<double>> IODE;
			vector<vector<double>> C_rs;
			vector<vector<double>> Delta_n;
			vector<vector<double>> M_0;
			vector<vector<double>> C_uc;
			vector<vector<double>> e;
			vector<vector<double>> C_us;
			vector<vector<double>> sqrtA;
			vector<vector<double>> t_oe;
			vector<vector<double>> C_ic;
			vector<vector<double>> Omega_0;
			vector<vector<double>> C_is;
			vector<vector<double>> i_0;
			vector<vector<double>> C_rc;
			vector<vector<double>> omega;
			vector<vector<double>> OmegaDot;
			vector<vector<double>> IDOT;
			vector<vector<double>> code_on_L2;
			vector<vector<double>> weekNo;
			vector<vector<double>> data_flag_on_L2;
			vector<vector<double>> svAccuracy;
			vector<vector<double>> svHealth;
			vector<vector<double>> T_GD;
			vector<vector<double>> IODC;
			vector<vector<double>> t_of_msg;
			vector<vector<double>> fitting_period;
			vector<double> latency_of_eph;
			int StatusFlag;
		} eph;


		void setTimeMessage(vector<int> prn, vector<int> y, vector<int> m, vector<int> d, vector<int> h, vector<int> min, vector<int> s,
				vector<int> itow, int size);

		void setEphOut(vector<vector<double>> t_oc, vector<vector<double>> a_f0, vector<vector<double>> a_f1, vector<vector<double>> a_f2, 
				vector<vector<double>> IODE, vector<vector<double>> C_rs, vector<vector<double>> Delta_n, vector<vector<double>> M_0,
				vector<vector<double>> C_uc, vector<vector<double>> e, vector<vector<double>> C_us, vector<vector<double>> sqrtA,
				vector<vector<double>> t_oe, vector<vector<double>> C_ic, vector<vector<double>> Omega_0, vector<vector<double>> C_is,
				vector<vector<double>> i_0, vector<vector<double>> C_rc, vector<vector<double>> omega, vector<vector<double>> OmegaDot,
				vector<vector<double>> IDOT, vector<vector<double>> code_on_L2, vector<vector<double>> weekNo, vector<vector<double>> data_flag_on_L2,
				vector<vector<double>> svAccuracy, vector<vector<double>> svHealth, vector<vector<double>> T_GD, vector<vector<double>> IODC,
				vector<vector<double>> t_of_msg, vector<vector<double>> fitting_period, int epochs);
};

#endif
