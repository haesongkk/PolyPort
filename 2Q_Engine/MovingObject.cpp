#include "pch.h"
#include "MovingObject.h"

#include "BitmapComponent.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "PlayerObject.h"
#include "TransformComponent.h"

MovingObject::MovingObject()
{
	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetCollisionType(CollisionType::ONEWAY);
	m_pBoxCollider->SetColliderGroup((ColliderGroup::GROUND));
	m_pBoxCollider->SetExtends(50.f,50.f );
	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
}

MovingObject::~MovingObject()
{
}

void MovingObject::Update(float dt)
{
	__super::Update(dt);
	if (m_distance == 0) return;
	auto a = m_pRootComponent->GetRelativeTranslation();
	auto b = min(m_endingPos.x, m_startingPos.x);
	auto c = max(m_endingPos.x, m_startingPos.x);
	if(GetRootComponent()->GetRelativeTranslation().x < min(m_endingPos.x,m_startingPos.x)|| GetRootComponent()->GetRelativeTranslation().x > max(m_endingPos.x, m_startingPos.x))
	{
		m_route = -m_route;
	}
	else if(GetRootComponent()->GetRelativeTranslation().y < min(m_endingPos.y, m_startingPos.y) || GetRootComponent()->GetRelativeTranslation().y > max(m_endingPos.y, m_startingPos.y))
	{
		m_route = -m_route;
	}
	GetRootComponent()->AddRelativeTranslation(m_route * dt / m_distance * 200);
}

void MovingObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	GameObject::Render(pRenderTarget);
}

bool MovingObject::Initialize()
{
	m_route = m_endingPos - m_startingPos;
	m_distance = m_route.Length();
	return __super::Initialize();
}

void MovingObject::OnCollisionEnter(Collider& other)
{
	if (m_distance == 0) return;

	if(other.GetOwner()->GetTag() == "player")
	{
		dynamic_cast<PlayerObject*>(other.GetOwner())->SetAttachedObject(this);
	}
}

void MovingObject::OnCollisionExit(Collider& other)
{
	if (m_distance == 0) return;

	if (other.GetOwner()->GetTag() == "player")
	{
		dynamic_cast<PlayerObject*>(other.GetOwner())->SetAttachedObject(nullptr);
	}
}

void MovingObject::SetSize(int size)
{
	for (int i = 1; i <= size; i++)
	{
		BitmapComponent* bitmap = AddComponent<BitmapComponent>("bitmap");
		if (i == 1) bitmap->SetBitmap(L"../Resource/tile/cloud_b_01.png");
		else if (i == size) bitmap->SetBitmap(L"../Resource/tile/cloud_b_03.png");
		else bitmap->SetBitmap(L"../Resource/tile/cloud_b_02.png");

		if (size % 2 == 0) bitmap->SetRelativeTranslation({ 64.f * (i - size / 2) - 32,0.f });
		else bitmap->SetRelativeTranslation({ 64.f * (i - size / 2 - 1),0.f });
	}
	m_pBoxCollider->SetExtends(size * TileSize / 2,TileSize / 2);
	
}
