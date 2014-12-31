#pragma once

#include "opengl.h"
#include <set>
#include <math.h>
#include <array>

#include "Logger.h"
#include "utilities.h"

/**
 * Handle the Camera for OpenGL
 */
class Camera {
private:
        
public:
        /**
         * Construct with the default values in config.h
         *
         * \ref p is initialized with POS_* from config.h
         *
         * \ref o and \ref r are initstate with ORI_* from config.h and
         * normalized
         *
         * \ref d is set to zero
         */
        Camera();
        
        /**
         * Calculate the next position
         *
         * \param physicDelta Relative move to compute by step, the smaller, the
         * more it will be but the more call it will need
         */
        void physic(const double &physicDelta);
        
        /**
         * Launch gluLookAt with the current state
         */
        void look();
};
