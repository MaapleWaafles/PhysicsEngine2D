#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() {}
//Physics Object Constructor that Sets the Objects to thier respective ID
PhysicsObject::PhysicsObject(ShapeType shapeid) : m_shapeID(shapeid)
{ }

ShapeType PhysicsObject::getShapeID()
{
	//Returns the Shapes ID
	return m_shapeID;
}
