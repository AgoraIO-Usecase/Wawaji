#pragma once

typedef struct tagVideoData
{
	tagVideoData()
	{
		bRunning = TRUE;
		hDC = NULL;
	}

	CString strRTSP;
	HWND hWnd;
	BOOL bRunning;
	HANDLE hProc;
	HDC hDC;
	CRect rectPre;
} VIDEODATA, *LPVIDEODATA;


#include "FileIO.h"

class CRtspSessionEx
{
public:
	CRtspSessionEx();
	~CRtspSessionEx();

	bool startRtsp(const std::string &rtspURL);
	bool stopRtsp();


private:
	HANDLE m_ThreadRtsp;
	bool m_isConnected;
	bool m_isStart;

	std::string  m_rtmpUrl;
	CFileIO m_fileYUV;	

	static DWORD WINAPI ThreadRtspProc(LPVOID lpParameter);
};