#pragma once

#include "GameObject.h"

class BitmapComponent;
class BoxCollider;
class DisappearingObject :
	public GameObject
{
public:
	DisappearingObject();
	virtual ~DisappearingObject();

private:
	bool m_bIsTrigger = false;
	bool m_bIsExist = true;
	float m_timer = 0.f;

	vector<BitmapComponent*> m_pBitmapComponents;
	BoxCollider* m_pBoxCollider;
	Vector2D m_originEx;

public:

	void SetSize(int size);
	virtual void Update(float dt) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

	void OnCollisionEnter(Collider& other) override;

};

