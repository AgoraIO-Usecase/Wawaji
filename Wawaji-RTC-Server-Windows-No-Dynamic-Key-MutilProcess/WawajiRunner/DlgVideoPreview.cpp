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
}


BEGIN_MESSAGE_MAP(CDlgVideoPreview, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHILD_Apply, &CDlgVideoPreview::OnBnClickedButtonChildApply)
	ON_BN_CLICKED(IDC_BUTTON_VideoPreview, &CDlgVideoPreview::OnBnClickedButtonVideopreview)
END_MESSAGE_MAP()


// CDlgVideoPreview 消息处理程序
BOOL CDlgVideoPreview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//TO DO
	ShowWindow(SW_HIDE);

	return true;
}

void CDlgVideoPreview::initCtrl()
{
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

	std::string strSection = cs2s(m_processIdName);
	bool bEnable = str2int(gWawajiConfig.getProcessEnable(strSection));
	((CButton*)GetDlgItem(IDC_CHECK_CameraList))->SetCheck(bEnable);
	std::string iniConfig = gWawajiConfig.getLoginUid(strSection);
	GetDlgItem(IDC_EDIT_CHILDUID)->SetWindowTextW(s2cs(iniConfig));
	iniConfig = gWawajiConfig.getCameraName(strSection);

	int cameracount = m_pAgoraCameraManager->GetDeviceCount();
	CString curDeviceName, curDeviceID;
	CString defDeviceID = s2cs(iniConfig);
	int curSel = CB_ERR;
	for (int DeviceId = 0; cameracount > DeviceId; DeviceId++)
	{
		m_pAgoraCameraManager->GetDevice(DeviceId,curDeviceName,curDeviceID);
		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->AddString(curDeviceName);
		if (defDeviceID == curDeviceName){
			curSel = DeviceId;
		}
	}

	if (curSel != CB_ERR)
	{
		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->SetCurSel(curSel);
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
	if (bres && true){

		((CComboBox*)(GetDlgItem(IDC_COMBO_CameraList)))->GetWindowTextW(curDeviceName);

		int DeviceCount = m_pAgoraCameraManager->GetDeviceCount();
		CString DeviceName, DeviceID;
		for (int nDeviceId = 0; DeviceCount > nDeviceId; nDeviceId++)
		{
			m_pAgoraCameraManager->GetDevice(nDeviceId, DeviceName, DeviceID);
			if (curDeviceName == DeviceName){
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
}