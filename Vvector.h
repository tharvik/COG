#pragma once

#include <array>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * Represent a tri-dimensionnal vector of float
 */
class Vvector {
	private:
		/**
		 * Elements of the array
		 */
		std::array<float, 3> scalar;

	public:
		/**
		 * Construct a Vvector of (0,0,0)
		 */
		Vvector();

		/**
		 * Construct a Vvector with the given values
		 *
		 * \param x Value of x
		 * \param y Value of y
		 * \param z Value of z
		 */
		Vvector(float x, float y, float z);

		/**
		 * Set the values
		 *
		 * \param x Value of x
		 * \param y Value of y
		 * \param z Value of z
		 */
		void set(float x, float y, float z);

		/**
		 * Set the Vvector to (0,0,0)
		 */
		void setNull();

		/**
		 * Transform to an unit Vvector
		 */
		void normalize();

		/**
		 * Return the norm
		 *
		 * \return Norm
		 */
		double length() const;

		/**
		 * Print the values
		 */
		void print() const;

		/**
		 * Add this Vvector with the given one
		 *
		 * \param a Vvector to add
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator+(Vvector const& a);

		/**
		 * Substract this Vvector with the given one
		 *
		 * \param a Vvector to substract
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator-(Vvector const& a);

		/**
		 * Cross product this Vvector with the given one
		 *
		 * \param a Vvector to cross product
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator^(Vvector const& a);  // vector product

		/**
		 * Multiply this Vvector by the given factor
		 *
		 * \param a Factor
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator*(const float a);     // scale

		/**
		 * Add to this Vvector, the given one
		 *
		 * \param a Vvector to add to
		 */
		void	operator+=(Vvector const& a);

		/**
		 * Substract to this Vvector, the given one
		 *
		 * \param a Vvector to substract to
		 */
		void	operator-=(Vvector const& a);

		/**
		 * Cross product to this Vvector, the given one
		 *
		 * \param a Vvector to cross product to
		 */
		void	operator^=(Vvector const& a); // vector product

		/**
		 * Update this Vvector by multipling by the given factor
		 *
		 * \param a Factor
		 */
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
