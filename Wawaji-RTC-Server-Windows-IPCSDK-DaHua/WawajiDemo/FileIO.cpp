#include "stdafx.h"
#include "FileIO.h"
#include <assert.h>

CFileIO::CFileIO() :
fileHandle_(nullptr)
, filelimitLine_(0)
, isLog_(false)
{
}

CFileIO::~CFileIO()
{
	fileHandle_ = nullptr;
	filelimitLine_ = 0;
	isLog_ = false;
}

void CFileIO::openLog(const std::string &filepath, int fileFlage /*= OPEN_ALWAYS */)
{
	assert(nullptr == fileHandle_);
	fileHandle_ = CreateFile(
		CString(filepath.c_str()),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		/*CREATE_NEW | OPEN_ALWAYS | TRUNCATE_EXISTING*/fileFlage,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
	if (INVALID_HANDLE_VALUE == fileHandle_)
	{
		fileHandle_ = nullptr;
		printf("文件创建失败!!!!!!\n");
		int retCode = GetLastError();
		if (ERROR_ALREADY_EXISTS == retCode)
		{
			printf("文件已经存在,创建文件失败!!!!\n");
		}
	}

	isLog_ = true;
	SetFilePointer(fileHandle_, 0, nullptr, FILE_END);
}

void CFileIO::openMedia(const std::string &filepath, int fileFlage /*= CREATE_ALWAYS*/)
{
	assert(nullptr == fileHandle_);
	fileHandle_ = CreateFile(CString(filepath.c_str()),
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		nullptr,
		fileFlage,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
	if (INVALID_HANDLE_VALUE == fileHandle_)
	{
		fileHandle_ = nullptr;
		printf("文件创建失败!!!!!!\n");
		int retCode = GetLastError();
		if (ERROR_ALREADY_EXISTS == retCode)
		{
			printf("文件已经存在,创建文件失败!!!!\n");
		}
	}
}

void CFileIO::openReadFile(const std::string &filePath)
{
	openLog(filePath);
	FlushFileBuffers(fileHandle_);
	SetFilePointer(fileHandle_, 0, nullptr, FILE_BEGIN);
}

void CFileIO::close()
{
	CloseHandle(fileHandle_);
	fileHandle_ = nullptr;
}

int CFileIO::write(char *bufferIn, int bufferLen)
{
	if (fileHandle_)
	{
		DWORD writenLen = 0;
		int res = WriteFile(fileHandle_, bufferIn, (DWORD)bufferLen, &writenLen, nullptr);
		if (0 == res)
		{
			printf("write buffer failed..retCode: %d!!!!!\n", GetLastError());
		}
		return int(writenLen);
	}

	return 0;
}

int CFileIO::write(std::string bufferStr)
{
	filelimitLine_++;
	if (isLog_)
	{
		bufferStr += "\r\n";
	}
	if (isLog_ && 100 == filelimitLine_)
	{//清空操作
		SetFilePointer(fileHandle_, 0, nullptr, FILE_BEGIN);
		SetEndOfFile(fileHandle_);
		filelimitLine_ = 0;
	}

	return write((char*)bufferStr.c_str(), bufferStr.length());
}

int CFileIO::read(char *bufferOut, int bufferLen)
{
	DWORD readLen = 0;
	int res = ReadFile(fileHandle_, bufferOut, bufferLen, &readLen, nullptr);
	if (0 == res)
	{
		printf("read buffer from file failed!!!,retCode: %d\n", GetLastError());
		return int(readLen);
	}
	return readLen;
}

std::string CFileIO::readLine()
{
	std::string strLine;
	char readTxt[2] = { 0 };
	DWORD readLen = 0; DWORD dwValue = 0;
	BOOL res = ReadFile(fileHandle_, readTxt, 1, &readLen, nullptr);
	std::string chKey = "\r";
	while (true)
	{
		if (res && 1 == readLen && chKey == readTxt)
		{
			res = ReadFile(fileHandle_, readTxt, 1, &readLen, nullptr);
			chKey = "\n";
			if (res && 1 == readLen && chKey == readTxt)
			{
				break;
			}
			else
			{
				printf("read error ,cloud read '\r\n'\n");
				return "";
			}
		}
		else if (res && 1 == readLen &&  chKey != readTxt)
		{
			strLine += readTxt;
			//dwValue = SetFilePointer(fileHandle_, readLen, nullptr, FILE_CURRENT);
			readLen = 0; ZeroMemory(readTxt, 2); dwValue = 0;
			res = ReadFile(fileHandle_, readTxt, 1, &readLen, nullptr);
		}
		if (res && 0 == readLen)
		{
			break;
		}
	}
	return strLine;
}

std::string CFileIO::read()
{
	return "";
}

bool CFileIO::generatorFile(const std::string &path)
{
	HANDLE fileHandle = CreateFile(CString(path.c_str()),
		GENERIC_READ | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
	if (INVALID_HANDLE_VALUE == fileHandle)
	{
		return false;
	}
	return true;
}
