#include "Light.h"

// Constructors
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

// Destructor
Light::~Light()
{}