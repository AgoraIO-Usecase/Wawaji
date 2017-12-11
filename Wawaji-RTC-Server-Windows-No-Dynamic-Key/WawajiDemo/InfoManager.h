#ifndef __INFOMANAGER_H__
#define __INFOMANGER_H__

#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;

//rapidJson
void add_json_member_string(Value& root, const char* member_name, const std::string& value, Document::AllocatorType& allocator);
void add_json_member_int(Value& root, const char* member_name, const int& value, Document::AllocatorType& allocator);
std::string get_json_content_string(Value& root);
std::string get_json_content_stylestring(Value& root);
std::string get_document_content_stylestring(Document &document);

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

std::string getCurSection();
std::string getOtherSection();

#endif