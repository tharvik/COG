//
//  imageLoader.cpp
//  Cplusplus OpenGL
//

#include "Image.h"
#include "utilities.h"
#include "PixelsGenerator.h"
#include "PixelsGenerator.cpp"

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
	switch (d)
	{
		case 1: return GL_LUMINANCE;

		case 3: return GL_RGB;

		case 4: return GL_RGBA;
	}

	return GL_RGB;
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