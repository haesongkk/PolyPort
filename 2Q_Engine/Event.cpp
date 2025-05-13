#include "pch.h"
#include "Event.h"

#include "GameProcess.h"
#include "GameObject.h"
#include "World.h"
#include "Load.h"
#include "CollisionManager.h"

queue<GameObject*> Event::m_objToCreate;
queue<GameObject*> Event::m_objToDelete;
bool Event::m_bDeleteWorld = false;

Event::Event(World* _pWorld)
	:m_pWorld(_pWorld)
{
}

void Event::DeleteObject(GameObject* _pObj)
{
	m_objToDelete.push(_pObj);
}

void Event::DeleteWorld()
{
	m_bDeleteWorld = true;
}

void Event::Update()
{
	if (m_bDeleteWorld)
	{
		/*m_bDeleteWorld = false;
		for (auto obj : m_pWorld->GetGameObjects())
		{
			delete obj;
		}
		m_pWorld->GetGameObjects().clear();
		CollisionManager::GetInstance()->Clear();*/
	}
	while (!m_objToDelete.empty())
	{
		GameObject* obj = m_objToDelete.front();
		m_objToDelete.pop();
		vector<GameObject*>& objs = m_pWorld->GetGameObjects();
		for (auto it = objs.begin(); it != objs.end(); it++)
		{
			if (*it == obj)
			{
				delete obj;
				objs.erase(it);
				break;
			}
		}
	}
	while (!m_objToCreate.empty())
	{
		GameObject* obj = m_objToCreate.front();
		m_objToCreate.pop();
		m_pWorld->GetGameObjects().push_back(obj);
		obj->SetOwnerWorld(m_pWorld);
		obj->Initialize();
	}
}
