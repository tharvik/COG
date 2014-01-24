//
//  imageLoader.h
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 17.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#ifndef Cplusplus_OpenGL_imageLoader_h
#define Cplusplus_OpenGL_imageLoader_h

enum imageOptions {
	PNM = 1<<0
};

#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>

#include "opengl.h"

using namespace std;

class Image {
protected:
	// width, height and depth (RGB, RGBA)
	GLushort w, h, d;
	
	
public:
	// Constructors
	Image();
	Image(GLushort width, GLushort height);
	Image(GLushort width, GLushort height, GLushort depth);

	//getters
	GLushort getWidth();
	GLushort getHeight();
	GLenum	getFormat();
};


class Img8b : public Image{
private:	
	// pixels
	GLubyte *pixels;
	
	// generate random pixels
	void generateRandom(GLushort width, GLushort height);
	
public:
	// Constructor random pixels
	Img8b(GLushort width, GLushort height);
	
	// Constructor from a file
	// @param src file path
	// @param options generate Random | Type
	Img8b(string src, imageOptions options);
	
	// load ASCII/Binary PGM (GRAY), PPM (RGB)
	// @param src file path
	void loadPNM(string src);
		
	// getters
	GLubyte* getPixels();
	
	// transform each pixel by a random one
	void generateRandom();
};

#endif
