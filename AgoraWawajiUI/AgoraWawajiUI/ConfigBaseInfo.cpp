// ConfigBaseInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiUI.h"
#include "ConfigBaseInfo.h"
#include "afxdialogex.h"


// CDlgConfigBaseInfo 对话框

IMPLEMENT_DYNAMIC(CDlgConfigBaseInfo, CDialogEx)

CDlgConfigBaseInfo::CDlgConfigBaseInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfigBaseInfo::IDD, pParent)
{

}

CDlgConfigBaseInfo::~CDlgConfigBaseInfo()
{
}

void CDlgConfigBaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BASEINFO_APPID, m_EditAppId);
	DDX_Control(pDX, IDC_EDIT_BASEINFO_APPCERTID, m_EditAppCertId);
	DDX_Control(pDX, IDC_EDIT_BASEINFO_CHANNEL, m_EditChannelName);
	DDX_Control(pDX, IDC_COMBO_BASEINFO_VideoProfile, m_comVideoProfile);
	DDX_Control(pDX, IDC_EDIT_BASEINFO_AutoClearLog, m_EditAutoClearLog);
	DDX_Control(pDX, IDC_COMBO_BaseInfo_Language, m_comLanguage);
	DDX_Control(pDX, IDC_CHECK_BaseInfo_EnablePreview, m_checkLocalPreview);
}


