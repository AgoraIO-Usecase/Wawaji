
// AgoraWawajiUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiUI.h"
#include "AgoraWawajiUIDlg.h"
#include "afxdialogex.h"

//#include "DlgConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CAgoraWawajiUIDlg 对话框



CAgoraWawajiUIDlg::CAgoraWawajiUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgoraWawajiUIDlg::IDD, pParent),
	m_nLastmileQuality(QUALITY_TYPE::QUALITY_DOWN),
	m_bIsAutomatic(TRUE),
	m_bIsJoinChannel(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgoraWawajiUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Camera1, m_CtlCamera1);
	DDX_Control(pDX, IDC_STATIC_Camera2, m_CtlCamera2);
	DDX_Control(pDX, IDC_STATIC_Value_UID_1, m_CtlUID1Value);
	DDX_Control(pDX, IDC_STATIC_Value_CameraID_1, m_CtlCamera1Vaule);
	DDX_Control(pDX, IDC_STATIC_Value_UID_2, m_CtlUID2Value);
	DDX_Control(pDX, IDC_STATIC_Value_CameraID_2, m_CtlCamera2Value);

	DDX_Control(pDX, IDC_STATIC_AppID, m_CtlAppIdKey);
	DDX_Control(pDX, IDC_EDIT_AppID, m_EditAppValue);
	DDX_Control(pDX, IDC_STATIC_AppCertificateID, m_CtlAppCertificateKey);
	DDX_Control(pDX, IDC_EDIT_AppCertificate, m_EditAppCertificateValue);
	DDX_Control(pDX, IDC_STATIC_Channel, m_CtlChannelKey);
	DDX_Control(pDX, IDC_EDIT_ChannelID,m_EditChannelValue);
	DDX_Control(pDX, IDC_STATIC_VideoProfile, m_CtlVideoProfileKey);
	DDX_Control(pDX, IDC_COMBO_VideoProfile, m_ComboVideoProfileValue);
	DDX_Control(pDX, IDC_STATIC_UptimeKey, m_CtlUpTimeKey);
	DDX_Control(pDX, IDC_STATIC_UpTime_Value, m_CtlUpTimeValue);
	DDX_Control(pDX, IDC_STATIC_SDKVersion, m_CtlSdkVersion);
	DDX_Control(pDX, IDC_LIST_WawajiLog, m_listLog);
	DDX_Control(pDX, IDC_BUTTON_Start, m_BtnStart);
	DDX_Control(pDX, IDC_BUTTON_Settings, m_BtnSettings);
	DDX_Control(pDX, IDC_BUTTON_Restart, m_BtnRestart);
	DDX_Control(pDX, IDC_BUTTON_UploadLogs, m_BtnUpLoadLog);
}

BEGIN_MESSAGE_MAP(CAgoraWawajiUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_Start, &CAgoraWawajiUIDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_Settings, &CAgoraWawajiUIDlg::OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_Restart, &CAgoraWawajiUIDlg::OnBnClickedButtonRestart)
	ON_BN_CLICKED(IDC_BUTTON_UploadLogs, &CAgoraWawajiUIDlg::OnBnClickedButtonUploadlogs)
	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS),&CAgoraWawajiUIDlg::OnJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_REJOINCHANNEL_SUCCESS), &CAgoraWawajiUIDlg::OnRejoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_ERROR), &CAgoraWawajiUIDlg::OnError)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_QUALITY), &CAgoraWawajiUIDlg::OnAudioQuality)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_VOLUME_INDICATION), &CAgoraWawajiUIDlg::OnAudioVolumeIndication)
	ON_MESSAGE(WM_MSGID(EID_LEAVE_CHANNEL), &CAgoraWawajiUIDlg::OnLeaveChannel)
	ON_MESSAGE(WM_MSGID(EID_MEDIA_ENGINE_EVENT), &CAgoraWawajiUIDlg::OnMediaEngineEvent)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_DEVICE_STATE_CHANGED), &CAgoraWawajiUIDlg::OnAudioDeviceStateChanged)
	ON_MESSAGE(WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), &CAgoraWawajiUIDlg::OnFirstLocalVideoFrame)
	ON_MESSAGE(WM_MSGID(EID_LASTMILE_QUALITY), &CAgoraWawajiUIDlg::OnLastmileQuality)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), &CAgoraWawajiUIDlg::OnFirstRemoteVideoDecoded)
	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CAgoraWawajiUIDlg::OnUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CAgoraWawajiUIDlg::OnUserOffline)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_AUDIO), &CAgoraWawajiUIDlg::OnUserMuteAudio)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_VIDEO), &CAgoraWawajiUIDlg::OnUserMuteVideo)
	ON_MESSAGE(WM_MSGID(EID_LOCAL_VIDEO_STAT), &CAgoraWawajiUIDlg::OnLocalVideoStats)
	ON_MESSAGE(WM_MSGID(EID_REMOTE_VIDEO_STAT), &CAgoraWawajiUIDlg::OnRemoteVideoStats)
	ON_MESSAGE(WawajiMsgType_Config,OnConfigParamSave)
	ON_MESSAGE(WawajiMsgType_RemoteVideoStats, OnInstanceRemoteVideoStats)
