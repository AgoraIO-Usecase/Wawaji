#include "stdafx.h"
#include "AGDynamicKeyRequestor.h"


CAGDynamicKeyRequestor::CAGDynamicKeyRequestor()
{
}


CAGDynamicKeyRequestor::~CAGDynamicKeyRequestor()
{
}

BOOL CAGDynamicKeyRequestor::Create()
{
	return m_httpOperator.Create();
}

BOOL CAGDynamicKeyRequestor::GetKey(LPCTSTR lpURL, CHAR *lpszKey, SIZE_T *lpKeySize)
{
	CString		strInfo;
	CString		strServer;
	CString		strObject;

	BOOL		bRet = FALSE;
	DWORD		dwURLLen = (DWORD)::lstrlen(lpURL);
	DWORD_PTR	dwContext = NULL;

	URL_COMPONENTS urlComponents;

	memset(&urlComponents, 0, sizeof(URL_COMPONENTS));
	urlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	urlComponents.dwHostNameLength = INTERNET_MAX_HOST_NAME_LENGTH;
	urlComponents.lpszHostName = strServer.GetBuffer(INTERNET_MAX_HOST_NAME_LENGTH + 1);
	urlComponents.dwUrlPathLength = INTERNET_MAX_PATH_LENGTH;
	urlComponents.lpszUrlPath = strObject.GetBuffer(INTERNET_MAX_PATH_LENGTH + 1);
	::InternetCrackUrl(lpURL, dwURLLen, ICU_DECODE, &urlComponents);
	strServer.ReleaseBuffer();
	strObject.ReleaseBuffer();

	LPCTSTR rgpszAcceptTypes[] = { _T("*/*"), NULL };

	do {
		if (!m_httpOperator.Connect(urlComponents.lpszHostName, urlComponents.nPort))
			break;

		if (!m_httpOperator.OpenRequest(_T("GET"), strObject, HTTP_VERSION, NULL, rgpszAcceptTypes, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, dwContext))
			break;

		if (!m_httpOperator.AddRequestHeader(_T("Accept: */*"), HTTP_ADDREQ_FLAG_ADD))
			break;

		if (!m_httpOperator.AddRequestHeader(_T("Accept-Language: zh-cn"), HTTP_ADDREQ_FLAG_ADD))
			break;

		if (!m_httpOperator.AddRequestHeader(_T("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0)"), HTTP_ADDREQ_FLAG_ADD))
			break;

		if (!m_httpOperator.AddRequestHeader(_T("Content-Type: application/x-www-form-urlencoded"), HTTP_ADDREQ_FLAG_ADD))
			break;

		strInfo.Format(_T("Host: %s"), strServer);
		if (!m_httpOperator.AddRequestHeader(strInfo, HTTP_ADDREQ_FLAG_ADD))
			break;

		if (!m_httpOperator.AddRequestHeader(_T("Connection: Keep-Alive"), HTTP_ADDREQ_FLAG_ADD))
			break;

//		strInfo.Format(_T("Content-Length: %d\r\n\r\n"), dwDataLen);
		if (!m_httpOperator.AddRequestHeader(strInfo, HTTP_ADDREQ_FLAG_ADD))
			break;

		if (!m_httpOperator.SendRequest(NULL, 0, NULL, 0))
			break;

		bRet = TRUE;

	} while (FALSE);

	if (bRet) {
		memset(lpszKey, 0, *lpKeySize);
		*lpKeySize = m_httpOperator.ReadHttpFile(lpszKey, *lpKeySize);
	}

	m_httpOperator.CloseRequest();

	return bRet;
}

void CAGDynamicKeyRequestor::Close()
{
	m_httpOperator.Close();
}