#include "TextureManager.h"

#include <string.h>

#include "stb_image.c"
#include "Logger.h"

TextureManager::TextureManager() {}

Texture TextureManager::load(std::string path)
{
	int x,y,n;
	unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

	if(data == NULL)
		logger::error(std::string("Loading texture \"") + path +
				"\" failed with message: \"" +
				stbi_failure_reason() + "\"", FL);

	int format;
	switch(n) {
		case 1: format = GL_LUMINANCE; break;
		case 2: format = GL_LUMINANCE_ALPHA; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default: format = GL_RGB;
	}

	Texture texture(x, y, format, data);

	stbi_image_free(data);

	return texture;
}
