#pragma once

#include <iostream>
#include <string>

#define _FL_ __FILE__,__LINE__

namespace logger
{
	void info(const std::string& msg, const std::string& file,
			const unsigned short line);
	void warn(const std::string& msg, const std::string& file,
			const unsigned short line);
	void error(const std::string& msg, const std::string& file,
			const unsigned short line);
	void log(const std::string& msg, const std::string& file,
			const unsigned short line);

};
