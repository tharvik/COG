#include "Texture.h"

// Constructors
Texture::Texture()
{}

Texture::Texture(GLushort w, GLushort h, GLushort d,
                 imageGenerationOption options)
{
	GLubyte* pixels = (GLubyte*) calloc(w * h * d, sizeof(GLubyte));
	
	switch (options) {
        case RANDOM:
                pixels = generateRandomPixels(w, h, d);
                if (d == 3)
                        createTexture(w, h, GL_RGB, pixels);
                else  if (d == 4)
                        createTexture(w, h, GL_RGBA, pixels);
                valid = true;                           // To check
                break;
        case UV_GRID:
                pixels = generateUVgrid(w, h, 3);
                createTexture(w, h, GL_RGB, pixels);
                valid = true;                           // To check
                break;
        case CHECKERBOARD:
                        
                break;
        default:
                pixels = nullptr; // really?
                break;
	}
        
        free(pixels);
}

Texture::Texture(GLushort width, GLushort height, int format,
		unsigned char *buffer)
{
	createTexture(width, height, format, buffer);
}

Texture::Texture(const std::string& path)
{
	SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface* surface = IMG_Load_RW(rwops, true);
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
        }
}
Texture::Texture(const std::string&& path)
{
	SDL_RWops *rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface *surface = IMG_Load_RW(rwops, true);
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
        }
}

Texture::Texture(const std::string& path, enum imageFileFormat fileFormat)
{
	SDL_RWops *rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface *surface;
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
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
                SDL_FreeRW(rwops);
        }
}
Texture::Texture(const std::string&& path, enum imageFileFormat fileFormat)
{
	SDL_RWops *rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface *surface;
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
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
                SDL_FreeRW(rwops);
        }
}

int Texture::findPixelFormat(SDL_Surface *surface)
{
        switch (surface->format->format) {
        case SDL_PIXELFORMAT_RGB24:     // PNM: ASCII
                return GL_RGB;
        case SDL_PIXELFORMAT_BGR24:     // BMP: RGB_4, RBG_0
                return GL_BGR;
        case SDL_PIXELFORMAT_RGB888:    // GIF: Gray, Palette, RGB
                                        // PNG: Gray, RGB
                                        // PNM: RGB_ASCII, RGB_Binary
                                        // JPG: Gray, Palette, RGB_1, RGB_2,   \
                                                RGB_3, RGB_4, RGB_bad_quality, \
                                                RGB_fast_integer,              \
                                                RGB_floating_point
        case SDL_PIXELFORMAT_ARGB8888:  // GIF: GrayA, PaletteA, RGBA
                                        // PNG: GrayA, PaletteA,               \
                                                RGB_no_compression, RGBA_gamma,\
                                                RGBA_interlacing,              \
                                                RGBA_no_alpha,                 \
                                                RGBA_offset_layer, RGBA
                                        // TIF: Gray, GrayA, RGB,              \
                                                RGBA_déflation, RGBA_jpeg,     \
                                                RGBA_LZW, RGBA_no_compression, \
                                                RGBA_pack_bits
                return GL_BGRA;
        case SDL_PIXELFORMAT_RGBA8888:  // BMP: RGB_5
                return GL_ABGR_EXT;
        case SDL_PIXELFORMAT_INDEX8:    // BMP: Gray
                                        // PNM: Gray_ASCII, Gray_Binary
                return GL_LUMINANCE;
        default:
                logger::warn("Unknow pixel format", FL);
                return GL_RGB;
        }
}

// Loaders
void Texture::load(const std::string&  path)
{
        SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (this->imageId != 0)
                glDeleteTextures(1, &this->imageId);
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface* surface = IMG_Load_RW(rwops, true);
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
        }
}
void Texture::load(const std::string&& path)
{
        SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (this->imageId != 0)
                glDeleteTextures(1, &this->imageId);
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface* surface = IMG_Load_RW(rwops, true);
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
        }
}

void Texture::load(const std::string&  path, enum imageFileFormat fileFormat)
{
        SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (this->imageId != 0)
                glDeleteTextures(1, &this->imageId);
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface *surface;
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
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
                SDL_FreeRW(rwops);
        }
}
void Texture::load(const std::string&& path, enum imageFileFormat fileFormat)
{
        SDL_RWops* rwops = SDL_RWFromFile(path.c_str(), "rb");
        
        if (this->imageId != 0)
                glDeleteTextures(1, &this->imageId);
        if (rwops == NULL) {
                logger::warn("Unable to read from datastream: " + path, FL);
        } else {
                SDL_Surface *surface;
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
                GLubyte* pixels = (GLubyte*) surface->pixels;
                GLushort w = surface->w;
                GLushort h = surface->h;
                createTexture(w, h, findPixelFormat(surface), pixels);
                SDL_FreeSurface(surface);
                SDL_FreeRW(rwops);
        }
}

GLushort findDepth(int &format)
{
        switch (format) {
        case GL_LUMINANCE:
                return 1;
        case GL_RGB:
        case GL_BGR:
                return 3;
        case GL_BGRA:
        case GL_ABGR_EXT:
                return 4;
        default:
                return 3;
        }
}
GLushort findDepth(int &&format)
{
        switch (format) {
                case GL_LUMINANCE:
                        return 1;
                case GL_RGB:
                case GL_BGR:
                        return 3;
                case GL_BGRA:
                case GL_ABGR_EXT:
                        return 4;
                default:
                        return 3;
        }
}

void Texture::createTexture(GLushort &w, GLushort &h, int format,
                            GLubyte* pixels)
{
        glGenTextures(1, &this->imageId);
        glBindTexture(GL_TEXTURE_2D, this->imageId);
        glTexImage2D (GL_TEXTURE_2D, 0, 4, w, h, 0, format,
                      GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLushort Texture::getWidth()
{
        int width;
        glGetTexLevelParameteriv(this->imageId, 0, GL_TEXTURE_WIDTH, &width);
	return (GLushort) width;
}

GLushort Texture::getHeight()
{
        int height;
        glGetTexLevelParameteriv(this->imageId, 0, GL_TEXTURE_HEIGHT, &height);
	return (GLushort) height;
}

GLenum Texture::getFormat()
{
        int format;
        glGetTexLevelParameteriv(this->imageId, 0, GL_TEXTURE_INTERNAL_FORMAT,
                                 &format);
	return format;
}

GLubyte* Texture::getPixels()
{
        GLubyte *pixels = nullptr;
        glGetTexImage(this->imageId, 0, getFormat(), GL_UNSIGNED_BYTE, pixels);
	return pixels;
}

bool Texture::isValid()
{
        return valid;
}

void Texture::bindTexture()
{
        glBindTexture(GL_TEXTURE_2D, this->imageId);
}

Texture::~Texture()
{}
