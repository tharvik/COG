#pragma once

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

class Texture {
private:
        // Is the image valid (missing texture, loading error...)
        bool valid = false;
        
        // Buffer for OpenGL
	GLuint imageId = 0;
	
        int findPixelFormat(SDL_Surface *surface);
        GLushort findDepth(const int format) const;
        void createTexture(const GLushort width, const GLushort height,
			const int format, const GLubyte* pixels);
public:
	// Constructors
        Texture();
        Texture(const GLushort width, const GLushort height,
			const GLushort depth,
			const enum imageGenerationOption options);
        Texture(const GLushort width, const GLushort height, const int format,
		unsigned char* buffer);
        
        Texture(const std::string&  path);
        Texture(const std::string&& path);
	Texture(const std::string&  path,
			const enum imageFileFormat fileFormat); // Not tested
        Texture(const std::string&& path,
			const enum imageFileFormat fileFormat); // Not tested
	
        // Loaders
        void load(const std::string&  path); // Not tested
        void load(const std::string&& path); // Not tested
        
	void load(const std::string&  path,
			const enum imageFileFormat fileFormat); // Not tested
        void load(const std::string&& path,
			const enum imageFileFormat fileFormat); // Not tested
        
	// Getters
	GLushort getWidth() const; // Not tested
	GLushort getHeight() const; // Not tested
	GLenum	 getFormat() const; // Not tested
	GLubyte* getPixels() const; // Not tested
        
        bool     isValid() const;
	
	// bind as the current texture
	void bindTexture() const;

	bool operator<(const Texture &b) const;

	// Destructor
	~Texture();
};
