///////////////////////////////////////////////////////////////////////////
// DS-40xxHC/HF BOARD SYSTEM SDK								 //	
/////////////////////////////////////////////////////////////////////////// 

#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#define FRAME_HEAD_MAGIC 0x03211546 
#define SYSTEM_SYNC_ID	2

typedef struct tagFrameInfo{
	ULONG	SyncId; /* 00000000000000000000000000010b */
	ULONG	Magic;
	USHORT	FrameType; /* I frames , P frames or BBP frames Audio frames or dsp status etc */
	ULONG	Length; /*lenth include this header */
	ULONG	FrameNumber; /* serial number of this frame */
	UCHAR	Breakable; /* indicate if stream breakable, you could restart new file(with PktSysHeader) if true */
	/*ULONG   Ack;*/
	ULONG	PTS; /* system clock when this frames is processed */
}TMFRAME_HEADER, *PTMFRAME_HEADER;

typedef enum _VideoStandard_t
{
   StandardNone                   = 0x80000000,
   StandardNTSC                   = 0x00000001,
   StandardPAL                    = 0x00000002,
   StandardSECAM                  = 0x00000004,
} VideoStandard_t;               


typedef enum _FrameType_t
{
	PktError = 0,
	PktIFrames = 0x0001,
	PktPFrames = 0x0002,
	PktBBPFrames = 0x0004,
	PktAudioFrames = 0x0008,
	PktMotionDetection = 0x00010,
	PktDspStatus = 0x00020,
	PktOrigImage = 0x00040,
	PktSysHeader = 0x00080,
	PktBPFrames = 0x00100,
	PktSFrames = 0x00200,
	PktSubIFrames = 0x00400,
	PktSubPFrames = 0x00800,
	PktSubBBPFrames = 0x01000,
	PktSubSysHeader = 0x02000
}FrameType_t;

typedef struct tagVersion{
	ULONG DspVersion, DspBuildNum;
	ULONG DriverVersion, DriverBuildNum;
	ULONG SDKVersion, SDKBuildNum;
}VERSION_INFO, *PVERSION_INFO;

typedef enum _PictureFormat_t
{
	ENC_CIF_FORMAT = 0,
	ENC_QCIF_FORMAT = 1,
	ENC_2CIF_FORMAT = 2,
	ENC_4CIF_FORMAT = 3,
	ENC_QQCIF_FORMAT = 4,
	ENC_CIFQCIF_FORMAT =5,
	ENC_CIFQQCIF_FORMAT =6,
	ENC_DCIF_FORMAT =7
}PictureFormat_t;
	
typedef struct tagMotionData{
	PictureFormat_t PicFormat;
	ULONG HorizeBlocks;
	ULONG VerticalBlocks;
	ULONG BlockSize;
}MOTION_DATA_HEADER, *PMOTION_DATA_HEADER;


#define _OSD_BASE	0x9000
#define	_OSD_YEAR4		_OSD_BASE+0
#define _OSD_YEAR2		_OSD_BASE+1
#define _OSD_MONTH3		_OSD_BASE+2
#define _OSD_MONTH2		_OSD_BASE+3
#define _OSD_DAY		_OSD_BASE+4
#define _OSD_WEEK3		_OSD_BASE+5
#define	_OSD_CWEEK1		_OSD_BASE+6
#define	_OSD_HOUR24		_OSD_BASE+7
#define	_OSD_HOUR12		_OSD_BASE+8
#define	_OSD_MINUTE		_OSD_BASE+9
#define _OSD_SECOND		_OSD_BASE+10


#endif
