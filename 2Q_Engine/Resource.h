#pragma once

#include <filesystem>

class D2DRenderer;
class World;

class Resource
{
public:
	Resource();
	~Resource();

	void Initialize();
	void Finalize() {}

	void LoadAnimation(wstring _animPath, D2DRenderer* _pRenderer);

protected:
	void LoadAnimInfoFromTextFile(filesystem::path _filePath, D2DRenderer* _pRenderer);

};

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by r.rc

// 다음은 새 개체에 사용할 기본값입니다.
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
