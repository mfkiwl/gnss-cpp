#include "GNSS_WLS_PR_PRR_innov_test.hpp"
#include "Euler_to_CTM.hpp"
#include "Get_GNSS_data.hpp"

GNSS_WLS GNSS_WLS_PR_PRR_innov_test(double in_profile[][10], int no_epochs, GNSS_data GNSS_data, WLS_config WLS_config) {

	struct GNSS_WLS GNSS_WLS;

	double time = in_profile[0][0];
	double true_L_b = in_profile[0][1];
	double true_lambda_b = in_profile[0][2];
	double true_h_b = in_profile[0][3];
	double true_v_eb_n[3];
	true_v_eb_n[0] = in_profile[0][4];
	true_v_eb_n[1] = in_profile[0][5];
	true_v_eb_n[2] = in_profile[0][6];
	double true_eul_nb[3];
	true_eul_nb[0] = in_profile[0][7];
	true_eul_nb[1] = in_profile[0][8];
	true_eul_nb[2] = in_profile[0][9];
	double true_C_b_n[3][3];
	Euler_to_CTM(true_eul_nb, true_C_b_n );

	struct GNSS_data GNSS_data_epoch = Get_GNSS_data(GNSS_data,1);

	return GNSS_WLS;
}
