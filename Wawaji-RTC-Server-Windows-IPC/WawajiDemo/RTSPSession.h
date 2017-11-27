#ifndef RTSP_SESSION_HEAD_FILE
#define RTSP_SESSION_HEAD_FILE

enum enConnectType
{
	enDisConnect = 0,
	enConnecting,
	enConnected
};

/*
***		��ȡ�������(�������������������)
*/
#define	MAX_READ_ERR_TIME						40

/*
***		״̬�任��ʱ����(����)
*/
#define STATUS_WORK_INTERVAL_TIME				100	

class CRtspSession
{
public:
	CRtspSession(void);
	~CRtspSession(void);

public:
	//�����ӿ�
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
	enConnectType													m_ConnectType;								//����״̬
	char															m_szURL[MAX_PATH];
	INT																m_nTimeOut;									//��ʱʱ�� (��λ����)
	INT																m_nReadErrTime;								//��ȡ�������
	RTSP_MEDIA_INFO*								m_pMediaInfo;								//ý����Ϣ

	DWORD ConnectStream();																						//���ӵ���
	DWORD DisConnectStream();																					//�Ͽ���

protected:
	//�ص�
	lpfuncRTSPNetMessageCb											m_lpNetCallback;
	VOID *															m_lpNetUser;

	lpfuncRTSPRealDataCb											m_lpRealCallback;
	VOID *															m_lpRealUser;

private:
	/*
	***		Result: ������Ϣʱ��
	*/
	static DWORD CALLBACK WorkThread(LPVOID lpParameter);					//��������
	INT DoDisConnectWork();																						//�Ͽ�״̬
	INT DoConnectingWork();																						//��������״̬
	INT DoConnectedWork();																						//������
};


#endif