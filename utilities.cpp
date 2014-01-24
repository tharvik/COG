//
//  File.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 17.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include <iostream>

bool optionsStatut8b(char options, unsigned char p)
{
	return (options >> p) % 2;
}