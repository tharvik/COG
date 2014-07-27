#include "Logger.h"

void logger::info(const std::string& msg, const std::string& file,
		const unsigned short line)
{

	log("INFO: " + msg, file, line);
}

void logger::warn(const std::string& msg, const std::string& file,
		const unsigned short line)
{
	log("WARNING: " + msg, file, line);
}

void logger::error(const std::string& msg, const std::string& file,
		const unsigned short line)
{
	log("ERROR: " + msg, file, line);
	exit(1);
}

void logger::log(const std::string& msg, const std::string& file,
		const unsigned short line)
{
	std::string shortFile = file.substr(file.find_last_of("/")+1);
	std::cerr << shortFile << ":" << line << ": " << msg << std::endl;
}
