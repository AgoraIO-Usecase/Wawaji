#pragma once
#include "afxwin.h"
#include "AGEdit.h"

// CDlgVideoPreview 对话框

class CAgoraCameraManager;
class CDlgVideoPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideoPreview)

public:
	CDlgVideoPreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideoPreview();

	void setChildInfo(const CString processName, CAgoraCameraManager* pCameraManager);
	void showChildWnd(bool Enable = true);
	void saveConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHILD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	void initCtrl();
	void uninitCtrl();
	bool getVideoParam(CString sSrc, int &width, int &height, int &fps, int &bitrate);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonChildApply();
	afx_msg void OnBnClickedButtonVideopreview();

private:
	CAgoraCameraManager *m_pAgoraCameraManager;
	CString m_processIdName;
	CString m_curDeviceID;

	CAGEdit m_edtRtmpWidth;
	CAGEdit m_edtRtmpHeight;
	CAGEdit m_edtRtmpFps;
	CAGEdit m_edtRtmpBitrate;
	CAGEdit m_edtRtmpUrl;
	CComboBox m_comVideoSolution;
	CButton m_ckRtmp;
	CButton m_ckLeftRotate90;
	CButton m_ckSwitchWH;
	LPTSTR m_szProfileDes[32];
};
