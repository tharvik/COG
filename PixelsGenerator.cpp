//
//  PixelsGenerator.cpp
//  COG
//

#include <iostream>
#include "PixelsGenerator.h"
#include <math.h>

template <typename T>
T* generateRandomPixels(GLushort width, GLushort height, GLubyte depth)
{
	srand((int) time(NULL));
	
	T* pixels = (T*) calloc(width * height * depth, sizeof(T));
	for (GLuint i = 0; i < width * height * depth; i++)
		pixels[i] = rand() % (T) (ceil(pow(2, 8 * sizeof(T))) - 1);
		
	return pixels;
}
