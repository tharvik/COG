//
//  logger.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 19.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
	public:
		static void info(std::string msg);
		static void warn(std::string msg);
		static void error(std::string msg);

	private:
		static void log(std::string level, std::string msg);
};

Logger log;

#endif
