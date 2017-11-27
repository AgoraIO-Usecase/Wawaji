#include "stdafx.h"
#include "SDKManager.h"
#include "RtspSession.h"

CSDKManager::CSDKManager(void)
	:m_nManagerRef(0)
	, m_pCSectionRtspSession(nullptr)
{
	m_pCSectionRtspSession = new CRITICAL_SECTION;
	InitializeCriticalSection(m_pCSectionRtspSession);
}

CSDKManager::~CSDKManager(void)
{
	DeleteCriticalSection(m_pCSectionRtspSession);
	if (m_pCSectionRtspSession)
	{
		delete m_pCSectionRtspSession;
		m_pCSectionRtspSession = nullptr;
	}
}

BOOL CSDKManager::IsInitManager()
{
	return (m_nManagerRef > 0);
}

LONG CSDKManager::InitializeSDKManager()
{
	av_register_all();
	avformat_network_init();
	m_nManagerRef++;

	return 0;
}

VOID CSDKManager::ReleaseSDKManager()
{
	avformat_network_deinit();
}

DWORD CSDKManager::CreateSession(HANDLE *hRTSPSession, const char * lpURL)
{
	*hRTSPSession = NULL;
	CRtspSessionPtr lpRtspSession = new CRtspSession;
	DWORD dwRet = lpRtspSession->CreateSession(lpURL);
	if (dwRet != 0)
	{
		lpRtspSession->DestroySession();
		return dwRet;
	}
	{
		EnterCriticalSection(m_pCSectionRtspSession);
		*hRTSPSession = lpRtspSession;
		m_mapRTSPSession[*hRTSPSession] = lpRtspSession;
		LeaveCriticalSection(m_pCSectionRtspSession);
	}
	return 0;
}

DWORD CSDKManager::DestroySession(HANDLE hRTSPSession)
{	
	EnterCriticalSection(m_pCSectionRtspSession);
	CRtspSessionPtr lpRtspSession;	
	std::map<VOID *, CRtspSessionPtr>::iterator Itor = m_mapRTSPSession.find(hRTSPSession);
	if (Itor == m_mapRTSPSession.end()){
		LeaveCriticalSection(m_pCSectionRtspSession);
		return __RTSP_ERR_ORDER_ERROR;
	}
	lpRtspSession = Itor->second;
	m_mapRTSPSession.erase(Itor);

	if (lpRtspSession)
	{
		lpRtspSession->DestroySession();
	}
	LeaveCriticalSection(m_pCSectionRtspSession);
	return 0;
}

DWORD CSDKManager::SetNetMessageCallback(HANDLE hRTSPSession, lpfuncRTSPNetMessageCb lpCallback, VOID *lpUser)
{
	EnterCriticalSection(m_pCSectionRtspSession);
	std::map<VOID *, CRtspSessionPtr>::iterator Itor = m_mapRTSPSession.find(hRTSPSession);
	if (Itor == m_mapRTSPSession.end()){
		LeaveCriticalSection(m_pCSectionRtspSession);
		return __RTSP_ERR_ORDER_ERROR;
	}
	CRtspSessionPtr lpRtspSession = Itor->second;
	LeaveCriticalSection(m_pCSectionRtspSession);
	return lpRtspSession->SetNetMessageCallback(lpCallback, lpUser);	
}

DWORD CSDKManager::Play(HANDLE hRTSPSession, lpfuncRTSPRealDataCb lpCallback, VOID *lpUser)
{
	EnterCriticalSection(m_pCSectionRtspSession);
	std::map<VOID *, CRtspSessionPtr>::iterator Itor = m_mapRTSPSession.find(hRTSPSession);
	if (Itor == m_mapRTSPSession.end()){
		LeaveCriticalSection(m_pCSectionRtspSession);
		return __RTSP_ERR_ORDER_ERROR;
	}

	CRtspSessionPtr lpRtspSession = Itor->second;
	LeaveCriticalSection(m_pCSectionRtspSession);
	return lpRtspSession->Play(lpCallback, lpUser);
}

DWORD CSDKManager::Stop(HANDLE hRTSPSession)
{
	EnterCriticalSection(m_pCSectionRtspSession);
	std::map<VOID *, CRtspSessionPtr>::iterator Itor = m_mapRTSPSession.find(hRTSPSession);
	if (Itor == m_mapRTSPSession.end()){
		LeaveCriticalSection(m_pCSectionRtspSession);
		return __RTSP_ERR_ORDER_ERROR;
	}
	CRtspSessionPtr lpRtspSession = Itor->second;
	LeaveCriticalSection(m_pCSectionRtspSession);
	return lpRtspSession->Stop();
}
