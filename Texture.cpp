#include "Texture.h"
#include "stb_image.h"
#include "Logger.h"

using namespace std;


Texture::Texture() : imageId(0)
{}

Texture::Texture(Texture&& texture) : imageId(texture.imageId)
{
	texture.imageId = 0;
}

Texture::Texture(const string& path)
{
	// width, height and number of components
	int x, y, n;
	
	// load image
	uint8_t *data = stbi_load(path.c_str(), &x, &y, &n, 0);
	
	if (data == NULL) {
		logger_error("Unable to load image '" + path + "'");
		return;
	}
	
	GLenum format;
	switch (n) {
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
			
		default:
			break;
	}
	
	// generate openGL texture
	glGenTextures(1, &this->imageId);
        glBindTexture(GL_TEXTURE_2D, this->imageId);
		
        glTexImage2D (GL_TEXTURE_2D, 0, 4, x, y, 0, format,
                      GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	logger_info("Image loaded from '" + path + "'");
}

Texture::Texture(const unsigned short width, const unsigned short height,
		const GLenum format, unsigned char *buffer) : imageId(0)
{
        glGenTextures(1, &this->imageId);
        glBindTexture(GL_TEXTURE_2D, this->imageId);
        glTexImage2D (GL_TEXTURE_2D, 0, 4, width, height, 0, format,
                      GL_UNSIGNED_BYTE, buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::bindTexture() const
{
        glBindTexture(GL_TEXTURE_2D, this->imageId);
}

bool Texture::operator<(const Texture &b) const
{
	return this->imageId < b.imageId;
}

Texture::~Texture()
{
	glDeleteBuffers(1, &this->imageId);
}
