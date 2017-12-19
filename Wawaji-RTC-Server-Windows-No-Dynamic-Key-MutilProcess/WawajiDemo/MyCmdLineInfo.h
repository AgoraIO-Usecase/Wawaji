#pragma once

class CMyCmdLineInfo:public CCommandLineInfo
{
public:
	CMyCmdLineInfo();
	~CMyCmdLineInfo();

private:
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

private:
	
};