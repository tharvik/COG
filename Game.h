#pragma once

#include "opengl.h"

#include "Universe.h"
#include "Renderer.h"
#include "Camera.h"
#include "GUI.h"
#include <memory>
#include "Event.h"
#include "RefreshEvent.h"
#include "eventHandler.h"

/// The whole Game
class Game {
private:
        void configureGLUT();
        
public:
        /// The game environement
        static Universe universe;
        
        /// The user interface
        static GUI interface;
        
        /// The renderer
        static Renderer renderer;
        
        /// The cameras
        static std::set<Camera> cameras;
        
        Game();
        
        void event(const std::unique_ptr<Event>& event);
};
