// SetupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AgoraWawajiDemo.h"
#include "SetupDlg.h"
#include "afxdialogex.h"
#include "commonFun.h"
#include "InfoManager.h"

// CSetupDlg �Ի���

IMPLEMENT_DYNAMIC(CSetupDlg, CDialogEx)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupDlg::IDD, pParent)
{

}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNCANCEL_SETUP, m_btnCancel);
	DDX_Control(pDX, IDC_BTNCONFIRM_SETUP, m_btnConfirm);
	DDX_Control(pDX, IDC_CKSAVESETTING_SETUP, m_ckSaveSettings);
	DDX_Control(pDX, IDC_CKSWPWH_SETUP, m_ckSwapWH);
	DDX_Control(pDX, IDC_CKFULLBAND_SETUP, m_ckFullBand);
	DDX_Control(pDX, IDC_CKSTEREO_SETUP, m_ckStereo);
	DDX_Control(pDX, IDC_CKFULLBITRATE_SETUP, m_ckFullBitrate);
	DDX_Control(pDX, IDC_CKENABLEEXT_SETUP, m_ckVideoExt);
	DDX_Control(pDX, IDC_EDWIDTH_SETUP, m_edWidth);
	DDX_Control(pDX, IDC_EDHEIGHT_SETUP, m_edHeight);
	DDX_Control(pDX, IDC_EDFRAME_SETUP, m_edFrame);
	DDX_Control(pDX, IDC_EDBITRATE_SETUP, m_edBitrate);
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNCONFIRM_SETUP, &CSetupDlg::OnBnClickedBtnconfirmSetup)
//	ON_CBN_SELCHANGE(IDC_CMBRES_SETUP, &CSetupDlg::OnCbnSelchangeCmbresSetup)
//	ON_CBN_SELCHANGE(IDC_CMBCODEC_SETUP, &CSetupDlg::OnCbnSelchangeCmbresSetup)

	ON_WM_HSCROLL()
	ON_WM_LBUTTONDBLCLK()

	ON_BN_CLICKED(IDC_BUTTON1, &CSetupDlg::OnBnClickedBtncancelSetup)
END_MESSAGE_MAP()


// CSetupDlg ��Ϣ�������


