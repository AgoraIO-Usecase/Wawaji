#pragma once


#include "dhnetsdk.h"
#include "dhconfigsdk.h"

#include "FileIO.h"

//报警接口
typedef struct
{
	NET_CLIENT_STATE cState;
	DWORD dError;
	DWORD dFull;
	BYTE  shelter[16];
	BYTE  soundalarm[16];
	BYTE  almDecoder[16];
}DEV_STATE;

//设备信息列表结构
typedef struct _DeviceNode {
	char UserNanme[40]; //登录用户名
	char Name[24];   //设备名称
	char IP[48];     //设备IP地址字符
	LONG LoginID;    //设备登录iD
	NET_DEVICEINFO Info;  //设备信息
	int nChnNum;        //设备通道数
	DEV_STATE State; //设备状态
	DWORD TotalKbps;     //设备当前总码流
	DWORD Max_Kbps;     //设置最大网络流量
	BOOL	bIsOnline;
}DeviceNode;

class CDaHua
{
public:
	CDaHua(int width,int height);
	CDaHua();
	~CDaHua();

	void setResolution(int width,int height);

	bool login(const std::string &addressIp,const std::string nport,const std::string &user,const std::string &psw);
	bool logout();

	bool startPlay(HWND wnd);
	bool stopPlay();

protected:
	static void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	static void CALLBACK ReconnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	static BOOL CALLBACK MsgRecvFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
	static void CALLBACK RealDataFunc(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser);

private:
	bool initDaHuaSdk();
	bool uninitDaHuaSdk();

	void DeviceDisconnect();
	void DeviceReconnect();

private:
	bool m_isLogin;
	bool m_isPlay;
	bool m_isConnect;

	short m_channelID;
	LONG m_nport;

	LONG m_lUserID;	
	LONG m_realHandle;

	HWND m_wnd;
	static unsigned char* m_yuv420buffer;
	
	static int m_height;
	static int m_wdith;
	CFileIO m_fileYuv;
};