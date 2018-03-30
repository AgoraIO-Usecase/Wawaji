#pragma once

class CMyCmdLineInfo:public CCommandLineInfo
{
public:
	CMyCmdLineInfo();
	~CMyCmdLineInfo();

	std::string getInstance();
	HWND getMainUIItemWnd();

private:
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

private:
	int m_nCmdIndex;
	std::string m_strAppLog;
	std::string m_strInstance;
	HWND m_Wnd;
};