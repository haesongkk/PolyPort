#pragma once
#include "Component.h"
#include "FSM.h"

class FSMCharacter;
class FiniteStateMachine;
class GameObject;
class FSMComponent :
	public Component
{
public:
	FSMComponent(GameObject* pOwner, const string& Name, TransformComponent* pRoot = nullptr)
		: Component(pOwner, Name)
		, m_pFSM(nullptr)
	{

	}

	virtual ~FSMComponent()
	{
		if (m_pFSM != nullptr)
			delete m_pFSM;
	}
protected:
	FSM* m_pFSM;
public:
	virtual void Update(float DeltaTime)
	{
		if (m_pFSM != nullptr)
			m_pFSM->Update(DeltaTime);
	}

	virtual void LateUpdate(float dt)
	{
		if (m_pFSM != nullptr)
			m_pFSM->Update(dt);
	}
	template<typename T>
	T* CreateFiniteStateMachine(string tag)
	{
		assert(m_pFSM == nullptr);
		// 부모클래스가 FSM인지 확인
		bool bIsFSM = is_base_of<FSM, T>::value;
		assert(bIsFSM);
		T* newFSM = new T(this, tag);

		m_pFSM = newFSM;
		return newFSM;
	}
};

