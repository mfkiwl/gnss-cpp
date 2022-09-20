#include<string>
#include<iostream>
#include <fstream>
#include "Parse_GPS_nav_from_RINEX.hpp"
#include "../Date_to_TOW.hpp"

using namespace std;

RINEX_NAV parse_GPS_nav_from_RINEX(string filename_nav, int nav_rinex_version) {

	RINEX_NAV out;
	
	ifstream readFile("data/"+filename_nav);

	for (int i = 0; i <= 10000; i++) {
		string i_line;
		getline(readFile, i_line);
		
		if (i_line.find("END OF HEADER") != std::string::npos) break;

		if (i_line.find("GPSA") != std::string::npos) {
			out.iono.alpha_0 = stod(i_line.substr(5,12));			
			out.iono.alpha_1 = stod(i_line.substr(19,10));			
			out.iono.alpha_2 = stod(i_line.substr(31,10));			
			out.iono.alpha_3 = stod(i_line.substr(43,10));			
		}

		if (i_line.find("GPSB") != std::string::npos) {
			out.iono.beta_0 = stod(i_line.substr(5,12));
			out.iono.beta_1 = stod(i_line.substr(19,10));			
			out.iono.beta_2 = stod(i_line.substr(31,10));			
			out.iono.beta_3 = stod(i_line.substr(43,10));			
		}
	}

	if (nav_rinex_version == 2) {

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

		int data_block_counter = 0; 
		int measurement_line_counter = 0; 
		int data_block_head_flag = 0; 

		string data_line;

		while(getline(readFile, data_line)) { 
			string segment_for_check = data_line.substr(0, 22);
			
			data_block_head_flag = !((segment_for_check.find("D") != std::string::npos) || (segment_for_check.find("e") != std::string::npos) 
					|| (segment_for_check.find("d") != std::string::npos) || (segment_for_check.find("E") != std::string::npos));

			int D_number = (data_line.find("D") != std::string::npos) + (data_line.find("e") != std::string::npos) 
					+ (data_line.find("d") != std::string::npos) + (data_line.find("E") != std::string::npos);

			if (D_number == 0) {
				cout << "Meet abnormal line" << endl;
				continue;
			}

			if (data_block_head_flag == 1) {
				PRN.push_back(stod(data_line.substr(0,2)));	
				year.push_back(stod(data_line.substr(2,3)));	
				month.push_back(stod(data_line.substr(5,3)));	
				day.push_back(stod(data_line.substr(8,3)));	
				hour.push_back(stod(data_line.substr(11,3)));	
				min.push_back(stod(data_line.substr(14,3)));	
				sec.push_back(stod(data_line.substr(17,5)));	
				iTOW.push_back(Date_to_TOW(year[data_block_counter], month[data_block_counter], day[data_block_counter], 
							hour[data_block_counter], min[data_block_counter], sec[data_block_counter]));

				t_oc.resize(data_block_counter+1);
				t_oc[data_block_counter].resize(32);

				a_f0.resize(data_block_counter+1);
				a_f1.resize(data_block_counter+1);
				a_f2.resize(data_block_counter+1);
				a_f0[data_block_counter].resize(32);
				a_f1[data_block_counter].resize(32);
				a_f2[data_block_counter].resize(32);

				t_oc[data_block_counter][PRN[data_block_counter]-1] = iTOW[data_block_counter];

				a_f0[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
				a_f1[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
				a_f2[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));

				measurement_line_counter++;
				
				continue;
			}
			
			if (data_block_head_flag == 0) {
				switch (measurement_line_counter) {
					case 1:
						IODE.resize(data_block_counter+1);
						C_rs.resize(data_block_counter+1);
						Delta_n.resize(data_block_counter+1);
						M_0.resize(data_block_counter+1);
						IODE[data_block_counter].resize(32);
						C_rs[data_block_counter].resize(32);
						Delta_n[data_block_counter].resize(32);
						M_0[data_block_counter].resize(32);

						IODE[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						C_rs[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						Delta_n[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						M_0[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 2:
						C_uc.resize(data_block_counter+1);
						e.resize(data_block_counter+1);
						C_us.resize(data_block_counter+1);
						sqrtA.resize(data_block_counter+1);
						C_uc[data_block_counter].resize(32);
						e[data_block_counter].resize(32);
						C_us[data_block_counter].resize(32);
						sqrtA[data_block_counter].resize(32);

						C_uc[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						e[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						C_us[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						sqrtA[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 3:
						t_oe.resize(data_block_counter+1);
						C_ic.resize(data_block_counter+1);
						Omega_0.resize(data_block_counter+1);
						C_is.resize(data_block_counter+1);
						t_oe[data_block_counter].resize(32);
						C_ic[data_block_counter].resize(32);
						Omega_0[data_block_counter].resize(32);
						C_is[data_block_counter].resize(32);

						t_oe[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						C_ic[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						Omega_0[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						C_is[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 4:
						i_0.resize(data_block_counter+1);
						C_rc.resize(data_block_counter+1);
						omega.resize(data_block_counter+1);
						OmegaDot.resize(data_block_counter+1);
						i_0[data_block_counter].resize(32);
						C_rc[data_block_counter].resize(32);
						omega[data_block_counter].resize(32);
						OmegaDot[data_block_counter].resize(32);

						i_0[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						C_rc[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						omega[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						OmegaDot[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 5:
						IDOT.resize(data_block_counter+1);
						code_on_L2.resize(data_block_counter+1);
						weekNo.resize(data_block_counter+1);
						data_flag_on_L2.resize(data_block_counter+1);
						IDOT[data_block_counter].resize(32);
						code_on_L2[data_block_counter].resize(32);
						weekNo[data_block_counter].resize(32);
						data_flag_on_L2[data_block_counter].resize(32);

						IDOT[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						code_on_L2[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						weekNo[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						data_flag_on_L2[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 6:
						svAccuracy.resize(data_block_counter+1);
						svHealth.resize(data_block_counter+1);
						T_GD.resize(data_block_counter+1);
						IODC.resize(data_block_counter+1);
						svAccuracy[data_block_counter].resize(32);
						svHealth[data_block_counter].resize(32);
						T_GD[data_block_counter].resize(32);
						IODC[data_block_counter].resize(32);

						svAccuracy[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
						svHealth[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
						T_GD[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(41, 19));
						IODC[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(60, 19));
						measurement_line_counter++;
						break;
					case 7:
						try {
							t_of_msg.resize(data_block_counter+1);
							fitting_period.resize(data_block_counter+1);
							t_of_msg[data_block_counter].resize(32);
							fitting_period[data_block_counter].resize(32);

							t_of_msg[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
							fitting_period[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(22, 19));
							measurement_line_counter = 0;
							data_block_counter++;
						} catch(...) {
							t_of_msg.resize(data_block_counter+1);
							fitting_period.resize(data_block_counter+1);
							t_of_msg[data_block_counter].resize(32);
							fitting_period[data_block_counter].resize(32);
							
							t_of_msg[data_block_counter][PRN[data_block_counter]-1] = stod(data_line.substr(3, 19));
							fitting_period[data_block_counter][PRN[data_block_counter]-1] = 0;
							measurement_line_counter = 0;
							data_block_counter++;
						}
				}
			}
		}
		out.setTimeMessage(PRN, year, month, day, hour, min, sec, iTOW, data_block_counter);
		out.setEphOut(t_oc, a_f0, a_f1, a_f2, IODE, C_rs, Delta_n, M_0, C_uc, e, C_us, sqrtA, t_oe, C_ic, Omega_0, C_is, i_0, C_rc,
				omega, OmegaDot, IDOT, code_on_L2, weekNo, data_flag_on_L2, svAccuracy, svHealth, T_GD, IODC, t_of_msg, fitting_period,
				data_block_counter);
	}

	if (nav_rinex_version == 3) {
		// TODO
	}

	return out;
}
