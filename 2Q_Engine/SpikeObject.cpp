#include "pch.h"
#include "SpikeObject.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "FSMCharacter.h"
#include "PlayerObject.h"

SpikeObject::SpikeObject()
{
	m_pBitmapComponent = AddComponent<BitmapComponent>("BitmapComponent");
	m_pBitmapComponent->SetBitmap(L"../Resource/tile/spike.png");
	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetExtends(10.f,10.f);
	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
	m_pBoxCollider->SetColliderGroup(ColliderGroup::OBSTACLE);

}

SpikeObject::~SpikeObject()
{
}

bool SpikeObject::Initialize()
{

	if(m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 0,-10 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike_02.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 10,0 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike_03.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 0,10 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike_04.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ -10,0 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike2.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 0,20 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike2_02.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ -20,0 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike2_03.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 0,-20 });
	}
	else if (m_pBitmapComponent->GetBitmapkey() == L"../Resource/tile\\spike2_04.png")
	{
		m_pBoxCollider->AddRelativeTranslation({ 20,0 });
	}

	
	return GameObject::Initialize();

	
}

void SpikeObject::Update(float dt)
{
	GameObject::Update(dt);
}

void SpikeObject::OnCollisionEnter(Collider& other)
{
	if(other.m_pOwner->GetTag() == "player")
	{
		dynamic_cast<PlayerObject*>(other.m_pOwner)->m_pFSMCharacter->m_bDeath = true;
	}
}
