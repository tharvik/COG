//
//  Vvector.cpp
//  COG
//
#include <string.h>

#include "Vvector.h"

#define vx scalar[0]
#define vy scalar[1]
#define vz scalar[2]

Vvector::Vvector()
{
	setNull();
}

Vvector::Vvector(float x, float y, float z)
{
	vx = x;
	vy = y;
	vz = z;
}

void Vvector::set(float x, float y, float z) {
	vx = x;
	vy = y;
	vz = z;
}

void Vvector::setNull()
{
	vx = 0;
	vy = 0;
	vz = 0;
}

double Vvector::length() const
{
	return sqrt(vx*vx + vy*vy + vz*vz);
}

void Vvector::normalize()
{
	double length = this->length();
	vx /= length;
	vy /= length;
	vz /= length;
}

void Vvector::print() const
{
	std::cout << "Vvector ("  << vx << ';' << vy << ';' << vz
			  << ") length: " << this->length() << std::endl;
}

Vvector Vvector::operator+(const Vvector &a)
{
	return Vvector(vx + a.vx, vy + a.vy, vz + a.vz);
}

Vvector Vvector::operator-(const Vvector &a)
{
	return Vvector(vx - a.vx, vy - a.vy, vz - a.vz);
}

Vvector Vvector::operator^(const Vvector &a)
{
	return Vvector(vy*a.vz - vz*a.vy,
				   vz*a.vx - vx*a.vz,
				   vx*a.vy - vy*a.vx);
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

double Vvector::operator*(const Vvector &a)
{
	return vx*a.vx + vy*a.vy + vz*a.vz;
}

bool Vvector::operator==(const Vvector &a)
{
	return vx == a.vx && vy == a.vy && vz == a.vz;
}

bool Vvector::operator!=(const Vvector &a)
{
	return vx != a.vx || vy != a.vy || vz != a.vz;
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