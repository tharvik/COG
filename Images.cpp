//
//  imageLoader.cpp
//  Cplusplus OpenGL
//
//  Created by Vianney Rousset on 17.01.14.
//  Copyright (c) 2014 EPFL. All rights reserved.
//

#include "Images.h"
#include "utilities.h"

Image::Image()
{
}

Image::Image(GLushort width, GLushort height) : w(width), h(height)
{
}

Image::Image(GLushort width, GLushort height, GLushort depth) : w(width),
h(height), d(depth)
{
}

unsigned short Image::getWidth()
{
	return w;
}

unsigned short Image::getHeight()
{
	return h;
}

////////////////////////////////////////////////////////////////////////////////

Img8b::Img8b(unsigned short width, unsigned short height) : Image(width, height, 3)
{	
	generateRandom();
	std::cout << "INFO: Image generated." << endl;
}

Img8b::Img8b(string src, imageOptions options) : Image()
{	
	if (optionsStatut8b(options, 0)){
		loadPNM(src);
	}
	std::cout << "INFO: Image loaded." << endl;
}

void Img8b::loadPNM(string src)
{
	GLushort maxIntensity = 0, numberOfChar = 0;

	cout << "INFO: Load PNM." << endl;
	
	ifstream imageFile(src);
	if (imageFile.is_open()) cout << "INFO: File '" << src << "' opened" << endl;
	else cout << "ERROR: File '" << src << "' cannot be opened." << endl;
	
	// get P1, P2, P3, P4, P5 or P6 info
	for (bool i = false; !i;) {
		switch (imageFile.get())
		{
			case '#':
				while (imageFile.get() != '\n') numberOfChar++;
				numberOfChar++;
				break;
				
			case '\n':
				numberOfChar++;
				break;
				
			case 'P':
			case 'p':
				i = true;
				break;
				
			default:
				cout << "WARNING: File corrupted.";
				break;
		}
	}
	
	char formatID = imageFile.get();
	cout << "[P" << formatID << "]" << endl; ///////////////////////////////////
		
	switch (formatID) {
		case '2': // ASCII PGM (Gray)
			cout << "INFO: load ASCII PGM (Gray)." << endl;
			d = 1;			
			break;
			
		case '3': // ASCII PPM (RGB)
			cout << "INFO: load ASCII PPM (RGB)." << endl;
			d = 3;
			break;
			
		default:
			cout << "ERROR: File '" << src << "' corrupted: unknown format P"
			<< formatID << endl;
			break;
	}

	// get size	
	for (bool i = false; !i;) {
		switch (imageFile.get()) {
			case '#':
				while (imageFile.get() != '\n');
				break;
				
			case '\n':
				break;
				
			default:
				imageFile.seekg(-1, ios::cur);
				imageFile >> w;
				imageFile >> h;
				i = 1;
				break;
		}
	}
	cout << w << 'x' << h << endl;//////////////////////////////////////////////
	
	// get maxIntensity	
	for (bool i = false; !i;) {
		switch (imageFile.get()) {
			case '#':
				while (imageFile.get() != '\n');
				break;
				
			case '\n':
				break;
				
			default:
				imageFile.seekg(-1, ios::cur);
				imageFile >> maxIntensity;
				i = 1;
				break;
		}
	}
	cout << "maxIntensity: " << maxIntensity << endl;///////////////////////////
	
	// get pixels
	pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
	for (bool i = false; !i;) {
		switch (imageFile.get()) {
			case '#':
				while (imageFile.get() != '\n');
				break;
				
			case '\n':
				break;
				
			default:
				i = true;
				break;
		}
	}		
	imageFile.seekg(-1, ios::cur);
	
	unsigned short reader = 0;
	switch (maxIntensity) {
		case 255:
			std::cout << d << std::endl;
			for (GLuint i = 0; i < w * h * d; i++) {
				imageFile >> reader;
				pixels[i] = reader;
				//std::cout << i << std::endl;
				//std::cout << i << ": " << pixels[i] << std::endl;
			}
			break;
			
		case 0:
			cout << "WARNING: File '" << src << "': maxIntensity = 0" << endl;
			for (GLuint i = 0; i < w * h * d; i++)
				pixels[i] = 0;
			break;
			
		default:
			cout << "WARNING: File '" << src << "': maxIntensity ≠ 255" << endl;
			for (GLuint i = 0; i < w * h * d; i++) {
				imageFile >> reader;
				pixels[i] = ((double) reader / (double) maxIntensity) * 255;
			}
			break;
	}
	
	std::cout << "end of it" << std::endl;
}

GLubyte* Img8b::getPixels()
{
	return pixels;
}

void Img8b::generateRandom()
{		
	srand((int) time(NULL));
	
	pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
	
	for (int i=0; i < (w * h * d); i++) {
		pixels[i] = rand() % 255;
	}	
}

GLenum Image::getFormat()
{
	switch (d) {
		case 1:
			return GL_LUMINANCE;
			break;
			
		case 3:
			return GL_RGB;
			break;
		case 4:
			return GL_RGBA;
			break;
	}
	return GL_RGB;
}
