#include "RINEX_NAV.hpp"

void RINEX_NAV::setTimeMessage(vector<int> prn, vector<int> y, vector<int> m, vector<int> d, vector<int> h, vector<int> min, vector<int> s,
				vector<int> itow, int size) {
	this->eph.PRN = prn;
	this->eph.year = y;
	this->eph.month = m;	
	this->eph.day = d;	
	this->eph.hour = h;	
	this->eph.min = min;	
	this->eph.sec = s;	
	this->eph.iTOW = itow;	
}

void RINEX_NAV::setEphOut(vector<vector<double>> t_oc, vector<vector<double>> a_f0, vector<vector<double>> a_f1, vector<vector<double>> a_f2, 
				vector<vector<double>> IODE, vector<vector<double>> C_rs, vector<vector<double>> Delta_n, vector<vector<double>> M_0,
				vector<vector<double>> C_uc, vector<vector<double>> e, vector<vector<double>> C_us, vector<vector<double>> sqrtA,
				vector<vector<double>> t_oe, vector<vector<double>> C_ic, vector<vector<double>> Omega_0, vector<vector<double>> C_is,
				vector<vector<double>> i_0, vector<vector<double>> C_rc, vector<vector<double>> omega, vector<vector<double>> OmegaDot,
				vector<vector<double>> IDOT, vector<vector<double>> code_on_L2, vector<vector<double>> weekNo, vector<vector<double>> data_flag_on_L2,
				vector<vector<double>> svAccuracy, vector<vector<double>> svHealth, vector<vector<double>> T_GD, vector<vector<double>> IODC,
				vector<vector<double>> t_of_msg, vector<vector<double>> fitting_period, int epochs) {

	this->eph.t_oc = t_oc;
	this->eph.a_f0 = a_f0;
	this->eph.a_f1 = a_f1;
	this->eph.a_f2 = a_f2;
	this->eph.IODE = IODE;
	this->eph.C_rs = C_rs;
	this->eph.Delta_n = Delta_n;
	this->eph.M_0 = M_0;
	this->eph.C_uc = C_uc;
	this->eph.e = e;
	this->eph.C_us = C_us;
	this->eph.sqrtA = sqrtA;
	this->eph.t_oe = t_oe;
	this->eph.C_ic = C_ic;
	this->eph.Omega_0 = Omega_0;
	this->eph.C_is = C_is;
	this->eph.i_0 = i_0;
	this->eph.C_rc = C_rc;
	this->eph.omega = omega;
	this->eph.OmegaDot = OmegaDot;
	this->eph.IDOT = IDOT;
	this->eph.code_on_L2 = code_on_L2;
	this->eph.weekNo = weekNo;
	this->eph.data_flag_on_L2 = data_flag_on_L2;
	this->eph.svAccuracy = svAccuracy;
	this->eph.svHealth = svHealth;
	this->eph.T_GD = T_GD;
	this->eph.IODC = IODC;
	this->eph.t_of_msg = t_of_msg;
	this->eph.fitting_period = fitting_period;
}