END_MESSAGE_MAP()


// CAgoraWawajiUIDlg 消息处理程序

BOOL CAgoraWawajiUIDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	//SetBackgroundImage(IDB_BITMAP_MAINUI);
	SetBackgroundColor(RGB(0xff, 0xff, 0xff), TRUE);

	TCHAR path[255];
	SHGetSpecialFolderPath(0, path, CSIDL_DESKTOPDIRECTORY, 0);
	CString strDesktop = _T("\\roominfo.txt");
	wcscat_s(path, 255, strDesktop.GetBuffer());
	CFileIO fileChannelName;
	fileChannelName.openReadFile(cs2s(path).data());
	m_strChannel = fileChannelName.readLine();
	gMaxCameraCount  = str2int(fileChannelName.readLine());
	gMaxCameraCount = gMaxCameraCount >= 2 ? gMaxCameraCount : 2;
	if ("" == m_strChannel){
		CAgoraFormatStr::AgoraMessageBox(_T("桌面roominfo.txt中没有频道信息,请修改"));
		ShellExecute(NULL, _T("open"), path, NULL, NULL, SW_SHOW);
		::PostQuitMessage(0);
		return FALSE;
	}

	gAgoraConfigMainUI.setChannelName(m_strChannel);
	int num = 0;
	closeProcess(KWawajiStream, num);

	m_strAppId = gAgoraConfigMainUI.getAppId();
	m_strAppcertId = gAgoraConfigMainUI.getAppCertificateId();
	m_strChannel = gAgoraConfigMainUI.getChannelName();

	if (0 == m_strAppId.length() || 0 == m_strAppcertId.length() || 0 == m_strChannel.length()){

		ShowWindow(SW_HIDE);
		OnBnClickedButtonSettings();
	}
	else{

		InitCtrl();
		initAgoraMedia();
		SetTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM, 1000, nullptr);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgoraWawajiUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAgoraWawajiUIDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (IsIconic())
	{
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
		if (m_bParamStatus){

			DrawClient(&dc);
		}
		//CDialogEx::OnPaint();
	}
}

void CAgoraWawajiUIDlg::OnNcPaint()
{
	CDialogEx::OnNcPaint();
}

void CAgoraWawajiUIDlg::OnLButtonDown(UINT, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAgoraWawajiUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

inline void CAgoraWawajiUIDlg::InitCtrl()
{
	//shell:startup
	HKEY kResult = NULL;
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_ALL_ACCESS, &kResult);
	if (lRet == ERROR_SUCCESS){

		TCHAR path[MAXPATHLEN] = { 0 };
			GetModuleFileName(nullptr, path, MAXPATHLEN);
			lRet = RegSetValueEx(kResult, _T("AgoraWawajiUI"), 0, REG_SZ, (const unsigned char*)path, (DWORD)MAXPATHLEN);
			if (ERROR_SUCCESS == lpRun){

				RegCloseKey(kResult);
				kResult = NULL;
			}
		}

	//initCtrlInfo
	m_nLastmileQuality = QUALITY_TYPE::QUALITY_DOWN;
	CBitmap	bmpNetQuality;
	bmpNetQuality.LoadBitmap(IDB_NETWORK_QUALITY);
	m_imgNetQuality.Create(32, 32, ILC_COLOR24 | ILC_MASK, 6, 1);
	m_imgNetQuality.Add(&bmpNetQuality, RGB(0xFF, 0, 0xFF));

	std::string strAgoraWawajiMainUILogPath = getAgoraWawajiAppLogPath(StrKeyQuote::KAppAttributeMainUI);
	gAgoraWawajiLog.openLog(strAgoraWawajiMainUILogPath);
	CAgoraFormatStr::AgoraWriteLog("=========Local Begin=========");
	int nIndex = strAgoraWawajiMainUILogPath.rfind("\\");
	m_strAgoraWawajiMainUILogPath = strAgoraWawajiMainUILogPath.substr(nIndex + 1,strAgoraWawajiMainUILogPath.length() - nIndex - 1);

	m_EditAppValue.EnableWindow(FALSE);
	m_EditAppCertificateValue.EnableWindow(FALSE);
	m_EditChannelValue.EnableWindow(FALSE);
	m_ComboVideoProfileValue.EnableWindow(FALSE);
	m_BtnRestart.ShowWindow(SW_HIDE);

	LPAG_WAWAJI_CONFIG lpData = new AG_WAWAJI_CONFIG;
	lpData->configInstance = eTagConfigType::eTagConfigType_Instance1;
	lpData->isRunStream = FALSE;
	::PostMessage(theApp.GetMainWnd()->m_hWnd, WawajiMsgType_Config, (WPARAM)lpData, NULL);

	LPAG_WAWAJI_CONFIG lpData1 = new AG_WAWAJI_CONFIG;
	lpData1->configInstance = eTagConfigType::eTagConfigType_Instance2;
	lpData1->isRunStream = FALSE;
	::PostMessage(theApp.GetMainWnd()->m_hWnd, WawajiMsgType_Config, (WPARAM)lpData1, NULL);

	m_nClearLog = str2int(gAgoraConfigMainUI.getClearLogInterval());
	SetTimer(EventType_TIMER_EVENT_CLEARLOG, 1000, NULL);
}

