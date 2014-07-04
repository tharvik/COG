#pragma once

#include "opengl.h"

#include <iostream>

/**
 * Represent a texture, give faces of a Mesh some image
 */
class Texture {
private:
        /**
         * Buffer used by OpenGL to keep the Texture
         */
        GLuint imageId;
        
public:
        /**
         * Construct an useless Texture but still valid
         */
        Texture();
        
        Texture(const Texture&) = delete;
        
        /**
         * Move constructor, leave \param texture in a useless but valid
         * state
         *
         * \param texture Texture to move from
         */
        Texture(Texture&& texture);
        
        /**
         * Construct with every needed info
         *
         * It will copy the given buffer into GRAM
         *
         * \param width Width of the image
         * \param height Height of the image
         * \param format Pixel format of the image
         * \param buffer Buffer containing the image
         */
        Texture(const unsigned short width, const unsigned short height,
                const int format, unsigned char* buffer);
        
        Texture(const std::string& name);
        
        /**
         * Bind the Texture to use it with OpenGL
         */
        void bindTexture() const;
        
        /**
         * Give a sorting capability
         *
         * \param b Texture to compare to
         *
         * \return True if the local \ref imageId is less than the one
         * of b
         */
        bool operator<(const Texture &b) const;
        
        /**
         * Destruct the Texture, delete his buffer
         */
        ~Texture();
};
