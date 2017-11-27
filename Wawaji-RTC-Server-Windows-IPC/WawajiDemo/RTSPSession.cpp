#include "stdafx.h"
#include "RtspSession.h"
#include "commonFun.h"

CRtspSession::CRtspSession(void)
	: m_pThread(NULL)
	, m_bRunning(FALSE)
	, m_ConnectType(enDisConnect)
	, m_pFormatCtx(NULL)
	, m_pPacket(NULL)
	, m_nReadErrTime(0)
{
	m_isThreadExit = true;
	memset(m_szURL, 0, sizeof(m_szURL));
}


CRtspSession::~CRtspSession(void)
{
}

DWORD CRtspSession::CreateSession(const char *lpURL)
{
	_snprintf_s(m_szURL, MAX_PATH, "%s", lpURL);
	if (NULL == m_pPacket)
	{
		m_pPacket = av_packet_alloc();
		av_new_packet(m_pPacket, MAX_PICTURE_SIZE);
	}
	m_pMediaInfo = new RTSP_MEDIA_INFO();
	memset(m_pMediaInfo, 0, sizeof(RTSP_MEDIA_INFO));
	return 0;
}

VOID CRtspSession::DestroySession(VOID)
{	
	memset(m_szURL, 0, sizeof(m_szURL));
	Stop();
	if (NULL != m_pPacket)
	{
		av_packet_free(&m_pPacket);
	}
}

DWORD CRtspSession::SetNetMessageCallback(lpfuncRTSPNetMessageCb lpCallback, VOID * lpUser)
{
	m_lpNetCallback = lpCallback;
	m_lpNetUser = lpUser;
	return 0;
}

DWORD CRtspSession::Play(lpfuncRTSPRealDataCb lpCallback, VOID * lpUser, INT nTimeOut)
{
	if (m_bRunning) 
		return __RTSP_ERR_INVALID_STATUS;

	if (0 == m_szURL[0]) return __RTSP_ERR_INVALID_PARAM;
	m_nTimeOut = nTimeOut;
	try
	{
		m_lpRealCallback = lpCallback;
		m_lpRealUser = lpUser;
	
		m_bRunning = true;		
		DWORD dwRet = ConnectStream();
		if (dwRet == __RTSP_ERR_NO_ERROR)
			m_ConnectType = enConnected;
		else
			m_ConnectType = enConnecting;

		if (NULL == m_pThread)
		{
			//m_pThread = new std::thread(std::bind(&CRtspSession::WorkThread, this));
			//m_isThreadExit = true;
			m_pThread = CreateThread(nullptr, 0, WorkThread, this, 0, nullptr);
		}

		return dwRet;
	}
	catch(...)
	{
		printf("Play Error!");
	}
	return __RTSP_ERR_OTHER_ERROR;	
}

DWORD CRtspSession::Stop(VOID)
{
	if (false == m_bRunning) 
		return __RTSP_ERR_INVALID_STATUS;

	m_bRunning = false;
	if (NULL != m_pThread)
	{
		m_isThreadExit = false;
		WaitForSingleObject(m_pThread, INFINITE);
		CloseHandle(m_pThread);
		m_pThread = NULL;
	}
	DisConnectStream();
	return 0;
}

//���ӵ���
DWORD CRtspSession::ConnectStream()
{
	try
	{
		AVDictionary * opts = NULL;
		std::string sTimeOut;
		sTimeOut = int2str(m_nTimeOut);		
		av_dict_set(&opts, "stimeout", sTimeOut.c_str(), 0);
		if (avformat_open_input(&m_pFormatCtx, m_szURL, NULL, &opts) != 0)
		{
			return __RTSP_ERR_CONNECT_TIMEOUT;	//���ӳ�ʱ
		}
		if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0)
		{
			return __RTSP_ERR_INVALID_MEDIA;
		}
		m_nReadErrTime = 0;
		return __RTSP_ERR_NO_ERROR;
	}
	catch(...)
	{
	}
	return __RTSP_ERR_OTHER_ERROR;
}

//�Ͽ���
DWORD CRtspSession::DisConnectStream()
{
	m_nReadErrTime = 0;
	if (NULL != m_pFormatCtx)
	{
		avformat_close_input(&m_pFormatCtx);
		m_pFormatCtx = NULL;
	}
	return __RTSP_ERR_NO_ERROR;
}

