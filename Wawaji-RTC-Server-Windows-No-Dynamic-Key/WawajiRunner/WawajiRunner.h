
// WawajiRunner.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWawajiRunnerApp: 
// �йش����ʵ�֣������ WawajiRunner.cpp
//

class CWawajiRunnerApp : public CWinApp
{
public:
	CWawajiRunnerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWawajiRunnerApp theApp;