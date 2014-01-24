//
//  logger.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 19.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include "Logger.h"

#include <iostream>
#include <stdlib.h>

void Logger::log(std::string level, std::string msg)
{
	std::cerr << level << ": " << msg << std::endl;
}

void Logger::info(std::string msg)
{
	log("INFO", msg);
}

void Logger::warn(std::string msg)
{
	log("WARNING", msg);
}

void Logger::error(std::string msg)
{
	log("ERROR", msg);
	exit(1);
}
