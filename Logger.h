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
		void info(std::string msg, std::string file,
				unsigned short line);
		void warn(std::string msg, std::string file,
				unsigned short line);
		void error(std::string msg, std::string file,
				unsigned short line);

	private:
		void log(std::string msg, std::string file,
				unsigned short line);

};

#endif
