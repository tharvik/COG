#pragma once

#include <iostream>

#include "Object.h"

class Planet : public Object {
private:
        
public:
        Planet(const std::string& name);
	
        Planet(const std::string& name, Vvector pos);
        
	void draw() const;
};
