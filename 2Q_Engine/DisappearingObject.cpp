#include "pch.h"
#include "DisappearingObject.h"

#include "BitmapComponent.h"
#include "CollisionManager.h"
#include "TileColliderComponent.h"
#include "BoxCollider.h"


DisappearingObject::DisappearingObject()
{
	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetCollisionType(CollisionType::ONEWAY);
	m_pBoxCollider->SetColliderGroup((ColliderGroup::GROUND));
	m_pBoxCollider->SetExtends(50.f, 50.f);
	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
}

DisappearingObject::~DisappearingObject()
{
}

void DisappearingObject::SetSize(int size)
{
	for (int i = 1; i <= size; i++)
	{
		BitmapComponent* bitmap = AddComponent<BitmapComponent>("bitmap");
		if (i == 1) bitmap->SetBitmap(L"../Resource/tile/cloud_y_01.png");
		else if (i == size) bitmap->SetBitmap(L"../Resource/tile/cloud_y_03.png");
		else bitmap->SetBitmap(L"../Resource/tile/cloud_y_02.png");

		if (size % 2 == 0) bitmap->SetRelativeTranslation({ 64.f * (i - size / 2) - 32,0.f });
		else bitmap->SetRelativeTranslation({ 64.f * (i - size / 2 - 1),0.f });

		m_pBitmapComponents.push_back(bitmap);
	}
	m_originEx = { size * TileSize / 2.f, TileSize / 2.f };
	m_pBoxCollider->SetExtends(m_originEx.x , m_originEx.y);
}

void DisappearingObject::Update(float dt)
{
	if(m_bIsTrigger)
	{
		m_timer += dt;
		float opacity = 1 - m_timer * 0.5f;
		if (opacity < 0)
			opacity = 0;
		for (auto bc : m_pBitmapComponents)
			bc->SetOpacity(opacity);
		if(m_timer >=2.f)
		{
			m_bIsExist = false;
			m_bIsTrigger = false;
			m_timer = 0.f;
			m_pBoxCollider->SetCollisionType(CollisionType::UNBLOCK);
			m_pBoxCollider->SetExtends(0.f, 0.f);
		}
	}

	if(!m_bIsExist)
	{
		m_timer += dt;
		if(m_timer >=2.f)
		{
			m_bIsExist = true;
			for (auto bc : m_pBitmapComponents)
				bc->SetOpacity(1.f);
			m_pBoxCollider->SetCollisionType(CollisionType::ONEWAY);
			m_pBoxCollider->SetExtends(m_originEx.x, m_originEx.y);

			m_timer = 0.f;
		}
	}
	__super::Update(dt);
}

void DisappearingObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	GameObject::Render(pRenderTarget);
}

void DisappearingObject::OnCollisionEnter(Collider& other)
{
	if(m_bIsExist)
	{
		if(other.GetOwner()->GetRootComponent()->GetWorldTransform()._32 - 10 < GetRootComponent()->GetWorldTransform()._32)
		{
		m_bIsTrigger = true;
			
		}
	}
}