inline void CAgoraWawajiUIDlg::InitCtrlTxt()
{
	m_strAppId = gAgoraConfigMainUI.getAppId();
	m_strAppcertId = gAgoraConfigMainUI.getAppCertificateId();
	m_strChannel = gAgoraConfigMainUI.getChannelName();
	m_nClearLog = str2int(gAgoraConfigMainUI.getClearLogInterval());

	gEnumLangType = (eTagLanguageType)(str2int(gAgoraConfigMainUI.getLanguagePack()));
	switchLang();

	m_EditAppValue.SetWindowTextW(s2cs(m_strAppId));
	m_EditAppCertificateValue.SetWindowTextW(s2cs(m_strAppcertId));
	m_EditChannelValue.SetWindowTextW(s2cs(m_strChannel));
	std::string strVideoProfile = gAgoraConfigMainUI.getResolution();
	m_ComboVideoProfileValue.ResetContent();
	m_ComboVideoProfileValue.AddString(s2cs(strVideoProfile));
	m_ComboVideoProfileValue.SetCurSel(0);
}

inline void CAgoraWawajiUIDlg::unInitCtrl()
{
	gAgoraWawajiLog.close();
	m_nLastmileQuality = QUALITY_TYPE::QUALITY_DOWN;
	Invalidate();

	for (std::map<std::string, LPAG_WAWAJI_STREAMINFO>::iterator it = m_mapStream.begin(); m_mapStream.end() != it;){
		
		delete it->second;
		it->second = nullptr;
		it = m_mapStream.erase(it);
	}

	m_mapStream.clear();
	m_mapUidMgr.clear();
}

inline void CAgoraWawajiUIDlg::switchLang()
{
	Language_Pack::switchLang();

	SetWindowText(gStrTitleUI);
	m_BtnSettings.SetWindowTextW(gStrSettings);
	m_BtnStart.SetWindowTextW(gStrStart);
	m_BtnRestart.SetWindowTextW(gStrRestart);
	m_BtnUpLoadLog.SetWindowTextW(gStrUploadLog);

}

inline void CAgoraWawajiUIDlg::initAgoraMedia()
{
	if ("" == m_strAppId){
		return;
	}
	m_lpAgoraObject = CAgoraObject::GetAgoraObject(s2cs(m_strAppId));
	ASSERT(m_lpAgoraObject);
	m_lpAgoraObject->SetMsgHandlerWnd(m_hWnd);

	m_lpRtcEngine = CAgoraObject::GetEngine();
	ASSERT(m_lpRtcEngine);

	m_lpAgoraObject->SetAppCert(s2cs(m_strAppcertId));
	CString strSdkLogFilePath = s2cs(getMediaSdkLogPath("MainUI"));
	m_lpAgoraObject->SetLogFilePath(strSdkLogFilePath);
	m_bParamStatus = TRUE;
	m_lpAgoraObject->EnableLastmileTest(TRUE);
	m_lpAgoraObject->EnableVideo(TRUE);

	CString strSdkVersion = CAgoraObject::GetSDKVersionEx();
	m_CtlSdkVersion.SetWindowTextW(strSdkVersion);
}

inline void CAgoraWawajiUIDlg::uninitAgoaMeida()
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

inline void CAgoraWawajiUIDlg::DrawClient(CDC *lpDC)
{
	if (0 <= m_nLastmileQuality){

		m_imgNetQuality.Draw(lpDC, m_nLastmileQuality, CPoint(980, 10), ILD_NORMAL);
	}
}

inline void CAgoraWawajiUIDlg::AddTxt(LPCTSTR lpFormat, ...)
{
	TCHAR szBuffer[1024] = { _T("\0") };
	va_list args;
	SYSTEMTIME st;
	GetLocalTime(&st);
	swprintf_s(szBuffer,_T("%02d%02d:%02d%02d%02d "),st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	va_start(args, lpFormat);
	_vsnwprintf(szBuffer + _tcslen(szBuffer), sizeof(szBuffer) / sizeof(TCHAR) - _tcslen(szBuffer), lpFormat, args);
	va_end(args);
	
	m_listLog.AddString(szBuffer);
}

void CAgoraWawajiUIDlg::OnBnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码	
	if (m_bIsJoinChannel){

		StopWawajiMonitor();

		SetTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM,2000,nullptr);
	}
}

