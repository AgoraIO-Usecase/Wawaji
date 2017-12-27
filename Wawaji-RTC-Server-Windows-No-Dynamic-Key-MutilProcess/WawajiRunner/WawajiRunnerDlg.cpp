
// WawajiRunnerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WawajiRunner.h"
#include "WawajiRunnerDlg.h"
#include "afxdialogex.h"
#include "../WawajiDemo/commonFun.h"
#include "../WawajiDemo/FileIO.h"
#include "AgoraObject.h"
#include "DlgVideoPreview.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#define TIMER_IDEVENT_RESTARTTIMER 1
#define TIMER_IDEVENT_RECHECK 2
#define TIMER_IDEVENT_LOGCLEAR 3
#define TIMER_INTERVAL_RESTARTTIMER 1000
#define TIMER_INTERVAL_RECHECK 5000
#define TIMER_INTERVAL_LOGCLEAR 100000

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


// CWawajiRunnerDlg 对话框



CWawajiRunnerDlg::CWawajiRunnerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWawajiRunnerDlg::IDD, pParent),
	m_pAgoraObject(nullptr)
	, m_pRtcEngine(nullptr)
	, m_pDlgVideoPreview(nullptr)
	, m_pDlgCurVideoPreview(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWawajiRunnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_RESTART, m_DataTimeCtlRestart);
	DDX_Control(pDX, IDC_TREE_PROCESSID, m_TcrlProcessId);
}

BEGIN_MESSAGE_MAP(CWawajiRunnerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_RESTART, &CWawajiRunnerDlg::OnDtnDatetimechangeDatetimepickerRestart)
	ON_BN_CLICKED(IDC_CHECK_TIMER_RESTART, &CWawajiRunnerDlg::OnBnClickedCheckTimerRestart)
	ON_BN_CLICKED(IDC_CHECK_VideoPreview, &CWawajiRunnerDlg::OnBnClickedCheckVideopreview)
	ON_MESSAGE(WM_MSGID(EID_LASTMILE_QUALITY), &CWawajiRunnerDlg::onLastMileQuality)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_PROCESSID, &CWawajiRunnerDlg::OnNMDblclkTreeProcessid)
	ON_BN_CLICKED(IDC_BUTTON_SAVEALL, &CWawajiRunnerDlg::OnBnClickedButtonSaveall)
END_MESSAGE_MAP()


// CWawajiRunnerDlg 消息处理程序

