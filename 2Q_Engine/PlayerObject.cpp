#include "pch.h"
#include "PlayerObject.h"

#include "AnimationComponent.h"
#include "FSMComponent.h"
#include "FSM.h"
#include "FSMCharacter.h"
#include "RigidBody.h"
#include "BoxComponent.h"
#include "BoxCollider.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Debug.h"
#include "Input.h"
#include "D2DRenderer.h"
#include "BitmapComponent.h"
#include "BubbleObject.h"
#include "FireObject.h"
#include "Event.h"
#include "MovingObject.h"
#include "World.h"
#include "PortObject.h"
#include "Sound.h"

#define FloatingTime 2.f


PlayerObject::PlayerObject()
{
	//m_pRigidBody = AddComponent<RigidBody>("RigidBody");
	//m_pRigidBody->SetMass(1.f);
	//m_pRigidBody->SetGravity(10.f);

	//m_pMovementComponent = AddComponent<MovementComponent>("MovementComponent");
	//m_pMovementComponent->SetMoveSpeed(100.f);

	//m_pAnimationComponent = AddComponent<AnimationComponent>("AnimationComponent");
	//m_pAnimationComponent->SetAnimationAsset(std::wstring(L"../Resource/testLoadAsset.txt"));

	//m_pFSMComponent = AddComponent<FSMComponent>("FSMComponent");
	//m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>();
	//m_pBoxComponent = AddComponent<BoxComponent>("BoxComponent"); // 이거 빼도 이제 네모 출력됨 -해성-
	//m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	//CollisionManager::GetInstance()->SetPlayerCollider(m_pBoxCollider);
	//m_pBoxCollider->SetExtends(100.f, 100.f);
	m_tag = "player";



	m_pMovementComponent = AddComponent<MovementComponent>("MovementComponent");
	m_pMovementComponent->SetMoveSpeed(20);
	m_pMovementComponent->SetDashSpeed(800);
	m_pMovementComponent->SetJumpPower(550);
	m_pMovementComponent->SetDashTime(0.045);

	m_pAnimationComponent = AddComponent<AnimationComponent>("AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"../Resource/Animation/PlayerAnimation.txt"));
	m_pAnimationComponent->SetRelativeTranslation({ 0,-10 });

	m_pBoxCollider = AddComponent<BoxCollider>("BoxCollider");
	m_pBoxCollider->SetExtends(30, 35);
	m_pBoxCollider->SetColliderGroup(ColliderGroup::PLAYER);

	m_pSceneCollider = AddComponent<BoxCollider>("SceneCollider");
	m_pSceneCollider->SetExtends(1, 1);
	m_pSceneCollider->SetColliderGroup(ColliderGroup::PLAYER);

	m_pRigidBody = AddComponent<RigidBody>("RigidBody");
	m_pRigidBody->SetGravity(0);
	m_pRigidBody->SetMass(1.f);

	m_pFSMComponent = AddComponent<FSMComponent>("FSMComponent");
	m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>("Player");


	CollisionManager::GetInstance()->AddCollider(m_pBoxCollider);
	CollisionManager::GetInstance()->SetPlayerCollider(m_pSceneCollider);
	m_pFloatingHUD = AddComponent<BitmapComponent>("bitmap");
	m_pFloatingHUD->SetParentTransform(m_pRootComponent);
	m_pFloatingHUD->AddRelativeTranslation({ 0,-100 });

	m_floatingKeys =
	{ L"../Resource/image/20%.png" ,
		L"../Resource/image/40%.png" ,
		L"../Resource/image/60%.png" ,
		L"../Resource/image/80%.png" ,
		L"../Resource/image/100%.png" };
	for (auto i : m_floatingKeys)
		m_pFloatingHUD->SetBitmap(i);
	m_pFloatingHUD->SetBitmap(L"");

	m_savepoint = { 290,1051 };
}

PlayerObject::~PlayerObject()
{
	for (auto i : m_floatingKeys)
		D2DRenderer::m_instance->ReleaseBitmap(i);
}

Vector2D PlayerObject::ModificationVector(Collider& other)
{

	
	Vector2D thisMinVector = m_pBoxCollider->GetMinColliderVector();
	Vector2D thisMaxVector = m_pBoxCollider->GetMaxColliderVector();
	Vector2D otherMinVector = other.GetMinColliderVector();
	Vector2D otherMaxVector = other.GetMaxColliderVector();
	Vector2D modificationVector = { 0,0 };

	if (thisMaxVector.y >= otherMinVector.y && thisMaxVector.y <= otherMinVector.y + 20 && ((thisMaxVector.x - 15 >= otherMinVector.x && thisMaxVector.x < otherMaxVector.x) || (thisMinVector.x + 15 <= otherMaxVector.x && thisMinVector.x > otherMinVector.x)))
	{
		if (m_pBoxCollider->GetExtends().y > (other.GetExtends().y * 0.3) || m_pRigidBody->GetVelocity().y >= 0)
			return { 0,-thisMaxVector.y + otherMinVector.y };

	}
	if (thisMinVector.y <= otherMaxVector.y && thisMinVector.y >= otherMaxVector.y - 20 && ((thisMaxVector.x - 15 >= otherMinVector.x && thisMaxVector.x < otherMaxVector.x) || (thisMinVector.x + 15 <= otherMaxVector.x && thisMinVector.x > otherMinVector.x)))
	{
		//if (m_pBoxCollider->GetExtends().y > (other.GetExtends().y * 0.4))
			return { 0,-thisMinVector.y + otherMaxVector.y + 10 };
	}
	if (thisMinVector.x <= otherMaxVector.x && thisMinVector.x >= otherMaxVector.x - 50 && ((thisMaxVector.y - 15 >= otherMinVector.y && thisMaxVector.y < otherMaxVector.y) || (thisMinVector.y + 10 <= otherMaxVector.y && m_pBoxCollider->GetCenterPos().y > otherMinVector.y)))
	{
		//if ((thisMaxVector.x - thisMinVector.x) > (other.GetExtends().x * 0.3))
		return { otherMaxVector.x - thisMinVector.x+1,0 };
	}
	if (thisMaxVector.x >= otherMinVector.x && thisMaxVector.x <= otherMinVector.x + 50 && ((thisMaxVector.y - 15 >= otherMinVector.y && thisMaxVector.y < otherMaxVector.y) || (thisMinVector.y + 15 <= otherMaxVector.y && m_pBoxCollider->GetCenterPos().y > otherMinVector.y)))
	{
		//if ((thisMaxVector.x - thisMinVector.x)> (other.GetExtends().x * 0.3))
		return { otherMinVector.x - thisMaxVector.x-1,0 };
	}
	return modificationVector;
}

bool PlayerObject::CheckLand(Collider& other)
{
	Vector2D thisMinVector = m_pBoxCollider->GetMinColliderVector();
	Vector2D thisMaxVector = m_pBoxCollider->GetMaxColliderVector();
	Vector2D otherMinVector = other.GetMinColliderVector();
	Vector2D otherMaxVector = other.GetMaxColliderVector();

	if (thisMaxVector.y >= otherMinVector.y && thisMaxVector.y <= otherMinVector.y + 20 && ((thisMaxVector.x - 15 >= otherMinVector.x && thisMaxVector.x < otherMaxVector.x) || (thisMinVector.x + 15 <= otherMaxVector.x && thisMinVector.x > otherMinVector.x)))
		return true;
	return false;
}

bool PlayerObject::Initialize()
{
	m_savepoint = m_pRootComponent->GetRelativeTranslation();
	return __super::Initialize();
}

void PlayerObject::Update(float dt)
{
	__super::Update(dt);
	if (Input::m_pInputInstance->GetKeyState(KEY::I) == KEY_STATE::TAP)
	{
		Debug::ModeSwitch();
	}
	if (Input::m_pInputInstance->GetKeyState(KEY::ESC) == KEY_STATE::TAP)
		m_pRootComponent->SetRelativeTranslation(m_savepoint);
	if (m_pFSMCharacter->m_bDeath)
		return;
	if(m_pAttachedObject !=nullptr)
	{
		GetRootComponent()->AddRelativeTranslation((dynamic_cast<MovingObject*>(m_pAttachedObject)->m_route) * dt / dynamic_cast<MovingObject*>(m_pAttachedObject)->m_distance * 50);
	}
	Vector2D direction = m_pRigidBody->GetVelocity();
	if (m_pFSMCharacter->m_bBubble)
	{
		m_bubbleTimer += dt;
		if (m_bubbleTimer >= 5.f)
			m_pFSMCharacter->m_bDeath = true;
	}
	else
	{
		m_bubbleTimer = 0.f;
	}
	/*if (!m_pFSMCharacter->m_bLand && m_pFSMCharacter->m_jumpCount==2)
	{
		m_pFSMCharacter->m_jumpCount--;
	}*/
	if (m_pFSMCharacter->m_bRespawn)
	{
		m_pRootComponent->SetRelativeTranslation(m_savepoint);
		m_pFSMCharacter->m_bRespawn = false;
	}
	if (!m_pBoxCollider->GetCollision() && !m_pFSMCharacter->m_bTeleport)
	{
		m_pRigidBody->SetGravity(17.5);
		m_pFSMCharacter->m_bLand = false;
	}
	if (m_pFSMCharacter->m_bBubble)
	{
		m_pFSMCharacter->m_pAnimationComponent->SetRelativeRotation(0);
		m_pMovementComponent->dashElapsedTime = 0;

		float radius = dynamic_cast<BubbleObject*>(m_pBubbleObject)->GetRadius();
		m_pRigidBody->SetGravity(0);
		//m_pRigidBody->SetVelocity({ 0,0 });
		direction = { 0,0 };
		if (Input::GetInstance()->GetKeyState(KEY::RBUTTON) == KEY_STATE::TAP)
		{
			if (dynamic_cast<BubbleObject*>(m_pBubbleObject)->GetFireObject()->m_bIsAble)
			{
				POINT mousePos = Input::GetInstance()->GetMousePos();
				Vector2D mousePosVector = { -m_pRootComponent->GetWorldTransform()._31 + static_cast<float>(mousePos.x),-m_pRootComponent->GetWorldTransform()._32 + static_cast<float>(mousePos.y) };
				direction = mousePosVector;
				direction.Normalize();
				m_pRootComponent->SetRelativeTranslation({ m_pRootComponent->GetRelativeTranslation().x + direction.x * radius,m_pRootComponent->GetRelativeTranslation().y + direction.y * radius });
				//m_pRootComponent->AddRelativeTranslation(direction * radius);
 			m_pFSMCharacter->m_bTeleport = true;
			
				Sound::Play(SFX, "../Resource/sound/bubble_out.mp3");
			}
		}
		
	}
	else if (!m_pFSMCharacter->m_bDash)
	{
		//좌우 이동
		m_pFSMCharacter->m_pAnimationComponent->SetRelativeRotation(0);
		m_pMovementComponent->dashElapsedTime = 0;

		if (Input::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
		{
			direction += m_pMovementComponent->Move(Vector2D(-1, 0));
		}
		else if (Input::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
		{
			direction += m_pMovementComponent->Move(Vector2D(1, 0));
		}
		if (Input::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::AWAY)
		{
			direction.x = 0;
			m_pMovementComponent->Move({ 0,0 });
		}
		if (Input::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::AWAY)
		{
			direction.x = 0;
			m_pMovementComponent->Move({ 0,0 });
		}
		if (Input::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::AWAY)
		{
			//m_teleportState = true;
		}
		if (Input::GetInstance()->GetKeyState(KEY::RBUTTON) == KEY_STATE::TAP && m_pFSMCharacter->m_DashCount != 0)
		{
			m_pFSMCharacter->m_DashCount--;
			m_pRigidBody->SetGravity(0);
			POINT mousePos = Input::GetInstance()->GetMousePos();
			Vector2D mousePosVector = { -m_pRootComponent->GetWorldTransform()._31 + static_cast<float>(mousePos.x),-m_pRootComponent->GetWorldTransform()._32 + static_cast<float>(mousePos.y) };
			direction = m_pMovementComponent->Dash(mousePosVector);
			m_pFSMCharacter->m_bDash = true;
			m_bDash = true;
			printf("마우스 좌표 : %d %d \n", mousePos.x, mousePos.y);
			printf("캐릭터 좌표 : %f %f \n", m_pRootComponent->GetWorldTransform()._31, m_pRootComponent->GetWorldTransform()._32);
			printf("%f", atan2f(direction.y, direction.x) * 180 / 3.141592);
			Sound::Play(SFX, "../Resource/sound/dash.mp3");

		}

		//점프
		if (Input::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP && m_pFSMCharacter->m_jumpCount != 0)
		{
			m_pFSMCharacter->m_jumpCount--;
			direction.y = 0;
			m_pRigidBody->SetGravity(0);
			direction += m_pMovementComponent->Jump();
		}

		//중력의 영향을 받는지 체크
		if (m_pRigidBody->IsAffectedGravity())
		{
			direction += {0, m_pRigidBody->GetGravity()* m_pRigidBody->GetMass()* GRAVITY};
		}

	}
	else
	{
		if (m_pMovementComponent->dashElapsedTime < 0.5)
		{
			
			m_pMovementComponent->dashElapsedTime += dt;
			m_pRigidBody->SetGravity(0);

			if(m_pMovementComponent->dashElapsedTime >=0.2)
			{
				if (direction.x < 0)
					m_pFSMCharacter->m_pAnimationComponent->SetRelativeRotation((atan2f(direction.y, -direction.x) * 180 / 3.141592));
				else
					m_pFSMCharacter->m_pAnimationComponent->SetRelativeRotation((atan2f(direction.y, direction.x) * 180 / 3.141592));
			}
		}
		else if (m_pMovementComponent->dashElapsedTime >= 0.5)
		{
			direction = m_pRigidBody->GetVelocity();
			Vector2D directionVector = { -direction.x * m_pMovementComponent->dashElapsedTime,-direction.y * m_pMovementComponent->dashElapsedTime };  
			m_pMovementComponent->dashElapsedTime = 0;
			m_pFSMCharacter->m_bDash = false;
			direction = { 0,0 };

			m_pFSMCharacter->m_pAnimationComponent->SetRelativeRotation(0);

		}


	}
	m_pRigidBody->SetVelocity(direction);


	wstring player = L"player pos :";
	player += to_wstring((int)m_pRootComponent->GetRelativeTranslation().x);
	player += L", ";
	player += to_wstring((int)m_pRootComponent->GetRelativeTranslation().y);
	Debug::Text(player);

	Debug::Text(L"save point : " + to_wstring((int)m_savepoint.x) + L", " + to_wstring((int)m_savepoint.y));

	FloatingUpdate(dt);
	PortUpdate(dt);

	// 죽는 애니메이션 끝나면 호출해줘야하는 함수 (플레이어 위치 바꿔줌)

	if(!m_inBubble)
		m_pFSMCharacter->m_bBubble = false;
	m_inBubble = false;
}


void PlayerObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	GameObject::Render(pRenderTarget);
}

void PlayerObject::AnimationEnd()  const
{
	m_pFSMCharacter->m_bAnimationComplete = true;
}

void PlayerObject::FloatingUpdate(float dt)
{
	if (m_bGetItem)
	{
		m_floatingTimer += dt;
		if (m_floatingTimer > FloatingTime)
		{
			m_bGetItem = false;
			m_pFloatingHUD->SetBitmap(L"");
			m_floatingTimer = 0;
		}
	}
}

void PlayerObject::PortUpdate(float dt)
{
	vector<BoxCollider*> objects = CollisionManager::m_pInstance->GetGameObjects();
	float distance = INT_MAX;
	Vector2D myPos = m_pRootComponent->GetRelativeTranslation();
	PortObject* nearPort = nullptr;
	for (auto obj : objects)
	{
		if (obj->GetOwner()->GetTag() != "port") continue;
		Vector2D otherPos = obj->GetOwner()->GetRootComponent()->GetRelativeTranslation();
		Vector2D dif = myPos - otherPos;
		if (dif.Length() < distance)
		{
			distance = dif.Length();
			nearPort = dynamic_cast<PortObject*>(obj->GetOwner());
		}
	}

	if (nearPort != nullptr&&!m_pFSMCharacter->m_bBubble) nearPort->PortActive();
}
	

void PlayerObject::OnCollisionEnter(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		
		//if()

		//m_rigidBody->SetVelocity({ 0,0 });

		//m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		if (ModificationVector(other).y < 0 && m_pRigidBody->GetVelocity().y>0)
		{
			m_pRigidBody->SetGravity(0);
			m_pRigidBody->SetYVelocity(0);
			m_pFSMCharacter->m_bLand = true;
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		}
 		else if (ModificationVector(other).y > 0)
		{
			m_pRootComponent->AddRelativeTranslation({ 0,ModificationVector(other).y });
			m_pRigidBody->SetYVelocity(0);
		}
		else
		{
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		}
		if (other.GetOwner()->GetTag() == "MOVE")
		{
			m_pRootComponent->AddRelativeTranslation({ 0,1 });

		}
		if (m_pFSMCharacter->m_bLand)
		{
			m_pFSMCharacter->m_bLand = true;
		}
		else
		{
			m_pFSMCharacter->m_bLand = CheckLand(other);
		}
	}
	else if (other.GetCollisionType() == CollisionType::ONEWAY)
	{

		if (ModificationVector(other).y < 0 && m_pRigidBody->GetVelocity().y>0)
		{
			if (other.GetOwner()->GetTag() == "spring")
			{
				m_pRigidBody->SetGravity(0);
				m_pRigidBody->SetYVelocity(-1000.f);
				m_pFSMCharacter->m_bLand = true;
			}
			else
			{
				m_pRigidBody->SetGravity(0);
				m_pRigidBody->SetYVelocity(0);
				m_pFSMCharacter->m_bLand = true;
				m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
			}
		}
		else
		{
			m_pRigidBody->SetGravity(17.5);
		}

	}
	else
	{
		if (other.GetOwner()->GetTag() == "item")
		{

			other.GetOwner()->GetRootComponent()->SetRelativeTranslation({ -1000,-1000 });
			m_bGetItem = true;
			m_pFloatingHUD->SetBitmap(m_floatingKeys[m_itemCount]);

			if (m_itemCount < 5) m_itemCount++;
			else if (m_itemCount == 5) m_pWorld->RealEnding();
			Sound::Play(SFX, "../Resource/sound/acquire_marble.mp3");

			Debug::Log(L"get item (" + to_wstring(m_itemCount) + L"/5)");
			
		}

		if (other.GetOwner()->GetTag() == "Bubble")
		{
			/*m_pRootComponent->SetRelativeTranslation({ other.GetOwner()->GetRootComponent()->GetRelativeTranslation().x - 10, other.GetOwner()->GetRootComponent()->GetRelativeTranslation().y });*/
			m_pRootComponent->SetRelativeRotation(0.f);
			m_teleportState = true;
			m_pBubbleObject = other.GetOwner();
			Sound::Play(SFX, "../Resource/sound/bubble_in.mp3");

			m_bubbleTimer = 0.f;
			m_inBubble = true;
		}
	}
		m_pBoxCollider->SetCenterPos(m_pRootComponent->GetRelativeTranslation().x, m_pRootComponent->GetRelativeTranslation().y);
}

void PlayerObject::OnCollisionStay(Collider& other)
{
	if (other.GetOwner()->GetTag() == "next")
	{
		other.GetOwner()->GetRootComponent()->SetRelativeTranslation({ -1000,-1000 });
		Event::DeleteWorld();
		GetOwnerWorld()->LoadNextScene();
		return;
	}
	if (other.GetOwner()->GetTag() == "savePoint")
	{
		m_savepoint = other.GetOwner()->GetRootComponent()->GetRelativeTranslation();
	}

	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		
		if (ModificationVector(other).y < 0 && m_pRigidBody->GetVelocity().y > 0)
		{
			m_pRigidBody->SetGravity(0);
			m_pRigidBody->SetYVelocity(0);
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
			m_pFSMCharacter->m_bLand = true;
		}
		else if (abs(ModificationVector(other).x) >= 0 && m_pRigidBody->GetVelocity().y != 0)
		{
			m_pRigidBody->SetGravity(17.5);
			m_pFSMCharacter->m_bLand = false;
			//m_pRigidBody->SetYVelocity(0);
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		}
		else
		{
			m_pFSMCharacter->m_bLand = false;
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		}
		m_pFSMCharacter->m_bLand = CheckLand(other);
	}
	else if (other.GetCollisionType() == CollisionType::ONEWAY)
	{
		if (ModificationVector(other).y < 0)
		{
			if (m_pRigidBody->GetVelocity().y > 0)
			{
				m_pRigidBody->SetYVelocity(0);
			}
			m_pRigidBody->SetGravity(0);
			
			m_pFSMCharacter->m_bLand = true;
			m_pRootComponent->AddRelativeTranslation(ModificationVector(other));
		}
		else if (!m_pFSMCharacter->m_bLand)
		{
			m_pBoxCollider->SetCollision(false);
		}

	}
	if (other.GetOwner()->GetTag() == "Bubble")
	{
		m_inBubble = true;

		/*m_pRootComponent->SetRelativeTranslation({other.GetOwner()->GetRootComponent()->GetRelativeTranslation().x - 10, other.GetOwner()->GetRootComponent()->GetRelativeTranslation().y});
		m_teleportState = true;
		m_pBubbleObject = other.GetOwner();*/
	}
	
}

void PlayerObject::OnCollisionExit(Collider& other)
{
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		if (other.GetMinColliderVector().y >= m_pBoxCollider->GetMaxColliderVector().y) {
			m_pRigidBody->SetGravity(17.5);
			m_pRigidBody->SetYVelocity(0);
		}
		//m_rigidBody->SetVelocity(Vector2D(0, 0));
	}
	if (other.GetOwner()->GetTag() == "MOVE")
	{
		m_pRootComponent->SetParentTransform(nullptr);
	}
	if (other.GetCollisionType() == CollisionType::BLOCK)
	{
		Debug::Log(L"block collision exit");
	}

}

void PlayerObject::Regame()
{
	m_itemCount = 0;
	__super::Regame();
}



