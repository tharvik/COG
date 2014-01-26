//
//  imageLoader.cpp
//  Cplusplus OpenGL
//

#include "Image.h"
#include "utilities.h"
#include "PixelsGenerator.h"
#include "PixelsGenerator.cpp"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2_image/SDL_image.h>

#include "IMG_bmp_loader.cpp"

template <class T>
Image<T>::Image(GLushort width, GLushort height, GLushort depth,
				imageGenerationOption options) : w(width), h(height), d(depth)
{
	pixels = (T*) calloc(w * h * d, sizeof(T));
	
	switch (options) {
		case RANDOM:
			pixels = generateRandomPixels<T>(w, h, d);
			break;
			
		case UV_GRID:
			pixels = generateUVgrid<T>(w, h, d);
			break;
			
		case CHECKERBOARD:
			
			break;
		default:
			break;
	}
}

template <class T>
Image<T>::Image(string src, enum imageFileFormat fileFormat)
{
	SDL_RWops *rwops;
	SDL_Surface *surface;

	switch (fileFormat) {			
		case BMP:
			loadBMPimage(SDL_RWFromFile(src.c_str(), "rb"));
			break;

		case GIF:
			break;
			
		case PNG:
			rwops = SDL_RWFromFile(src.c_str(), "rb");
			surface = IMG_LoadPNG_RW(rwops);
			pixels = (T*) surface->pixels;
			w	   = surface->w;
			h	   = surface->h;
			d	   = surface->format->BytesPerPixel;
			if (d == 4) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGBA;
				else
					format = GL_BGRA;
			} else if (d == 3) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGB;
				else
					format = GL_BGR;
			}
			break;

		case PNM:
			rwops = SDL_RWFromFile(src.c_str(), "rb");
			surface = IMG_LoadPNM_RW(rwops);
			pixels = (T*) surface->pixels;
			w	   = surface->w;
			h	   = surface->h;
			d	   = surface->format->BytesPerPixel;
			if (d == 4) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGBA;
				else
					format = GL_BGRA;
			} else if (d == 3) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGB;
				else
					format = GL_BGR;
			} else if (d == 1) {
				format = GL_LUMINANCE;
			}

			break;
			
		case TIF:
			rwops = SDL_RWFromFile(src.c_str(), "rb");
			surface = IMG_LoadTIF_RW(rwops);
			pixels = (GLubyte*) surface->pixels;
			w	   = surface->w;
			h	   = surface->h;
			d	   = surface->format->BytesPerPixel;
			if (d == 4) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGBA;
				else
					format = GL_BGRA;
			} else if (d == 3) {
				if (surface->format->Rmask == 0x000000FF)
					format = GL_RGB;
				else
					format = GL_BGR;
			}
			break;
			
	}
}

template <class T>
GLushort Image<T>::getWidth()
{
	return w;
}

template <class T>
GLushort Image<T>::getHeight()
{
	return h;
}

template <class T>
GLenum Image<T>::getFormat()
{
	return format;
}

template <class T>
T* Image<T>::getPixels()
{
	return pixels;
}

template <class T>
Image<T>::~Image()
{
	free(pixels);
}
