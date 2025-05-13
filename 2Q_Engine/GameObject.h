//���� ������Ʈ
//������Ʈ���� create�ؼ� ����

#pragma once

#include "BaseObject.h"
#include "Component.h"

class World;
class Component;
class TransformComponent;
class GameObject :
	public BaseObject
{
protected:
	World* m_pWorld; //�� ������Ʈ�� ���� ����
	string m_tag;
	TransformComponent* m_pRootComponent; // ������Ʈ�� �ֻ����� �ִ� TransformComponent
	vector<Component*> m_pComponents; // �� ������Ʈ�� ������ �ִ� ������Ʈ�� ����
	GameObject* m_pParentObject;
	bool m_bVisible = true;
	
public:
	Vector2D m_originPos;
	virtual void Regame();
	bool m_bDash = false;
	GameObject();
	virtual ~GameObject() override;

	virtual bool Initialize();
	virtual void Update(float dt);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
	virtual void LateUpdate(float dt);

	void OnCollisionEnter(Collider& other) override { m_bVisible = true; }
	void OnCollisionExit(Collider& other) override { m_bVisible = false; }
	World* GetOwnerWorld() const { return m_pWorld; }
	bool IsVisible() { return m_bVisible; }
	void SetVisible(bool bVisible) { m_bVisible = bVisible; }
    void SetOwnerWorld(World* world) { m_pWorld = world; }
	World* GetOwnerWorld() { return m_pWorld; }
    string GetTag() { return m_tag; }
    void SetTag(string _tag) { m_tag = _tag; }
	TransformComponent* GetRootComponent() { return m_pRootComponent; }
	void SetParentObject(GameObject* pParent) {	m_pParentObject = pParent;	}
	GameObject* GetParentObject() const { return m_pParentObject; }
	template<typename T>
	T* AddComponent(string _name = 0)
	{
		bool bIsComponent = is_base_of<Component, T>::value;
		assert(bIsComponent);
		T* component = new T(this, _name, this->m_pRootComponent);
		m_pComponents.push_back(component);
		return component;
	}

    template <class T>
    T* GetComponent(string name)
    {
        for (auto& component : m_pComponents)
        {
            if (component->GetName() == name)
            {
                return dynamic_cast<T*>(component);
            }
        }
		return nullptr;
    }
};

