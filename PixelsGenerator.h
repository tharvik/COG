//
//  PixelsGenerator.h
//  COG
//

#ifndef COG_PixelsGenerator_h
#define COG_PixelsGenerator_h

#include <math.h>

#include "opengl.h"

template <typename T>
T* generateRandomPixels(GLushort width, GLushort height, GLubyte depth);

template <typename T>
T* generateUVgrid(GLushort width, GLushort height, GLubyte depth);
#endif
