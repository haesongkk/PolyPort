#include "pch.h"
#include "ButtonManager.h"

#include "Debug.h"
#include "Event.h"
#include "CutSceneObject.h"

ButtonManager* ButtonManager::m_pInstance = nullptr;

void ButtonManager::OnButton(const string& _name)
{
	if (m_pInstance == nullptr) m_pInstance = new ButtonManager;

	wstring wname;
	wname.assign(_name.begin(), _name.end());
	Debug::Text(L"on " + wname);


}

