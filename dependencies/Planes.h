#pragma once
#include "Vector2.h"
#include "AABB.h"
#include "AABS.h"
enum ePlaneResult : int {
	FRONT = -1,
	BACK = -1,
	INTERSECTS = 0
};

class Planes
{
public:
	Planes();
	Planes(float x, float y, float d) : n_vec(x, y), s_offset(d) {}
	Planes(const Vector2& n, float d) : n_vec(n), s_offset(d) {}
	Planes(const Vector2& p1, const Vector2& p2);
	Planes(const Vector2& p1, const Vector2& p2, const Vector2& p3);
	~Planes();

	float distanceTo(const Vector2& p) const;
	Vector2 closestPoint(const Vector2& p) const;

	ePlaneResult testPointSide(const Vector2& p) const;
	ePlaneResult testSphere(const AABS& Sphere) const;
	ePlaneResult testBoxSide(const AABB& aabb) const;

	Vector2	n_vec;
	float s_offset;
};

