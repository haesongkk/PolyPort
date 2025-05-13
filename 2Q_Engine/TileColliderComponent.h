#pragma once
#include "BoxCollider.h"
class BitmapComponent;
class TileColliderComponent : public BoxCollider
{
public:
	TileColliderComponent(GameObject* pOwner, string Name, TransformComponent* pRoot);
	virtual ~TileColliderComponent();

	virtual bool Initialize() override;
	virtual void Update(float dt) override;

	void SetTileColliderVertex(POINT _leftTop,POINT _rightBottom);

	POINT GetLeftTop() { return m_leftTop; }
	POINT GetRightBottom() { return m_rightBottom; }
	vector< BitmapComponent*> GetBitmaps() { return m_pBitmaps; }
private:
	POINT m_leftTop;
	POINT m_rightBottom;
	vector< BitmapComponent*> m_pBitmaps;

};
