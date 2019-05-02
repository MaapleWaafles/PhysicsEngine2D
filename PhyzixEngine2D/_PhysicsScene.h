#pragma once
#include <vector>
#include "_PhysicsObject.h"
using std::vector;

class _PhysicsScene {

public:
	_PhysicsScene();
	~_PhysicsScene();

	//Adds a Physics Object as an Actor
	void addActor(_PhysicsObject* actor);
	//Removes a Actor from the Container
	bool removeActor(_PhysicsObject* actor);
	//Updates the items each frame
	void update(float deltaTime);
	//Updates all Gizmos for each frame
	void updateGizmos();
	//Displays data from variables
	void debugScene();

	//Sets the Gravity for the Scene
	void setGravity(const glm::vec2& gravity);
	//Gets the Gravity of the Scenes
	glm::vec2 getGravity() const;

	//Sets the Time Step for the scene
	void setTimeStep(const float& timeStep);
	//Gets the Time Step of the Scene
	float getTimeStep() const;

	//Checks whether the Objects have achieved Collision
	void checkForCollision();

	//Function Pointer for Planes: Plane To Plane Collision, Plane To Circle Collision, Plane To Square Collision
	static bool planetoplane(_PhysicsObject*, _PhysicsObject*);
	static bool planetocircle(_PhysicsObject*, _PhysicsObject*);
	static bool planetosquare(_PhysicsObject*, _PhysicsObject*);

	//Function Pointer for Circles: Plane To Plane Collision, Plane To Circle Collision, Plane To Square Collision
	static bool circletoplane(_PhysicsObject*, _PhysicsObject*);
	static bool circletocircle(_PhysicsObject*, _PhysicsObject*);
	static bool circletosquare(_PhysicsObject*, _PhysicsObject*);

	//Function Pointer for Planes: Plane To Plane Collision, Plane To Circle Collision, Plane To Square Collision
	static bool squaretoplane(_PhysicsObject*, _PhysicsObject*);
	static bool squaretocircle(_PhysicsObject*, _PhysicsObject*);
	static bool squaretosquare(_PhysicsObject*, _PhysicsObject*);

protected:

	//Member Variables
	float m_timeStep;
	glm::vec2 m_gravity;
	std::vector<_PhysicsObject*> m_actors;
};
