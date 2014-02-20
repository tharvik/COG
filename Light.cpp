#include "Light.h"

// Constructors
Light::Light()
{
	p.setNull();
}

Light::Light(const Vvector& position, const Vvector& direction)
{
	p = position;
	d = direction;
}

Light::Light(const float px, const float py, const float pz, const float dx,
		const float dy, const float dz)
{
	p.set(px, py, pz);
	d.set(dx, dy, dz);
}

// Destructor
Light::~Light()
{}
