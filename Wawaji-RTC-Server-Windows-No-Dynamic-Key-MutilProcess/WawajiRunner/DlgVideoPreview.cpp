// DlgVideoPreview.cpp : 实现文件
//

#include "stdafx.h"
#include "WawajiRunner.h"
#include "DlgVideoPreview.h"
#include "afxdialogex.h"
#include "../WawajiDemo/commonFun.h"
#include "../WawajiDemo/FileIO.h"
#include "AgoraCameraManager.h"

// CDlgVideoPreview 对话框

IMPLEMENT_DYNAMIC(CDlgVideoPreview, CDialogEx)

CDlgVideoPreview::CDlgVideoPreview(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVideoPreview::IDD, pParent)
{

}

CDlgVideoPreview::~CDlgVideoPreview()
{
}

void CDlgVideoPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RTMPWDITH, m_edtRtmpWidth);
	DDX_Control(pDX, IDC_EDIT_RTMPHEIGHT, m_edtRtmpHeight);
	DDX_Control(pDX, IDC_EDIT_RTMPFPS, m_edtRtmpFps);
	DDX_Control(pDX, IDC_EDIT_RTMPBITRATE, m_edtRtmpBitrate);
	DDX_Control(pDX, IDC_EDIT_RTMPURL, m_edtRtmpUrl);
	DDX_Control(pDX, IDC_COMBO_VIDEORESOLUTION, m_comVideoSolution);
	DDX_Control(pDX, IDC_CHECK_RTMP, m_ckRtmp);
	DDX_Control(pDX, IDC_CHECK_LEFTRotate90, m_ckLeftRotate90);
	DDX_Control(pDX, IDC_CHECK_SwitchWH, m_ckSwitchWH);
}


BEGIN_MESSAGE_MAP(CDlgVideoPreview, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHILD_Apply, &CDlgVideoPreview::OnBnClickedButtonChildApply)
	ON_BN_CLICKED(IDC_BUTTON_VideoPreview, &CDlgVideoPreview::OnBnClickedButtonVideopreview)
	ON_BN_CLICKED(IDC_CHECK_LEFTRotate90, &CDlgVideoPreview::OnBnClickedCheckLeftrotate90)
	ON_BN_CLICKED(IDC_CHECK_SwitchWH, &CDlgVideoPreview::OnBnClickedCheckSwitchwh)
END_MESSAGE_MAP()


// CDlgVideoPreview 消息处理程序
BOOL CDlgVideoPreview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//TO DO
	ShowWindow(SW_HIDE);
	initCtrl();

	return true;
}

