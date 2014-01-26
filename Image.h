//
//  imageLoader.h
//  Cplusplus OpenGL
//

/*
Copyright (C) <année> <détenteur du droit d'auteur>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef COG_Image_h
#define COG_Image_h

enum imageFileFormat {
	BMP,
	GIF,
	ICO,
	JPG,
	PNG,
	PNM,
	TIF
};

enum imageGenerationOption {
	RANDOM,
	UV_GRID,
	CHECKERBOARD
};

#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>

#include "opengl.h"
#include <SDL2_image/SDL_image.h>

using namespace std;

template <class T>
class Image
{
private:
	// Pixels array
	T* pixels;

	// Width, height and depth (RGB, RGBA)
	GLushort w, h, d;

	GLenum format = GL_RGB;

	void loadBMPimage(SDL_RWops *src);
	int readRlePixels(SDL_RWops *src, int isRle8); // was static
	void CorrectAlphaChannel(); // was static

public:
	// Constructors
	Image(GLushort width, GLushort height, GLushort depth,
		  imageGenerationOption options);
	Image(string src, enum imageFileFormat imgFormat);

	// Getters
	GLushort getWidth();
	GLushort getHeight();
	GLenum	 getFormat();
	T*		 getPixels();

	// Destructor
	~Image();
};

#endif
