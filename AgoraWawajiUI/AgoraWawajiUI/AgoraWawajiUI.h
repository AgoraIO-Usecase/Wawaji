
// AgoraWawajiUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAgoraWawajiUIApp: 
// �йش����ʵ�֣������ AgoraWawajiUI.cpp
//

class CAgoraWawajiUIApp : public CWinApp
{
public:
	CAgoraWawajiUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAgoraWawajiUIApp theApp;