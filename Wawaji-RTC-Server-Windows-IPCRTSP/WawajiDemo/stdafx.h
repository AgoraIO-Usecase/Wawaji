
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#include <Dbt.h>

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#define HAVE_JPEG
#include "LanguageSet.h"
#include "AGMessage.h"

#pragma warning(disable:4800)
#pragma warning(disable:4018)
#pragma warning(disable: 4996)
#include "AgoraObject.h"

#include "AGEventDef.h"
#include <afxdisp.h>
#include <map>

#include <IAgoraRtcEngine.h>
#include <IAgoraMediaEngine.h>
#include "agora_api_win.h"
#pragma comment(lib, "agorartc.lib")
#pragma comment(lib,"agorasdk.lib")
using namespace agora::util;
using namespace agora::media;
using namespace agora_sdk_win;
namespace SingleDesc
{
	enum SingleMsg
	{
		WM_Default = WM_USER,
		WM_Reconnecting,
		WM_Reconnected,
		WM_LoginSuccess,
		WM_LogOut,
		WM_LoginFailed,
		WM_ChannelJoined,
		WM_ChannelJoinedFailed,
		WM_ChannelLeaved,
		WM_ChannelUserJoined,
		WM_ChannelUserLeaved,
		WM_ChannelUserList,
		WM_ChannelQueryUserNumResult,
		WM_ChannelQueryUserIsIn,
		WM_ChannelAttrUpdated,
		WM_InviteReceived,
		WM_InviteReceivedByPeer,
		WM_InviteAcceptedByPeer,
		WM_InviteRefusedByPeer,
		WM_InviteFailed,
		WM_InviteEndByPeer,
		WM_InviteEndByMyself,
		WM_InviteMsg,
		WM_MessageSendError,
		WM_MessageSendProgress,
		WM_MessageSendSuccess,
		WM_MessageAppReceived,
		WM_MessageInstantReceive,
		WM_MessageChannelReceive,
		WM_Log,
		WM_InvokeRet,
		WM_Msg,
		WM_UserAttrResult,
		WM_UserAttrAllResult,
		WM_Error,
		WM_QueryUserStatusResult,
		WM_Dbg,
		WM_BCCall_result,

		//operator
		WM_SingleInstanceSendMsg,
		WM_SingleSwitchCamera,

		WM_UNKWOWN = WM_USER + 0xff
	};

}

using namespace SingleDesc;
#define MAXPATHLEN 10000

extern "C"
{
#include "libavutil\opt.h"
#include "libavutil\imgutils.h"
#include "libavcodec\avcodec.h"
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
#include "libswresample\swresample.h"
}
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "swresample")


namespace LibMedia
{
	/*
	***		类型
	*/
	enum enCode_Type
	{
		enVideoType = 0,
		enAudioType = 1
	};

	/*
	***		视频格式
	*/
	enum enVideoFormat
	{
		//VIDEO Format
		VIDEO_FORMAT_NONE = 0,
		VIDEO_FORMAT_H264,												//H264
		VIDEO_FORMAT_RGB24,
		VIDEO_FORMAT_I420,
	};


	/*
	***		音频格式
	*/
	enum enAudioFormat
	{
		AUDIO_FORMAT_NONE = 0,
		AUDIO_FORMAT_AAC,
		AUDIO_FORMAT_PCM
	};

}

/*
***	RTSP 媒体信息
*/
// #pragma pack(push)
// #pragma pack(1)
struct RTSP_MEDIA_INFO
{
	INT							nCodeType;					//媒体类型(Video or Audio) -1:Error 0:Video 1:Audio

	INT							nVideoCodec;				//视频编码类型
	INT							nVideoWidth;				//视频宽
	INT							nVideoHeight;				//视频高
	BYTE						nFPS;						//帧率

	INT							nAudioCodec;				//音频编码类型
	INT							nSampleRate;
	INT							nSampleFmt;					//
	INT							nChannels;

	unsigned long				ulPts;						//时间戳

	BYTE						reserved1[4];
	UINT						reserved2[4];				//保留字段
};

using namespace LibMedia;

/*
***		最大图像 1080P
*/
#define MAX_PICTURE_SIZE									(1920 * 1080 * 3 + 100)
/*
***		错误码
*/
#define __RTSP_ERR_NO_ERROR									0		//没有错误
#define __RTSP_ERR_ORDER_ERROR								100		//错误索引
#define __RTSP_ERR_INVALID_PARAM							101		//无效参数
#define __RTSP_ERR_INVALID_URL								110  //无效url
#define __RTSP_ERR_INVALID_HANDLE							102		//无效句柄
#define __RTSP_ERR_INVALID_STATUS							103		//无效状态
#define __RTSP_ERR_INVALID_MEDIA							104		//无效媒体
#define __RTSP_ERR_OTHER_ERROR								109		//其他错误
#define __RTSP_ERR_CONNECT_TIMEOUT							116		//连接超时

typedef VOID(__stdcall* lpfuncRTSPNetMessageCb)(HANDLE hRTSPSession, DWORD dwMessageType, VOID *lpUser);
typedef VOID(__stdcall* lpfuncRTSPRealDataCb)(HANDLE hRTSPSession, const BYTE *lpBuffer, DWORD dwBufferSize, RTSP_MEDIA_INFO * lpMediaInfo, VOID *lpUser);
