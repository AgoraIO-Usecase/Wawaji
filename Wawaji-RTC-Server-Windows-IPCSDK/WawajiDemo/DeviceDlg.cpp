// DeviceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiDemo.h"
#include "DeviceDlg.h"
#include "afxdialogex.h"
#include "commonFun.h"


// CDeviceDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceDlg, CDialogEx)

CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeviceDlg::IDD, pParent)
{
}

CDeviceDlg::~CDeviceDlg()
{
}

void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLKAIN_DEVICE, m_slkAudInTest);
	DDX_Control(pDX, IDC_SLKAOUT_DEVICE, m_slkAudOutTest);
	DDX_Control(pDX, IDC_SLKCAM_DEVICE, m_slkCamTest);

	DDX_Control(pDX, IDC_BTNCANCEL_DEVICE, m_btnCancel);
	DDX_Control(pDX, IDC_BTNCONFIRM_DEVICE, m_btnConfirm);
	DDX_Control(pDX, IDC_BTNAPPLY_DEVICE, m_btnApply);

	//    DDX_Control(pDX, IDC_CMBAIN_DEVICE, m_cbxAIn);
	//    DDX_Control(pDX, IDC_CMBAOUT_DEVICE, m_cbxAOut);
	//    DDX_Control(pDX, IDC_CMBCAM_DEVICE, m_cbxCam);

	DDX_Control(pDX, IDC_SLDAIN_DEVICE, m_sldAInVol);
	DDX_Control(pDX, IDC_SLDAOUT_DEVICE, m_sldAOutVol);
	DDX_Control(pDX, IDC_CHECK_ExternalVideo, m_ckExternalVideo);
	DDX_Control(pDX, IDC_EDIT_ExVideoWidth, m_ctlExVideoWdith);
	DDX_Control(pDX, IDC_EDIT_ExVideoHeight, m_ctlExVideoHeight);
	DDX_Control(pDX, IDC_EDIT_IP, m_ctrlIPCIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_ctlIPCPort);
	DDX_Control(pDX, IDC_EDIT_USER,m_ctlIPCUser);
	DDX_Control(pDX, IDC_EDIT_PSW, m_ctlIPCPsw);
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	
	ON_STN_CLICKED(IDC_SLKAIN_DEVICE, &CDeviceDlg::OnStnClickedSlkainDevice)
	ON_STN_CLICKED(IDC_SLKAOUT_DEVICE, &CDeviceDlg::OnStnClickedSlkaoutDevice)
	ON_STN_CLICKED(IDC_SLKCAM_DEVICE, &CDeviceDlg::OnStnClickedSlkcamDevice)

	ON_BN_CLICKED(IDC_BTNCANCEL_DEVICE, &CDeviceDlg::OnBnClickedBtncancelDevice)
	ON_BN_CLICKED(IDC_BTNCONFIRM_DEVICE, &CDeviceDlg::OnBnClickedBtnconfirmDevice)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_VOLUME_INDICATION), &CDeviceDlg::OnEIDAudioVolumeIndication)

	ON_BN_CLICKED(IDC_BTNAPPLY_DEVICE, &CDeviceDlg::OnBnClickedBtnapplyDevice)
END_MESSAGE_MAP()


// CDeviceDlg 消息处理程序
void CDeviceDlg::OnPaint()
{
	CPaintDC dc(this);

	DrawClient(&dc);
}

BOOL CDeviceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lpRtcEngine = CAgoraObject::GetEngine();

	m_ftLink.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftDes.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftBtn.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_wndVideoTest.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 40), this, IDC_VIDEOTEST_DEVICE);
	m_wndVideoTest.SetVolRange(100);

	m_cbxAIn.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 40), this, IDC_CMBAIN_DEVICE);
	m_cbxAOut.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 40), this, IDC_CMBAOUT_DEVICE);
	m_cbxCam.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 40), this, IDC_CMBCAM_DEVICE);
	m_penFrame.CreatePen(PS_SOLID, 1, RGB(0xD8, 0xD8, 0xD8));

	m_cbExIPCType.Create(WS_CHILD | WS_VISIBLE|WS_BORDER, CRect(0, 0, 300, 40), this, IDC_CMBIPCType_DEVICE);

	SetBackgroundColor(RGB(0xFF, 0xFF, 0xFF), TRUE);
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDeviceDlg::EnableDeviceTest(BOOL bEnable)
{
	m_slkAudInTest.EnableWindow(bEnable);
	m_slkAudOutTest.EnableWindow(bEnable);
	m_slkCamTest.EnableWindow(bEnable);
}

