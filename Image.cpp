//
//  imageLoader.cpp
//  Cplusplus OpenGL
//

#include "Image.h"
#include "utilities.h"
#include "PixelsGenerator.h"
#include "PixelsGenerator.cpp"
#include "Logger.h"

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
Image<T>::Image(string src, imageFormat imgFormat)
{
	switch (imgFormat) {
		case PNM:
			LoadPNM(src);
			break;
			
		default:
			break;
	}
}

template <class T>
void Image<T>::LoadPNM(string src)
{
	GLushort maxIntensity(0), numberOfEndl(0);
	bool modeASCII(false);
	
	char buffer = (0);
	
	cout << "INFO: Load PNM." << endl;
	
	ifstream imageFile(src);
	if (imageFile.is_open()) cout << "INFO: File '" << src << "' opened" << endl;
	else cout << "ERROR: File '" << src << "' cannot be opened." << endl;
	
	// get P1, P2, P3, P4, P5 or P6 info
	PNMloadMagicNumber(&imageFile, &numberOfEndl, &modeASCII);
		
	// get size	
	for (bool i = false; !i;) {
		switch (imageFile.get()) {
			case '#':
				while (imageFile.get() != '\n');
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << __LINE__ << endl;
				break;
				
			case '\n':
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << __LINE__ << endl;
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
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
				
			case '\n':
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
				
			default:
				imageFile.seekg(-1, ios::cur);
				imageFile >> maxIntensity;
				i = 1;
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
		}
	}
	cout << "maxIntensity: " << maxIntensity << endl;///////////////////////////
	
	// get pixels
	if (modeASCII) {
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
	}
	
	else
	{
		pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
		imageFile.close();
		ifstream nouvelleImageFile(src, ios::in|ios::binary);
		
		for (unsigned int i = 0; i < numberOfEndl;) {
			nouvelleImageFile.read(&buffer, 1);
			if (buffer == '\n') i++;
			cout << "[" << i << "]" << endl;
		}
		
		for (unsigned int i = 0; i < w * h * d; i++) {
			nouvelleImageFile.read(reinterpret_cast<char*>(pixels), w * h * d);
		}
	}
}

template <class T>
void Image<T>::PNMloadMagicNumber(ifstream* imgFile, GLushort* numberOfEndl, bool* modeASCII)
{
	for (bool i = false; !i;) {
		switch (imgFile->get())
		{
			case '#':
				while (imgFile->get() != '\n');
				(*numberOfEndl)++;
				break;
				
			case '\n':
				(*numberOfEndl)++;
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
	
	char formatID = imgFile->get();	
	cout << "[P" << formatID << "]" << endl; ///////////////////////////////////
	
	switch (formatID) {
		case '2': // ASCII PGM (Gray)
			cout << "INFO: load ASCII PGM (Gray)." << endl;
			d = 1;
			*modeASCII = true;
			break;
			
		case '3': // ASCII PPM (RGB)
			cout << "INFO: load ASCII PPM (RGB)." << endl;
			d = 3;
			*modeASCII = true;
			break;
			
		case '5': // Binary PGM (Gray)
			cout << "INFO: load binary PGM (Gray)." << endl;
			d = 1;
			break;
			
		case '6': // Binary PPM (RGB)
			cout << "INFO: load binary PPM (RGB)." << endl;
			d = 3;
			break;
			
		default:
			cout << "ERROR: File corrupted: unknown format P"
			<< formatID << endl;
			break;
	}

}

//template <class T>
//void Image<T>::PNMloadSize
//{
//
//}

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