void CDlgVideoPreview::initCtrl()
{
	m_szProfileDes[0] = _T("160x120 15fps 65kbps");
	m_szProfileDes[1] = _T("120x120 15fps 50kbps");
	m_szProfileDes[2] = _T("320x180 15fps 140kbps");
	m_szProfileDes[3] = _T("180x180 15fps 100kbps");
	m_szProfileDes[4] = _T("240x180 15fps 120kbps");
	m_szProfileDes[5] = _T("320x240 15fps 200kbps");
	m_szProfileDes[6] = _T("240x240 15fps 140kbps");
	m_szProfileDes[7] = _T("424x240 15fps 220kbps");
	m_szProfileDes[8] = _T("640x360 15fps 400kbps");
	m_szProfileDes[9] = _T("360x360 15fps 260kbps");
	m_szProfileDes[10] = _T("640x360 30fps 600kbps");
	m_szProfileDes[11] = _T("360x360 30fps 400kbps");
	m_szProfileDes[12] = _T("480x360 15fps 320kbps");
	m_szProfileDes[13] = _T("480x360 30fps 490kbps");
	m_szProfileDes[14] = _T("640x360 15fps 800kbps");
	m_szProfileDes[15] = _T("640x480 15fps 500kbps");
	m_szProfileDes[16] = _T("480x480 15fps 400kbps");
	m_szProfileDes[17] = _T("640x480 30fps 750kbps");
	m_szProfileDes[18] = _T("480x480 30fps 600kbps");
	m_szProfileDes[19] = _T("848x480 15fps 610kbps");
	m_szProfileDes[20] = _T("848x480 30fps 930kbps");
	m_szProfileDes[21] = _T("1280x720 15fps 1130kbps");
	m_szProfileDes[22] = _T("1280x720 30fps 1710kbps");
	m_szProfileDes[23] = _T("960x720 15fps 910kbps");
	m_szProfileDes[24] = _T("960x720 30fps 1380kbps");
	m_szProfileDes[25] = _T("1920x1080 15fps 2080kbps");
	m_szProfileDes[26] = _T("1920x1080 30fps 3150kbps");
	m_szProfileDes[27] = _T("1920x1080 60fps 4780kbps");
	m_szProfileDes[28] = _T("2560x1440 30fps 4850kbps");
	m_szProfileDes[29] = _T("3560x1440 60fps 7350kbps");
	m_szProfileDes[30] = _T("3840x2160 30fps 8190kbps");
	m_szProfileDes[31] = _T("3840x2160 60fps 13500kbps");

	for (int nIndex = 0; nIndex < 32; nIndex++){

		m_comVideoSolution.AddString(m_szProfileDes[nIndex]);
	}

	m_comVideoSolution.SetCurSel(15);//default VideoSolutionIndex
}

void CDlgVideoPreview::uninitCtrl()
{

}

