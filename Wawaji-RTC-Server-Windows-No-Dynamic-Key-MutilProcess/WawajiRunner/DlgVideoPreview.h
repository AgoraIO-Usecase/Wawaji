#pragma once


// CDlgVideoPreview �Ի���

class CAgoraCameraManager;
class CDlgVideoPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideoPreview)

public:
	CDlgVideoPreview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVideoPreview();

	void setChildInfo(const CString processName, CAgoraCameraManager* pCameraManager);
	void showChildWnd(bool Enable = true);
	void saveConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHILD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	void initCtrl();
	void uninitCtrl();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChildApply();
	afx_msg void OnBnClickedButtonVideopreview();

private:
	CAgoraCameraManager *m_pAgoraCameraManager;
	CString m_processIdName;
	CString m_curDeviceID;
};