void CDeviceDlg::videoExternCapture(BOOL bEnable /*= ture*/, HWND wnd /*= nullptr*/)
{
	if (!m_ckExternalVideo.GetCheck()){
		return;
	}

	CString rtspURL;
	m_ctlExVideoWdith.GetWindowText(rtspURL);
	if (_T("") == rtspURL){
		printf("!!RTSPURL is Invalid...\n");
		return;
	}

	if (bEnable){

		//m_rtspEx.startRtsp(cs2s(rtspURL));
		m_HikVision.startPlay(wnd);
		CAgoraObject::GetAgoraObject()->EnableExtendVideoCapture(TRUE, &m_exCapVideoFrameObserver);
	}
	else{

		//m_rtspEx.stopRtsp();
		m_HikVision.stopPlay();
		CAgoraObject::GetAgoraObject()->EnableExtendVideoCapture(FALSE, nullptr);
	}
}

void CDeviceDlg::InitCtrls()
{
	CRect ClientRect;

	MoveWindow(0, 0, 512, 640, 1);
	CenterWindow();

	GetClientRect(&ClientRect);

	m_cbxAIn.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbxAIn.MoveWindow(160, 65, 215, 22, TRUE);
	
	m_cbxAOut.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbxAOut.MoveWindow(160, 120, 215, 22, TRUE);

	m_cbxCam.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbxCam.MoveWindow(160, 325, 215, 22, TRUE);

	m_sldAInVol.MoveWindow(155, 90, 285, 24, TRUE);
	m_sldAOutVol.MoveWindow(155, 150, 285, 24, TRUE);

	m_cbExIPCType.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbExIPCType.MoveWindow(135, 280, 120, 24, TRUE);
	m_cbExIPCType.AddString(_T("HIKVISION"));
	m_cbExIPCType.AddString(_T("DAHUA"));
	m_ckExternalVideo.SetCheck(TRUE);

	m_ckExternalVideo.SetFont(&m_ftDes);
	m_ckExternalVideo.MoveWindow(80, 280, 50, 24, true);
	m_ctlExVideoWdith.MoveWindow(260, 280, 50, 24, TRUE);
	m_ctlExVideoWdith.SetCaretPos(CPoint(12, 148));
	m_ctlExVideoWdith.ShowCaret();
	m_ctlExVideoWdith.SetTip(_T("1280"));
	m_ctlExVideoWdith.SetFocus();
	
	m_ctlExVideoHeight.MoveWindow(320, 280, 50, 24, TRUE);
	m_ctlExVideoHeight.SetCaretPos(CPoint(12, 148));
	m_ctlExVideoHeight.ShowCaret();
	m_ctlExVideoHeight.SetTip(_T("720"));
	m_ctlExVideoHeight.SetFocus();

	m_ctrlIPCIP.SetTip(_T("192.168.1.201"));
	m_ctrlIPCIP.SetFocus();
	m_ctlIPCPort.SetTip(_T("8000"));
	m_ctlIPCPort.SetFocus();
	m_ctlIPCUser.SetTip(_T("admin"));
	m_ctlIPCUser.SetFocus();
	m_ctlIPCPsw.SetTip(_T("a1234567"));
	m_ctlIPCPsw.SetFocus();

	m_wndVideoTest.MoveWindow(155, 378, 192, 120, TRUE);

	m_slkAudInTest.SetFont(&m_ftLink);
	m_slkAudInTest.MoveWindow(405, 65, 72, 40, TRUE);
	m_slkAudOutTest.SetFont(&m_ftLink);
	m_slkAudOutTest.MoveWindow(405, 120, 72, 40, TRUE);
	m_slkCamTest.SetFont(&m_ftLink);
	m_slkCamTest.MoveWindow(405, 325, 72, 40, TRUE);

	m_btnCancel.MoveWindow(46, ClientRect.Height() - 88, 120, 36, TRUE);

	m_btnConfirm.MoveWindow(199, ClientRect.Height() - 88, 120, 36, TRUE);
	
	m_btnApply.MoveWindow(346, ClientRect.Height() - 88, 120, 36, TRUE);
	
	m_cbxAIn.SetFont(&m_ftDes);
	m_cbxAOut.SetFont(&m_ftDes);
	m_cbxCam.SetFont(&m_ftDes);

	m_btnCancel.SetBackColor(RGB(0, 160, 239), RGB(0, 160, 239), RGB(0, 160, 239), RGB(192, 192, 192));
	m_btnCancel.SetFont(&m_ftBtn);
	m_btnCancel.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xC8, 0x64), RGB(0xFF, 0xC8, 0x64), RGB(0xCC, 0xCC, 0xCC));
	m_btnCancel.SetWindowText(LANG_STR("IDS_DEVICE_CANCEL"));

	m_btnConfirm.SetBackColor(RGB(248, 170, 31), RGB(248, 170, 31), RGB(248, 170, 31), RGB(0xCC, 0xCC, 0xCC));
	m_btnConfirm.SetFont(&m_ftBtn);
	m_btnConfirm.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xC8, 0x64), RGB(0xFF, 0xC8, 0x64), RGB(0xCC, 0xCC, 0xCC));
	m_btnConfirm.SetWindowText(LANG_STR("IDS_DEVICE_CONFIRM"));

	m_cbxAIn.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbxAOut.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbxCam.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbExIPCType.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbxAIn.SetFont(&m_ftDes);
	m_cbxAOut.SetFont(&m_ftDes);
	m_cbxCam.SetFont(&m_ftDes);
	m_cbExIPCType.SetFont(&m_ftDes);

	m_slkAudInTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	m_slkAudOutTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	m_slkCamTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));

	m_btnCancel.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnCancel.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnCancel.SetFont(&m_ftBtn);
	m_btnCancel.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnCancel.SetWindowText(LANG_STR("IDS_DEVICE_CANCEL"));

	m_btnConfirm.SetBackColor(RGB(0x00, 0xA0, 0xE9), RGB(0x05, 0x78, 0xAA), RGB(0x05, 0x78, 0xAA), RGB(0xE6, 0xE6, 0xE6));
	m_btnConfirm.SetFont(&m_ftBtn);
	m_btnConfirm.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xCC, 0xCC, 0xCC));
	m_btnConfirm.SetWindowText(LANG_STR("IDS_DEVICE_CONFIRM"));

	m_btnApply.SetBackColor(RGB(0x00, 0xA0, 0xE9), RGB(0x05, 0x78, 0xAA), RGB(0x05, 0x78, 0xAA), RGB(0xE6, 0xE6, 0xE6));
	m_btnApply.SetFont(&m_ftBtn);
	m_btnApply.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xCC, 0xCC, 0xCC));
	m_btnApply.SetWindowText(LANG_STR("IDS_DEVICE_APPLY"));

	m_sldAInVol.SetThumbBitmap(IDB_SLDTHUMB_NORMAL, IDB_SLDTHUMB_HOT, IDB_SLDTHUMB_HOT, RGB(0xFF, 0, 0xFF));
	m_sldAInVol.SetRange(0, 255);

	m_sldAOutVol.SetThumbBitmap(IDB_SLDTHUMB_NORMAL, IDB_SLDTHUMB_HOT, IDB_SLDTHUMB_HOT, RGB(0xFF, 0, 0xFF));
	m_sldAOutVol.SetRange(0, 255);
}

void CDeviceDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;

	GetClientRect(&rcClient);

	CFont *lpDefFont = lpDC->SelectObject(&m_ftDes);
	CPen *lpDefPen = lpDC->SelectObject(&m_penFrame);
	
	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	lpDC->SetTextColor(RGB(0xD8, 0xD8, 0xD8));

	rcText.SetRect(rcClient.Width() / 2 - 190, 60, rcClient.Width() / 2 + 130, 92);
	lpDC->RoundRect(&rcText, CPoint(32, 32));

	lpString = LANG_STR("IDS_DEVICE_AUDIOIN");
	lpDC->TextOut(80, 69, lpString, _tcslen(lpString));

	rcText.SetRect(rcClient.Width() / 2 - 190, 115, rcClient.Width() / 2 + 130, 147);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	lpString = LANG_STR("IDS_DEVICE_AUDIOOUT");
	lpDC->TextOut(80, 124, lpString, _tcslen(lpString));
	
	rcText.SetRect(rcClient.Width() / 2 - 190, 320, rcClient.Width() / 2 + 130, 352);
	lpDC->RoundRect(&rcText, CPoint(32, 32));
	lpString = LANG_STR("IDS_DEVICE_CAMERA");
	lpDC->TextOut(80, 329, lpString, _tcslen(lpString));

	lpString = LANG_STR("IDS_DEVICE_VOLUME");
	lpDC->SetTextColor(RGB(0x00, 0x00, 0x00));
	lpDC->TextOut(66, 95, lpString, _tcslen(lpString));
	lpDC->TextOut(66, 155, lpString, _tcslen(lpString));

	lpDC->SelectObject(lpDefPen);
	lpDC->SelectObject(lpDefFont);
}

void CDeviceDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	if (!bShow) {
		m_agPlayout.Close();
		m_agAudioin.Close();
		m_agCamera.Close();
		return;
	}

	CString strDeviceName;
	CString strDeviceID;
	CString strCurID;

	m_agPlayout.Create(m_lpRtcEngine);
	m_agAudioin.Create(m_lpRtcEngine);
	m_agCamera.Create(m_lpRtcEngine);

	m_sldAOutVol.SetPos(m_agPlayout.GetVolume());
	m_sldAInVol.SetPos(m_agAudioin.GetVolume());

	m_cbxAOut.ResetContent();
	strCurID = m_agPlayout.GetCurDeviceID();
	for (UINT nIndex = 0; nIndex < m_agPlayout.GetDeviceCount(); nIndex++){
		m_agPlayout.GetDevice(nIndex, strDeviceName, strDeviceID);
		m_cbxAOut.InsertString(nIndex, strDeviceName);

		if (strCurID == strDeviceID)
			m_cbxAOut.SetCurSel(nIndex);
	}

	m_cbxAIn.ResetContent();
	strCurID = m_agAudioin.GetCurDeviceID();
	for (UINT nIndex = 0; nIndex < m_agAudioin.GetDeviceCount(); nIndex++){
		m_agAudioin.GetDevice(nIndex, strDeviceName, strDeviceID);
		m_cbxAIn.InsertString(nIndex, strDeviceName);

		if (strCurID == strDeviceID)
			m_cbxAIn.SetCurSel(nIndex);
	}

	m_cbxCam.ResetContent();
	strCurID = m_agCamera.GetCurDeviceID();
	for (UINT nIndex = 0; nIndex < m_agCamera.GetDeviceCount(); nIndex++){
		m_agCamera.GetDevice(nIndex, strDeviceName, strDeviceID);
		m_cbxCam.InsertString(nIndex, strDeviceName);

		if (strCurID == strDeviceID)
			m_cbxCam.SetCurSel(nIndex);
	}
}


BOOL CDeviceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN){
		switch (pMsg->wParam){
		case VK_ESCAPE:
			OnBnClickedBtncancelDevice();
			return FALSE;
		case VK_RETURN:
			OnBnClickedBtnconfirmDevice();
			return FALSE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDeviceDlg::OnStnClickedSlkainDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_agAudioin.IsTesting()) {
		m_agAudioin.TestAudInputDevice(NULL, FALSE);
		m_slkAudInTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	}
	else {
		m_agAudioin.TestAudInputDevice(GetSafeHwnd(), TRUE);
		m_slkAudInTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTESTOFF"));
	}
}


void CDeviceDlg::OnStnClickedSlkaoutDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_agPlayout.IsTesting()) {
		m_agPlayout.TestPlaybackDevice(ID_TEST_AUDIO, FALSE);
		m_slkAudOutTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	}
	else {
		m_agPlayout.TestPlaybackDevice(ID_TEST_AUDIO, TRUE);
		m_slkAudOutTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTESTOFF"));
	}
}


