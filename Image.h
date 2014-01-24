//
//  imageLoader.h
//  Cplusplus OpenGL
//

#ifndef COG_Image_h
#define COG_Image_h

enum imageFormat {
	PNM = 1<<0
};

enum imageGenerationOption {
	RANDOM		 = 0,
	UV_GRID		 = 1<<0,
	CHECKERBOARD = 1<<1
};

#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>

#include "opengl.h"

using namespace std;

template <class T>
class Image
{
private:
	// Pixels array
	T* pixels;

	// Width, height and depth (RGB, RGBA)
	GLushort w, h, d;
	
	
public:
	// Constructors
	Image(GLushort width, GLushort height, GLushort depth,
		  imageGenerationOption options);
	
	// Getters
	GLushort getWidth();
	GLushort getHeight();
	GLenum	 getFormat();
	T*		 getPixels();
	
	// Destructor
	~Image();
};

#endif
