#include "Log_closest_eph_SVi.hpp"


RINEX_NAV Log_closest_eph_SVi(RINEX_NAV eph, int SVi, RINEX_NAV eph_SVi, int idx_eph_SVi, double start_TOW) {
	eph.eph.a_f0[SVi] = eph_SVi.eph.a_f0[idx_eph_SVi];
	eph.eph.a_f1[SVi] = eph_SVi.eph.a_f1[idx_eph_SVi];
	eph.eph.a_f2[SVi] = eph_SVi.eph.a_f2[idx_eph_SVi];
	eph.eph.IODE[SVi] = eph_SVi.eph.IODE[idx_eph_SVi];
	eph.eph.C_rs[SVi] = eph_SVi.eph.C_rs[idx_eph_SVi];
	eph.eph.Delta_n[SVi] = eph_SVi.eph.Delta_n[idx_eph_SVi];
	eph.eph.M_0[SVi] = eph_SVi.eph.M_0[idx_eph_SVi];
	eph.eph.C_uc[SVi] = eph_SVi.eph.C_uc[idx_eph_SVi];
	eph.eph.e[SVi] = eph_SVi.eph.e[idx_eph_SVi];
	eph.eph.C_us[SVi] = eph_SVi.eph.C_us[idx_eph_SVi];
	eph.eph.sqrtA[SVi] = eph_SVi.eph.sqrtA[idx_eph_SVi];
	eph.eph.t_oe[SVi] = eph_SVi.eph.t_oe[idx_eph_SVi];
	eph.eph.C_ic[SVi] = eph_SVi.eph.C_ic[idx_eph_SVi];
	eph.eph.Omega_0[SVi] = eph_SVi.eph.Omega_0[idx_eph_SVi];
	eph.eph.C_is[SVi] = eph_SVi.eph.C_is[idx_eph_SVi];
	eph.eph.i_0[SVi] = eph_SVi.eph.i_0[idx_eph_SVi];
	eph.eph.C_rc[SVi] = eph_SVi.eph.C_rc[idx_eph_SVi];
	eph.eph.omega[SVi] = eph_SVi.eph.omega[idx_eph_SVi];
	eph.eph.OmegaDot[SVi] = eph_SVi.eph.OmegaDot[idx_eph_SVi];
	eph.eph.IDOT[SVi] = eph_SVi.eph.IDOT[idx_eph_SVi];
	eph.eph.code_on_L2[SVi] = eph_SVi.eph.code_on_L2[idx_eph_SVi];
	eph.eph.weekNo[SVi] = eph_SVi.eph.weekNo[idx_eph_SVi];
	eph.eph.data_flag_on_L2[SVi] = eph_SVi.eph.data_flag_on_L2[idx_eph_SVi];
	eph.eph.svAccuracy[SVi] = eph_SVi.eph.svAccuracy[idx_eph_SVi];
	eph.eph.svHealth[SVi] = eph_SVi.eph.svHealth[idx_eph_SVi];
	eph.eph.T_GD[SVi] = eph_SVi.eph.T_GD[idx_eph_SVi];
	eph.eph.IODC[SVi] = eph_SVi.eph.IODC[idx_eph_SVi];
	eph.eph.t_oc[SVi] = eph_SVi.eph.t_oc[idx_eph_SVi];
	eph.eph.fitting_period[SVi] = eph_SVi.eph.fitting_period[idx_eph_SVi];
	eph.eph.latency_of_eph[SVi] = start_TOW - eph_SVi.eph.iTOW[idx_eph_SVi];
	return eph;
}

