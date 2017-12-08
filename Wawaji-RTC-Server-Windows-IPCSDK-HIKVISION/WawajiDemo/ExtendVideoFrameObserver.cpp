#include "stdafx.h"
#include "ExtendVideoFrameObserver.h"
#include "VideoPackageQueue.h"
#include "CircularBuffer.h"
#include "commonFun.h"


CExtendVideoFrameObserver::CExtendVideoFrameObserver()
{
	m_lpImageBuffer = new BYTE[0x800000];
	m_fileCatchYuv.openMedia(getAbsoluteDir() + "catchyuv.log");
}

CExtendVideoFrameObserver::~CExtendVideoFrameObserver()
{
	m_fileCatchYuv.close();
	delete[] m_lpImageBuffer;
}

bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
	static DWORD begintime = GetTickCount();
	static int ncount = 0;

	int nBufferSize = 0x800000;

	//BOOL bSuccess = CVideoPackageQueue::GetInstance()->PopVideoPackage(m_lpImageBuffer, &nBufferSize);
	BOOL bSuccess = CircularBuffer::getinstance()->pop((char*)m_lpImageBuffer, nBufferSize);
	if (!bSuccess)
		return false;

	
	//m_fileCatchYuv.write((char*)m_lpImageBuffer, nBufferSize);
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	CString stimeFormat;
	stimeFormat.Format(_T("%4d/%02d/%02d %02d:%02d:%02d.%03d ÐÇÆÚ%d"), sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
	m_fileCatchYuv.write(cs2s(stimeFormat));

	m_lpY = m_lpImageBuffer;
	m_lpU = m_lpImageBuffer + videoFrame.height*videoFrame.width;
	m_lpV = m_lpImageBuffer + 5 * videoFrame.height*videoFrame.width / 4;

	memcpy_s(videoFrame.yBuffer, videoFrame.height*videoFrame.width, m_lpY, videoFrame.height*videoFrame.width);
	videoFrame.yStride = videoFrame.width;
	
	memcpy_s(videoFrame.uBuffer, videoFrame.height*videoFrame.width / 4, m_lpU, videoFrame.height*videoFrame.width / 4);
	videoFrame.uStride = videoFrame.width/2;

	memcpy_s(videoFrame.vBuffer, videoFrame.height*videoFrame.width / 4, m_lpV, videoFrame.height*videoFrame.width / 4);
	videoFrame.vStride = videoFrame.width/2;

	videoFrame.type = FRAME_TYPE_YUV420;
	videoFrame.rotation = 0;

	DWORD timeEnd = GetTickCount();
	ncount++;
	TRACE("capture one frame cost : %d\n",timeEnd - begintime);
	if (timeEnd - begintime > 5000){
		float capturerate = (ncount * 1000) / (timeEnd - begintime);
		TRACE("externcapture rate: %.2f",capturerate);
		ncount = 0;
		begintime = timeEnd;
	}
	return true;
}

bool CExtendVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame)
{
	return true;
}
