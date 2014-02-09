#include <iostream>

#include "ShadowMapFBO.h"

ShadowMapFBO::ShadowMapFBO()
{
	this->m_fbo		  = 0;
	this->m_shadowMap = 0;
}

bool ShadowMapFBO::Init()
{
	GLushort shadowWidth = glutGet(GLUT_WINDOW_WIDTH)  * SHADOW_PRECISION_RATIO;
	GLushort shadowHeight= glutGet(GLUT_WINDOW_HEIGHT) * SHADOW_PRECISION_RATIO;
	

    // Create the FBO
    glGenFramebuffers(1, &this->m_fbo);    

    // Create the depth buffer
    glGenTextures(1, &m_shadowMap);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);
    glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_DEPTH_COMPONENT,
				 shadowWidth,
				 shadowHeight,
				 0,
				 GL_DEPTH_COMPONENT,
				 GL_FLOAT,
				 NULL);
				 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
						   GL_DEPTH_ATTACHMENT,
						   GL_TEXTURE_2D,
						   this->m_shadowMap,
						   0);

    // Disable writes to the color buffer
    glDrawBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        return false;
    }

    return true;
}

void ShadowMapFBO::BindForReading(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, this->m_shadowMap);
}

void ShadowMapFBO::BindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
}

ShadowMapFBO::~ShadowMapFBO()
{
    if (m_fbo != 0) {
        glDeleteFramebuffers(1, &this->m_fbo);
    }

    if (m_shadowMap != 0) {
        glDeleteTextures(1, &this->m_shadowMap);
    }
}