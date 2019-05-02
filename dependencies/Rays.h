#pragma once
#include <cmath>
#include "Vector2.h"
#include "AABB.h"
#include "AABS.h"
#include "Planes.h"
class Rays
{
public:
	Rays();
	Rays(const Vector2& strt, const Vector2& dir, float l = INFINITY);
	~Rays();

	Vector2 closestPoint(const Vector2& point) const;
	bool sphereIntersect(const AABS& sphere, Vector2* I = nullptr, Vector2* R = nullptr) const;
	bool planesIntersect(const Planes& plne, Vector2* I = nullptr, Vector2* R = nullptr) const;
	bool boxIntersect(const AABB& aabb, Vector2* I = nullptr, Vector2* R = nullptr) const;
	float min(const float& a, const float& b) const;
	float max(const float& a, const float& b) const;

	Vector2 origin;
	Vector2 direction;
	float length;
};

