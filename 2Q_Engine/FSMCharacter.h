#pragma once
#include "FSM.h"
#include "FSMState.h"
//#include "FSMTransition.h"
#include "StateIdle.h"
#include "StateDash.h"
#include "StateMove.h"
#include "StateDeath.h"
//#include "TransitionDeath.h"

//#include "FSMStateAlias.h"
#include "FSMComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "StateBubble.h"
#include "StateDoubleJump.h"
#include "StateDoubleJumpDescent.h"
#include "StateDoubleJumpLand.h"
#include "StateJump.h"
#include "StateJumpDescent.h"
#include "StateJumpLand.h"
#include "StateTeleport.h"
#include "RigidBody.h"
#include "StateBubbleBurst.h"
#include "StateBubbleIdle.h"
#include "StateBubbleInteract.h"

class AnimationComponent;
class MovementComponent;
/*
	이 FSM은 PlayerCharacter와 분리된 게임 정보로 작동되므로
	NPC에게도 사용할수있다.
*/
class FSMCharacter :
	public FSM
{
public:
	

	FSMCharacter(FSMComponent* pOwner, string tag)
		: FSM(pOwner, tag)
		, m_stateIdle(this)
		, m_stateMove(this)
		, m_stateDeath(this)
		, m_stateDash(this)
		, m_stateJump(this)
		, m_stateJumpDescent(this)
		, m_stateJumpLand(this)
		, m_stateDoubleJump(this)
		, m_stateDoubleJumpDescent(this)
		, m_stateDoubleJumpLand(this)
		, m_stateBubble(this)
		, m_stateTeleport(this)
		, m_stateBubbleIdle(this)
		, m_stateBubbleInteract(this)
		, m_stateBubbleBurst(this)
		/*m_TransitionToDeath(this),
		m_StateAliasDeath(this)*/
	{
		if(tag == "Player")
		{
			AddState(&m_stateMove);
			AddState(&m_stateIdle);
			AddState(&m_stateDeath);
			AddState(&m_stateDash);
			AddState(&m_stateJump);
			AddState(&m_stateJumpDescent);
			AddState(&m_stateJumpLand);
			AddState(&m_stateDoubleJump);
			AddState(&m_stateDoubleJumpDescent);
			AddState(&m_stateDoubleJumpLand);
			AddState(&m_stateBubble);
			AddState(&m_stateTeleport);

			//AddStateAlias(&m_StateAliasDeath);

			/*m_StateAliasDeath.BindState(&m_StateMove);
			m_StateAliasDeath.BindState(&m_StateAttack);
			m_StateAliasDeath.BindState(&m_StateIdle);*/

			SetInitialState("Idle");

			GameObject* pGameObject = pOwner->GetOwner();
			m_pAnimationComponent = (AnimationComponent*)pGameObject->GetComponent<AnimationComponent>("AnimationComponent");
			m_pRigidbody = (RigidBody*)pGameObject->GetComponent<RigidBody>("RigidBody");
			m_pMovementComponent = (MovementComponent*)pGameObject->GetComponent<MovementComponent>("MovementComponent");
			m_bMirror = false;
			m_bAnimationComplete = false;
			m_bDeath = false;
			m_bDash = false;
			m_bLand = false;
		}
		else if(tag == "Bubble")
		{
			AddState(&m_stateBubbleBurst);
			AddState(&m_stateBubbleIdle);
			AddState(&m_stateBubbleInteract);

			SetInitialState("BubbleIdle");

			GameObject* pGameObject = pOwner->GetOwner();
			m_pAnimationComponent = dynamic_cast<AnimationComponent*>(pGameObject->GetComponent<AnimationComponent>("AnimationComponent"));
			m_bAnimationComplete = false;
			m_bInteract = false;
			m_bBurst = false;
		}
	}
	virtual ~FSMCharacter()
	{

	}

	StateMove m_stateMove;
	StateDeath m_stateDeath;
	StateIdle m_stateIdle;
	StateDash m_stateDash;
	StateJump m_stateJump;
	StateJumpDescent m_stateJumpDescent;
	StateJumpLand m_stateJumpLand;
	StateDoubleJump m_stateDoubleJump;
	StateDoubleJumpDescent m_stateDoubleJumpDescent;
	StateDoubleJumpLand m_stateDoubleJumpLand;
	StateBubble m_stateBubble;
	StateTeleport m_stateTeleport;
	StateBubbleIdle m_stateBubbleIdle;
	StateBubbleInteract m_stateBubbleInteract;
	StateBubbleBurst m_stateBubbleBurst;


	AnimationComponent* m_pAnimationComponent;
	RigidBody* m_pRigidbody;
	MovementComponent* m_pMovementComponent;

	Vector2D m_moveDirection;
	Vector2D m_prevDirection;
	bool m_bAnimationComplete;
	bool m_bMirror;
	bool m_bDeath;
	bool m_bDash;
	bool m_bLand;
	bool m_bBubble;
	bool m_bInteract;
	bool m_bBurst;
	bool m_bRespawn;
	bool m_bTeleport;

	int m_jumpCount = 2;
	int m_DashCount = 1;
	virtual void Update(float DeltaTime) override;
};

