#ifndef GNSS_WLS_PR_PRR_innov_test_HPP
#define GNSS_WLS_PR_PRR_innov_test_HPP

#include "structs/Structs.hpp"

struct GNSS_WLS {
	int test;
};

GNSS_WLS GNSS_WLS_PR_PRR_innov_test(double in_profile[][10], int no_epochs, GNSS_data GNSS_data, WLS_config WLS_config);

#endif

