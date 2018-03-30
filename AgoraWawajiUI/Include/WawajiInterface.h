#pragma once

#include <iostream>
using namespace std;

namespace AgoraWawaji{

#define MAX_Camera_Count 2

	enum eTagConfigType{
		eTagConfigType_NULL = -1,
		eTagConfigType_BaseInfo,
		eTagConfigType_Instance1,
		eTagConfigType_Instance2,
		eTagConfigType_Instance3,
		eTagConfigType_Instance4,
		eTagConfigType_Instance5,
		eTagConfigType_Instance6,
		eTagConfigType_Instance7,
		eTagConfigType_Instance8,
		eTagConfigType_Instance9,
		eTagConfigType_Instance10,
		eTagConfigType_Instance11,
		eTagConfigType_Instance12,
		eTagConfigType_Instance13,
		eTagConfigType_Instance14,
		eTagConfigType_Instance15,

		eTagConfigType_UNKNOWN = 0xff
	};

	typedef struct eTagConfig{
		std::string szBufferDesc;
		void* m_pDlg;
	}AG_CONFIG, *PAG_CONFIG, *LPAG_CONFIG;


	enum enumWawajiMsgType{
		WawajiMsgType_NULL = WM_USER,
		WawajiMsgType_Config,


		WawajiMsgType_UNKNOWN = 0xff,
	};

	typedef struct eTagWawajiStreamInfo{
		eTagConfigType InstanceType;
		uid_t uRemoteUid;
		DWORD dProcessId;
		BOOL bIsRunning;
		HWND wnd;

	}AG_WAWAJI_STREAMINFO,*PAG_WAWAJI_STREAMINFO,*LPAG_WAWAJI_STREAMINFO;

	enum enumWawajiEventType{
		EventType_TIMER_EVENT_NULL = 0,
		EventType_TIMER_EVENT_CHECK_CAMERAPARAM,
		EventType_TIMER_EVENT_CHECK_BASEINFOPARAM,
		EventType_TIMER_EVENT_Runnin_Stream,
		EventType_TIMER_EVENT_UpTime,

		EventType_TIMER_EVENT_UNKNOWN,
	};

	typedef struct eTagWawajiConfig{
		eTagConfigType configInstance;
		bool isRunStream;

	}AG_WAWAJI_CONFIG,*PAG_WAWAJI_CONFIG,*LPAG_WAWAJI_CONFIG;

}