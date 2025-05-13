#include "pch.h"
#include "ToolManager.h"

ToolManager* ToolManager::m_pInstance = nullptr;

ToolManager* ToolManager::GetInst()
{
	if (m_pInstance == nullptr)
		m_pInstance = new ToolManager;
	return m_pInstance;
}

std::wstring ToolManager::GetCurTileKey()
{
	return curTileKey;
}

void ToolManager::SetCurTileKey(std::wstring _tileTag)
{
	curTileKey = _tileTag;
}

POINT ToolManager::GetColliderLeftTop()
{
	return m_tmpLeftTop;
}

void ToolManager::SetColliderLeftTop(POINT _leftTop)
{
	m_tmpLeftTop.x = _leftTop.x;
	m_tmpLeftTop.y = _leftTop.y;
}

void ToolManager::SetMode(MODE _mode)
{
	m_curMode = _mode;
}

MODE ToolManager::GetMode()
{
	return m_curMode;
}
