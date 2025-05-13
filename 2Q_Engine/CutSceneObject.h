#pragma once
#include "GameObject.h"
enum class CutScene
{
	Credit,
	Opening,
	Insert1,
	Insert2,
	Insert3,
	Ending,
	EndingA,
	EndingB,
	End
};
class UIComponent;
class TextComponent;
class ButtonComponent;
class CutSceneObject : public GameObject
{
public:
	CutSceneObject();
	virtual ~CutSceneObject() override;

	virtual void Update(float dt);

	void SetCutSceneType(CutScene _cutScene);

private:

	ButtonComponent* m_pSkipButton;
	UIComponent* m_pImage;
	vector<wstring> m_images;

	int m_index = 0;
	float m_timer = 0;


	CutScene m_type;
	

};

