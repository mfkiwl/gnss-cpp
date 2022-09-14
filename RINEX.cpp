#include "RINEX.hpp"

void RINEX::setHdrType(string type[][5], int lines) {
	this->hdr.type = new vector<string>[lines];

	for (int i = 0; i<lines; i++) {
		for (int j = 0; j<5; j++) this->hdr.type[i].push_back(type[i][j]);
	}
}

void RINEX::setTotalSvNum(int totalSVnum[], int size) {
	this->hdr.total_SVnum.resize(size);

	for (int i = 0; i<size; i++) {
		this->hdr.total_SVnum[i] = totalSVnum[i];
	}
}

void RINEX::setTimeMessage(int y[], int m[], int d[], int h[], int min[], int s[], int itow[], int size) {
	this->obs.year.resize(size);	
	this->obs.month.resize(size);	
	this->obs.day.resize(size);	
	this->obs.hour.resize(size);	
	this->obs.min.resize(size);	
	this->obs.sec.resize(size);	
	this->obs.iTOW.resize(size);	

	for (int i = 0; i<size; i++) {
		this->obs.year[i] = y[i];
		this->obs.month[i] = m[i];
		this->obs.day[i] = h[i];
		this->obs.hour[i] = h[i];
		this->obs.min[i] = min[i];
		this->obs.sec[i] = s[i];
		this->obs.iTOW[i] = itow[i];
	}
}

void RINEX::setSvNumLx(int numSV_L1[], int numSV_L2[], int numSV_L5[],int size) {
	this->obs.numSV_L1.resize(size);
	this->obs.numSV_L2.resize(size);
	this->obs.numSV_L5.resize(size);

	for (int i = 0; i<size; i++) {
		this->obs.numSV_L1[i] = numSV_L1[i];
		this->obs.numSV_L2[i] = numSV_L2[i];
		this->obs.numSV_L5[i] = numSV_L5[i];
	}
}

void RINEX::setObsOut(int sv_L1[][32], double pr_L1[][32],double precise_pr_L1[][32],double cp_L1[][32],double do_L1[][32],double snr_L1[][32],double lli_L1[][32],double ssi_L1[][32],
						int sv_L2[][32], double pr_L2[][32],double precise_pr_L2[][32],double cp_L2[][32],double do_L2[][32],double snr_L2[][32],double lli_L2[][32],double ssi_L2[][32],
						int sv_L5[][32], double pr_L5[][32],double cp_L5[][32],double do_L5[][32],double snr_L5[][32],double lli_L5[][32],double ssi_L5[][32],
						int epochs) {
	this->obs.sv_L1 = new vector<int>[epochs];                   
	this->obs.pr_L1 = new vector<double>[epochs];  
	this->obs.precise_pr_L1 = new vector<double>[epochs];                                 
	this->obs.cp_L1 = new vector<double>[epochs];  
	this->obs.do_L1 = new vector<double>[epochs];        
	this->obs.snr_L1 = new vector<double>[epochs];                                       
	this->obs.lli_L1 = new vector<double>[epochs];                               
	this->obs.ssi_L1 = new vector<double>[epochs];                               

	this->obs.sv_L2 = new vector<int>[epochs];                                 
	this->obs.pr_L2 = new vector<double>[epochs];                                 
	this->obs.precise_pr_L2 = new vector<double>[epochs];    
	this->obs.do_L2 = new vector<double>[epochs];                                
	this->obs.cp_L2 = new vector<double>[epochs];                                
	this->obs.snr_L2 = new vector<double>[epochs];                                       
	this->obs.lli_L2 = new vector<double>[epochs];                               
	this->obs.ssi_L2 = new vector<double>[epochs];                               

	this->obs.sv_L5 = new vector<int>[epochs];                                 
	this->obs.pr_L5 = new vector<double>[epochs];                                 
	this->obs.do_L5 = new vector<double>[epochs];                
	this->obs.cp_L5 = new vector<double>[epochs];                                
	this->obs.snr_L5 = new vector<double>[epochs];                               
	this->obs.lli_L5 = new vector<double>[epochs];                               
	this->obs.ssi_L5 = new vector<double>[epochs];

	for (int i = 0; i<epochs; i++) {
		for (int j = 0; j<32; j++){
			this->obs.sv_L1[i].push_back(sv_L1[i][j]);
			this->obs.pr_L1[i].push_back(pr_L1[i][j]);
			this->obs.precise_pr_L1[i].push_back(precise_pr_L1[i][j]);
			this->obs.cp_L1[i].push_back(cp_L1[i][j]);
			this->obs.do_L1[i].push_back(do_L1[i][j]);
			this->obs.snr_L1[i].push_back(snr_L1[i][j]);
			this->obs.lli_L1[i].push_back(lli_L1[i][j]);
			this->obs.ssi_L1[i].push_back(ssi_L1[i][j]);

			this->obs.sv_L2[i].push_back(sv_L2[i][j]);
			this->obs.pr_L2[i].push_back(pr_L2[i][j]);
			this->obs.precise_pr_L2[i].push_back(precise_pr_L2[i][j]);
			this->obs.do_L2[i].push_back(do_L2[i][j]);
			this->obs.cp_L2[i].push_back(cp_L2[i][j]);
			this->obs.snr_L2[i].push_back(snr_L2[i][j]);
			this->obs.lli_L2[i].push_back(lli_L2[i][j]);
			this->obs.ssi_L2[i].push_back(ssi_L2[i][j]);

			this->obs.sv_L5[i].push_back(sv_L5[i][j]);
			this->obs.pr_L5[i].push_back(pr_L5[i][j]);
			this->obs.do_L5[i].push_back(do_L5[i][j]);
			this->obs.cp_L5[i].push_back(cp_L5[i][j]);
			this->obs.snr_L5[i].push_back(snr_L5[i][j]);
			this->obs.lli_L5[i].push_back(lli_L5[i][j]);
			this->obs.ssi_L5[i].push_back(ssi_L5[i][j]);
		}
	}	

}
