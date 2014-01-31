#include <iostream>
#include <string>

#include "opengl.h"


#ifdef __APPLE__
#	include <SDL2_image/SDL_image.h>
#else
#	include <SDL2/SDL_image.h>
#endif

#ifndef IMAGE_H
#define IMAGE_H

enum imageFileFormat {
	BMP,
	GIF,
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

template <class T>
class Image
{
private:
	// Pixels array
	T* pixels = nullptr; // insecure

	// Width, height and depth (RGB, RGBA)
	GLushort w = 0, h = 0, d = 0;
        
        // Is the image valid (missing texture, loading error...)
        bool valid = false;
        
        GLenum format = GL_RGB;
	
        void findFormatAndDepth(SDL_Surface *surface);

	// buffer for OpenGL
	GLuint imageId;
public:
	// Constructors
	Image(GLushort width, GLushort height, GLushort depth,
		  imageGenerationOption options);
        
        Image(std::string &src);
        Image(std::string &&src);
	Image(std::string &src, enum imageFileFormat imgFormat);
        Image(std::string &&src, enum imageFileFormat imgFormat);
	
	// Getters
	GLushort getWidth();
	GLushort getHeight();
	GLenum	 getFormat();
	T*	 getPixels();
        
        bool     isValid();
	
	// bind as the current texture
	void bindTexture();

	// Destructor
	~Image();
};

#endif
