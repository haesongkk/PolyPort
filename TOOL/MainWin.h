#pragma once
#include <vector>

class TileButton;

class ImagePalette;

class SaveWindow;
class LoadWindow;
class NewWindow;

class MainWin : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(MainWin)

public:
	MainWin() noexcept;
	virtual ~MainWin();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* _pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void AddCollider(POINT _lt, POINT _rb);

	void OnFileNew();
	void OnFileOpen();
	void OnFileSave();

	void SaveData(std::wstring _filePath);
	void LoadData(std::wstring _filePath);
	void NewData(int _tileWidth, int _tileHeight);

	std::string CastWstr(std::wstring& _wstr);
	std::wstring CastStr(std::string& _str);
	
private:
	CRect btnRt = CRect(0, 0, TileSize, TileSize);

	TileButton** m_pTiles;
	std::vector<CRect> m_colliders;

	ImagePalette* m_pPalette;

	SaveWindow* m_pSaveWindow;
	LoadWindow* m_pLoadWindow;
	NewWindow* m_pNewWindow;

	DECLARE_MESSAGE_MAP()

};

