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
		Vvector(const float x, const float y, const float z);

		/**
		 * Set the values
		 *
		 * \param x Value of x
		 * \param y Value of y
		 * \param z Value of z
		 */
		void set(const float x, const float y, const float z);

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
		Vvector operator+(Vvector const& a) const;

		/**
		 * Substract this Vvector with the given one
		 *
		 * \param a Vvector to substract
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator-(Vvector const& a) const;

		/**
		 * Cross product this Vvector with the given one
		 *
		 * \param a Vvector to cross product
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator^(Vvector const& a) const;

		/**
		 * Multiply this Vvector by the given factor
		 *
		 * \param a Factor
		 *
		 * \return Resulting Vvector
		 */
		Vvector operator*(const float a) const;

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
		void	operator^=(Vvector const& a);

		/**
		 * Update this Vvector by multipling by the given factor
		 *
		 * \param a Factor
		 */
		void	operator*=(const float a);

		/**
		 * Dot product this Vvector with the given one
		 *
		 * \param a to dot product
		 *
		 * \return Result
		 */
		double operator*(Vvector const& a) const;

		/**
		 * Test if the given Vvector is equal
		 *
		 * \param a to test
		 *
		 * \return true if it is equal
		 */
		bool	operator==(Vvector const& a) const;

		/**
		 * Test if the given Vvector is different
		 *
		 * \param a to test
		 *
		 * \return true if it is different
		 */
		bool	operator!=(Vvector const& a) const;

		/**
		 * Return a reference of the value at given indices
		 *
		 * \param a Indice in \ref scalar to return
		 *
		 * \return Reference of the value at the given indice
		 */
		float&	operator[](const unsigned short a);

		/**
		 * Return the value of x
		 *
		 * \return The value of x
		 */
		float x() const;

		/**
		 * Return the value of y
		 *
		 * \return The value of y
		 */
		float y() const;

		/**
		 * Return the value of z
		 *
		 * \return The value of z
		 */
		float z() const;

		/**
		 * Return a copy of \ref scalar
		 *
		 * \return a copy of \ref scalar
		 */
		std::array<float, 3> scalars() const;
};
