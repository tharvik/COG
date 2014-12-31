#pragma once

#include "opengl.h"
#include <set>
#include <string>

#include "Camera.h"
#include "config.h"
#include "Light.h"
#include "Object.h"
#include "Planet.h"
#include "Event.h"

#include <memory>

#include <BulletDynamics/btBulletDynamicsCommon.h>

#define perspective() gluPerspective(FOV,GLdouble(glutGet(GLUT_WINDOW_WIDTH)/\
        glutGet(GLUT_WINDOW_HEIGHT)),NEAREST,FAREST)

/// The whole Universe
class Universe {
private:
        /// Set of Object the Universe has to draw
        std::set<std::unique_ptr<Object>> objects;

        /// Main Light
        Light mainLight;

        // Physical part of the universe
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;
        
public:

	/**
	 * Enum used with the refresh function, to know what is needed to be
	 * recomputed
	 */
	typedef enum
	{
		NONE  = 0,	/**< no flags **/
		LEVEL = 1	/**< recalculate object mesh levels **/
	} universeRefreshFlags;

        /**
         * Construct with default Camera and the \ref mainLight as a
         * carefully chosen position
         *
         * \todo Why this position for \ref Universe.mainLight?
         */
        Universe();

        const std::set<std::unique_ptr<Object>>& getObjects();
        
	/**
	 * Add a new planet, with the given name, to the \ref objects
	 *
	 * \param name	The name of the planet to create
	 *
	 * \return The previous size of \ref objects
	 */
        size_t addPlanet(const std::string& name);

	/**
	 * Add a new planet, with the given name and position, to the
	 * \ref objects
	 *
	 * \param name	The name of the planet to create
	 * \param pos	The position of the planet to create
	 *
	 * \return The previous size of \ref objects
	 */
        size_t addPlanet(const std::string& name, btVector3 pos);

        void addRigidBody(btRigidBody* rigidBody);
        
        void removeRigidBody(btRigidBody* rigidBody);
        
        void event(const std::unique_ptr<Event>& event);

        /**
         * Reset the perspective, draw the camera and the \ref objects
	 *
	 * \param flags	The type of refresh to do
         */
        void calculateLevel(const Camera& camera);

        /**
         * Handle physic inside the Universe, mainyl forwarded to
         * \ref camera
         *
         * \param physicDelta Delta of physic to compute
         */
        void physics(const double& dt);
        
        /// Draw every Object of \ref objects
        void draw() const;
        
        ~Universe();
};
