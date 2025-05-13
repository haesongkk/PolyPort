#pragma once
#include <afxwin.h>
class ColliderButton : public CButton
{
	DECLARE_DYNAMIC(ColliderButton)
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnButtonClicked();

	void SetColliderTag(std::wstring _colliderTag);
	std::wstring GetCollideTag();

private: 
	std::wstring m_colliderType;

};

