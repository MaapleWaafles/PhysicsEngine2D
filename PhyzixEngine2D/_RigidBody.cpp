#include "_RigidBody.h"
#include <iostream>

_RigidBody::_RigidBody()  {}

//Constructor that Takes in the Physics Object ID and assigns it's dedicated variables - eg: Position, Velocity etc
_RigidBody::_RigidBody(ShapeType shapeID, const glm::vec2 & position, const glm::vec2 & velocity, float linearVelocity, float elasticity, float rotation, float mass) : 
	      _PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_linearDrag(linearVelocity), m_elasticity(elasticity), m_rotation(rotation), m_mass(mass)
{
	m_isKinematic = false;
}

_RigidBody::~_RigidBody() {}

void _RigidBody::debug() {}

void _RigidBody::applyForce(glm::vec2 force)
{
	//Velocity increases with the amount of force inputed divided by mass
	m_velocity += force / getMass();
}

void _RigidBody::resolveCollision(_RigidBody * actor2)
{
	//Normalised Vector that shrinks and shows the distance between obj1 position and obj2 position
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	//Velocity that is returned back to the obj2 that has collided
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	//Refers to how bouncy and object is ( No Bounce: 0, Super Bounce: 1)
	float elasticity = (m_elasticity + actor2->getElasticity()) / 2;
	//Calculates the impulse magnitude required to shoot the object back  
	// J = DOT(-(1 + elastic) *  incoming velocity, normalised distance / DOT (normalised distance, normalised distance * (1 / mass) + 1 / actor2->getMass)
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / getMass()) + (1 / actor2->getMass())));
	//Required Force to Push Back
	glm::vec2 force = normal * j;
	//Applied Force
	applyForceToActor(actor2, force);
}

void _RigidBody::applyForceToActor(_RigidBody * actor2, glm::vec2 force)
{
	//Applys Force to the first actor
	applyForce(-force);
	//Applys Opposite force to the second actor
	actor2->applyForce(force);
}

void _RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	//Checks if the object is kinematic
	if (m_isKinematic)
		return;

	//Force is applied, with Gravity * Mass * time Step
	applyForce(gravity * getMass() * timeStep);
	//Position is moved through Velocity * Time
	m_position += m_velocity * timeStep;
	//Velocity is decraesed with Velocity * Drag * Time
	m_velocity -= m_velocity * m_linearDrag * timeStep;
}

glm::vec2 _RigidBody::getPosition() const
{
	//Returns the Position
	return m_position;
}

void _RigidBody::setPosition(glm::vec2 newPosition)
{
	//Sets the position to the new position
	m_position = newPosition;
}

float _RigidBody::getRotation() const
{
	//returns our current rotation
	return m_rotation;
}

void _RigidBody::setRotation(float newRotate)
{
	//Sets the rotation to the new rotation
	m_rotation = newRotate;
}

bool _RigidBody::isKinematic()
{
	//Returns the isKinematic Boolean
	return m_isKinematic;
}

void _RigidBody::setKinematic(bool state)
{
	//Sets the isKinematic to the new state
	m_isKinematic = state;
}

glm::vec2 _RigidBody::getVelocity() const
{
	//returns our current velocity
	return m_velocity;
}

void _RigidBody::setVelocity(glm::vec2 newVelocity)
{
	//Sets the velocity to the new velocity
	m_velocity = newVelocity;
}

float _RigidBody::getMass() const
{
	//returns our current mass
	return (m_isKinematic) ? FLT_MAX : m_mass;
}

void _RigidBody::setMass(float newMass)
{
	//Sets the mass to the new mass
	m_mass = newMass;
}

float _RigidBody::getElasticity() const
{
	//returns our current elasticity
	return m_elasticity;
}

void _RigidBody::setElasticity(float newElastic)
{
	//Sets the elasticty to the new elasticity
	m_elasticity = newElastic;
}

