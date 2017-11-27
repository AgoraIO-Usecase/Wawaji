#ifndef SDK_MANAGER_HEAD_FILE
#define SDK_MANAGER_HEAD_FILE

class CRtspSession;
typedef CRtspSession*	CRtspSessionPtr;

class CSDKManager
{
public:
	CSDKManager(void);
	~CSDKManager(void);

public:
	//�ӿ�
	BOOL IsInitManager();
	LONG InitializeSDKManager();
	VOID ReleaseSDKManager();

	//�����ӿ�
	DWORD CreateSession(HANDLE *hRTSPSession, const char * lpURL);
	DWORD DestroySession(HANDLE hRTSPSession);
	DWORD SetNetMessageCallback(HANDLE hRTSPSession, lpfuncRTSPNetMessageCb lpCallback, VOID *lpUser);
	DWORD Play(HANDLE hRTSPSession, lpfuncRTSPRealDataCb lpCallback, VOID *lpUser);
	DWORD Stop(HANDLE hRTSPSession);

protected:
	int	m_nManagerRef;

	std::map<VOID *, CRtspSessionPtr>	m_mapRTSPSession;
	PCRITICAL_SECTION m_pCSectionRtspSession;
};

#endif