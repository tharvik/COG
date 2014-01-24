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
	
	for (GLuint i = 0; i < (GLuint) width * height * depth; i++)
		pixels[i] = rand() % (T) (ceil(pow(2, 8 * sizeof(T))) - 1);

	return pixels;
}


template <typename T>
T* generateUVgrid(GLushort width, GLushort height, GLubyte depth)
{
	T* pixels = (T*) calloc(width * height * depth, sizeof(T));
	
	GLuint pixelID = 0;
	
	for (GLushort y = 0; y < height; y++) {
		for (GLushort x = 0; x < width; x++) {
			for (GLubyte d = 0; d < depth; d++) {
				
				pixelID = y * width * depth + x * depth + d;
				
				if(!((y+7 )%16+(x+7 )%16) || !((y+7 )%16+(x+10)%16)
				|| !((y+10)%16+(x+7 )%16) || !((y+10)%16+(x+10)%16))
				{
					if ((y/16 + x/16) % 2)
						pixels[pixelID] = rand() % (T) (ceil(pow(2, 8 * sizeof(T))/3) - 1)
						+ ceil(pow(2, 8 * sizeof(T))/3*2);
					
					else
						pixels[pixelID] = rand() % (T) (ceil(pow(2, 8 * sizeof(T))/1.5) - 1);
				}
				
				else pixels[pixelID] = ((y/16 + x/16) % 2) ? 0x42 : 0xaa;
			}
		}
	}
	
	return pixels;
}