BOOL CSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ftHead.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftDes.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_ftBtn.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_penFrame.CreatePen(PS_SOLID, 1, RGB(0xD8, 0xD8, 0xD8));
	m_cbxVideoProfile.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, CRect(0, 0, 300, 40), this, IDC_CMBVDOPRF_SETUP);
	SetBackgroundColor(RGB(0xFF, 0xFF, 0xFF), TRUE);

    InitData();
    InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CSetupDlg::InitCtrls()
{
	CRect ClientRect;

	MoveWindow(0, 0, 320, 450, 1);
	GetClientRect(&ClientRect);

	int nResolutionIndex = 0;
	CString str;
	
	m_cbxVideoProfile.MoveWindow(210, 80, 300, 22, TRUE);
	m_cbxVideoProfile.SetFont(&m_ftDes);
	m_cbxVideoProfile.SetButtonImage(IDB_CMBBTN, 12, 12, RGB(0xFF, 0x00, 0xFF));
	m_cbxVideoProfile.SetFaceColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_cbxVideoProfile.SetListMaxHeight(600);

	m_edWidth.SetFont(&m_ftDes);
	m_edWidth.SetWindowText(_T("640"));
	m_edWidth.MoveWindow(80, 150, 80, 24, TRUE);
	m_edHeight.SetFont(&m_ftDes);
	m_edHeight.SetWindowText(_T("480"));
	m_edHeight.MoveWindow(165, 150, 80, 24, TRUE);
	m_edFrame.SetFont(&m_ftDes);
	m_edFrame.SetWindowText(_T("10"));
	m_edFrame.MoveWindow(250, 150, 80, 24, TRUE);
	m_edBitrate.SetFont(&m_ftDes);
	m_edBitrate.SetWindowText(_T("300"));
	m_edBitrate.MoveWindow(335, 150, 80, 24, TRUE);

	m_ckVideoExt.MoveWindow(80, 180, 200, 20, TRUE);
	m_ckSwapWH.MoveWindow(80, 120, 20, 20, TRUE);
	m_ckSaveSettings.MoveWindow(80, ClientRect.Height() - 95, 20, 20, TRUE);

	m_ckFullBand.MoveWindow(80, 220, 20, 20, TRUE);
	m_ckStereo.MoveWindow(80, 240, 20, 20, TRUE);
	m_ckFullBitrate.MoveWindow(80, 260, 20, 20, TRUE);

	m_btnCancel.MoveWindow(ClientRect.Width() / 2 - 93, ClientRect.Height() - 58, 174, 36, TRUE);

	m_btnConfirm.MoveWindow(ClientRect.Width() / 2 + 93, ClientRect.Height() - 58, 174, 36, TRUE);

	for (int nIndex = 0; nIndex < 31; nIndex++) {
		m_cbxVideoProfile.InsertString(nIndex, m_szProfileDes[nIndex]);
		m_cbxVideoProfile.SetItemData(nIndex, (DWORD_PTR)m_nProfileValue[nIndex]);
	}

	m_btnCancel.SetBorderColor(RGB(0xD8, 0xD8, 0xD8), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));
	m_btnCancel.SetBackColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_btnCancel.SetTextColor(RGB(0x55, 0x58, 0x5A), RGB(0x00, 0xA0, 0xE9), RGB(0x00, 0xA0, 0xE9), RGB(0xCC, 0xCC, 0xCC));

	m_btnConfirm.SetBackColor(RGB(0, 160, 239), RGB(0, 160, 239), RGB(0, 160, 239), RGB(192, 192, 192));
	m_btnConfirm.SetFont(&m_ftBtn);
	m_btnConfirm.SetTextColor(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xC8, 0x64), RGB(0xFF, 0xC8, 0x64), RGB(0xCC, 0xCC, 0xCC));
	m_btnConfirm.SetWindowText(LANG_STR("IDS_SET_BTCONFIRM"));

	std::string curSection = getInfoManager()->getCurSection();
	std::string ResolutionSave = getInfoManager()->getConfig()->getResolutionSave(curSection);
	nResolutionIndex = str2int(getInfoManager()->getConfig()->getResolutionIndex(curSection));
	if ("1" == ResolutionSave)
	{
		m_ckSaveSettings.SetCheck(TRUE);
	}
	else
	{
		m_ckSaveSettings.SetCheck(FALSE);
		nResolutionIndex = 15;
	}
	m_cbxVideoProfile.SetCurSel(nResolutionIndex);
}

void CSetupDlg::InitData()
{
	m_szProfileDes[0] = _T("160x120 15fps 65kbps");
	m_nProfileValue[0] = 0;
	m_szProfileDes[1] = _T("120x120 15fps 50kbps");
	m_nProfileValue[1] = 2;

	m_szProfileDes[2] = _T("320x180 15fps 140kbps");
	m_nProfileValue[2] = 10;
	m_szProfileDes[3] = _T("180x180 15fps 100kbps");
	m_nProfileValue[3] = 12;
	m_szProfileDes[4] = _T("240x180 15fps 120kbps");
	m_nProfileValue[4] = 13;

	m_szProfileDes[5] = _T("320x240 15fps 200kbps");
	m_nProfileValue[5] = 20;
	m_szProfileDes[6] = _T("240x240 15fps 140kbps");
	m_nProfileValue[6] = 22;
	m_szProfileDes[7] = _T("424x240 15fps 220kbps");
	m_nProfileValue[7] = 23;

	m_szProfileDes[8] = _T("640x360 15fps 400kbps");
	m_nProfileValue[8] = 30;
	m_szProfileDes[9] = _T("360x360 15fps 260kbps");
	m_nProfileValue[9] = 32;
	m_szProfileDes[10] = _T("640x360 30fps 600kbps");
	m_nProfileValue[10] = 33;
	m_szProfileDes[11] = _T("360x360 30fps 400kbps");
	m_nProfileValue[11] = 35;
	m_szProfileDes[12] = _T("480x360 15fps 320kbps");
	m_nProfileValue[12] = 36;
	m_szProfileDes[13] = _T("480x360 30fps 490kbps");
	m_nProfileValue[13] = 37;
	m_szProfileDes[14] = _T("640x360 15fps 800kbps");
	m_nProfileValue[14] = 38;

	m_szProfileDes[15] = _T("640x480 15fps 500kbps");
	m_nProfileValue[15] = 40;
	m_szProfileDes[16] = _T("480x480 15fps 400kbps");
	m_nProfileValue[16] = 42;
	m_szProfileDes[17] = _T("640x480 30fps 750kbps");
	m_nProfileValue[17] = 43;
	m_szProfileDes[18] = _T("480x480 30fps 600kbps");
	m_nProfileValue[18] = 44;
	m_szProfileDes[19] = _T("848x480 15fps 610kbps");
	m_nProfileValue[19] = 47;
	m_szProfileDes[20] = _T("848x480 30fps 930kbps");
	m_nProfileValue[20] = 48;

	m_szProfileDes[21] = _T("1280x720 15fps 1130kbps");
	m_nProfileValue[21] = 50;
	m_szProfileDes[22] = _T("1280x720 30fps 1710kbps");
	m_nProfileValue[22] = 52;
	m_szProfileDes[23] = _T("960x720 15fps 910kbps");
	m_nProfileValue[23] = 54;
	m_szProfileDes[24] = _T("960x720 30fps 1380kbps");
	m_nProfileValue[24] = 55;

	m_szProfileDes[25] = _T("1920x1080 15fps 2080kbps");
	m_nProfileValue[25] = 60;
	m_szProfileDes[26] = _T("1920x1080 30fps 3150kbps");
	m_nProfileValue[26] = 62;
	m_szProfileDes[27] = _T("1920x1080 60fps 4780kbps");
	m_nProfileValue[27] = 64;
	m_szProfileDes[28] = _T("2560x1440 30fps 4850kbps");
	m_nProfileValue[28] = 66;
	m_szProfileDes[29] = _T("3560x1440 60fps 7350kbps");
	m_nProfileValue[29] = 67;

	m_szProfileDes[30] = _T("3840x2160 30fps 8190kbps");
	m_nProfileValue[30] = 70;
	m_szProfileDes[31] = _T("3840x2160 60fps 13500kbps");
	m_nProfileValue[31] = 72;
}

