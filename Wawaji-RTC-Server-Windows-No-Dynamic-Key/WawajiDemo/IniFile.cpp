#include "StdAfx.h"
#include "IniFile.h"

//File
IniFile::IniFile(void)
{
}

IniFile::~IniFile(void)
{
}

std::string IniFile::getFilename()
{
	return _filename;
}

void IniFile::setFilename(const std::string &filename)
{
	_filename = filename;
}

std::string	IniFile::getStr(const std::string &appName, const std::string &keyName)
{
	char buf[300] = {0};

	//如果读取失败，请注意文件格式是否为ANSI格式
	BOOL res = GetPrivateProfileStringA(appName.c_str(), keyName.c_str(), NULL, buf, sizeof(buf), _filename.c_str());

	return buf;
}

BOOL IniFile::writeStr(const std::string &appName, const std::string &keyName, const std::string &value)
{
	return WritePrivateProfileStringA(appName.c_str(), keyName.c_str(), value.c_str(), _filename.c_str());
}

BOOL IniFile::writeSection(const std::string &appName, const std::string &keyName)
{
	return WritePrivateProfileSectionA(appName.c_str(), keyName.c_str(), _filename.c_str());
}
