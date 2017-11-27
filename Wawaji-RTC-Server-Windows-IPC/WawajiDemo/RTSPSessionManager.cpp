#include "stdafx.h"
#include "RTSPSessionManager.h"
#include "commonFun.h"


CRTSPSessionManager::CRTSPSessionManager() :m_session(nullptr)
{
	m_sdkManager.InitializeSDKManager();
}

CRTSPSessionManager::~CRTSPSessionManager()
{
	m_sdkManager.ReleaseSDKManager();
}

bool CRTSPSessionManager::startRTSP(const std::string &url)
{
	HANDLE hSession = NULL;
	m_session = hSession;
	if ("" == url)
	{
		return __RTSP_ERR_INVALID_URL;
	}
	DWORD rs = m_sdkManager.CreateSession(&hSession, url.data());
	if (rs != 0 || NULL == hSession)
	{
		return false;
	}

	m_h264RtspFile.openMedia(getAbsoluteDir() + std::string("rtsp.h264"));
	m_sdkManager.SetNetMessageCallback(hSession, RTSPNetMessage, this);
	return m_sdkManager.Play(hSession, RTSPRealData, this);
}

bool CRTSPSessionManager::stopRTSP()
{
	if (m_session)
	{
		m_h264RtspFile.close();
		m_sdkManager.Stop(m_session);
		m_sdkManager.DestroySession(m_session);
	}

	return true;
}

VOID __stdcall CRTSPSessionManager::RTSPNetMessage(HANDLE hRTSPSession, DWORD dwMessageType, VOID *lpUser)
{
	CRTSPSessionManager* pThis = (CRTSPSessionManager*)lpUser;
}

VOID __stdcall CRTSPSessionManager::RTSPRealData(HANDLE hRTSPSession, const BYTE *lpBuffer, DWORD dwBufferSize, RTSP_MEDIA_INFO * lpMediaInfo, VOID *lpUser)
{
	CRTSPSessionManager* pThis = (CRTSPSessionManager*)lpUser;
	if (!pThis || !lpMediaInfo)
		return;

	if (lpMediaInfo->nCodeType == 0)
	{//VIDEO
		//pThis->m_h264RtspFile.write((char*)lpBuffer, int(dwBufferSize));
		//decod & trans

	}
	else if (lpMediaInfo->nCodeType == 1)
	{
	}
}
