#pragma once


// CDlgConfig 对话框

#include "AgoraCameraManager.h"
class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_Config };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

	inline void initCtrl();
	inline void uninitCtrl();
	
	inline void initResource();
	inline void uninitResource();

private:

	CTabCtrl m_TabCtrlConfig;

	eTagConfigType m_curConfigType;
	LPAG_CONFIG m_curConfigData;
	std::map<eTagConfigType, LPAG_CONFIG> m_mapConfigInfo;
	CAgoraCameraManager m_AgoraCameraManager;


public:
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnDoubleclickedButtonSaveall();
};
