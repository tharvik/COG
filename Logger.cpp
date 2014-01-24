//
//  logger.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 19.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include "Logger.h"

#include <error.h>

void Logger::log(int status, std::string msg, std::string file,
		unsigned short line)
{
	error_at_line(status, 0, file.c_str(), line, msg.c_str());
}

void Logger::info(std::string msg, std::string file, unsigned short line)
{
	log(0, "INFO " + msg, file, line);
}

void Logger::warn(std::string msg, std::string file, unsigned short line)
{
	log(0, "WARN " + msg, file, line);
}

void Logger::error(std::string msg, std::string file, unsigned short line)
{
	log(1, "ERROR " + msg, file, line);
}
