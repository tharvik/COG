#include "Image.h"
#include "PixelsGenerator.cpp"

template <class T>
Image<T>::Image(GLushort width, GLushort height, GLushort depth,
				imageGenerationOption options) : w(width), h(height), d(depth), imageId(0)
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
                        pixels = nullptr;
			break;
	}
}

template <class T>
Image<T>::Image(std::string &src) : imageId(0)
{
	SDL_RWops *rwops = SDL_RWFromFile(src.c_str(), "rb");
	SDL_Surface *surface;
        
        if (rwops == NULL) {
                SDL_SetError("Unable to read from datastream");
        } else {
                surface = IMG_Load_RW(rwops, true);
                pixels = (T*) surface->pixels;
                w = surface->w;
                h = surface->h;
                findFormatAndDepth(surface);
        }
}
template <class T>
Image<T>::Image(std::string &&src) : imageId(0)
{
	SDL_RWops *rwops = SDL_RWFromFile(src.c_str(), "rb");
	SDL_Surface *surface;
        
        if (rwops == NULL) {
                SDL_SetError("Unable to read from datastream");
        } else {
                surface = IMG_Load_RW(rwops, true);
                pixels = (T*) surface->pixels;
                w = surface->w;
                h = surface->h;
                findFormatAndDepth(surface);
        }
}

template <class T>
Image<T>::Image(std::string &src, enum imageFileFormat fileFormat) : imageId(0)
{
	SDL_RWops *rwops = SDL_RWFromFile(src.c_str(), "rb");
	SDL_Surface *surface;
        
        if (rwops == NULL) {
                SDL_SetError("Unable to read from datastream");
        } else {
                switch (fileFormat) {
                        case BMP:
                                surface = IMG_LoadBMP_RW(rwops);
                                break;
                        case GIF:
                                surface = IMG_LoadGIF_RW(rwops);
                                break;
                        case PNG:
                                surface = IMG_LoadPNG_RW(rwops);
                                break;
                        case PNM:
                                surface = IMG_LoadPNM_RW(rwops);
                                break;
                        case JPG:
                                surface = IMG_LoadJPG_RW(rwops);
                                break;
                        case TIF:
                                surface = IMG_LoadTIF_RW(rwops);
                                break;
                }
                pixels = (T*) surface->pixels;
                w = surface->w;
                h = surface->h;
                findFormatAndDepth(surface);
        }
}
template <class T>
Image<T>::Image(std::string &&src, enum imageFileFormat fileFormat)
	: imageId(0)
{
	SDL_RWops *rwops = SDL_RWFromFile(src.c_str(), "rb");
	SDL_Surface *surface;
        
        if (rwops == NULL) {
                SDL_SetError("Unable to read from datastream");
        } else {
                switch (fileFormat) {
                        case BMP:
                                surface = IMG_LoadBMP_RW(rwops);
                                break;
                        case GIF:
                                surface = IMG_LoadGIF_RW(rwops);
                                break;
                        case PNG:
                                surface = IMG_LoadPNG_RW(rwops);
                                break;
                        case PNM:
                                surface = IMG_LoadPNM_RW(rwops);
                                break;
                        case JPG:
                                surface = IMG_LoadJPG_RW(rwops);
                                break;
                        case TIF:
                                surface = IMG_LoadTIF_RW(rwops);
                                break;
                }
                pixels = (T*) surface->pixels;
                w = surface->w;
                h = surface->h;
                findFormatAndDepth(surface);
        }
}

template <class T>
void Image<T>::findFormatAndDepth(SDL_Surface *surface)
{
        switch (surface->format->format) {
                case SDL_PIXELFORMAT_RGB24:     // PNM: ASCII
                        format = GL_RGB;
                        d = 3;
                        break;
                case SDL_PIXELFORMAT_BGR24:     // BMP: RGB_4, RBG_0
                        format = GL_BGR;
                        d = 3;
                        break;
                case SDL_PIXELFORMAT_RGB888:    // GIF: Gray, Palette, RGB
                                                // PNG: Gray, RGB
                                                // PNM: RGB_ASCII, RGB_Binary
                                                // JPG: Gray, Palette, RGB_1, RGB_2, RGB_3, RGB_4, RGB_bad_quality, RGB_fast_integer, RGB_floating_point
                case SDL_PIXELFORMAT_ARGB8888:  // GIF: GrayA, PaletteA, RGBA
                                                // PNG: GrayA, PaletteA, RGB_no_compression, RGBA_gamma, RGBA_interlacing, RGBA_no_alpha, RGBA_offset_layer, RGBA
                                                // TIF: Gray, GrayA, RGB, RGBA_déflation, RGBA_jpeg, RGBA_LZW, RGBA_no_compression, RGBA_pack_bits
                        format = GL_BGRA;
                        d = 4;
                        break;
                case SDL_PIXELFORMAT_RGBA8888:  // BMP: RGB_5
                        format = GL_ABGR_EXT;
                        d = 4;
                        break;
                case SDL_PIXELFORMAT_INDEX8:    // BMP: Gray
                                                // PNM: Gray_ASCII, Gray_Binary
                        format = GL_LUMINANCE;
                        d = 1;
                        break;
                default:
                        SDL_SetError("Unknow pixel format");
                        format = GL_RGB;
                        d = 3;
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
bool Image<T>::isValid()
{
        return valid;
}

template <class T>
Image<T>::~Image()
{
	free(pixels);
}

template <class T>
void Image<T>::bindTexture()
{
	if(this->imageId == 0) {

		glGenTextures(1, &this->imageId);
		glBindTexture(GL_TEXTURE_2D, this->imageId);
		glTexImage2D (
				GL_TEXTURE_2D,
				0, 4,
				this->getWidth(),
				this->getHeight(),
				0,
				this->getFormat(),
				GL_UNSIGNED_BYTE,
				this->getPixels()
			     );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
	} else {
		glBindTexture(GL_TEXTURE_2D, this->imageId);
	}
}
