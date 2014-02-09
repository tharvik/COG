#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <array>

class Vvector {

private:

#ifdef __APPLE__
	std::array<float, 3> scalar = {1, 2, 3};
#else
	std::array<float, 3> scalar {{1, 2, 3}};
#endif

public:
	
	// constructors
	Vvector();
	Vvector(float x, float y, float z);

	// setters
	void set(float x, float y, float z);
	void setNull();
	void normalize();

	double length() const;
	void print() const;

	Vvector operator+(Vvector const& a);
	Vvector operator-(Vvector const& a);
	Vvector operator^(Vvector const& a);  // vector product

	void	operator+=(Vvector const& a);
	void	operator-=(Vvector const& a);
	void	operator^=(Vvector const& a); // vector product

	double operator*(Vvector const& a);   // dot product

	bool	operator==(Vvector const& a);
	bool	operator!=(Vvector const& a);
	
	// getters
	float x() const;
	float y() const;
	float z() const;
	std::array<float, 3> scalars() const;
};

#define VEC_ZERO(v)		v[0] = 0; v[1] = 0; v[2] = 0;

#define VEC_LENGHT(v)		sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])

#define VEC_NORMALIZE(v)	v[0] = v[0] / VEC_LENGHT(v); \
				v[1] = v[1] / VEC_LENGHT(v); \
				v[2] = v[2] / VEC_LENGHT(v);

#define VEC_COPY(r, v)		r[0] = v[0]; r[1] = v[1]; r[2] = v[2];

#define VEC_SCALE(r, m, v)	r[0] = v[0] * m; \
				r[1] = v[1] * m; \
				r[2] = v[2] * m;

#define VEC_SUM(r, v1, v2)	r[0] = v1[0] + v2[0]; \
				r[1] = v1[1] + v2[1]; \
				r[2] = v1[2] + v2[2];

#define VEC_DIFF(r, v1, v2)	r[0] = v1[0] - v2[0]; \
				r[1] = v1[1] - v2[1]; \
				r[2] = v1[2] - v2[2];
