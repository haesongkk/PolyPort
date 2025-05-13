#pragma once
class TOOL : public CWinAppEx
{
public:
	TOOL() noexcept;
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern TOOL theApp;
