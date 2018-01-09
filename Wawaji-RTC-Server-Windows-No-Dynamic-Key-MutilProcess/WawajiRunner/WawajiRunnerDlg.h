
// WawajiRunnerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include "AgoraCameraManager.h"
#include "afxcmn.h"

class CDlgVideoPreview;

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
	void initCtrl();
	void uninitCtrl();
	void getTimerStartIni(SYSTEMTIME &st,const std::string &timeStr);
	void initAgora();
	void uninitAgora();
	void getInvalidFileList(std::vector<CString> &vecFileList, const CString&strFilePath,int IntervalTime);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_DataTimeCtlRestart;
	afx_msg void OnDtnDatetimechangeDatetimepickerRestart(NMHDR *pNMHDR, LRESULT *pResult);
	SYSTEMTIME m_TimerRestart;
	afx_msg void OnBnClickedCheckTimerRestart();
	afx_msg void OnBnClickedCheckVideopreview();

	HRESULT onLastMileQuality(WPARAM wParam, LPARAM lParam);

private:
	std::string m_appId;
	CAgoraObject* m_pAgoraObject;
	IRtcEngine* m_pRtcEngine;
	CAgoraCameraManager m_AgoraCameraManager;
public:
	CTreeCtrl m_TcrlProcessId;
	CDlgVideoPreview *m_pDlgVideoPreview;
	CDlgVideoPreview *m_pDlgCurVideoPreview;
	afx_msg void OnNMDblclkTreeProcessid(NMHDR *pNMHDR, LRESULT *pResult);
	int m_processCount;
	afx_msg void OnBnClickedButtonSaveall();
	std::map<std::string, DWORD > m_mapProcessId;
	afx_msg void OnBnClickedCheckAppcertificated();
};
