// DlgCamera.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiUI.h"
#include "DlgCamera.h"
#include "afxdialogex.h"

// CDlgCamera 对话框

IMPLEMENT_DYNAMIC(CDlgCamera, CDialogEx)

CDlgCamera::CDlgCamera(CString strInstance,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCamera::IDD, pParent),
	m_InstanceDesc(strInstance),
	m_lpAgoraObject(nullptr),
	m_lpRtcEngine(nullptr)
{
	swscanf_s(strInstance.GetBuffer(), _T("Instance%d"), &m_nCurIndex);
}

CDlgCamera::~CDlgCamera()
{
	m_lpAgoraObject = nullptr;
	m_lpAgoraObject = nullptr;
}

void CDlgCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INSTANCEDESC,m_ctlInstance);
	DDX_Control(pDX, IDC_CHECK_IsValid, m_checkEnable);
	DDX_Control(pDX, IDC_COMBO_CameraName, m_comCameraName);
	DDX_Control(pDX, IDC_CHECK_SwitchWidthHeight, m_checkSwitchWidthHeight);
	DDX_Control(pDX, IDC_EDIT_RTMPWIDTH, m_editRtmpWidth);
	DDX_Control(pDX, IDC_EDIT_RTMPHEIGHT, m_editRtmpHeight);
	DDX_Control(pDX, IDC_EDIT_RTMPFPS, m_editRtmpFps);
	DDX_Control(pDX, IDC_EDIT_RTMPBitrate, m_editRtmpBitrate);
	DDX_Control(pDX, IDC_EDIT_RTMPUrl, m_editRtmpUrl);
	DDX_Control(pDX, IDC_STATIC_LocalCamera_Preview, m_ctlLocalVideoPreview);
	DDX_Control(pDX, IDC_CHECK_RTMPSave, m_checkRtmpSave);
	DDX_Control(pDX, IDC_CHECK_VerCamera, m_checkVerCamera);
	DDX_Control(pDX, IDC_CHECK_SwitchWidthHeight, m_checkSwitchWidthHeight);	
	DDX_Control(pDX, IDC_EDIT_UID, m_editLoginUID);
}


BEGIN_MESSAGE_MAP(CDlgCamera, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_Preview, &CDlgCamera::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_CHECK_VerCamera, &CDlgCamera::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK_SwitchWidthHeight, &CDlgCamera::OnBnClickedCheckSwitchwidthheight)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CDlgCamera::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CDlgCamera 消息处理程序
BOOL CDlgCamera::OnInitDialog()
{
	//TO DO
	UpdateData(FALSE);
	initData();
	ShowWindow(SW_HIDE);

	return CDialogEx::OnInitDialog();
}