void CDeviceDlg::OnStnClickedSlkcamDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_agCamera.IsTesting()) {
		m_agCamera.TestCameraDevice(NULL, FALSE);
		m_slkCamTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	}
	else {
		m_agCamera.TestCameraDevice(m_wndVideoTest.GetVideoSafeHwnd(), TRUE);
		m_slkCamTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTESTOFF"));
	}
}


void CDeviceDlg::OnBnClickedBtncancelDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	m_agAudioin.TestAudInputDevice(NULL, FALSE);
	m_slkAudInTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));

	m_agPlayout.TestPlaybackDevice(ID_TEST_AUDIO, FALSE);
	m_slkAudOutTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));

	m_agCamera.TestCameraDevice(NULL, FALSE);
	m_slkCamTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));

	CDialogEx::OnCancel();
}


void CDeviceDlg::OnBnClickedBtnconfirmDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	int		nCurSel = 0;
	CString strDeviceName;
	CString strDeviceID;

	m_agAudioin.SetVolume(m_sldAInVol.GetPos());
	m_agPlayout.SetVolume(m_sldAOutVol.GetPos());

	m_agAudioin.TestAudInputDevice(NULL, FALSE);
	m_slkAudInTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	nCurSel = m_cbxAIn.GetCurSel();
	if (nCurSel != -1) {
		m_agAudioin.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agAudioin.SetCurDevice(strDeviceID);
	}

	m_agPlayout.TestPlaybackDevice(ID_TEST_AUDIO, FALSE);
	m_slkAudOutTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	nCurSel = m_cbxAOut.GetCurSel();
	if (nCurSel != -1) {
		m_agPlayout.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agPlayout.SetCurDevice(strDeviceID);
	}

	m_agCamera.TestCameraDevice(NULL, FALSE);
	m_slkCamTest.SetWindowText(LANG_STR("IDS_DEVICE_BTNTEST"));
	nCurSel = m_cbxCam.GetCurSel();
	if (nCurSel != -1) {
		m_agCamera.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agCamera.SetCurDevice(strDeviceID);
	}

	if (m_ckExternalVideo.GetCheck()){

		CString param;
		m_ctrlIPCIP.GetWindowText(param);
		std::string ip = cs2s(param);
		m_ctlIPCPort.GetWindowText(param);
		std::string port = cs2s(param);
		m_ctlIPCUser.GetWindowText(param);
		std::string user = cs2s(param);
		m_ctlIPCPsw.GetWindowText(param);
		std::string psw = cs2s(param);

		m_HikVision.login(ip,port,user,psw);

		m_ctlExVideoWdith.GetWindowText(param);
		int width = str2int(cs2s(param));
		m_ctlExVideoHeight.GetWindowText(param);
		int height = str2int(cs2s(param));
		m_HikVision.setResolution(width, height);
	}

	CDialogEx::OnOK();
}

void CDeviceDlg::OnBnClickedBtnapplyDevice()
{
	// TODO:  在此添加控件通知处理程序代码
	int		nCurSel = 0;
	CString strDeviceName;
	CString strDeviceID;

	m_agAudioin.SetVolume(m_sldAInVol.GetPos());
	m_agPlayout.SetVolume(m_sldAOutVol.GetPos());

	nCurSel = m_cbxAIn.GetCurSel();
	if (nCurSel != -1) {
		m_agAudioin.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agAudioin.SetCurDevice(strDeviceID);
	}

	nCurSel = m_cbxAOut.GetCurSel();
	if (nCurSel != -1) {
		m_agPlayout.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agPlayout.SetCurDevice(strDeviceID);
	}

	nCurSel = m_cbxCam.GetCurSel();
	if (nCurSel != -1) {
		m_agCamera.GetDevice(nCurSel, strDeviceName, strDeviceID);
		m_agCamera.SetCurDevice(strDeviceID);
	}
}


LRESULT CDeviceDlg::OnEIDAudioVolumeIndication(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_VOLUME_INDICATION lpData = (LPAGE_AUDIO_VOLUME_INDICATION)wParam;
	m_wndVideoTest.SetCurVol(lpData->totalVolume);

	delete lpData;

	return 0;
}

void CDeviceDlg::OnDestroy()
{
	videoExternCapture(FALSE);
	m_HikVision.logout();

	return CDialogEx::OnDestroy();
}