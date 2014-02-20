#pragma once

#include <iostream>
#include <math.h>
#include "opengl.h"

GLubyte* generateRandomPixels(const GLushort width, const GLushort height,
		const GLubyte depth);
GLubyte* generateUVgrid(const GLushort width, const GLushort height,
		const GLubyte depth);
