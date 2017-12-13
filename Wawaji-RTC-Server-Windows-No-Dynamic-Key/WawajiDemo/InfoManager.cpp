#include "stdafx.h"
#include "InfoManager.h"
#include "commonFun.h"


void add_json_member_string(Value& root, const char* member_name, const std::string& value, Document::AllocatorType& allocator)
{
	Value json_member(kStringType);
	json_member.SetString(value.c_str(), value.size(), allocator);

	root.AddMember(member_name, json_member, allocator);
}

void add_json_member_int(Value& root, const char* member_name, const int& value, Document::AllocatorType& allocator)
{
	Value json_member(kNumberType);
	json_member.SetInt(value);

	root.AddMember(member_name, json_member, allocator);
}

std::string get_json_content_string(Value& root)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	root.Accept(writer);

	return buffer.GetString();
}

std::string get_json_content_stylestring(Value& root)
{
	return get_json_content_string(root);

	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	root.Accept(writer);

	return buffer.GetString();
}

std::string get_document_content_stylestring(Document &document)
{
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	document.Accept(writer);

	return buffer.GetString();
}


CInfoManager::CInfoManager():
m_ProcessType(Type_NULL)
{
	m_curProcessName = getCurRunningExeName();
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
		//AfxMessageBox(_T("配置文件异常,需要手动清除DeviceState选项.或者重启所有程序."));
		m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
		m_IniConfig.setDeviceState(INI_DeviceInfoBack, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "0");
		PostQuitMessage(0);
		return;
	}

	bool otherChoosefront = str2int(m_IniConfig.getDeviceChoose(INI_DeviceInfoFront));
	bool otherChooseback = str2int(m_IniConfig.getDeviceChoose(INI_DeviceInfoBack));
	if (otherChooseback&&otherChoosefront){
		//AfxMessageBox(_T("配置文件异常,需要手动清除DeviceChoose选项.或者重启所有程序."));
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
		PostQuitMessage(0);
		return;
	}

	if (1== processNum){
		m_ProcessType = getProcessID(m_curProcessName) > 0 ? Type_Front : Type_Back;
		m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "1");
		m_IniConfig.setDeviceState(INI_DeviceInfoBack, "0");
		m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
	}
	else if (2== processNum){
		if (otherChoosefront && !otherChooseback){
			m_ProcessType = Type_Back;
			m_IniConfig.setDeviceState(INI_DeviceInfoBack, "0");
			m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "0");
			m_IniConfig.setDeviceChoose(INI_DeviceInfoBack, "1");
		}
		else if (otherChooseback && !otherChoosefront){
			m_ProcessType = Type_Front;
			m_IniConfig.setDeviceState(INI_DeviceInfoFront, "0");
			m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "0");
			m_IniConfig.setDeviceChoose(INI_DeviceInfoFront, "1");
		}
	}

	if (Type_Front == m_ProcessType){
	
		m_curSection = INI_DeviceInfoFront;
		m_sdkLogPath = getsdkLogPath();
	}
	else if (Type_Back == m_ProcessType){

		m_curSection = INI_DeviceInfoBack;
		m_sdkLogPath = getsdkLogPath();
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
	m_IniConfig.setDeviceChoose(getOtherSection(), "0");
	m_IniConfig.setDeviceChoose(getCurSection(), "1");
	m_IniConfig.setDeviceState(getCurSection(), "0");
}

void CInfoManager::setStateInfo()
{
	if (Type_Front == m_ProcessType){

		m_curSection = INI_DeviceInfoFront;
		m_sdkLogPath = getsdkLogPath();
	}
	else if (Type_Back == m_ProcessType){

		m_curSection = INI_DeviceInfoBack;
		m_sdkLogPath = getsdkLogPath();
	}
}

std::string getCurSection()
{
	std::string section;
	enumCameraType cameraType = getInfoManager()->getCameraType();
	switch (cameraType)
	{
	case Type_Front:section = INI_DeviceInfoFront; break;
	case Type_Back:section = INI_DeviceInfoBack; break;
	default:break;
	}

	return section;
}

std::string getOtherSection()
{
	std::string section;
	enumCameraType cameraType = getInfoManager()->getCameraType();
	switch (cameraType)
	{
	case Type_Front:section = INI_DeviceInfoBack; break;
	case Type_Back:section = INI_DeviceInfoFront; break;
	default:break;
	}

	return section;
}

std::string getsdkLogPath()
{
	CString strRet;
	std::string strTime;
	std::string exeName;
	std::string pirorDir;

	pirorDir = getPirorDir(getFilePath());
	strTime = getTime();

	enumCameraType cameraType = getInfoManager()->getCameraType();
	if (Type_Front == cameraType){

		exeName = "AgoraWawajiDemo-Front.log";
	}
	else if (Type_Back == cameraType){

		exeName = "AgoraWawajiDemo-Back.log";
	}

	strRet.Format(_T("%slogger\\%s_%s"),s2cs(pirorDir),s2cs(strTime),s2cs(exeName));
	CString logPirorDir = s2cs(getPirorDirEx(cs2s(strRet)));
	BOOL res = CreateDirectory(logPirorDir,NULL);

	return cs2s(strRet);
}