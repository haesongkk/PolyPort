#include "pch.h"
#include "CameraObject.h"

#include "CameraComponent.h"
#include "BoxComponent.h"
#include "MovementComponent.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "CollisionManager.h"

#include "Debug.h"
#include "World.h"
#include "GameProcess.h"
#include "Input.h"
#include "PartSceneObject.h"
#include "PlayerObject.h"

CameraObject::CameraObject()
	: GameObject()
	, m_pCameraComponent(nullptr)
{
	m_tag = "camera";

	m_pCameraComponent = AddComponent<CameraComponent>("CameraComponent");

	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetExtends(960.f, 540.f);
	CollisionManager::GetInstance()->SetCameraCollider(m_pBoxCollider);
	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
	//m_pRigidBody = AddComponent<RigidBody>("RigidBody");
	//m_pRigidBody->SetMass(1.f);
	//m_pRigidBody->SetGravity(10.f);

}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float dt)
{
	
	__super::Update(dt);

	/*Vector2D cameraTranslationLT;
	Vector2D cameraTranslationRB;

	
	cameraTranslationLT = m_pBoxCollider->GetMinColliderVector();
	cameraTranslationRB = m_pBoxCollider->GetMaxColliderVector();
	

	if(m_pWorld->m_curScene != nullptr)
	{
		Vector2D sceneTranslationLT = m_pWorld->m_curScene->m_pBoxCollider->GetMinColliderVector();
		Vector2D sceneTranslationRB = m_pWorld->m_curScene->m_pBoxCollider->GetMaxColliderVector();
	
		if(cameraTranslationLT.x < sceneTranslationLT.x || cameraTranslationRB.x > sceneTranslationRB.x || cameraTranslationLT.y < sceneTranslationLT.y || cameraTranslationRB.y > sceneTranslationLT.y)
		{
			if(GetFocusingObject() != nullptr)
				SetFocusingObject(nullptr);
			
		}
	}*/

	D2D1_MATRIX_3X2_F matrix = m_pRootComponent->GetWorldTransform();
	D2D1InvertMatrix(&matrix);
	World::m_cameraTransform = matrix * D2D1::Matrix3x2F::Translation(GameProcess::m_screenWidth / 2, GameProcess::m_screenHeight / 2);



	auto a = m_pRootComponent->GetWorldTransform()._31;
	auto b = m_pRootComponent->GetWorldTransform()._32;

	wstring x = to_wstring((int)a);
	wstring y = to_wstring((int)b);

	//Debug::Text(x + L" " + y);

}

bool CameraObject::Initialize()
{
	return false;
}

