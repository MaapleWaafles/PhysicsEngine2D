#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <Gizmos.h>
#include "_RigidBody.h"
using std::vector;

class _AABB : public _RigidBody {
public:
	_AABB();
	//Setup Constructor for Creating the AABB
	_AABB(const glm::vec2& position, const glm::vec2& extents, const glm::vec2& velocity, float linearVelocity, float elasticity, float mass, const glm::vec4& colour);
	~_AABB();

	//Draws the AABB
	virtual void makeGizmo();

	//Gets the Minimum Axis for the AABB
	glm::vec2 getMin() const;
	//Gets the Maximum Axis for the AABB
	glm::vec2 getMax() const;
	//Gets the Extents (Width and Height) for the AABB
	glm::vec2 getExtents() const;
	//Gets the Colour for the AABB
	glm::vec4 getColour() const;

	//Gets all 4 Corners for the AABB
	std::vector<glm::vec2> corners() const;

protected:

	//Member Variables
	glm::vec2 m_extents;
	glm::vec4 m_colour;
};