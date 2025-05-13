#pragma once
#include <string>

enum class MODE
{
	CreateImage,
	DeleteImage,
	CreateCollider,
	DeleteCollider
};

class ToolManager
{
public:
	static ToolManager* m_pInstance;
	static ToolManager* GetInst();
	
	std::wstring GetCurTileKey();
	void SetCurTileKey(std::wstring _tileTag);

	POINT GetColliderLeftTop();
	void SetColliderLeftTop(POINT _leftTop);

	void SetMode(MODE _mode);
	MODE GetMode();

private:
	std::wstring curTileKey = L"";

	POINT m_tmpLeftTop = { -1,-1 };

	MODE m_curMode = MODE::CreateImage;
};

