
// WawajiStreamInstance.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWawajiStreamInstanceApp: 
// �йش����ʵ�֣������ WawajiStreamInstance.cpp
//

class CWawajiStreamInstanceApp : public CWinApp
{
public:
	CWawajiStreamInstanceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWawajiStreamInstanceApp theApp;