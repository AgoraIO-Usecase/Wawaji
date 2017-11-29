#include "StdAfx.h"
#include "HttpOperator.h"


CHttpOperator::CHttpOperator(void)
	: m_hInternetSession(NULL)
	, m_hHttpConnection(NULL)
{

}


CHttpOperator::~CHttpOperator(void)
{
}

BOOL CHttpOperator::Create(LPCTSTR lpszAgent, DWORD dwAccessType, LPCTSTR lpszProxyName, LPCTSTR lpszProxyBypass, DWORD dwFlags)
{
	m_hInternetSession = ::InternetOpen(lpszAgent, dwAccessType, lpszProxyName, lpszProxyBypass, dwFlags);
	
	return m_hInternetSession == NULL ? FALSE : TRUE;
}

BOOL CHttpOperator::Connect(LPCTSTR lpszServerName, INTERNET_PORT nServerPort, LPCTSTR lpszUsername, LPCTSTR lpszPassword)
{
	if(m_hInternetSession == NULL)
		return FALSE;

	m_hHttpConnection = ::InternetConnect(m_hInternetSession, lpszServerName, nServerPort, lpszUsername, lpszPassword, INTERNET_SERVICE_HTTP, 0, 0);
	
	return m_hHttpConnection == NULL ? FALSE : TRUE;
} 

BOOL CHttpOperator::OpenRequest(LPCTSTR lpszVerb, LPCTSTR lpszObjectName, LPCTSTR lpszVersion, LPCTSTR lpszReferer, LPCTSTR *lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext)
{
	if(m_hInternetSession == NULL || m_hHttpConnection == NULL)
		return FALSE;

	m_hHttpFile = ::HttpOpenRequest(m_hHttpConnection, lpszVerb, lpszObjectName, lpszVersion, lpszReferer, lplpszAcceptTypes, dwFlags, dwContext);
	
	return m_hHttpFile == NULL ? FALSE : TRUE;
}

BOOL CHttpOperator::AddRequestHeader(LPCTSTR lpszHeaders, DWORD dwModifiers)
{
	// ÅÐ¶ÏÇëÇó¾ä±ú
	if(m_hHttpFile == NULL)
		return FALSE;

	DWORD dwHeaderLength = (DWORD)::lstrlen(lpszHeaders);
	
	return ::HttpAddRequestHeaders(m_hHttpFile, lpszHeaders, dwHeaderLength, dwModifiers);
}

BOOL CHttpOperator::SendRequest(LPCTSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength)
{
	// ÅÐ¶ÏÇëÇó¾ä±ú
	if(m_hHttpFile == NULL)
		return FALSE;

#ifdef DEBUG
	BOOL bRet = ::HttpSendRequest(m_hHttpFile, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength);
	DWORD dwLastError = ::GetLastError();
	return bRet;
#else
	return ::HttpSendRequest(m_hHttpFile, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength);
#endif
	::HttpEndRequest(m_hHttpFile, NULL, 0, NULL);
}

DWORD CHttpOperator::ReadHttpFile(LPVOID lpBuffer, DWORD dwBytesToRead)
{
	// ÅÐ¶ÏÇëÇó¾ä±ú
	if(m_hHttpFile == NULL)
		return FALSE;

	DWORD dwBytesRead = 0;
	BOOL bRet = ::InternetReadFile(m_hHttpFile, lpBuffer, dwBytesToRead, &dwBytesRead);

	if(!bRet)
		return 0;

	return dwBytesRead;
}

void CHttpOperator::CloseRequest()
{
	if(m_hHttpFile != NULL)
		::InternetCloseHandle(m_hHttpFile);

	m_hHttpFile = NULL;
}

void CHttpOperator::Disconnect()
{
	CloseRequest();
	if(m_hHttpConnection != NULL)
		::InternetCloseHandle(m_hHttpConnection);

	m_hHttpConnection = NULL;
}

void CHttpOperator::Close()
{
	CloseRequest();
	Disconnect();
	if(m_hInternetSession != NULL)
		::InternetCloseHandle(m_hInternetSession);

	m_hInternetSession = NULL;
}