#pragma once
class ButtonComponent;
class ButtonManager
{
public:
	static void OnButton(const string& _name);
	static void OnButtonClick(const string& _name);
private:
	static ButtonManager* m_pInstance;
};

