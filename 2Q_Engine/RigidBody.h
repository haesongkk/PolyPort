#pragma once
#include "TransformComponent.h"

class BoxCollider;

class RigidBody:public TransformComponent
{
private:
	Vector2D m_velocity;
	float m_mass;
	float m_gravity;
	
	const float MAX_GRAVITY = 800.f;

public:
	RigidBody(GameObject* pOwner, string Name, TransformComponent* pRoot)
		:TransformComponent(pOwner, Name, pRoot),
		m_velocity(0, 0),
		m_mass(1.0f),
		m_gravity(100.0f) {}
	virtual ~RigidBody() {}
	virtual void Update(float dt) override;

	bool IsAffectedGravity();

	void SetGravity(float gravity) { m_gravity = gravity; }
	float GetGravity() { return m_gravity; }

	void SetMass(float mass) { m_mass = mass; }
	float GetMass() { return m_mass; }

	void SetXVelocity(float x) { m_velocity.x = x; }
	void SetYVelocity(float y) { m_velocity.y = y; }

	void SetVelocity(Vector2D velocity) { m_velocity = velocity; }
	Vector2D GetVelocity() { return m_velocity; }
	void AddVelocity(Vector2D velocity) { m_velocity += velocity; }

};

