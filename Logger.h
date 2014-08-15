#include <iostream>

#define logger_info(msg)       logger_log("INFO : ", msg)
#define logger_warn(msg)       logger_log("WARN : ", msg)
#define logger_error(msg)      logger_log("ERROR: ", msg)
#define logger_log(type, msg)  std::cerr << __FILE__ ":" << __LINE__	\
				<< ": " type << ": " << msg << std::endl
