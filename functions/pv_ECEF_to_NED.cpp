#include "math.h"
#include "pv_ECEF_to_NED.hpp"
#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

boost::numeric::ublas::matrix<double> matrix_prod(double a[][3], double b[]) {
	boost::numeric::ublas::matrix<double> A(3,3), B(3,1), C(3,1);
	for (int n = 0; n < 3; n++) {
		B(n,0) = b[n]; 
		for(int m = 0; m < 3; m++) {
			A(n,m) = a[n][m];
		}
	}
	boost::numeric::ublas::axpy_prod(A, B, C);
	return C;
}

NED pv_ECEF_to_NED(double r_eb_e[3], double v_eb_e[3]) {

	struct NED NED;

	double R_0 = 6378137;
	double e = 0.0818191908425; 

	NED.lambda_b = atan2(r_eb_e[1],r_eb_e[0]);

	double k1 = sqrt(1 - e*e) * abs(r_eb_e[2]);
	double k2 = e*e * R_0;
	double beta = sqrt(r_eb_e[0]*r_eb_e[0] + r_eb_e[1]*r_eb_e[1]);
	double E = (k1 - k2) / beta;
 	double F = (k1 + k2) / beta;

	double P = double(4.0/3.0) * (E*F + 1);

 	double Q = 2 * (E*E - F*F);

	double D = P*P*P + Q*Q;

	double V = pow(sqrt(D) - Q, 1.0/3.0) - pow(sqrt(D) + Q, 1.0/3.0);

 	double G = 0.5 * (sqrt(E*E + V) + E);

	double T = sqrt(G*G + (F - V * G) / (2 * G - E)) - G;

	NED.L_b = sign(r_eb_e[2]) * atan((1 - T*T) / (2 * T * sqrt (1 - e*e)));

	NED.h_b = (beta - R_0 * T) * cos(NED.L_b) + (r_eb_e[2] - sign(r_eb_e[2]) * R_0 * sqrt(1 - e*e)) * sin(NED.L_b);
      
	double cos_lat = cos(NED.L_b);
	double sin_lat = sin(NED.L_b);
	double cos_long = cos(NED.lambda_b);
	double sin_long = sin(NED.lambda_b);
	double C_e_n[3][3] = {{-sin_lat * cos_long, -sin_lat * sin_long,  cos_lat},
						  {-sin_long,cos_long, 0},
						  {-cos_lat * cos_long, -cos_lat * sin_long, -sin_lat}};
	boost::numeric::ublas::matrix<double> res = matrix_prod(C_e_n, v_eb_e);
	
	NED.v_eb_n[0] = res(0,0);
	NED.v_eb_n[1] = res(1,0);
	NED.v_eb_n[2] = res(2,0);
	return NED;
}
