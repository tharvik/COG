#pragma once

#include "opengl.h"

#include "Logger.h"
#include "Vvector.h"

class Light {
private:
	Vvector p;
	Vvector d;
	
	int width, height;
	float intensity;

	GLuint depthTextureId, shadowFrameBufferId;
	
	void generateDepthTexture();
	void generateShadowFrameBuffer();

public:
	// Constructors
	Light();
	Light(const Vvector& position, const Vvector& direction);
	Light(const float px, const float py, const float pz, const float dx,
			const float dy, const float dz);

	Vvector position() const;
        
        // Destructor
        ~Light();
};