inline void CDlgCamera::initCtrl()
{
	std::string strSection = cs2s(m_InstanceDesc);
	std::string strParam;
	strParam = gAgoraConfigMainUI.getProcessEnable(strSection);
	m_checkEnable.SetCheck(str2int(strParam));

	strParam = gAgoraConfigMainUI.getLoginUid(strSection);
	m_editLoginUID.SetWindowTextW(s2cs(strParam));

	strParam = gAgoraConfigMainUI.getCameraName(strSection);
	m_comCameraName.SetWindowTextW(s2cs(strParam));

	strParam = gAgoraConfigMainUI.getLeftRotate90(strSection);
	m_checkVerCamera.SetCheck(str2int(strParam));

	strParam = gAgoraConfigMainUI.getSwitchWHEnable(strSection);
	m_checkSwitchWidthHeight.SetCheck(str2int(strParam));

	strParam = gAgoraConfigMainUI.getRtmpSave(strSection);
	m_checkRtmpSave.SetCheck(str2int(strParam));
	
	//Encoder SendVideo Profile
	std::string strFormat =  (gAgoraConfigMainUI.getResolution()).data();
	int nWidth = 0,nHeight = 0,nFps = 0, nBitrate = 0;
	sscanf_s(strFormat.data(), ("%dx%d %dfps %dkbps"),&nWidth,&nHeight,&nFps,&nBitrate);
	gAgoraConfigMainUI.setResolutionWidth(strSection, int2str(nWidth));
	gAgoraConfigMainUI.setResolutionHeight(strSection, int2str(nHeight));
	gAgoraConfigMainUI.setResolutionFps(strSection, int2str(nFps));
	gAgoraConfigMainUI.setResolutionBitrate(strSection, int2str(nBitrate));

	//Rtmp SendVideo Profile
	strParam = gAgoraConfigMainUI.getRtmpWidth(strSection);
	strParam = ((("") ==strParam) ? int2str(nWidth) : strParam);
	m_editRtmpWidth.SetWindowTextW(s2cs(strParam));
	
	strParam = gAgoraConfigMainUI.getRtmpHeight(strSection);
	strParam = (("" == strParam) ? int2str(nHeight) : strParam);
	m_editRtmpHeight.SetWindowTextW(s2cs(strParam));

	strParam = gAgoraConfigMainUI.getRtmpFps(strSection);
	strParam = (("" == strParam ? int2str(nFps) : strParam));
	m_editRtmpFps.SetWindowTextW(s2cs(strParam));
	
	strParam = gAgoraConfigMainUI.getRtmpBitrate(strSection);
	strParam = (("" == strParam) ? int2str(nBitrate) : strParam);
	m_editRtmpBitrate.SetWindowTextW(s2cs(strParam));

	strParam = gAgoraConfigMainUI.getRtmpUrl(strSection);
	m_editRtmpUrl.SetWindowTextW(s2cs(strParam));
}

inline void CDlgCamera::uninitCtrl()
{

}

inline void CDlgCamera::initData()
{
	m_ctlInstance.SetWindowTextW(m_InstanceDesc);
	m_checkEnable.SetCheck(FALSE);

	m_lpAgoraObject = CAgoraObject::GetAgoraObject();
	m_lpRtcEngine = CAgoraObject::GetEngine();
	int nDefIndex = -1;
	CString strDefCameraName = s2cs(gAgoraConfigMainUI.getCameraName(cs2s(m_InstanceDesc)));
	if (m_lpAgoraObject && m_lpRtcEngine){

		BOOL bRes = m_AgoraCameraManager.Create(m_lpRtcEngine);
		if (bRes){
			int nCameraCount = m_AgoraCameraManager.GetDeviceCount();
			CString strDeviceName; CString strDeviceComID;
			for (int nCameraIndex = 0; nCameraIndex < nCameraCount; nCameraIndex++){

				m_AgoraCameraManager.GetDevice(nCameraIndex, strDeviceName, strDeviceComID);
				m_comCameraName.AddString(strDeviceName);
				if (strDeviceName == strDefCameraName){
					nDefIndex = nCameraIndex;
				}
			}
		}
	}
	if (0 <= nDefIndex){
		m_comCameraName.SetCurSel(nDefIndex);
	}
	else
		m_comCameraName.SetCurSel(m_nCurIndex - 1);

	m_checkRtmpSave.SetCheck(FALSE);
	m_editRtmpHeight.SetWindowTextW(_T("0"));
	m_editRtmpWidth.SetWindowTextW(_T("0"));
	m_editRtmpFps.SetWindowTextW(_T("0"));
	m_editRtmpBitrate.SetWindowTextW(_T("0"));
	m_editRtmpUrl.SetWindowTextW(_T(""));
}

