#pragma once
#include "pch.h"


class BoxCollider;

class AABB
{
private:
	Vector2D m_difference;
public:
	bool Intersect(BoxCollider& a, BoxCollider& b);
	Vector2D GetDifference() { return m_difference; }

};

