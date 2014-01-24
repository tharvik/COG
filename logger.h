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

#include "utilities.h"

enum logType {
  INFO,
  WARNING,
  ERROR
};

void log(logType type, std::string message,
		std::string file, unsigned short line);

#endif
