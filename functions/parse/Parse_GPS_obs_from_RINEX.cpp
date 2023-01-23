#include <iostream>
#include <fstream>
#include <algorithm>
#include "Parse_GPS_obs_from_RINEX.hpp"
#include "../structs/RINEX_OBS.hpp"
#include "../Date_to_TOW.hpp"

using namespace std;

vector<int> getSubStringIndexes(string str, string sub) {
	vector<int> positions;
	size_t pos = str.find(sub, 0);
	while(pos != string::npos) {
		positions.push_back(pos);
		pos = str.find(sub,pos+1);
	}
	return positions;
}

RINEX_OBS parse_GPS_obs_from_RINEX(string filename_obs, int start_time, int duration) {

	RINEX_OBS out;

	ifstream readFile("data/"+filename_obs);

	int total_obs_type_num, total_obs_type_num_1;
	int remain_obs_type_num = -1;
	int type_line = 0;
	for (int i = 1; i <= 1000; i++) {
		string i_line;
		getline(readFile, i_line);

		int row_type, col_type;

		if (i_line.find("END OF HEADER") != std::string::npos) break;

		if (i_line.find("TYPES OF OBSERV") != std::string::npos) {
			if (remain_obs_type_num < 0) {
				total_obs_type_num = stoi(i_line.substr(5, 2));	
				total_obs_type_num_1 = total_obs_type_num;
			} else {
				total_obs_type_num = remain_obs_type_num;
				type_line += 1;
			}

			string type[total_obs_type_num/5 + (total_obs_type_num % 5 != 0)][5];

			if (type_line == 0) 
				for (int j = 0; j < total_obs_type_num; j++) {
					row_type = j/5; 
					col_type = j - 5*(row_type);
					type[row_type][col_type] = i_line.substr(5+6*(j+1)-1, (6+6*(j+1))-(5+6*(j+1)-1));
					remain_obs_type_num = total_obs_type_num_1 - j;
					if (j == 8) break;
				}
			else if (type_line == 1)
				for (int j = 10; j <= total_obs_type_num_1; j++) {
					row_type = j/5;
					col_type = j - 5*(row_type);
					type[row_type][col_type] = i_line.substr(5+6*(j-9), (6+6*(j-9))-(5+6*(j-9)));
					remain_obs_type_num = total_obs_type_num_1 - j;
				}
			else if (type_line == 2)
				for (int j = 19; j <= total_obs_type_num_1; j++) {
					row_type = j/5;
					col_type = j - 5*(row_type);
					type[row_type][col_type] = i_line.substr(5+6*(j-18), (6+6*(j-18))-(5+6*(j-18)));
				}
			else cout << "ERROR IN EXTRACTING HEADER" << endl;

			out.setHdrType(type, total_obs_type_num_1/5 + (total_obs_type_num % 5 != 0));
		}

		if (i_line.find("APPROX POSITION XYZ") != std::string::npos) {
			out.hdr.antenna_location[0] = stod(i_line.substr(0, 14));
			out.hdr.antenna_location[1] = stod(i_line.substr(15, 14));
			out.hdr.antenna_location[2] = stod(i_line.substr(29, 14));
		}
		
		if (i_line.find("TIME OF FIRST OBS") != std::string::npos) {
			out.hdr.first_year = stoi(i_line.substr(0,6));
			out.hdr.first_month = stoi(i_line.substr(6,6));
			out.hdr.first_day = stoi(i_line.substr(12,6));
			out.hdr.first_hour = stoi(i_line.substr(18,6));
			out.hdr.first_min = stoi(i_line.substr(24,6));
			out.hdr.first_sec = stoi(i_line.substr(30,6));
			out.hdr.first_iTOW = Date_to_TOW(out.hdr.first_year,out.hdr.first_month,out.hdr.first_day,
					out.hdr.first_hour,out.hdr.first_min,out.hdr.first_sec);	
		}

		if (i_line.find("INTERVAL") != std::string::npos) {
			out.hdr.interval = stod(i_line.substr(0,11));	
		}
	}

	int meas_line_num = total_obs_type_num_1/5;

	int flag_findG_nextline = 0;
	int body_line_counter = 0;
	int data_block_counter = 0;
	int measurement_line_counter = -1;
	int SV_idx_counter = 0;
	int flag_log_measurement = 0;
	int flag_log_measurement_counter = 0;
	int flag_then_find_G = 1;


	int size = duration/(int)out.hdr.interval;
	int total_SVnum[size];
	int y[size];
	int m[size];
	int d[size];
	int h[size];
	int min[size];
	int s[size];
	int itow[size];

	int numSV_L1[size];
	int numSV_L2[size];
	int numSV_L5[size];

	int sv_L1[size][32];
	double pr_L1[size][32];
	double precise_pr_L1[size][32];
	double cp_L1[size][32];
	double do_L1[size][32];
	double snr_L1[size][32];
	double lli_L1[size][32];
	double ssi_L1[size][32];

	int sv_L2[size][32];
	double pr_L2[size][32];
	double precise_pr_L2[size][32];
	double do_L2[size][32];
	double cp_L2[size][32];
	double snr_L2[size][32];
	double lli_L2[size][32];
	double ssi_L2[size][32];

	int sv_L5[size][32];
	double pr_L5[size][32];
	double do_L5[size][32];
	double cp_L5[size][32];
	double snr_L5[size][32];
	double lli_L5[size][32];
	double ssi_L5[size][32];

	int num_line_header_data_block;
	int SV_num_found;
	int SV_num;
	vector<int> GPS_PRN_remain;
	vector<int> GPS_meas_remain;

	int sv_L1_counter;
	int sv_L2_counter;
	int sv_L5_counter;

	string data_line;
	while(getline(readFile, data_line)) {
		vector<int> GPS_PRN_idx = getSubStringIndexes(data_line, "G");
		vector<int> GPS_meas_idx;
		GPS_meas_idx.resize(GPS_PRN_idx.size());
		for (int i = 0; i < GPS_PRN_idx.size(); i++) {
			GPS_meas_idx[i] = (GPS_PRN_idx[i] - 30)/3;
		}

		
		if (!GPS_PRN_idx.empty() && flag_findG_nextline == 0) {
			num_line_header_data_block = 1;
			flag_then_find_G = 0;
			int flag_log_measurement_counter = flag_log_measurement_counter + 1;
			SV_num = stoi(data_line.substr(30,3));
			SV_num_found = (data_line.length()-32)/3;

			if (SV_num > 12) flag_findG_nextline = 1;

			if (start_time < Date_to_TOW(stoi(data_line.substr(0,3)), stoi(data_line.substr(3,3)), stoi(data_line.substr(6,3)),
                stoi(data_line.substr(9,3)), stoi(data_line.substr(12,3)), stoi(data_line.substr(15,3))))  
					flag_log_measurement = 1;
			else if (flag_log_measurement == 0) continue;

			if ((start_time + duration) < Date_to_TOW(stoi(data_line.substr(0,3)), stoi(data_line.substr(3,3)), stoi(data_line.substr(6,3)),
                stoi(data_line.substr(9,3)), stoi(data_line.substr(12,3)), stoi(data_line.substr(15,3))))  break;

			total_SVnum[data_block_counter] = SV_num;

			sv_L1_counter = 0;
			sv_L2_counter = 0;
			sv_L5_counter = 0;

			for (int j = 0; j < GPS_PRN_idx.size(); j++) 
				GPS_PRN_idx[j] = stoi(data_line.substr(GPS_PRN_idx[j]+1,(GPS_PRN_idx[j]+2)-(GPS_PRN_idx[j])));

			GPS_PRN_remain = GPS_PRN_idx;
			GPS_meas_remain = GPS_meas_idx;

			y[data_block_counter] = stoi(data_line.substr(0,3));
			m[data_block_counter]= stoi(data_line.substr(3,3));
			d[data_block_counter] = stoi(data_line.substr(6,3));
			h[data_block_counter] = stoi(data_line.substr(9,3));
			min[data_block_counter] = stoi(data_line.substr(12,3));
			s[data_block_counter] = stoi(data_line.substr(15,3));
			itow[data_block_counter] = Date_to_TOW(y[data_block_counter], m[data_block_counter], d[data_block_counter],
					h[data_block_counter], min[data_block_counter], s[data_block_counter]);

			continue;
		}

		if (flag_findG_nextline == 1) {
			num_line_header_data_block = num_line_header_data_block + 1;             
			SV_num_found = SV_num_found + (data_line.length() - 32)/3;

			for (int j = 0; j < GPS_PRN_idx.size(); j++) 
				GPS_PRN_idx[j] = stoi(data_line.substr(GPS_PRN_idx[j]+1,(GPS_PRN_idx[j]+2)-(GPS_PRN_idx[j]+1)));

			GPS_PRN_remain.insert(GPS_PRN_remain.end(), GPS_PRN_idx.begin(), GPS_PRN_idx.end());
			if (!GPS_meas_idx.empty())
				std::for_each(GPS_meas_idx.begin(), GPS_meas_idx.end(), [&num_line_header_data_block](int& i) { 
						i += 12*(num_line_header_data_block - 1);
					});
			GPS_meas_remain.insert(GPS_meas_remain.end(), GPS_meas_idx.begin(), GPS_meas_idx.end());

			if (SV_num_found == SV_num)  flag_findG_nextline = 0;

			continue;
		}

		if (flag_findG_nextline == 0 && flag_log_measurement == 1 && flag_then_find_G == 0) {
			measurement_line_counter = measurement_line_counter + 1; 

			if (std::find(GPS_meas_remain.begin(), GPS_meas_remain.end(), SV_idx_counter) != GPS_meas_remain.end()) 
				for (int j = 0; j < 5; j++) {
					if (out.hdr.type[measurement_line_counter][j] == "") continue;

					double this_meas;
					try {
						this_meas = stod(data_line.substr(16*(j+1)-15,(16*(j+1)-2)-(16*(j+1)-15)));
					} catch (...) {
						this_meas = 0;	
					}

					if (out.hdr.type[measurement_line_counter][j] == "L1" && this_meas != 0) {
						cp_L1[data_block_counter][GPS_PRN_remain[0]] = this_meas;
						try {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L1[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1)-1, 1));
							if (data_line.length() > 16*(j+1)) 
								ssi_L1[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1), 1));
						} catch (...) {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L1[data_block_counter][GPS_PRN_remain[0]] = 0;
							if (data_line.length() > 16*(j+1)) 
								ssi_L1[data_block_counter][GPS_PRN_remain[0]] = 0;
						}
					}

					if (out.hdr.type[measurement_line_counter][j] == "L2" && this_meas != 0) {
						cp_L2[data_block_counter][GPS_PRN_remain[0]] = this_meas;
						try {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L2[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1)-1, 1));
							if (data_line.length() > 16*(j+1)) 
								ssi_L2[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1), 1));
						} catch (...) {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L2[data_block_counter][GPS_PRN_remain[0]] = 0;
							if (data_line.length() > 16*(j+1)) 
								ssi_L2[data_block_counter][GPS_PRN_remain[0]] = 0;
						}	
					}
			
					if (out.hdr.type[measurement_line_counter][j] == "L5" && this_meas != 0) {
						cp_L5[data_block_counter][GPS_PRN_remain[0]] = this_meas;
						try {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L5[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1)-1, 1));
							if (data_line.length() > 16*(j+1)) 
								ssi_L5[data_block_counter][GPS_PRN_remain[0]] = stod(data_line.substr(16*(j+1), 1));
						} catch (...) {
							if (data_line.length() > 16*(j+1)-1) 
								lli_L5[data_block_counter][GPS_PRN_remain[0]] = 0;
							if (data_line.length() > 16*(j+1)) 
								ssi_L5[data_block_counter][GPS_PRN_remain[0]] = 0;
						}
					}

					if (out.hdr.type[measurement_line_counter][j] == "C1" && pr_L1[data_block_counter][GPS_PRN_remain[0]] == 0)
						pr_L1[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "C2" && pr_L2[data_block_counter][GPS_PRN_remain[0]] == 0)
						pr_L2[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "C5" && pr_L5[data_block_counter][GPS_PRN_remain[0]] == 0)
						pr_L5[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "P1" && this_meas != 0) 
						precise_pr_L1[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "P2" && this_meas != 0) 
						precise_pr_L2[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "D1") 
						do_L1[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "D2") 
						do_L2[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "D5") 
						do_L5[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "S1") 
						snr_L1[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "S2") 
						snr_L2[data_block_counter][GPS_PRN_remain[0]] = this_meas;

					if (out.hdr.type[measurement_line_counter][j] == "S5") 
						snr_L5[data_block_counter][GPS_PRN_remain[0]] = this_meas;
				}
			
			if (measurement_line_counter == meas_line_num) {

				if (find(GPS_meas_remain.begin(), GPS_meas_remain.end(), SV_idx_counter) != GPS_meas_remain.end()) {

					if (snr_L1[data_block_counter][GPS_PRN_remain[0]] > 0) {
						sv_L1[data_block_counter][sv_L1_counter] = GPS_PRN_remain[0];
						numSV_L1[data_block_counter] = numSV_L1[data_block_counter] + 1;
						sv_L1_counter = sv_L1_counter + 1;
					}

					if (snr_L2[data_block_counter][GPS_PRN_remain[0]] > 0) {
					  sv_L2[data_block_counter][sv_L2_counter] = GPS_PRN_remain[0];
					  numSV_L2[data_block_counter] = numSV_L2[data_block_counter] + 1;
					  sv_L2_counter = sv_L2_counter + 1;
					}

					if (snr_L5[data_block_counter][GPS_PRN_remain[0]] > 0) {
					  sv_L5[data_block_counter][sv_L5_counter] = GPS_PRN_remain[0];
					  numSV_L5[data_block_counter] = numSV_L5[data_block_counter] + 1;
					  sv_L5_counter = sv_L5_counter + 1;
					}

					GPS_PRN_remain.erase(GPS_PRN_remain.begin());
				}
				measurement_line_counter = -1;
				SV_idx_counter = SV_idx_counter + 1;

				if (SV_idx_counter == total_SVnum[data_block_counter] + 1) {
					SV_idx_counter = 1;
					data_block_counter = data_block_counter + 1;
					flag_then_find_G = 1;
				}
			}
		}
	}

	out.setTotalSvNum(total_SVnum, size);
	out.setTimeMessage(y, m, d, h, min, s, itow, size);
	out.setObsOut(sv_L1,pr_L1,precise_pr_L1,cp_L1,do_L1,snr_L1,lli_L1,ssi_L1,
			sv_L2,pr_L2,precise_pr_L2,do_L2,cp_L2,snr_L2,lli_L2,ssi_L2,
			sv_L5,pr_L5,do_L5,cp_L5,snr_L5,lli_L5,ssi_L5, size);

	readFile.close();

	return out;
}
