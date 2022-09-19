CC = g++
CFLAGS = -Wall -g -Ihome/iza/MESTRADO/gnss-cpp/functions

main: main.o Parse_GPS_obs_from_RINEX.o Date_to_TOW.o RINEX.o

main.o: PP_PPP_GNSS_Test_1.cpp functions/parse/Parse_GPS_obs_from_RINEX.o functions/Date_to_TOW.o
	$(CC) $(CFLAGS) -c PP_PPP_GNSS_Test_1.cpp -o main.o

Parse_GPS_obs_from_RINEX.o: functions/parse/Parse_GPS_obs_from_RINEX.cpp functions/Date_to_TOW.o functions/structs/RINEX.o
	$(CC) $(CFLAGS) -c functions/parse/Parse_GPS_obs_from_RINEX.cpp 

Date_to_TOW.o: functions/Date_to_TOW.cpp
	$(CC) $(CFLAGS) -c functions/Date_to_TOW.cpp

RINEX.o: functions/structs/RINEX.cpp
	$(CC) $(CFLAGS) -c functions/structs/RINEX.cpp




