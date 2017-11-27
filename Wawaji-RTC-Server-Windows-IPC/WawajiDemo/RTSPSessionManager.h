#ifndef __RTSPSESSION_H__
#define __RTSPSESSION_H__

#include "SDKManager.h"
#include "FileIO.h"

class CRTSPSessionManager
{
public:
	CRTSPSessionManager();
	~CRTSPSessionManager();

	bool startRTSP(const std::string &url);
	bool stopRTSP();

private:
	static VOID __stdcall RTSPNetMessage(HANDLE hRTSPSession, DWORD dwMessageType, VOID *lpUser);
	static VOID __stdcall RTSPRealData(HANDLE hRTSPSession, const BYTE *lpBuffer, DWORD dwBufferSize, RTSP_MEDIA_INFO * lpMediaInfo, VOID *lpUser);

private:
	std::string m_rtspUrl;
	HANDLE m_session;
	
	CSDKManager m_sdkManager;
	CFileIO m_h264RtspFile;
};



#endif