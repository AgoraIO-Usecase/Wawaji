#pragma once

#include "HttpOperator.h"

class CAGDynamicKeyRequestor
{
public:
	CAGDynamicKeyRequestor();
	~CAGDynamicKeyRequestor();

	BOOL Create();

	BOOL GetKey(LPCTSTR lpURL, CHAR *lpszKey, SIZE_T *lpKeySize);

	void Close();


private:
	CHttpOperator	m_httpOperator;
};

