
// AgoraVideoCallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgoraWawajiDemo.h"
#include "AgoraWawajiDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CAgoraVideoCallDlg dialog



CAgoraWawajiDemoDlg::CAgoraWawajiDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CAgoraWawajiDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_nVideoProfile = 0;
	m_lpAgoraObject = NULL;
	m_lpRtcEngine = NULL;

	m_nLastmileQuality = 0;
}

void CAgoraWawajiDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNMIN, m_btnMin);
	DDX_Control(pDX, IDC_BTNCLOSE, m_btnClose);

	DDX_Control(pDX, IDC_LINKAGORA, m_linkAgora);
}

BEGIN_MESSAGE_MAP(CAgoraWawajiDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
    ON_MESSAGE(WM_GOBACK, &CAgoraWawajiDemoDlg::OnBackPage)
    ON_MESSAGE(WM_GONEXT, &CAgoraWawajiDemoDlg::OnNextPage)
    ON_MESSAGE(WM_JOINCHANNEL, &CAgoraWawajiDemoDlg::OnJoinChannel)
    ON_MESSAGE(WM_LEAVECHANNEL, &CAgoraWawajiDemoDlg::OnLeaveChannel)
	
    ON_BN_CLICKED(IDC_BTNMIN, &CAgoraWawajiDemoDlg::OnBnClickedBtnmin)
    ON_BN_CLICKED(IDC_BTNCLOSE, &CAgoraWawajiDemoDlg::OnBnClickedBtnclose)

	ON_MESSAGE(WM_MSGID(EID_LASTMILE_QUALITY), &CAgoraWawajiDemoDlg::OnEIDLastmileQuality)

    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAgoraVideoCallDlg message handlers
BOOL CAgoraWawajiDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN){
		switch (pMsg->wParam){
		case VK_ESCAPE:
		case VK_RETURN:
			return FALSE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CAgoraWawajiDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ftTitle.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftLink.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftVer.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	SetBackgroundImage(IDB_DLG_MAIN);
	InitCtrls();
	InitChildDialog();

	LONG lVer = CLIENT_GetSDKVersion();
	CString strVerTmp, strVer;
	strVerTmp.Format(_T("%ld"), lVer);
	strVer = strVerTmp.Left(1) + "." + strVerTmp.Right(strVerTmp.GetLength() - 1).Left(2) + "." + strVerTmp.Right(strVerTmp.GetLength() - 3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAgoraWawajiDemoDlg::InitCtrls()
{
	CRect ClientRect;
	CBitmap	bmpNetQuality;

	MoveWindow(0, 0, 720, 600, 1);
	GetClientRect(&ClientRect);

	bmpNetQuality.LoadBitmap(IDB_NETWORK_QUALITY);

	m_imgNetQuality.Create(32, 32, ILC_COLOR24 | ILC_MASK, 6, 1);
	m_imgNetQuality.Add(&bmpNetQuality, RGB(0xFF, 0, 0xFF));

	m_btnMin.MoveWindow(ClientRect.Width() - 46, 1, 22, 22, TRUE);
	m_btnClose.MoveWindow(ClientRect.Width() - 23, 1, 22, 22, TRUE);
	m_linkAgora.MoveWindow(ClientRect.Width() / 2 - 30, ClientRect.Height()-55, 80, 20, TRUE);

	m_btnMin.SetBackImage(IDB_BTNMIN, RGB(0xFF, 0, 0xFF));
	m_btnClose.SetBackImage(IDB_BTNCLOSE, RGB(0xFF, 0, 0xFF));

	m_linkAgora.SetFont(&m_ftLink);
	m_linkAgora.SetURL(_T("http://www.agora.io"));
	m_linkAgora.SetWindowText(LANG_STR("IDS_LOGO_AGORAWEB"));
	CMFCButton::EnableWindowsTheming(FALSE);
}

void CAgoraWawajiDemoDlg::InitChildDialog()
{
	CString str;

	m_dlgEnterChannel.Create(CEnterChannelDlg::IDD, this);
	m_dlgSetup.Create(CSetupDlg::IDD, this);
	m_dlgVideo.Create(CVideoDlg::IDD, this);

	m_dlgEnterChannel.MoveWindow(110, 70, 500, 450, TRUE);
	m_dlgSetup.MoveWindow(110, 70, 500, 450, TRUE);

	m_dlgEnterChannel.ShowWindow(SW_SHOW);
	m_lpCurDialog = &m_dlgEnterChannel;

//    m_dlgSetup.SetVideoSolution(15);
	m_dlgEnterChannel.SetVideoString(m_dlgSetup.GetVideoSolutionDes());
}

void CAgoraWawajiDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAgoraWawajiDemoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawClient(&dc);
//		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAgoraWawajiDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CAgoraWawajiDemoDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT lResult = CDialogEx::OnNcHitTest(point);
	if (lResult == HTCLIENT && ::GetAsyncKeyState(MK_LBUTTON) < 0)
			lResult = HTCAPTION;
		
	return lResult;
}

void CAgoraWawajiDemoDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;
	CFont* defFont = lpDC->SelectObject(&m_ftTitle);

	m_imgNetQuality.Draw(lpDC, m_nLastmileQuality, CPoint(16, 40), ILD_NORMAL);

	GetClientRect(&rcClient);
	lpDC->SetBkColor(RGB(0x00, 0x9E, 0xEB));
	lpDC->SetTextColor(RGB(0xFF, 0xFF, 0xFF));
	lpString = LANG_STR("IDS_TITLE");
	lpDC->TextOut(12, 3, lpString, _tcslen(lpString));
	
	lpDC->SelectObject(&m_ftVer);
	lpDC->SetTextColor(RGB(0x91, 0x96, 0xA0));
	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));

	CString strVer = CAgoraObject::GetSDKVersionEx();
	
	rcText.SetRect(0, rcClient.Height() - 30, rcClient.Width(), rcClient.Height() - 5);
	lpDC->DrawText(strVer, strVer.GetLength(), &rcText, DT_CENTER | DT_SINGLELINE);
	lpDC->SelectObject(defFont);
}

