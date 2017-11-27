#ifndef RTSP_SESSION_HEAD_FILE
#define RTSP_SESSION_HEAD_FILE

enum enConnectType
{
	enDisConnect = 0,
	enConnecting,
	enConnected
};

/*
***		读取错误次数(超过次数，则进行重连)
*/
#define	MAX_READ_ERR_TIME						40

/*
***		状态变换，时间间隔(毫秒)
*/
#define STATUS_WORK_INTERVAL_TIME				100	

class CRtspSession
{
public:
	CRtspSession(void);
	~CRtspSession(void);

public:
	//基本接口
	DWORD CreateSession(const char *lpURL);
	VOID DestroySession(VOID);
	DWORD SetNetMessageCallback(lpfuncRTSPNetMessageCb lpCallback, VOID * lpUser);
	DWORD Play(lpfuncRTSPRealDataCb lpCallback, VOID * lpUser, INT nTimeOut = 5000);
	DWORD Stop(VOID);


private:
	bool											m_bRunning;
	HANDLE 									m_pThread;
	bool m_isThreadExit;

	AVFormatContext *												m_pFormatCtx;
	AVPacket *														m_pPacket;									//Packet
	enConnectType													m_ConnectType;								//连接状态
	char															m_szURL[MAX_PATH];
	INT																m_nTimeOut;									//超时时间 (单位毫秒)
	INT																m_nReadErrTime;								//读取错误次数
	RTSP_MEDIA_INFO*								m_pMediaInfo;								//媒体信息

	DWORD ConnectStream();																						//连接到流
	DWORD DisConnectStream();																					//断开流

protected:
	//回调
	lpfuncRTSPNetMessageCb											m_lpNetCallback;
	VOID *															m_lpNetUser;

	lpfuncRTSPRealDataCb											m_lpRealCallback;
	VOID *															m_lpRealUser;

private:
	/*
	***		Result: 返回休息时间
	*/
	static DWORD CALLBACK WorkThread(LPVOID lpParameter);					//工作函数
	INT DoDisConnectWork();																						//断开状态
	INT DoConnectingWork();																						//正在连接状态
	INT DoConnectedWork();																						//已连接
};


#endif