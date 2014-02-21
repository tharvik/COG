#pragma once

#include "Object.h"
#include "Vvector.h"

/**
 * Represent a Component of a Ship
 */
class Component : public Object {

	private:
		/**
		 * Current position to move to before drawing
		 */
		Vvector position;

	public:
		/**
		 * Construct with the given Object
		 *
		 * \param object Object to pass to Object constructor
		 */
		Component(const Object& object);

		/**
		 * Construct with the given relative position
		 *
		 * \param object Object to pass to Object constructor
		 * \param position Vvector to draw to (so used in a relative
		 * context) 
		 */
		Component(const Object& object, const Vvector& position);

		/**
		 * Draw the component using it's position
		 *
		 * \todo Implement the drawing relativly with \ref position
		 */
		void draw() const;
};