BEGIN_MESSAGE_MAP(CDlgConfigBaseInfo, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_Save, &CDlgConfigBaseInfo::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CDlgConfigBaseInfo 消息处理程序
BOOL CDlgConfigBaseInfo::OnInitDialog()
{
	UpdateData(FALSE);
	ShowWindow(SW_HIDE);
	initData();

	return CDialogEx::OnInitDialog();
}

inline void CDlgConfigBaseInfo::initData()
{
	LPTSTR m_szProfileDes[32];
	int m_nProfileValue[32];
	m_szProfileDes[0] = _T("160x120 15fps 65kbps");
	m_nProfileValue[0] = 0;
	m_szProfileDes[1] = _T("120x120 15fps 50kbps");
	m_nProfileValue[1] = 2;

	m_szProfileDes[2] = _T("320x180 15fps 140kbps");
	m_nProfileValue[2] = 10;
	m_szProfileDes[3] = _T("180x180 15fps 100kbps");
	m_nProfileValue[3] = 12;
	m_szProfileDes[4] = _T("240x180 15fps 120kbps");
	m_nProfileValue[4] = 13;

	m_szProfileDes[5] = _T("320x240 15fps 200kbps");
	m_nProfileValue[5] = 20;
	m_szProfileDes[6] = _T("240x240 15fps 140kbps");
	m_nProfileValue[6] = 22;
	m_szProfileDes[7] = _T("424x240 15fps 220kbps");
	m_nProfileValue[7] = 23;

	m_szProfileDes[8] = _T("640x360 15fps 400kbps");
	m_nProfileValue[8] = 30;
	m_szProfileDes[9] = _T("360x360 15fps 260kbps");
	m_nProfileValue[9] = 32;
	m_szProfileDes[10] = _T("640x360 30fps 600kbps");
	m_nProfileValue[10] = 33;
	m_szProfileDes[11] = _T("360x360 30fps 400kbps");
	m_nProfileValue[11] = 35;
	m_szProfileDes[12] = _T("480x360 15fps 320kbps");
	m_nProfileValue[12] = 36;
	m_szProfileDes[13] = _T("480x360 30fps 490kbps");
	m_nProfileValue[13] = 37;
	m_szProfileDes[14] = _T("640x360 15fps 800kbps");
	m_nProfileValue[14] = 38;

	m_szProfileDes[15] = _T("640x480 15fps 500kbps");
	m_nProfileValue[15] = 40;
	m_szProfileDes[16] = _T("480x480 15fps 400kbps");
	m_nProfileValue[16] = 42;
	m_szProfileDes[17] = _T("640x480 30fps 750kbps");
	m_nProfileValue[17] = 43;
	m_szProfileDes[18] = _T("480x480 30fps 600kbps");
	m_nProfileValue[18] = 44;
	m_szProfileDes[19] = _T("848x480 15fps 610kbps");
	m_nProfileValue[19] = 47;
	m_szProfileDes[20] = _T("848x480 30fps 930kbps");
	m_nProfileValue[20] = 48;

	m_szProfileDes[21] = _T("1280x720 15fps 1130kbps");
	m_nProfileValue[21] = 50;
	m_szProfileDes[22] = _T("1280x720 30fps 1710kbps");
	m_nProfileValue[22] = 52;
	m_szProfileDes[23] = _T("960x720 15fps 910kbps");
	m_nProfileValue[23] = 54;
	m_szProfileDes[24] = _T("960x720 30fps 1380kbps");
	m_nProfileValue[24] = 55;

	m_szProfileDes[25] = _T("1920x1080 15fps 2080kbps");
	m_nProfileValue[25] = 60;
	m_szProfileDes[26] = _T("1920x1080 30fps 3150kbps");
	m_nProfileValue[26] = 62;
	m_szProfileDes[27] = _T("1920x1080 60fps 4780kbps");
	m_nProfileValue[27] = 64;
	m_szProfileDes[28] = _T("2560x1440 30fps 4850kbps");
	m_nProfileValue[28] = 66;
	m_szProfileDes[29] = _T("3560x1440 60fps 7350kbps");
	m_nProfileValue[29] = 67;

	m_szProfileDes[30] = _T("3840x2160 30fps 8190kbps");
	m_nProfileValue[30] = 70;
	m_szProfileDes[31] = _T("3840x2160 60fps 13500kbps");
	m_nProfileValue[31] = 72;

	for (int nIndex = 0; nIndex < 32; nIndex++){

		m_comVideoProfile.AddString(m_szProfileDes[nIndex]);
		m_comVideoProfile.SetItemData(nIndex, (DWORD_PTR)m_nProfileValue[nIndex]);
	}
	m_comVideoProfile.SetCurSel(15);

	m_EditChannelName.SetWindowTextW(_T("wawaji_demo"));
	m_comLanguage.AddString(_T("English"));
	m_comLanguage.AddString(_T("Chinese"));
	m_comLanguage.SetCurSel(0);

	m_EditAutoClearLog.SetWindowTextW(_T("0"));
	m_checkLocalPreview.SetCheck(TRUE);
}

inline void CDlgConfigBaseInfo::initCtrl()
{
	//InitData
	std::string strAppId = gAgoraConfigMainUI.getAppId();
	std::string strAppCertID = gAgoraConfigMainUI.getAppCertificateId();
	std::string strChannelName = gAgoraConfigMainUI.getChannelName();
	std::string strVideoProfile = gAgoraConfigMainUI.getResolutionIndex();
	std::string strAutoClearLog = gAgoraConfigMainUI.getClearLogInterval();
	std::string strLanguage = gAgoraConfigMainUI.getLanguagePack();
	std::string strPreview = gAgoraConfigMainUI.getVideoPreview();

	m_EditAppId.SetWindowTextW(s2cs(strAppId));
	m_EditAppCertId.SetWindowTextW(s2cs(strAppCertID));
	m_EditChannelName.SetWindowTextW(s2cs(strChannelName));
	m_comVideoProfile.SetCurSel(str2int(strVideoProfile));
	if ("" != strVideoProfile)
		m_comVideoProfile.SetCurSel(str2int(strVideoProfile));

	if ("" != strAutoClearLog)
	m_EditAutoClearLog.SetWindowTextW(s2cs(strAutoClearLog));

	if ("" != strLanguage)
		m_comLanguage.SetWindowTextW(s2cs(strLanguage));

	m_checkLocalPreview.SetCheck(str2int(strPreview));
}

inline void CDlgConfigBaseInfo::uninitCtrl()
{

}

BOOL CDlgConfigBaseInfo::SaveConfigInfo()
{
	//SaveAll
	CString strParam;
	m_EditAppId.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setAppId(cs2s(strParam));
	m_EditAppCertId.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setAppCertificateId(cs2s(strParam));
	m_EditChannelName.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setChannelName(cs2s(strParam));
	m_comVideoProfile.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setResolution(cs2s(strParam));
	int nResolutionIndex = m_comVideoProfile.GetCurSel();
	gAgoraConfigMainUI.setResolutionIndex(int2str(nResolutionIndex));
	m_EditAutoClearLog.GetWindowTextW(strParam);
	gAgoraConfigMainUI.setClearLogInterval(cs2s(strParam));
	int nLanguage = m_comLanguage.GetCurSel();
	gAgoraConfigMainUI.setLanguagePack(int2str(nLanguage));
	BOOL bCheck = m_checkLocalPreview.GetCheck();
	gAgoraConfigMainUI.setVideoPreview(int2str(bCheck));

	return TRUE;
}

void CDlgConfigBaseInfo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	initCtrl();
	CDialogEx::OnShowWindow(bShow, nStatus);
}

void CDlgConfigBaseInfo::OnClose()
{
	//To Do
	uninitCtrl();

	CDialogEx::OnCancel();
}

void CDlgConfigBaseInfo::OnBnClickedButtonSave()
{
	// TODO:  在此添加控件通知处理程序代码
	SaveConfigInfo();
}
