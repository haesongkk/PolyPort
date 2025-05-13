#include "pch.h"
#include "AABB.h"

#include "BoxCollider.h"

bool AABB::Intersect(BoxCollider& a, BoxCollider& b)
{
	{
		m_difference = { 0,0 };
		Vector2D aMin = a.GetCenterPos() - a.GetExtends();
		Vector2D aMax = a.GetCenterPos() + a.GetExtends();
		Vector2D bMin = b.GetCenterPos() - b.GetExtends();
		Vector2D bMax = b.GetCenterPos() + b.GetExtends();
		if (aMin == bMin)
			return true;
		if (aMin.x > bMax.x || aMin.y > bMax.y || aMax.x < bMin.x || aMax.y < bMin.y) 
		{
			return false;
		}
		else 
		{
			
			return true;
		}
	}
}
