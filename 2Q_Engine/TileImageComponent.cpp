#include "pch.h"
#include "TileImageComponent.h"

#include "World.h"
#include "GameObject.h"

TileImageComponent::TileImageComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
	:BitmapComponent(pOwner,name,pRoot)
{
}

void TileImageComponent::SetTilePos(POINT _tilePos)
{
	m_tilePos = _tilePos;
	m_relativeTranslation.x = (float)_tilePos.x * TileSize + TileSize / 2;
	m_relativeTranslation.y = (float)_tilePos.y * TileSize + TileSize / 2;
}
