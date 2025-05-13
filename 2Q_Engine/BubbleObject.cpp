#include "pch.h"
#include "BubbleObject.h"

#include "EllipseComponent.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "PlayerObject.h"
#include "FireObject.h"
#include "FSMCharacter.h"
#include "BoxCollider.h"
#include "World.h"

BubbleObject::BubbleObject()
{
	m_tag = "Bubble";

	m_radius = 300;

	m_pRootComponent->SetRelativeTranslation({ 700.f,500.f });
	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
	m_pBoxCollider->SetColliderGroup(ColliderGroup::BUBBLE);
	m_pBoxCollider->SetExtends(40.f, 40.f);

	m_pAnimationComponent = AddComponent<AnimationComponent>("AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(L"../Resource/Animation/BubbleAnimation.txt");
	m_pAnimationComponent->SetAnimation("Idle", false, true);



	m_pFSMComponent = AddComponent<FSMComponent>("FSMComponent");
	m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>("Bubble");

	

}
BubbleObject::~BubbleObject()
{
}

void BubbleObject::OnCollisionEnter(Collider& other)
{
	if (m_bIsActive == false)
		return;
	if(other.m_pOwner->GetTag() == "player")
	{
		m_bInteract = true;
		dynamic_cast<PlayerObject*>(other.m_pOwner)->m_pFSMCharacter->m_bBubble = true;
		m_pFSMCharacter->m_bInteract = true;
		other.GetOwner()->GetRootComponent()->SetRelativeTranslation({GetRootComponent()->GetRelativeTranslation().x - 10, GetRootComponent()->GetRelativeTranslation().y});
	}
	
}

void BubbleObject::OnCollisionExit(Collider& other)
{
	if (other.m_pOwner->GetTag() == "player")
	{
		m_bIsActive = false;
		m_bInteract = false;
		m_pBoxCollider->SetColliderGroup(ColliderGroup::NONE);
		//dynamic_cast<PlayerObject*>(other.m_pOwner)->m_pFSMCharacter->m_bBubble = false;
		other.SetCollision(false);
		m_pFSMCharacter->m_bBurst = true;
		m_pAnimationComponent->SetAnimation("Burst", false, false);
		m_pAnimationComponent->SetFrameIndex(0);
	}
}

bool BubbleObject::Initialize()
{
	m_pFireobject = m_pWorld->CreateGameObject<FireObject>();
	m_pFireobject->GetRootComponent()->SetParentTransform(this->GetRootComponent());
	m_pFireobject->SetRadius(m_radius);
	return __super::Initialize();
}

void BubbleObject::Update(float dt)
{

	
	__super::Update(dt);
	
}

void BubbleObject::LateUpdate(float dt)
{
	if (m_bIsActive)
	{
		SetVisible(true);
		m_activationTimer = 0.f;
	}
	else
	{
		m_activationTimer += dt;
		if (m_activationTimer >= 5.f)
		{
			m_bIsActive = true;
			m_pBoxCollider->SetColliderGroup(ColliderGroup::BUBBLE);
		}
			
		SetVisible(false);
	}
	if (!m_bInteract)
	{
		m_elapsedTime += dt;
		m_pRootComponent->AddRelativeTranslation({ 0,static_cast<float>(sin(static_cast<double>(m_elapsedTime) * 3.14)) });
		m_pFireobject->SetVisible(false);
	}
	if (m_bInteract)
	{
		m_pFireobject->SetVisible(true);
	}
	
}
void BubbleObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void BubbleObject::AnimationEnd() const
{
	m_pFSMCharacter->m_bAnimationComplete = true;
}
