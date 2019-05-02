#pragma once
#include "Vector2.h"
#include "AABB.h"
class AABS : public AABB
{
public:
	AABS() {};
	AABS(const Vector2& focus, float rad) : center(focus), radius(rad) {};
	~AABS() {};

	Vector2 center;
	float radius;
	Vector2 closestPoint(const Vector2& p) const;
	void VSfit(const Vector2* points, unsigned int count);
	void Vfit(const std::vector<Vector2>& points);
	bool vecOverlaps(const Vector2& p) const;
	bool aabsOverlaps(const AABS& other) const;
	bool collOverlap(const AABB& aabb) const;
};


 