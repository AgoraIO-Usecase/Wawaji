
// WawajiStreamInstanceDlg.h : 头文件
//

#pragma once

#include "MyCmdLineInfo.h"

// CWawajiStreamInstanceDlg 对话框
class CWawajiStreamInstanceDlg : public CDialogEx
{
// 构造
public:
	CWawajiStreamInstanceDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WAWAJISTREAMINSTANCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT OnRejoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT OnWarning(WPARAM wParam, LPARAM lParam);
	LRESULT OnError(WPARAM wParam, LPARAM lParam);
	LRESULT OnAudioQuality(WPARAM wParam, LPARAM lParam);
	LRESULT OnAudioVolumeIndication(WPARAM wParam, LPARAM lParam);

	LRESULT OnLeaveChannel(WPARAM wParam, LPARAM lParam);
	LRESULT OnRtcStats(WPARAM wParam, LPARAM lParam);
	LRESULT OnMediaEngineEvent(WPARAM wParam, LPARAM lParam);

	LRESULT OnAudioDeviceStateChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoDeviceStateChanged(WPARAM wParam, LPARAM lParam);

	LRESULT OnRequestChannelKey(WPARAM wParam, LPARAM lParam);
	LRESULT OnLastmileQuality(WPARAM wParam, LPARAM lParam);
	LRESULT OnFirstLocalVideoFrame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFirstRemoteVideoDecoded(WPARAM wParam, LPARAM lParam);
	LRESULT OnFirstRemoteVideoFrame(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserJoined(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserOffline(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserMuteAudio(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserMuteVideo(WPARAM wParam, LPARAM lParam);
	LRESULT OnApiCallExecuted(WPARAM wParam, LPARAM lParam);

	LRESULT OnLocalVideoStats(WPARAM wParam, LPARAM lParam);
	LRESULT OnRemoteVideoStats(WPARAM wParam, LPARAM lParam);
	LRESULT OnCameraReady(WPARAM wParam, LPARAM lParam);
	LRESULT OnVideoStopped(WPARAM wParam, LPARAM lParam);
	LRESULT OnConnectionLost(WPARAM wParam, LPARAM lParam);
	LRESULT OnConnectionInterrupted(WPARAM wParam, LPARAM lParam);

	LRESULT OnUserEnableVideo(WPARAM wParam, LPARAM lParam);

	LRESULT OnStartRecordingService(WPARAM wParam, LPARAM lParam);
	LRESULT OnStopRecordingService(WPARAM wParam, LPARAM lParam);
	LRESULT OnRefreshRecordingServiceStatus(WPARAM wParam, LPARAM lParam);

protected:
	
	inline void initData();
	inline void initCtrl();
	inline void uninitCtrl();

	inline void initAgoraMedia();
	inline void uninitAgoraMedia();

	inline void joinChannel();

	inline void parseCmdLine();

private:

	int m_nProfileValue[32];

	std::string m_strInstance;
	eTagConfigType m_eInstanceType;
	std::string m_strAppId;
	std::string m_strAppcertificateId;
	std::string m_strChannel;
	UINT m_uLoginUid;
	std::string m_strCameraName;

	CAgoraObject* m_lpAgoraObject;
	IRtcEngine* m_lpRtcEngine;
	HWND m_hMainUIItemWnd;
	HWND m_hMainUIWnd;
	CMyCmdLineInfo m_cmdInfo;
};