void CSetupDlg::DrawClient(CDC *lpDC)
{
	CRect	rcText;
	CRect	rcClient;
	LPCTSTR lpString = NULL;

	GetClientRect(&rcClient);

	CFont *lpDefFont = lpDC->SelectObject(&m_ftHead);
	CPen  *lpDefPen = lpDC->SelectObject(&m_penFrame);

	rcText.SetRect(rcClient.Width() / 2 - 188, 75, rcClient.Width() / 2 + 172, 107);
	lpDC->RoundRect(&rcText, CPoint(32, 32));

	lpDC->SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	lpDC->SetTextColor(RGB(0xD8, 0xD8, 0xD8));

	lpDC->SetTextColor(RGB(0x44, 0x45, 0x46));
	lpString = LANG_STR("IDS_SET_RESOLUTION");
	lpDC->TextOut(80, 83, lpString, _tcslen(lpString));
	
	lpString = LANG_STR("IDS_SET_SWAPWH");
	lpDC->TextOut(100, 120, lpString, _tcslen(lpString));

	lpString = LANG_STR("IDS_SET_FULLBAND");
	lpDC->TextOut(100, 220, lpString, _tcslen(lpString));
	lpString = LANG_STR("IDS_SET_STEREO");
	lpDC->TextOut(100, 240, lpString, _tcslen(lpString));
	lpString = LANG_STR("IDS_SET_FULLBITRATE");
	lpDC->TextOut(100, 260, lpString, _tcslen(lpString));


	lpString = LANG_STR("IDS_SET_SAVESETTING");
	lpDC->TextOut(100, rcClient.Height() - 95, lpString, _tcslen(lpString));

	lpDC->SelectObject(lpDefPen);
	lpDC->SelectObject(lpDefFont);
}

void CSetupDlg::OnBnClickedBtnconfirmSetup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetParent()->SendMessage(WM_GOBACK, 0, 0);
	
	std::string curSection = getInfoManager()->getCurSection();
	if (m_ckSaveSettings.GetCheck() == TRUE) {
		getInfoManager()->getConfig()->setResolutionSave(curSection, "1");
		getInfoManager()->getConfig()->setResolutionIndex(curSection, int2str(m_cbxVideoProfile.GetCurSel()));
	}
	else
	{
		getInfoManager()->getConfig()->setResolutionSave(curSection, "0");
	}

	BOOL bFullBand = m_ckFullBand.GetCheck();
	BOOL bStereo = m_ckStereo.GetCheck();
	BOOL bFullBitrate = m_ckFullBitrate.GetCheck();

