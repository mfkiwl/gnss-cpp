CC = g++
CFLAGS = -g -Ihome/iza/MESTRADO/gnss-cpp/functions
#CFLAGS = -Wall -g -Ihome/iza/MESTRADO/gnss-cpp/functions

GNSS_Test_11: GNSS_Test_11.o \
	Parse_GPS_obs_from_RINEX.o \
	Parse_GPS_nav_from_RINEX.o \
	Date_to_TOW.o \
	pv_ECEF_to_NED.o \
	GNSS_WLS_PR_PRR_innov_test.o \
	Euler_to_CTM.o \
	Get_GNSS_data.o \
	RINEX_OBS.o \
	RINEX_NAV.o
	$(CC) $(CFLAGS) -o GNSS_Test_11 GNSS_Test_11.o \
		Parse_GPS_obs_from_RINEX.o \
		Parse_GPS_nav_from_RINEX.o \
		Date_to_TOW.o \
		pv_ECEF_to_NED.o \
		GNSS_WLS_PR_PRR_innov_test.o \
		Euler_to_CTM.o \
		Get_GNSS_data.o \
		RINEX_OBS.o \
		RINEX_NAV.o
	rm -f *.o functions/*.o functions/parse/*.o functions/structs/*.o

PP_PPP_GNSS_Test_1: PP_PPP_GNSS_Test_1.o \
	Parse_GPS_obs_from_RINEX.o \
	Parse_GPS_nav_from_RINEX.o \
	Date_to_TOW.o \
	pv_ECEF_to_NED.o \
	RINEX_OBS.o \
	RINEX_NAV.o
	$(CC) $(CFLAGS) -o PP_PPP_GNSS_Test_1 PP_PPP_GNSS_Test_1.o \
		Parse_GPS_obs_from_RINEX.o \
		Parse_GPS_nav_from_RINEX.o \
		Date_to_TOW.o \
		pv_ECEF_to_NED.o \
		RINEX_OBS.o \
		RINEX_NAV.o
	rm -f *.o functions/*.o functions/parse/*.o functions/structs/*.o

GNSS_Test_11.o: GNSS_Test_11.cpp \
	functions/parse/Parse_GPS_obs_from_RINEX.o \
	functions/parse/Parse_GPS_nav_from_RINEX.o \
	functions/Date_to_TOW.o
	$(CC) $(CFLAGS) -c GNSS_Test_11.cpp -o GNSS_Test_11.o

PP_PPP_GNSS_Test_1.o: PP_PPP_GNSS_Test_1.cpp \
	functions/parse/Parse_GPS_obs_from_RINEX.o \
	functions/parse/Parse_GPS_nav_from_RINEX.o \
	functions/Date_to_TOW.o
	$(CC) $(CFLAGS) -c PP_PPP_GNSS_Test_1.cpp -o  PP_PPP_GNSS_Test_1.o

GNSS_WLS_PR_PRR_innov_test.o: functions/GNSS_WLS_PR_PRR_innov_test.cpp functions/Euler_to_CTM.o functions/Get_GNSS_data.o
	$(CC) $(CFLAGS) -c functions/GNSS_WLS_PR_PRR_innov_test.cpp

Parse_GPS_obs_from_RINEX.o: functions/parse/Parse_GPS_obs_from_RINEX.cpp functions/Date_to_TOW.o functions/structs/RINEX_OBS.o
	$(CC) $(CFLAGS) -c functions/parse/Parse_GPS_obs_from_RINEX.cpp 

Parse_GPS_nav_from_RINEX.o: functions/parse/Parse_GPS_nav_from_RINEX.cpp functions/Date_to_TOW.o functions/structs/RINEX_NAV.o
	$(CC) $(CFLAGS) -c functions/parse/Parse_GPS_nav_from_RINEX.cpp 

Date_to_TOW.o: functions/Date_to_TOW.cpp
	$(CC) $(CFLAGS) -c functions/Date_to_TOW.cpp

pv_ECEF_to_NED.o: functions/pv_ECEF_to_NED.cpp
	$(CC) $(CFLAGS) -c functions/pv_ECEF_to_NED.cpp

RINEX_OBS.o: functions/structs/RINEX_OBS.cpp
	$(CC) $(CFLAGS) -c functions/structs/RINEX_OBS.cpp

RINEX_NAV.o: functions/structs/RINEX_NAV.cpp
	$(CC) $(CFLAGS) -c functions/structs/RINEX_NAV.cpp

Euler_to_CTM.o: functions/Euler_to_CTM.cpp
	$(CC) $(CFLAGS) -c functions/Euler_to_CTM.cpp

Get_GNSS_data.o: functions/Get_GNSS_data.cpp
	$(CC) $(CFLAGS) -c functions/Get_GNSS_data.cpp
