#pragma once
#include "PlayerObject.h"
#include "TransformComponent.h"
class PartSceneObject;
class GameObject;
class CameraObject;
class Event;
class Load;
enum class LOADSCENE
{
	Credit, Title, Opening, Insert1, Stage1, Insert2, Stage2, Insert3, Stage3, Ending, EndingA, EndingB,  Last,
};
class World
{
private:
	vector<GameObject*> m_gameObjects;
	PartSceneObject* m_scene4;
	PartSceneObject* m_scene3;
	PartSceneObject* m_scene2;
	PartSceneObject* m_scene1;

public:
	PartSceneObject* m_curScene;
	PartSceneObject* m_prevScene;
	CameraObject* m_pCameraObject;
	GameObject* m_pPlayerObject;
	Event* m_pEvent;
	Load* m_pLoad;
	static D2D1_MATRIX_3X2_F m_cameraTransform;
	vector<Vector2D> m_savePoints;
	vector<Vector2D>& SavePoints() { return m_savePoints; }
public:
	template <typename T>
	T* CreateGameObject()
	{
		bool bIsGameObject = is_base_of<GameObject, T>::value;
		assert(bIsGameObject);
		T* newObject = new T();
		newObject->SetOwnerWorld(this);
		m_gameObjects.push_back(newObject);
		return newObject;
	}

	void Initialize();
	void Update(float dt);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	void LateUpdate(float dt);
	void Enter();
	void Exit();

	D2D1_MATRIX_3X2_F GetCameraTransform() { return m_cameraTransform; }
	vector<GameObject*>& GetGameObjects() { return m_gameObjects; }
	CameraObject* GetCameraObject() { return m_pCameraObject; }
	GameObject* GetPlayerObject() { return m_pPlayerObject; }
	void SetCameraObject(CameraObject* _pCameraObj) { m_pCameraObject = _pCameraObj; }
	void SetPlayerObject(PlayerObject* pPlayerObj) { m_pPlayerObject = pPlayerObj; }
	void SetFocus();
	void ForDebug();

public:
	World();
	~World();

	

	LOADSCENE m_scene = LOADSCENE::Title;

	void LoadNextScene();
	void LoadScene(LOADSCENE _scene);
	bool m_bRealEnding = false;
	void RealEnding() { m_bRealEnding = true; }

	void LoadAll();
};
