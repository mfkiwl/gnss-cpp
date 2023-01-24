#include "Eph_SVi_in_file.hpp"
#include "Date_to_TOW.hpp"

RINEX_NAV Eph_SVi_in_file(vector<int> eph_SV_ind, int SV, RINEX_NAV ephemeris){

	struct RINEX_NAV eph_SVi;

	eph_SVi.eph.a_f0.resize(eph_SV_ind.size());
	eph_SVi.eph.a_f1.resize(eph_SV_ind.size());
	eph_SVi.eph.a_f2.resize(eph_SV_ind.size());
	eph_SVi.eph.IODE.resize(eph_SV_ind.size());
	eph_SVi.eph.C_rs.resize(eph_SV_ind.size());
	eph_SVi.eph.Delta_n.resize(eph_SV_ind.size());
	eph_SVi.eph.M_0.resize(eph_SV_ind.size());
	eph_SVi.eph.C_uc.resize(eph_SV_ind.size());
	eph_SVi.eph.e.resize(eph_SV_ind.size());
	eph_SVi.eph.C_us.resize(eph_SV_ind.size());
	eph_SVi.eph.sqrtA.resize(eph_SV_ind.size());
	eph_SVi.eph.t_oe.resize(eph_SV_ind.size());
	eph_SVi.eph.C_ic.resize(eph_SV_ind.size());
	eph_SVi.eph.Omega_0.resize(eph_SV_ind.size());
	eph_SVi.eph.C_is.resize(eph_SV_ind.size());
	eph_SVi.eph.i_0.resize(eph_SV_ind.size());
	eph_SVi.eph.C_rc.resize(eph_SV_ind.size());
	eph_SVi.eph.omega.resize(eph_SV_ind.size());
	eph_SVi.eph.OmegaDot.resize(eph_SV_ind.size());
	eph_SVi.eph.IDOT.resize(eph_SV_ind.size());
	eph_SVi.eph.code_on_L2.resize(eph_SV_ind.size());
	eph_SVi.eph.weekNo.resize(eph_SV_ind.size());
	eph_SVi.eph.data_flag_on_L2.resize(eph_SV_ind.size());
	eph_SVi.eph.svAccuracy.resize(eph_SV_ind.size());
	eph_SVi.eph.svHealth.resize(eph_SV_ind.size());
	eph_SVi.eph.T_GD.resize(eph_SV_ind.size());
	eph_SVi.eph.IODC.resize(eph_SV_ind.size());
	eph_SVi.eph.t_oc.resize(eph_SV_ind.size());
	eph_SVi.eph.fitting_period.resize(eph_SV_ind.size());

	int count = 0;
	for(int i : eph_SV_ind) {
		eph_SVi.eph.year.push_back(ephemeris.eph.year[i]);
		eph_SVi.eph.month.push_back(ephemeris.eph.month[i]);
		eph_SVi.eph.day.push_back(ephemeris.eph.day[i]);
		eph_SVi.eph.hour.push_back(ephemeris.eph.hour[i]);
		eph_SVi.eph.min.push_back(ephemeris.eph.min[i]);
		eph_SVi.eph.sec.push_back(ephemeris.eph.sec[i]);
		eph_SVi.eph.iTOW.push_back(Date_to_TOW(eph_SVi.eph.year[i],eph_SVi.eph.month[i],eph_SVi.eph.day[i],eph_SVi.eph.hour[i],eph_SVi.eph.min[i],eph_SVi.eph.sec[i]));
		eph_SVi.eph.a_f0[count].push_back(ephemeris.eph.a_f0[i][SV-1]);
		eph_SVi.eph.a_f1[count].push_back(ephemeris.eph.a_f1[i][SV-1]);
		eph_SVi.eph.a_f2[count].push_back(ephemeris.eph.a_f2[i][SV-1]);
		eph_SVi.eph.IODE[count].push_back(ephemeris.eph.IODE[i][SV-1]);
		eph_SVi.eph.C_rs[count].push_back(ephemeris.eph.C_rs[i][SV-1]);
		eph_SVi.eph.Delta_n[count].push_back(ephemeris.eph.Delta_n[i][SV-1]);
		eph_SVi.eph.M_0[count].push_back(ephemeris.eph.M_0[i][SV-1]);
		eph_SVi.eph.C_uc[count].push_back(ephemeris.eph.C_uc[i][SV-1]);
		eph_SVi.eph.e[count].push_back(ephemeris.eph.e[i][SV-1]);
		eph_SVi.eph.C_us[count].push_back(ephemeris.eph.C_us[i][SV-1]);
		eph_SVi.eph.sqrtA[count].push_back(ephemeris.eph.sqrtA[i][SV-1]);
		eph_SVi.eph.t_oe[count].push_back(ephemeris.eph.t_oe[i][SV-1]);
		eph_SVi.eph.C_ic[count].push_back(ephemeris.eph.C_ic[i][SV-1]);
		eph_SVi.eph.Omega_0[count].push_back(ephemeris.eph.Omega_0[i][SV-1]);
		eph_SVi.eph.C_is[count].push_back(ephemeris.eph.C_is[i][SV-1]);
		eph_SVi.eph.i_0[count].push_back(ephemeris.eph.i_0[i][SV-1]);
		eph_SVi.eph.C_rc[count].push_back(ephemeris.eph.C_rc[i][SV-1]);
		eph_SVi.eph.omega[count].push_back(ephemeris.eph.omega[i][SV-1]);
		eph_SVi.eph.OmegaDot[count].push_back(ephemeris.eph.OmegaDot[i][SV-1]);
		eph_SVi.eph.IDOT[count].push_back(ephemeris.eph.IDOT[i][SV-1]);
		eph_SVi.eph.code_on_L2[count].push_back(ephemeris.eph.code_on_L2[i][SV-1]);
		eph_SVi.eph.weekNo[count].push_back(ephemeris.eph.weekNo[i][SV-1]);
		eph_SVi.eph.data_flag_on_L2[count].push_back(ephemeris.eph.data_flag_on_L2[i][SV-1]);
		eph_SVi.eph.svAccuracy[count].push_back(ephemeris.eph.svAccuracy[i][SV-1]);
		eph_SVi.eph.svHealth[count].push_back(ephemeris.eph.svHealth[i][SV-1]);
		eph_SVi.eph.T_GD[count].push_back(ephemeris.eph.T_GD[i][SV-1]);
		eph_SVi.eph.IODC[count].push_back(ephemeris.eph.IODC[i][SV-1]);
		eph_SVi.eph.t_oc[count].push_back(ephemeris.eph.t_oc[i][SV-1]);
		eph_SVi.eph.fitting_period[count].push_back(ephemeris.eph.fitting_period[i][SV-1]);
		count++;
	}

	return eph_SVi;
}