void CAgoraWawajiUIDlg::OnBnClickedButtonSettings()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM);
	KillTimer(EventType_TIMER_EVENT_CHECK_CAMERAPARAM);
	KillTimer(EventType_TIMER_EVENT_Runnin_Stream);

	if (m_lpAgoraObject)
	m_lpAgoraObject->EnableLastmileTest(TRUE);
	INT_PTR nResponse = m_DlgConfig.DoModal();
	if (IDOK == nResponse){

		m_DlgConfig.ShowWindow(SW_SHOW);
	}
	else if (IDCANCEL == nResponse){

	}

	if (IDYES==  (nResponse = AfxMessageBox(_T("修改【BaseInfo】配置信息 建议重启程序,是否重启所有程序 (Y-是; N-否)"), IDOK | IDCANCEL))){

		PostQuitMessage(0);
		//run restart.bat
		std::string strBatPath = getAbsoluteDir() + "Restart.bat";
		ShellExecute(NULL, _T("open"), s2cs(strBatPath), NULL, NULL, SW_SHOW);
	}
	else{

		if (IDYES == (nResponse = AfxMessageBox(_T("修改【推流配置】信息 建议重新开始推流, 是否重新推流 (Y-是; N-否)"), IDOK | IDCANCEL))){

			ShowWindow(SW_SHOW);
			//重新收集配置信息

			LPAG_WAWAJI_CONFIG lpData = new AG_WAWAJI_CONFIG;
			lpData->configInstance = eTagConfigType::eTagConfigType_NULL;
			lpData->isRunStream = true;
			::PostMessage(m_hWnd, WawajiMsgType_Config, (WPARAM)lpData, NULL);

			AddTxt(_T("[Monitor] !!!!!! 更新配置会重启所有推流程序\n"));
		}
	}
}


void CAgoraWawajiUIDlg::OnBnClickedButtonRestart()
{
	// TODO:  在此添加控件通知处理程序代码
	CAgoraFormatStr::AgoraWriteLog("Restart");
	
	StopWawajiMonitor();

	SetTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM,1000,nullptr);
}

void CAgoraWawajiUIDlg::OnBnClickedButtonUploadlogs()
{
	// TODO:  在此添加控件通知处理程序代码
	CAgoraFormatStr::AgoraMessageBox(_T("功能开发中.."));
}

void CAgoraWawajiUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (enumWawajiEventType::EventType_TIMER_EVENT_CHECK_CAMERAPARAM == nIDEvent){
	
		checkCameraInfo();
	}
	else if (enumWawajiEventType::EventType_TIMER_EVENT_CHECK_BASEINFOPARAM == nIDEvent){

		int num = 0;
		closeProcess(KWawajiStream, num);
		//ASSERT(num <= m_mapStream.size());
		for (std::map<std::string, LPAG_WAWAJI_STREAMINFO>::iterator it = m_mapStream.begin();
			m_mapStream.end() != it;){//容易造成内存泄漏.
			delete it->second; 
			it->second = nullptr;
			it = m_mapStream.erase(it);
		}
		m_mapStream.clear();
		m_mapUidMgr.clear();

		InitCtrlTxt();
		checkBaseInfo();
	}
	else if (EventType_TIMER_EVENT_Runnin_Stream == nIDEvent){
		
		StartRunWawajiStream();
	}
	else if (EventType_TIMER_EVENT_UpTime == nIDEvent){

		m_ltimeInterval += 1;

		int nHour = 0; int nMinutes = 0; int nSeconds = 0;
		int nDivison = 0; int nReminds = 0;
		nHour = nDivison = m_ltimeInterval / 3600;
		nReminds = m_ltimeInterval % 3600;
		nMinutes = nDivison = nReminds / 60;
		nSeconds = nReminds = nReminds % 60;
		CString strUpTime;
		strUpTime.Format(_T("%02d:%02d:%02d"),nHour,nMinutes,nSeconds);
		m_CtlUpTimeValue.SetWindowTextW(strUpTime);
	}

	if (EventType_TIMER_EVENT_CLEARLOG == nIDEvent){

		std::vector<CString> vecFileList;
		std::string logPath = getAbsoluteDir() + "logger\\";
		getInvalidFileList(vecFileList, s2cs(logPath), m_nClearLog);

		for (std::vector<CString>::iterator it = vecFileList.begin(); vecFileList.end() != it; it++){
			if (DeleteFile(*it)){

				CAgoraFormatStr::AgoraOutDebugStr(_T("ClearLogTimer Delete File %s"), (*it));
			}
		}
	}
}

void CAgoraWawajiUIDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CRect rt;
	m_CtlCamera1.GetClientRect(&rt);
	//m_CtlCamera1.MoveWindow(rt.left + 50, rt.top + 10, rt.right - rt.left ,rt.bottom - rt.top + 180);
	//m_CtlCamera2.MoveWindow(rt.right+ 160, rt.top + 10, rt.right - rt.left, rt.bottom - rt.top + 180);
	CDialogEx::OnShowWindow(bShow, nStatus);
}