BOOL CWawajiRunnerDlg::OnInitDialog()
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
	initCtrl();
	
	SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);
	SetTimer(TIMER_IDEVENT_LOGCLEAR, TIMER_INTERVAL_LOGCLEAR, nullptr);
	//WinExec("WawajiDemo.exe", SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWawajiRunnerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWawajiRunnerDlg::OnPaint()
{
	if (IsIconic())
	{
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

void CWawajiRunnerDlg::OnClose()
{
	uninitCtrl();
	KillTimer(TIMER_IDEVENT_LOGCLEAR);
	KillTimer(TIMER_IDEVENT_RECHECK);
	KillTimer(TIMER_IDEVENT_RESTARTTIMER);

	CDialogEx::OnCancel();
}

void CWawajiRunnerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_IDEVENT_RESTARTTIMER == nIDEvent)
	{
		bool res = ((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->GetCheck();
		if (res){
			SYSTEMTIME stTemp;
			GetLocalTime(&stTemp);
			if (stTemp.wHour == m_TimerRestart.wHour
				&& stTemp.wMinute == m_TimerRestart.wMinute
				&& stTemp.wSecond == m_TimerRestart.wSecond){

				KillTimer(TIMER_IDEVENT_RECHECK);
				int num = 0;
				closeProcess("WawajiDemo.exe", num);

				//AfxMessageBox(_T("定点重启程序"));
				SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);
			}
		}
	}

	if (TIMER_IDEVENT_RECHECK == nIDEvent)
	{
		std::string curExeName = "WawajiDemo.exe";
		std::vector<DWORD> vecProcess;
		vecProcess = getProcessMutilVec(curExeName);
		int processNum = vecProcess.size();
		std::string processFreeName;
		for (std::map<std::string, DWORD>::iterator it = m_mapProcessId.begin(); m_mapProcessId.end() != it; it++)
		{
			std::vector<DWORD>::iterator itt = find(vecProcess.begin(), vecProcess.end(), it->second);
			if (vecProcess.end() == itt){
				processFreeName = it->first;
				it->second = -1;
				break;
			}
		}

		if (m_mapProcessId.size() > processNum && "" != processFreeName){
			DWORD processId = openProcess("WawajiDemo.exe", processFreeName);
			if (0 < processId){

				m_mapProcessId[processFreeName] = processId;
				GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(s2cs(processFreeName + "已启动"));
			}
		}
	}

	if (TIMER_IDEVENT_LOGCLEAR == nIDEvent)
	{
		CString strEditParam;
		GetDlgItem(IDC_EDIT_CLEARLOG)->GetWindowTextW(strEditParam);
		if (_T("") == strEditParam){
			return;
		}

		int nIntervalTime = str2int(cs2s(strEditParam));
		std::vector<CString> vecFileList;
		std::string logPath = getAbsoluteDir() + "logger\\";
		getInvalidFileList(vecFileList, s2cs(logPath), nIntervalTime);

		for (std::vector<CString>::iterator it = vecFileList.begin(); vecFileList.end() != it; it++){
			if (DeleteFile(*it)){

				TRACE(_T("delete file %s\n"),(*it));
			}
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWawajiRunnerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWawajiRunnerDlg::initCtrl()
{
	m_appId = gWawajiConfig.getAppId();
	if ("" == m_appId){
		AfxMessageBox(_T("APPID 不能为空"));
		return;
	}
	else 
	{
		initAgora();
	}

	std::string channelName = gWawajiConfig.getChannelName();
	GetDlgItem(IDC_EDIT_ChannelName)->SetWindowText(s2cs(channelName));
	GetDlgItem(IDC_EDIT_APPID)->SetWindowText(s2cs(m_appId));
	GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(_T("正在启动.."));
	GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetFocus();

	registerStartUp();

	std::string restartTimer = gWawajiConfig.getRestartTimer();
	std::string restartTimerStatus = gWawajiConfig.getRestartTimerStatus();
	((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->SetCheck(str2int(restartTimerStatus));
	getTimerStartIni(m_TimerRestart, restartTimer);
	m_DataTimeCtlRestart.SetTime(m_TimerRestart);

	std::string strVideoPreview = gWawajiConfig.getVideoPreview();
	if ("" == strVideoPreview){

		strVideoPreview = "1";
		gWawajiConfig.setVideoPreview(strVideoPreview);
	}
	((CButton*)(GetDlgItem(IDC_CHECK_VideoPreview)))->SetCheck(str2int(strVideoPreview));

	if ("1" == restartTimerStatus)
	SetTimer(TIMER_IDEVENT_RESTARTTIMER, TIMER_INTERVAL_RESTARTTIMER, nullptr);
	
	int cameraCount = m_AgoraCameraManager.GetDeviceCount();
	ASSERT(cameraCount);
	if (nullptr == m_pDlgVideoPreview){
		m_processCount = cameraCount;
		m_pDlgVideoPreview = new CDlgVideoPreview[cameraCount];
	}
	CString strProcessId;
	HTREEITEM hItem, hSubItem;
	m_TcrlProcessId.SetTextColor(RGB(0, 0, 255));
	hItem = m_TcrlProcessId.InsertItem(_T("Wawaji"), TVI_ROOT);
	CWnd* parentWnd = GetDlgItem(IDC_STATIC_SHOWCHILD);
	for (int processId = 0; cameraCount > processId; processId++){

		m_pDlgVideoPreview[processId].Create(CDlgVideoPreview::IDD, parentWnd);
		strProcessId.Format(_T("Process%d"),processId);
		m_pDlgVideoPreview[processId].setChildInfo(strProcessId, &m_AgoraCameraManager);
		hSubItem = m_TcrlProcessId.InsertItem(strProcessId, hItem);
	}
	m_TcrlProcessId.Expand(hItem, TVE_EXPAND);
	m_pDlgVideoPreview[0].showChildWnd(true);
	m_pDlgCurVideoPreview = &m_pDlgVideoPreview[0];

	for (int i = 0; i < m_processCount; i++){
		std::string processName;
		processName.append("process");
		processName.append(int2str(i));
		if ("1" == gWawajiConfig.getProcessEnable(processName)){
			m_mapProcessId[processName] = -1;
		}
	}
}

void CWawajiRunnerDlg::getTimerStartIni(SYSTEMTIME &st,const std::string &timeStr)
{
	int nindexleft = timeStr.find(":");
	int nindexright = timeStr.rfind(":");
	DWORD dhour = str2int(timeStr.substr(0, nindexleft));
	DWORD dmin = str2int(timeStr.substr(nindexleft + 1, nindexright));
	DWORD dsec = str2int(timeStr.substr(nindexright + 1, timeStr.length() - 1));
	
	GetLocalTime(&st);
	st.wHour = dhour;
	st.wMinute = dmin;
	st.wSecond = dsec;
}

void CWawajiRunnerDlg::uninitCtrl()
{
	if (m_pDlgVideoPreview){
		delete[] m_pDlgVideoPreview;
		m_pDlgVideoPreview = nullptr;
	}
	m_pDlgCurVideoPreview = nullptr;

	uninitAgora();
}

void CWawajiRunnerDlg::initAgora()
{
	m_pAgoraObject = CAgoraObject::GetAgoraObject(s2cs(m_appId));
	ASSERT(m_pAgoraObject);
	m_pRtcEngine = m_pAgoraObject->GetEngine();
	ASSERT(m_pRtcEngine);

	m_pAgoraObject->EnableWebSdkInteroperability(TRUE);

	m_pAgoraObject->SetMsgHandlerWnd(m_hWnd);
	m_pAgoraObject->EnableVideo(TRUE);
	m_pAgoraObject->EnableLastmileTest(TRUE);

	m_AgoraCameraManager.Create(m_pRtcEngine);

	CString strVersion = m_pAgoraObject->GetSDKVersion();
	CString sVersiono;
	sVersiono.Format(_T("Wawaji SDK Version: %s"), strVersion);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(sVersiono);
}

void CWawajiRunnerDlg::uninitAgora()
{
	if (m_pRtcEngine){
		m_AgoraCameraManager.Close();
	}
	if (m_pAgoraObject){
		m_pAgoraObject->EnableLastmileTest(FALSE);
		m_pAgoraObject->SetMsgHandlerWnd(nullptr);
		m_pAgoraObject->EnableWebSdkInteroperability(FALSE);
		delete m_pAgoraObject;
		m_pAgoraObject = nullptr;
	}
}

void CWawajiRunnerDlg::getInvalidFileList(std::vector<CString> &vecFileList, const CString &strFilePath,int IntervalTime)
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

				CTime timeNow =CTime::GetCurrentTime();
				CTimeSpan  timeTemp = timeNow - timeLastWrite;
				if (timeTemp.GetDays() > IntervalTime){
					vecFileList.push_back(strFilePath + fileName);
				}
			}
		}
		else if(L"." != fileName && L".." != fileName){

			getInvalidFileList(vecFileList, strFilePath + (fileName + _T("\\")), IntervalTime);
		}
	}
}

void CWawajiRunnerDlg::OnDtnDatetimechangeDatetimepickerRestart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	
	bool isRestartTimer = ((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->GetCheck();
	if (isRestartTimer){

		m_TimerRestart = pDTChange->st;
		CString restartFormat;
		restartFormat.Format(_T("%02d:%02d:%02d"), pDTChange->st.wHour, pDTChange->st.wMinute, pDTChange->st.wSecond);
		gWawajiConfig.setRestartTimerStatus("1");
		gWawajiConfig.setRestartTimer(cs2s(restartFormat));
	}
}

void CWawajiRunnerDlg::OnBnClickedCheckTimerRestart()
{
	// TODO:  在此添加控件通知处理程序代码
	bool res = ((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->GetCheck();
	if (res)
	{
		m_DataTimeCtlRestart.GetTime(&m_TimerRestart);

		CString restartFormat;
		restartFormat.Format(_T("%02d:%02d:%02d"), m_TimerRestart.wHour, m_TimerRestart.wMinute, m_TimerRestart.wSecond);
		gWawajiConfig.setRestartTimerStatus("1");
		gWawajiConfig.setRestartTimer(cs2s(restartFormat));
	}

	gWawajiConfig.setRestartTimerStatus(int2str(res));
}


void CWawajiRunnerDlg::OnBnClickedCheckVideopreview()
{
	// TODO:  在此添加控件通知处理程序代码
	bool res = ((CButton*)(GetDlgItem(IDC_CHECK_VideoPreview)))->GetCheck();
	gWawajiConfig.setVideoPreview(int2str(res));
}

HRESULT CWawajiRunnerDlg::onLastMileQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LASTMILE_QUALITY lpData = (LPAGE_LASTMILE_QUALITY)wParam;
	int netQuality = lpData->quality;

	delete lpData; lpData = nullptr;
	if (m_pAgoraObject){
		m_pAgoraObject->EnableLastmileTest(FALSE);
	}

	if (netQuality == QUALITY_EXCELLENT ||
		QUALITY_GOOD == netQuality ||
		QUALITY_POOR == netQuality ||
		QUALITY_BAD == netQuality || 
		QUALITY_VBAD == netQuality){

		GetDlgItem(IDC_STATIC_NETWORK)->SetWindowText(_T("NetWork IS OK"));
	}
	else if(QUALITY_DOWN == netQuality){

		GetDlgItem(IDC_STATIC_NETWORK)->SetWindowText(_T("NetWork IS DOWN"));
	}

	return true;
}

void CWawajiRunnerDlg::OnNMDblclkTreeProcessid(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0; 

	HTREEITEM hItem = m_TcrlProcessId.GetSelectedItem();
	CString strText;
	strText = m_TcrlProcessId.GetItemText(hItem);
	int rKeyIndex = strText.ReverseFind(_T('r'));
	CString strProcessId = strText.Mid(strText.GetLength() - rKeyIndex,rKeyIndex);
	m_pDlgCurVideoPreview->showChildWnd(false);
	m_pDlgVideoPreview[str2int(cs2s(strProcessId))].showChildWnd(true);
	m_pDlgCurVideoPreview = &m_pDlgVideoPreview[str2int(cs2s(strProcessId))];
}

void CWawajiRunnerDlg::OnBnClickedButtonSaveall()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(TIMER_IDEVENT_RECHECK);
	int num = 0;
	closeProcess("WawajiDemo.exe", num);
	SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);

	CString sParam;
	GetDlgItem(IDC_EDIT_APPID)->GetWindowTextW(sParam);
	gWawajiConfig.setAppId(cs2s(sParam));
	GetDlgItem(IDC_EDIT_ChannelName)->GetWindowTextW(sParam);
	gWawajiConfig.setChannelName(cs2s(sParam));

	
	for (int i = 0; m_processCount > i; i++){
		m_pDlgVideoPreview[i].saveConfig();
	}

	KillTimer(TIMER_IDEVENT_RECHECK);
	m_mapProcessId.clear();
	for (int i = 0; i < m_processCount; i++){
		std::string processName;
		processName.append("process");
		processName.append(int2str(i));
		if ("1" == gWawajiConfig.getProcessEnable(processName)){
			m_mapProcessId[processName] = -1;
		}
	}
	SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);
}