//////////////////////////////////////////////////////////////////////////
//�����߳�
DWORD CRtspSession::WorkThread(LPVOID lpParameter)
{
	CRtspSession *pObj = (CRtspSession*)lpParameter;
	INT nSleepTime = 100;
	while (pObj->m_bRunning)
	{
		switch (pObj->m_ConnectType)
		{
		case enDisConnect: { nSleepTime = pObj->DoDisConnectWork(); break; }
		case enConnecting: { nSleepTime = pObj->DoConnectingWork(); break; }
		case enConnected: { nSleepTime = pObj->DoConnectedWork(); break; }
		default: { printf("WorkThread ConnectType Error! ConnectType = %d", pObj->m_ConnectType); break; }
		}
		//ֻ�е�SleepTime����0����Ҫ��Ϣ
		if (nSleepTime > 0)
		{
			Sleep(nSleepTime);
		}
	}

	return true;
}

//�Ͽ�״̬
INT CRtspSession::DoDisConnectWork()
{
	TRACE("DoDisConnectWork: �ⲿҪ��DisConnect!\n");
	return STATUS_WORK_INTERVAL_TIME;
}

//��������״̬
INT CRtspSession::DoConnectingWork()
{
	TRACE("DoConnectingWork ��������!\n");
	DisConnectStream();
	DWORD dwRet = ConnectStream();
	printf("DoConnectingWork ConnectStream Ret = %d",dwRet);
	if (__RTSP_ERR_NO_ERROR == dwRet)
	{
		m_ConnectType = enConnected;
		//֪ͨ�ⲿ״̬
		if (m_lpNetCallback)
			m_lpNetCallback(this, 1, m_lpNetUser);
		printf("����RTSP�� %s �ɹ�",m_szURL);
		return 0;					
	}
	return STATUS_WORK_INTERVAL_TIME;
}

//������
INT CRtspSession::DoConnectedWork()
{
	TRACE("DoConnectedWork\n");
	try
	{
		av_init_packet(m_pPacket);
		if (av_read_frame(m_pFormatCtx, m_pPacket) == 0)
		{
			m_nReadErrTime = 0;

			AVStream * Stream = m_pFormatCtx->streams[m_pPacket->stream_index];
			AVCodecParameters * AVCodecParam = Stream->codecpar;
			memset(m_pMediaInfo, 0, sizeof(RTSP_MEDIA_INFO));
			//���ݻص�
			if (NULL != m_lpRealCallback)
			{
				if ((AVCodecParam->codec_type == AVMEDIA_TYPE_VIDEO)&&(AVCodecParam->codec_id == AV_CODEC_ID_H264))
				{
					m_pMediaInfo->nCodeType = LibMedia::enVideoType;
					m_pMediaInfo->nVideoCodec = LibMedia::VIDEO_FORMAT_H264;
					m_pMediaInfo->nVideoWidth = AVCodecParam->width;
					m_pMediaInfo->nVideoHeight = AVCodecParam->height;
					m_pMediaInfo->ulPts = m_pPacket->pts;
					m_lpRealCallback(this, (BYTE *)m_pPacket->data, m_pPacket->size, m_pMediaInfo, m_lpRealUser);
				}
				else if ((AVCodecParam->codec_type == AVMEDIA_TYPE_AUDIO) && (AVCodecParam->codec_id = AV_CODEC_ID_AAC))
				{
					m_pMediaInfo->nCodeType = LibMedia::enAudioType;
					m_pMediaInfo->nAudioCodec = LibMedia::AUDIO_FORMAT_AAC;
					m_pMediaInfo->nSampleRate = AVCodecParam->sample_rate;
					m_pMediaInfo->nChannels = AVCodecParam->channels;
					m_pMediaInfo->ulPts = m_pPacket->pts;
					m_pMediaInfo->nSampleFmt = AVCodecParam->format;
					m_lpRealCallback(this, (BYTE *)m_pPacket->data, m_pPacket->size, m_pMediaInfo, m_lpRealUser);
				}
				else
					printf("DoConnectedWork Media Type Error!");
			}
			else 
			{
				printf("DoConnectedWork m_lpRealCallback == NULL !");
			}
			av_free_packet(m_pPacket);
			return 0;
		}
		else	//��ȡʧ��
		{
			printf("av_read_frame Error!");
			++m_nReadErrTime;
			if (m_nReadErrTime > MAX_READ_ERR_TIME)	//
			{
				printf("״̬��ת����������!");
				m_ConnectType = enConnecting;	//ת������״̬
				//֪ͨ�ⲿ״̬
				if (m_lpNetCallback)
					m_lpNetCallback(this, 0, m_lpNetUser);
			}
			return STATUS_WORK_INTERVAL_TIME;
		}
	}
	catch(...)
	{ 
		printf("DoConnectedWork Error!");
	}
	return STATUS_WORK_INTERVAL_TIME;
}