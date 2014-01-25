//
//  imageLoader.h
//  Cplusplus OpenGL
//

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
	
	void LoadPNM(string src);
	
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
