#include "Light.h"

// Constructors
Light::Light() : width(0), height(0), intensity(0), p({0, 0, 0}) // Is btvector automatically set to null?
{}

Light::Light(const btVector3& position, const btVector3& direction) :
	p(position), d(direction), width(0), height(0), intensity(0)
{}

// Destructor
Light::~Light()
{}