void CDlgVideoPreview::OnBnClickedButtonChildApply()
{
	// TODO:  在此添加控件通知处理程序代码
	CString curDeviceName;
	((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetWindowTextW(curDeviceName);

	int DeviceCount = m_pAgoraCameraManager->GetDeviceCount();
	CString DeviceName, DeviceID;
	for (int nDeviceId = 0; DeviceCount > nDeviceId; nDeviceId++)
	{
		m_pAgoraCameraManager->GetDevice(nDeviceId, DeviceName, DeviceID);
		if (curDeviceName == DeviceName){
			m_pAgoraCameraManager->SetCurDevice(DeviceID);
			break;
		}
	}	
}


void CDlgVideoPreview::OnBnClickedButtonVideopreview()
{
	// TODO:  在此添加控件通知处理程序代码
	CString curDeviceName;
	((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetWindowTextW(curDeviceName);
	int nCurDeviceIndex = ((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetCurSel();

	int DeviceCount = m_pAgoraCameraManager->GetDeviceCount();
	CString DeviceName, DeviceID;
	for (int nDeviceId = 0; DeviceCount > nDeviceId; nDeviceId++)
	{
		m_pAgoraCameraManager->GetDevice(nDeviceId, DeviceName, DeviceID);
		if (curDeviceName == DeviceName && nDeviceId == nCurDeviceIndex){
			m_pAgoraCameraManager->SetCurDevice(DeviceID);
			break;
		}
	}

	HWND wnd = (GetDlgItem(IDC_STATIC_PIC_VIDEOPREVIEW))->m_hWnd;
	if (!m_pAgoraCameraManager->IsTesting()){

		m_pAgoraCameraManager->TestCameraDevice(wnd, TRUE);
		GetDlgItem(IDC_BUTTON_VideoPreview)->SetWindowTextW(_T("Stop Preview"));
	}
	else{

		m_pAgoraCameraManager->TestCameraDevice(NULL, FALSE);
		GetDlgItem(IDC_BUTTON_VideoPreview)->SetWindowTextW(_T("VideoPreview"));
	}
}

void CDlgVideoPreview::setChildInfo(const CString processName, CAgoraCameraManager* pCameraManager)
{
	ASSERT(pCameraManager);
	m_processIdName = processName;
	m_pAgoraCameraManager = pCameraManager;

	GetDlgItem(IDC_STATIC_CHILDPROCESSDESC)->SetWindowText(processName);

	//Enable
	std::string strSection = cs2s(m_processIdName);
	bool bEnable = str2int(gWawajiConfig.getProcessEnable(strSection));
	((CButton*)GetDlgItem(IDC_CHECK_CameraList))->SetCheck(bEnable);

	//UID
	std::string configValue = gWawajiConfig.getLoginUid(strSection);
	GetDlgItem(IDC_EDIT_CHILDUID)->SetWindowTextW(s2cs(configValue));

	//ChannelName
	std::string strChannelName = gWawajiConfig.getChannelName(strSection);
	GetDlgItem(IDC_EDIT_CHILD_CHANNELNAME)->SetWindowTextW(s2cs(strChannelName));

	//Camera
	configValue = gWawajiConfig.getCameraName(strSection);
	CString configValueDeviceId = s2cs(gWawajiConfig.getCameraComID(strSection));
	int cameracount = m_pAgoraCameraManager->GetDeviceCount();
	CString curDeviceName, curDeviceID;
	CString defDeviceName = s2cs(configValue);
	int nCurSection = CB_ERR;
	for (int DeviceId = 0; cameracount > DeviceId; DeviceId++)
	{
		m_pAgoraCameraManager->GetDevice(DeviceId,curDeviceName,curDeviceID);
		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->AddString(curDeviceName);
		if (defDeviceName == curDeviceName && configValueDeviceId == curDeviceID){
			nCurSection = DeviceId;
		}
	}
	if (nCurSection != CB_ERR)
	{
		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->SetCurSel(nCurSection);
	}

	//VideoResolution
	nCurSection = CB_ERR;
	configValue = gWawajiConfig.getResolutionIndex(strSection);
	if ("" == configValue || "-1" == configValue){
		nCurSection = 15;
	}
	else{
		nCurSection = str2int(configValue);
	}
	m_comVideoSolution.SetCurSel(nCurSection);

	//RTMP
	BOOL bRes = FALSE;
	configValue = gWawajiConfig.getRtmpSave(strSection);
	if ("" == configValue || "0" == configValue){
		bRes = FALSE;
	}
	else if("1" == configValue){
		bRes = TRUE;
	}
	m_ckRtmp.SetCheck(bRes);

	configValue = gWawajiConfig.getRtmpWidth(strSection);
	m_edtRtmpWidth.SetTip("" == configValue ? _T("Width") : s2cs(configValue));
	configValue = gWawajiConfig.getRtmpHeight(strSection);
	m_edtRtmpHeight.SetTip("" == configValue ? _T("Height") : s2cs(configValue));
	configValue = gWawajiConfig.getRtmpFps(strSection);
	m_edtRtmpFps.SetTip("" == configValue ? _T("FPS") : s2cs(configValue));
	configValue = gWawajiConfig.getRtmpBitrate(strSection);
	m_edtRtmpBitrate.SetTip("" == configValue ? _T("BITRATE") : s2cs(configValue));
	configValue = gWawajiConfig.getRtmpUrl(strSection);
	m_edtRtmpUrl.SetTip("" == configValue ? _T("RTMPURL") : s2cs(configValue));

	std::string strRemoteVideoRotate90 = gWawajiConfig.getLeftRotate90(strSection);
	if ("" == strRemoteVideoRotate90 || "0" == strRemoteVideoRotate90){
		m_ckLeftRotate90.SetCheck(FALSE);
	}
	else if("1" == strRemoteVideoRotate90){
		m_ckLeftRotate90.SetCheck(TRUE);
	}

	std::string strSwitchWH = gWawajiConfig.getSwitchWHEnable(strSection);
	if ("" == strSwitchWH || "0" == strSwitchWH){
		m_ckSwitchWH.SetCheck(FALSE);
	}
	else if ("1" == strSwitchWH){
		m_ckSwitchWH.SetCheck(TRUE);
	}
}

void CDlgVideoPreview::showChildWnd(bool Enable /*= true*/)
{
	if (Enable){
		ShowWindow(SW_SHOW);
	}
	else{
		ShowWindow(SW_HIDE);
	}
}

void CDlgVideoPreview::saveConfig()
{
	m_pAgoraCameraManager->TestCameraDevice(NULL, FALSE);
	bool bres = ((CButton*)(GetDlgItem(IDC_CHECK_CameraList)))->GetCheck();
	CString curDeviceName;
	if (bres){

		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetWindowTextW(curDeviceName);
		int nCurDeviceIndex = ((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetCurSel();

		int DeviceCount = m_pAgoraCameraManager->GetDeviceCount();
		CString DeviceName, DeviceID;
		for (int nDeviceId = 0; DeviceCount > nDeviceId; nDeviceId++)
		{
			m_pAgoraCameraManager->GetDevice(nDeviceId, DeviceName, DeviceID);
			if (curDeviceName == DeviceName && nCurDeviceIndex == nDeviceId){
				//AfxMessageBox(m_processIdName + s2cs(int2str(nDeviceId)));
				m_curDeviceID = DeviceID;
				break;
			}
		}
	}

	std::string strSection = cs2s(m_processIdName);
	gWawajiConfig.setProcessEnable(strSection, int2str(bres));
	gWawajiConfig.setCameraComID(strSection, cs2s(m_curDeviceID));
	gWawajiConfig.setCameraName(strSection, cs2s(curDeviceName));

	CString sParam;
	GetDlgItem(IDC_EDIT_CHILDUID)->GetWindowText(sParam);
	gWawajiConfig.setLoginUid(strSection, cs2s(sParam));

	GetDlgItem(IDC_EDIT_CHILD_CHANNELNAME)->GetWindowTextW(sParam);
	gWawajiConfig.setChannelName(strSection, cs2s(sParam));

	//VideoSolution
	bool res = m_ckLeftRotate90.GetCheck();
	gWawajiConfig.setLeftRotate90(strSection, int2str(res));

	int curSel = m_comVideoSolution.GetCurSel();
	int width = 0, height = 0, fps = 0, bitrate = 0;
	std::string bitrateUrl;
	m_comVideoSolution.GetWindowTextW(sParam);
	gWawajiConfig.setResolutionSave(strSection,"1");
	gWawajiConfig.setResolutionIndex(strSection, int2str(curSel));
	getVideoParam(sParam, width, height, fps, bitrate);
	gWawajiConfig.setResolutionWidth(strSection, int2str(res ? height : width));
	gWawajiConfig.setResolutionHeight(strSection, int2str(res ? width : height));
	gWawajiConfig.setResolutionFps(strSection,int2str(fps));
	gWawajiConfig.setResolutionBitrate(strSection,int2str(bitrate));

	//SwitchWidthHeight
	res = m_ckSwitchWH.GetCheck();
	gWawajiConfig.setSwitchWHEnable(strSection, int2str(res));

	//RTMP
	res = m_ckRtmp.GetCheck();
	gWawajiConfig.setRtmpSave(strSection, int2str(res));
	m_edtRtmpWidth.GetWindowTextW(sParam);
	gWawajiConfig.setRtmpWidth(strSection, cs2s(sParam));
	m_edtRtmpHeight.GetWindowTextW(sParam);
	gWawajiConfig.setRtmpHeight(strSection, cs2s(sParam));
	m_edtRtmpFps.GetWindowTextW(sParam);
	gWawajiConfig.setRtmpFps(strSection, cs2s(sParam));
	m_edtRtmpBitrate.GetWindowTextW(sParam);
	gWawajiConfig.setRtmpBitrate(strSection, cs2s(sParam));
	m_edtRtmpUrl.GetWindowTextW(sParam);
	gWawajiConfig.setRtmpUrl(strSection, cs2s(sParam));
}

bool CDlgVideoPreview::getVideoParam(CString sSrc, int &width, int &height, int &fps, int &bitrate)
{
	//424x240 15fps 220kbps
	if (_T("") != sSrc){
		int nFindKeyIndex = sSrc.Find(_T("x"));
		CString sSubStr = sSrc.Mid(0, nFindKeyIndex);
		width = str2int(cs2s(sSubStr));
		int nFindKeyIndex1 = sSrc.Find(_T(" "));
		sSubStr = sSrc.Mid(nFindKeyIndex + 1, nFindKeyIndex1 - nFindKeyIndex - 1);
		height = str2int(cs2s(sSubStr));
		nFindKeyIndex = sSrc.Find(_T("fps"));
		sSubStr = sSrc.Mid(nFindKeyIndex1 + 1, nFindKeyIndex - nFindKeyIndex1 - 1);
		fps = str2int(cs2s(sSubStr));
		nFindKeyIndex1 = sSrc.Find(_T("kbps"));
		sSubStr = sSrc.Mid(nFindKeyIndex + 4, nFindKeyIndex1 - nFindKeyIndex - 4);
		bitrate = str2int(cs2s(sSubStr));
		return TRUE;
	}

	return FALSE;
}

void CDlgVideoPreview::OnBnClickedCheckLeftrotate90()
{
	// TODO:  在此添加控件通知处理程序代码
	BOOL bRes = m_ckRtmp.GetCheck();
	if (bRes){

		m_ckSwitchWH.SetCheck(!bRes);
	}
}


void CDlgVideoPreview::OnBnClickedCheckSwitchwh()
{
	// TODO:  在此添加控件通知处理程序代码
	BOOL bRes = m_ckSwitchWH.GetCheck();
	if (bRes){
		
		m_ckLeftRotate90.SetCheck(!bRes);
	}
}


bool CDlgVideoPreview::checkParam()
{
	std::string strSection = cs2s(m_processIdName);

	//RTMP
	if ("1" == gWawajiConfig.getRtmpSave(strSection)){

		int nSolutionWidth = str2int(gWawajiConfig.getResolutionWidth(strSection));
		int nSolutionHeight = str2int(gWawajiConfig.getResolutionHeight(strSection));
		int nSolutionFps = str2int(gWawajiConfig.getResolutionFps(strSection));
		int nSolutionBitrate = str2int(gWawajiConfig.getResolutionBitrate(strSection));

		int nRtmpWidth = str2int(gWawajiConfig.getRtmpWidth(strSection));
		int nRtmpHeight = str2int(gWawajiConfig.getRtmpHeight(strSection));
		int nRtmpFps = str2int(gWawajiConfig.getRtmpFps(strSection));
		int nRtmpBitrate = str2int(gWawajiConfig.getRtmpBitrate(strSection));

		if (nSolutionWidth < nRtmpWidth ||
			nSolutionHeight < nRtmpHeight ||
			nSolutionFps < nRtmpFps ||
			nSolutionBitrate < nRtmpBitrate){

			CString strDesc;
			strDesc.Format(_T("进程: %s 对应的 Rtmp 推流参数设置 不合理( 检查参数设置是否超过了采集参数)"), m_processIdName);
			AfxMessageBox(strDesc);
		}

		//Camera occupancy
		std::string strCurProcessComId = gWawajiConfig.getCameraComID(strSection);
		std::string strKey = "process";
		std::string strInex = strSection.substr(strKey.length(), strSection.length() - strKey.length());
		int nIndexCur = str2int(strInex);
		for (int nIndex = 0; nIndex < nIndexCur; nIndex++){

			std::string strIndexTemp = strKey + int2str(nIndex);
			if ("1" == gWawajiConfig.getProcessEnable(strSection)){

				std::string strCameraComID = gWawajiConfig.getCameraComID(strIndexTemp);
				if (strCameraComID == strCurProcessComId){
					CString strDesc;
					strDesc.Format(_T("进程: %s 与 %s 的摄像头相互占用,请更改"), m_processIdName, s2cs(strIndexTemp));
					AfxMessageBox(strDesc);
					break;
				}
			}
		}
	}

	return TRUE;
}