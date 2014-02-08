//
//  Light.h
//  COG
//

#pragma once

#include "Vvector.h"
#include "opengl.h"
#include "Logger.h"

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
	
	// constructors
	Light();
	Light(Vvector position, Vvector direction);
	Light(float px, float py, float pz, float dx, float dy, float dz);

	Vvector position();
};