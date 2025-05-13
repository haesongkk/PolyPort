#include "pch.h"
#include "CollisionManager.h"

#include "AABB.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "OBB.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Debug.h"
#include "PortObject.h"

CollisionManager* CollisionManager::m_pInstance = nullptr;

CollisionManager::CollisionManager()
	:m_playerBox(nullptr),
	m_otherBoxes()
{
	aabb = new AABB;
	obb = new OBB;
}

CollisionManager::~CollisionManager()
{
	delete aabb;
	delete obb;
	m_otherBoxes.clear();
	m_objectBoxes.clear();
}

bool CollisionManager::BoxCollision(BoxCollider& player, BoxCollider& other)
{

	bool bIsCollision = false;

	if (player.GetColliderType() == ColliderType::OBB || other.GetColliderType() == ColliderType::OBB)
	{
		if (obb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	else
	{
		if (aabb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	return bIsCollision;
}

void CollisionManager::CameraCollision(BoxCollider& camera, BoxCollider& other)
{
	bool bIsCollision = false;
	bool otherCollision = other.GetCollision();
	if (camera.GetColliderType() == ColliderType::OBB || other.GetColliderType() == ColliderType::OBB)
	{
		if (obb->Intersect(camera, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	else
	{
		if (aabb->Intersect(camera, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	if (bIsCollision)
	{
		if (other.GetOwner()->GetTag() == "Fire"||other.GetColliderGroup()==ColliderGroup::DESTINATION)
		{
			m_objectBoxes.push_back(&other);
			//return;
		}
		else if (other.GetOwner()->GetTag() == "port")
		{
			other.GetOwner()->SetVisible(bIsCollision);
			m_objectBoxes.push_back(&other);
			if (m_portObject != nullptr)
				return;
			m_portObject = other.GetOwner();
		}
		else
		{
		other.GetOwner()->SetVisible(bIsCollision);
		m_objectBoxes.push_back(&other);
		}
	}
	else
	{
		if (other.GetOwner()->GetTag() == "Fire" || other.GetColliderGroup() == ColliderGroup::DESTINATION)
		{
			other.SetFireCollision(true);
			//return;
		}
		else if (other.GetOwner()->GetTag() == "port")
		{
			other.GetOwner()->SetVisible(bIsCollision);
		}
		else
		{
			other.GetOwner()->SetVisible(bIsCollision);
		}
	}

}

void CollisionManager::PlayerSceneCollision(BoxCollider& player, BoxCollider& other)
{
	bool bIsCollision = false;
	bool otherCollision = other.GetSceneCollision();

	if (player.GetColliderType() == ColliderType::OBB || other.GetColliderType() == ColliderType::OBB)
	{
		if (obb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}
	else
	{
		if (aabb->Intersect(player, other))
		{
			bIsCollision = true;
		}
		else
		{
			bIsCollision = false;
		}
	}

	if (bIsCollision)
	{

		if (otherCollision)
		{
			other.GetOwner()->OnCollisionStay(player);
			return;
		}
		else
		{
			other.GetOwner()->OnCollisionEnter(player);
			player.GetOwner()->OnCollisionEnter(other);
			other.SetSceneCollision(bIsCollision);
			return;
		}
	}
	else
	{
		if (otherCollision)
		{
			other.SetSceneCollision(bIsCollision);
			other.GetOwner()->OnCollisionExit(player);
			return;
		}

		other.SetSceneCollision(bIsCollision);
	}
}

void CollisionManager::CameraSceneCollision(BoxCollider& camera, BoxCollider& other)
{
}

void CollisionManager::Update()
{
	m_objectBoxes.clear();
	int j = 0, k=0;
	int playerIndex = 0;
	int fire=0;
	int groundCnt=0;
	int collisionGround = 0;
	/*for (int i = 0; i < m_otherBoxes.size(); i++)
	{
		BoxCollision(*m_playerBox, *m_otherBoxes[i]);
	}*/
	for (int i = 0; i < m_otherBoxes.size(); i++)
	{
		CameraCollision(*m_cameraBox, *m_otherBoxes[i]);
	}

	for (int i = 0; i < m_sceneParts.size(); i++)
	{
		CameraSceneCollision(*m_cameraBox, *m_sceneParts[i]);
	}
	if (m_objectBoxes.size() == 0) return;
	else
	{
		for (int i = 0; i < m_objectBoxes.size(); i++)
		{
			if (m_objectBoxes[i]->GetColliderGroup() == ColliderGroup::GROUND)
			{
				groundCnt++;
			}
			if (nullptr != dynamic_cast<PortObject*>(m_objectBoxes[i]->GetOwner()))
			{
				if (m_objectBoxes[i]->GetColliderGroup() == ColliderGroup::DESTINATION && dynamic_cast<PortObject*>(m_objectBoxes[i]->GetOwner())->GetActive())
					fire = i;
			}
			else if (m_objectBoxes[i]->GetColliderGroup() == ColliderGroup::DESTINATION && m_objectBoxes[i]->GetOwner()->IsVisible())
				fire=i;
			if (m_objectBoxes[i]->GetOwner()->GetTag() == "player")
			{
				playerIndex = i;
			}
				for (int k = 0; k < m_sceneParts.size(); k++)
				{
					PlayerSceneCollision(*m_playerBox, *m_sceneParts[k]);
				}

			for (int k = i+1; k < m_objectBoxes.size(); k++)
			{
				BoxCollider* left = m_objectBoxes[i];
				BoxCollider* right = m_objectBoxes[k];
				/*if ((int)m_objectBoxes[i]->GetColliderGroup() > (int)m_objectBoxes[k]->GetColliderGroup())
				{
					left = m_objectBoxes[k];
					right = m_objectBoxes[i];
				}*/
				if (CheckGroup(*left, *right))
				{
					CheckCollision(*left, *right);
				}
			}
		}

	}
	for (j = 0; j < m_objectBoxes.size(); j++)
	{
		if (m_objectBoxes[j]->GetOwner()->GetTag() == "camera" || m_objectBoxes[j]->GetOwner()->GetTag() == "player" || m_objectBoxes[j]->GetColliderGroup() == ColliderGroup::DESTINATION)
			continue;
		if (m_objectBoxes[j]->GetColliderGroup() == ColliderGroup::GROUND && !m_objectBoxes[j]->GetCollision())
			collisionGround++;
	}
	for (k = 0; k < m_objectBoxes.size(); k++)
	{
		if ( m_objectBoxes[k]->GetColliderGroup() == ColliderGroup::DESTINATION)
			continue;
		if (m_objectBoxes[k]->GetFireCollision())
			break;
	}
	if (collisionGround!= 0 && collisionGround==groundCnt)
	{
		m_objectBoxes[playerIndex]->SetCollision(false);
	}
	if (k >= m_objectBoxes.size())
	{
	m_objectBoxes[fire]->SetFireCollision(false);
	}
	
}

void CollisionManager::AddCollider(BoxCollider* boxCollider)
{

	m_otherBoxes.push_back(boxCollider);
}

void CollisionManager::AddScenePart(BoxCollider* boxCollider)
{
	m_sceneParts.push_back(boxCollider);
}

void CollisionManager::SetPlayerCollider(BoxCollider* playerCollider)
{
	m_playerBox = playerCollider;
}

void CollisionManager::SetCameraCollider(BoxCollider* cameraCollider)
{
	m_cameraBox = cameraCollider;
}

void CollisionManager::CheckCollision(BoxCollider& leftBox, BoxCollider& rightBox)
{
	BoxCollider* left = &leftBox;
	BoxCollider* right = &rightBox;

	if ((int)leftBox.GetColliderGroup() > (int)rightBox.GetColliderGroup())
	{
		left = &rightBox;
		right = &leftBox;
	}
	if (CheckGroup(*left, *right))
	{
		if (left->GetColliderGroup() == ColliderGroup::PLAYER)
		{
			bool bIsCollision = false;
			bool otherCollision = right->GetCollision();

			if (left->GetColliderType() == ColliderType::OBB || right->GetColliderType() == ColliderType::OBB)
			{
				if (obb->Intersect(*left, *right))
				{
					bIsCollision = true;
				}
				else
				{
					bIsCollision = false;
				}
			}
			else
			{
				if (aabb->Intersect(*left, *right))
				{
					bIsCollision = true;
				}
				else
				{
					bIsCollision = false;
				}
			}
			if (bIsCollision)
			{

				if (otherCollision)
				{
					left->SetCollision(true);
					left->GetOwner()->OnCollisionStay(*right);
					right->GetOwner()->OnCollisionStay(*left);
					return;
				}
				else
				{
					if (left->GetCollision())
					{
						right->SetCollision(bIsCollision);
						left->GetOwner()->OnCollisionStay(*right);
						right->GetOwner()->OnCollisionEnter(*left);

						return;
					}
					else
					{
						left->SetCollision(bIsCollision);
						right->SetCollision(bIsCollision);
   						left->GetOwner()->OnCollisionEnter(*right);
						right->GetOwner()->OnCollisionEnter(*left);
						return;
					}
				}
			}
			else
			{
				if (otherCollision)
				{
					right->SetCollision(bIsCollision);
 					right->GetOwner()->OnCollisionExit(*left);
					return;
				}
				//player.GetOwner()->OnCollisionExit(other);

				right->SetCollision(bIsCollision);
			}
		}
		else if ((right->GetColliderGroup() == ColliderGroup::DESTINATION && left->GetColliderGroup() == ColliderGroup::GROUND))
			if (!dynamic_cast<PortObject*>(right->GetOwner())->GetActive() || !right->GetOwner()->IsVisible())
				return;
		{
			
			bool bIsCollision = false;
			bool otherCollision = left->GetFireCollision();
			
			
			if (left->GetColliderType() == ColliderType::OBB || right->GetColliderType() == ColliderType::OBB)
			{
				if (obb->Intersect(*left, *right))
				{
					bIsCollision = true;
				}
				else
				{
					bIsCollision = false;
				}
			}
			else
			{
				if (aabb->Intersect(*left, *right))
				{
					bIsCollision = true;
				}
				else
				{
					bIsCollision = false;
				}
			}
			if (bIsCollision)
			{
				if (otherCollision)
				{
					
					return;
				}
				else
				{
					left->SetFireCollision(bIsCollision);
					right->SetFireCollision(bIsCollision);
					return;
				}
			}
			else
			{
				
				if (otherCollision)
				{
					
					left->SetFireCollision(bIsCollision);
					//right->SetFireCollision(bIsCollision);
					return;
				}
				//right->GetOwner()->OnCollisionExit(*left);
				//player.GetOwner()->OnCollisionExit(other);
				
				left->SetFireCollision(bIsCollision);
				///right->SetFireCollision(bIsCollision);
			}
		}
		
	}
}

bool CollisionManager::CheckGroup(BoxCollider& left, BoxCollider& right)
{
	if (left.GetColliderGroup() == ColliderGroup::PLAYER|| right.GetColliderGroup() == ColliderGroup::PLAYER)
	{
		for (int i = (int)ColliderGroup::GROUND; i < (int)ColliderGroup::PARTSCENE; i++)
		{
			if (right.GetColliderGroup() == (ColliderGroup)i|| left.GetColliderGroup() == (ColliderGroup)i)
				return true;
		}
	}
	else if (left.GetColliderGroup() == ColliderGroup::DESTINATION && right.GetColliderGroup() == ColliderGroup::GROUND || right.GetColliderGroup() == ColliderGroup::DESTINATION && left.GetColliderGroup() == ColliderGroup::GROUND)
	{
		return true;
	}
	return false;
}

void CollisionManager::Clear()
{
	m_otherBoxes.clear();
	m_sceneParts.clear();
	m_objectBoxes.clear();
}

