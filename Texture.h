#pragma once

#include "opengl.h"

class Texture {
	private:
		// Buffer for OpenGL
		GLuint imageId;

	public:
		Texture();
		Texture(Texture&& texture);

		Texture(const unsigned short width, const unsigned short height,
				const int format, unsigned char* buffer);

		// bind as the current texture
		void bindTexture() const;

		bool operator<(const Texture &b) const;

		// Destructor
		~Texture();
};
