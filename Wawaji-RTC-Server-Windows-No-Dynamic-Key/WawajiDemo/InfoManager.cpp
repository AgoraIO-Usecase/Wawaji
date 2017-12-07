#include "stdafx.h"
#include "InfoManager.h"
#include "commonFun.h"

CInfoManager::CInfoManager():
m_ProcessType(Type_NULL)
{
	m_batFile = (getPirorDir(getFilePath()) + "start.bat");
	m_curProcessName = getCurRunningExeName()/*"WawajiDemo.exe"*/;//
	int processNum = getProcessIdMutil(m_curProcessName);
	//processNum += 1;
	if (2 < processNum){
		//AfxMessageBox(_T("不能启动3个进程."));
		PostQuitMessage(0);
		return;
	}

	bool frontStatus = str2int(getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoFront));
	bool backStatus = str2int(getInfoManager()->getConfig()->getDeviceState(INI_DeviceInfoBack));
	if (frontStatus && backStatus){
		//AfxMessageBox(_T("配置文件异常,需要手动手动清除DeviceState选项.或者重启所有程序."));
		m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
		m_IniConfig.setDeviceState(INI_DeviceInfoBack, "0");
		PostQuitMessage(0);
		return;
	}

	if (1== processNum){
		m_ProcessType = getProcessID(m_curProcessName) > 0 ? Type_Front : Type_Back;
		m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
	}
	else if (2== processNum){
		if (frontStatus && !backStatus){
			m_ProcessType = Type_Back;
			m_IniConfig.setDeviceState(INI_DeviceInfoBack, "0");
		}
		else if (backStatus && !frontStatus){
			m_ProcessType = Type_Front;
			m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
		}
	}

	bool otherChoosefront = str2int(m_IniConfig.getDeviceChoose(INI_DeviceInfoFront));
	bool otherChooseback = str2int(m_IniConfig.getDeviceChoose(INI_DeviceInfoBack));
	if (otherChooseback&&otherChoosefront){
		//AfxMessageBox(_T("配置文件异常,需要手动手动清除DeviceChoose选项.或者重启所有程序."));
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
		PostQuitMessage(0);
		return;
	}

	//backup
	if (Type_Front == m_ProcessType){
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "1");
	}
	else if (Type_Back == m_ProcessType){
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "1");
	}
	else if (Type_NULL == m_ProcessType){
		}

	if (otherChoosefront){
		m_ProcessType = Type_Back;
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "1");
	}
	else if (otherChooseback){
		m_ProcessType = Type_Front;
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "1");
	}

	if (Type_Front == m_ProcessType){
	
		m_curSection = INI_DeviceInfoFront;
		m_sdkLogPath = getAbsoluteDir() + "SdkFront.log";
	}
	else if (Type_Back == m_ProcessType){

		m_curSection = INI_DeviceInfoBack;
		m_sdkLogPath = getAbsoluteDir() + "SdkBack.log";
	}

	std::string cameraFrontComId = m_IniConfig.getCameraComID(INI_DeviceInfoFront);
	std::string cameraBackComId = m_IniConfig.getCameraComID(INI_DeviceInfoBack);
	if (cameraFrontComId == cameraBackComId && cameraBackComId != ""){
		m_IniConfig.setCameraComID(m_curSection, "");
		//AfxMessageBox(_T("配置文件读到 前后摄像头信息配置相同..强制清空!!"));
	}
}

CInfoManager::~CInfoManager()
{
	m_ProcessType = Type_NULL;
}

void CInfoManager::setCameraType(enumCameraType cameratype)
{
	m_ProcessType = cameratype;
	setStateInfo();
}

void CInfoManager::setStateInfo()
{
	if (Type_Front == m_ProcessType){

		m_curSection = INI_DeviceInfoFront;
		m_sdkLogPath = getAbsoluteDir() + "SdkFront.log";
	}
	else if (Type_Back == m_ProcessType){

		m_curSection = INI_DeviceInfoBack;
		m_sdkLogPath = getAbsoluteDir() + "SdkBack.log";
	}

}