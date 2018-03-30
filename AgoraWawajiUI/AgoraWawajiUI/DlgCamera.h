#pragma once

#include "AgoraCameraManager.h"
// CDlgCamera 对话框

class CDlgCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCamera)

public:
	CDlgCamera(CString strInstance,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCamera();

	BOOL SaveConfigInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CameraConfig };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()

	inline void initCtrl();
	inline void uninitCtrl();

	inline void initData();

private:

	CStatic m_ctlInstance;
	CButton m_checkEnable;
	CComboBox m_comCameraName;
	CButton m_checkVerCamera;
	CButton m_checkSwitchWidthHeight;
	CButton m_checkRtmpSave;

	CEdit m_editRtmpWidth;
	CEdit m_editRtmpHeight;
	CEdit m_editRtmpFps;
	CEdit m_editRtmpBitrate;
	CEdit m_editRtmpUrl;
	CEdit m_editLoginUID;

	CStatic m_ctlLocalVideoPreview;

	CString m_InstanceDesc;

	CAgoraObject* m_lpAgoraObject;
	IRtcEngine* m_lpRtcEngine;
	CAgoraCameraManager m_AgoraCameraManager;

	int m_nCurIndex;
public:
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheckSwitchwidthheight();
	afx_msg void OnBnClickedButtonSave();
};
