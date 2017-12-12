#include "StdAfx.h"
#include "H264Decoder.h"

H264Decoder::H264Decoder(void)
: _colorFormat(0),
_flip(0),
_handle(NULL),
_bUseFFmpeg(false)
{
}

H264Decoder::~H264Decoder(void)
{
	uninit();
}

bool H264Decoder::init(ColorFormat colorFormat, int flip, bool bUseFFmpeg /*= false*/)
{
	if (isInit())
	{
		return false;
	}
	
	_bUseFFmpeg = bUseFFmpeg;
	if (_bUseFFmpeg)
	{
		_handle =  H264DecInit();
	}
	else
	{
		_handle = H264DecInit_i(colorFormat, flip);
	}

	/*switch (flip)
	{
	case FLIP_VERTICAL:
		_handle = H264DecInit_i(colorFormat, FLIP_VERTICAL);
		break;
	default:
		_handle = H264DecInit_i(colorFormat, NO_FLIP);
		break;
	}*/

	if (_handle)
	{
		_colorFormat = colorFormat;
		_flip = flip;

		return true;
	}

	uninit();

	return false;
}

void H264Decoder::uninit()
{
	if (_handle)
	{
		if (_bUseFFmpeg)
		{
			H264DecUnInit(_handle);
		}
		else
		{
			H264DecUnInit_i(_handle);
		}

		_handle = NULL;
	}

	_colorFormat = 0;
	_flip = 0;
	_bUseFFmpeg = false;
}

bool H264Decoder::isInit()
{
	return _handle != NULL;
}

int H264Decoder::dec(const char *inBuf, int inBufLen, char *outbuf, int *width, int *height, int *picFlag)
{
	if (!_handle)
	{
		return -1;
	}

	if (_bUseFFmpeg)
	{
		return H264DecProc(_handle, (unsigned char *)inBuf, inBufLen, (unsigned char *)outbuf, width, height, picFlag);
	}
	else
	{
		return H264DecProc_i(_handle, (unsigned char *)inBuf, inBufLen, (unsigned char *)outbuf, width, height, picFlag);
	}
}