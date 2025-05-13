#include "pch.h"
#include "FireObject.h"

#include "AnimationComponent.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Debug.h"
#include "Input.h"
#include "World.h"
#include "PortObject.h"

FireObject::FireObject()
	:m_distance(500.f)
{
	m_tag = "Fire";

	m_bVisible = false;

	m_pAnimationComponent = AddComponent<AnimationComponent>("AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(L"../Resource/Animation/FireAnimation.txt");
	m_pAnimationComponent->SetAnimation("BlueFire", false, true);

	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetExtends(30, 30);
	m_pBoxCollider->SetColliderGroup(ColliderGroup::DESTINATION);

	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
}

FireObject::~FireObject()
{

}

bool FireObject::Initialize()
{
	__super::Initialize();
	return true;
}

void FireObject::Update(float dt)
{
	if (!m_bVisible)
		return;
	if(m_pBoxCollider->GetFireCollision())
	{
		m_pAnimationComponent->SetAnimation("RedFire", false, true);
		m_bIsAble = false;
	}
	else
	{
		m_pAnimationComponent->SetAnimation("BlueFire", false, true);
		m_bIsAble = true;
	}
	
		Vector2D mousePos = { static_cast<float>(Input::GetInstance()->GetRealMousePos().x), static_cast<float>(Input::GetInstance()->GetRealMousePos().y) };
		Vector2D bubblePos = { m_pRootComponent->GetParentTransform()->GetWorldTransform()._31 + World::m_cameraTransform._31, m_pRootComponent->GetParentTransform()->GetWorldTransform()._32 + World::m_cameraTransform._32 };
		Vector2D vector = { mousePos.x - bubblePos.x, mousePos.y - bubblePos.y };
		Debug::Text(L"bubble port : "+to_wstring((int)vector.x) + L" " + to_wstring((int)vector.y));
		float length = vector.Length();
		GetRootComponent()->SetRelativeTranslation({ (vector * m_distance / length).x, (vector * m_distance / length).y });
		__super::Update(dt);

}

void FireObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}



