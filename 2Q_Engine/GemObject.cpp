#include "pch.h"
#include "GemObject.h"

#include "TransformComponent.h"
#include "World.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "BitmapComponent.h"
#include "Sound.h"
#include "PlayerObject.h"
#include "FSMCharacter.h"

GemObject::GemObject()
	:GameObject()
{
	m_pBitmap = AddComponent<BitmapComponent>("bitmap");
	m_pBitmap->SetBitmap(L"../Resource/Tile/gem.png");

	m_pCollider = AddComponent<BoxCollider>("boxCollider");
	m_pCollider->SetColliderGroup(ColliderGroup::ITEM);
	m_pCollider->SetExtends(TileSize / 2, TileSize / 2);
	CollisionManager::GetInstance()->AddCollider(m_pCollider);
}

bool GemObject::Initialize()
{
	vector<GameObject*> objects = GetOwnerWorld()->GetGameObjects();
	GameObject* nearObj = nullptr;
	m_pPlayer = static_cast<PlayerObject*>(m_pWorld->GetPlayerObject());

	float distance = INT_MAX;
	// 가장 가까운 물체가 짝일 경우 _pos는 그냥 자기 위치
	// 이 경우 맵툴에서 한번에 추가 가능
	// 아닌 경우 눈대중으로 포지션 찍고 거기서 가장 가까운 구름 찾게 하기
	// 이 경우 구름들은 맵툴에서 추가하고 젬은 직접 추가하기
	for (auto obj : objects)
	{
		if (obj->GetTag() != "gemConnect") continue;
		Vector2D pos = obj->GetRootComponent()->GetRelativeTranslation();
		Vector2D dif = pos - m_connectedPos;
		if (dif.Length() < distance)
		{
			distance = dif.Length();
			nearObj = obj;
		}
	}

	assert(nearObj != nullptr);
	m_pConnectedObj = nearObj;

	m_pRootComponent->AddRelativeTranslation({ 16,16 });
	return __super::Initialize();
}

void GemObject::LateUpdate(float _dt)
{
	if (m_bTouch)
	{
		m_bVisible = false;
		m_pConnectedObj->SetVisible(false);
	}
	if (m_pPlayer->m_pFSMCharacter->m_bDeath)
	{
		Regame();
		m_pConnectedObj->Regame();
	}
}

void GemObject::OnCollisionStay(Collider& other)
{
	m_buttonPos = m_pRootComponent->GetRelativeTranslation();
	m_connectedObjPos = m_pConnectedObj->GetRootComponent()->GetRelativeTranslation();

	m_bTouch = true;
	m_pRootComponent->SetRelativeTranslation({ -1000,-1000 });
	m_pConnectedObj->GetRootComponent()->SetRelativeTranslation({ -1000,-1000 });
	Sound::Play(SFX, "../Resource/sound/acquire_gem.mp3");
	// -1000,-1000... 여긴 쓰레기통.....
}

void GemObject::SetConnectedObject(Vector2D _pos)
{
	m_connectedPos = _pos;
	
}

void GemObject::Regame()
{
	m_bTouch = false;
	__super::Regame();
}

