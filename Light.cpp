//
//  Light.cpp
//  COG
//

#include <iostream>

#include "Light.h"

Light::Light()
{
	p.setNull();
}

Light::Light(Vvector position, Vvector direction)
{
	p = position;
	d = direction;
}

Light::Light(float px, float py, float pz, float dx, float dy, float dz)
{
	p.set(px, py, pz);
	d.set(dx, dy, dz);
}

void Light::generateDepthTexture()
{
	// Try to use a texture depth component
	glGenTextures(1, &this->depthTextureId);
	glBindTexture(GL_TEXTURE_2D, this->depthTextureId);
	
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	//glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
	
	
	
	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->width, this->height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Light::generateShadowFrameBuffer()
{
	GLenum shadowFrameBufferStatus;

	glGenFramebuffersEXT(1, &this->shadowFrameBufferId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, this->shadowFrameBufferId);
	
	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);
	
	// check FBO status
	shadowFrameBufferStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(shadowFrameBufferStatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		logger::error("Unable to create a shadow frame buffer", FL);
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}