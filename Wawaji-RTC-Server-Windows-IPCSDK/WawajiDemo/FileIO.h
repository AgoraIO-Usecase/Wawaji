#ifndef __FILEIO_H__
#define __FILEIO_H__

class CFileIO
{
public:
	CFileIO();
	~CFileIO();

	void openLog(const std::string &filepath, int fileFlage = OPEN_ALWAYS);
	void openMedia(const std::string &filepath, int fileFlage = CREATE_ALWAYS);
	void openReadFile(const std::string &filePath);
	void close();
	int write(std::string bufferStr);
	int read(char *bufferOut, int bufferLen);
	std::string readLine();
	std::string read();

public:
	static bool generatorFile(const std::string &path);

public:
	int write(char *bufferIn, int bufferLen);

private:
	HANDLE fileHandle_;
	int filelimitLine_;
	bool isLog_;
};

#endif
