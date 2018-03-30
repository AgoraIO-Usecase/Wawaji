#include "stdafx.h"
#include "MyCmdLineInfo.h"
#include "commonFun.h"

CMyCmdLineInfo::CMyCmdLineInfo():
m_nCmdIndex(0)
{

}

CMyCmdLineInfo::~CMyCmdLineInfo()
{

}

void CMyCmdLineInfo::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag && !bLast){
		
#ifdef _DEBUG
		m_strAppLog = getAbsoluteDir() +std::string("logger\\") +  cs2s(pszParam);
#else
		m_strAppLog = getAbsoluteDir() + std::string("logger\\") + cs2s(pszParam);
#endif
		
		char *pszTemp = (char*)m_strAppLog.c_str();
		while ('\0' != *pszTemp){
			if ('\\' == *pszTemp){
				*pszTemp = '/';
			}
			pszTemp++;
		}

 		gAgoraWawajiLog.openLog(m_strAppLog,OPEN_ALWAYS);
 		gStrInstance = "=========";
 		CAgoraFormatStr::AgoraWriteLog("parseParam logPath: %s", m_strAppLog.data());
	}
	else if (!bFlag && !bLast){

		m_strInstance = cs2s(pszParam);
		gStrInstance = m_strInstance;
		CAgoraFormatStr::AgoraWriteLog("parseParam InstanceDesc: %s", m_strInstance.data());
	}
	else if (!bFlag && bLast){

		swscanf(pszParam, _T("%x"), &m_Wnd);
		CAgoraFormatStr::AgoraWriteLog("parseParam videoCanvans: %x", m_Wnd);
	}
}

std::string CMyCmdLineInfo::getInstance()
{
	return m_strInstance;
}

HWND CMyCmdLineInfo::getMainUIItemWnd()
{
	return m_Wnd;
}