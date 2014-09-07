#pragma once

#include "opengl.h"

#include <iostream>

//--------------------------------- Texture ----------------------------------//
//									      //
// 
//									      //
//----------------------------------------------------------------------------//

class Texture {
private:
        /**
         * openGL buffer keeping the Texture
         */
        GLuint imageId;
        
public:
        /**
         * default constructor
         */
        Texture();
                
	/**
	 * construct from an image file
	 *
	 * \param path path to the image file
	 */
	 Texture(const std::string& path);
	
	/**
         * construct with every needed info
         *
         * it will copy the given buffer into GRAM
         *
         * \param width width of the image
         * \param height height of the image
         * \param format pixel format of the image
         * \param buffer buffer containing the image
         */
        Texture(const unsigned short width, const unsigned short height,
                const GLenum format, unsigned char* buffer);
	
	/**
	 * delete copy constructor
	 */
        Texture(const Texture&) = delete;
	
        /**
         * move constructor
         *
         * \param texture texture to move from
         */
        Texture(Texture&& texture);
                        
        /**
         * bind the Texture to use it with OpenGL
         */
        void bindTexture() const;
        
        /**
         * give a sorting capability
         *
         * \param b texture to compare to
         *
         * \return true if the local \ref imageId is less than the one
         * of b
         */
        bool operator<(const Texture &b) const;
        
        /**
         * destruct the Texture, delete his buffer
         */
        ~Texture();
};
