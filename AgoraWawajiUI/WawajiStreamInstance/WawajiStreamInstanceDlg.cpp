
// WawajiStreamInstanceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WawajiStreamInstance.h"
#include "WawajiStreamInstanceDlg.h"
#include "afxdialogex.h"
#include "MyCmdLineInfo.h"
#include "AgoraCameraManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INSTANCE_TEST

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWawajiStreamInstanceDlg 对话框


CWawajiStreamInstanceDlg::CWawajiStreamInstanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWawajiStreamInstanceDlg::IDD, pParent),
	m_lpAgoraObject(nullptr),
	m_lpRtcEngine(nullptr),
	m_hMainUIItemWnd(nullptr),
	m_hMainUIWnd(nullptr),
	m_eInstanceType(eTagConfigType::eTagConfigType_NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	parseCmdLine();

	m_strInstance = m_cmdInfo.getInstance();
	m_hMainUIItemWnd = m_cmdInfo.getMainUIItemWnd();
	m_hMainUIWnd = m_cmdInfo.getMainUIWnd();

	int nIndex = 0;
	sscanf_s(m_strInstance.data(), "Instance%d", &nIndex);
	m_eInstanceType = (eTagConfigType)nIndex;
}

void CWawajiStreamInstanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWawajiStreamInstanceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()

	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), &CWawajiStreamInstanceDlg::OnJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_REJOINCHANNEL_SUCCESS), &CWawajiStreamInstanceDlg::OnRejoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_ERROR), &CWawajiStreamInstanceDlg::OnError)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_QUALITY), &CWawajiStreamInstanceDlg::OnAudioQuality)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_VOLUME_INDICATION), &CWawajiStreamInstanceDlg::OnAudioVolumeIndication)
	ON_MESSAGE(WM_MSGID(EID_LEAVE_CHANNEL), &CWawajiStreamInstanceDlg::OnLeaveChannel)
	ON_MESSAGE(WM_MSGID(EID_MEDIA_ENGINE_EVENT), &CWawajiStreamInstanceDlg::OnMediaEngineEvent)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_DEVICE_STATE_CHANGED), &CWawajiStreamInstanceDlg::OnAudioDeviceStateChanged)
	ON_MESSAGE(WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), &CWawajiStreamInstanceDlg::OnFirstLocalVideoFrame)
	ON_MESSAGE(WM_MSGID(EID_LASTMILE_QUALITY), &CWawajiStreamInstanceDlg::OnLastmileQuality)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), &CWawajiStreamInstanceDlg::OnFirstRemoteVideoDecoded)
	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CWawajiStreamInstanceDlg::OnUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CWawajiStreamInstanceDlg::OnUserOffline)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_AUDIO), &CWawajiStreamInstanceDlg::OnUserMuteAudio)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_VIDEO), &CWawajiStreamInstanceDlg::OnUserMuteVideo)
	ON_MESSAGE(WM_MSGID(EID_LOCAL_VIDEO_STAT), &CWawajiStreamInstanceDlg::OnLocalVideoStats)
	ON_MESSAGE(WM_MSGID(EID_REMOTE_VIDEO_STAT), &CWawajiStreamInstanceDlg::OnRemoteVideoStats)
END_MESSAGE_MAP()


// CWawajiStreamInstanceDlg 消息处理程序

BOOL CWawajiStreamInstanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
 
#ifdef INSTANCE_TEST
	SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	ShowWindow(SW_HIDE);
