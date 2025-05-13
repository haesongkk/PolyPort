#include "pch.h"
#include "ButtonObject.h"

#include "ButtonComponent.h"
#include "Sound.h"
#include "Debug.h"
#include "Event.h"
#include "World.h"


void ButtonObject::OnButtonClick(const string& _name)
{
	
	if (_name == "startButton")
	{
		for (auto obj : m_pWorld->GetGameObjects())
		{
			if (obj->GetComponent<ButtonComponent>("button") != nullptr)
				Event::DeleteObject(obj);
			if (obj->GetComponent<UIComponent>("ui") != nullptr)
				Event::DeleteObject(obj);
		}
			
		GetOwnerWorld()->LoadNextScene();
	}
	if (_name == "creditButton")
	{
		for (auto obj : m_pWorld->GetGameObjects())
			if (obj->GetComponent<ButtonComponent>("button") != nullptr)
				Event::DeleteObject(obj);

		GetOwnerWorld()->LoadScene(LOADSCENE::Credit);
	}
	if (_name == "quitButton")
	{
		PostQuitMessage(0);
	}
	if (_name == "pauseButton")
	{

	}
}

