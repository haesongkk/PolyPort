#include "pch.h"
#include "BoxCollider.h"

#include "D2DRenderer.h"
#include "Debug.h"
#include "World.h"
#include "GameObject.h"
#include "CameraObject.h"

BoxCollider::BoxCollider(GameObject* pOwner, string Name, TransformComponent* pRoot)
	:Collider(pOwner,Name,pRoot),
	m_widthVector(0, 0),
	m_heightVector(0, 0),
	m_color(RGB(255, 0, 0))

{
}
BoxCollider::~BoxCollider()
{
	if (!m_vertex.empty())
	{
		m_vertex.erase(m_vertex.begin(), m_vertex.end());
	}
	m_vertex.clear();
}

void BoxCollider::Update(float dt)
{
	__super::Update(dt);
	D2D1_MATRIX_3X2_F matrix;
	//m_centerPos = m_pParentComponent->GetRelativeTranslation();
	m_centerPos = { GetWorldTransform()._31,GetWorldTransform()._32 };
	SetVertex();
	SetAxis();
	if (((int)this->GetRelativeRotation() % 90) <= 0)
	{
		m_colliderType = ColliderType::AABB;
	}
	else
	{
		m_colliderType = ColliderType::OBB;
	}

	if (!m_pOwner->IsVisible()) return;

	wstring x = to_wstring((int)GetWorldTransform()._31);
	wstring y = to_wstring((int)GetWorldTransform()._32);
	// 콜라이더 디버그 정보 출력
	if (dynamic_cast<CameraObject*>(m_pOwner) != m_pOwner->GetOwnerWorld()->GetCameraObject())
		matrix = GetWorldTransform() * World::m_cameraTransform;
	else matrix = GetWorldTransform();

	if (GetCollision() || GetCameraCollision()) Debug::Rect(GetWorldTransform() * World::m_cameraTransform, { m_extends.x * 2,m_extends.y * 2 }, true, x + L" " + y);
	else Debug::Rect(GetWorldTransform() * World::m_cameraTransform, { m_extends.x * 2,m_extends.y * 2 }, false, x + L" " + y);
}

void BoxCollider::SetAxis()
{
	m_widthVector = { m_vertex[0].x - m_vertex[1].x,m_vertex[0].y - m_vertex[1].y };
	m_heightVector = { m_vertex[1].x - m_vertex[2].x,m_vertex[1].y - m_vertex[2].y };
	
	m_widthVector.Normalize();
	m_heightVector.Normalize();
}

void BoxCollider::SetVertex()
{
	m_vertex[0] = Vector2D(- m_extends.x, - m_extends.y);
	m_vertex[1]= Vector2D( m_extends.x, - m_extends.y);
	m_vertex[2] = Vector2D( m_extends.x,  m_extends.y);
	m_vertex[3]= Vector2D( - m_extends.x,  m_extends.y);

	D2D1_MATRIX_3X2_F transform = GetWorldTransform();

	m_vertex[0] = { m_vertex[0].x * transform._11 + m_vertex[0].y * transform._21+ transform._31,m_vertex[0].x * transform._12 + m_vertex[0].y * transform._22+ transform._32 };
	m_vertex[1] = { m_vertex[1].x * transform._11 + m_vertex[1].y * transform._21+ transform._31,m_vertex[1].x * transform._12 + m_vertex[1].y * transform._22 + transform._32};
	m_vertex[2] = { m_vertex[2].x * transform._11 + m_vertex[2].y * transform._21+ transform._31,m_vertex[2].x * transform._12 + m_vertex[2].y * transform._22 + transform._32 };
	m_vertex[3] = { m_vertex[3].x * transform._11 + m_vertex[3].y * transform._21+ transform._31,m_vertex[3].x * transform._12 + m_vertex[3].y * transform._22 + transform._32 };
}