void CAgoraWawajiDemoDlg::OnBnClickedBtnmin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_MINIMIZE);
}


void CAgoraWawajiDemoDlg::OnBnClickedBtnclose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

LRESULT CAgoraWawajiDemoDlg::OnBackPage(WPARAM wParam, LPARAM lParam)
{
	if (m_lpCurDialog == &m_dlgSetup) {
		m_lpCurDialog->ShowWindow(SW_HIDE);
		m_lpCurDialog = &m_dlgEnterChannel;
	}

    m_nVideoProfile = m_dlgSetup.GetVideoSolution();
    m_dlgEnterChannel.SetVideoString(m_dlgSetup.GetVideoSolutionDes());

	m_lpCurDialog->ShowWindow(SW_SHOW);

	return 0;
}

LRESULT CAgoraWawajiDemoDlg::OnNextPage(WPARAM wParam, LPARAM lParam)
{
	m_lpCurDialog->ShowWindow(SW_HIDE);
	if (m_lpCurDialog == &m_dlgEnterChannel)
			m_lpCurDialog = &m_dlgSetup;

	m_lpCurDialog->ShowWindow(SW_SHOW);

	return 0;
}

LRESULT CAgoraWawajiDemoDlg::OnJoinChannel(WPARAM wParam, LPARAM lParam)
{	
	m_lpAgoraObject = CAgoraObject::GetAgoraObject();
	m_lpRtcEngine = CAgoraObject::GetEngine();
	m_lpAgoraObject->SetMsgHandlerWnd(m_dlgVideo.GetSafeHwnd());

	CString strChannelName = m_dlgEnterChannel.GetChannelName();

	m_dlgVideo.MoveWindow(0, 0, 960, 720, 1);
	m_dlgVideo.ShowWindow(SW_SHOW);
	m_dlgVideo.CenterWindow();

	//m_dlgEnterChannel.m_dlgDevice.videoExternCapture(TRUE, m_dlgVideo.GetLocalVideoWnd());

	VideoCanvas vc;

	vc.uid = 0;
	vc.view = m_dlgVideo.GetLocalVideoWnd();
	vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_FIT;

	m_lpAgoraObject->EnableLastmileTest(FALSE);
	m_lpAgoraObject->MuteAllRemoteAudio();
	m_lpAgoraObject->MuteAllRemoteVideo();

	m_dlgSetup.SetVideoProfile();
	m_dlgVideo.SetWindowText(strChannelName);
	m_lpRtcEngine->setupLocalVideo(vc);
	m_lpRtcEngine->startPreview();

	CStringA channelKey = m_lpAgoraObject->GetDynChannelKey(strChannelName, m_lpAgoraObject->GetAppID(), m_lpAgoraObject->GetAppCert());

	int uid = m_lpAgoraObject->GetSelfUID();

	//m_lpAgoraObject->JoinChannel(strChannelName,uid,channelKey);
	m_lpAgoraObject->JoinChannel(strChannelName, uid);

	return 0;
}

LRESULT CAgoraWawajiDemoDlg::OnLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	CAgoraObject	*lpAgoraObject = CAgoraObject::GetAgoraObject();

	lpAgoraObject->LeaveCahnnel();
    
	return 0;
}

LRESULT CAgoraWawajiDemoDlg::OnEIDLastmileQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_LASTMILE_QUALITY lpData = (LPAGE_LASTMILE_QUALITY)wParam;

	if (m_nLastmileQuality != lpData->quality) {
		m_nLastmileQuality = lpData->quality;
		InvalidateRect(CRect(16, 40, 48, 72), TRUE);
	}

	delete lpData;
	return 0;
}

void CAgoraWawajiDemoDlg::OnClose()
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CDialogEx::OnClose();
}
