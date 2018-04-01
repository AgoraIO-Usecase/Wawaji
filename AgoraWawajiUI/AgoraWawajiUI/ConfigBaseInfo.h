#pragma once


// CDlgConfigBaseInfo �Ի���

class CDlgConfigBaseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfigBaseInfo)

public:
	CDlgConfigBaseInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfigBaseInfo();

	BOOL SaveConfigInfo();
// �Ի�������
	enum { IDD = IDD_DIALOG_BaseInfo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
	
	inline void initData();
	inline void initCtrl();
	inline void uninitCtrl();
	
	inline void getTimerStartIni(SYSTEMTIME &st, const std::string &timeStr);

private:

	int m_nProfileValue[32];

	CEdit m_EditAppId;
	CEdit m_EditAppCertId;
	CEdit m_EditChannelName;
	CComboBox m_comVideoProfile;
	CEdit m_EditAutoClearLog;
	CComboBox m_comLanguage;
	CButton m_checkLocalPreview;

	CDateTimeCtrl m_DataTimeCtlRestart;
	SYSTEMTIME m_stRestart;

public:
	afx_msg void OnBnClickedButtonSave();
};
