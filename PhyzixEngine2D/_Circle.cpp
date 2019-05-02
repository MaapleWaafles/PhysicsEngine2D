#include "_Circle.h"

//Constructor for creating the sphere passing in variables, Segments, Radius and Colour are based of this class. Shares all other variables of the Rigid Body
_Circle::_Circle(const glm::vec2& position, const glm::vec2& velocity, int segments, float linearVelocity, float elasticity, float mass, float radius, const glm::vec4& colour) :
	_RigidBody(CIRCLE, position, velocity, linearVelocity, elasticity, 0, mass)
{
	//radius passes into m_radius
	m_radius = radius;
	//colour passes into m_colour
	m_colour = colour;
	//segments passes into m_segments
	m_segments = segments;
}

_Circle::~_Circle() {}

void _Circle::makeGizmo()
{
	//Draws a Circle with a position, its radius, the amount of edges and the colour
	aie::Gizmos::add2DCircle(m_position, m_radius, m_segments, m_colour, nullptr);
}

float _Circle::getRadius() const
{
	//Returns the Circles Radius
	return m_radius;
}

int _Circle::getSegments() const
{
	//Returns the Circles Segments
	return m_segments;
}

glm::vec4 _Circle::getColour() const
{
	//Returns the Circles Colour
	return m_colour;
}