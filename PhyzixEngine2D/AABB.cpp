#include "AABB.h"

AABB::AABB() { }

//Constructor that Takes in extents and color for the AABB, All other values are shared with the Rigid Body / Shape ID for the AABB is SQUARE
AABB::AABB(const glm::vec2& position, const glm::vec2& extents, const glm::vec2& velocity, float linearVelocity, float elasticity, float mass, const glm::vec4& colour) 
	: RigidBody(SQUARE, position, velocity, linearVelocity, elasticity, 0, mass)
{
	//extents is passed into m_extents
	m_extents = extents;
	//colour is passed into m_colour
	m_colour = colour;
}

AABB::~AABB() { }

void AABB::makeGizmo()
{
	//Draws the AABB by taking a Center : Position / Extents : m_Extents / Colour
	aie::Gizmos::add2DAABB(m_position, m_extents, m_colour);
}

glm::vec2 AABB::getMin() const
{
	//Returns the Position - Extents (W / H)
	return m_position - m_extents;
}

glm::vec2 AABB::getMax() const
{
	//Returns the Position + the Extents (W / H)
	return m_position + m_extents;
}

glm::vec2 AABB::getExtents() const
{
	//Returns the Extents (W / H)
	return m_extents;
}

glm::vec4 AABB::getColour() const
{
	//Returns the Colour of the Box
	return m_colour;
}

std::vector<glm::vec2> AABB::corners() const
{
	//Sets the container to hold 4 items
	std::vector<glm::vec2> corners(4);
	//Holds Both X and Y of Min
	corners[0] = getMin();
	//Holds X of Min and Y of Max
	corners[1] = { getMin().x, getMax().y };
	//Holds Both X and Y of Max
	corners[2] = getMax();
	//Holds X of Max and Y of Min
	corners[3] = { getMax().x, getMin().y };

	//Returns the Corners of the Box
	return corners;
}