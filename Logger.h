#include <iostream>
#include "config.h"

#define logger_info(msg)       logger_log(0, "INFO : ", msg)
#define logger_warn(msg)       logger_log(1, "WARN : ", msg)
#define logger_error(msg)      logger_log(2, "ERROR: ", msg)
#define logger_log(level, type, msg)					\
	if(level >= LOGGER_LEVEL) {					\
	std::cerr << __FILE__ ":" << __LINE__ << ": " type << ": "	\
		  << msg << std::endl;					\
	}
