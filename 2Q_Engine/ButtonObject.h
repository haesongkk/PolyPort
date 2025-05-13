#pragma once
#include "GameObject.h"

class ButtonComponent;
class ButtonObject : public GameObject
{
public:
	virtual void OnButtonClick(const string& _name) override;
};

