// DlgConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraWawajiUI.h"
#include "DlgConfig.h"
#include "afxdialogex.h"

#include "DlgCamera.h"
#include "ConfigBaseInfo.h"

// CDlgConfig 对话框

IMPLEMENT_DYNAMIC(CDlgConfig, CDialogEx)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfig::IDD, pParent),
	m_curConfigType(eTagConfigType::eTagConfigType_BaseInfo),
	m_curConfigData(NULL)
{

}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Config, m_TabCtrlConfig);
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Config, &CDlgConfig::OnTcnSelchangeTabConfig)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_SaveAll, &CDlgConfig::OnBnDoubleclickedButtonSaveall)
END_MESSAGE_MAP()


// CDlgConfig 消息处理程序
BOOL CDlgConfig::OnInitDialog()
{
	// TO DO
	UpdateData(FALSE);
	CenterWindow();
//	initCtrl();

	return CDialogEx::OnInitDialog();
}

inline void CDlgConfig::initCtrl()
{
	CRect rt;
	m_TabCtrlConfig.GetClientRect(&rt);
	rt.top = rt.top + 20;
	rt.bottom = rt.bottom;

	m_TabCtrlConfig.InsertItem(0,s2cs(KConfigBaseInfo));
	eTagConfigType conType = eTagConfigType::eTagConfigType_NULL;
	LPAG_CONFIG lpConfigData = new AG_CONFIG;
	conType = eTagConfigType::eTagConfigType_BaseInfo;
	lpConfigData->szBufferDesc = KConfigBaseInfo;
	CDlgConfigBaseInfo  *pDlgBaseInfo = new CDlgConfigBaseInfo(&m_TabCtrlConfig);
	pDlgBaseInfo->Create(CDlgConfigBaseInfo::IDD,&m_TabCtrlConfig);
	lpConfigData->m_pDlg = static_cast<void*>(pDlgBaseInfo);
	m_mapConfigInfo[conType] = lpConfigData;
	pDlgBaseInfo->MoveWindow(rt);

	if (lpConfigData){

		m_curConfigType = eTagConfigType::eTagConfigType_BaseInfo;
		m_curConfigData = lpConfigData;
	}

	CAgoraObject* pAgoraObject = CAgoraObject::GetAgoraObject();
	IRtcEngine* pRtcEngine = CAgoraObject::GetEngine();
	if (pAgoraObject && pRtcEngine){

		pAgoraObject->EnableVideo(TRUE);
		m_AgoraCameraManager.Create(pRtcEngine);
		int nCameraCount = m_AgoraCameraManager.GetDeviceCount();

		for (int nIndex = 1; nCameraCount >= nIndex && nIndex <= gMaxCameraCount; nIndex++){

			TCHAR tszBuffer[128] = { _T('\0') };
			swprintf_s(tszBuffer,_T("Instance%d"),nIndex);

			if (2 == gMaxCameraCount){
				if (1 == nIndex)
					m_TabCtrlConfig.InsertItem(nIndex, KFrontCamera);
				else
					m_TabCtrlConfig.InsertItem(nIndex, KBackCamera);
			}
			else
				m_TabCtrlConfig.InsertItem(nIndex, tszBuffer);
			conType = (eTagConfigType)(nIndex);
			lpConfigData = new AG_CONFIG;
			lpConfigData->szBufferDesc = cs2s(tszBuffer);
			CDlgCamera *pDlgCamera = new CDlgCamera(tszBuffer,&m_TabCtrlConfig);
			pDlgCamera->Create(CDlgCamera::IDD,&m_TabCtrlConfig);
			pDlgCamera->MoveWindow(rt);
			lpConfigData->m_pDlg = static_cast<void*>(pDlgCamera);
			m_mapConfigInfo[conType] = lpConfigData;
		}
	}

	((CWnd*)(m_curConfigData->m_pDlg))->ShowWindow(SW_SHOW);
}

