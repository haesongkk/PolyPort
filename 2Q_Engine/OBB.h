#pragma once

class BoxCollider;

class OBB
{
public:
	bool Intersect(BoxCollider& a, BoxCollider& b);
};

