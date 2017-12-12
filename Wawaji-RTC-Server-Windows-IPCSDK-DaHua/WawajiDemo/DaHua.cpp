#include "stdafx.h"
#include "DaHua.h"
#include "commonFun.h"
#include "CircularBuffer.h"
#include "libyuv.h"

unsigned char* CDaHua::m_yuv420buffer = nullptr;
int CDaHua::m_wdith = 0;
int CDaHua::m_height = 0;

CDaHua::CDaHua(int width, int height) :
m_isLogin(FALSE)
, m_isPlay(FALSE)
, m_isConnect(FALSE)
, m_lUserID(-1)
, m_realHandle(-1)
, m_nport(-1)
, m_wnd(nullptr)
{
	initDaHuaSdk();
	m_wdith = width; m_height = height;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

CDaHua::CDaHua():
m_isLogin(FALSE)
, m_isPlay(FALSE)
, m_lUserID(-1)
, m_realHandle(-1)
, m_nport(-1)
, m_wnd(nullptr)
{
	initDaHuaSdk();
	m_wdith = 1280; m_height = 720;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

CDaHua::~CDaHua()
{
	if (m_yuv420buffer){ delete[] m_yuv420buffer; m_yuv420buffer = nullptr; }
	uninitDaHuaSdk();
	m_lUserID = -1;
	m_realHandle = -1;
	m_isLogin = false;
	m_isPlay = false;
	m_isConnect = false;
	m_nport = -1;
	m_wnd = nullptr;
	m_yuv420buffer = nullptr;
	m_wdith = 0;
	m_height = 0;
	CircularBuffer::getinstance()->releaseInstance();
}

bool CDaHua::initDaHuaSdk()
{
	DWORD dwuser = 0;
	bool res = CLIENT_Init(DisConnectFunc,(DWORD)this);
	if (!res){

		TRACE("InitHikVisonSdk retCode: %d\n",CLIENT_GetLastError());
	}
	
	CLIENT_SetAutoReconnect(ReconnectFunc, (DWORD)this);
	CLIENT_SetConnectTime(3000, 3);

	return res;
}

bool CDaHua::uninitDaHuaSdk()
{
	 CLIENT_Cleanup();

	return true;
}

void CDaHua::DeviceDisconnect()
{
}

void CDaHua::DeviceReconnect()
{
}

void CDaHua::setResolution(int width, int height)
{
	m_wdith = width; m_height = height;
	m_yuv420buffer = new unsigned char[m_wdith * m_height * 3 / 2];
	ZeroMemory(m_yuv420buffer, m_wdith * m_height * 3 / 2);
	CircularBuffer::getinstance()->init(m_wdith * m_height, 2);
}

bool CDaHua::login(const std::string &addressIp, const std::string nport, const std::string &user, const std::string &psw)
{
	NET_PARAM netParam;
	CLIENT_SetNetworkParam(&netParam);

	NET_DEVICEINFO netDeviceInfo;
	int err = 0;
	m_lUserID = CLIENT_Login(addressIp.data(), str2int(nport), user.data(), psw.data(), &netDeviceInfo, &err);
	if (0 == m_lUserID){
		TRACE("Login failed errCode: %d\n",err);
		return false;
	}
	int channelNum = netDeviceInfo.byChanNum;

	return true;
}

bool CDaHua::logout()
{
	if (m_lUserID){

		CLIENT_Logout(m_lUserID);
		m_lUserID = -1;
	}

	return true;
}

bool CDaHua::startPlay(HWND wnd)
{
	m_wnd = wnd;
// 	NET_DEV_CHN_COUNT_INFO DevChannelInfoCollection;
// 	DevChannelInfoCollection.dwSize = { sizeof(NET_DEV_CHN_COUNT_INFO) };
// 	DevChannelInfoCollection.stuVideoIn.dwSize = sizeof(DevChannelInfoCollection.stuVideoIn);
// 	DevChannelInfoCollection.stuVideoOut.dwSize = sizeof(DevChannelInfoCollection.stuVideoOut);
// 	int RetLen = 0;
// 	if (!CLIENT_QueryDevState(m_lUserID, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&DevChannelInfoCollection, DevChannelInfoCollection.dwSize, &RetLen)){
// 
// 		TRACE("QueryDevState errCode: %d\n", CLIENT_GetLastError());
// 		return false;
// 	}
	//channelNum = DevChannelInfoCollection.stuVideoIn.nMaxLocal;
	m_realHandle = CLIENT_RealPlayEx(m_lUserID, 0, m_wnd, DH_RType_Realplay_0);
	int nStreamType = DH_RType_Realplay_0;
	if (nStreamType >= DH_RType_Realplay_0 && nStreamType <= DH_RType_Realplay_3){
		nStreamType -= (int)DH_RType_Realplay_0;
	}
	else {
		nStreamType = 0;
	}
	CLIENT_MakeKeyFrame(m_lUserID, 0, nStreamType);
	if (!m_realHandle){
		TRACE("RealPlayEx failed errCode: %d\n", CLIENT_GetLastError());
		return false;
	}

// 	BYTE bVideo[4];
// 	BOOL nRet = CLIENT_ClientGetVideoEffect(m_realHandle, &bVideo[0], &bVideo[1], &bVideo[2], &bVideo[3]);
// 	if (!nRet){
// 		TRACE("ClientGetVideoEffect errCode: %d\n",CLIENT_GetLastError());
// 		return false;
// 	}

	BOOL cbRec = CLIENT_SetRealDataCallBackEx(m_realHandle, RealDataFunc, (DWORD)this, 0x00000004);
	if (!cbRec){
		TRACE("SetRealDataCallBack failed errCode: %d\n", CLIENT_GetLastError());
		return false;
	}

	return true;
}

bool CDaHua::stopPlay()
{
	if (m_realHandle){
		CLIENT_StopRealPlayEx(m_realHandle);
	}

	return true;
}

void CALLBACK CDaHua::DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if (dwUser == 0)
	{
		return;
	}

	CDaHua *pInstance = (CDaHua*)dwUser;
	pInstance->DeviceDisconnect();
}

void CALLBACK CDaHua::ReconnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if (0 == dwUser){

		return;
	}

	CDaHua *pInstance = (CDaHua*)dwUser;
	pInstance->DeviceReconnect();
}

BOOL CALLBACK CDaHua::MsgRecvFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if (0 == dwUser){

		return false;
	}

	TRACE("Message: %s \n",pBuf);
}

void CALLBACK CDaHua::RealDataFunc(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser)
{
	if (0 == dwUser){

		TRACE("RealDataFunc errcode.\n");
		return;
	}
	
	//RealDataCallBack
	if (0 == dwDataType){
		TRACE("Src Data\n");
	}
	if (1 == dwDataType){
		tagVideoFrameParam *pVideoFrame = (tagVideoFrameParam*)param;

		TRACE("IFrame Data\n");
	}
	else if (2 == dwDataType){

		TRACE("yuv Video Data\n");
		CDaHua *pInstance = (CDaHua*)dwUser;
		if (pInstance){
// 			std::string yuvPath = getAbsoluteDir() + "dahua.yuv";
// 			pInstance->m_fileYuv.openMedia(yuvPath.data());
// 
// 			pInstance->m_fileYuv.write((char*)pBuffer, dwBufSize);
// 			pInstance->m_fileYuv.close();
			CircularBuffer::getinstance()->push((char*)pBuffer, dwBufSize);
		}
	}
	else if (3 == dwDataType){
		TRACE("pcm audio Data\n");
	}
}