inline void CDlgConfig::uninitCtrl()
{
	m_AgoraCameraManager.Close();
	std::map<eTagConfigType, LPAG_CONFIG>::iterator it = m_mapConfigInfo.begin();
	for (; m_mapConfigInfo.end() != it;){
		if (eTagConfigType::eTagConfigType_BaseInfo == it->first){

			delete (CDlgConfigBaseInfo*)it->second->m_pDlg;
			it->second->m_pDlg = nullptr;
			delete it->second;
			it->second = nullptr;
			it = m_mapConfigInfo.erase(it);
		}
		else if (eTagConfigType::eTagConfigType_Instance1<= it->first){

			delete (CDlgCamera*)it->second->m_pDlg;
			it->second->m_pDlg = nullptr;
			delete it->second;
			it->second = nullptr;
			it = m_mapConfigInfo.erase(it);
		}
	}

	m_mapConfigInfo.clear();
}

inline void CDlgConfig::initResource()
{

}

inline void CDlgConfig::uninitResource()
{

}

void CDlgConfig::OnClose()
{
	uninitCtrl();
	uninitResource();

	CDialogEx::OnCancel();
}

void CDlgConfig::OnShowWindow(BOOL bShow, UINT nStatus)
{
	initCtrl();

	CDialogEx::OnShowWindow(bShow, nStatus);
}

void CDlgConfig::OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	
	int nIndex = m_TabCtrlConfig.GetCurSel();
	CAgoraFormatStr::AgoraOutDebugStr(_T("select nIndex : %d"),nIndex);
	m_curConfigType = (eTagConfigType)nIndex;
	m_curConfigData = (m_mapConfigInfo[m_curConfigType]);

	for (std::map<eTagConfigType, LPAG_CONFIG>::iterator it = m_mapConfigInfo.begin(); m_mapConfigInfo.end() != it; it++){

		((CWnd*)(it->second->m_pDlg))->ShowWindow(SW_HIDE);
	}

	((CWnd*)(m_curConfigData->m_pDlg))->ShowWindow(SW_SHOW);
}


void CDlgConfig::OnBnDoubleclickedButtonSaveall()
{
	// TODO:  在此添加控件通知处理程序代码
	for (std::map<eTagConfigType, LPAG_CONFIG>::iterator it = m_mapConfigInfo.begin(); m_mapConfigInfo.end() != it; it++){
		switch (it->first)
		{
		case eTagConfigType::eTagConfigType_BaseInfo:
			((CDlgConfigBaseInfo*)(it->second->m_pDlg))->SaveConfigInfo();
			break;
		case eTagConfigType::eTagConfigType_Instance1:
		case eTagConfigType::eTagConfigType_Instance2:
		case eTagConfigType::eTagConfigType_Instance3:
		case eTagConfigType::eTagConfigType_Instance4:
		case eTagConfigType::eTagConfigType_Instance5:
		case eTagConfigType::eTagConfigType_Instance6:
		case eTagConfigType::eTagConfigType_Instance7:
		case eTagConfigType::eTagConfigType_Instance8:
		case eTagConfigType::eTagConfigType_Instance9:
		case eTagConfigType::eTagConfigType_Instance10:
		case eTagConfigType::eTagConfigType_Instance11:
		case eTagConfigType::eTagConfigType_Instance12:
		case eTagConfigType::eTagConfigType_Instance13:
		case eTagConfigType::eTagConfigType_Instance14:
			((CDlgCamera*)(it->second->m_pDlg))->SaveConfigInfo();
			break;
		default:
			break;
		}
	}

	return CDialogEx::OnCancel();
}

BOOL CDlgConfig::PreTranslateMessage(MSG* pMsg)
{
	HWND wnd = (GetDlgItem(IDC_BUTTON_SaveAll))->m_hWnd;
	if (pMsg->hwnd == wnd && pMsg->message == WM_LBUTTONDOWN){
		OnBnDoubleclickedButtonSaveall();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}