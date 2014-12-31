#pragma once

#include "opengl.h"

#include "Logger.h"

#include <LinearMath/btVector3.h>

class Light {
private:
	btVector3 p;
	btVector3 d;
	
	int width, height;
	float intensity;

	GLuint depthTextureId, shadowFrameBufferId;
	
	void generateDepthTexture();
	void generateShadowFrameBuffer();

public:
	// Constructors
	Light();
	Light(const btVector3& position, const btVector3& direction);

	btVector3 position() const;
        
        // Destructor
        ~Light();
};
