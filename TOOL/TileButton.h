#pragma once
#include <afxwin.h>
class TileButton : public CButton
{
	DECLARE_DYNAMIC(TileButton)
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	afx_msg void OnButtonClicked();

	void SetTilePos(POINT _tilePos);
	POINT GetTilePos();

	void SetTileTag(std::wstring _tileTag);
	std::wstring GetTileTag();

	void SetColliderLeftTop(POINT _lt);
	POINT GetColliderLeftTop();

	bool GetIsCreated();

private:
	POINT m_tilePos = {};
	bool m_bIsCreated = false;

	std::wstring m_tileTag = L"../Resource/tile/default.jpg";

	CImage* m_pImage = nullptr;

	POINT m_leftTop = { -1,-1 };
};

