#include "Euler_to_CTM.hpp"
#include "math.h"

void Euler_to_CTM(double eul[3], double C[3][3]) {
	double sin_phi = sin(eul[0]);
	double cos_phi = cos(eul[0]);
	double sin_theta = sin(eul[1]);
	double cos_theta = cos(eul[1]);
	double sin_psi = sin(eul[2]);
	double cos_psi = cos(eul[2]);

	C[0][0] = cos_theta * cos_psi;
	C[0][1] = cos_theta * sin_psi;
	C[0][2] = -sin_theta;
	C[1][0] = -cos_phi * sin_psi + sin_phi * sin_theta * cos_psi;
	C[1][1] = cos_phi * cos_psi + sin_phi * sin_theta * sin_psi;
	C[1][2] = sin_phi * cos_theta;
	C[2][0] = sin_phi * sin_psi + cos_phi * sin_theta * cos_psi;
	C[2][1] = -sin_phi * cos_psi + cos_phi * sin_theta * sin_psi;
	C[2][2] = cos_phi * cos_theta;
}