inline void CAgoraWawajiUIDlg::checkBaseInfo()
{
	if (NULL == m_DlgConfig.m_hWnd || !m_DlgConfig.IsWindowVisible()){

		//Check BaseInfo :AppID,AppCertID,Channel,
		if (0 == m_strAppId.length() || 0 == m_strAppcertId.length() || 0 == m_strChannel.length()){
			CAgoraFormatStr::AgoraOutDebugStr(_T("AppId:%s\n AppCert:%s\n ChannelName:%s\n 其中有一个参数为空，不满足要求!"),
				s2cs(m_strAppId).GetBuffer(), s2cs(m_strAppcertId).GetBuffer(), s2cs(m_strChannel).GetBuffer());
			CAgoraFormatStr::AgoraWriteLog("AppId: %s\n AppCertificateId: %s ChannelName: %s 参数自检失败, ", m_strAppId.data(), m_strAppcertId.data(), m_strChannel.data());
			KillTimer(enumWawajiEventType::EventType_TIMER_EVENT_CHECK_CAMERAPARAM);
			KillTimer(EventType_TIMER_EVENT_Runnin_Stream);
		}
		else{

			KillTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM);
			SetTimer(enumWawajiEventType::EventType_TIMER_EVENT_CHECK_CAMERAPARAM, 1000, nullptr);
		}
	}
}

inline void CAgoraWawajiUIDlg::checkCameraInfo()
{
	if (nullptr == m_DlgConfig.m_hWnd || !m_DlgConfig.IsWindowVisible()){

		//Check CameraInfo for joinChannel. //Running by-Slef
		//GetCameraInfo
		//m_lpAgoraObject->EnableVideo(TRUE);
		CAgoraCameraManager agoraCameraManager;
		agoraCameraManager.Create(m_lpRtcEngine);
		int nInstanceMax = agoraCameraManager.GetDeviceCount();
		for (int nIndex = 1; nInstanceMax >= nIndex && gMaxCameraCount >= nIndex; nIndex++){

			char szbuf[128] = { '\0' };
			sprintf_s(szbuf, "Instance%d", nIndex);
			uid_t uRemoteUid = str2int(gAgoraConfigMainUI.getLoginUid(szbuf));
			BOOL bRes = str2int(gAgoraConfigMainUI.getProcessEnable(szbuf));
			if (bRes){
				//兼容配置项中的项数目比实际摄像头数目多的情况
				LPAG_WAWAJI_STREAMINFO lpData = new AG_WAWAJI_STREAMINFO;
				lpData->bIsRunning = FALSE;
				lpData->uRemoteUid = uRemoteUid;
				lpData->dProcessId = -1;
				lpData->InstanceType = (eTagConfigType)nIndex;
				lpData->wnd = (nIndex == 1 ? m_CtlCamera1 : m_CtlCamera2);
				m_mapStream[szbuf] = lpData;

				m_mapUidMgr[uRemoteUid] = szbuf;
			}
		}

		//Running WawajiStream.
		KillTimer(EventType_TIMER_EVENT_CHECK_CAMERAPARAM);

		if (m_mapStream.size()){

			StartWawajiMonitor();
			SetTimer(EventType_TIMER_EVENT_Runnin_Stream, 2000, nullptr);
		}
		else{

			CAgoraFormatStr::AgoraMessageBox(_T("Wawaji直播程序 没有检测到 有效的摄像头实例.\r\n 请点击【配置/Settings】按钮 检查是否有摄像头,或摄像头配置是否正确."));
		}
	}
}

inline void CAgoraWawajiUIDlg::StartWawajiMonitor()
{
	if (m_lpAgoraObject){

		CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
		m_lpAgoraObject->EnableLastmileTest(FALSE);

		//m_uMonitorUId = str2int(getRandomUid());
		m_uMonitorUId = 20;
		m_lpAgoraObject->EnableVideo(FALSE);
		m_lpAgoraObject->EnableAudio(FALSE);

		m_lpAgoraObject->SetClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_AUDIENCE);
		m_lpAgoraObject->SetChannelProfile(TRUE);

		m_lpAgoraObject->MuteAllRemoteAudio(TRUE);
		m_lpAgoraObject->MuteAllRemoteVideo(TRUE);

		m_lpAgoraObject->LocalVideoPreview(NULL, TRUE);

		if (m_strAppcertId.length()){

			CStringA strAppCertificateId = m_lpAgoraObject->getDynamicMediaChannelKey(s2cs(m_strChannel));
			m_lpAgoraObject->JoinChannel(s2cs(m_strChannel), m_uMonitorUId, strAppCertificateId);
		}
		else{

			m_lpAgoraObject->JoinChannel(s2cs(m_strChannel), m_uMonitorUId);
		}
	}
}

inline void CAgoraWawajiUIDlg::StopWawajiMonitor()
{
	if (m_lpAgoraObject){

		CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
		m_lpAgoraObject->LeaveCahnnel();
		m_lpAgoraObject->LocalVideoPreview(NULL, FALSE);
	}
}

