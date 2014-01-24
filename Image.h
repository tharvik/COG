//
//  imageLoader.h
//  Cplusplus OpenGL
//

// test github

#ifndef COG_Image_h
#define COG_Image_h

enum imageFormat {
	PNM
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

using namespace std;

template <class T>
class Image
{
private:
	// Pixels array
	T* pixels;

	// Width, height and depth (RGB, RGBA)
	GLushort w, h, d;
	
	
	void LoadPNM(string src);
	void PNMloadMagicNumber(ifstream* imgFile, GLushort* numberOfEndl, bool* modeASCII);
	
public:
	// Constructors
	Image(GLushort width, GLushort height, GLushort depth,
		  imageGenerationOption options);
	Image(string src, imageFormat imgFormat);
	
	// Getters
	GLushort getWidth();
	GLushort getHeight();
	GLenum	 getFormat();
	T*		 getPixels();
	
	
	// Destructor
	~Image();
};

#endif
