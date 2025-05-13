#pragma once
#include "GameObject.h"
class BoxCollider;
class BitmapComponent;
class PlayerObject;

class GemObject : public GameObject
{
public:
	GemObject();
	virtual bool Initialize() override;
	virtual void LateUpdate(float _dt);
	virtual void OnCollisionStay(Collider& other);

	void SetConnectedObject(Vector2D _pos);

	virtual void Regame() override;
private:
	GameObject* m_pConnectedObj;
	BoxCollider* m_pCollider;
	BitmapComponent* m_pBitmap;
	Vector2D m_connectedPos;
	PlayerObject* m_pPlayer;

	Vector2D m_buttonPos;
	Vector2D m_connectedObjPos;

	bool m_bTouch;

};

