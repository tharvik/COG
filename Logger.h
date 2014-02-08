#pragma once

#include <iostream>
#include <string>

#define FL __FILE__,__LINE__

namespace logger
{
	void info(std::string msg, std::string file, unsigned short line);
	void warn(std::string msg, std::string file, unsigned short line);
	void error(std::string msg, std::string file, unsigned short line);
	void log(std::string msg, std::string file, unsigned short line);

};