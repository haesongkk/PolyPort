#pragma once
#include "GameObject.h"
class BoxCollider;
class BitmapComponent;
class AnimationComponent;
class FireObject;
class EllipseComponent;

class PortObject : public GameObject
{
public:
	PortObject();
	virtual ~PortObject() override;
	
	virtual bool Initialize() override;
	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	void PortActive() { m_bActive = true; }
	bool GetActive() {if(nullptr!=this) return m_bActive; }
	float GetRadius() { return m_radius; }
private:
	float m_radius;
	Vector2D m_playerPos;
	Vector2D m_des;
	Vector2D m_pos;

	BoxCollider* m_pPortCollider;
	BitmapComponent* m_pPortImage;
	EllipseComponent* m_pEllipseComponent;

	TransformComponent* m_pFireTransform;
	AnimationComponent* m_pShadowAnimation;
	BoxCollider* m_pShadowCollider;

	ID2D1SolidColorBrush* m_pBrush = nullptr;

	FireObject* m_pFire;

	GameObject* m_pPlayer;

	bool m_bPreCollision;
	bool m_bCurCollision;

	bool m_bActive;
};

