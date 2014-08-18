#pragma once

#include <iostream>

#include "Object.h"

/**
 * Represent a planet
 *
 * \todo Should be an usefull object, not only an instantiation of Object
 */
class Planet : public Object {
private:
        
public:
	/**
	 * Create a new planet, with the given name
	 *
	 * \param name The name of the planet
	 */
        Planet(const std::string& name);
	
	/**
	 * Create a new planet, with the given name and position
	 *
	 * \param name	The name of the planet
	 * \param pos	The initial positon of the planet
	 */
        Planet(const std::string& name, Vvector pos);
        
	/**
	 * Draw the planet, currently only forwarding it to Object
	 */
	void draw() const;
};
