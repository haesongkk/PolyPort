#pragma once

class AABB;
class OBB;
class BoxCollider;
class GameObject;

class CollisionManager
{
private:
	AABB* aabb;
	OBB* obb;

	BoxCollider* m_playerBox;
	BoxCollider* m_cameraBox;
	vector<BoxCollider*> m_otherBoxes;
	vector<BoxCollider*>m_sceneParts;
	vector<BoxCollider*>m_objectBoxes;
	
public:

	static CollisionManager* m_pInstance;

public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* GetInstance()
	{
		return m_pInstance;
	}
	void AddCollider(BoxCollider* boxCollider);
	void AddScenePart(BoxCollider* boxCollider);
	bool BoxCollision(BoxCollider& player, BoxCollider& other);
	void CameraCollision(BoxCollider& camera, BoxCollider& other);
	void PlayerSceneCollision(BoxCollider& player, BoxCollider& other);
	void CameraSceneCollision(BoxCollider& camera, BoxCollider& other);
	void Update();
	void SetPlayerCollider(BoxCollider* playerCollider);
	void SetCameraCollider(BoxCollider* cameraCollider);

	GameObject* m_portObject;

	void CheckCollision(BoxCollider& left, BoxCollider& right);
	bool CheckGroup(BoxCollider& left, BoxCollider& right);

	vector<BoxCollider*>& GetGameObjects() { return m_objectBoxes; }

	void Clear();
};

