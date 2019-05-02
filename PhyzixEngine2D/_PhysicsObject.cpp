#include "_PhysicsObject.h"

_PhysicsObject::_PhysicsObject() {}
//Physics Object Constructor that Sets the Objects to thier respective ID
_PhysicsObject::_PhysicsObject(ShapeType shapeid) : m_shapeID(shapeid)
{ }

ShapeType _PhysicsObject::getShapeID()
{
	//Returns the Shapes ID
	return m_shapeID;
}
