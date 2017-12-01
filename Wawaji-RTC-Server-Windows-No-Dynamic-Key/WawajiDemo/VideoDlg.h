#pragma once
#include "AGButton.h"
#include "AGVideoWnd.h"
#include "DeviceDlg.h"
#include "ChatDlg.h"
#include "SEIDlg.h"
#include "AGScreenCaptureDlg.h"

// CVideoDlg 对话框

class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoDlg();

// 对话框数据
	enum { IDD = IDD_VIDEO_DIALOG };

	enum { 
		SCREEN_VIDEO1 = 0,	// 单屏
		SCREEN_VIDEO4,		// 4分屏
		SCREEN_VIDEOMULTI,	// 1大4小
	};

	HWND GetRemoteVideoWnd(int nIndex);
	HWND GetLocalVideoWnd() { return m_wndLocal.GetSafeHwnd(); };

	void RebindVideoWnd();

	void ShowControlButton(BOOL bShow = TRUE);

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus); 
	afx_msg void OnMove(int x, int y);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg LRESULT OnShowModeChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowBig(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedBtnmin();
	afx_msg void OnBnClickedBtnclose();
	afx_msg void OnBnClickedBtnrest();

	afx_msg void OnBnClickedBtnmessage();
	afx_msg void OnBnClickedBtnmode();
	afx_msg void OnBnClickedBtnaudio();
	afx_msg void OnBnClickedBtntip();
	afx_msg void OnBnClickedBtnScreenCapture();
	afx_msg void OnBnClickedBtnMore();

	afx_msg void OnBnClickedBtnfullscr();
	afx_msg void OnCbnSelchangeCmbRole();

	afx_msg void OnBnClickedScreenshare();
	afx_msg void OnBnClickedWindowshare();

	afx_msg void OnBnClickedBtnsetup();
	afx_msg void OnBnClickedBtSEIPush();

	// 用于处理引擎的回调消息
	afx_msg LRESULT OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnEIDFirstLocalFrame(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDFirstRemoteFrameDecoded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserJoined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserOffline(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDConnectionLost(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDVideoDeviceChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoteVideoStat(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnStartRecordingService(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopRecordingService(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnApiCallExecuted(WPARAM wParam, LPARAM lParam);


	//SINGLE
	HRESULT onSingleReconnecting(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleReconnected(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleLoginSuccess(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleLogout(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleLoginFailed(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelJoined(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelJoinFailed(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelLeaved(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelUserJoined(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelUserLeaved(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelUserList(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelQueryUserNumResult(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelQueryUserIsIn(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleChannelAttrUpdated(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteReceived(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteReceivedByPeer(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteAcceptedByPeer(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteRefusedByPeer(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteFailed(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteEndByPeer(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteEndByMyself(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInviteMsg(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageSendError(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageSendProgress(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageSendSuccess(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageAppReceived(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageInstantReceive(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMessageChannelReceive(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleLog(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleInvokeRet(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleMsg(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleUserAttrResult(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleUserAttrAllResult(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleError(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleQueryUserStatusResult(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleDbg(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleBCCall_result(WPARAM wParam, LPARAM lParam);

	HRESULT onSingleSendInstanceMsg(WPARAM wParam, LPARAM lParam);
	HRESULT onSingleSwitchCamera(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

protected:
	BOOL NeedShowSizeBox(CPoint point);
	void EnableSize(BOOL bEnable);
	void CreateScreenShareMenu();
	void CreateMoreMenu();

	void DrawHead(CDC *pDC);

	void InitCtrls();

	void ShowVideo1();
	void ShowVideo4();
	void ShowMulti();

	void ShowButtonsNormal();

	void AdjustButtonsNormal(int cx, int cy);

	void AdjustSizeVideo1(int cx, int cy);
	void AdjustSizeVideo4(int cx, int cy);
	void AdjustSizeVideoMulti(int cx, int cy);

	//SINGLE
public:
	void startSingle(const std::string &appID, const std::string &channelName, const std::string &account);	
	IAgoraAPI* getAgoraInstance();
	static DWORD WINAPI ThreadStartRunning(LPVOID lpParam);
	void switchCamera(const std::string &msg);

private:
	CBrush			m_brHead;
	CFont			m_ftDes;

	CAGButton		m_btnMin;
	CAGButton		m_btnRst;
	CAGButton		m_btnClose;
	
//	CAGButton		m_btnSetup;

	CAGButton       m_btnMessage;
	CAGButton		m_btnMode;
	CAGButton		m_btnAudio;
	CAGButton		m_btnEndCall;
	CComboBox		m_cbxRole;
	CAGButton		m_btnShow;
	CAGButton		m_btnTip;
	CAGButton		m_btnScrCap;

	CAGButton       m_btnMore;

	BOOL			m_bLastStat;
	UINT			m_nScreenMode;
	UINT			m_nBigShowedUID;
	
	CAGVideoWnd		m_wndLocal;
	CAGVideoWnd		m_wndVideo[4];
	CAGVideoWnd		*m_lpBigShowed;

	CDeviceDlg		m_dlgDevice;
	CChatDlg        m_dlgChat;
	CSEIDlg			m_dlgSEI;

	CRect			m_rcVideoArea;
	CRect			m_rcChildVideoArea;

	CBitmap         m_bitMenuDevice;
	CBitmap			m_bitMenuSEI;

	CAGScreenCaptureDlg	m_dlgScreenCapture;

private:	// data	

	typedef struct _AGVIDEO_WNDINFO
	{
		UINT	nUID;
		int		nIndex;

		UINT	nWidth;
		UINT	nHeight;
		int		nBitrate;
		int		nFramerate;
		int		nCodec;

	} AGVIDEO_WNDINFO, *PAGVIDEO_WNDINFO, *LPAGVIDEO_WNDINFO;

	CList<AGVIDEO_WNDINFO>	m_listWndInfo;

	BOOL			m_bRecording;
	BOOL			m_bFullScreen;
	int				m_nTimeCounter;

	//SINGLE

	std::string appId_;
	std::string channelName_;
	std::string appCertificateId_;
	std::string tokenId_;
	std::string userName_;

	std::string callRemoteAccount_;

	IAgoraAPI* pSingleInstance_;
	HANDLE threadStartHandle_;

	bool isLogin_;
	bool isInChannel_;
	bool isAppExit_;
	bool isNeedExitPM_;
};
