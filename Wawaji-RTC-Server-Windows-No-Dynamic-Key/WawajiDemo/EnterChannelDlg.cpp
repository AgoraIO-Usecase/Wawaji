// EnterChannelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiDemo.h"
#include "EnterChannelDlg.h"
#include "afxdialogex.h"
#include "commonFun.h"
#include "InfoManager.h"

// CEnterChannelDlg 对话框

IMPLEMENT_DYNAMIC(CEnterChannelDlg, CDialogEx)

CEnterChannelDlg::CEnterChannelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnterChannelDlg::IDD, pParent)
{
    
}

CEnterChannelDlg::~CEnterChannelDlg()
{
}

void CEnterChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_APPID, m_ctrAppId);
	DDX_Control(pDX, IDC_EDCHNAME_CHANNEL, m_ctrChannel);
	DDX_Control(pDX, IDC_BTNTEST_CHANNEL, m_btnTest);
	DDX_Control(pDX, IDC_BTNJOIN_CHANNEL, m_btnJoin);
	DDX_Control(pDX, IDC_BTNSET_CHANNEL, m_btnSetup);
	DDX_Control(pDX, IDC_EDCHPSWD_CHANNEL, m_ctrPassword);
	DDX_Control(pDX, IDC_EDIT_UID, m_ctrUid);
	DDX_Control(pDX, IDC_EDIT_PUBLISH_WIDHT, m_edPublishWidth);
	DDX_Control(pDX, IDC_EDIT_PUBLISH_HEIGHT, m_edPublishHeight);
	DDX_Control(pDX, IDC_EDIT_PUBLISH_FPS, m_edPublishFps);
	DDX_Control(pDX, IDC_EDIT_PUBLISH_BITRATE, m_edPublishBitrate);
	DDX_Control(pDX, IDC_EDIT_PUBLISH_RTMPURL, m_edPublishRtmpUrl);
}


BEGIN_MESSAGE_MAP(CEnterChannelDlg, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNTEST_CHANNEL, &CEnterChannelDlg::OnBnClickedBtntestChannel)
	ON_BN_CLICKED(IDC_BTNJOIN_CHANNEL, &CEnterChannelDlg::OnBnClickedBtnjoinChannel)
	ON_BN_CLICKED(IDC_BTNSET_CHANNEL, &CEnterChannelDlg::OnBnClickedBtnsetChannel)
	ON_BN_CLICKED(IDC_CHECK_FRONT, &CEnterChannelDlg::OnBnClickedCheckFront)
	ON_BN_CLICKED(IDC_CHECK_BACK, &CEnterChannelDlg::OnBnClickedCheckBack)
	ON_CBN_SELCHANGE(IDC_CMBROLE_CHANNEL, &CEnterChannelDlg::OnCbnSelchangeCmbRole)

END_MESSAGE_MAP()


