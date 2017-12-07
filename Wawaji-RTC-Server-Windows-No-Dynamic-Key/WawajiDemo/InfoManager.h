#ifndef __INFOMANAGER_H__
#define __INFOMANGER_H__

#include "FileIO.h"

class CInfoManager
{
public:
	CInfoManager();
	~CInfoManager();

	enumCameraType getCameraType(){ return m_ProcessType; }
	CConfigWawaji* getConfig(){ return &m_IniConfig; }
	std::string getSdkLogPath(){ return m_sdkLogPath; }
	std::string getCurSection(){ return m_curSection;}
	void setCameraType(enumCameraType cameratype);

protected:
	void setStateInfo();

private:

	enumCameraType m_ProcessType;
	CConfigWawaji m_IniConfig;
	std::string m_curSection;
	std::string m_sdkLogPath;

	std::string m_curProcessName;
	CFileIO m_filelog;
	std::string m_batFile;
};


#endif