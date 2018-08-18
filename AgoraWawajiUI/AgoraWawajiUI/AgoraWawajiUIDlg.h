
// AgoraWawajiUIDlg.h : 头文件
//

#pragma once

#include "DlgConfig.h"
#include <thread>
/*class CDlgConfig;*/

// CAgoraWawajiUIDlg 对话框
class CAgoraWawajiUIDlg : public CDialogEx
{
// 构造
public:
	CAgoraWawajiUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AGORAWAWAJIUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	inline void InitCtrl();	
	inline void InitCtrlTxt();
	inline void unInitCtrl();

	inline void switchLang();

	inline void initAgoraMedia();
	inline void uninitAgoaMeida();

	inline void DrawClient(CDC *lpDC);
	inline void AddTxt(LPCTSTR lpFormat,...);

	inline void checkBaseInfo();
	inline void checkCameraInfo();

	inline void StartWawajiMonitor();
	inline void StopWawajiMonitor();
	inline void StartRunWawajiStream();

	inline void reserveStream(const std::string &Instance);

	inline void getInvalidFileList(std::vector<CString> &vecFileList, const CString&strFilePath, int IntervalTime);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonStart();

	//AgoraMsg
	LRESULT OnJoinChannelSuccess(WPARAM wParam,LPARAM lParam);
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

	//WawajiMsg
	LRESULT OnConfigParamSave(WPARAM wParam,LPARAM lParam);
	LRESULT OnInstanceRemoteVideoStats(WPARAM wParam,LPARAM lParam);

	void RestartWawaji(bool bInit = false);
private:
	CStatic m_CtlCamera1;
	CStatic m_CtlCamera2;
	CRect m_MainUIClient;
	
	CStatic m_CtlUID1Value;
	CStatic m_CtlCamera1Vaule;
	CStatic m_CtlUID2Value;
	CStatic m_CtlCamera2Value;

	CStatic m_CtlAppIdKey;
	CEdit m_EditAppValue;
	CStatic m_CtlAppCertificateKey;
	CEdit m_EditAppCertificateValue;
	CStatic m_CtlChannelKey;
	CEdit m_EditChannelValue;
	CStatic m_CtlVideoProfileKey;
	CComboBox m_ComboVideoProfileValue;
	CStatic m_CtlUpTimeKey;
	CStatic m_CtlUpTimeValue;

	CButton m_BtnSettings;
	CButton m_BtnStart;
	CButton m_BtnRestart;
	CButton m_BtnUpLoadLog;
	CStatic m_CtlSdkVersion;
	CListBox m_listLog;

	std::string m_strAppId;
	std::string m_strAppcertId;
	std::string m_strChannel;
	std::string m_strVideoProfile;
	std::string m_strUpTime;
	
	CAgoraObject* m_lpAgoraObject;
	IRtcEngine* m_lpRtcEngine;
	CImageList m_imgNetQuality;
	int m_nLastmileQuality;
	BOOL m_bParamStatus;
	int m_nClearLog;

	CDlgConfig m_DlgConfig;

	std::string m_strAgoraWawajiMainUILogPath;
	std::map<std::string /*strInstance*/, LPAG_WAWAJI_STREAMINFO /*instanceProcess*/> m_mapStream;
	std::map<uid_t /*uRemoteId*/, std::string /*strInstance*/> m_mapUidMgr;

	BOOL m_bIsAutomatic;
	uid_t m_uMonitorUId;
	BOOL m_bIsJoinChannel;
	long m_ltimeInterval;
	
	int nIDEventRestart = 1000;
public:
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnBnClickedButtonUploadlogs();
};
