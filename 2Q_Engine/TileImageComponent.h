#pragma once
#include "BitmapComponent.h"
class TileImageComponent : public BitmapComponent
{
public:
	TileImageComponent(GameObject* pOwner, const string name, TransformComponent* pRoot);
	virtual ~TileImageComponent() { }

	void SetTilePos(POINT _tilePos);
	POINT GetTilePos() { return m_tilePos; }

protected:
	POINT m_tilePos;
};