inline void CAgoraWawajiUIDlg::StartRunWawajiStream()
{
	CAgoraFormatStr::AgoraWriteLog("StartRunWawajiStream");
	std::vector<DWORD> vecProcess;
	vecProcess = getProcessMutilVec(KWawajiStream);
	int processNum = vecProcess.size();
	std::map<std::string, LPAG_WAWAJI_STREAMINFO>::iterator it = m_mapStream.begin();
	for (; m_mapStream.end() != it; it++){

		std::vector<DWORD>::iterator itt = find(vecProcess.begin(), vecProcess.end(), it->second->dProcessId);
		if (vecProcess.end() == itt){
			it->second->bIsRunning = FALSE;//有可能人为关闭/crash/
			it->second->dProcessId = -1;
			break;
		}
	}

	if (m_mapStream.end() != it){

		char szbuf[512] = { '\0' };
		BOOL bEnableLocalPreview = str2int(gAgoraConfigMainUI.getVideoPreview());
		if (bEnableLocalPreview)
			sprintf_s(szbuf, "%s %s %x %x", m_strAgoraWawajiMainUILogPath.data(), it->first.data(),m_hWnd, it->second->wnd);
		else
			sprintf_s(szbuf, "%s %s %x %x", m_strAgoraWawajiMainUILogPath.data(), it->first.data(), m_hWnd, NULL);
		CAgoraFormatStr::AgoraWriteLog((char*)std::string(szbuf).data());
		CAgoraFormatStr::AgoraOutDebugStr(s2cs(szbuf));
		DWORD processId = openProcess(KWawajiStream, szbuf);
		it->second->bIsRunning = TRUE;
		it->second->dProcessId = processId;
	}
}

inline void CAgoraWawajiUIDlg::reserveStream(const std::string &Instance)
{
	CAgoraFormatStr::AgoraWriteLog("reserveStream %s", Instance.data());
	KillTimer(EventType_TIMER_EVENT_Runnin_Stream);

	std::map<std::string, LPAG_WAWAJI_STREAMINFO>::iterator it = m_mapStream.find(Instance);
	assert(m_mapStream.end() != it);
	assert(it->second->dProcessId > 0);
	BOOL bRes = closeProcess(it->second->dProcessId);

	SetTimer(EventType_TIMER_EVENT_Runnin_Stream,2000,nullptr);
}

void CAgoraWawajiUIDlg::getInvalidFileList(std::vector<CString> &vecFileList, const CString &strFilePath, int IntervalTime)
{
	DWORD dwAttr = GetFileAttributes(strFilePath);
	if (INVALID_FILE_ATTRIBUTES == dwAttr){
		return;
	}

	CFileFind findHandle;
	CString strDestDir = strFilePath + _T("*.*");
	bool isNotEmpty = findHandle.FindFile(strDestDir);
	while (isNotEmpty){

		isNotEmpty = findHandle.FindNextFileW();
		CString fileName = findHandle.GetFileName();
		if (!findHandle.IsDirectory() && !findHandle.IsDots()){
			CTime timeLastWrite;
			if (findHandle.GetLastWriteTime(timeLastWrite)){

				CTime timeNow = CTime::GetCurrentTime();
				CTimeSpan  timeTemp = timeNow - timeLastWrite;
				if (timeTemp.GetDays() >= IntervalTime){
					vecFileList.push_back(strFilePath + fileName);
				}
			}
		}
		else if (L"." != fileName && L".." != fileName){

			getInvalidFileList(vecFileList, strFilePath + (fileName + _T("\\")), IntervalTime);
		}
	}
}

void CAgoraWawajiUIDlg::OnClose()
{
	KillTimer(EventType_TIMER_EVENT_CLEARLOG);
	KillTimer(EventType_TIMER_EVENT_Runnin_Stream);
	KillTimer(EventType_TIMER_EVENT_UpTime);
	KillTimer(enumWawajiEventType::EventType_TIMER_EVENT_CHECK_CAMERAPARAM);
	KillTimer(enumWawajiEventType::EventType_TIMER_EVENT_CHECK_BASEINFOPARAM);

	int nNum = 0;
	closeProcess(KWawajiStream, nNum);

	if (m_lpAgoraObject){

		m_lpAgoraObject->LeaveCahnnel();
	}
	if (m_lpRtcEngine){

		m_lpRtcEngine->stopPreview();
	}

	uninitAgoaMeida();
	unInitCtrl();

	CDialogEx::OnCancel();
}

