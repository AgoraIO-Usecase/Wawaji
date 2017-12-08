#pragma once

#include "HCNetSDK.h"
#include "PlayM4.h"

#include "FileIO.h"
class CHikVision
{
public:
	CHikVision(int width,int height);
	CHikVision();
	~CHikVision();

	void setResolution(int width,int height);

	bool login(const std::string &addressIp,const std::string nport,const std::string &user,const std::string &psw);
	bool logout();

	bool startPlay(HWND wnd);
	bool stopPlay();

protected:
	static void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
	static void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);

private:
	bool initHikVisionSdk();
	bool uninitHikVisionSdk();

private:
	bool m_isLogin;
	bool m_isPlay;

	short m_channelID;
	LONG m_nport;

	LONG m_lUserID;	
	LONG m_realHandle;

	HWND m_wnd;
	static unsigned char* m_yuv420buffer;
	
	static int m_height;
	static int m_wdith;
};