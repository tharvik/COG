#include "Texture.h"

using namespace std;


Texture::Texture() : imageId(0)
{}

Texture::Texture(Texture&& texture) : imageId(texture.imageId)
{
	texture.imageId = 0;
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
