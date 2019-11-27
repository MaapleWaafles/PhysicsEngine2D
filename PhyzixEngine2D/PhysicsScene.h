#pragma once
#include <vector>
#include "PhysicsObject.h"
using std::vector;

class PhysicsScene {

public:
	PhysicsScene();
	~PhysicsScene();

	//Adds a Physics Object as an Actor
	void addActor(PhysicsObject* actor);
	//Removes a Actor from the Container
	bool removeActor(PhysicsObject* actor);
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
	static bool planetoplane(PhysicsObject*, PhysicsObject*);
	static bool planetocircle(PhysicsObject*, PhysicsObject*);
	static bool planetosquare(PhysicsObject*, PhysicsObject*);

	//Function Pointer for Circles: Plane To Plane Collision, Plane To Circle Collision, Plane To Square Collision
	static bool circletoplane(PhysicsObject*, PhysicsObject*);
	static bool circletocircle(PhysicsObject*, PhysicsObject*);
	static bool circletosquare(PhysicsObject*, PhysicsObject*);

	//Function Pointer for Planes: Plane To Plane Collision, Plane To Circle Collision, Plane To Square Collision
	static bool squaretoplane(PhysicsObject*, PhysicsObject*);
	static bool squaretocircle(PhysicsObject*, PhysicsObject*);
	static bool squaretosquare(PhysicsObject*, PhysicsObject*);

protected:

	//Member Variables
	float m_timeStep;
	glm::vec2 m_gravity;
	std::vector<PhysicsObject*> m_actors;
};
