//
//  logger.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 19.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include "logger.h"

#include <iostream>

#define LOG_OUTPUT std::cout

void log(logType type, std::string message,
		std::string file, unsigned short line)
{
	std::string str;
	switch(type) {
		case INFO:
			str = "INFO"; break;
		case WARNING:
			str = "WARNING"; break;
		case ERROR:
			str = "ERROR"; break;
	}

	LOG_OUTPUT << str << " in " << file << " l." << line << " : "
		<< message << std::endl;
}
