
// WawajiRunnerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WawajiRunner.h"
#include "WawajiRunnerDlg.h"
#include "afxdialogex.h"
#include "../WawajiDemo/commonFun.h"
#include "../WawajiDemo/FileIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#define TIMER_IDEVENT_RESTARTTIMER 1
#define TIMER_IDEVENT_RECHECK 2
#define TIMER_INTERVAL_RESTARTTIMER 1000
#define TIMER_INTERVAL_RECHECK 5000
CConfigWawaji gWawajiConfig;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWawajiRunnerDlg �Ի���



CWawajiRunnerDlg::CWawajiRunnerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWawajiRunnerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWawajiRunnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_RESTART, m_DataTimeCtlRestart);
}

BEGIN_MESSAGE_MAP(CWawajiRunnerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_RESTART, &CWawajiRunnerDlg::OnDtnDatetimechangeDatetimepickerRestart)
END_MESSAGE_MAP()


// CWawajiRunnerDlg ��Ϣ�������

BOOL CWawajiRunnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	initExe();
	SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);
	WinExec("WawajiDemo.exe", SW_HIDE);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWawajiRunnerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWawajiRunnerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CWawajiRunnerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_IDEVENT_RESTARTTIMER == nIDEvent)
	{
		bool res = ((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->GetCheck();
		if (res){
			SYSTEMTIME stTemp;
			GetLocalTime(&stTemp);
			if (stTemp.wHour == m_TimerRestart.wHour
				&& stTemp.wMinute == m_TimerRestart.wMinute
				&& stTemp.wSecond == m_TimerRestart.wSecond){

				KillTimer(TIMER_IDEVENT_RECHECK);
				int num = 0;
				closeProcess("WawajiDemo.exe",num);
				if (2 == num){

					gWawajiConfig.setDeviceChoose(INI_DeviceInfoFront, "0");
					gWawajiConfig.setDeviceState(INI_DeviceInfoFront, "0");
					gWawajiConfig.setDeviceState(INI_DeviceInfoBack, "0");
					gWawajiConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
				}

				//AfxMessageBox(_T("������������"));
				SetTimer(TIMER_IDEVENT_RECHECK, TIMER_INTERVAL_RECHECK, nullptr);
			}
		}
	}
	
	if (TIMER_IDEVENT_RECHECK == nIDEvent)
	{
		std::string curExeName = "WawajiDemo.exe";
		int processNum = getProcessIdMutil(curExeName);
		if (2 > processNum){

			WinExec("WawajiDemo.exe", SW_HIDE);
		}

		bool frontStatus = str2int(gWawajiConfig.getDeviceState(INI_DeviceInfoFront));
		if (frontStatus){
			GetDlgItem(IDC_EDIT_FRONT)->SetWindowTextW(_T("������"));
		}
		else{
			GetDlgItem(IDC_EDIT_FRONT)->SetWindowTextW(_T("δ����"));
		}

		bool backStatus = str2int(gWawajiConfig.getDeviceState(INI_DeviceInfoBack));
		if (backStatus){
			GetDlgItem(IDC_EDIT_BACK)->SetWindowTextW(_T("������"));
		}
		else{
			GetDlgItem(IDC_EDIT_BACK)->SetWindowTextW(_T("δ����"));
		}

		processNum = getProcessIdMutil(curExeName);
		if (2 >= processNum){
			if (frontStatus && backStatus){
				GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(_T("ǰ������Ѿ�����..."));
			}
			else if (frontStatus && !backStatus){
				GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(_T("׼���������ó���.."));
			}
			else if (!frontStatus && backStatus){
				GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(_T("׼������ǰ�ó���.."));
			}
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWawajiRunnerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWawajiRunnerDlg::initExe()
{
	GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetWindowTextW(_T("��������.."));
	GetDlgItem(IDC_EDIT_FRONT)->SetWindowText(_T("δ����"));
	GetDlgItem(IDC_EDIT_BACK)->SetWindowText(_T("δ����"));

	GetDlgItem(IDC_EDIT_FRONT)->SetFocus();
	GetDlgItem(IDC_EDIT_BACK)->SetFocus();
	GetDlgItem(IDC_STATIC_TIMERSTATUS)->SetFocus();

	registerStartUp();

	std::string restartTimer = gWawajiConfig.getRestartTimer();
	std::string restartTimerStatus = gWawajiConfig.getRestartTimerStatus();
	((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->SetCheck(str2int(restartTimerStatus));
	getTimerStartIni(m_TimerRestart, restartTimer);
	m_DataTimeCtlRestart.SetTime(m_TimerRestart);

	if ("1" == restartTimerStatus)
	SetTimer(TIMER_IDEVENT_RESTARTTIMER, TIMER_INTERVAL_RESTARTTIMER, nullptr);
}

void CWawajiRunnerDlg::getTimerStartIni(SYSTEMTIME &st,const std::string &timeStr)
{
	int nindexleft = timeStr.find(":");
	int nindexright = timeStr.rfind(":");
	DWORD dhour = str2int(timeStr.substr(0, nindexleft));
	DWORD dmin = str2int(timeStr.substr(nindexleft + 1, nindexright));
	DWORD dsec = str2int(timeStr.substr(nindexright + 1, timeStr.length() - 1));
	
	GetLocalTime(&st);
	st.wHour = dhour;
	st.wMinute = dmin;
	st.wSecond = dsec;
}

void CWawajiRunnerDlg::uninitExe()
{

}

void CWawajiRunnerDlg::OnDtnDatetimechangeDatetimepickerRestart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	bool isRestartTimer = ((CButton*)(GetDlgItem(IDC_CHECK_TIMER_RESTART)))->GetCheck();
	if (isRestartTimer){

		m_TimerRestart = pDTChange->st;
		CString restartFormat;
		restartFormat.Format(_T("%02d:%02d:%02d"), pDTChange->st.wHour, pDTChange->st.wMinute, pDTChange->st.wSecond);
		gWawajiConfig.setRestartTimerStatus("1");
		gWawajiConfig.setRestartTimer(cs2s(restartFormat));
	}
}
