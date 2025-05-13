#pragma once
#include "TransformComponent.h"
enum class ColliderType
{
	AABB,
	OBB,
};

enum class CollisionType
{
	BLOCK,
	UNBLOCK, 
	ONEWAY,
};

enum class ColliderGroup
{
	DEFAULT,
	PLAYER,
	GROUND,
	OBSTACLE,
	ITEM,
	SAVEPOINT,
	BUBBLE,
	PARTSCENE,
	DESTINATION,
	END,
	NONE,
};
class Collider :
	public TransformComponent
{
protected:
	Vector2D m_centerPos = { 0,0 };
	Vector2D m_extends = { 0,0 };

	bool bPlayerCollision;                   //충돌유무
	bool bFireCollision;
	bool bCameraCollision;
	bool bSceneCollision;
	ColliderType m_colliderType;        //충돌체크 타입(AABB,OBB)
	CollisionType m_collisionType;      //통과 가능 유무(Block,Unblock)
	ColliderGroup m_colliderGroup;

public:
	Collider(GameObject* pOwner, string Name, TransformComponent* pRoot)
		:TransformComponent(pOwner, Name, pRoot),
		bPlayerCollision(false),
		m_colliderType(ColliderType::AABB),
		m_collisionType(CollisionType::UNBLOCK)
	{}
	virtual ~Collider() {}

	virtual void Update(float dt) { __super::Update(dt); }

	Vector2D GetCenterPos() { return m_centerPos; }
	void SetCenterPos(float x, float y) { m_centerPos = { x, y }; }

	Vector2D GetExtends() { return m_extends; }
	void SetExtends(float width, float height) {
		m_extends = { width ,height };
	}

	void SetCollision(bool isCollision) { this->bPlayerCollision = isCollision; }
	void SetFireCollision(bool isCollision) { this->bFireCollision = isCollision; }
	void SetCameraCollision(bool isCollision) { this->bCameraCollision = isCollision; }
	void SetSceneCollision(bool isCollision) { bSceneCollision = isCollision; }

	bool GetCollision() const { return bPlayerCollision; }
	bool GetFireCollision() const { return bFireCollision; }
	bool GetCameraCollision() const { return bCameraCollision; }
	bool GetSceneCollision() const { return bSceneCollision; }

	ColliderType GetColliderType() { return m_colliderType; }

	CollisionType GetCollisionType() { return m_collisionType; }
	void SetCollisionType(CollisionType collisionType) { m_collisionType = collisionType; }

	ColliderGroup GetColliderGroup() { return m_colliderGroup; }
	void SetColliderGroup(ColliderGroup group) { m_colliderGroup = group; }

	Vector2D GetMinColliderVector() { return m_centerPos - m_extends; }
	Vector2D GetMaxColliderVector() { return m_centerPos + m_extends; }

};