//	CAgoraObject::GetAgoraObject()->SetHighQualityAudio(bFullBand, bStereo, bFullBitrate);
}

void CSetupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	DrawClient(&dc);
}

int CSetupDlg::GetVideoSolution()
{
    int nIndex = m_cbxVideoProfile.GetCurSel();
    return (int)m_cbxVideoProfile.GetItemData(nIndex);
}

void CSetupDlg::SetVideoSolution(int nIndex)
{
	m_cbxVideoProfile.SetCurSel(nIndex);
}

CString CSetupDlg::GetVideoSolutionDes()
{
	CString str;
	CString strWidth;
	CString strHeight;
	CString strFrame;
	CString strBitrate;

	if (m_ckVideoExt.GetCheck()) {
		m_edWidth.GetWindowText(strWidth);
		m_edHeight.GetWindowText(strHeight);
		m_edFrame.GetWindowText(strFrame);
		m_edBitrate.GetWindowText(strBitrate);
		str.Format(_T("%s*%s,%sfps,%skbps"), strWidth, strHeight, strFrame, strBitrate);
	}
	else {
		int nIndex = m_cbxVideoProfile.GetCurSel();
		if (nIndex == -1)
			nIndex = 0;

		str = m_szProfileDes[nIndex];
	}

	return str;
}

int CSetupDlg::getSolutionWidth()
{
	if (!m_ckVideoExt.GetCheck())
	{
		int indexSrc = m_cbxVideoProfile.GetCurSel();
		CString videoProfileDesc = m_szProfileDes[indexSrc];

		int spaceIndex = videoProfileDesc.Find(_T("x"), 0);
		CString widthStr = videoProfileDesc.Mid(0, spaceIndex);
		return str2int(cs2s(widthStr));
	}
	else
	{
		CString sWidth;
		m_edWidth.GetWindowText(sWidth);

		return str2int(cs2s(sWidth));

	}
}

int CSetupDlg::getSolutionHeight()
{
	if (m_ckVideoExt.GetCheck())
	{
		CString sHeight;
		m_edHeight.GetWindowTextW(sHeight);

		return str2int(cs2s(sHeight));
	}
	else
	{
		int indexSrc = m_cbxVideoProfile.GetCurSel();
		CString videoProfileDesc = m_szProfileDes[indexSrc];

		int spaceInex = videoProfileDesc.Find(_T(" "), 0);
		int xindex = videoProfileDesc.Find(_T("x"),0);
		CString widthStr = videoProfileDesc.Mid(xindex+1, spaceInex - xindex);
		return str2int(cs2s(widthStr));
	}
}

void CSetupDlg::SetVideoProfile()
{
	CString str;
	CString strWidth;
	CString strHeight;
	CString strFrame;
	CString strBitrate;

	if (m_ckVideoExt.GetCheck()) {
		UINT nWidth = GetDlgItemInt(IDC_EDWIDTH_SETUP);
		UINT nHeight = GetDlgItemInt(IDC_EDHEIGHT_SETUP);
		UINT nFrameRate = GetDlgItemInt(IDC_EDFRAME_SETUP);
		UINT nBitrate = GetDlgItemInt(IDC_EDBITRATE_SETUP);
		
		CAgoraObject::GetAgoraObject()->SetVideoProfileEx(nWidth, nHeight, nFrameRate, nBitrate);
	}
	else {
		int nIndex = m_cbxVideoProfile.GetCurSel();
		if (nIndex == -1)
			nIndex = 0;

		int nVideoSolution = static_cast<int>(m_cbxVideoProfile.GetItemData(nIndex));
		CAgoraObject::GetEngine()->setVideoProfile((VIDEO_PROFILE_TYPE)nVideoSolution, m_ckSwapWH.GetCheck());
	}
}

void CSetupDlg::SetWHSwap(BOOL bSwap)
{
	m_ckSwapWH.SetCheck(bSwap);
}

BOOL CSetupDlg::IsWHSwap()
{
	return (BOOL)m_ckSwapWH.GetCheck();
}

void CSetupDlg::OnBnClickedBtncancelSetup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetParent()->SendMessage(WM_GOBACK, 0, 0);
}
