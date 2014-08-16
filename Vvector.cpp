#include "Vvector.h"

#include <assert.h>

#define vx scalar[0]
#define vy scalar[1]
#define vz scalar[2]

#define DELTA 0.000001F

// Constructors
Vvector::Vvector() : scalar()
{
	setNull();
}

Vvector::Vvector(const float _x, const float _y, const float _z) : scalar()
{
	vx = _x;
	vy = _y;
	vz = _z;
}

void Vvector::set(const float _x, const float _y, const float _z)
{
	vx = _x;
	vy = _y;
	vz = _z;
}

void Vvector::setNull()
{
	vx = 0;
	vy = 0;
	vz = 0;
}

float Vvector::length() const
{
	return float(sqrt(vx*vx + vy*vy + vz*vz));
}

void Vvector::normalize()
{
	float len = this->length();
	vx /= len;
	vy /= len;
	vz /= len;
}

void Vvector::print() const
{
	std::cout << "Vvector ("  << vx << ';' << vy << ';' << vz
			  << ") length: " << this->length() << std::endl;
}

Vvector Vvector::operator+(const Vvector &a) const
{
	return Vvector(vx + a.vx, vy + a.vy, vz + a.vz);
}

Vvector Vvector::operator-(const Vvector &a) const
{
	return Vvector(vx - a.vx, vy - a.vy, vz - a.vz);
}

Vvector Vvector::operator^(const Vvector &a) const
{
	return Vvector(vy*a.vz - vz*a.vy,
				   vz*a.vx - vx*a.vz,
				   vx*a.vy - vy*a.vx);
}

Vvector Vvector::operator*(const float a) const
{
	return Vvector(vx * a, vy * a, vz * a);
}

void Vvector::operator+=(const Vvector &a)
{
	this->vx += a.vx;
	this->vy += a.vy;
	this->vz += a.vz;
}

void Vvector::operator-=(const Vvector &a)
{
	this->vx -= a.vx;
	this->vy -= a.vy;
	this->vz -= a.vz;
}

void Vvector::operator^=(const Vvector &a) // doesn't work?!
{
	this->vx = vy*a.vz - vz*a.vy;
	this->vy = vz*a.vx - vx*a.vz;
	this->vz = vx*a.vy - vy*a.vx;
}

void Vvector::operator*=(const float a)
{
	this->vx *= a;
	this->vy *= a;
	this->vz *= a;
}

double Vvector::operator*(const Vvector &a) const
{
	return vx*a.vx + vy*a.vy + vz*a.vz;
}

bool Vvector::operator==(const Vvector &a) const
{
	return  fabsf(vx - a.vx) < DELTA &&
		fabsf(vy - a.vy) < DELTA &&
		fabsf(vz - a.vz) < DELTA;
}

bool Vvector::operator!=(const Vvector &a) const
{
	return !(*this == a);
}

float& Vvector::operator[](const unsigned short a)
{
	assert(a < this->scalar.size());
	return this->scalar[a];
}

float Vvector::x() const
{
	return this->vx;
}

float Vvector::y() const
{
	return this->vy;
}

float Vvector::z() const
{
	return this->vz;
}

std::array<float, 3> Vvector::scalars() const
{
	return this->scalar;
}

#undef vx
#undef vy
#undef vz

#undef DELTA
