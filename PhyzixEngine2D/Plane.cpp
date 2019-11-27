#include "Plane.h"
#include <glm/ext.hpp>

Plane::Plane() {}

//Constructor that takes in the values to create a Plane. Since it is static we do not have to worry about Velocity, Mass etc
Plane::Plane(const glm::vec2& normal, float distance, const glm::vec4& colour) : PhysicsObject(ShapeType::PLANE) {
	//distance passes into m_distance
	m_distance = distance;
	//normal passes into m_normal
	m_normal = normal;
	//colour passes into m_colour
	m_colour = colour;
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep) {}

void Plane::debug() {}

void Plane::makeGizmo()
{
	//Length Of One Line
	float lineSegmentLength = 300;
	//Center of the Plane is the Normal * Distance
	glm::vec2 centerPoint = m_normal * m_distance;
	//Parrallel is Drawn by the Y and -X
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	//Start of the plane is the center + the parralel line 
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	//End of the plane is the center - the parralel line 
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	//Draws a 2D Line with a start and an end fresh with colour
	aie::Gizmos::add2DLine(start, end, m_colour);
}

void Plane::resetPosition() {}

void Plane::resolveCollision(RigidBody * actor2)
{
	//Refers to how bouncy and object is ( No Bounce: 0, Super Bounce: 1)
	float elasticity = actor2->getElasticity();
	//Velocity that is returned back to the obj2 that has collided
	glm::vec2 relativeVelocity = actor2->getVelocity();
	//Calculates the impulse magnitude required to shoot the object back  
	// J = DOT(-(1 + elastic) *  incoming velocity, normalised distance / DOT (normalised distance, normalised distance * (1 / mass) + 1 / actor2->getMass)
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), m_normal) / (1 / actor2->getMass());
	//Required Force to Push Back
	glm::vec2 force = m_normal * j;
	//Applied Force
	actor2->applyForce(force);
}

glm::vec2 Plane::getNormal() const
{
	//Returns the Planes Collision Normal
	return m_normal;
}

float Plane::getDistance() const
{
	//Returns the Planes Distance 
	return m_distance;
}

glm::vec4 Plane::getColour() const
{
	//Returns the Planes Colour
	return m_colour;
}

