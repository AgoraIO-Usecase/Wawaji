#include "stdafx.h"
#include "RtspSessionEx.h"
#include "commonFun.h"
#include "VideoPackageQueue.h"

CRtspSessionEx::CRtspSessionEx() :m_ThreadRtsp(nullptr)
, m_isStart(FALSE)
, m_isConnected(FALSE)
{
	av_register_all();
	avformat_network_deinit();
}

CRtspSessionEx::~CRtspSessionEx()
{
	m_ThreadRtsp = nullptr;
	m_isStart = false;
	m_isConnected = false;
	
	avformat_network_deinit();
}

bool CRtspSessionEx::startRtsp(const std::string &rtspURL)
{
	m_rtmpUrl = rtspURL;
	m_isStart = true;

	//m_fileYUV.openMedia(getAbsoluteDir() + "1yuv.yuv");
	m_ThreadRtsp = CreateThread(nullptr, 0, ThreadRtspProc, this, 0, nullptr);

	return true;
}

bool CRtspSessionEx::stopRtsp()
{
	m_isStart = false;
	m_fileYUV.close();
	WaitForSingleObject(m_ThreadRtsp, INFINITE);
	CloseHandle(m_ThreadRtsp);
	m_ThreadRtsp = nullptr;

	return true;
}

DWORD WINAPI CRtspSessionEx::ThreadRtspProc(LPVOID lpParameter)
{
	CRtspSessionEx *pObj = (CRtspSessionEx*)lpParameter;
	bool isSetBuffer = false; char* yuvCaptureBuffer = nullptr;

	while (pObj->m_isStart){

		AVFormatContext *pFormatCtx = avformat_alloc_context();
		if(0 != avformat_open_input(&pFormatCtx, pObj->m_rtmpUrl.c_str(), NULL, NULL)){
			printf("Couldn't open input stream.\n");
			continue;
		}

		if (0 > avformat_find_stream_info(pFormatCtx, NULL)){
			printf("Couldn't find stream information.\n");
			continue;
		}
		pObj->m_isConnected = true;

		if (pObj->m_isConnected){
			int streamCount = 0, videoIndex = 0;
			AVCodecContext *pCodecCtx = nullptr;
			AVCodec *pCodec = nullptr;

			for (int nIndex = 0; nIndex < pFormatCtx->nb_streams; nIndex++){

				if (pFormatCtx->streams[nIndex]->codec->codec_type == AVMEDIA_TYPE_VIDEO && 
					pFormatCtx->streams[nIndex]->codec->codec_id == AV_CODEC_ID_H264){
					videoIndex = nIndex;
				}
				else if (pFormatCtx->streams[nIndex]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
					
				}
			}
			pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
			pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
			if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0){
				continue;
			}

			AVFrame *pFrame, *pFrameYUV = nullptr;
			AVPacket *packet = nullptr;
			pFrame = av_frame_alloc();
			pFrameYUV = av_frame_alloc();
			int video_w = pCodecCtx->width;
			int video_h = pCodecCtx->height;

			av_dump_format(pFormatCtx, 0, pObj->m_rtmpUrl.data(), 0);
			struct SwsContext *img_convert_ctx;
			img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
				pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AVPixelFormat::AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

			int ret = 0;
			int got_pictrue = 0;
			while (pObj->m_isStart && pObj->m_isConnected){
				packet = (AVPacket *)av_malloc(sizeof(AVPacket));
				if (0 <= av_read_frame(pFormatCtx, packet) && packet->stream_index == videoIndex){
					ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_pictrue, packet);
					if (ret < 0){
					break;
					}
					if (got_pictrue){
#if 1
						//TRACE("width: %d\n", pFrame->width);
						//TRACE("height: %d\n", pFrame->height);
						int width = pFrame->width;
						int height = pFrame->height;
						int yStride = pFrame->linesize[0];
						int uStride = pFrame->linesize[1];
						int vStride = pFrame->linesize[2];
						char* bufferY = (char*)pFrame->data[0];
						char* bufferU = (char*)pFrame->data[1];
						char* bufferV = (char*)pFrame->data[2];
// 						pObj->m_fileYUV.write(bufferY, height * yStride);
// 						pObj->m_fileYUV.write(bufferU, height * uStride / 2);
// 						pObj->m_fileYUV.write(bufferV, height * vStride / 2);
						if (!isSetBuffer){

							isSetBuffer = true;
							BITMAPINFOHEADER bitHeader;
							bitHeader.biWidth = width;
							bitHeader.biHeight = height;
							CVideoPackageQueue::GetInstance()->SetVideoFormat(width, height);
							 yuvCaptureBuffer = new char[width * height * 3 / 2];
						}
#endif
						memcpy(yuvCaptureBuffer, bufferY,height * yStride);
						memcpy(yuvCaptureBuffer + height * yStride, bufferU, height * uStride / 2);
						memcpy(yuvCaptureBuffer + height * yStride + height * uStride / 2, bufferV, height * vStride / 2);
						//pObj->m_fileYUV.write(yuvCaptureBuffer,width * height * 3 /2);
						CVideoPackageQueue::GetInstance()->PushVideoPackage((LPVOID)yuvCaptureBuffer, width * height * 3 / 2);
					}
				}
				av_free_packet(packet);
			}

			sws_freeContext(img_convert_ctx);
			av_free(pFrame);
			av_free(pFrameYUV);
			avcodec_close(pCodecCtx);
			avformat_close_input(&pFormatCtx);
			if (yuvCaptureBuffer){
				delete[] yuvCaptureBuffer;
				yuvCaptureBuffer = nullptr;
			}

		}
		Sleep(1);
		continue;;
	}

	return true;
}
