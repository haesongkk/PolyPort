//최상위 오브젝트
//컴포넌트랑 게임 오브젝트가 이걸 상속 받음

#pragma once

class Collider;
class ButtonComponent;

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	virtual bool Initialize() = 0; //초기화로 오브젝트를 사용가능한지확인한다.
	virtual void Update(float dt) = 0;	//오브젝트의 상태를 업데이트한다.

	virtual void OnCollisionEnter(Collider& other){}
	virtual void OnCollisionStay(Collider& other) {}
	virtual void OnCollisionExit(Collider& other) {}

	virtual void OnButtonClick(const string& _name) {}

	//virtual void FixedUpdate(float elapsedTime) = 0;
};

