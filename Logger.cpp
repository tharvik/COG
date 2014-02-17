#include "Logger.h"

void logger::info(std::string msg, std::string file, unsigned short line)
{
	log("INFO: " + msg, file, line);
}

void logger::warn(std::string msg, std::string file, unsigned short line)
{
	log("WARNING: " + msg, file, line);
}

void logger::error(std::string msg, std::string file, unsigned short line)
{
	log("ERROR: " + msg, file, line);
	exit(1);
}

void logger::log(std::string msg, std::string file, unsigned short line)
{
	std::cerr << file << ":" << line << ": " << msg << std::endl;
}