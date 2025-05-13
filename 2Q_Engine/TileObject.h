#pragma once
#pragma once
#include "GameObject.h"
enum class CollisionType;
class MovementComponent;
class RigidBody;
class TileObject : public GameObject
{
public:
	TileObject();
public:
	virtual bool Initialize() override;
	virtual void Update(float dt) override;

public:
	virtual void OnCollisionEnter(Collider& other);
	virtual void OnCollisionExit(Collider& other);
	virtual void OnCollisionStay(Collider& other);

private:
	CollisionType m_type;
	bool m_bPlayerContact;

	MovementComponent* m_pMovementComponent;
	RigidBody* m_pRigidBody;
};

