//
//  imageLoader.cpp
//  Cplusplus OpenGL
//

#include "Image.h"
#include "utilities.h"
#include "PixelsGenerator.h"
#include "PixelsGenerator.cpp"
#include "Logger.h"
#include "stb_image.c"

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

		case PNG:
			int onSenFout;
			pixels = stbi_load(src, &w, &h, &onSenFout, 0);
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
		
	cout << "INFO: Load PNM." << endl;
	
	ifstream imageFile(src);
	if (imageFile.is_open()) cout << "INFO: File '" << src << "' opened" << endl;
	else cout << "ERROR: File '" << src << "' cannot be opened." << endl;
	
	PNMloadMagicNumber(imageFile, numberOfEndl, modeASCII);
		
	PNMloadSize(imageFile, numberOfEndl);	
		
	PNMloadMaxIntensity(imageFile, numberOfEndl, maxIntensity);
	
	if (modeASCII)
		PNMloadPixelsASCII(imageFile, maxIntensity);
	
	else
		PNMloadPixelsBinary(imageFile, numberOfEndl, maxIntensity, src);
}

template <class T>
void Image<T>::PNMloadMagicNumber(ifstream& imgFile, GLushort& numberOfEndl,
								  bool& modeASCII)
{
	for (bool i = false; !i;) {
		switch (imgFile.get())
		{
			case '#':
				while (imgFile.get() != '\n');
				numberOfEndl++;
				break;
				
			case '\n':
				numberOfEndl++;
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
	
	char formatID = imgFile.get();	
	
	switch (formatID) {
		case '2': // ASCII PGM (Gray)
			cout << "INFO: load ASCII PGM (Gray)." << endl;
			d = 1;
			modeASCII = true;
			break;
			
		case '3': // ASCII PPM (RGB)
			cout << "INFO: load ASCII PPM (RGB)." << endl;
			d = 3;
			modeASCII = true;
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

template <class T>
void Image<T>::PNMloadSize(ifstream& imgFile, GLushort& numberOfEndl)
{
		for (bool i = false; !i;) {
		switch (imgFile.get()) {
			case '#':
				while (imgFile.get() != '\n');
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << __LINE__ << endl;
				break;
				
			case '\n':
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << __LINE__ << endl;
				break;
				
			default:
				imgFile.seekg(-1, ios::cur);
				imgFile >> w;
				imgFile >> h;
				i = 1;
				break;
		}
	}

}

template <class T>
void Image<T>::PNMloadMaxIntensity(ifstream& imgFile, GLushort& numberOfEndl,
								   GLushort& maxIntensity)
{
	for (bool i = false; !i;) {
		switch (imgFile.get()) {
			case '#':
				while (imgFile.get() != '\n');
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
				
			case '\n':
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
				
			default:
				imgFile.seekg(-1, ios::cur);
				imgFile >> maxIntensity;
				i = 1;
				numberOfEndl++;
				cout << '-' << numberOfEndl << '-' << endl;
				break;
		}
	}
	cout << "maxIntensity: " << maxIntensity << endl;///////////////////////////
}

template <class T>
void Image<T>::PNMloadPixelsASCII(ifstream &imgFile, GLushort maxIntensity)
{
	pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
	for (bool i = false; !i;) {
		switch (imgFile.get()) {
			case '#':
				while (imgFile.get() != '\n');
				break;
				
			case '\n':
				break;
				
			default:
				i = true;
				break;
		}
	}	
	
	imgFile.seekg(-1, ios::cur);
	
	unsigned short reader = 0;
	switch (maxIntensity) {
		case 255:
			std::cout << d << std::endl;
			for (GLuint i = 0; i < w * h * d; i++) {
				imgFile >> reader;
				pixels[i] = reader;
				//std::cout << i << std::endl;
				//std::cout << i << ": " << pixels[i] << std::endl;
			}
			break;
			
		case 0:
			for (GLuint i = 0; i < w * h * d; i++)
				pixels[i] = 0;
			break;
			
		default:
			for (GLuint i = 0; i < w * h * d; i++) {
				imgFile >> reader;
				pixels[i] = ((double) reader / (double) maxIntensity) * 255;
			}
			break;
	}
}

template <class T>
void Image<T>::PNMloadPixelsBinary(ifstream &imgFile, GLushort numberOfEndl,
	GLushort maxIntensity, string src)
{
	char buffer(0);
	
	pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
	imgFile.close();
	ifstream BinaryImgFile(src, ios::in|ios::binary);
	
	for (unsigned int i = 0; i < numberOfEndl;) {
		BinaryImgFile.read(&buffer, 1);
		if (buffer == '\n') i++;
		cout << "[" << i << "]" << endl;
	}
	
	for (unsigned int i = 0; i < w * h * d; i++) {
		BinaryImgFile.read(reinterpret_cast<char*>(pixels), w * h * d);
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
