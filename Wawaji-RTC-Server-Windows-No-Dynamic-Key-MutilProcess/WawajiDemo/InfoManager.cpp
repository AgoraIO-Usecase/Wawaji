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

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CInfoManager::CInfoManager()
{
}

CInfoManager::~CInfoManager()
{
}

void CInfoManager::setCurSection(const std::string &section)
{
	m_curSection = section;
	setsdkLogPath();
}

std::string CInfoManager::setsdkLogPath()
{
	CString strRet;
	std::string strTime;
	std::string exeName;
	std::string pirorDir;

	pirorDir = getPirorDir(getFilePath());
	strTime = getTime();

	exeName.append("wawajiDemo_");
	exeName.append(m_curSection);
	exeName.append(".log");

	strRet.Format(_T("%slogger\\%s_%s"),s2cs(pirorDir),s2cs(strTime),s2cs(exeName));
	CString logPirorDir = s2cs(getPirorDirEx(cs2s(strRet)));
	BOOL res = CreateDirectory(logPirorDir,NULL);
	m_sdkLogPath = cs2s(strRet);

	return cs2s(strRet);
}