LRESULT CAgoraWawajiUIDlg::OnConfigParamSave(WPARAM wParam, LPARAM lParam)
{
	LPAG_WAWAJI_CONFIG lpData = (LPAG_WAWAJI_CONFIG)wParam;
	if (lpData){
		if (lpData->isRunStream){
			
			StopWawajiMonitor();
			SetTimer(EventType_TIMER_EVENT_CHECK_BASEINFOPARAM, 1000, NULL);
		}
		else{
			//信息通知.
			if (eTagConfigType::eTagConfigType_BaseInfo == lpData->configInstance){
				//更新基础信息对应的指定模块

				InitCtrlTxt();
			}
			else if (eTagConfigType::eTagConfigType_BaseInfo < lpData->configInstance){
				//更新摄像头的对应模块
				char szSection[16] = { '\0' };
				sprintf_s(szSection, "Instance%d", lpData->configInstance);

				switch (lpData->configInstance){
				case eTagConfigType::eTagConfigType_Instance1:{

					BOOL bRes = str2int(gAgoraConfigMainUI.getProcessEnable(szSection));
					m_CtlUID1Value.ShowWindow(bRes);
					m_CtlCamera1Vaule.ShowWindow(bRes);

					std::string strLoginUid1 = gAgoraConfigMainUI.getLoginUid(szSection);
					std::string strCameraName1 = gAgoraConfigMainUI.getCameraName(szSection);
					m_CtlUID1Value.SetWindowTextW(s2cs(strLoginUid1));
					m_CtlCamera1Vaule.SetWindowTextW(s2cs(strCameraName1));
				}
															  break;
				case eTagConfigType::eTagConfigType_Instance2:{

					BOOL bRes = str2int(gAgoraConfigMainUI.getProcessEnable(szSection));
					m_CtlUID2Value.ShowWindow(bRes);
					m_CtlCamera2Value.ShowWindow(bRes);

					std::string strLoginUid2 = gAgoraConfigMainUI.getLoginUid(szSection);
					std::string strCameraName2 = gAgoraConfigMainUI.getCameraName(szSection);
					m_CtlUID2Value.SetWindowTextW(s2cs(strLoginUid2));
					m_CtlCamera2Value.SetWindowTextW(s2cs(strCameraName2));
				}
															  break;
				default:break;
				}
			}
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnInstanceRemoteVideoStats(WPARAM wParam, LPARAM lParam)
{
	LPAG_WAWAJI_LOCALVIDEO_STATS lpData = (LPAG_WAWAJI_LOCALVIDEO_STATS)wParam;
	if (lpData){
		
		CAgoraFormatStr::AgoraWriteLog("RemoteVideoStats SendBitrate 0 uid: %u", lpData->uRemoteInstanceUID);

		uid_t uRemoteUID = lpData->uRemoteInstanceUID;
		std::map<uid_t,std::string>::iterator it = m_mapUidMgr.find(uRemoteUID);
		if (m_mapUidMgr.end() != it){
			assert(lpData->strInstance == it->second);

			//reserveStream(it->second);
			AddTxt(_T("RemoteVideoStats: uid: %u,%s"), lpData->uRemoteInstanceUID, s2cs(lpData->strInstance));
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

BOOL CAgoraWawajiUIDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (pCopyDataStruct){

		if (pCopyDataStruct->lpData){

			LPAG_WAWAJI_LOCALVIDEO_STATS lpData = (LPAG_WAWAJI_LOCALVIDEO_STATS)pCopyDataStruct->lpData;
			CAgoraFormatStr::AgoraWriteLog("RemoteVideoStats SendBitrate 0 uid: %u", lpData->uRemoteInstanceUID);

			uid_t uRemoteUID = lpData->uRemoteInstanceUID;
			std::map<uid_t, std::string>::iterator it = m_mapUidMgr.find(uRemoteUID);
			if (m_mapUidMgr.end() != it){
				assert(lpData->strInstance == it->second);

				AddTxt(_T("[%s] Uid: %u 推流停止."), s2cs(lpData->strInstance),lpData->uRemoteInstanceUID);
				reserveStream(it->second);
			}
		}
	}
	
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

LRESULT CAgoraWawajiUIDlg::OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;
	if (lpData){

		m_bIsJoinChannel = TRUE;
		m_BtnStart.SetWindowTextW(gStrStart);
		assert(m_uMonitorUId == lpData->uid);
		AddTxt(_T("[Monitor] 监控程序正常启动.."));
		CAgoraFormatStr::AgoraWriteLog("uid: %u joinchannelSuccess", m_uMonitorUId);
		delete lpData; lpData = NULL;

		m_ltimeInterval = 0;
		m_CtlUpTimeValue.SetWindowTextW(_T("00:00:00"));
		SetTimer(EventType_TIMER_EVENT_UpTime, 1000, NULL);
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnRejoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_REJOINCHANNEL_SUCCESS lpData = (LPAGE_REJOINCHANNEL_SUCCESS)wParam;
	if (lpData){

		AddTxt(_T("[Monitor] 监控程序重新启动..."));
		CAgoraFormatStr::AgoraWriteLog("Uid: %u Channel: %s RejoinChannelSuccess",lpData->uid,lpData->channel);
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnWarning(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnError(WPARAM wParam, LPARAM lParam)
{
	LPAGE_ERROR lpData = (LPAGE_ERROR)wParam;
	if (lpData){
		AddTxt(_T("[Monitor] Error Code: %d, msg: %s"), lpData->err, s2cs(lpData->msg));
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnAudioQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_QUALITY lpData = (LPAGE_AUDIO_QUALITY)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnAudioVolumeIndication(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_VOLUME_INDICATION lpData = (LPAGE_AUDIO_VOLUME_INDICATION)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LEAVE_CHANNEL lpData = (LPAGE_LEAVE_CHANNEL)wParam;
	if (lpData){

		m_ltimeInterval = 0;
		m_CtlUpTimeValue.SetWindowTextW(_T("00:00:00"));
		KillTimer(EventType_TIMER_EVENT_UpTime);

		m_bIsJoinChannel = FALSE;
		gStrStart = gEnumLangType == eLanguage_CHZ ? L"重启中..." : L"Restartting....";
		m_BtnStart.SetWindowTextW(gStrStart);
		AddTxt(_T("[Monitor] 监控程序退出."));
		CAgoraFormatStr::AgoraWriteLog("LeaveChannel uid: %u", lpData->rtcStat.users);
		delete lpData; lpData = nullptr;
	}
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnRtcStats(WPARAM wParam, LPARAM lParam)
{
	
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnMediaEngineEvent(WPARAM wParam, LPARAM lParam)
{
	LPAGE_MEDIA_ENGINE_EVENT lpData = (LPAGE_MEDIA_ENGINE_EVENT)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnAudioDeviceStateChanged(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_DEVICE_STATE_CHANGED lpData = (LPAGE_AUDIO_DEVICE_STATE_CHANGED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnLastmileQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LASTMILE_QUALITY lpData = (LPAGE_LASTMILE_QUALITY)wParam;

	if (lpData && m_nLastmileQuality != lpData->quality){

		m_nLastmileQuality = lpData->quality;
		CAgoraFormatStr::AgoraOutDebugStr(_T("nLastmileQuality: %d\n"), m_nLastmileQuality);
		Invalidate(TRUE);
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnVideoDeviceStateChanged(WPARAM wParam, LPARAM lParam)
{
	LPAGE_VIDEO_DEVICE_STATE_CHANGED lpData = (LPAGE_VIDEO_DEVICE_STATE_CHANGED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnFirstLocalVideoFrame(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_LOCAL_VIDEO_FRAME lpData = (LPAGE_FIRST_LOCAL_VIDEO_FRAME)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnFirstRemoteVideoDecoded(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = (LPAGE_FIRST_REMOTE_VIDEO_DECODED)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnFirstRemoteVideoFrame(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_FRAME lpData = (LPAGE_FIRST_REMOTE_VIDEO_FRAME)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}
	
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnUserJoined(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_JOINED lpData = (LPAGE_USER_JOINED)wParam;
	if (lpData){

		std::map<uid_t, std::string>::iterator it = m_mapUidMgr.find(lpData->uid);
		if (m_mapUidMgr.end() == it){

			AddTxt(_T("[Monitor] Other UserJoin UID : %u"), lpData->uid);
		}
		else{

			AddTxt(_T("[Monitor] %s UserJoin UID : %u"), s2cs(it->second),lpData->uid);
		}
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnUserOffline(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_OFFLINE lpData = (LPAGE_USER_OFFLINE)wParam;
	if (lpData){

		std::map<uid_t, std::string>::iterator it = m_mapUidMgr.find(lpData->uid);
		if (m_mapUidMgr.end() == it){

			AddTxt(_T("[Monitor] Other UserOffline UID: %u"), lpData->uid);
		}
		else{

			CAgoraFormatStr::AgoraWriteLog("UserOffline UID: %u", lpData->uid);
			AddTxt(_T("[Monitor] %s UserOffline UID : %u"), s2cs(it->second), lpData->uid);
			//reserve stream
			reserveStream(it->second);
		}
		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnUserMuteAudio(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_AUDIO lpData = (LPAGE_USER_MUTE_AUDIO)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnUserMuteVideo(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_VIDEO lpData = (LPAGE_USER_MUTE_VIDEO)wParam;
	if (lpData){
		
		std::map<uid_t, std::string>::iterator it = m_mapUidMgr.find(lpData->uid);
		if (m_mapUidMgr.end() != it){
			
			if (lpData->muted){

				AddTxt(_T("[Monitor] %s UID: %u 开始直播推流"), s2cs(it->second).GetBuffer(), lpData->uid);
				Invalidate(TRUE);
			}
			else{

				CAgoraFormatStr::AgoraWriteLog("UserMuteVideo UID :%u,%d", lpData->uid, lpData->muted);
				AddTxt(_T("[Monitor] %s UID: %u 停止直播推流",s2cs(it->second).GetBuffer(),lpData->uid));
				//reserve livestream
				reserveStream(it->second);
			}
		}
		else{
			
			AddTxt(_T("[Monitor] OtherUser %u 加入该房间 推流 "), lpData->uid);
		}

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnApiCallExecuted(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnLocalVideoStats(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LOCAL_VIDEO_STAT lpData = (LPAGE_LOCAL_VIDEO_STAT)wParam;
	if (lpData){


		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnRemoteVideoStats(WPARAM wParam, LPARAM lParam)
{
	LPAGE_REMOTE_VIDEO_STAT lpData = (LPAGE_REMOTE_VIDEO_STAT)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnCameraReady(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnVideoStopped(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnConnectionLost(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnConnectionInterrupted(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnUserEnableVideo(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_MUTE_VIDEO lpData = (LPAGE_USER_MUTE_VIDEO)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnStartRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnStopRecordingService(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraWawajiUIDlg::OnRefreshRecordingServiceStatus(WPARAM wParam, LPARAM lParam)
{
	LPAGE_RCDSRV_STATUS lpData = (LPAGE_RCDSRV_STATUS)wParam;
	if (lpData){

		delete lpData; lpData = nullptr;
	}

	return TRUE;
}
