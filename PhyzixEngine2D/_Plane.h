#pragma once
#include "_PhysicsObject.h"
#include "_RigidBody.h"

class _Plane : public _PhysicsObject {
public:
	_Plane();
	//Setup Constructor for the Plane
	_Plane(const glm::vec2& normal, float distance, const glm::vec4& colour);
	~_Plane() {};

	//Updates Physics For Each Frame
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	//Displays Variable Info
	virtual void debug();
	//Creates the Physics Object
	virtual void makeGizmo();
	//Resets the Objects Position
	virtual void resetPosition();

	//Resolves all Collisions with Planes that are Rigid Bodies
	void resolveCollision(_RigidBody* actor2);

	//Gets the Collision Normal of the Plane
	glm::vec2 getNormal() const;
	//Gets the Distance of the Plane
	float getDistance() const;
	//Gets the Colour of the Plane
	glm::vec4 getColour() const;

protected:
	//Member Variables
	glm::vec2 m_normal;
	glm::vec4 m_colour;
	float m_distance;
};