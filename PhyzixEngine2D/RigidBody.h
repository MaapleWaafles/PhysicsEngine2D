#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject {
public:
	RigidBody();
	//Set Up Constructor
	RigidBody(ShapeType shapeID, const glm::vec2& position, const glm::vec2& velocity, float linearVelocity, float elasticity, float rotation, float mass);
	~RigidBody();

	virtual void debug();
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	//Resolves Collision with Physics Objects that share Rigid Bodies
	void resolveCollision(RigidBody* actor2);

	//Applys Force to One Object
	void applyForce(glm::vec2 force);
	//Applys Force to Two Objects
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);

	//Gets the Current Position
	glm::vec2 getPosition() const;
	//Sets the New Position
	void setPosition(glm::vec2 newPosition);

	//Gets the Current Rotation
	float getRotation() const;
	//Sets the New Rotation
	void setRotation(float newRotate);

	//Checks if the object is kinematic
	bool isKinematic();
	//Sets the Object to be Kinematic
	void setKinematic(bool state);

	//Gets the Current Velocity
	glm::vec2 getVelocity() const;
	//Sets the New Velocity
	void setVelocity(glm::vec2 newVelocity);

	//Gets the Current Mass
	float getMass() const;
	//Sets the New Mass
	void setMass(float newMass);

	//Gets the Current Elasticity
	float getElasticity() const;
	//Sets the New Elasticity
	void setElasticity(float newElasticity);

protected:

	//Member Variables 
	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_mass;
	float m_rotation;
	float m_elasticity;
	float m_linearDrag;
	float m_angularDrag;

	bool m_isKinematic;
};