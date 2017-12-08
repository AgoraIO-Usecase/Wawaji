#pragma once

#include "wxCodec.h"

class H264Decoder
{
public:
	H264Decoder(void);

	~H264Decoder(void);

public:
	bool init(ColorFormat colorFormat = BGR24, int flip = FLIP_VERTICAL, bool bUseFFmpeg = false);

	void uninit();

	bool isInit();

	int dec(const char *inBuf, int inBufLen, char *outbuf, int *width, int *height, int *picFlag);

private:
	void	*_handle;
	int		_colorFormat;
	int		_flip;

	//是否使用ffmpeg解码
	bool   _bUseFFmpeg;
};
