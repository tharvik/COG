#include "Light.h"

// Constructors
Light::Light() : width(0), height(0), intensity(0)
{
	p.setNull();
}

Light::Light(const Vvector& position, const Vvector& direction) :
	p(position), d(direction), width(0), height(0), intensity(0)
{}

Light::Light(const float px, const float py, const float pz, const float dx,
		const float dy, const float dz) :
	width(0), height(0), intensity(0)
{
	p.set(px, py, pz);
	d.set(dx, dy, dz);
}

// Destructor
Light::~Light()
{}
