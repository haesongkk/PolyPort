#include "pch.h"
#include "OBB.h"

#include"BoxCollider.h"

bool OBB::Intersect(BoxCollider& a, BoxCollider& b)
{
	
	float aMin, aMax, bMin, bMax;
	Vector2D aAxis[] = { a.m_widthVector,a.m_heightVector };
	Vector2D bAxis[] = { b.m_widthVector,b.m_heightVector };
	for (auto& ax : aAxis)
	{
		aMin = a.GetVertex()[0].x * ax.x + a.GetVertex()[0].y * ax.y;
		bMin = b.GetVertex()[0].x * ax.x + b.GetVertex()[0].y * ax.y;
		aMax = aMin;
		bMax = bMin;
		for (int i = 0; i < 4; i++)
		{
			if (aMin > a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y)
			{
				aMin = a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y;
			}
			else if (aMax < a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y)
			{
				aMax = a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y;
			}
			if (bMin > b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y)
			{
				bMin = b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y;
			}
			else if (bMax < b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y)
			{
				bMax = b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y;
			}
		}
		if (aMin > bMax || bMin > aMax)
			return false;
	}
	for (auto& ax : bAxis)
	{
		aMin = a.GetVertex()[0].x * ax.x + a.GetVertex()[0].y * ax.y;
		bMin = b.GetVertex()[0].x * ax.x + b.GetVertex()[0].y * ax.y;
		aMax = aMin;
		bMax = bMin;
		for (int i = 0; i < 4; i++)
		{
			if (aMin > a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y)
			{
				aMin = a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y;
			}
			else if (aMax < a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y)
			{
				aMax = a.GetVertex()[i].x * ax.x + a.GetVertex()[i].y * ax.y;
			}
			if (bMin > b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y)
			{
				bMin = b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y;
			}
			else if (bMax < b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y)
			{
				bMax = b.GetVertex()[i].x * ax.x + b.GetVertex()[i].y * ax.y;
			}
		}
		if (aMin > bMax || bMin > aMax)
			return false;
	}
	return true;
}
