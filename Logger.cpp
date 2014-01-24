//
//  logger.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 19.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include "Logger.h"

#include <stdlib.h>
#include <iostream>

void logger::log(std::string msg, std::string file,
		unsigned short line)
{
	std::cerr << file << ":" << line << ": " << msg << std::endl;
}

void logger::info(std::string msg, std::string file, unsigned short line)
{
	log("INFO " + msg, file, line);
}

void logger::warn(std::string msg, std::string file, unsigned short line)
{
	log("WARN " + msg, file, line);
}

void logger::error(std::string msg, std::string file, unsigned short line)
{
	log("ERROR " + msg, file, line);
	exit(1);
}