#endif

	// TODO:  在此添加额外的初始化代码
	SetWindowText(s2cs(m_strInstance));

	initData();
	initCtrl();
	initAgoraMedia();
	joinChannel();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWawajiStreamInstanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWawajiStreamInstanceDlg::OnPaint()
{
	if (IsIconic())
	{
#ifdef INSTANCE_TEST
		CWnd::ShowWindow(SW_HIDE);
#endif
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWawajiStreamInstanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

inline void CWawajiStreamInstanceDlg::initData()
{
	m_nProfileValue[0] = 0;
	m_nProfileValue[1] = 2;
	m_nProfileValue[2] = 10;
	m_nProfileValue[3] = 12;
	m_nProfileValue[4] = 13;
	m_nProfileValue[5] = 20;
	m_nProfileValue[6] = 22;
	m_nProfileValue[7] = 23;
	m_nProfileValue[8] = 30;
	m_nProfileValue[9] = 32;
	m_nProfileValue[10] = 33;
	m_nProfileValue[11] = 35;
	m_nProfileValue[12] = 36;
	m_nProfileValue[13] = 37;
	m_nProfileValue[14] = 38;
	m_nProfileValue[15] = 40;
	m_nProfileValue[16] = 42;
	m_nProfileValue[17] = 43;
	m_nProfileValue[18] = 44;
	m_nProfileValue[19] = 47;
	m_nProfileValue[20] = 48;
	m_nProfileValue[21] = 50;
	m_nProfileValue[22] = 52;
	m_nProfileValue[23] = 54;
	m_nProfileValue[24] = 55;
	m_nProfileValue[25] = 60;
	m_nProfileValue[26] = 62;
	m_nProfileValue[27] = 64;
	m_nProfileValue[28] = 66;
	m_nProfileValue[29] = 67;
	m_nProfileValue[30] = 70;
	m_nProfileValue[31] = 72;
}

inline void CWawajiStreamInstanceDlg::initCtrl()
{
	m_strAppId = gAgoraConfigInstance.getAppId();
	m_strAppcertificateId = gAgoraConfigInstance.getAppCertificateId();
	m_strChannel = gAgoraConfigInstance.getChannelName();
	m_uLoginUid = str2int(gAgoraConfigInstance.getLoginUid(m_strInstance));
	
	if ((0 == m_strAppId.length() || 0 == m_strAppcertificateId.length() || 0 == m_strChannel.length() || 0 == m_uLoginUid)){
		CAgoraFormatStr::AgoraMessageBox(_T("There are one empty AppId, AppCertificateId, Channel, and LoginUID in the configuration file. Please modify"));
		//PostQuitMessage(0);
		return;
	}
}

inline void CWawajiStreamInstanceDlg::uninitCtrl()
{

}

inline void CWawajiStreamInstanceDlg::initAgoraMedia()
{
	m_lpAgoraObject = CAgoraObject::GetAgoraObject(s2cs(m_strAppId));
	ASSERT(m_lpAgoraObject);
	m_lpAgoraObject->SetMsgHandlerWnd(m_hWnd);

	m_lpRtcEngine = CAgoraObject::GetEngine();
	ASSERT(m_lpRtcEngine);

	CString strSdkLogFilePath = s2cs(getMediaSdkLogPath(m_strInstance));
	m_lpAgoraObject->SetLogFilePath(strSdkLogFilePath);

	m_lpAgoraObject->EnableWebSdkInteroperability(TRUE);

	std::string leftRotate90 = gAgoraConfigInstance.getLeftRotate90(m_strInstance);
	m_lpAgoraObject->EnableLocalPublishLeftRotate90(str2int(leftRotate90));
	m_lpAgoraObject->EnableLocalMirrorImage(!str2int(leftRotate90));

	m_lpAgoraObject->EnableVideo(TRUE);
	m_lpAgoraObject->EnableAudio(FALSE);

	m_lpAgoraObject->EnableLastmileTest(FALSE);
	m_lpAgoraObject->SetClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
	m_lpAgoraObject->SetChannelProfile(TRUE);

	//Rtmp
	BOOL bEnableRotate = str2int(gAgoraConfigInstance.getLeftRotate90(m_strInstance));
	BOOL bEnableRtmp = str2int(gAgoraConfigInstance.getRtmpSave(m_strInstance));
	if (bEnableRtmp){

		int nRtmpWidth = str2int(gAgoraConfigInstance.getRtmpWidth(m_strInstance));
		int nRtmpHeight = str2int(gAgoraConfigInstance.getRtmpHeight(m_strInstance));
		int nRtmpFps = str2int(gAgoraConfigInstance.getRtmpFps(m_strInstance));
		int nRtmpBitrate = str2int(gAgoraConfigInstance.getResolutionBitrate(m_strInstance));
		std::string strRtmpURL = gAgoraConfigInstance.getRtmpUrl(m_strInstance);
		AGE_PUBLISH_PARAM pp;
		pp.bitrate = nRtmpBitrate;
		pp.fps = nRtmpFps;
		pp.height = bEnableRotate ? nRtmpWidth : nRtmpHeight;
		pp.width = bEnableRotate ? nRtmpHeight : nRtmpWidth;
		pp.rtmpUrl = strRtmpURL;
		m_lpAgoraObject->setPublishParam(pp);
		m_lpAgoraObject->enablePublish(true);

		CAgoraFormatStr::AgoraWriteLog(("RtmpParam Width: %d,Height: %d,Fps: %d,Bitrate: %d,URL: %s"),pp.width,pp.height,pp.fps,pp.bitrate,(pp.rtmpUrl).data());
		CAgoraFormatStr::AgoraOutDebugStr(_T("Rtmp Wdith: %d,Height: %d,Fps: %d,Bitrate: %d \r\n URL : %s"),pp.width,pp.height,pp.fps,pp.bitrate,s2cs(pp.rtmpUrl));
	}
}

inline void CWawajiStreamInstanceDlg::uninitAgoraMedia()
{
	if (nullptr == m_lpAgoraObject){
		return;
	}

	m_lpAgoraObject->EnableVideo(FALSE);
	m_lpAgoraObject->EnableLastmileTest(FALSE);
	if (m_lpAgoraObject){
		CAgoraObject::CloseAgoraObject();
		m_lpAgoraObject = nullptr;
		m_lpRtcEngine = nullptr;
	}
}

inline void CWawajiStreamInstanceDlg::joinChannel()
{
	std::string strCameraComId = gAgoraConfigInstance.getCameraComID(m_strInstance);
	CAgoraCameraManager agoraCameraManager;
	agoraCameraManager.Create(m_lpRtcEngine);
	BOOL bRes = agoraCameraManager.SetCurDevice(s2cs(strCameraComId));
	CAgoraFormatStr::AgoraWriteLog("SetComID: %s, nRet: %d", strCameraComId.data(), bRes);

	m_uLoginUid = str2int(gAgoraConfigInstance.getLoginUid(m_strInstance));
	std::string strAppcertificatId = gAgoraConfigInstance.getAppCertificateId();
	m_lpAgoraObject->SetSelfUID((m_uLoginUid));
	m_lpAgoraObject->SetAppCert(s2cs(strAppcertificatId));

	VideoCanvas vc;
	vc.renderMode = RENDER_MODE_FIT;
	vc.uid = m_uLoginUid;
#ifdef INSTANCE_TEST
	vc.view = m_hMainUIItemWnd;
#else
	vc.view = /*hMainUIItemWnd*/m_hWnd;
#endif
	m_lpRtcEngine->setupLocalVideo(vc);

	int nVideoProfileIndex = m_nProfileValue[str2int(gAgoraConfigInstance.getResolutionIndex())];
	BOOL bEnableRotate = str2int(gAgoraConfigInstance.getLeftRotate90(m_strInstance));
	BOOL bEnableSwithchWH = str2int(gAgoraConfigInstance.getSwitchWHEnable(m_strInstance));
	std::string strFormat = gAgoraConfigInstance.getResolution();
	int nWidth = 0, nHeight = 0, nFps = 0, nBitrate = 0;
	sscanf_s(strFormat.data(), ("%dx%d %dfps %dkbps"), &nWidth, &nHeight, &nFps, &nBitrate);
	if (bEnableRotate && !bEnableSwithchWH){

		if (bEnableRotate)
		m_lpAgoraObject->SetVideoProfileEx(nHeight, nWidth, nFps, nBitrate);

		CAgoraFormatStr::AgoraWriteLog(("Rotate90 SetVideoProfileEx Width: %d,Height: %d,Fps: %d,Bitrate."), nHeight,nWidth,nFps,nBitrate);
		CAgoraFormatStr::AgoraOutDebugStr(_T("Rotate90 SetVideoProfileEx Wdith: %d,Height: %d,Fps: %d,Bitrate: %d"),nHeight,nWidth,nFps,nBitrate);
	}
	else if (!bEnableRotate && bEnableSwithchWH){

		m_lpAgoraObject->SetVideoProfile((VIDEO_PROFILE_TYPE)nVideoProfileIndex, bEnableSwithchWH);
		CAgoraFormatStr::AgoraWriteLog(("SwitchWH SetVideoProfileEx Width: %d,Height: %d,Fps: %d,Bitrate."), nWidth, nHeight, nFps, nBitrate);
		CAgoraFormatStr::AgoraOutDebugStr(_T("SwitchWH SetVideoProfileEx Wdith: %d,Height: %d,Fps: %d,Bitrate: %d"), nWidth, nHeight, nFps, nBitrate);
	}
	else if (!bEnableSwithchWH && !bEnableRotate){

		m_lpAgoraObject->SetVideoProfile((VIDEO_PROFILE_TYPE)nVideoProfileIndex,bEnableSwithchWH);
		CAgoraFormatStr::AgoraWriteLog(("SetVideoProfileEx Width: %d,Height: %d,Fps: %d,Bitrate."), nWidth, nHeight, nFps, nBitrate);
		CAgoraFormatStr::AgoraOutDebugStr(_T("SetVideoProfileEx Wdith: %d,Height: %d,Fps: %d,Bitrate: %d"), nWidth, nHeight, nFps, nBitrate);
	}

	m_lpRtcEngine->startPreview();

	m_lpAgoraObject->MuteAllRemoteVideo(TRUE);
	m_lpAgoraObject->MuteAllRemoteAudio(TRUE);

	if(0 == m_strAppcertificateId.length()){

		m_lpAgoraObject->JoinChannel(s2cs(m_strChannel), m_uLoginUid);
	}
	else{

		CStringA strMediaChannelKey = m_lpAgoraObject->getDynamicMediaChannelKey(s2cs(m_strChannel));
		m_lpAgoraObject->JoinChannel(s2cs(m_strChannel), m_uLoginUid, strMediaChannelKey);
	}
}

void CWawajiStreamInstanceDlg::OnClose()
{
	int nNum = 0;
	closeProcess(KWawajiStream,nNum);

	if (m_lpAgoraObject){

		m_lpAgoraObject->LeaveCahnnel();
	}
	if (m_lpRtcEngine){

		m_lpRtcEngine->stopPreview();
	}

	uninitAgoraMedia();
	uninitCtrl();

	CDialogEx::OnCancel();
	CDialogEx::OnCancel();
}

void CWawajiStreamInstanceDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

inline void CWawajiStreamInstanceDlg::parseCmdLine()
{
	theApp.ParseCommandLine(m_cmdInfo);
}


LRESULT CWawajiStreamInstanceDlg::OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;
	if (lpData){


		delete lpData; lpData = NULL;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnRejoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_REJOINCHANNEL_SUCCESS lpData = (LPAGE_REJOINCHANNEL_SUCCESS)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnWarning(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnError(WPARAM wParam, LPARAM lParam)
{
	LPAGE_ERROR lpData = (LPAGE_ERROR)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnAudioQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_QUALITY lpData = (LPAGE_AUDIO_QUALITY)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnAudioVolumeIndication(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_VOLUME_INDICATION lpData = (LPAGE_AUDIO_VOLUME_INDICATION)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LEAVE_CHANNEL lpData = (LPAGE_LEAVE_CHANNEL)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnRtcStats(WPARAM wParam, LPARAM lParam)
{

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnMediaEngineEvent(WPARAM wParam, LPARAM lParam)
{
	LPAGE_MEDIA_ENGINE_EVENT lpData = (LPAGE_MEDIA_ENGINE_EVENT)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnAudioDeviceStateChanged(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_DEVICE_STATE_CHANGED lpData = (LPAGE_AUDIO_DEVICE_STATE_CHANGED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnLastmileQuality(WPARAM wParam, LPARAM lParam)
{

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnVideoDeviceStateChanged(WPARAM wParam, LPARAM lParam)
{
	LPAGE_VIDEO_DEVICE_STATE_CHANGED lpData = (LPAGE_VIDEO_DEVICE_STATE_CHANGED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnFirstLocalVideoFrame(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_LOCAL_VIDEO_FRAME lpData = (LPAGE_FIRST_LOCAL_VIDEO_FRAME)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnFirstRemoteVideoDecoded(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = (LPAGE_FIRST_REMOTE_VIDEO_DECODED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnFirstRemoteVideoFrame(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_FRAME lpData = (LPAGE_FIRST_REMOTE_VIDEO_FRAME)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnUserJoined(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_JOINED lpData = (LPAGE_USER_JOINED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnUserOffline(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_OFFLINE lpData = (LPAGE_USER_OFFLINE)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnUserMuteAudio(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_AUDIO lpData = (LPAGE_USER_MUTE_AUDIO)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnUserMuteVideo(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_VIDEO lpData = (LPAGE_USER_MUTE_VIDEO)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnApiCallExecuted(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnLocalVideoStats(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LOCAL_VIDEO_STAT lpData = (LPAGE_LOCAL_VIDEO_STAT)wParam;
	if (lpData){

		if (0 == lpData->sentBitrate || 0 == lpData->sentFrameRate){
			
			AG_WAWAJI_LOCALVIDEO_STATS DataLocalVideoStats;
			DataLocalVideoStats.InstanceType = m_eInstanceType;
			DataLocalVideoStats.strInstance = m_strInstance;
			DataLocalVideoStats.uRemoteInstanceUID = m_uLoginUid;
			char szbuf[24] = { '\0' };
			COPYDATASTRUCT cd;
			cd.dwData = m_uLoginUid;
			cd.cbData = sizeof(DataLocalVideoStats);
			cd.lpData = (PVOID)&DataLocalVideoStats;
			::SendMessage(m_hMainUIWnd, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cd);
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnRemoteVideoStats(WPARAM wParam, LPARAM lParam)
{
	LPAGE_REMOTE_VIDEO_STAT lpData = (LPAGE_REMOTE_VIDEO_STAT)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnCameraReady(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnVideoStopped(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnConnectionLost(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnConnectionInterrupted(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnUserEnableVideo(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_VIDEO lpData = (LPAGE_USER_MUTE_VIDEO)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnStartRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnStopRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CWawajiStreamInstanceDlg::OnRefreshRecordingServiceStatus(WPARAM wParam, LPARAM lParam)
{
	LPAGE_RCDSRV_STATUS lpData = (LPAGE_RCDSRV_STATUS)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}
