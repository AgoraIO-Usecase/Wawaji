#include "stdafx.h"
#include "HikVision.h"
#include "commonFun.h"
#include "CircularBuffer.h"
#include "libyuv.h"

unsigned char* CHikVision::m_yuv420buffer = nullptr;
int CHikVision::m_wdith = 0;
int CHikVision::m_height = 0;

CHikVision::CHikVision(int width, int height) :
m_isLogin(FALSE)
, m_isPlay(FALSE)
, m_lUserID(-1)
, m_realHandle(-1)
, m_nport(-1)
, m_wnd(nullptr)
{
	initHikVisionSdk();
	m_wdith = width; m_height = height;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

CHikVision::CHikVision():
m_isLogin(FALSE)
, m_isPlay(FALSE)
, m_lUserID(-1)
, m_realHandle(-1)
, m_nport(-1)
, m_wnd(nullptr)
{
	initHikVisionSdk();
	m_wdith = 1280; m_height = 720;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

CHikVision::~CHikVision()
{
	if (m_yuv420buffer){ delete[] m_yuv420buffer; m_yuv420buffer = nullptr; }
	uninitHikVisionSdk();
	m_lUserID = -1;
	m_realHandle = -1;
	m_isLogin = false;
	m_isPlay = false;
	m_nport = -1;
	m_wnd = nullptr;
	m_yuv420buffer = nullptr;
	m_wdith = 0;
	m_height = 0;
	CircularBuffer::getinstance()->releaseInstance();
}

bool CHikVision::initHikVisionSdk()
{
	bool res = NET_DVR_Init();
	return res;
}

bool CHikVision::uninitHikVisionSdk()
{
	int res = NET_DVR_Cleanup();
	return res;
}

void CHikVision::setResolution(int width, int height)
{
	m_wdith = width; m_height = height;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

bool CHikVision::login(const std::string &addressIp, const std::string nport, const std::string &user, const std::string &psw)
{
	NET_DVR_DEVICEINFO_V30 devInfo;
	m_lUserID = NET_DVR_Login_V30((char*)addressIp.data(), str2int(nport), (char*)user.data(), (char*)psw.data(), &devInfo);
	if (0 > m_lUserID){

		int res = NET_DVR_GetLastError();
		TRACE("IP : %s login failed errorcode %d..\n",addressIp.data(),res);
	}
	else{

		TRACE("IP: %s login success.\n",addressIp.data());
	}

	return true;
}

bool CHikVision::logout()
{
	if (m_lUserID )
	return 	NET_DVR_Logout_V30(m_lUserID);
}

bool CHikVision::startPlay(HWND wnd)
{
	if (0 <= m_lUserID){
		if (0 > m_realHandle){

			NET_DVR_CLIENTINFO ClientInfo;
			m_channelID = 1;
			ClientInfo.lChannel = m_channelID;
			ClientInfo.hPlayWnd = NULL;
			ClientInfo.lLinkMode = 0;
			ClientInfo.sMultiCastIP = NULL;

			m_realHandle = NET_DVR_RealPlay_V30(m_lUserID, &ClientInfo, fRealDataCallBack, this, TRUE);
			if (0 > m_realHandle){

				TRACE("Net_Dvr_RealPlay_V30 failed . ErrCode: %d \n",NET_DVR_GetLastError());
				return false;
			}
		}
	}
	m_wnd = wnd;

	return false;
}

bool CHikVision::stopPlay()
{
	if (m_realHandle){
		if (!NET_DVR_StopRealPlay(m_realHandle)){

			TRACE("Net_Dvr_StopRealPlay failed.. errCode: %d", NET_DVR_GetLastError());
			return false;
		}

		if (m_nport > -1){
			if (!PlayM4_Stop(m_nport)){
				TRACE("PlayM4_Stop failed .. errCode : %d\n", PlayM4_GetLastError(m_nport));
			}
			if (!PlayM4_CloseStream(m_nport)){
				TRACE("PlayM4_CloseStream failed..errCode: %d\n", PlayM4_GetLastError(m_nport));
			}
			PlayM4_FreePort(m_nport);
			m_nport = -1;
		}

	}
	return true;
}

void CALLBACK CHikVision::fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	DWORD dRet = 0;
	BOOL inData = FALSE;
	CHikVision *pThis = (CHikVision*)pUser;

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (pThis->m_nport >= 0)
		{
			break; //同一路码流不需要多次调用开
		}

		if (!PlayM4_GetPort(&(pThis->m_nport)))
		{
			break;
		}

		if (!PlayM4_OpenStream(pThis->m_nport, pBuffer, dwBufSize, 1024 * 1024))
		{
			dRet = PlayM4_GetLastError(pThis->m_nport);
			break;
		}

		//设置解码回调函数 解码且显示
		if (!PlayM4_SetDecCallBackEx(pThis->m_nport, DecCBFun, NULL, 0))
		{
			dRet = PlayM4_GetLastError(pThis->m_nport);
			break;
		}

		//打开视频解码
		if (!PlayM4_Play(pThis->m_nport, pThis->m_wnd))
		{
			dRet = PlayM4_GetLastError(pThis->m_nport);
			break;
		}

		//打开音频解码, 需要码流是复合流
		if (FALSE && !PlayM4_PlaySound(pThis->m_nport))
		{
			dRet = PlayM4_GetLastError(pThis->m_nport);
			break;
		}
		break;

	case NET_DVR_STREAMDATA:
		inData = PlayM4_InputData(pThis->m_nport, pBuffer, dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData = PlayM4_InputData(pThis->m_nport, pBuffer, dwBufSize);
			TRACE("Net_DVR_StreamData PlayM4_InputData failed \n");
		}
		break;
	default:
		inData = PlayM4_InputData(pThis->m_nport, pBuffer, dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData = PlayM4_InputData(pThis->m_nport, pBuffer, dwBufSize);
			TRACE("default PlayM4_InputData failed \n");
		}
		break;
	}
}

void CALLBACK CHikVision::DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
	long lFrameType = pFrameInfo->nType;
	if (lFrameType == T_AUDIO16)
	{
	}
	else if (lFrameType == T_YV12 && m_yuv420buffer)
	{
		int width = m_wdith; int height = m_height;
		int yStride = width; int uStride = width / 2; int vStride = width / 2;
		unsigned char* bufferY = m_yuv420buffer;
		unsigned char* bufferU =m_yuv420buffer + yStride * height;
		unsigned char* bufferV = m_yuv420buffer + yStride * height + uStride * height / 2;
		
		int res = libyuv::ConvertToI420((unsigned char*)pBuf, nSize, bufferY, yStride, bufferU, uStride, bufferV, vStride, 0, 0, width, height, width, height, libyuv::RotationMode::kRotate0, libyuv::FourCC::FOURCC_YV12);
		CircularBuffer::getinstance()->push((const char*)m_yuv420buffer, nSize);
	}
}