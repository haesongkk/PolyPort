#pragma once
#include "GameObject.h"
#include "RigidBody.h"

class AnimationComponent;
class MovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class CameraComponent;
class BoxComponent;
class BitmapComponent;
class PlayerObject :
    public GameObject
{
public:
	PlayerObject();
	virtual ~PlayerObject();

	MovementComponent* m_pMovementComponent;
	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	FSMCharacter* m_pFSMCharacter;
	RigidBody* m_pRigidBody;
	BoxComponent* m_pBoxComponent;
	BoxCollider* m_pBoxCollider;
	BitmapComponent* m_pFloatingHUD;
	BoxCollider* m_pSceneCollider;
	GameObject* m_pBubbleObject;
	GameObject* m_pAttachedObject;

	Vector2D ModificationVector(Collider& other);
	bool CheckLand(Collider& other);
	bool m_teleportState;
	bool m_inBubble;

public:

	virtual bool Initialize() override;
	virtual void Update(float dt) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	void AnimationEnd() const;
	
	void FloatingUpdate(float dt);
	void PortUpdate(float dt);

	virtual void OnCollisionEnter(Collider& other)override;
	virtual void OnCollisionStay(Collider& other)override;
	virtual void OnCollisionExit(Collider& other)override;

	virtual void Regame();

	void SetAttachedObject(GameObject* pObject)
	{
		m_pAttachedObject = pObject;
		if (pObject != nullptr)
		{
			m_offset = pObject->GetRootComponent()->GetRelativeTranslation() - GetRootComponent()->GetRelativeTranslation();
		}
	}
	Vector2D m_savepoint;

	vector<wstring> m_floatingKeys;
	bool m_bGetItem;
	int m_itemCount = 0;
	float m_floatingTimer = 0;
	float m_bubbleTimer = 0;
	Vector2D m_offset;

};