// CEnterChannelDlg 消息处理程序
BOOL CEnterChannelDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN){
		switch (pMsg->wParam){
		case VK_ESCAPE:
			return FALSE;
		case VK_RETURN:
			OnBnClickedBtnjoinChannel();
			return FALSE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CEnterChannelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ftHead.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftDesc.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftBtn.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_penFrame.CreatePen(PS_SOLID, 1, RGB(0xD8, 0xD8, 0xD8));

	m_dlgDevice.Create(CDeviceDlg::IDD, this);
	m_dlgDevice.EnableDeviceTest(TRUE);

	SetBackgroundColor(RGB(0xFF, 0xFF, 0xFF));
	InitCtrls();
	SetTimer(1, 1000, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CEnterChannelDlg::InitCtrls()
{
	CRect ClientRect;

	GetClientRect(&ClientRect);


	std::string appId = getInfoManager()->getConfig()->getAppId();
	std::string channelName = getInfoManager()->getConfig()->getChannelName();
	enumCameraType cameraType = getInfoManager()->getCameraType();
	std::string uid;
	if (Type_Front == cameraType){

		((CButton*)GetDlgItem(IDC_CHECK_FRONT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_BACK))->SetCheck(FALSE);
		 uid = getInfoManager()->getConfig()->getLoginUid(INI_DeviceInfoFront);
	}
	else if (Type_Back == cameraType){

		((CButton*)GetDlgItem(IDC_CHECK_FRONT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_BACK))->SetCheck(TRUE);
		uid = getInfoManager()->getConfig()->getLoginUid(INI_DeviceInfoBack);
	}

	m_ctrAppId.MoveWindow(160, 33, 240, 22, TRUE);
	m_ctrAppId.SetFont(&m_ftDesc);
	m_ctrAppId.SetCaretPos(CPoint(12, 148));
	m_ctrAppId.ShowCaret();
	m_ctrAppId.SetTip(s2cs(appId));
	//m_ctrAppId.SetTip(_T("f4637604af81440596a54254d53ade20"));
	m_ctrAppId.SetFocus();
	
	m_ctrChannel.MoveWindow(200, 82, 200, 22, TRUE);
    m_ctrChannel.SetFont(&m_ftDesc);
	m_ctrChannel.SetCaretPos(CPoint(12, 148));
	m_ctrChannel.ShowCaret();
	m_ctrChannel.SetTip(s2cs(channelName));
	//m_ctrChannel.SetTip(_T("wawaji_demo")); 
	m_ctrChannel.SetFocus();
    
//  m_ctrPassword.MoveWindow(90, 131, 120, 22, TRUE);
// 	m_ctrPassword.SetFont(&m_ftDesc);
// 	m_ctrPassword.SetTip(LANG_STR("IDS_CHN_ROOMPASSWORD"));
// 	m_ctrPassword.SetFocus();

	m_ctrUid.MoveWindow(120, 131, 90, 22, TRUE);
	m_ctrUid.SetFont(&m_ftDesc);
	//m_ctrUid.SetTip(_T("1"));
	m_ctrUid.SetTip(s2cs(uid));
	m_ctrUid.SetFocus();

	m_edPublishWidth.SetFont(&m_ftDesc);
	m_edPublishWidth.SetTip(_T("width"));
	m_edPublishWidth.SetFocus();

	m_edPublishHeight.SetFont(&m_ftDesc);
	m_edPublishHeight.SetTip(_T("height"));
	m_edPublishHeight.SetFocus();

	m_edPublishFps.SetFont(&m_ftDesc);
	m_edPublishFps.SetTip(_T("fps"));
	m_edPublishFps.SetFocus();

	m_edPublishBitrate.SetFont(&m_ftDesc);
	m_edPublishBitrate.SetTip(_T("bitrate"));
	m_edPublishBitrate.SetFocus();

	m_edPublishRtmpUrl.SetFont(&m_ftDesc);
	m_edPublishRtmpUrl.SetTip(_T("RtmpUrl"));
	m_edPublishRtmpUrl.SetFocus();

	GetDlgItem(IDC_CHECK_FRONT)->MoveWindow(160, 280, 80, 22, TRUE);
	GetDlgItem(IDC_CHECK_BACK)->MoveWindow(250, 280, 80, 22, TRUE);

	m_ctrRole.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE, CRect(ClientRect.Width() / 2 + 1, 168, 180, 32), this, IDC_CMBROLE_CHANNEL);
	m_ctrRole.MoveWindow(280, 127, 130, 22, TRUE);
	m_ctrRole.SetFont(&m_ftDesc);
	m_ctrRole.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_ctrRole.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_ctrRole.InsertString(0, LANG_STR("IDS_CHN_CASTER"));
	m_ctrRole.InsertString(1, LANG_STR("IDS_CHN_AUDIENCE"));
	m_ctrRole.SetCurSel(0);

	m_ctrRole.SetCurSel(0);
   
	m_btnJoin.MoveWindow(70, 310, 360, 36, TRUE);
	m_btnTest.MoveWindow(70, 355, 108, 36, TRUE);
	m_btnSetup.MoveWindow(190, 355, 240, 36, TRUE);

	m_btnJoin.SetBackColor(RGB(0x00, 0xA0, 0xE9), RGB(0x05, 0x78, 0xAA), RGB(0x05, 0x78, 0xAA), RGB(0xE6, 0xE6, 0xE6));
	m_btnJoin.SetFont(&m_ftBtn);
	m_btnJoin.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xCC, 0xCC, 0xCC));
	m_btnJoin.SetWindowText(LANG_STR("IDS_CHN_BTJOIN"));

	m_btnTest.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnTest.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnTest.SetFont(&m_ftBtn);
	m_btnTest.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnTest.SetWindowText(LANG_STR("IDS_CHN_BTTEST"));

	m_btnSetup.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnSetup.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnSetup.SetFont(&m_ftBtn);
	m_btnSetup.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnSetup.SetWindowText(_T("1920*1080,15fps, 3mbps"));

	CMFCButton::EnableWindowsTheming(FALSE);
}

void CEnterChannelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	DrawClient(&dc);
}

void CEnterChannelDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent){
		KillTimer(nIDEvent);
		OnBnClickedBtnjoinChannel();
	}
}

void CEnterChannelDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;

	GetClientRect(&rcClient);

    CFont* defFont = lpDC->SelectObject(&m_ftDesc);
	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	lpDC->SetTextColor(RGB(0x44, 0x45, 0x46));

	lpDC->SelectObject(&m_penFrame);
	rcText.SetRect(rcClient.Width() / 2 - 180, 25, rcClient.Width() / 2 + 170, 57);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	lpDC->TextOut(rcClient.Width() / 2 - 175 ,32, _T("APPID"));

	rcText.OffsetRect(0, 49);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	lpDC->TextOut(rcClient.Width() / 2 - 175, 81, _T("ChannelName"));

	rcText.OffsetRect(0, 49);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	lpDC->TextOutW(rcClient.Width() /2 -175,130,_T("UID"));

	lpString = LANG_STR("IDS_CHN_ROLETITLE");
	lpDC->SetTextColor(RGB(0xD8, 0xD8, 0xD8));
	lpDC->TextOut(220, 80, lpString, _tcslen(lpString));

	lpDC->SelectObject(defFont);

	// Done with the font.  Delete the font object.
	//	font.DeleteObject();
}

void CEnterChannelDlg::OnBnClickedBtntestChannel()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strAppId;
	m_ctrAppId.GetWindowText(strAppId);	
	if (strAppId.IsEmpty() || strAppId == _T("APPID"))
	{
		MessageBox(_T("前先填写APPID."), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	CAgoraObject* m_lpAgoraObject = CAgoraObject::GetAgoraObject(strAppId);
	m_lpAgoraObject->SetLogFilePath(NULL);
	m_lpAgoraObject->SetMsgHandlerWnd(GetSafeHwnd());
	CAgoraObject::GetEngine()->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_lpAgoraObject->EnableVideo(TRUE);
	m_lpAgoraObject->SetClientRole(CLIENT_ROLE_BROADCASTER);
	CAgoraObject::GetAgoraObject()->EnableLastmileTest(TRUE);

	m_dlgDevice.ShowWindow(SW_SHOW);
	m_dlgDevice.CenterWindow();
}


void CEnterChannelDlg::OnBnClickedBtnjoinChannel()
{
	// TODO:  在此添加控件通知处理程序代码
	CString     strKey;
    CString     strChannelName;
    CString     strInfo;
    CString     strOperation;
    BOOL        bFound = FALSE;
    BOOL        bSuccess = FALSE;
	
	CString strAppId;
	m_ctrAppId.GetWindowText(strAppId);
	if (strAppId.IsEmpty() || strAppId == _T("APPID"))
	{
		MessageBox(_T("前先填写APPID."), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	getInfoManager()->getConfig()->setAppId(cs2s(strAppId));
	CAgoraObject* m_lpAgoraObject = CAgoraObject::GetAgoraObject(strAppId);
	IRtcEngine *pRtcEngine = CAgoraObject::GetEngine();
	
	RtcEngineParameters rep(pRtcEngine);
	rep.enableWebSdkInteroperability(true);
 	m_lpAgoraObject->SetLogFilePath(s2cs(getInfoManager()->getSdkLogPath()));
	m_lpAgoraObject->SetMsgHandlerWnd(GetSafeHwnd());
	CAgoraObject::GetEngine()->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_lpAgoraObject->EnableVideo(TRUE);
	m_lpAgoraObject->SetClientRole(CLIENT_ROLE_BROADCASTER);

	CString param;
	m_ctrUid.GetWindowText(param);
	m_lpAgoraObject->SetSelfUID(str2int(cs2s(param)));
	getInfoManager()->getConfig()->setLoginUid(getCurSection(),cs2s(param));

	m_ctrChannel.GetWindowText(param);
	getInfoManager()->getConfig()->setChannelName(cs2s(param));
	
	bool res = ((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->GetCheck();
	if (res){
		getInfoManager()->setCameraType(Type_Front);
	}
	res = ((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->GetCheck();
	if (res){
		getInfoManager()->setCameraType(Type_Back);
	}

	if (!m_dlgDevice.DeviceInfoCheck()){
		OnBnClickedBtntestChannel();
		return;
	}

	AGE_PUBLISH_PARAM publishParam;
	m_edPublishWidth.GetWindowText(param);
	publishParam.width = str2int(cs2s(param));
	m_edPublishHeight.GetWindowText(param);
	publishParam.height = str2int(cs2s(param));
	m_edPublishFps.GetWindowText(param);
	publishParam.fps = str2int(cs2s(param));
	m_edPublishBitrate.GetWindowText(param);
	publishParam.bitrate = str2int(cs2s(param));
	m_edPublishRtmpUrl.GetWindowText(param);
	publishParam.rtmpUrl = cs2s(param);
	CAgoraObject::GetAgoraObject()->setPublishParam(publishParam);
	CAgoraObject::GetAgoraObject()->enablePublish(true);

	//m_lpAgoraObject->EnableLocalMirrorImage(FALSE);

	CAgoraObject::GetAgoraObject()->EnableLastmileTest(TRUE);
	
    m_ctrChannel.GetWindowText(strChannelName);
    m_ctrPassword.GetWindowText(strKey);

	GetParent()->SendMessage(WM_JOINCHANNEL, 0, 0);
}


void CEnterChannelDlg::OnBnClickedBtnsetChannel()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strAppId;
	m_ctrAppId.GetWindowText(strAppId);
	if (strAppId.IsEmpty() || strAppId == _T("APPID"))
	{
		MessageBox(_T("前先填写APPID."), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	CAgoraObject* m_lpAgoraObject  = CAgoraObject::GetAgoraObject(strAppId);
	m_lpAgoraObject->SetLogFilePath(NULL);
	m_lpAgoraObject->SetMsgHandlerWnd(GetSafeHwnd());
	CAgoraObject::GetEngine()->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_lpAgoraObject->EnableVideo(TRUE);
	m_lpAgoraObject->SetClientRole(CLIENT_ROLE_BROADCASTER);
	CAgoraObject::GetAgoraObject()->EnableLastmileTest(TRUE);

	GetParent()->SendMessage(WM_GONEXT, 0, 0);
}

void CEnterChannelDlg::OnCbnSelchangeCmbRole()
{
	int nSel = m_ctrRole.GetCurSel();

	if (nSel == 0)
		CAgoraObject::GetAgoraObject()->SetClientRole(CLIENT_ROLE_BROADCASTER);
	else
		CAgoraObject::GetAgoraObject()->SetClientRole(CLIENT_ROLE_AUDIENCE);
}

CString CEnterChannelDlg::GetChannelName()
{
	CString strChannelName;

	m_ctrChannel.GetWindowText(strChannelName);

	return strChannelName;
}

void CEnterChannelDlg::SetVideoString(LPCTSTR lpVideoString)
{
	m_btnSetup.SetWindowText(lpVideoString);
}

void CEnterChannelDlg::OnBnClickedCheckFront()
{
	// TODO:  在此添加控件通知处理程序代码
	bool res = ((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->GetCheck();
	((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->SetCheck(!res);
	
	if (res){
		if ("1" == getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoFront)){
			AfxMessageBox(_T("前置摄像头对应进程已经启动..."));
			((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->SetCheck(FALSE);
			((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->SetCheck(TRUE);
		}
	}
	else{
		if ("1" == getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoBack)){
			AfxMessageBox(_T("后置摄像头对应进程已经启动.."));
			((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->SetCheck(FALSE);
			((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->SetCheck(TRUE);
		}
	}	

	res = ((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->GetCheck();
	std::string loginUid = getInfoManager()->getConfig()->getLoginUid((res?INI_DeviceInfoFront:INI_DeviceInfoBack));
	m_ctrUid.SetWindowTextW(s2cs(loginUid));
}

void CEnterChannelDlg::OnBnClickedCheckBack()
{
	// TODO:  在此添加控件通知处理程序代码
	bool res = ((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->GetCheck();
	((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->SetCheck(!res);
	
	if (res){
		if ("1" == getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoBack)){
			AfxMessageBox(_T("后置摄像头对应进程已经启动..."));
			((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->SetCheck(TRUE);
			((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->SetCheck(FALSE);
		}
	}
	else{
		if ("1" == getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoBack)){
			AfxMessageBox(_T("前置摄像头对应进程已经启动.."));
			((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->SetCheck(FALSE);
			((CButton*)(GetDlgItem(IDC_CHECK_FRONT)))->SetCheck(TRUE);
		}
	}

	res = ((CButton*)(GetDlgItem(IDC_CHECK_BACK)))->GetCheck();
	std::string loginUid = getInfoManager()->getConfig()->getLoginUid((res?INI_DeviceInfoBack:INI_DeviceInfoFront));
	m_ctrUid.SetWindowTextW(s2cs(loginUid));
}
