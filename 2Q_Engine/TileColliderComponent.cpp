#include "pch.h"
#include "TileColliderComponent.h"

#include "GameObject.h"
#include "TileImageComponent.h"
#include "World.h"
#include "Debug.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Event.h"

TileColliderComponent::TileColliderComponent(GameObject* pOwner, string Name, TransformComponent* pRoot)
	:BoxCollider(pOwner, Name, pRoot), m_leftTop{}, m_rightBottom{}
{
	SetCollisionType(CollisionType::BLOCK); 
	m_colliderType = ColliderType::AABB;
	m_colliderGroup = ColliderGroup::GROUND;
}

TileColliderComponent::~TileColliderComponent()
{
}

bool TileColliderComponent::Initialize()
{
	// �ݶ��̴� �»�ܰ� ���ϴ��� Ÿ�� ��ǥ�� �̿��Ͽ� 
	// �ݶ��̴� ���� ��ġ�� Ÿ�ϸ��� ã�� ���ӽ�Ű�� ����
	vector<GameObject*> objects = m_pOwner->GetOwnerWorld()->GetGameObjects();
	for (auto obj : objects)
	{
		// ��� ������Ʈ �� Ÿ�� �̹����� ���� ������Ʈ ã��
		TileImageComponent* tileImage = obj->GetComponent<TileImageComponent>("tileImage");
		if (tileImage == nullptr) continue;

		// �ݶ��̴� ũ�⸸ŭ ����, ���� ���������� ����
		for (int i = m_rightBottom.x; i >= m_leftTop.x; i--)
		{
			if (tileImage->GetTilePos().x != i) continue;

			for (int j = m_rightBottom.y; j >= m_leftTop.y; j--)
			{
				if (tileImage->GetTilePos().y != j) continue;
				
				// �ش� ��ġ�� ������Ʈ�� ã���� ���ӽ�Ų��
				BitmapComponent* bitmap = nullptr;
				if (i != m_rightBottom.x || j != m_rightBottom.y)
				{
					Event::DeleteObject(obj);
					bitmap = m_pOwner->AddComponent<BitmapComponent>("bitmap");

				}
				if (i == m_rightBottom.x && j == m_rightBottom.y)
				{
					bitmap = m_pOwner->GetComponent<TileImageComponent>("tileImage");
				}
				assert(bitmap != nullptr);
				float x = i * TileSize + TileSize / 2 - m_centerPos.x;
				float y = j * TileSize + TileSize / 2 - m_centerPos.y;
				bitmap->SetBitmap(tileImage->GetBitmapkey());
				bitmap->SetRelativeTranslation({ x,y });
				bitmap->SetParentTransform(m_pOwner->GetRootComponent());
				m_pBitmaps.push_back(bitmap);
			}
		}
	}


	if (m_pOwner->GetTag() == "hSpike") 
		SetExtends(2, m_extends.y);
	if (m_pOwner->GetTag() == "vSpike") 
		SetExtends(m_extends.x, 2);
	// test
	//m_pOwner->GetRootComponent()->SetRelativeTranslation({ 0,0 });
	//m_relativeTranslation = { 800,500 };
	return false;
}

void TileColliderComponent::Update(float dt)
{
	TransformComponent::Update(dt);
	m_centerPos = m_pOwner->GetRootComponent()->GetRelativeTranslation();

	wstring x = to_wstring((int)m_pOwner->GetRootComponent()->GetWorldTransform()._31);
	wstring y = to_wstring((int)m_pOwner->GetRootComponent()->GetWorldTransform()._32);

	if (!m_pOwner->IsVisible()) return;
	if(GetCollision() || GetCameraCollision()) Debug::Rect(m_pOwner->GetRootComponent()->GetWorldTransform() * World::m_cameraTransform, { m_extends.x * 2,m_extends.y * 2 }, true, x + L" " + y);
	else Debug::Rect(m_pOwner->GetRootComponent()->GetWorldTransform() * World::m_cameraTransform, { m_extends.x * 2,m_extends.y * 2 }, false, x + L" " + y);

}

void TileColliderComponent::SetTileColliderVertex(POINT _leftTop, POINT _rightBottom)
{
	m_leftTop = _leftTop;
	m_rightBottom = _rightBottom;

	m_centerPos.x = (_leftTop.x + _rightBottom.x + 1) * TileSize / 2;
	m_centerPos.y = (_leftTop.y + _rightBottom.y + 1) * TileSize / 2;

	m_relativeTranslation.x = m_centerPos.x;
	m_relativeTranslation.y = m_centerPos.y ;

	m_extends.x = (_rightBottom.x + 1 - _leftTop.x) * TileSize / 2;
	m_extends.y = (_rightBottom.y + 1 - _leftTop.y) * TileSize / 2;

	m_pOwner->GetRootComponent()->SetRelativeTranslation(m_centerPos);
	SetParentTransform(m_pOwner->GetRootComponent());
}