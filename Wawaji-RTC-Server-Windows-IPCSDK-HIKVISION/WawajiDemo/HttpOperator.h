#pragma once

#include <WinInet.h>
#pragma comment(lib, "Wininet.lib")

class CHttpOperator
{
public:
	CHttpOperator(void);
	~CHttpOperator(void);

	BOOL Create(LPCTSTR lpszAgent = _T("Mozilla/4.0 (Compatible; MSIE 6.0;)"), DWORD dwAccessType = INTERNET_OPEN_TYPE_DIRECT, LPCTSTR lpszProxyName = NULL, LPCTSTR lpszProxyBypass = NULL, DWORD dwFlags = 0);
	BOOL Connect(LPCTSTR lpszServerName, INTERNET_PORT nServerPort = INTERNET_DEFAULT_HTTP_PORT, LPCTSTR lpszUsername = NULL, LPCTSTR lpszPassword = NULL);

	BOOL OpenRequest(LPCTSTR lpszVerb, LPCTSTR lpszObjectName, LPCTSTR lpszVersion, LPCTSTR lpszReferer, LPCTSTR *lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext);
	BOOL AddRequestHeader(LPCTSTR lpszHeaders, DWORD dwModifiers);
	BOOL SendRequest(LPCTSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
	DWORD ReadHttpFile(LPVOID lpBuffer, DWORD dwBytesToRead);

	void CloseRequest();
	void Disconnect();
	void Close();

private:
	HINTERNET	m_hInternetSession;
	HINTERNET	m_hHttpConnection;

	HINTERNET	m_hHttpFile;

	DWORD_PTR	m_dwContext;

};

