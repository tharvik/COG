#pragma once

#include <array>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

class Vvector {
private:
	std::array<float, 3> scalar;

public:
	// Constructors
	Vvector();
	Vvector(float x, float y, float z);

	// Setters
	void set(float x, float y, float z);
	void setNull();
	void normalize();

	double length() const;
	void print() const;

	Vvector operator+(Vvector const& a);
	Vvector operator-(Vvector const& a);
	Vvector operator^(Vvector const& a);  // vector product
	Vvector operator*(const float a);     // scale

	void	operator+=(Vvector const& a);
	void	operator-=(Vvector const& a);
	void	operator^=(Vvector const& a); // vector product
	void	operator*=(const float a);    // scale

	double operator*(Vvector const& a);   // dot product

	bool	operator==(Vvector const& a);
	bool	operator!=(Vvector const& a);

	float&	operator[](const unsigned short a);
	
	// Getters
	float x() const;
	float y() const;
	float z() const;
	std::array<float, 3> scalars() const;
        
        // Destructor
        ~Vvector();
};
