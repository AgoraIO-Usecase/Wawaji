
// WawajiRunnerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"


// CWawajiRunnerDlg �Ի���
class CWawajiRunnerDlg : public CDialogEx
{
// ����
public:
	CWawajiRunnerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WAWAJIRUNNER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	void initExe();
	void uninitExe();
	void getTimerStartIni(SYSTEMTIME &st,const std::string &timeStr);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_DataTimeCtlRestart;
	afx_msg void OnDtnDatetimechangeDatetimepickerRestart(NMHDR *pNMHDR, LRESULT *pResult);
	SYSTEMTIME m_TimerRestart;
	afx_msg void OnBnClickedCheckTimerRestart();
	afx_msg void OnBnClickedCheckVideopreview();
};
