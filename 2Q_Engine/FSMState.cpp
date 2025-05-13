#include "pch.h"
#include "FSMState.h"

#include "FSMCharacter.h"
#include "Debug.h"

#include <sstream>


void FSMState::Enter()
{
	
}

void FSMState::Update(float dt)
{
	string origin = "CurrentState : " + GetName();
	wstringstream wss;
	wss << origin.c_str();
	wstring converted = wss.str();
	//Debug::Text(converted);
}

bool FSMState::CheckTransition(string& nextState)
{
	return false;
}
