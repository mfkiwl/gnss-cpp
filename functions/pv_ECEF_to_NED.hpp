#ifndef pv_ECEF_to_NED_HPP
#define pv_ECEF_to_NED_HPP

struct NED{
	double L_b;
	double lambda_b;
	double h_b;
	double v_eb_n[3];
};

NED pv_ECEF_to_NED(double r_eb_e[], double v_eb_e[]);

#endif

