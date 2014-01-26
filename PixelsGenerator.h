//
//  PixelsGenerator.h
//  COG
//

#ifndef COG_PixelsGenerator_h
#define COG_PixelsGenerator_h

#include <math.h>

#include "opengl.h"

GLubyte* generateRandomPixels(GLushort width, GLushort height, GLubyte depth);

GLubyte* generateUVgrid(GLushort width, GLushort height, GLubyte depth);
#endif
