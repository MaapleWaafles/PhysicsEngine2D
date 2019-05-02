#pragma once
#include <glm/ext.hpp>
#include <Gizmos.h>

enum ShapeType {
	PLANE = 0,
	CIRCLE,
	SQUARE,

	SHAPE_COUNT
};

class _PhysicsObject {

protected:
	_PhysicsObject();
	//Constructor that asks for what shape we are using. This then diretly assigns it to the Phys_ShapeID which is of the enum type
	_PhysicsObject(ShapeType shapeid);

public:
	//Virtual ensures that the correct function is called
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}

	//Gets The ShapeID of the Specific Object
	ShapeType getShapeID();
protected:
	//ID holder of ShapeType
	ShapeType m_shapeID;
};