BOOL CDlgCamera::SaveConfigInfo()
{
#define IMPLEMENT_CameraInfo_SecurityChecek()\
	if (_T("") == strParam){\
		CAgoraFormatStr::AgoraMessageBox(_T("UID, CameraName 不能为空,请重新输入"));\
		return FALSE;\
	}\

	CString strParam;
	BOOL bRes = m_checkEnable.GetCheck();
	std::string strSection = cs2s(m_InstanceDesc);
	gAgoraConfigMainUI.setProcessEnable(strSection, int2str(bRes));

	m_editLoginUID.GetWindowTextW(strParam);
	IMPLEMENT_CameraInfo_SecurityChecek()
	gAgoraConfigMainUI.setLoginUid(strSection,cs2s(strParam));

	m_comCameraName.GetWindowTextW(strParam);
	IMPLEMENT_CameraInfo_SecurityChecek();
	gAgoraConfigMainUI.setCameraName(strSection, cs2s(strParam));
	CString strCameraName; CString strCameraComID;
	int nCurVideoIndex = m_comCameraName.GetCurSel();
	m_AgoraCameraManager.GetDevice(nCurVideoIndex, strCameraName, strCameraComID);
	gAgoraConfigMainUI.setCameraComID(strSection, cs2s(strCameraComID));

	bRes = m_checkVerCamera.GetCheck();
	gAgoraConfigMainUI.setLeftRotate90(strSection,int2str(bRes));
	bRes = m_checkSwitchWidthHeight.GetCheck();
	gAgoraConfigMainUI.setSwitchWHEnable(strSection, int2str(bRes));

	bRes = m_checkRtmpSave.GetCheck();
	gAgoraConfigMainUI.setRtmpSave(strSection, int2str(bRes));
	m_editRtmpWidth.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setRtmpWidth(strSection, cs2s(strParam));
	m_editRtmpHeight.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setRtmpHeight(strSection, cs2s(strParam));
	m_editRtmpFps.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setRtmpFps(strSection, cs2s(strParam));
	m_editRtmpBitrate.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setRtmpBitrate(strSection, cs2s(strParam));
	m_editRtmpUrl.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setRtmpUrl(strSection, cs2s(strParam));

	//Check Encoder VideoProfile and Rtmp SendVideoProfile Security Check
	//TO DO

	return TRUE;
}

void CDlgCamera::OnClose()
{
	uninitCtrl();
	CDialogEx::OnClose();
}

void CDlgCamera::OnShowWindow(BOOL bShow, UINT nStatus)
{
	initCtrl();
	CDialogEx::OnShowWindow(bShow, nStatus);
}

void CDlgCamera::OnBnClickedButtonPreview()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_lpAgoraObject && m_lpRtcEngine){

		CString strDeviceName; CString strDeviceComID;
		int nCameraIndex = m_comCameraName.GetCurSel();

		if (m_AgoraCameraManager.GetDevice(nCameraIndex, strDeviceName, strDeviceComID)){

			if (m_AgoraCameraManager.SetCurDevice(strDeviceComID)){

				m_comCameraName.EnableWindow(m_AgoraCameraManager.IsTesting());
				m_AgoraCameraManager.TestCameraDevice(m_ctlLocalVideoPreview, !m_AgoraCameraManager.IsTesting());
				m_ctlLocalVideoPreview.Invalidate();
			}
		}
	}
}

void CDlgCamera::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	BOOL bRes = m_checkVerCamera.GetCheck();

	if (bRes)
		m_checkSwitchWidthHeight.SetCheck(!bRes);
}


void CDlgCamera::OnBnClickedCheckSwitchwidthheight()
{
	// TODO:  在此添加控件通知处理程序代码
	BOOL bRes = m_checkSwitchWidthHeight.GetCheck();
	
	if (bRes)
		m_checkVerCamera.SetCheck(!bRes);
}


void CDlgCamera::OnBnClickedButtonSave()
{
	// TODO:  在此添加控件通知处理程序代码
	SaveConfigInfo();

	LPAG_WAWAJI_CONFIG lpData = new AG_WAWAJI_CONFIG;
	lpData->configInstance = (eTagConfigType)m_nCurIndex;
	lpData->isRunStream = FALSE;
	::PostMessage(theApp.GetMainWnd()->m_hWnd, WawajiMsgType_Config, (WPARAM)lpData, NULL);
}
