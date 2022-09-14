#ifndef RINEX_HPP
#define RINEX_HPP

#include <vector>
#include <string>

using namespace std;

class RINEX {
	public:
		struct {
			vector<string> *type;
			double antenna_location[3];
			int first_year; 
			int first_month;
			int first_day;
			int first_hour; 
			int first_min;
			int first_sec;
			int first_iTOW;
			double interval;
			vector<int> total_SVnum;
		} hdr;

		struct {
			vector<int> year; 
			vector<int> month;
			vector<int> day;
			vector<int> hour; 
			vector<int> min;
			vector<int> sec;
			vector<int> iTOW;

			vector<int> numSV_L1;

			vector<int> *sv_L1;
			vector<double> *pr_L1;
			vector<double> *precise_pr_L1;
			vector<double> *cp_L1;
			vector<double> *do_L1;
			vector<double> *snr_L1;
			vector<double> *lli_L1;
			vector<double> *ssi_L1;

			vector<int> numSV_L2;

			vector<int> *sv_L2;
			vector<double> *pr_L2;
			vector<double> *precise_pr_L2;
			vector<double> *do_L2;
			vector<double> *cp_L2;
			vector<double> *snr_L2;
			vector<double> *lli_L2;
			vector<double> *ssi_L2;

			vector<int> numSV_L5;

			vector<int> *sv_L5;
			vector<double> *pr_L5;
			vector<double> *do_L5;
			vector<double> *cp_L5;
			vector<double> *snr_L5;
			vector<double> *lli_L5;
			vector<double> *ssi_L5;
		} obs;

		void setHdrType(string type[][5], int lines);

		void setTotalSvNum(int totalSVnum[], int size);

		void setSvNumLx(int numSV_L1[], int numSV_L2[], int numSV_L5[],int size);

		void setTimeMessage(int y[], int m[], int d[], int h[], int min[], int s[], int itow[], int size);

		void setObsOut(int sv_L1[][32], double pr_L1[][32],double precise_pr_L1[][32],double cp_L1[][32],double do_L1[][32],double snr_L1[][32],double lli_L1[][32],double ssi_L1[][32],
						int sv_L2[][32], double pr_L2[][32],double precise_pr_L2[][32],double cp_L2[][32],double do_L2[][32],double snr_L2[][32],double lli_L2[][32],double ssi_L2[][32],
						int sv_L5[][32], double pr_L5[][32],double cp_L5[][32],double do_L5[][32],double snr_L5[][32],double lli_L5[][32],double ssi_L5[][32],
						int epochs);
};

#endif
