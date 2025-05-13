#pragma once
#include <queue>
class World;
class GameObject;
class Event
{
public:
	Event(World* _pWorld);
	~Event() { }

	void Update();

	template<class T>
	static T* CreateObject()
	{
		T* newObject = new T;
		m_objToCreate.push(newObject);
		return newObject;
	}
	static void DeleteObject(GameObject* _pObj);
	static void DeleteWorld();

private:
	World* m_pWorld;
	static queue<GameObject*> m_objToCreate;
	static queue<GameObject*> m_objToDelete;
	static bool m_bDeleteWorld;
};