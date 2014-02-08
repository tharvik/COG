#pragma once

#include <iostream>
#include "opengl.h"
#include <string>

#ifdef __APPLE__
#	include <SDL2_image/SDL_image.h>
#else
#	include <SDL2/SDL_image.h>
#endif

#include "Logger.h"
#include "PixelsGenerator.h"

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

class Texture
{
private:
        // Is the image valid (missing texture, loading error...)
        bool valid = false;
        
        // Buffer for OpenGL
	GLuint imageId = 0;
	
        int findPixelFormat(SDL_Surface *surface);
        GLushort findDepth(int  &format);
        GLushort findDepth(int &&format);
        void createTexture(GLushort &width, GLushort &height, int format,
                           GLubyte* pixels);
public:
	// Constructors
        Texture();
        Texture(GLushort width, GLushort height, GLushort depth,
                enum imageGenerationOption options);
        Texture(GLushort width, GLushort height, int format,
		unsigned char* buffer);
        
        Texture(const std::string&  path);
        Texture(const std::string&& path);
	Texture(const std::string&  path, enum imageFileFormat fileFormat); // Not tested
        Texture(const std::string&& path, enum imageFileFormat fileFormat); // Not tested
	
        // Loaders
        void load(const std::string&  path); // Not tested
        void load(const std::string&& path); // Not tested
        
	void load(const std::string&  path, enum imageFileFormat fileFormat); // Not tested
        void load(const std::string&& path, enum imageFileFormat fileFormat); // Not tested
        
	// Getters
	GLushort getWidth(); // Not tested
	GLushort getHeight(); // Not tested
	GLenum	 getFormat(); // Not tested
	GLubyte* getPixels(); // Not tested
        
        bool     isValid();
	
	// bind as the current texture
	void bindTexture();

	// Destructor
	~Texture();
};
