#pragma once

#include "def.h"

class UTILC_LIB_DECLSPEC IniFile
{
public:
	IniFile(void);

	~IniFile(void);

public:
	std::string getFilename();

	void setFilename(const std::string &filename);

	std::string
		getStr(const std::string &appName, const std::string &keyName);

	BOOL writeStr(const std::string &appName, const std::string &keyName, const std::string &value);

	BOOL writeSection(const std::string &appName, const std::string &keyName);

private:
	std::string	_filename;
};