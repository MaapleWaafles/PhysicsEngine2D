#pragma once
#include "RigidBody.h"

class Circle : public RigidBody {
public:
	//Setup Constructor to Create a Circle
	Circle(const glm::vec2& position, const glm::vec2& velocity, int segments, float linearVelocity, float elastic, float mass, float radius, const glm::vec4& colour);
	~Circle();

	//Creats the Circle
	virtual void makeGizmo();

	//Gets The Radius of the Circle
	float getRadius() const;
	//Gets The Segments of the Circle
	int getSegments() const;
	//Gets the Colour of the Circle
	glm::vec4 getColour() const;
	

protected:
	//Member Variables
	float m_radius;
	int m_segments;
	glm::vec4 m_colour;
};