
#ifndef DHCONFIGSDK_H
#define DHCONFIGSDK_H

#include "avglobal.h"
#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#ifdef CONFIGSDK_EXPORTS

#define CLIENT_CFG_API  __declspec(dllexport) 

#else

#define CLIENT_CFG_API  __declspec(dllimport)

#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#ifndef LLONG
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LLONG __int64
#else //WIN32 
#define LLONG LONG
#endif
#else	//Linux
#define LLONG long 
#endif
#endif

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LDWORD __int64
#else //WIN32 
#define LDWORD DWORD
#endif
#else	//Linux
#define LDWORD long 
#endif
#endif

#else	//Linux

#ifndef INTERNAL_COMPILE
#define CFG_RELEASE_HEADER
#endif

#ifndef CFG_RELEASE_HEADER 
#include "../Platform/platform.h"
#endif

#define CLIENT_CFG_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#endif


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** Constant Definition 
 ***********************************************************************/

#define MAX_CHANNEL_COUNT                       16
#define MAX_VIDEO_CHANNEL_NUM                   256         // Max 64 channels
#define MAX_CHANNELNAME_LEN                     64          // Max channel name length
#define MAX_VIDEOSTREAM_NUM                     3           // Max video stream amount
#define MAX_VIDEO_COVER_NUM                     16          // Max privacy mask zone amount
#define WEEK_DAY_NUM                            7           // The days in one week
#define MAX_REC_TSECT                           6           // Record period amount
#define MAX_REC_TSECT_EX                        10          // Record period extend amount
#define MAX_WATERMARK_LEN                       4096        // Max length of digital watermark data
#define MAX_MOTION_ROW                          32          // Row amount of the motion detect zone
#define MAX_MOTION_COL                          32          // Column amount of the motion detect zone
#define MAX_IMAGESIZE_NUM                       256         // Max resolution amount supported
#define MAX_FPS_NUM                             1024        // Max frame rate amount supported
#define MAX_QUALITY_NUM                         32          // Max quality amount supported
#define MAX_ADDRESS_LEN                         256         // Max address length
#define MAX_USERNAME_LEN                        64          // Max user name length
#define MAX_PASSWORD_LEN                        64          // Max password length
#define MAX_DIRECTORY_LEN                       256         // The name string length of the folder
#define MAX_NAS_TIME_SECTION                    2           // The network storage period amount
#define MAX_NAME_LEN                            128         // The general name string length
#define	MAX_SCENE_TYPE_LIST_SIZE 				8			// Max scene numbers of the scene list
#define MAX_DECPRO_LIST_SIZE                    100         // Max decoder protocol list amount
#define MAX_SCENE_LIST_SIZE                     32          // Video analyze supported max scene list number
#define MAX_OBJECT_LIST_SIZE                    16          // Video analyze supported max module list number
#define MAX_RULE_LIST_SIZE                      128         // Video analyze supported max rule list number
#define	MAX_SUPPORTED_COMP_SIZE					4			// Max supported size of combination scene
#define	MAX_SUPPORTED_COMP_DATA					8			// Max number scene of combaination  
#define MAX_ANALYSE_MODULE_NUM                  16          // Video analyze supported max detection module number
#define MAX_ANALYSE_RULE_NUM                    32          // Video analyze supported max rule number
#define MAX_POLYGON_NUM                         20          // Video analyze device max detection region point number
#define MAX_POLYLINE_NUM                        20          // Video analyze device max line point number
#define MAX_TEMPLATEREGION_NUM                  32          // Video analyze device max simulate region point pair 
#define POINT_PAIR_NUM                          2           // Video analyze device number of simulate region point pair
#define MAX_VEHICLE_SIZE_LIST                   4           // Video analyze device max car size number
#define MAX_VEHICLE_TYPE_LIST                   4           // Video analyze device max car type number
#define MAX_PLATE_TYPE_LIST                     32          // Video analyze device max plate type number
#define MAX_LANE_NUM                            8           // Video analyze device max road number
#define MAX_STAFF_NUM                           20          // Video analyze device max staff number	
#define MAX_CALIBRATEAREA_NUM                   20          // Video analyze device max calibrate area number
#define MAX_EXCLUDEREGION_NUM                   10          // Video analyse's exclude region max number in detect region  
#define MAX_CALIBRATEBOX_NUM                    10          // Video analyze device max celibate box number
#define MAX_SPECIALDETECT_NUM                   10          // Aptitude analyze specialdetect area upper limit
#define MAX_HUMANFACE_LIST_SIZE	                8           // Video analyze supported human face detect type max number
#define	MAX_SEVER_NUM                           16          // Sever type max number
#define MAX_SERVER_NAME_LEN                     16          // Server name max length
#define MAX_POWER_NUM                           8           // Power max number
#define MAX_FUN_NUM                             8           // Fun max number
#define MAX_CPU_NUM                             8           // CPU max number
#define MAX_HARDDISK_NUM                        32          // Disk max number
#define MAX_TANK_NUM                            16          // Tank max number
#define MAX_CHAN_NUM                            256         // Channel max number
#define MAX_RAID_NUM                            16          // Raid max number
#define MAX_DEV_NUM                             16          // Device max number
#define MAX_STORAGEPOOL_NUM                     16          // Storage pool max number
#define MAX_STRORAGEPOS_NUM                     16          // Storage pos max number
#define	MAX_VIDEODEV_NUM                        256         // Video device number
#define MAX_REMOTEDEVICENAME_LEN                32          // Remote device name number
#define	MAX_REMOTE_DEV_NUM                      256         // Remote device number
#define MAX_PLATEHINT_NUM                       8           // Plate hint string length
#define MAX_LIGHT_NUM                           8           // Traffic light max number
#define MAX_LIGHTGROUP_NUM                      8           // Traffic light group max number
#define MAX_LIGHT_TYPE                          8           // Traffic light type max number
#define MAX_LIGHT_DIRECTION                     8           // Traffic light direction max number
#define MAX_TRIGGERMODE_NUM                     32          // Traffic junction rule mode max number 
#define MAX_VIOLATIONCODE                       16          // Traffic violation code max length
#define MAX_DETECTOR                            6           // Traffic detector max number
#define MAX_COILCONFIG                          3           // Traffic detector's coil max number
#define MAX_DEVICE_ADDRESS                      256         // TrafficSnapshot device address max length
#define MAX_DEPARTMENT                          256         // Max length of the department info of the device
#define MAX_ROADWAYNO                           128         // Road no info max length
#define MAX_VIOLATIONCODE_DESCRIPT              64          // Violation info max length
#define MAX_DRIVINGDIRECTION                    256         // Drive direction info max length
#define MAX_ACTIVEUSER_NUM                      64          // Active user info max number
#define MAX_POLYGON_NUM10                       10          // Video analyze max polygon number in device region
#define MAX_VIDEODIAGNOSIS_DETECT_TYPE          11          // Video diagnosis type max number
#define MAX_ACTION_LIST_SIZE                    16          // Video analyze the max number of proper action type list the device supported 
#define MAX_STORAGEGROUPNAME_LEN                32          // Buffering threshold of storage group name 
#define MAX_CALIBRATEAREA_TYPE_NUM              4           // Calibrate region type max number
#define MAX_PROTOCOL_NAME_LEN                   32          // Protocol name length
#define	MAX_COMM_NUM                            16          // COM max number 
#define MAX_DNS_SERVER_NUM                      2           // DNS max number
#define MAX_NETWORK_INTERFACE_NUM               32          // Network Internet card max number
#define	MAX_NAS_NUM	                            16          // NAS max number
#define MAX_STORAGEPOINT_NUM                    32          // Max mapping of video storage point 
#define MAX_TRACKSCENE_NUM                      10          // Video track scene max number
#define MAX_STATUS_NUM                          16          // Means of transportation status max number
#define MAX_SERVICE_NUM                         128         // Server to support the maximum number of services
#define MAX_DBKEY_NUM                           64          // Max of DB key 
#define MAX_SUMMARY_LEN                         1024        // The max length of the jpeg image excerpta information
#define MAX_MOTION_WINDOW                       10          // Motion support video window value
#define MAX_OSD_SUMMARY_LEN                     256         // The max length of osd summary  
#define MAX_OSD_TITLE_LEN                       128         // The max length of osd title
#define MAX_CUSTOMCASE_NUM                      16          // Maximum number of custom judicial case
#define MAX_GLOBAL_MSTERSLAVE_NUM               64          // Master-slave tracker maximum number of global configuration
#define MAX_OBJECT_ATTRIBUTES_SIZE              16		    // Video analyse equipment support test object attribute type list number limit
#define MAX_MODEL_LEN                           32			// Model type length
#define MAX_BURNING_DEV_NUM                     32			// The max number of burning device
#define MAX_NET_TYPE_NUM                        8           // The max number of network type
#define MAX_NET_TYPE_LEN                        64          // The length of network type 
#define MAX_DEVICE_NAME_LEN                     64			// Name of device
#define MAX_DEV_ID_LEN_EX                       128		    // The max length of device ID
#define MONTH_OF_YEAR                           12			// Months of a year
#define MAX_SERVER_NUM                          10          // Maximum number of server
#define MAX_REGISTER_NUM                        10          // Maximum number of active registered configuration
#define MAX_VIDEO_IN_ZOOM                       32          // The Maximum Single-channel Variable Configuration Number
#define	MAX_ANALYSE_SCENE_NUM	                32          // The Maximum Number of Video Analysis of Global Configuration Scene
#define	MAX_CONFIG_NUM                          32          // The Maximum Number of Configuration for Each PTZ
#define	MAX_PTZ_PRESET_NAME_LEN                 64          // PTZ Preset Name Length
#define CFG_COMMON_STRING_16                    16          // Universal String Length 16
#define CFG_COMMON_STRING_32                    32          // Universal String Length 32
#define CFG_COMMON_STRING_64                    64          // Universal String Length 64
#define CFG_COMMON_STRING_128                   128         // Universal String Length 128
#define CFG_COMMON_STRING_256                   256         // Universal String Length 256
#define CFG_COMMON_STRING_512                   512         // Universal String Length 512
#define AV_CFG_Channel_Name_Len                 64          // Length of the channel name 
#define CFG_MAX_CHANNEL_NAME_LEN                256         // Max length of the channel name    
#define AV_CFG_Weekday_Num                      7           // Days of a week
#define AV_CFG_Max_TimeSection                  6           // The number of time section
#define AV_CFG_Device_ID_Len                    64          // Length of decice ID
#define AV_CFG_IP_Address_Len                   32          // Length of ip
#define AV_CFG_IP_Address_Len_EX                40          // extern IP address string length, support IPv6
#define AV_CFG_User_Name_Len                    64          // Length of user name 
#define AV_CFG_Password_Len                     64          // Length of password 
#define AV_CFG_Protocol_Len				        32          // Length of protocol name 
#define AV_CFG_Serial_Len				        32          // Length of serial name
#define AV_CFG_Device_Class_Len			        16          // Length of device class
#define AV_CFG_Device_Type_Len                  32          // Length of device type
#define AV_CFG_Device_Name_Len                  128         // Device name
#define AV_CFG_Address_Len                      128         // The address of machine deployment
#define AV_CFG_Max_Path	                        260         // The max length of path
#define AV_CFG_Max_Split_Window                 128			// The maximum number of split window
#define	AV_CFG_Monitor_Favorite_In_Channel      64		    // Each output channel of the largest wheelround number
#define AV_CFG_Monitor_Favorite_Name_Len        64		    // The length of monitor favorite name
#define AV_CFG_Max_Monitor_Favorite_Window      64		    // The maximum number of monitor favorite widow
#define AV_CFG_Max_Split_Group                  64		    // The maximum number of split group
#define AV_CFG_Max_Split_Mode                   32		    // The maximum number of split mode
#define AV_CFG_Raid_Name_Len                    64		    // Length of RAID name 
#define AV_CFG_Max_Rail_Member                  32		    // A single raid contains the disk
#define AV_CFG_Max_Encode_Main_Format           3		    // Main stream  encoding type number
#define AV_CFG_Max_Encode_Extra_Format          3		    // Extra stream  encoding type number
#define	AV_CFG_Max_Encode_Snap_Format           3		    // Grasp the coding type number
#define AV_CFG_Max_VideoColor                   24		    // The largest number of each channel video color input
#define AV_CFG_Custom_Title_Len                 1024		// Length of custom title
#define AV_CFG_Custom_TitleType_Len             32          // Custom Title Type Length
#define AV_CFG_Max_Video_Widget_Cover           16          // The maximum number of video widget cover
#define AV_CFG_Max_Video_Widget_Custom_Title    8          // The Maximum Number of Encoding Objects Custom Title
#define AV_CFG_Max_Video_Widget_Sensor_Info	    2           // The Maximum number of Encoding Object Superimposed Sensor Information
#define AV_CFG_Max_Description_Num              4           // The Maximum number of Stacking Area Description Information
#define AV_CFG_Group_Name_Len                   64		    // The length of group name
#define AV_CFG_DeviceNo_Len                     32		    // The length of Device number
#define AV_CFG_Group_Memo_Len                   128		    // The length of group explain
#define AV_CFG_Max_Channel_Num                  1024	    // The maximum number of channel
#define AV_CFG_Time_Format_Len                  32		    // Length of time format
#define AV_CFG_Max_White_List                   1024	    // The number of white list
#define AV_CFG_Max_Black_List                   1024	    // The number of black list
#define AV_CFG_Filter_IP_Len                    96		    // The max length of filter IP
#define AV_CFG_Max_ChannelRule                  32		    // The max length of channel storage rule,only of channel
#define AV_CFG_Max_DBKey_Num                    64		    // Number of event keywords
#define AV_CFG_DBKey_Len                        32		    // Length of event keywords
#define AV_CFG_Max_Summary_Len                  1024	    // Length of summary
#define AV_CFG_Max_Event_Title_Num              32		    // Number of event title
#define AV_CFG_Max_Tour_Link_Num                128		    // The maximum number of tour link
#define AV_CFG_PIP_BASE                         1000	    // Picture in picture model based segmentation
#define DES_KEY_LEN	                            8           // Bits Length of DES Key
#define DES_KEY_NUM                             3           // The Number of  3DES key
#define AES_KEY_LEN	                            32          // Bits Length of AES Key
#define MAX_TIME_SCHEDULE_NUM                   8           // Schedule Element Number
#define MAX_SCENE_SUBTYPE_LEN                   64          // Scene Subtype String Length
#define MAX_SCENE_SUBTYPE_NUM                   32          //  Scene Subtype String Maximum Number
#define MAX_VIDEO_IN_FOCUS                      32          // Single-channel Maximum Focus Configuration Number
#define MAX_TIMESPEEDLIMIT_NUM                  16          //  Maximum Time Limit Configuration Number
#define MAX_VOICEALERT_NUM                      64          // The Maximum Voice Prompt Configuration Number
#define CFG_MAX_LOWER_MATRIX_NUM                16          // The Maximum Lower-level Matrix Number
#define CFG_MAX_LOWER_MATRIX_INPUT              64          // The Maximum Lower-level Matrix Input Channel Number
#define CFG_MAX_LOWER_MATRIX_OUTPUT	            32          // The Maximum Lower-level Matrix Output Channel Number
#define CFG_MAX_AUDIO_MATRIX_INPUT              32          // The Maximum Audio Matrix Input Channels
#define CFG_MAX_AUDIO_OUTPUT_CHN                32			// The Maximum Audio Matrix Output Channels
#define CFG_MAX_AUDIO_MATRIX_NUM                4           // The Maximum Audio Matrix
#define CFG_MAX_AUDIO_MATRIX_OUTPUT             8           // The Maximum OutPut Channels Of Each Audio Matrix
#define CFG_MAX_INFRARED_BOARD_TEMPLATE_NUM     16          //  The Maximum Infrared Panel Template Number
#define	CFG_MAX_INFRARED_KEY_NUM                128	        // The Maximum Infrared Panel Template Button Number
#define	CFG_MAX_INFRARED_BOARD_NUM              16          //  The Maximum Infrared Panel Template Number
#define CFG_MAX_VTO_NUM                         128         // Maximum number of door machine
#define MAX_PHONE_NUMBER_LEN                    32          // Maximum Phone Number Length 
#define MAX_AUDIO_OUTPUT_NUM                    16          // The Maximum Channels Number of Audio Output 
#define MAX_AUDIO_INPUT_NUM						32			// The Maximum Channels Number of Audio Input
#define MAX_AUDIO_MIX_NUM						16			// The Maximum Number of Mix Audio
#define MAX_PSTN_SERVER_NUM	                    8           // The Maximum Number of  Alarm Call Servers
#define MAX_ALARM_CHANNEL_NUM                   32          // The Maximum Number of Alarm Channels
#define MAX_ALARM_DEFENCE_TYPE_NUM              8           // The Maximum Number of Alarm Protection Zone Type
#define MAX_ALARM_SENSE_METHOD_NUM              16          // The Maximum Number of Alarm Sensors Way
#define MAX_EXALARMBOX_PROTOCOL_NUM             8           // The Maximum Number of Protocol Support Extended Alarm Boxes
#define MAX_EXALARM_CHANNEL_NUM	                256	        // The Maximum Number of Alarm Channels
#define MAX_EXALARMBOX_NUM                      8           // The Maximum Number of Alarm Boxes
#define MAX_MAILTITLE_LEN                       256         // Max Mail Title Length
#define MAX_DEVICE_ID_LEN                       48          // Max device encoding length
#define MAX_DEVICE_MARK_LEN                     64          // Max device description length
#define MAX_BRAND_NAME_LEN                      64          // Max device brand length
#define MAX_ADDRESS_NUM                         16          // Max serial address quantity
#define MAX_AIRCONDITION_NUM                    16          // Max air conditioner device quantity
#define CFG_MAX_COLLECTION_NUM                  64          // Max collection quantity
#define MAX_FLOOR_NUM                           128         // Max floor
#define MAX_SEAT_NUM                            8           // Max Seat
#define AV_CFG_Local_Device_ID				    "Local"	    // Local device ID
#define AV_CFG_Remote_Devce_ID				    "Remote"    // Remote device ID
#define MAX_LANE_CONFIG_NUMBER                  32          // Max lane number
#define MAX_PRIORITY_NUMBER                     256         // Violation priority includes max violation number
#define MAX_CATEGORY_TYPE_NUMBER                128         // Number of category type
#define MAX_TRIGGER_MODE_NUMBER                 64			// Number of trigger mode
#define MAX_ABNORMAL_DETECT_TYPE                32          // max number of abnormal detect type
#define	MAX_ABNORMAL_THRESHOLD_LEN				32			// max threshold counts
#define TS_POINT_NUM                            3           // Touch screen calibration points
#define CFG_FILTER_IP_LEN                       96          // Max len of filter ip
#define CFG_MAX_TRUST_LIST				        1024        // Max number in trust list
#define CFG_MAX_BANNED_LIST                     1024        // Max number in banned list
#define VIDEOIN_TSEC_NUM                        3           // the various VideoIn config protocols' time section number, by now, we have three: 'day', 'night', 'normal'
#define	MAX_RECT_COUNT							4			// The Maximum Number of mosaic  Channel supported
#define CFG_MAX_SSID_LEN                        36          // SSID max length
/************************************************************************
 ** Configuration Command
 ***********************************************************************/

#define CFG_CMD_ENCODE                      "Encode"                    // Video channel property setup (corresponding to CFG_ENCODE_INFO)
#define CFG_CMD_RECORD                      "Record"                    // Schedule record setup
#define CFG_CMD_ALARMINPUT                  "Alarm"                     // External input alarm setup
#define CFG_CMD_NETALARMINPUT               "NetAlarm"                  // Network alarm setup
#define CFG_CMD_MOTIONDETECT                "MotionDetect"              // Motion detect alarm setup
#define CFG_CMD_VIDEOLOST                   "LossDetect"                // Video loss alarm setup
#define CFG_CMD_VIDEOBLIND                  "BlindDetect"               // Camera masking alarm setup
#define CFG_CMD_STORAGENOEXIST              "StorageNotExist"           // No storage device alarm setup
#define CFG_CMD_STORAGEFAILURE              "StorageFailure"            // The storage device access error alarm setup
#define CFG_CMD_STORAGELOWSAPCE	            "StorageLowSpace"           // The insufficient storage space alarm setup
#define CFG_CMD_NETABORT                    "NetAbort"                  // Network disconnection alarm setup	
#define CFG_CMD_IPCONFLICT                  "IPConflict"                // IP conflict alarm setup
#define CFG_CMD_SNAPCAPINFO                 "SnapInfo"                  // Snapshot competence search
#define CFG_CMD_NAS                         "NAS"                       // NAS setup
#define CFG_CMD_PTZ                         "Ptz"                       // PTZ setup
#define	CFG_CMD_PTZ_AUTO_MOVEMENT           "PtzAutoMovement"           // PTZ Timed Action Configuration(corresponding CFG_PTZ_AUTOMOVE_INFO)
#define CFG_CMD_WATERMARK                   "WaterMark"                 // Video watermark setup
#define CFG_CMD_ANALYSEGLOBAL               "VideoAnalyseGlobal"        // Video analyze global config(corresponding struct CFG_ANALYSEGLOBAL_INFO)
#define CFG_CMD_ANALYSEMODULE               "VideoAnalyseModule"        // Video analyze module config(corresponding struct CFG_ANALYSEMODULES_INFO)
#define CFG_CMD_ANALYSERULE                 "VideoAnalyseRule"          // Video analyze rule config(corresponding struct CFG_ANALYSERULES_INFO)
#define CFG_CMD_ANALYSESOURCE               "VideoAnalyseSource"        // Video analyze source config(corresponding struct CFG_ANALYSESOURCE_INFO)
#define CFG_CMD_RAINBRUSH                   "RainBrush"                 // Rain brush(corresponding struct CFG_RAINBRUSH_INFO)
#define CFG_CMD_INTELLECTIVETRAFFIC         "TrafficSnapshot"           // Intelligent Transport configuration
#define CFG_CMD_TRAFFICGLOBAL               "TrafficGlobal"             // Traffic global configuration(CFG_TRAFFICGLOBAL_INFO)
#define CFG_CMD_DEV_GENERRAL                "General"                   // General configuration (CFG_DEV_DISPOSITION_INFO)
#define CFG_CMD_ATMMOTION                   "FetchMoneyOverTime"        // ATM motion alarm(struct CFG_ATMMOTION_INFO)
#define CFG_CMD_DEVICESTATUS                "DeviceStatus"              // Device state information
#define CFG_CMD_HARDDISKTANK                "HardDiskTank"              // Hard disk tank info
#define CFG_CMD_RAIDGROUP                   "RaidGroup"                 // Raid group information
#define CFG_CMD_STORAGEPOOLGROUP            "StoragePoolGroup"          // Storage pool group information
#define CFG_CMD_STORAGEPOSITIONGROUP        "StoragePositionGroup"      // Storage position group info
#define CFG_CMD_VIDEOINDEVGROUP             "VideoInDevGroup"           // Video device group information
#define CFG_CMD_DEVRECORDGROUP              "DevRecordGroup"            // Device record group state
#define CFG_CMD_IPSSERVER                   "IpsServer"                 // Server state
#define CFG_CMD_SNAPSOURCE                  "SnapSource"                // Snap source configuration(struct CFG_SNAPSOURCE_INFO)
#define CFG_CMD_DHRADER                     "DahuaRadar"                // Dahua rader configuration (json string only)
#define CFG_CMD_DHRADER_PP                  "DahuaRadar"                // Dahua rader configuration (parse to C structure, CFG_DAHUA_RADAR)
#define CFG_CMD_TRANSRADER                  "TransRadar"                // Trans radar configuration
#define CFG_CMD_LANDUNRADER                 "LanDunRadar"               // Landun rader configuration
#define CFG_CMD_LANDUNCOILS                 "LanDunCoils"               // Landun coils configuration
#define CFG_CMD_MATRIX_SPOT                 "SpotMatrix"                // Spot video matrix 
#define CFG_CMD_HDVR_DSP                    "DspEncodeCap"              // DSP encode capability
#define CFG_CMD_HDVR_ATTR_CFG               "SystemAttr"                // Hdvr's each channel connected device's information
#define CFG_CMD_CHANNEL_HOLIDAY             "HolidaySchedule"		 
#define CFG_CMD_HEALTH_MAIL                 "HealthMail"                // Health mail
#define CFG_CMD_CAMERAMOVE                  "IntelliMoveDetect"         // Camera intelligence move detect linkage
#define CFG_CMD_SPLITTOUR                   "SplitTour"                 // Video split tour configuration(Corresponding of CFG_VIDEO_MATRIX) 
#define CFG_CMD_VIDEOENCODEROI              "VideoEncodeROI"            // Video encode ROI configuration(Region of Interest)
#define CFG_CMD_VIDEO_INMETERING            "VideoInMetering"           // Video inmetering configuration(Corresponding of CFG_VIDEO_INMETERING_INFO) 
#define CFG_CMD_TRAFFIC_FLOWSTAT            "TrafficFlowStat"           // Traffic flow statistic configuration(Corresponding of CFG_TRAFFIC_FLOWSTAT_INFO) 
#define CFG_CMD_HDMIMATRIX                  "HDMIMatrix"                // HDMI matrix configuration
#define CFG_CMD_VIDEOINOPTIONS              "VideoInOptions"            // Video input front-end option(Corresponding of CFG_VIDEO_IN_OPTIONS)
#define CFG_CMD_RTSP                        "RTSP"                      // RTSP configuration( Corresponding of CFG_RTSP_INFO_IN and CFG_RTSP_INFO_OUT ) 
#define CFG_CMD_TRAFFICSNAPSHOT             "TrafficSnapshotNew"        // Traffic snapshot(CFG_TRAFFICSNAPSHOT_INFO)
#define CFG_CMD_TRAFFICSNAPSHOT_MULTI       "TrafficSnapshotNew"        // Traffic snapshot(CFG_TRAFFICSNAPSHOT_NEW_INFO)
#define CFG_CMD_MULTICAST                   "Multicast"                 // Multicast configuration(Corresponding of CFG_MULTICASTS_INFO_IN and CFG_MULTICASTS_INFO_OUT) 
#define CFG_CMD_VIDEODIAGNOSIS_PROFILE      "VideoDiagnosisProfile"     // Video diagnosis parameter list(CFG_VIDEODIAGNOSIS_PROFILE)
#define CFG_CMD_VIDEODIAGNOSIS_TASK	        "VideoDiagnosisTask"        // Video diagnosis task list (CFG_VIDEODIAGNOSIS_TASK) 
#define CFG_CMD_VIDEODIAGNOSIS_PROJECT      "VideoDiagnosisProject"     // Video diagnosis project(CFG_VIDEODIAGNOSIS_PROJECT) 
#define CFG_CMD_VIDEODIAGNOSIS_REALPROJECT "VideoDiagnosisRealProject"  // Video Diagnosis Real-time Schedule(CFG_VIDEODIAGNOSIS_REALPROJECT)
#define CFG_CMD_VIDEODIAGNOSIS_GLOBAL       "VideoDiagnosisGlobal"      // Video diagnosis global(CFG_VIDEODIAGNOSIS_GLOBAL) 
#define CFG_CMD_VIDEODIAGNOSIS_TASK_ONE     "VideoDiagnosisTask.x"      // Video diagnosis task list(CFG_VIDEODIAGNOSIS_TASK)  
#define CFG_CMD_TRAFFIC_WORKSTATE           "WorkState"                 // Device workstate Info(Corresponding of CFG_TRAFFIC_WORKSTATE_INFO)
#define CFG_CMD_STORAGEDEVGROUP             "StorageDevGroup"           // Storage device group configuration(Corresponding of CFG_STORAGEGROUP_INFO)
#define CFG_CMD_RECORDTOGROUP               "RecordToGroup"             // Video record storage group configuration(Corresponding of CFG_RECORDTOGROUP_INFO) 
#define CFG_CMD_INTELLITRACKSCENE           "IntelliTrackScene"         // Intelligence track scene configuration(CFG_INTELLITRACKSCENE_INFO)
#define CFG_CMD_IVSFRAM_RULE                "IVSFramRule"               // Intelligence video frame rule(Corresponding of CFG_ANALYSERULES_INFO) 
#define CFG_CMD_RECORD_STORAGEPOINT         "RecordStoragePoint"        // Video record storage point mapping info(Corresponding of CFG_RECORDTOSTORAGEPOINT_INFO) 
#define CFG_CMD_MD_SERVER                   "MetaDataServer"	        // Metadata server configuration(Corresponding of CFG_METADATA_SERVER structure body) 
#define CFG_CMD_CHANNELTITLE                "ChannelTitle"              // Channel name (Corresponding of AV_CFG_ChannelName) 
#define	CFG_CMD_RECORDMODE                  "RecordMode"                // Record mode (Corresponding of AV_CFG_RecordMode) 
#define CFG_CMD_VIDEOOUT                    "VideoOut"                  // Video out property(Corresponding of AV_CFG_VideoOutAttr)
#define CFG_CMD_REMOTEDEVICE                "RemoteDevice"              // Remote device info (Corresponding of AV_CFG_RemoteDevice array , has no relationship with channel) 
#define CFG_CMD_REMOTECHANNEL               "RemoteChannel"             // Remote Channel (Corresponding of AV_CFG_RemoteChannel) 
#define CFG_CMD_MONITORTOUR                 "MonitorTour"               // Monitor tour configuration (Corresponding of AV_CFG_MonitorTour) 
#define CFG_CMD_MONITORCOLLECTION           "MonitorCollection"         // Monitor favorite configuration (Corresponding of )
#define CFG_CMD_DISPLAYSOURCE               "DisplaySource"             // Monitor split display source configuration (Corresponding of AV_CFG_ChannelDisplaySource) 
#define CFG_CMD_RAID                        "Raid"                      // Storage group configuration (Corresponding of AV_CFG_Raid array , has no relationship with channel)
#define CFG_CMD_RECORDSOURCE                "RecordSource"              // Record source configuration (Corresponding of AV_CFG_RecordSource) 
#define CFG_CMD_VIDEOCOLOR                  "VideoColor"                // Video input color configuration (Corresponding of AV_CFG_ChannelVideoColor)
#define CFG_CMD_VIDEOWIDGET                 "VideoWidget"               // Video widget configuration (Corresponding of AV_CFG_VideoWidget)
#define CFG_CMD_STORAGEGROUP                "StorageGroup"              // Storage group info. Does not support (Corresponding of AV_CFG_StorageGroup array , has no relationship with channel), 
#define CFG_CMD_LOCALS                      "Locales"                   // Zone configuration (Corresponding of AV_CFG_Locales) 
#define CFG_CMD_LANGUAGE                    "Language"                  // Language (Corresponding of AV_CFG_Language)
#define CFG_CMD_ACCESSFILTER                "AccessFilter"              // Access filter (Corresponding of AV_CFG_AccessFilter) 
#define CFG_CMD_AUTOMAINTAIN                "AutoMaintain"              // Automatic maintenance (Corresponding of AV_CFG_AutoMaintain)
#define CFG_CMD_REMOTEEVENT                 "RemoteEvent"               // Remote device event treatment (Corresponding of AV_CFG_RemoteEvent array ) Does not support.
#define CFG_CMD_MONITORWALL                 "MonitorWall"               // Video wall configuration (Corresponding of AV_CFG_MonitorWall array , has no relationship with channel) 
#define	CFG_CMD_SPLICESCREEN                "VideoOutputComposite"      // Splicing screen configuration (Corresponding of AV_CFG_SpliceScreen array , has no relationship with channel) 
#define CFG_CMD_TEMPERATUREALARM            "TemperatureAlarm"          // Temperature alarm (Corresponding of AV_CFG_TemperatureAlarm, has no relationship with channel) 
#define	CFG_CMD_FANSPEEDALARM               "FanSpeedAlarm"             // Fan speed alarm (Corresponding of AV_CFG_FanSpeedAlarm, has no relationship with channel)
#define CFG_CMD_RECORDBACKUP                "RecordBackupRestore"       // Record restore configuration (Corresponding of AV_CFG_RecordBackup, has no relationship with channel)
#define CFG_CMD_COMM                        "Comm"                      // COM configuration (Corresponding of CFG_COMMGROUP_INFO)
#define	CFG_CMD_NETWORK                     "Network"                   // Network config (Corresponding of CFG_NETWORK_INFO)
#define CFG_CMD_NASEX                       "NAS"                       // NAS configuration, multi server (Corresponding of CFG_NAS_GROUP_INFO_EX)
#define CFG_CMD_LDAP                        "LDAP"                      // LDAP configuration
#define CFG_CMD_ACTIVE_DIR                  "ActiveDirectory"           // Active directory configuration
#define CFG_CMD_FLASH                       "FlashLight"                // Flash light(Corresponding of CFG_FLASH_LIGHT)
#define CFG_CMD_AUDIO_ANALYSERULE           "AudioAnalyseRule"          // Audio analyse rule(Corresponding of CFG_ANALYSERULES_INFO)
#define CFG_CMD_JUDICATURE                  "Judicature"                // Judicature (Corresponding of CFG_JUDICATURE_INFO)
#define CFG_CMD_GOODS_WEIGHT                "CQDTSet"                   // CQDT set(Corresponding of CFG_GOOD_WEIGHT_INFO)
#define CFG_CMD_VIDEOIN	                    "VideoIn"                   // VideoIn(Corresponding of CFG_VIDEO_IN_INFO)
#define CFG_CMD_ENCODEPLAN                  "EncodePlan"                // Encode plan(Corresponding of CFG_ENCODE_PLAN_INFO)
#define CFG_CMD_PICINPIC                    "PicInPic"                  // PicInPic(Corresponding of CFG_PICINPIC_INFO)
#define CFG_CMD_BURNFULL                    "BurnFull"                  // Burn full(Corresponding of CFG_BURNFULL_INFO)
#define CFG_CMD_MASTERSLAVE_GLOBAL          "MasterSlaveTrackerGlobal"  // Master slave tracker global(Corresponding of)
#define CFG_CMD_ANALYSEWHOLE                "VideoAnalyseWhole"         // Video analyse whole(Corresponding of CFG_ANALYSEWHOLE_INFO)
#define CFG_CMD_VIDEO_IN_BOUNDARY           "VideoInBoundary"           // Video in boundary(Corresponding of CFG_VIDEO_IN_BOUNDARY)
#define	CFG_CMD_MONITORWALL_COLLECTION      "MonitorWallCollection"	    // Monitor wall collection(Corresponding of CFG_MONITORWALL_COLLECTION array)
#define CFG_CMD_ANALOGMATRIX                "AnalogMatrix"              // Analog matrix(Corresponding of CFG_ANALOG_MATRIX_INFO)
#define CFG_CMD_ANALOG_MATRIX_PROTOCOL	    "AnalogMatrixProtocol"      // Analog matrix protocol(Corresponding of CFG_ANALOG_MATRIX_PROTOCOL array)
#define	CFG_CMD_VIDEO_OUT_TITLE		        "VideoOutputTitle"          // Video output title(Corresponding of CFG_VIDEO_OUT_TITLE)
#define CFG_CMD_DISK_FLUX_ALARM		        "DiskFluxAlarm"             // Disk flux alarm(Corresponding of CFG_DISK_FLUX_INFO)
#define CFG_CMD_NET_FLUX_ALARM              "NetFluxAlarm"              // Net flux alarm(Corresponding of CFG_NET_FLUX_INFO)
#define CFG_CMD_DVRIP                       "DVRIP"                     // DVRIP(Corresponding of CFG_DVRIP_INFO)
#define CFG_CMD_PARKINGSPACE_SCREEN         "ParkingSpaceScreen"        // Parking space screen(Corresponding of  CFG_PARKINGSPACE_SCREEN_INFO , is group, element max value is DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen)
#define CFG_CMD_PARKINGSPACE_STATUS         "ParkingSpaceCellStatus"    // Parking spaceCell status (Corresponding of  CFG_PARKINGSPACE_STATUS_INFO , is group , element max value is DH_PRODUCTION_DEFNITION.nMaxRoadWays)
#define CFG_CMD_CLIENT_CUSTOM_DATA          "ClientCustomData"          // Client custom data(Corresponding of CFG_CLIENT_CUSTOM_INFO)
#define CFG_CMD_BURN_RECORD_FORMAT          "BurnRecordFormat"          // Burn record format(Corresponding of  CFG_BURN_RECORD_FORMAT)
#define CFG_CMD_MULTIBURN                   "MultiBurn"                 // Multi burn synchronization(Corresponding of CFG_MULTIBURN_INFO)is a group, each group of element means one group multi-disk sync recording and parity
#define	CFG_CMD_ENCODE_ENCRYPT              "EncodeEncrypt"             // Code Encryption Configuration Information( CFG_ENCODE_ENCRYPT_CHN_INFO )
#define CFG_CMD_VIDEO_IN_ZOOM               "VideoInZoom"               // Zoom PTZ channel configuration(Corresponding CFG_VIDEO_IN_ZOOM)
#define CFG_CMD_SNAP                        "Snap"                      //  Snapshot Configuration (Corresponding CFG_SNAP_INFO)
#define CFG_CMD_REMOTE_STORAGE_LIMIT        "RemoteStorageLimit"        // Network Storage Server Limit Configuration(Corresponding CFG_REMOTE_STORAGELIMIT_GROUP)
#define CFG_CMD_SPECIAL_DIR                 "SpecialDirectoryDefine"    // Special Purpose Directory Definitions(Corresponding CFG_SPECIAL_DIR_INFO)
#define CFG_CMD_AUTO_STARTUP_DELAY          "AutoStartupDelay"          // Delay Automatic Boot  after Shutdown Configuration(Corresponding CFG_AUTO_STARTUP_DELAY_INFO)
#define CFG_CMD_CANFILTER                   "CANFilter"                 // CAN Passthrough Configuration(Corresponding CFG_CANFILTER_LIST)
#define CFG_CMD_VIDEOIN_FOCUS               "VideoInFocus"              // Focus Setting(Corresponding CFG_VIDEO_IN_FOCUS)
#define CFG_CMD_ENCODE_ADAPT                "EncodeAdapt"               // Coding Adaptive Configuration(Corresponding CFG_ENCODE_ADAPT_INFO)
#define CFG_CMD_VIDEOANALYSE_CALIBRATE      "VideoAnalyseCalibrate"     // Video Analysis Calibration Configuration(CorrespondingCFG_VIDEO_ANALYSE_CALIBRATEAREA)
#define CFG_CMD_PTZ_PRESET                  "PtzPreset"                 // PTZ Preset Point Configuration(Corresponding structure PTZ_PRESET_INFO)
#define CFG_CMD_TIMESPEEDLIMIT              "TimeSpeedLimit"            // The Values of Speed Limit Time Configuration(Corresponding structure CFG_TIMESPEEDLIMIT_LIST)
#define CFG_CMD_VOICEALERT                  "VoiceAlert"                // Voice Prompt Configuration(Corresponding structure CFG_VOICEALERT_LIST)
#define CFG_CMD_DEVICEKEEPALIVE	            "DeviceKeepAlive"           // Device Keep Alive Configuration (Corresponding structure CFG_DEVICEKEEPALIVELIST)

#define CFG_CMD_AUDIO_SPIRIT                "AudioSpirit"               // Voice Incentive(Corresponding CFG_AUDIO_SPIRIT)
#define CFG_CMD_AUDIO_MATRIX_SILENCE    	"AudioMatrixSilence"   		// Audio matrix silence config (Corresponding CFG_AUDIO_MATRIX_SILENCE)
#define CFG_CMD_AUDIO_MATRIX		        "AudioMatrixConfig"         // Audio matrix config(Corresponding CFG_AUDIO_MATRIX)
#define CFG_CMD_COMPOSE_CHANNEL             "ComposeChannel"            // Synthetic Channel Configuration(Corresponding CFG_COMPOSE_CHANNEL)
#define CFG_CMD_COMPOSE_LINKAGE             "ComposeLinkage"            // Synthetic Channel Configuration, Change exhibit (Corresponding CFG_COMPOSE_CHANNEL)
#define CFG_CMD_LOWER_MATRIX                "LowerMatrix"               // Lower Matrix Configurations(Corresponding CFG_LOWER_MATRIX_LIST) 
#define CFG_CMD_INFRARED_BOARD_TEMPLATE	    "InfraredBoardTemplate"     // Infrared Panel Template(Corresponding CFG_INFRARED_BOARD_TEMPLATE_GROUP)
#define CFG_CMD_INFRARED_BOARD              "InfraredBoard"             // Infrared Panel Template(Corresponding CFG_INFRARED_BOARD_GROUP)
#define CFG_CMD_VIDEOIN_EXPOSURE            "VideoInExposure"           // Exposure Settings(CorrespondingCFG_VIDEOIN_EXPOSURE_INFO)

#define CFG_CMD_ACCESS_GENERAL              "AccessControlGeneral"      // Entrance Guard Basic Configuration(Corresponding CFG_ACCESS_GENERAL_INFO)
#define CFG_CMD_ACCESS_EVENT                "AccessControl"             // Entrance Guard Event Configuration(Corresponding CFG_ACCESS_EVENT_INFO array)     
#define CFG_CMD_WIRELESS                    "Wireless"                  // Wi-Fi Settings(CorrespondingCFG_WIRELESS_INFO)
#define CFG_CMD_ALARMSERVER                 "AlarmServer"               // Alarm Server Configuration(CorrespondingCFG_ALARMCENTER_INFO)
#define CFG_CMD_COMMGLOBAL                  "CommGlobal"                // Alarm Global Configuration(CorrespondingCFG_COMMALARM_INFO)
#define CFG_CMD_ANALOGALARM	                "AnalogAlarm"               // Analog Alarm Channel Configuration(CorrespondingCFG_ANALOGALARM_INFO)
#define CFG_CMD_ALARMOUT                    "AlarmOut"                  // Alarm Output Channel Configuration(CorrespondingCFG_ALARMOUT_INFO)
#define CFG_CMD_NTP                         "NTP"                       // Time Synchronization Server(CorrespondingCFG_NTP_INFO)
#define CFG_CMD_ALARMBELL                   "AlarmBell"                 // Alarm configuration(CorrespondingCFG_ALARMBELL_INFO)
#define CFG_CMD_MOBILE                      "Mobile"                    // Mobile Related Business Configuration(CorrespondingCFG_MOBILE_INFO)
#define CFG_CMD_PHONEEVENTNOTIFY            "PhoneEventNotify"          // (CorrespondingCFG_PHONEEVENTNOTIFY_INFO)
#define CFG_CMD_PSTN_ALARM_SERVER           "PSTNAlarmServer"           // Telephone Alarm Center Configuration(CFG_PSTN_ALARM_CENTER_INFO)
#define CFG_CMD_AUDIO_OUTPUT_VOLUME	        "AudioOutputVolume"	        // Audio Output Volume(CFG_AUDIO_OUTPUT_VOLUME)
#define CFG_CMD_AUDIO_INPUT_VOLUME          "AudioInputVolume"          // Audio Input Volume(CFG_AUDIO_INPUT_VOLUME)
#define	CFG_CMD_AUDIO_MIX_VOLUME			"AudioMixVolume"			// Audio Mix  Volume(CFG_AUDIO_MIX_VOLUME)
#define CFG_CMD_ALARMKEYBOARD               "AlarmKeyboard"	            // Alarm Keyboard Configuration(CFG_ALARMKEYBOARD_INFO)
#define CFG_CMD_POWERFAULT                  "PowerFault"                // Power Failure Configuration(CFG_POWERFAULT_INFO)
#define CFG_CMD_CHASSISINTRUSION            "ChassisIntrusion"          // Chassis Intrusion Alarm(Tamper Alarm) Configuration(CFG_CHASSISINTRUSION_INFO)
#define CFG_CMD_EXALARMBOX                  "ExAlarmBox"                //  Extension Alarm Box Configuration(CFG_EXALARMBOX_INFO)
#define CFG_CMD_EXALARMOUTPUT               "ExAlarmOut"                // Extension Alarm Output Configuration(CFG_EXALARMOUTPUT_INFO)
#define CFG_CMD_EXALARMINPUT                "ExAlarm"                   // Extension Alarm Input Configuration(CFG_EXALARMINPUT_INFO)
#define CFG_CMD_ACCESSTIMESCHEDULE          "AccessTimeSchedule"        // Entrance Guard Card Period of Time(CFG_ACCESS_TIMESCHEDULE_INFO)
#define CFG_CMD_URGENCY	                    "Emergency"                 // Emergency Configuration(CFG_URGENCY_INFO)
#define CFG_CMD_SENSORSAMPLING              "SensorSampling"            // The Sensor Sampling(CFG_SENSORSAMPLING_INFO)
#define CFG_CMD_STP	                        "STP"                       // Ring Network Configuration(CFG_STP_INFO)
#define CFG_CMD_ALARM_SUBSYSTEM	            "AlarmSubSystem"            // Alarm SubConfig(CFG_ALARM_SUBSYSTEM_INFO)
#define CFG_CMD_BATTERY_LOW_POWER           "BatteryLowPowerAlarm"      // Battery Power Min Config(CFG_BATTER_LOW_POWER_INFO)
#define CFG_CMD_SNAPLIKAGE                  "SnapLinkage"               // Snapshot Channel Activation External Config(CFG_SNAPLINKAGE_INFO)
#define CFG_CMD_AUDIOINPUT                  "AudioInput"                // Audio Input Config(CFG_AUDIO_INPUT)
#define CFG_CMD_EMAIL                       "Email"                     // Mail Sending Config(CFG_EMAIL_INFO)
#define CFG_CMD_TRAFFIC_TRANSFER_OFFLINE    "TrafficTransferOffline"    // Send Offline File Config(TRAFFIC_TRANSFER_OFFLINE_INFO)
#define CFG_CMD_COMMSUBSCRIBE		        "CommSubscribe"		        // Order serial data config(CFG_DEVCOMM_SUBSCRIBE)
#define CFG_CMD_PARKINGSPACE_LIGHT_STATE    "ParkingSpaceLightState"    // Vehicle status corresponding spot indicator(CFG_PARKINGSPACE_LIGHT_STATE)
#define CFG_CMD_AIRCONDITION		        "AirCondition"		        // Air conditioner device config(CFG_AIRCONDITION_INFO)
#define CFG_CMD_COMPRESS_PLAY               "CompressPlay"              // Compression playback config(CFG_COMPRESS_PLAY_INFO)
#define CFG_CMD_BUILDING                    "Building"                  // VTO floor config (CFG_BUILDING_INFO)
#define CFG_CMD_BUILDING_EXTERNAL           "BuildingExternal"          // VTO floor expansion config(CFG_BUILDING_EXTERNAL_INFO)
#define CFG_CMD_DIALRULE                    "DialRule"                  // Dial rule (CFG_DIALRULE_INFO)
#define CFG_CMD_OIL_MASS_INFO               "OilMassInfo"               // Vehicle tank config(CFG_OIL_MASS_INFO)
#define CFG_CMD_FISHEYE_INFO                "FishEye"                   // Fish eye detailed info config(CFG_FISHEYE_DETAIL_INFO)
#define CFG_CMD_VTNOANSWER_FORWARD          "VTNoAnswerForward"         // Platform issues call no-response transfer config list(CFG_VT_NOANSWER_FORWARD_INFO)
#define CFG_CMD_VTO_CALL                    "VTOCall"                   // VTO call config (CFG_VTO_CALL_INFO)
#define CFG_CMD_MACCONFLICT                 "MacConflict"               // MAC conflict alarm config(CFG_MACCONFLICT_INFO)
#define CFG_CMD_IDLEMOTION_INFO             "IdleMotion"                // Idle config(CFG_IDLE_MOTION_INFO)
#define CFG_CMD_MONITORWALL_COLL_TOUR       "MonitorWallCollectionTour" // TV wall scheme tour config(CFG_MONITORWALL_COLLECTION_TOUR_INFO)
#define CFG_CMD_PSTN_BREAK_LINE             "PSTNBreakLine"             // PSTN offline event config(CFG_PSTN_BREAK_LINE_INFO)
#define CFG_CMD_NET_COLLECTION              "NetCollection"	            // Network capture device config(CFG_NET_COLLECTION_INFO)
#define CFG_CMD_ALARM_SLOT_BOND             "AlarmSlotBond"             // Virtual Slot node detailed physical device corresponding relation(CFG_ALARM_SLOT_BOND_INFO)
#define CFG_CMD_TRAFFICSTROBE               "TrafficStrobe"             // Gateway config(CFG_TRAFFICSTROBE_INFO)
#define CFG_CMD_TRAFFICVOICE                "TrafficVoiceBroadcast"     // Intelligent traffic audio report config(CFG_TRAFFICVOICE_BROADCAST)
#define CFG_CMD_STANDING_TIME               "StandingTime"              // Oarking time config(CFG_STANDING_TIME_INFO)
#define CFG_CMD_ENCLOSURE_TIME_SCHEDULE     "EnclosureTimeSchedule"     // E-fence alarm period config(CFG_ENCLOSURE_TIME_SCHEDULE_INFO)
#define CFG_CMD_ECKCONFIG                   "ECKConfig"			        // Parking lot entrance/exit controller config(CFG_ECKCONFIG_INFO)
#define CFG_CMD_PARKING_CARD                "ParkingCard"               // Parking lot entrance/exit swiping card alarm event config(CFG_PARKING_CARD_INFO)
#define CFG_CMD_RCEMERGENCY_CALL            "RCEmergencyCall"           // Emergency call alarm event config(CFG_RCEMERGENCY_CALL_INFO)
#define CFG_CMD_LANES_STATE_REPORT          "LanesStateReport"          // Lane info report config(CFG_LANES_STATE_REPORT)
#define CFG_CMD_OPEN_DOOR_GROUP             "OpenDoorGroup"             // Multiple people multi-door combination config(CFG_OPEN_DOOR_GROUP_INFO)
#define CFG_CMD_OPEN_DOOR_ROUTE             "OpenDoorRoute"             // Unlock path collection?ê?or anti-passby path config(CFG_OPEN_DOOR_ROUTE_INFO)
#define CFG_CMD_BURNPLAN                    "BurnPlan"                  // Burning plan config(corresponding to CFG_BURNPLAN_INFO)
#define CFG_CMD_SCADA_DEV                   "SCADADev"                  // Detect collection device config(CFG_SCADA_DEV_INFO)
#define CFG_CMD_VSP_GAYS                    "VSP_GAYS"                  // Public security 1 platform input config(CFG_VSP_GAYS_INFO)
#define CFG_CMD_AUDIODETECT                 "AudioDetect"               // Audio detection alarm config(CFG_AUDIO_DETECT_INFO group)
#define CFG_CMD_GUIDESCREEN                 "GuideScreen"               // Guide screen config(CFG_GUIDESCREEN_INFO)
#define CFG_CMD_VTS_CALL_INFO               "VTSCallInfo"               // VTS call config(CFG_VTS_CALL_INFO)
#define CFG_CMD_DEV_LIST                    "DevList"                   // The list of device config(CFG_DEV_LIST_INFO)
#define CFG_CMD_CALIBRATE_MATRIX            "CalibrateMatrix"           // Calibrate matrix config info(CFG_CALIBRATE_MATRIX_INFO)
#define CFG_CMD_DEFENCE_AREA_DELAY          "DefenceAreaDelay"          // Defence area delay config(CFG_DEFENCE_AREA_DELAY_INFO)
#define CFG_CMD_THERMO_GRAPHY               "ThermographyOptions"       // Thermal imaging camera property config(CFG_THERMOGRAPHY_INFO)
#define CFG_CMD_THERMOMETRY_RULE            "ThermometryRule"           // Thermal imaging temperature measurement rule config(CFG_THERMOMETRY_RULE_INFO)
#define CFG_CMD_TEMP_STATISTICS             "TemperatureStatistics"     // Temperature statistics config(CFG_TEMP_STATISTICS_INFO)
#define CFG_CMD_THERMOMETRY                 "HeatImagingThermometry"    // Thermal imaging temperature measurement global config(CFG_THERMOMETRY_INFO)
#define CFG_CMD_LIGHTING                    "Lighting"                  // Configuration of lighting(CFG_LIGHTING_INFO)
#define CFG_CMD_RAINBRUSHMODE               "RainBrushMode"             // Rain brush mode(CFG_RAINBRUSHMODE_INFO)
#define CFG_CMD_LIGHTINGSCHEDULE            "LightingSchedule"			// Lighting Schedule (CFG_LIGHTINGSCHEDULE_INFO)
#define CFG_CMD_EMERGENCY_RECORD_FOR_PULL   "EmergencyRecordForPull"    // Emergency record for pull when there is someting wrong with pulling(CFG_EMERGENCY_RECORD_FOR_PULL_INFO)
#define CFG_CMD_ALARM_SHIELD_RULE           "AlarmShieldRule"           // Alarm shield rule(CFG_ALARM_SHIELD_RULE_INFO)
#define CFG_CMD_VIDEOIN_ANALYSERULE         "VideoInAnalyseRule"        // Video in analyse rule(CFG_VIDEOIN_ANALYSE_RULE_INFO)
#define CFG_CMD_ACCESS_WORK_MODE            "AccessWorkMode"            // Access work mode(CFG_ACCESS_WORK_MODE_INFO)
#define CFG_CMD_VIDEO_TALK_PHONE_GENERAL    "VideoTalkPhoneGeneral"     // Video talk call general config(CFG_VIDEO_TALK_PHONE_GENERAL)
#define CFG_CMD_TRAFFIC_SNAP_MOSAIC         "TrafficSnapMosaic"         // Snapshot combination config(corresponding to CFG_TRAFFIC_SNAP_MOSAIC_INFO)
#define CFG_CMD_SCENE_SNAP_RULE             "SceneSnapShotWithRule"     // Scene snapshot setup(corresponding to CFG_SCENE_SNAPSHOT_RULE_INFO)
#define CFG_CMD_PTZTOUR                     "PtzTour"                   // PTZ patrol path config (corresponding to CFG_PTZTOUR_INFO)
#define CFG_CMD_VTO_INFO                    "VTOInfo"                   // VTO config (corresponding to CFG_VTO_LIST)
#define CFG_CMD_TS_POINT                    "TSPoint"                   // Touch screen calibration config (corresponding toCFG_TSPOINT_INFO)
#define CFG_CMD_VTH_NUMBER_INFO             "VTHNumberInfo"             // VTH no. info (corresponding to CFG_VTH_NUMBER_INFO)
#define CFG_CMD_GPS                         "GPS"                       // GPS config (corresponding to CFG_GPS_INFO_ALL)
#define CFG_CMD_VTO_BASIC_INFO              "VTOBasicInfo"              // VTO basic info (corresponding to CFG_VTO_BASIC_INFO)
#define CFG_CMD_SHORTCUT_CALL               "ShortcutCall"              // Quick no. config (corresponding to CFG_SHORTCUT_CALL_INFO)
#define CFG_CMD_GPS_LOCATION_VER            "GPSLocationVersion"        // Record GPSLocation  version no.(corresponding toCFG_LOCATION_VER_INFO)
#define CFG_CMD_PARKING_SPACE_ACCESS_FILTER "ParkingSpaceAccessFilter"  // Access filter(corresponding to CFG_PARKING_SPACE_ACCESS_FILTER_INFO)
#define CFG_CMD_WORK_TIME                   "WorkTime"                  // work time config(corresponding to CFG_WORK_TIME_INFO)
#define CFG_CMD_PARKING_SPACE_LIGHT_GROUP   "ParkingSpaceLightGroup"    // Parking Space Light Group config(corresponding to CFG_PARKING_SPACE_LIGHT_GROUP_INFO_ALL)
#define CFG_CMD_CUSTOM_AUDIO                "CustomAudio"               // Custom audio(CFG_CUSTOM_AUDIO)
#define CFG_CMD_WIFI_SEARCH                 "AroudWifiSearch"           // configuration of search wifi device(corresponding to CFG_WIFI_SEARCH_INFO)
#define CFG_CMD_G3G4AUTOCHANGE              "G3G4AutoChange"            // vehicle-mounted communication module 3G/4G auto change(CFG_G3G4AUTOCHANGE)
#define CFG_CMD_CHECKCODE                   "CheckCode"                 // POS checkcode(corresponding to CFG_CHECKCODE_INFO)
#define CFG_CMD_VSP_SCYDKD                  "VSP_SCYDKD"                // configuration of Sichuan Mobile keep an eye on shop(corresponding to CFG_VSP_SCYDKD_INFO)
#define CFG_CMD_VIDEOIN_DAYNIGHT            "VideoInDayNight"           // day/night color change config (CFG_VIDEOIN_DAYNIGHT_INFO)
#define CFG_CMD_PTZ_POWERUP                 "PowerUp"                   // ptz power up action config ( CFG_PTZ_POWERUP_INFO)
#define CFG_CMD_AUDIO_MIX_CHANNEL           "AudioMixChannel"           // configuration of audio mix channel(corresponding to CFG_AUDIO_MIX_CHANNEL_INFO_ALL)
#define CFG_CMD_AUDIO_TOUCH                 "AudioTouch"                // configuration of audio pitch,change pitch(corresponding to CFG_AUDIO_TOUCH_INFO_ALL)
#define	CFG_CMD_VIDEO_MOSAIC				"VideoMosaic"				// configuration of video mosaic(corresponding to CFG_VIDEO_MOSAIC_INFO)
#define CFG_CMD_VTH_REMOTE_IPC_INFO         "VTHRemoteIPCInfo"          // configuration of VTH's remote IPC(corresponding to CFG_VTH_REMOTE_IPC_INFO), this config is global, not for single channel 
#define CFG_CMD_UNFOCUSDETECT               "UnFocusDetect"             // unFocusDetect alarm setup( CFG_UNFOCUSDETECT_INFO)
#define	CFG_CMD_MOVE_DETECT					"MovedDetect"				// configuration of scene moved detect(corresponding to CFG_MOVE_DETECT_INFO)
#define CFG_CMD_FLOODLIGHT                  "Floodlight"                // configuration of protection flood light(corresponding CFG_FLOODLIGHT_CONTROLMODE_INFO)
#define CFG_CMD_AIRFAN                      "AirFan"                    // configuration of protection airfan(corresponding CFG_AIRFAN_CONTROLMODE_INFO)
#define CFG_CMD_WLAN                        "WLan"                      // configuration of WLAN(corresponding to CFG_NETAPP_WLAN)
#define CFG_CMD_SMART_ENCODE				"SmartEncode"				// Smart H264 code (corresponding to CFG_SMART_ENCODE_INFO)
#define CFG_CMD_VEHICLE_HIGH_SPEED			"HighSpeed"					// vehicle mounted high speed alarm config(corresponding to CFG_VEHICLE_HIGHSPEED_INFO )
#define CFG_CMD_VEHICLE_LOW_SPEED			"LowSpeed"					// vehicle mounted low speed alarm config(corresponding to CFG_VEHICLE_LOWSPEED_INFO )
#define CFG_CMD_PSTN_PERSON_SERVER			"PSTNPersonServer"			// configuration of answer the personal telephone(corresponding to CFG_PSTN_PERSON_SERVER_INFO_ALL )
#define CFG_CMD_ARM_LINK                	"ArmLink"			        // configuration of Arm or disarm(corresponding to CFG_ARMLINK_INFO )

 /************************************************************************
 /************************************************************************
 ** Capacity set command  Corresponding of CLIENT_QueryNewSystemInfo
 ***********************************************************************/

#define CFG_CAP_CMD_VIDEOANALYSE			"devVideoAnalyse.getCaps"					// Video analyze capability(CFG_CAP_ANALYSE_INFO)
#define CFG_NETAPP_REMOTEDEVICE				"netApp.getRemoteDeviceStatus"				// Get back end device's online state(struct CFG_REMOTE_DEVICE_STATUS)
#define CFG_CAP_CMD_PRODUCTDEFINITION		"magicBox.getProductDefinition"				// Access equipment information
#define CFG_DEVICE_CAP_CMD_VIDEOANALYSE		"intelli.getVideoAnalyseDeviceChannels"		// Device video analyze capability(struct CFG_DEVICE_ANALYSE_INFO)
#define CFG_DEVICE_CAP_NEW_CMD_VIDEOANALYSE "devVideoAnalyse.factory.getCollect"		// Device video analyze capability(struct CFG_DEVICE_ANALYSE_INFO)
#define CFG_CAP_CMD_CPU_COUNT				"magicBox.getCPUCount"						// Get CPU number
#define CFG_CAP_CMD_CPU_USAGE				"magicBox.getCPUUsage"						// Get CPU usage
#define CFG_CAP_CMD_MEMORY_INFO				"magicBox.getMemoryInfo"					// Get memory info
#define CFG_CAP_CMD_DEVICE_STATE			"trafficSnap.getDeviceStatus"				// Get device status
#define CFG_CAP_CMD_VIDEOINPUT				"devVideoInput.getCaps"						// The caps of video input(struct CFG_CAP_VIDEOINPUT_INFO)
#define CFG_USERMANAGER_ACTIVEUSER			"userManager.getActiveUserInfoAll"			// Get all active user info (Corresponding of CFG_ACTIVEUSER_INFO)
#define CFG_CAP_VIDEOSTAT_SUMMARY			"videoStatServer.getSummary"				// Get video statistic summary info(Corresponding of CFG_VIDEOSATA_SUMMARY_INFO) 
#define CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER	"videoDiagnosisServer.getCaps"				//  Get video diagnosis server capacity (CFG_VIDEODIAGNOSIS_CAPS_INFO)
#define CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT   "videoDiagnosisServer.factory.getCollect"	// Get video diagnosis factory number (CFG_VIDEODIAGNOSIS_GETCOLLECT_INFO) 
#define CFG_CMD_VIDEODIAGNOSIS_GETSTATE     "videoDiagnosisServer.getState"				// Get video diagnosis in process state (CFG_VIDEODIAGNOSIS_STATE_INFO)
#define CFG_CAP_CMD_SERVICE_LIST            "system.listService"						// Get list of supported service from server
#define CFG_CAP_CMD_EVENTHANDLER            "capsManager.get&EventManagerEventHandler"  // To obtain a list server up adn supported by server(CFG_CAP_EVENTHANDLER_INFO)
#define CFG_CAP_ALARM                       "alarm.getAlarmCaps"                        // Get alarm capacity(CFG_CAP_ALARM_INFO)
#define CFG_CAP_CMD_AUDIO_ANALYSE           "devAudioAnalyse.getCaps"                   // Get audio analyse capacity(CFG_CAP_AUDIO_ANALYSE_INFO)
#define CFG_CMD_MASTERSLAVE_GETCOLLECT      "masterSlaveTracker.factory.getCollect"     // Get channel number of master-slave tracker(CFG_MASTERSLAVETRACKER_INFO)
#define CFG_CAP_CMD_MASTERSLAVE             "capsManager.get&MasterSlaveTracker"        // Get capacity of master-slave tracker(CFG_CAP_MASTERSLAVE_INFO)
#define CFG_CAP_CMD_FOCUS_STATE             "devVideoInput.getFocusStatus"              // Get focus status of lens (CFG_CAP_FOCUS_STATUS)
#define CFG_CAP_CMD_NETAPP                  "netApp.getCaps"                            // Get capacity of net app(CFG_CAP_NETAPP)
#define CFG_CAP_CMD_PTZ_ENABLE              "ptz.factory.instance"                      //Get cloud platform support information(CFG_CAP_PTZ_ENABLEINFO )
#define CFG_CAP_CMD_RECORD                  "recordManager.getCaps"                     // Get capacity of record manager(CFG_CAP_RECORD_INFO)
#define CFG_CAP_CMD_BURN_MANAGER            "BurnManager.getCaps"                       // Get capacity of burn manager( CFG_CAP_BURN_MANAGER)
#define CFG_CAP_CMD_PTZ                     "ptz.getCurrentProtocolCaps"                // Get PTZ capability set(CFG_PTZ_PROTOCOL_CAPS_INFO)
#define CFG_CMD_ENCODE_GETCAPS              "encode.getCaps"                            // Get Encoding Capability set(CFG_ENCODECAP)
#define CFG_CAP_CMD_VIDEOINPUT_EX           "devVideoInput.getCapsEx"                   // Video Input Capability set extension(CorrespondingCFG_CAP_VIDEOINPUT_INFO_EX)
#define CFG_CAP_CMD_ANALYSE_MODE            "intelli.getCaps.AnalyseMode"               // Get Device Intelligent analysis mode(Corresponding CFG_ANALYSE_MODE)
#define CFG_CAP_CMD_EVENTMANAGER            "eventManager.getCaps"                      // The Ability to obtain equipment alarm linkage,The old agreement has been abolished,Please use the newly developed field(CFG_CAP_EVENTMANAGER_INFO)
#define CFG_CAP_CMD_FILEMANAGER             "FileManager.getCaps"                       // The Ability to Obtain Documents(CFG_CAP_FILEMANAGER)
#define	CFG_CAP_CMD_LOG                     "log.getCaps"                               // Get the Log Service Capabilities(CFG_CAP_LOG)
#define CFG_CAP_CMD_SPEAK                   "speak.getCaps"                             // Speaker Play Capability(CFG_CAP_SPEAK)
#define CFG_CAP_CMD_ACCESSCONTROLMANAGER    "accessControlManager.getCaps"              // Entrance Guard Capability(CFG_CAP_ACCESSCONTROL)
#define CFG_CAP_CMD_EXALARM                 "alarm.getExAlarmCaps"                      // Get Extension Alarm Capability set (CorrespondingStructure CFG_CAP_EXALARM_INFO)
#define CFG_CAP_CMD_EXALARMBOX              "alarm.getExAlarmBoxCaps"                   // Get Extension Alarm Boxes Capability set, (CorrespondingStructure CFG_CAP_EXALARMBOX_INFO)
#define CFG_CAP_CMD_RECORDFINDER            "RecordFinder.getCaps"                      // Get Query Records Capability set (CorrespondingStructure CFG_CAP_RECORDFINDER_INFO)
#define CFG_CAP_CMD_ANALOGALARM             "AnalogAlarm.getCaps"                       // Analog Alarm Input Channel Capacity(CorrespondingStructure CFG_CAP_ANALOGALARM)
#define CFG_CAP_CMD_LOWRATEWPAN	            "LowRateWPAN.getCaps"                       // Get LowRateWPAN capacity(corresponding structure CFG_CAP_LOWRATEWPAN)

// Log Capability
typedef struct tagCFG_CAP_LOG
{
    DWORD       dwMaxLogItems;      //  The Maximum Log Number 
    DWORD       dwMaxPageItems;     //  The Maximum Log Number of Each Page
    BOOL        bSupportStartNo;    //  Query Whether to Support the Initial Sequence  Number
    BOOL        bSupportTypeFilter;	//  Query Whether to Support the Type Filter
    BOOL        bSupportTimeFilter;	//  Query Whether to Support the Time Filter
}CFG_CAP_LOG;


#define MAX_AUDIO_PROPERTY_NUM       32          //  Maximum Number of Audio Attribute
#define MAX_AUDIO_FORMAT_NUM         16          //  Maximum Number of Audio Format

//  Audio Encoding Compression Format
enum EM_TALK_AUDIO_TYPE
{
	EM_TALK_AUDIO_PCM,
	EM_TALK_AUDIO_ADPCM, 
	EM_TALK_AUDIO_G711A, 
	EM_TALK_AUDIO_G711Mu, 
	EM_TALK_AUDIO_G726, 
	EM_TALK_AUDIO_G729, 
	EM_TALK_AUDIO_MPEG2, 
	EM_TALK_AUDIO_AMR, 
	EM_TALK_AUDIO_AAC, 
};

// Audio Properties
typedef struct CFG_AUDIO_PROPERTY
{
    int            nBitRate;               // Stream Size?ê?Unit:kbps?ê?such as 192kbps
    int            nSampleBit;             // Sampling Depth?ê?such as8 or 16
    int            nSampleRate;            // Sampling Frequency?ê?Unit:Hz?ê?such as 44100Hz
}CFG_AUDIO_PROPERTY;

//  Supports Audio Formats
typedef struct CFG_CAP_AUDIO_FORMAT
{
    EM_TALK_AUDIO_TYPE  emCompression;          // Audio Compressed Format?ê?See the enumeration AV_Talk_Audio_Type
    int                 nPropertyNum;           // Audio Properties Number
    CFG_AUDIO_PROPERTY  stuProperty[MAX_AUDIO_PROPERTY_NUM]; // Audio Properties
}CFG_CAP_AUDIO_FORMAT;

// The Speaker Ability
typedef struct CFG_CAP_SPEAK
{
    int                     nAudioCapNum;                      // The Number of Audio Formats Supported
    CFG_CAP_AUDIO_FORMAT    stuAudioCap[MAX_AUDIO_FORMAT_NUM]; // Supported Audio Formats 
}CFG_CAP_SPEAK;

//  Entrance Guard Control Ability
typedef struct tagCFG_CAP_ACCESSCONTROL
{
    int	                    nAccessControlGroups;              //  Class Number of Entrance Guard
}CFG_CAP_ACCESSCONTROL;

//  Enumeration Type Sensor Sensing Way
typedef enum tagEM_SENSE_METHOD
{
    EM_SENSE_UNKNOWN = -1,       // Unknown type
    EM_SENSE_DOOR=0,             // Magnetic Door
    EM_SENSE_PASSIVEINFRA,       // Passive Infrared
    EM_SENSE_GAS,                // Gas Sense 
    EM_SENSE_SMOKING,            // Smoking Sense
    EM_SENSE_WATER,              // Water Sense
    EM_SENSE_ACTIVEFRA,          // Active Infrared
    EM_SENSE_GLASS,	             // Glass Broken
    EM_SENSE_EMERGENCYSWITCH,    // EMERGENCY SWITCH
    EM_SENSE_SHOCK,              // Shock
    EM_SENSE_DOUBLEMETHOD,       // Double Method(Infrared+Microwave)
    EM_SENSE_THREEMETHOD,        // Three Method
    EM_SENSE_TEMP,               // Temperature
    EM_SENSE_HUMIDITY,           // Humidity
    EM_SENSE_WIND,               // Wind
    EM_SENSE_CALLBUTTON,         // Call Button
    EM_SENSE_GASPRESSURE,        // Gas Pressure
    EM_SENSE_GASCONCENTRATION,   // Gas Concentration
    EM_SENSE_GASFLOW,            // Gas Flow
    EM_SENSE_OIL,                // Oil
    EM_SENSE_MILEAGE,            // Mileage
    EM_SENSE_OTHER,              // Other
    EM_SENSE_NUM                 // The Total Number of Enumerated Types
}EM_SENSE_METHOD;


// Sensor Alarm way
typedef struct tagCFG_EXALARM_SENSE_METHOD
{
    int                 nSupportSenseMethodNum;                             // The number of supported sensors way
    EM_SENSE_METHOD     emSupportSenseMethod[MAX_ALARM_SENSE_METHOD_NUM];   // Supported sensor way
}CFG_EXALARM_SENSE_METHOD;

// Analog Alarm Input Channel Capacity
typedef struct tagCFG_CAP_ANALOGALARM 
{
    DWORD                       dwLocalNum;                                 // Local Analog Alarm Input Channel number
    DWORD                       dwExLocalNum;                               //  Expand Analog Alarm input channel number
    int                         nAnalogAlarmChannelNum;                     // Analog Alarm Channel number, Zero said each channel support for all types of sensors
    CFG_EXALARM_SENSE_METHOD    stuAnalogAlarmChannel[MAX_EXALARM_CHANNEL_NUM];	// Alarm Channel Set
}CFG_CAP_ANALOGALARM;

// Get LowRateWPAN capacity structure
typedef struct tagCFG_CAP_LOWRATEWPAN
{
	int			nMaxPageSize;			// Max page search code items
}CFG_CAP_LOWRATEWPAN;

//the scene
typedef enum tagEM_SCENE_TYPE
{
	EM_SECNE_UNKNOW,			// Unknown type
	EM_SCENE_NORMAL,			// "Normal" 
	EM_SCENE_TRAFFIC,			// "Traffic" 
	EM_SCENE_TRAFFIC_PATROL,	// "TrafficPatrol" 
	EM_SCENE_FACEDETECTION,		// "FaceDetection" 
	EM_SCENE_ATM,				// "ATM"
	EM_SENCE_INDOOR,			// "Indoor"  
	EM_SENCE_FACERECOGNITION,	// "FaceRecognition" 
	EM_SENCE_PRISON,			// "Prison"
	EM_SENCE_NUMBERSTAT,		// "NumberStat" 
	EM_SENCE_HEAT_MAP,			// "HeatMap"
	EM_SENCE_VIDEODIAGNOSIS,	// "VideoDiagnosis" 
	EM_SENCE_VEHICLEANALYSE,	// "VehicleAnalyse" 
	EM_SENCE_COURSERECORD,		// "CourseRecord"
	EM_SENCE_VEHICLE,			// "Vehicle" 
    EM_SENCE_STANDUPDETECTION	// "StandUpDetection" 
	}EM_SCENE_TYPE;


/************************************************************************
 ** fAnalyzerData call function dwDataType type definition 
 ***********************************************************************/
#define    TYPE_CB_VIDEOSTAT            0x1000000      // Callback and analyze video state summary type, corresponding composition is CFG_VIDEOSATA_SUMMARY_INFO
#define    TYPE_CB_ANARULES             0x1000001      //  Callback and analyze all event rule type that corresponding to video input factory, corresponding composition is CFG_ANALYSERULES_INFO
#define    TYPE_CB_VIDEOSYNOPSIS        0x1000002      // Callback and analyze condensed the intelligence of video frames,corresponding composition is DH_MSG_OBJECT
#define	   TYPE_CB_TRAFFICFLOWINFO      0x1000003      // Back to the Mediation Analysis Traffic Flow Information?ê?CorrespondingStructureDEV_EVENT_TRAFFIC_FLOWSTAT_INFO	
#define    TYPE_CB_TRAFFICFLOWRULE      0x1000004      // Back to the Mediation Rules of Traffic Flow Information?ê?CorrespondingStructure CFG_TRAFFIC_FLOWSTAT_INFO 	
#define    TYPE_CB_VIDEOSYNOPSIS_RULE   0x1000005      // Callback parsing rules enrichment video information corresponding to the structure NET_VIDEOSYNOPSISRULE_INFO	
/************************************************************************
 ** Configuration Information (There is competence information for each structure to distinguish different device models and application versions. )
 ***********************************************************************/

// Protocol version info
enum 
{
	CFG_PROTOCOL_VERSION_2 = 2,						// The 2nd protocol 
	CFG_PROTOCOL_VERSION_3 = 3						// The 3rd protocol
};

// Video input channel
struct CFG_RemoteDeviceVideoInput 
{
	BOOL			bEnable;
	char			szName[MAX_DEVICE_NAME_LEN];
	char			szControlID[MAX_DEV_ID_LEN_EX];
	char			szMainUrl[MAX_PATH];			// Main stream url address
	char			szExtraUrl[MAX_PATH];			// Extra stream url address
	int				nServiceType;					// Service type, 0-TCP, 1-UDP, 2-MCAST, -1-AUTO
};

// Remote device
struct AV_CFG_RemoteDevice 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// Enable
	char				szID[AV_CFG_Device_ID_Len];		// Device ID
	char				szIP[AV_CFG_IP_Address_Len];	// Device IP
	AV_int32			nPort;							// Port
	char				szProtocol[AV_CFG_Protocol_Len];// Protocol type
	char				szUser[AV_CFG_User_Name_Len];	//User name
	char				szPassword[AV_CFG_Password_Len];// Password
	char				szSerial[AV_CFG_Serial_Len];	// Device serial number
	char				szDevClass[AV_CFG_Device_Class_Len];// Device class
	char				szDevType[AV_CFG_Device_Type_Len];	// Device type
	char				szName[AV_CFG_Device_Name_Len];	// Device name
	char				szAddress[AV_CFG_Address_Len];	// Device deploy address
	char				szGroup[AV_CFG_Group_Name_Len];	// Device group name
	AV_int32			nDefinition;					// Definition, 0-standard definition, 1-high definition
	AV_int32			nVideoChannel;					// Number of vodeo input channel
	AV_int32			nAudioChannel;					// Number of audio input channel
	AV_int32            nRtspPort;                      // Rtsp port
	char                szVendor[MAX_PATH];             // Access device type
	CFG_RemoteDeviceVideoInput *pVideoInput;            // Video input channel,user apply nMaxVideoInputs * CFG_RemoteDeviceVideoInput space
	int                 nMaxVideoInputs;
	int                 nRetVideoInputs;
    int                 nHttpPort;                      //Http  Port Number
	AV_BOOL				bGB28181;						// Support GB28181
	int					nDevLocalPort;					// Device local port
	char				szDeviceNo[AV_CFG_DeviceNo_Len];// Device number
};

//-----------------------------Image channel property-------------------------------

// Image quality 
typedef enum tagCFG_IMAGE_QUALITY
{
	IMAGE_QUALITY_Q10 = 1,							// Image quality 10%
	IMAGE_QUALITY_Q30,								// Image quality 30%
	IMAGE_QUALITY_Q50,								// Image quality 50%
	IMAGE_QUALITY_Q60,								// Image quality 60%
	IMAGE_QUALITY_Q80,								// Image quality 80%
	IMAGE_QUALITY_Q100,								// Image quality 100%
} CFG_IMAGE_QUALITY;

// Video compression format 
typedef enum tagCFG_VIDEO_COMPRESSION
{
	VIDEO_FORMAT_MPEG4,								// MPEG4
	VIDEO_FORMAT_MS_MPEG4,							// MS-MPEG4
	VIDEO_FORMAT_MPEG2,								// MPEG2
	VIDEO_FORMAT_MPEG1,								// MPEG1
	VIDEO_FORMAT_H263,								// H.263
	VIDEO_FORMAT_MJPG,								// MJPG
	VIDEO_FORMAT_FCC_MPEG4,							// FCC-MPEG4
	VIDEO_FORMAT_H264,								// H.264
    VIDEO_FORMAT_H265,								// H.265
	VIDEO_FORMAT_SVAC,								// SVAC
} CFG_VIDEO_COMPRESSION;
// audio coding mode
typedef enum tatCFG_AUDIO_FORAMT
{
	AUDIO_FORMAT_G711A,                              // G711a
    AUDIO_FORMAT_PCM,                                // PCM
    AUDIO_FORMAT_G711U,                              // G711u
    AUDIO_FORMAT_AMR,                                // AMR
    AUDIO_FORMAT_AAC,                                // AAC
} CFG_AUDIO_FORMAT;

// Bit stream control mode 
typedef enum tagCFG_BITRATE_CONTROL
{
	BITRATE_CBR,									// Constant bit rate (CBR)
	BITRATE_VBR,									// Variable bit rate (VBR)
} CFG_BITRATE_CONTROL;

// H264 Encode Level
typedef enum tagCFG_H264_PROFILE_RANK
{
	PROFILE_BASELINE = 1,                           // Offer I/P Frame?ê?Only support progressive(Progressive Scan)and CAVLC
	PROFILE_MAIN,                                   // Offer I/P/B Frame?ê?Support progressiv and interlaced?ê?Offer CAVLC or CABAC
	PROFILE_EXTENDED,                               // Offer I/P/B/SP/SI Frame?ê?Only support progressive(Progressive Scan)and CAVLC
	PROFILE_HIGH,                                   // FRExt?ê?Main_Profile Based on the new?êo8x8 intra prediction(8x8 Intra-frame Predicdion), custom 
												    // Quant(custom quant ), lossless video coding(lossless video encoding), more yuv format
}CFG_H264_PROFILE_RANK;

// Resolution enumeration
typedef enum tagCFG_CAPTURE_SIZE
{
	IMAGE_SIZE_D1,								// 704*576(PAL)  704*480(NTSC)
	IMAGE_SIZE_HD1,								// 352*576(PAL)  352*480(NTSC)
	IMAGE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	IMAGE_SIZE_CIF,								// 352*288(PAL)  352*240(NTSC)
	IMAGE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	IMAGE_SIZE_VGA,								// 640*480
	IMAGE_SIZE_QVGA,							// 320*240
	IMAGE_SIZE_SVCD,							// 480*480
	IMAGE_SIZE_QQVGA,							// 160*128
	IMAGE_SIZE_SVGA,							// 800*592
	IMAGE_SIZE_XVGA,							// 1024*768
	IMAGE_SIZE_WXGA,							// 1280*800
	IMAGE_SIZE_SXGA,							// 1280*1024  
	IMAGE_SIZE_WSXGA,							// 1600*1024  
	IMAGE_SIZE_UXGA,							// 1600*1200
	IMAGE_SIZE_WUXGA,							// 1920*1200
	IMAGE_SIZE_LTF,								// 240*192
	IMAGE_SIZE_720,								// 1280*720
	IMAGE_SIZE_1080,							// 1920*1080
	IMAGE_SIZE_1_3M,							// 1280*960
	IMAGE_SIZE_2M,							    // 1872*1408
	IMAGE_SIZE_5M,						   	    // 3744*1408
	IMAGE_SIZE_3M,							    // 2048*1536
	IMAGE_SIZE_5_0M,                            // 2432*2050
	IMAGE_SIZE_1_2M,							// 1216*1024
	IMAGE_SIZE_1408_1024,                       // 1408*1024
	IMAGE_SIZE_8M,                              // 3296*2472
	IMAGE_SIZE_2560_1920,                       // 2560*1920(5M)
	IMAGE_SIZE_960H,                            // 960*576(PAL) 960*480(NTSC)
	IMAGE_SIZE_960_720,                         // 960*720
	IMAGE_SIZE_NHD,							    // 640*360
	IMAGE_SIZE_QNHD,							// 320*180
	IMAGE_SIZE_QQNHD,							// 160*90
	IMAGE_SIZE_NR  
} CFG_CAPTURE_SIZE;

// Video format
typedef struct tagCFG_VIDEO_FORMAT
{
	// Competence 
	bool				abCompression;
	bool				abWidth;
	bool				abHeight;
	bool				abBitRateControl;
	bool				abBitRate;
	bool				abFrameRate;
	bool				abIFrameInterval;
	bool				abImageQuality;
	bool				abFrameType;
	bool				abProfile;

	// Information
	CFG_VIDEO_COMPRESSION emCompression;			// Video compression mode 
	int					nWidth;						// Video width
	int					nHeight;					// Video height
	CFG_BITRATE_CONTROL	emBitRateControl;			// Bit rate control mode 
	int					nBitRate;					// Video bit rate (kbps)
    float               nFrameRate;                 // Frame Rate 
	int					nIFrameInterval;			// I frame interval(1-100). For example, 50 means there is I frame in each 49 B frame or P frame.
	CFG_IMAGE_QUALITY	emImageQuality;				// Video quality 
	int					nFrameType;					// Sniffer mode,0-DHAV,1-"PS"
    CFG_H264_PROFILE_RANK emProfile;                // H.264 Encode level
} CFG_VIDEO_FORMAT;

// Audio format
typedef struct tagCFG_AUDIO_FORMAT 
{
	// Capacity 
	bool				abCompression;
	bool				abDepth;
	bool				abFrequency;
	bool				abMode;
	bool				abFrameType;
	bool				abPacketPeriod;

	//Info
	CFG_AUDIO_FORMAT	emCompression;				// Audio compression mode
	AV_int32			nDepth;						// Audio sampling depth
	AV_int32			nFrequency;					// Audio sampling frequency
	AV_int32			nMode;						// Audio encode mode
	AV_int32			nFrameType;					// 0-DHAV, 1-PS Audio pack mode
	AV_int32			nPacketPeriod;				// Audio pack period(ms)
} CFG_AUDIO_ENCODE_FORMAT;

// Video encode parameter
typedef struct tagCFG_VIDEOENC_OPT
{
	// Competence
	bool				abVideoEnable;
	bool				abAudioEnable;
	bool				abSnapEnable;
	bool                abAudioAdd;                 // Audio overlay capacity
	bool				abAudioFormat;

	// Information
	BOOL				bVideoEnable;				// Video enable
	CFG_VIDEO_FORMAT	stuVideoFormat;				// Video format
	BOOL				bAudioEnable;				// Audio enable
	BOOL				bSnapEnable;				// Schedule snapshot enable
	BOOL                bAudioAddEnable;            // Audio add enable
	CFG_AUDIO_ENCODE_FORMAT	stuAudioFormat;			// Audio format
} CFG_VIDEOENC_OPT; 

// RGBA information
typedef struct tagCFG_RGBA
{
	int					nRed;
	int					nGreen;
	int					nBlue;
	int					nAlpha;
} CFG_RGBA;

// Zone information
typedef struct tagCFG_RECT
{
	int					nLeft;
	int					nTop;
    int					nRight;
    int					nBottom;				
} CFG_RECT;

// Zone point info
typedef struct tagCFG_POLYGON
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYGON;

//Region information
typedef struct tagCFG_REGION
{
	int         nPointNum;
	CFG_POLYGON stuPolygon[MAX_POLYGON_NUM];
}CFG_REGION;

// Line point info
typedef struct tagCFG_POLYLINE
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYLINE;

typedef enum tagCFG_FLOWSTAT_DIRECTION
{
    CFG_DRIVING_DIR_APPROACH,           //Upstream?ê?The vehicle is getting closer and closer to equipment deployment point
    CFG_DRIVING_DIR_LEAVE,              //Downstream?ê?The vehicle is getting farther and farther to equipment deployment point
}CFG_FLOWSTAT_DIRECTION;

#define  CFG_FLOWSTAT_ADDR_NAME			16						//Place Names Length of Upstream and Downstream 
// Vehicle Flow Statistics Lane Direction Information
typedef struct tagCFG_TRAFFIC_FLOWSTAT_DIR_INFO
{
	CFG_FLOWSTAT_DIRECTION		emDrivingDir;							//Driving Direction
	char						szUpGoing[CFG_FLOWSTAT_ADDR_NAME];			//Upstream Location
	char						szDownGoing[CFG_FLOWSTAT_ADDR_NAME];		// Downstream Location
}CFG_TRAFFIC_FLOWSTAT_DIR_INFO;

//Road info
typedef struct tagCFG_LANE
{
	int                nLaneId;                             // Road
	int                nDirection;                          // Road direction(where the car go),0-north 1-east north 2-east 3-east south 4-south 5-west south 6-west 7-west north
	CFG_POLYLINE       stuLeftLine[MAX_POLYLINE_NUM];       // Left road line,acord the road left is left road line
	int                nLeftLineNum;                        // Left road line number
	CFG_POLYLINE       stuRightLine[MAX_POLYLINE_NUM];      // Right road line,acord the road right is right road line
	int                nRightLineNum;                       // Right road line number
	int                nLeftLineType;                       // Left road line attribute,1 means white solid line, 2 means withe dotted line, 3 means yellow line
	int                nRightLineType;                      // Right road line attribute, 1 means white solid line, 2 means withe dotted line, 3 means yellow line
	BOOL               bDriveDirectionEnable;               // Road direction enable
	int                nDriveDirectionNum;                  // Road direction number
	char               szDriveDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];  // Road direction,"Straight","TurnLeft","TurnRight","U-Turn"
	int                nStopLineNum;                        // Road's stop line's point number
	CFG_POLYLINE       stuStopLine[MAX_POLYLINE_NUM];       //Road's stop line
	int                nTrafficLightNumber;                 // Road's traffic light group id
	bool               abDetectLine;                        // Detect capacity
	bool               abPreLine;
	bool               abPostLine;
	BYTE               byReserved[1];

	int                nDetectLine;
	CFG_POLYLINE       stuDetectLine[MAX_POLYLINE_NUM];     // Road detect line
	int                nPreLine;
	CFG_POLYLINE       stuPreLine[MAX_POLYLINE_NUM];        //Road preline
	int                nPostLine;
	CFG_POLYLINE       stuPostLine[MAX_POLYLINE_NUM];       //Road post line
	CFG_TRAFFIC_FLOWSTAT_DIR_INFO stuTrafficFlowDir;	    //  Lane traffic information
}CFG_LANE;

// Traffic light attribute
typedef struct tagCFG_LIGHTATTRIBUTE
{
	BOOL			  bEnable;											// Instruct the current traffic light's effectiveness 
	int				  nTypeNum; 
	char			  szLightType[MAX_LIGHT_TYPE][MAX_NAME_LEN];		// Current light display(include:Red,Yellow,Green,Countdown),for example some traffic light has red, yellow, green three color, and other only can only display countdown
	int				  nDirectionNum;
	char			  szDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];	// The direction of traffic light display,"Straight","TurnLeft","TurnRight","U-Turn"
	int				  nYellowTime;										// Yellow light on time
}CFG_LIGHTATTRIBUTE;

// Traffic light configuration
typedef struct tagCFG_LIGHTGROUPS
{
	int                nLightGroupId;                     //Light group id
	CFG_RECT           stuLightLocation;                  //Light group location
	int                nDirection;                        // Light group direction,1- horizontal,2- vertical
	BOOL               bExternalDetection;                // Instruct whether circumscribe traffic light signal; when be true, it will be trigger rule while the signal changed
	BOOL               bSwingDetection;                   // Whether support self-adaptation light swing detect, when be in a sence that easy to swing, the light location will be lillte changed, it will cost a longer time that let the algorithm do the detect, 	int                nLightNum;                         //The number of light in the group
	int                nLightNum;                         // The number of light in the group
	CFG_LIGHTATTRIBUTE stuLightAtrributes[MAX_LIGHT_NUM]; // Each light's attribute

}CFG_LIGHTGROUPS;

enum EM_STAFF_TYPE
{
	EM_STAFF_TYPE_ERR,
	EM_STAFF_TYPE_HORIZONTAL,							// "Horizontal" Horizontal segment
	EM_STAFF_TYPE_VERTICAL,								// "Vertical"  Vertical segment
	EM_STAFF_TYPE_ANY,									// "Any" Any line 
	EM_STAFF_TYPE_CROSS,								// "Cross" Perpendicular cross segment
};

enum EM_CALIBRATEAREA_TYPE
{
	EM_CALIBRATEAREA_TYPE_ERR,
	EM_CALIBRATEAREA_TYPE_GROUD,                         // "Groud" : Require: N vertical segment(s) + M horizontal segment(s)((N=3,M=1);(N=2,M=2);with further development)
	EM_CALIBRATEAREA_TYPE_HORIZONTAL,                    // "Horizontal"  : Require the projection and stright segment between a point on plane to the point on ground	
	EM_CALIBRATEAREA_TYPE_VERTICAL,                      // "Vertical" : Require the intersecting line of vertical side and the ground
	EM_CALIBRATEAREA_TYPE_ANY,                           // "Any" plane. N vertical segment with length (N=3,with further development)
};

// Sepcial region property type
enum EM_SEPCIALREGION_PROPERTY_TYPE
{
	EM_SEPCIALREGION_PROPERTY_TYPE_HIGHLIGHT = 1,            // Hight light, screen detection area has this feature 
	EM_SEPCIALREGION_PROPERTY_TYPE_REGULARBLINK,             // Regular blink,card area has this feature
	EM_SEPCIALREGION_PROPERTY_TYPE_IREGULARBLINK,            // Iregular blink,keyboard area has this feature
	EM_SEPCIALREGION_PROPERTY_TYPE_NUM,
};


// Face detection type
enum EM_FACEDETECTION_TYPE
{
	EM_FACEDETECTION_TYPE_ERR,
	EM_FACEDETECTION_TYPE_SMALLFACE,						//Little face, about 17% of the total face in the video
	EM_FACEDETECTION_TYPE_LARGEFACE,						//Big face, about 33% of the total face in the video
	EM_FACEDETECTION_TYPE_BOTH,								//Detection type
};



typedef struct tagCFG_STAFF
{
	CFG_POLYLINE       stuStartLocation;      // Start location
	CFG_POLYLINE       stuEndLocation;        //End location
	float                nLenth;                // Lenth, in pixel unit
	EM_STAFF_TYPE	   emType;                // Staff type
}CFG_STAFF;

// Size
typedef struct tagCFG_SIZE
{
	union
	{
		float				nWidth;			// Width
		float				nArea;			// Area
	};
	float				nHeight;		//Height
	
} CFG_SIZE;

// Privacy mask information
typedef struct tagCFG_COVER_INFO
{
	// Competence
	bool				abBlockType;
	bool				abEncodeBlend;
	bool				abPreviewBlend;

	// Information
	CFG_RECT			stuRect;					// The position (coordinates) of the mask zone
	CFG_RGBA			stuColor;					// The mask color
	int					nBlockType;					// The mask mode ;0-black block,1-Mosaic
	int					nEncodeBlend;				// Encode-level privacy mask;1-enable,0-disable
	int					nPreviewBlend;				// Preview mask;1-enable,0-disable
} CFG_COVER_INFO;

// Multiple-zone mask configuration
typedef struct tagCFG_VIDEO_COVER
{
	int                 nTotalBlocks;						// The supported privacy mask zone amount
	int					nCurBlocks;							// The zone amount already set
	CFG_COVER_INFO		stuCoverBlock[MAX_VIDEO_COVER_NUM];	// The mask zone	
} CFG_VIDEO_COVER;

// OSD information
typedef struct tagCFG_OSD_INFO
{
	//Capcity 
	bool				abShowEnable;

	// Information
	CFG_RGBA			stuFrontColor;				// Front color
	CFG_RGBA			stuBackColor;				// Background color
	CFG_RECT			stuRect;					// Rectangle zone
	BOOL				bShowEnable;				// Display enbale
} CFG_OSD_INFO;

// Video color property
typedef struct tagCFG_COLOR_INFO
{
	int					nBrightness;				// Brgihtness(0-100)
	int					nContrast;					// Contrast(0-100)
	int					nSaturation;				// Saturation (0-100)
	int					nHue;						//Hue (0-100)
	int					nGain;						// Gain(0-100)
	BOOL				bGainEn;					// Gain enable
} CFG_COLOR_INFO;

// Video channel property information
typedef struct tagCFG_ENCODE_INFO
{
	int                 nChannelID;							// Channel number(Begins with 0)
	char				szChnName[MAX_CHANNELNAME_LEN];		// Channel name
	CFG_VIDEOENC_OPT	stuMainStream[MAX_VIDEOSTREAM_NUM];	// Main stream,0-General record,1-Motion detect,2-alarm record
	CFG_VIDEOENC_OPT	stuExtraStream[MAX_VIDEOSTREAM_NUM];// Extra stream,0-Extra stream 1,1-Extra stream 2,2-Extra stream 3
	CFG_VIDEOENC_OPT	stuSnapFormat[MAX_VIDEOSTREAM_NUM];	// Snapshot,0-General snapshot,1-Motion detect snapshot,2-alarm snapshot
	DWORD				dwCoverAbilityMask;					// The subnet mask of the privacy mask competence. Use the bit to represent. There are local preview, record and network monitor.
	DWORD				dwCoverEnableMask;					// The subnet mask of the privacy mask enable.Use the bit to represent. There are local preview, record and network monitor.
	CFG_VIDEO_COVER		stuVideoCover;						// Privacy mask 
	CFG_OSD_INFO		stuChnTitle;						// Channel title
	CFG_OSD_INFO		stuTimeTitle;						// Time title
	CFG_COLOR_INFO		stuVideoColor;						// Video color
	CFG_AUDIO_FORMAT    emAudioFormat;                       // Audio format: 0:G711A,1:PCM,2:G711U,3:AMR,4:AAC
	int					nProtocolVer;						// Protocol Version No., read only
} CFG_ENCODE_INFO;

// Video Input Front-end Capability Set
typedef struct tagCFG_VIDEO_ENCODECAP
{
    int                 nMaxCIFFrame;                       // CIF P Frames Max Unit Kbits, Default 40
    int	                nMinCIFFrame;                       // CIF P Frames Min  Unit Kbits, Default 7
}CFG_VIDEO_ENCODECAP;

//  Encoding Capability Set
typedef enum tagCFG_EM_PREVIEW_MODE
{
    CFG_EM_PREVIEW_MODE_UNKNOWN = 0,                        // 
    CFG_EM_PREVIEW_MODE_SNAPSHOT,                           // a snapshot
    CFG_EM_PREVIEW_MODE_SPLITENCODE,                        // division encoding
    CFG_EM_PREVIEW_MODE_SPLITSNAP,                          // Split Snapshot mode
}CFG_EM_PREVIEW_MODE;
#define MAX_PREVIEW_MODE_SPLIT_TYPE_NUM     8                           // The largest multi-screen preview window dividing the number of species
typedef struct tagCFG_ENCODECAP
{
	int                    nChannelNum;                                 // The Actual Number of Channels
	CFG_VIDEO_ENCODECAP    stuVideoEncodeCap[MAX_VIDEO_CHANNEL_NUM];	// Each Channel Encoding Capability Information Array
    CFG_EM_PREVIEW_MODE     emPreviewMode;                              // Multi-screen preview mode
    int                     nSplitModeNum;                              // Effective multi-screen preview window division number of species
    int                     anSplitMode[MAX_PREVIEW_MODE_SPLIT_TYPE_NUM];// Multi-screen preview window division number information, which can be 1, 4, 6, 8, 9, 16, 25, 36 ...
}CFG_ENCODECAP;

// Watermark configuration
typedef struct tagCFG_WATERMARK_INFO 
{
	int                 nChannelID;					// Channel number(Begins with 0)
	BOOL				bEnable;					// Enable
	int					nStreamType;				// Bit stream type (1~n),0-all stremas
	int					nDataType;					// Data type,1-character,2-image
	char				pData[MAX_WATERMARK_LEN];	// String watermark data
} CFG_WATERMARK_INFO;

// DSP configuration
typedef struct tagCFG_DSPENCODECAP_INFO{
	DWORD				dwVideoStandardMask;	// Video format mask. Bit stands for the video format device supported.
	DWORD				dwImageSizeMask;		// Resolution mask bit. Bit stands for the resolution setup devices supported.
	DWORD				dwEncodeModeMask;		// Encode mode mask bit. Bit stands for the encode mode devices supported.
	DWORD				dwStreamCap;			// The multiple-media function the devices supported
                                             	// The first bit:main stream
	                                         	// The second bit:extra stream 1
	                                         	// The third bit:extra stream 2
	                                         	// The fifth bit: snapshot in .jpg format
	DWORD				dwImageSizeMask_Assi[32];// When the main stream is the corresponding resolution, the supported extra stream resolution mask.
	DWORD				dwMaxEncodePower;		// The highest encode capacity DSP supported 
	WORD				wMaxSupportChannel;		// The max video channel amount each DSP supported
	WORD				wChannelMaxSetSync;		// Max encode bit setup in each DSP channel  are synchronized or not ;0:do not synchronized,1:synchronized
	BYTE				bMaxFrameOfImageSize[256];// The max sampling frame rate in different resolution. Bit corresponding to the dwVideoStandardMask.
	BYTE				bEncodeCap;				// Symbol. The configuration shall meet the following requirements, otherwise the configuration is invalid.
	                                         	// 0: main stream encode capacity+extra stream encode capacity<= device encode capacity
	                                         	// 1: main stream encode capacity +extra stream encode capacity<= device encode capacity 
	                                         	// Extra stream encode capacity <=main stream encode capacity
	                                         	// Extra stream resolution<=main stream resolution
	                                         	// Main stream resolution and extra stream resolution <=front-end video collection frame rate
	                                         	// 2:N5 Device
	                                         	// Extra stream encode capacity <=main stream encode capacity
												// Query  the supported resolution and the corresponding maximum frame rate
	BYTE				byResolutionNum;			// bResolution's lenth
	BYTE				byResolutionNum_1;		// bResolution_1's lenth
	BYTE				byReserved;
	BYTE				byResolution[256];		//Main stream, referrence as the resolution, if support this resolution,then the bResolution[n]'s value is the max supported resolution. else if it will be 0.							
	BYTE				byResolution_1[256];	//Extra stream1, the same as main stream.
	char				reserved[28];
	BYTE				byImageSize[256];		// Support resolution array, see enum CAPTURE_SIZE
	BYTE				byImageSize_Assi[256][256]; //When the main stream for the resolution, the support of the auxiliary code flow reloution, the array subscript said resolution supported by the main stream values
}CFG_DSPENCODECAP_INFO;
typedef enum tagEM_PTZ_ACTION {
    EM_PTZ_ACTION_UNKNOWN,                                      // unknown
    EM_PTZ_ACTION_SCAN,                                         // scan
    EM_PTZ_ACTION_PRESET,                                       // preset
    EM_PTZ_ACTION_PATTERN,                                      // pattern
    EM_PTZ_ACTION_TOUR,                                         // tour
} EM_PTZ_ACTION;
//-------------------------------Record Configuration---------------------------------

// Period information
typedef struct tagCFG_TIME_SECTION 
{
	DWORD				dwRecordMask;						// Record subnet mask. The bit represents motion detect reocrd, alarm record, schedule record. Bit3~Bit15 is reserved. Bit 16 motion detect snapshot, Bit 17 alarm snapshot, Bit18 schedule snapshot
	int					nBeginHour;
	int					nBeginMin;
	int					nBeginSec;
	int					nEndHour;
	int					nEndMin;
	int					nEndSec;	
} CFG_TIME_SECTION;

// Schedule Information
typedef struct tagCFG_TIME_SCHEDULE
{
    BOOL                bEnableHoliday;                     // whether holiday config is enabled, default value is FALSE, DO NOT enable it unless you get TRUE after get config
	CFG_TIME_SECTION	stuTimeSection[MAX_TIME_SCHEDULE_NUM][MAX_REC_TSECT]; // The First Dimension Before the 7 Elements Corresponding 7 Days a week?ê?Eighth Elements Corresponding Holiday?ê?Up to Six Time Periods Per Day
} CFG_TIME_SCHEDULE;

// Schedule record configuration information
typedef struct tagCFG_RECORD_INFO
{
	int                 nChannelID;					// The channel number(Begins with 0)
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT]; // Time table
	int					nPreRecTime;				// Pre-record time.The value ranges from 0 to 300. This function is disable when the value is 0.
	BOOL				bRedundancyEn;				// Record redundancy enbale button
	int					nStreamType;				// 0-main stream,1-extra stream 1,2-extra stream 2,3-extra stream 3
	int					nProtocolVer;				//  Protocol Version No., read only

	// Capacity
    BOOL                abHolidaySchedule;          // There are Holiday Configuration Information When it  is True?ê?bHolidayEn??éstuHolTimeSection is effective;
    BOOL                bHolidayEn;                 // Holiday Video Enable TRUE:Enable,FALSE:Unable
    CFG_TIME_SECTION    stuHolTimeSection[MAX_REC_TSECT];  // Holiday Video Schedule
} CFG_RECORD_INFO;

//-------------------------------Alarm Configuration---------------------------------

// PTZ activation type
typedef enum tagCFG_LINK_TYPE
{
	LINK_TYPE_NONE,									// No activation
	LINK_TYPE_PRESET,								// Activate the preset
	LINK_TYPE_TOUR,									// Activate the tour
	LINK_TYPE_PATTERN,								// Activate the pattern
} CFG_LINK_TYPE;

// PTZ activation information
typedef struct tagCFG_PTZ_LINK
{
	CFG_LINK_TYPE		emType;						// Activation type
	int					nValue;						// The activation value is the corresponding preset number, tour number and etc.
} CFG_PTZ_LINK;

// PTZ activation extend information
typedef struct tagCFG_PTZ_LINK_EX
{
	CFG_LINK_TYPE	emType;				// Activation type 
	int			    nParam1;			// Activation parameter1
	int			    nParam2;            // Activation parameter2
	int			    nParam3;            // Activation parameter3
	int			    nChannelID;         // Activation channel
} CFG_PTZ_LINK_EX;

// Event title
typedef struct tagCFG_EVENT_TITLE
{
	char				szText[MAX_CHANNELNAME_LEN];
	CFG_POLYGON			stuPoint;			// Title on the upper left corner coordinates, using the 0-8191 to sitting
	CFG_SIZE     		stuSize;			// The height and width of title, using 0-8191 relative coordinnate system, the item or two adaptive width 0 said according to the font
    CFG_RGBA			stuFrontColor;		// Front color
    CFG_RGBA			stuBackColor;		// Back color
} CFG_EVENT_TITLE;

// Mail attachment type
typedef enum tagCFG_ATTACHMENT_TYPE
{
		ATTACHMENT_TYPE_PIC,							// Picture attachment
		ATTACHMENT_TYPE_VIDEO,							// Video attachment
		ATTACHMENT_TYPE_NUM,							// Attachment
} CFG_ATTACHMENT_TYPE;
// Mail detail 
typedef struct tagCFG_MAIL_DETAIL
{
	   CFG_ATTACHMENT_TYPE emAttachType;                 // Attachment type 
       int                 nMaxSize;                     // The max size for file, unit kB
       int                 nMaxTimeLength;               // Max time length, unit sec, effective for video
}CFG_MAIL_DETAIL;

// Split mode 
typedef enum tagCFG_SPLITMODE
{
	    SPLITMODE_1 = 1,						// 1 picture
	    SPLITMODE_2 = 2,						// 2 picture
	    SPLITMODE_4 = 4,						// 4 picture
		SPLITMODE_6 = 6,						// 6 picture
		SPLITMODE_8 = 8,						// 8 picture
		SPLITMODE_9 = 9,						// 9 picture
		SPLITMODE_12 = 12,				    	// 12 picture
		SPLITMODE_16 = 16,				    	// 16 picture
		SPLITMODE_20 = 20,				    	// 20 picture
		SPLITMODE_25 = 25,					    // 25 picture
		SPLITMODE_36 = 36,					    // 36 picture
		SPLITMODE_64 = 64,					    // 64 picture
		SPLITMODE_144 = 144,					// 144 picture
		SPLITMODE_PIP = 1000,                   // Picinpic segmentation model base value
		SPLITMODE_PIP1 = SPLITMODE_PIP + 1,		// Picinpic type, a full screen image + 1 small screen window
		SPLITMODE_PIP3 = SPLITMODE_PIP + 3,		// Picinpic type, a full screen image + 3 small screen window
		SPLITMODE_FREE = SPLITMODE_PIP * 2,		// Free window mode, can freely create close the window, free settings window corresponding to the Z axis
		SPLITMODE_COMPOSITE_1 = SPLITMODE_PIP * 3 + 1,	// Panel member 1 segmentation
		SPLITMODE_COMPOSITE_4 = SPLITMODE_PIP * 3 + 4,	// Panel member 4 segmentation
		SPLITMODE_EOF,                          // The end 
} CFG_SPLITMODE;

// Tour link configuration
typedef struct tagCFG_TOURLINK
{
	BOOL				bEnable;			             // Tour enable
	CFG_SPLITMODE	    emSplitMode;		             // Touring, split mode
	int			        nChannels[MAX_VIDEO_CHANNEL_NUM];  // Touring,video channel
	int			        nChannelCount;		             // Touring,channel count
} CFG_TOURLINK;

// Entrance Guard Operation Type
enum EM_CFG_ACCESSCONTROLTYPE
{
	EM_CFG_ACCESSCONTROLTYPE_NULL = 0,					//  Do not operate
	EM_CFG_ACCESSCONTROLTYPE_AUTO,						//  Automatic
	EM_CFG_ACCESSCONTROLTYPE_OPEN,						// Open the Door
	EM_CFG_ACCESSCONTROLTYPE_CLOSE,						// Close the Door 
	EM_CFG_ACCESSCONTROLTYPE_OPENALWAYS,				// Open Always
	EM_CFG_ACCESSCONTROLTYPE_CLOSEALWAYS,				// Close Always
};

// The Combination of Entrance Guard Combined Operation

#define MAX_ACCESSCONTROL_NUM	8						//  Maximum Number of Combination of Entrance Guard Operation


//  Voice Calls Originating
typedef enum
{
	EM_CALLER_DEVICE = 0,								// Device Originating
}EM_CALLER_TYPE;

//  Call Protocol
typedef enum
{
	EM_CALLER_PROTOCOL_CELLULAR = 0,					// Phone Mode
}EM_CALLER_PROTOCOL_TYPE;


//  Voice Call Linkage Information
typedef struct tagCFG_TALKBACK_INFO
{
	BOOL				bCallEnable;					// Voice Call Enable
	EM_CALLER_TYPE		emCallerType;					// Voice Calls Originating
	EM_CALLER_PROTOCOL_TYPE	emCallerProtocol;			// Voice Call Protocol
}CFG_TALKBACK_INFO;

//  Telephone Alarm Center Linkage Information
typedef struct tagCFG_PSTN_ALARM_SERVER
{
	BOOL				bNeedReport;						//  Whether to Report to the Call Center
	int					nServerCount;						//  The Number of Telephone Alarm Server					
	BYTE 				byDestination[MAX_PSTN_SERVER_NUM];//  Report to the Alarm Center Subscript,See the Configuration CFG_PSTN_ALARM_CENTER_INFO
}CFG_PSTN_ALARM_SERVER;

// Alarm activation information
typedef struct tagCFG_ALARM_MSG_HANDLE
{
	//Competence 
	bool				abRecordMask;
	bool				abRecordEnable;
	bool				abRecordLatch;
	bool				abAlarmOutMask;
	bool				abAlarmOutEn;
	bool				abAlarmOutLatch;	
	bool				abExAlarmOutMask;
	bool				abExAlarmOutEn;
	bool				abPtzLinkEn;
	bool				abTourMask;
	bool				abTourEnable;
	bool				abSnapshot;
	bool				abSnapshotEn;
	bool				abSnapshotPeriod;
	bool				abSnapshotTimes;
	bool				abTipEnable;
	bool				abMailEnable;
	bool				abMessageEnable;
	bool				abBeepEnable;
	bool				abVoiceEnable;
	bool				abMatrixMask;
	bool				abMatrixEnable;
	bool				abEventLatch;
	bool				abLogEnable;
	bool				abDelay;
	bool				abVideoMessageEn;
	bool				abMMSEnable;
	bool				abMessageToNetEn;
	bool				abTourSplit;
	bool				abSnapshotTitleEn;

    bool                abChannelCount;
	bool                abAlarmOutCount;
	bool                abPtzLinkEx;
	bool                abSnapshotTitle;
	bool                abMailDetail;
	bool                abVideoTitleEn;
	bool                abVideoTitle;
	bool                abTour;
	bool                abDBKeys;
	bool                abJpegSummary;
	bool                abFlashEn;
	bool                abFlashLatch;
	//Information
	int					nChannelCount;								// The video channel of the device
	int					nAlarmOutCount;								// The alarm output amount of the device
	DWORD				dwRecordMask[MAX_CHANNEL_COUNT];				// Subnet mask of the recording channel(use the bit to represent)
	BOOL				bRecordEnable;								// Record enable
	int					nRecordLatch;								// Record delay time(s)
	DWORD				dwAlarmOutMask[MAX_CHANNEL_COUNT];			// Subnet mask of alarm output channel 
	BOOL				bAlarmOutEn;								// Alarm output enable
	int					nAlarmOutLatch;								//Alarm output delay time (s)
	DWORD				dwExAlarmOutMask[MAX_CHANNEL_COUNT];			// Subnet mask of extension alarm output channel 
	BOOL				bExAlarmOutEn;								// Extension alarm output enable
	CFG_PTZ_LINK		stuPtzLink[MAX_VIDEO_CHANNEL_NUM];			// PTZ activation item
	BOOL				bPtzLinkEn;									// PTZ activation enable
	DWORD				dwTourMask[MAX_CHANNEL_COUNT];				// Subnet mask of tour channel 
	BOOL				bTourEnable;								// Tour enable
	DWORD				dwSnapshot[MAX_CHANNEL_COUNT];				// Snapshot channel subnet mask
	BOOL				bSnapshotEn;								// Snapshot enable
	int					nSnapshotPeriod;							// Snapshot period(s)
	int					nSnapshotTimes;								// Snapshot times
	BOOL				bTipEnable;									// Local prompt dialogue box
	BOOL				bMailEnable;								// Send out emali. The image is sent out as the attachment. 
	BOOL				bMessageEnable;								// Upload to the alarm server 
	BOOL				bBeepEnable;								// Buzzer
	BOOL				bVoiceEnable;								// Audio prompt
	DWORD				dwMatrixMask[MAX_CHANNEL_COUNT];				// Subnet mask of the activated video channel
	BOOL				bMatrixEnable;								// Activate the video matrix
	int					nEventLatch;								// Activation delay time (s),0-15
	BOOL				bLogEnable;									// Record log or not
	int					nDelay;										// Delay first and then becomes valid when set. Unit is second.
	BOOL				bVideoMessageEn;							// Overlay the prompt character to the video. The overlay character includes the event type, channel number. The unit is second.
	BOOL				bMMSEnable;									// Enable MMS
	BOOL				bMessageToNetEn;							// Send the message to the network enable
	int					nTourSplit;									// Tour split mod 0: 1tour; 1: 8tour
	BOOL				bSnapshotTitleEn;							// Enble osd
	int                 nPtzLinkExNum;                                // PTZ link configuration number
	CFG_PTZ_LINK_EX     stuPtzLinkEx[MAX_VIDEO_CHANNEL_NUM];          // PTZ extend information
	int                 nSnapTitleNum;                                // Number of picture title
	CFG_EVENT_TITLE     stuSnapshotTitle[MAX_VIDEO_CHANNEL_NUM];      // Picture title content
	CFG_MAIL_DETAIL     stuMailDetail;                                // Mail detial
	BOOL                bVideoTitleEn;                                // Whether overlay video title, mainly refers to the main stream
    int                 nVideoTitleNum;                               // Video title num
	CFG_EVENT_TITLE     stuVideoTitle[MAX_VIDEO_CHANNEL_NUM];         // Video title
	int                 nTourNum;                                     // Tour num
	CFG_TOURLINK        stuTour[MAX_VIDEO_CHANNEL_NUM];               // Tour configuration
	int                 nDBKeysNum;			                          // Specify the db keyword on the number of effective
	char                szDBKeys[MAX_DBKEY_NUM][MAX_CHANNELNAME_LEN]; // The specify event detail information need write the BD keyword
	BYTE                byJpegSummary[MAX_SUMMARY_LEN];               // The summary information of the jpeg image
	BOOL                bFlashEnable;                                 // Whether enable flash
	int                 nFlashLatch;                                  // Flash delay time (s),the time range:[10,300]
	
	bool				abAudioFileName;
	bool				abAlarmBellEn;
	bool				abAccessControlEn;
	bool				abAccessControl;

    char                szAudioFileName[MAX_PATH];                  // The Absolute Path to the Linkage Audio Files
    BOOL                bAlarmBellEn;                               // Warning Signal Enable
    BOOL                bAccessControlEn;                           // Entrance Guard Enable

    DWORD               dwAccessControl;                            // Class Number of Entrance Guard
    EM_CFG_ACCESSCONTROLTYPE    emAccessControlType[MAX_ACCESSCONTROL_NUM];	// Entrance Guard Linkage Operation Information
	
    bool                abTalkBack;	
    CFG_TALKBACK_INFO   stuTalkback;                                // Voice Call Linkage Information

    bool                abPSTNAlarmServer;
    CFG_PSTN_ALARM_SERVER   stuPSTNAlarmServer;                     //  Telephone Alarm Center Linkage Information
    CFG_TIME_SCHEDULE       stuTimeSection;                         // Event Response Timetable
	bool				abAlarmBellLatch;
	int					nAlarmBellLatch;							// Police no. output delay time(10-300 s)

} CFG_ALARM_MSG_HANDLE;



//Alarm control method
typedef enum tagEM_CTRL_ENABLE
{
	EM_CTRL_NORMAL=0,   //No enable
	EM_CTRL_ALWAYS_EN,  //Always enable
	EM_CTRL_ONCE_DIS,   //Bypass
	EM_CTRL_ALWAYS_DIS, //Disappear
	EM_CTRL_NUM         //The total of enum type
}EM_CTRL_ENABLE;

// DefenceArea Type
typedef enum tagEM_CFG_DEFENCEAREATYPE
{
	EM_CFG_DefenceAreaType_Unknown = 0,	// unknown type
	EM_CFG_DefenceAreaType_InTime,		// instant zone
	EM_CFG_DefenceAreaType_Delay,		// delay zone
	EM_CFG_DefenceAreaType_FullDay,		// 24-hour zone
    EM_CFG_DefenceAreaType_Follow,          // follow zone
    EM_CFG_DefenceAreaType_Medical,         // medical zone
    EM_CFG_DefenceAreaType_Panic,           // panic zone
    EM_CFG_DefenceAreaType_Fire,			// Fire zone
    EM_CFG_DefenceAreaType_FullDaySound,	// 24-hour sound zone
    EM_CFG_DefenceAreaType_FullDaySlient,	// 24-hour mute zone
    EM_CFG_DefenceAreaType_Entrance1,		// enter zone 1
    EM_CFG_DefenceAreaType_Entrance2,		// enter zone 2
    EM_CFG_DefenceAreaType_InSide,			// internal zone
    EM_CFG_DefenceAreaType_OutSide,			// external zone
}EM_CFG_DEFENCEAREATYPE;

// External alarm setup
typedef struct tagCFG_ALARMIN_INFO
{
	int					nChannelID;									// Alarm channel number (Begins with 0)
	BOOL				bEnable;									// Enable
	char				szChnName[MAX_CHANNELNAME_LEN];				// Alarm channel name
	int					nAlarmType;									// Alarm device type,0:NO,1:NC
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm activation
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
	BOOL				abDevID;									// 
	char				szDevID[MAX_NAME_LEN];						// Device ID
	int                 nPole;                                      // Sensor trigger mode, 0:high effective,1low effective;
	                                                                // Sensor grounding or supply,with nAlarmType 
	EM_SENSE_METHOD     emSense;                                    // Inductive sensor 
	EM_CTRL_ENABLE      emCtrl;                                     // Alarm control
	int                 nDisDelay;                                  // Delay time machine, unit(s),0~300,
	                                                                //emCtrl value is EM_CTRL_NORMAL or EM_CTRL_ALWAYS_EN  valid

	EM_CFG_DEFENCEAREATYPE emDefenceAreaType;						// DefenceArea Type , Specific Types Supported by Querying the Ability to Obtain
	int					nEnableDelay;								//  Delay Protection Time, DefenceArea Type is"Delay"(Delay DefenceArea)is Effective, Unit: Second,  Maximum Time by Querying the Ability to Obtain
    int                 nSlot;                                      // Root address, -1 means invalid, 0 means local channel, 1 means connect to 1st serial extention channel, 2??é3...and so on
    int                 nLevel1;                                    // 1st level cascading address, means connection to no.nSlot serial no.nLevel 1 detector or meter, -1 means invalid, from 0
    bool                abLevel2;                                   // Means if nLevel2 text exists
    int                 nLevel2;                                    // 2rd level cascading address, means connected to no. nLevel1 meter??￥s detector no., -1 means invalid, from 0
} CFG_ALARMIN_INFO;

// Network input alarm setup
typedef struct tagCFG_NETALARMIN_INFO 
{
	int					nChannelID;									// Alarm channel number (Begins with 0)
	BOOL				bEnable;									// Enable
	char				szChnName[MAX_CHANNELNAME_LEN];				// Alarm channel name
	int					nAlarmType;									// Alarm device type,0:NC,1:NO
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm activation
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
} CFG_NETALARMIN_INFO;


// Dynamic configuartion support video window
typedef struct tagCFG_MOTION_WINDOW
{
	int                  nThreshold;           // The area threshold,[0, 100]
	int                  nSensitive;           //Sensitive,[0, 100]
	CFG_RECT             stuWindow;            // Motion window area, coordinate range [0, 8192)
}CFG_MOTION_WINDOW;

typedef struct tagCFG_DETECT_REGION
{
    int				     nRegionID;									    // Zone ID
    char                 szRegionName[CFG_COMMON_STRING_64];            // Motion window name
    int                  nThreshold;                                    //Area threshold?ê?value[0, 100]
	int					 nSenseLevel;								    // Sensitivity 1??6
	int					 nMotionRow;									// Motion zone row
	int					 nMotionCol;									// Motion detection zone column
	BYTE				 byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	    // Detection zone?ê?max 32*32 blocks 
}CFG_DETECT_REGION;

// Motion detect alarm setup
typedef struct tagCFG_MOTION_INFO 
{
	int					nChannelID;									// Alarm channel number (Begins with 0)
	BOOL				bEnable;									// Enable
	int					nSenseLevel;								// Sensitivity 1~6
	int					nMotionRow;									// The rows of the motion detect zone 
	int					nMotionCol;									// The columns of the motion detect zone
	BYTE				byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	// Motion detect,Max 32*32 zones
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm activation
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
	int			         nVersion;                                  // 0, 1, be determined by the capability set set, read only,when equal 1,the following fields
	BOOL                 bSenseLevelEn;                             // Read only,decide nSenseLevel efficiency or not
	BOOL                 bVRatioEn;                                 // Read only,the area impropriate enable, decide nVolumeRatio efficiency or not
	int                  nVolumeRatio;                              // The area impropriate,1-100
	BOOL                 bSRatioEn;                                 // Read only, sensitivity enable,decide nVolumeRatio efficiency or not
	int                  nSubRatio;                                 //Motion inspection of residual error threshold, 1-100
	BOOL                 abWindow;                                  // Read only,0: nMotionRow, nMotionCol,byRegion availability, 1: the following field in the video window
	int                  nWindowCount;                              // Number of video window
	CFG_MOTION_WINDOW    stuWindows[MAX_MOTION_WINDOW];             // Video window
	BOOL                 abDetectRegion;                            // Read only?ê?1?êonRegionCount?ê?stuRegion valid
                                                                    //       0?êonMotionRow?ê?nMotionCol?ê?byRegion valid
	int                  nRegionCount;                              // 3rd generation motion detection zone quantity
	CFG_DETECT_REGION    stuRegion[MAX_MOTION_WINDOW];              // 3rd generation motion detection zone
} CFG_MOTION_INFO;

// Video loss alarm setup
typedef struct tagCFG_VIDEOLOST_INFO 
{
	int					nChannelID;									// Alarm channel number (Begins with 0)
	BOOL				bEnable;									// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm activation
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
} CFG_VIDEOLOST_INFO;

// Camera masking alarm setup
typedef struct tagCFG_SHELTER_INFO 
{
	int					nChannelID;									// Alarm channel number (Begins with 0)
	BOOL				bEnable;									// Enable
	int					nSenseLevel;								// Sensitivity
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm activation
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
} CFG_SHELTER_INFO;

// No storage device alarm setup
typedef struct tagCFG_STORAGENOEXIST_INFO 
{
	BOOL				bEnable;						// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// Alarm activation
} CFG_STORAGENOEXIST_INFO;

// Storage device access error alarm setup
typedef struct tagCFG_STORAGEFAILURE_INFO 
{
	BOOL				bEnable;						// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// Alarm activation
} CFG_STORAGEFAILURE_INFO;

// Insufficient storage space alarm setup
typedef struct tagCFG_STORAGELOWSAPCE_INFO 
{
	BOOL				bEnable;						// Enable
	int					nLowerLimit;					// The HDD free space threshold. Percentage (0~99)
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// Alarm activation
} CFG_STORAGELOWSAPCE_INFO;

//Network disconnection alarm setup
typedef struct tagCFG_NETABORT_INFO 
{
	BOOL				bEnable;						// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// Alarm activation
} CFG_NETABORT_INFO;

// IP conflict alarm setup
typedef struct tagCFG_IPCONFLICT_INFO 
{
	BOOL				bEnable;						// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// Alarm activation
} CFG_IPCONFLICT_INFO;

// CLIENT_QueryNewSystemInfo interface order, CFG_CAP_ALARM (get alarm capacity)

// Sensor Alarm Way
typedef struct tagCFG_ALARM_SENSE_METHOD
{
	int                 nSupportSenseMethodNum;								// The Number of Supported Sensors Way
	EM_SENSE_METHOD     emSupportSenseMethod[MAX_ALARM_SENSE_METHOD_NUM];   // Supported Sensor Way
}CFG_ALARM_SENSE_METHOD;

typedef struct tagCFG_CAP_ALARM_INFO
{
	BOOL                bAlarmPir;                      // Device support PIR alarm or not(thermal sensors),a kind of external alarm
	BOOL                bFlashLight;                    // Device support flash light of not
    int                 nDefenceAreaTypeNum;            // DefenceArea Type Number ,0 Indicates No Such Alarm Input does not Use as a DefenceArea
    EM_CFG_DEFENCEAREATYPE	emDefenceAreaType[MAX_ALARM_DEFENCE_TYPE_NUM];// Supported DefenceArea Type 
    int	                nMaxDelay;                      // Delay DefenceArea Maximum Time,Unit:Second, Only Support Delay DefenceArea is Effective
    int	                nAlarmChannelNum;               // Alarm Channel,In Order to Maintain Compatibility, 0 Indicates that Each Channel  Support All Types of Sensors
	CFG_ALARM_SENSE_METHOD stuAlarmChannel[MAX_ALARM_CHANNEL_NUM];	// Alarm Channel Set
	int	                nAlarmBellCount;                // Number of Alarm
	int	                nMaxBackupAlarmServer;          // The Maximum number of alarms backup center,The default is 0 when no such field,0 indicates no support for alternate Alarm Center
	int	                nMaxPSTNAlarmServer;            // The Maximum number of Phone alarms  center, he default is 0 when no such field,0 indicates no support for Phone Alarm Center
}CFG_CAP_ALARM_INFO;

// Flash light configuration
typedef struct tagCFG_FLASH_LIGHT
{
	BOOL                bEnable;                        // Enable
	int                 nBrightness;                    // Brightness 0~100
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Flash light time section
}CFG_FLASH_LIGHT;

typedef struct tagCFG_CUSTOMCASE
{
	char                szCaseTitle[MAX_OSD_TITLE_LEN];    // Case title
	char                szCaseContent[MAX_OSD_SUMMARY_LEN];  // Case content
	BOOL                bCaseNoOsdEn;                        // Case's number enable
}CFG_CUSTOMCASE;

// Time
typedef struct tagCFG_NET_TIME
{
    int                 nStructSize;
    DWORD				dwYear;					// Year
    DWORD				dwMonth;				// Month
    DWORD				dwDay;					// Day
    DWORD				dwHour;					// Hour
    DWORD				dwMinute;				// Minute
    DWORD				dwSecond;				// Second
} CFG_NET_TIME;

//Judicature configuration
typedef struct tagCFG_JUDICATURE_INFO
{
	char                szDiskPassword[MAX_PASSWORD_LEN];	// Disk password,input the correct password is needed to play
	char                szCaseNo[MAX_OSD_SUMMARY_LEN];     // Case num
	BOOL                bCaseNoOsdEn;                      // Case num enable
	char                szCaseTitle[MAX_OSD_SUMMARY_LEN];  // Case title
	BOOL                bCaseTitleOsdEn;                   // Case title enable
	char                szOfficer[MAX_OSD_SUMMARY_LEN];    // Officer
	BOOL                bOfficerOsdEn;                     // Officer enable
	char                szLocation[MAX_OSD_SUMMARY_LEN];   // Location
	BOOL                bLocationOsdEn;                    // Location enable
	char                szRelatedMan[MAX_OSD_SUMMARY_LEN]; //Related man
	BOOL                bRelatedManOsdEn;                  // Related man enable
	char                szDiskNo[MAX_OSD_SUMMARY_LEN];     // Disk num
	BOOL                bDiskNoOsdEn;                      // Disk num enable

	BOOL                bCustomCase;                       // TRUE:custom judicial case info ,FALSE: such as szCaseNo effective
	int                 nCustomCase;                       // Fact CFG_CUSTOMCASE number
	CFG_CUSTOMCASE      stuCustomCases[MAX_CUSTOMCASE_NUM];// Custom judicial case info

	BOOL                bDataCheckOsdEn;                   // Disk facet date check configuration enable
	BOOL                bAttachFileEn;                     // Attach file enable
    char                szPassword[MAX_PASSWORD_LEN];      // Password, when burning CD, config password
    int                 nPasswordLen;                      // Password length
    CFG_NET_TIME        stuStartTime;                      // Opening info overlay start time
    int                 nPeriod;                           // Opening info overlay time length, unit:minute
}CFG_JUDICATURE_INFO;

// Burn full configuration
typedef struct tagCFG_BURNFULL_ONE
{
	char                szBurnDisk[MAX_NAME_LEN];          // Burn disk
	BOOL                bEnable;                           // Enable
	unsigned int        nLowerLimit;                       // CD remaining capacity limit,unit:M
	BOOL                bBurnStop;                         // Burn stop enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm enable
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event respond time section
	 BOOL                bChangeDisk;                       // enable for change disk
}CFG_BURNFULL_ONE;

typedef struct tagCFG_BURNFULL_INFO
{
	unsigned int        nBurnDev;                          // The number of the actual burning device
	CFG_BURNFULL_ONE    stuBurns[MAX_BURNING_DEV_NUM];     // Each element corresponds to a recording device
}CFG_BURNFULL_INFO;

//-------------------------------Snapshot Configuration Competence ---------------------------------
// Snapshot configuration competence 
typedef struct tagCFG_SNAPCAPINFO_INFO  
{
	int					nChannelID;						// Snapshot channel number(Begin with 0)
	DWORD				dwIMageSizeNum;					// The  supported resolution information
	CFG_CAPTURE_SIZE	emIMageSizeList[MAX_IMAGESIZE_NUM];
	DWORD				dwFramesPerSecNum;				// The supported frame rate information
	int					nFramesPerSecList[MAX_FPS_NUM];
	DWORD				dwQualityMun;					// The supported image quality information
	CFG_IMAGE_QUALITY	emQualityList[MAX_QUALITY_NUM];

	DWORD               dwMode;							// Mode,use the bit to represent :The first bit:Schedule. The second bit:Manual.
	DWORD               dwFormat;						// Image format mode,use the bit to represent:The first bit:bmp;The second bit:jpg.
} CFG_SNAPCAPINFO_INFO;


//-------------------------------NAS Configuration---------------------------------
// NAS configuration
typedef struct tagCFG_CHANNEL_TIME_SECTION 
{
	CFG_TIME_SECTION stuTimeSection[WEEK_DAY_NUM][MAX_NAS_TIME_SECTION];//Storage period
} CFG_CHANNEL_TIME_SECTION;

typedef struct tagCFG_NAS_INFO
{
	BOOL						bEnable;									// Enable button
	int							nVersion;									// NAS version 0=Old FTP,1=NAS
	int							nProtocol;									// Protocol type 0=FTP 1=SMB
	char						szAddress[MAX_ADDRESS_LEN];					// IP address or network name
	int							nPort;										// Port number
	char						szUserName[MAX_USERNAME_LEN];				// Account name
	char						szPassword[MAX_PASSWORD_LEN];				// Password 
	char						szDirectory[MAX_DIRECTORY_LEN];				// Share folder name
	int							nFileLen;									// File length
	int							nInterval;									// Adjacent file interval
	CFG_CHANNEL_TIME_SECTION	stuChnTime[MAX_VIDEO_CHANNEL_NUM];			// Storage period
	int                         nChnTimeCount;                              // Storage period number
} CFG_NAS_INFO;

//------------------------------PTZ Configuration--------------------------------------------
// Protocol name
typedef struct tagCFG_PRONAME
{
	char				name[MAX_NAME_LEN];			// Protocol name
} CFG_PRONAME;

// COM basic property
typedef struct tagCFG_COMM_PROP
{
	BYTE				byDataBit;					// Data bit;0:5,1:6,2:7,3:8
	BYTE				byStopBit;					// Stop bit;0:1-bit,1:1.5-bit,2:2-bit
	BYTE				byParity;					// Parity;0:None,1:Odd;2:Even
	BYTE				byBaudRate;					// Baud rate;0:300,1:600,2:1200,3:2400,4:4800,	
													// 5:9600,6:19200,7:38400,8:57600,9:115200
} CFG_COMM_PROP;
// Place the default configuration
typedef struct tagCFG_PRESET_HOMING
{
	int          nPtzPresetId;   //PTZ pre set Id	0~65535, -1 means inefficacy
	int          nFreeSec;       //Free time,unit(s)
}CFG_PRESET_HOMING;
// PTZ configuration
typedef struct tagCFG_PTZ_INFO
{
	//Competence
	bool				abMartixID;
	bool				abCamID;
	bool				abPTZType;

	// Information
	int					nChannelID;								// Channel name(Begins with 0)	
	BOOL                bEnable;                                // Enable
	char                szProName[MAX_NAME_LEN];                // Protocol name list (Read-only)
	int					nDecoderAddress;						// Decoder address;0 - 255
	CFG_COMM_PROP		struComm;
	int					nMartixID;								// PTZ number
	int					nPTZType;								// PTZ type 0-compatible,local PTZ 1-Remote network PTZ
	int					nCamID;									// Camera ID
	int                 nPort;                                  // Serial port number
	CFG_PRESET_HOMING   stuPresetHoming;                        // Don't operate ptz for a period of time, auto matic homing to the preset point
	int                 nControlMode;                           // Control Mode, 0:"RS485"serial port control(default);1:"Coaxial" Coaxial port control
} CFG_PTZ_INFO;

// Timing Function Type
typedef enum tagCFG_PTZ_FUNC_TYPE
{
	FUNC_TYPE_TOUR = 0 ,		//Tour
	FUNC_TYPE_PATTERN  ,		//Pattern
	FUNC_TYPE_PRE	   ,		//Preset
	FUNC_TYPE_SCAN	   ,		//Scan
	FUNC_TYPE_MAX	   ,		
}CFG_PTZ_FUNC_TYPE;


//Auto Homing
typedef struct tagCFG_AUTO_HOMING
{
	BOOL	bEnable;		// Auto Homing Switch
	int		nTime;			// Free Time,indicate Free Time ?ê?Unit is Second
}CFG_AUTO_HOMING;

//Regular Action Configuration
typedef struct tagCFG_PTZ_PER_AUTOMOVE_INFO
{
	BOOL				bEnable;		//	Regular action Switch Mark  TRUE open?ê?FALSE close
	CFG_TIME_SCHEDULE	stTimeSchedule;	//  Schedule Type 
	CFG_PTZ_FUNC_TYPE	emFuncType;		//  Timing Function
	int					nTourId;		// 	Tour ID,		Range refer CFG_PTZ_PROTOCOL_CAPS_INFO of wTourMin and wTourMax
	int					nPatternId;		// 	Pattern ID,	Range refer CFG_PTZ_PROTOCOL_CAPS_INFO of wPatternMin and wPatternMax
	int					nPresetId;		//  Preset ID,		Range refer CFG_PTZ_PROTOCOL_CAPS_INFO of wPresetMin and wPresetMax
	int					nScanId;		//	Scan ID,	Range refer CFG_PTZ_PROTOCOL_CAPS_INFO of wAutoScanMin and wAutoScanMax
	CFG_AUTO_HOMING		stAutoHoming;	//  AutoHoming,Period of time does not operate PTZ?ê?Automatic homing to the period of the action
	BOOL				bSnapshotEnable;		//	Snapshot enable
	int					nSnapshortDelayTime;	//	The delaytime of Snapshot
}CFG_PTZ_PER_AUTOMOVE_INFO;

typedef struct tagCFG_PTZ_ALL_AUTOMOVE_INFO
{
	CFG_PTZ_PER_AUTOMOVE_INFO stPTZPerInfo[MAX_CONFIG_NUM];		//Configuration Information
	int						  nCfgNum;							//Get the Number of Configuration
}CFG_PTZ_ALL_AUTOMOVE_INFO;

//PTZ configuration timed action?ê?Attention?ê?This Structure for the Device
typedef struct tagCFG_PTZ_AUTOMOVE_INFO
{
	CFG_PTZ_ALL_AUTOMOVE_INFO *pstPTZAutoConfig;				//PTZ Configuration Information
	int						   nMaxPTZNum;						//Structure PTZ Application Number(For Multi -Channel Query?ê?Apply for not less than Equipment Number?ê?For Single-channel Queries?ê?One is Enough)
	int						   nReturnPTZNum;					//The Number of PTZ Device Return(General is Device Channels)
}CFG_PTZ_AUTOMOVE_INFO;

//----------------------------------Video analysis device configuration------------------------------------------ 
//  Scene  rule supported
typedef struct
{
	DWORD             dwSupportedRule;                                         // Rule Type
	int               nSupportedObjectTypeNum;                                 // Supported object type number
	char              szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	   // Supported object type list
	int               nSupportedActionsNum;                                    // Supported detection object action number
	char              szSupportedActions[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];  // Supported detection object action list
	int               nSupportedDetectTypeNum;                                 // Supported detection type number
	char              szSupportedDetectTypes[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];// Supported detection type list
	int               nSupportFaceTypeNum;                                       // Supported facial recognition type number
	char              szSupportFaceTypes[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // Supported facial recognition type list
	BOOL              bTriggerPosition;                                        // Support trigger alarm position or not
}SCENE_SUPPORT_RULE;

// Calibrating area capacity info
typedef struct tagCFG_CAP_CELIBRATE_AREA
{
	EM_CALIBRATEAREA_TYPE  emType;												 // Calibrating area type
	BYTE                   byMaxHorizontalStaffNum;                              // Supported horizontal staff max number
	BYTE                   byMinHorizontalStaffNum;                              // Supported horizontal staff min number
	BYTE                   byMaxVerticalStaffNum;                                // Supported vertical staff max number
	BYTE                   byMinVerticalStaffNum;                                // Supported vertical staff min number
}CFG_CAP_CELIBRATE_AREA;

// Scene capacity
typedef struct tagCFG_CAP_SCENE
{
	char               szSceneName[MAX_PATH];                                   // Scene Name
	int                nSupportedObjectTypeNum;                                 // Number of detection object type supported by the current rule type
	char               szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// List of detection object type supported by the current rule type
	int                nSupportRules;                                           // Supported rule number
	SCENE_SUPPORT_RULE stSpportRules[MAX_RULE_LIST_SIZE];                       // Supported rule list

	//Supported module parameter
	bool               bDisturbance;                                            // Support disturbance sensitivity  set up or not 
	bool               bAntiDisturbance;                                        // Support anti-disturbance or not 
	bool               bBacklight;                                              // Support backlight or not 
	bool               bShadow;                                                 // Support shadow or not 
	bool               bAccuracy;                                               // Support test accuracy
	bool               bMovingStep;												// Support step detection  or not  
	bool               bScalingFactor;                                          //Support zoom detect or not 
	bool               bThresholdY;                                             // Support threshold Y or not 
	bool               bThresholdUV;                                            // Support threshold UV or not 
	bool               bThresholdEdge;                                          // Support edge detection to confirm threshold or not 
	bool               bDetectBalance;                                          // Support detecting balance or not 
	bool               bAlgorithmIndex;                                         // Support algorithm SN or not 
	bool               bHighlight;                                              // Support high light process ( the  background parameter)  
	bool               bSnapshot;                                               // Support object snapshot or not 
	bool               bDetectRegion;                                           // Support detection region configuration or not 
	bool               bExcludeRegion;                                          // Support exclusion region configuration or not 
	bool               bContourAssistantTrack;                                  // upport contour assistant track or not 

	//Supported scene parameter
	bool               bCameraAspect;                                            // Support camera parameter or not 
	bool               bJitter;                                                  // Support jitter parameter or not 
	bool               bDejitter;                                                // Support dejitter parameter or not 

	// Supported calibration capacity collection
	int               nMaxCalibrateAreaNum;                                      // Max calibration area number 
	int               nCalibrateAreaNum;                                         // Calibration area capacity info number
	CFG_CAP_CELIBRATE_AREA stCalibrateAreaCap[MAX_CALIBRATEAREA_TYPE_NUM];       //  Calibration area capacity info

	// Dimension filter measurement method
	bool              bPixel;                                                    // Support pixel measurement method or not 
	bool              bMetric;                                                   // Support real length measurement method or not 
	bool              bCalibratedPixel;                                          // Support measurement method with far and near-end calibration or not 

	char              szSubType[MAX_SCENE_SUBTYPE_NUM][MAX_SCENE_SUBTYPE_LEN];  // Sub- Scene Types Supported by the Current Scene
	int               nSubTypeNum;                                              // Sub- Scene Types Number
}CFG_CAP_SCENE;

//  Scene list
typedef struct tagCFG_VACAP_SUPPORTEDSCENES
{
	int                nScenes;													   //Supported scene number
	CFG_CAP_SCENE      stScenes[MAX_SCENE_LIST_SIZE];                              // Supported scene list
}CFG_VACAP_SUPPORTEDSCENES;

#define CFG_DEVICE_ANALYSE_INFO CFG_CAP_DEVICE_ANALYSE_INFO
//Video analysis device capacity info
typedef struct tagCFG_CAP_DEVICE_ANALYSE_INFO
{
	int                 nMaxChannels;                           // The max number of supported analyse channel
}CFG_CAP_DEVICE_ANALYSE_INFO;

//The rule's resbond object type
typedef struct
{
	DWORD               dwRuleType;                                             //Rule type
	int					nSupportedObjectTypeNum;								// The resbond object number
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// The object type list
}RULE_SUPPORTED_OBJECT_TYPE;

// scene compair info
typedef struct tagCFG_SUPPORTED_COMP
{
	int 	nSupportedData;													// the counts of scenes
	char	szSupportedData[MAX_SUPPORTED_COMP_DATA][CFG_COMMON_STRING_16];	// the list of scenes
}CFG_SUPPORTED_COMP;

typedef struct tagCFG_CAP_ANALYSE_INFO
{
	int					nSupportedSceneNum;										//  Supported scene number
	char				szSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];			//  Supported scene list
	int					nMaxMoudles;											//  Max analysis modules supported by each channel
	int					nSupportedObjectTypeNum;								//  Supported object type number
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	//  Supported object type list
	int					nMaxRules;												//  Max rules supported by each factory
	int					nSupportedRulesNum;										//  Supported event-type rule number
	DWORD				dwRulesType[MAX_RULE_LIST_SIZE];	             		// Supported event-type rule list, event type, details in dhnetsdk.h "Intellgence analyze event type"
	int					nMaxStaffs;												//   Supported max staff number
	int					nMaxPointOfLine;										// Max point of line
	int					nMaxPointOfRegion;										// Max point of region
	int                 nMaxInternalOptions;                                    // Max internal options
	bool                bComplexSizeFilter;                                     // Support complex size filter or not   complex size filter employ independent area filter and aspect ratio filter parameter     
	bool                bSpecifiedObjectFilter;                                 // Support specified object filter or not 
	int                 nMaxExcludeRegionNum;                                   // Support max exclusion region number in module
	int                 nMaxCalibrateBoxNum;                                    // Max calibration box number in supported module
	int                 nMinCalibrateBoxNum;                                    // Min calibration box number in module
	int                 nMaxSepcialDetectRegions;                               // max support special region detection in module
	int                 nSupportedTimeSectionNum;                               // number of periods in the day
	int                 nSpecialDetectPropertyNum;                              // Support special attributes number detection area
	int			        nSupportedSpecialDetectPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM]; // Support special testing area properties 
	DWORD				nSupportedVideoChannelType;								// Support video channel type choice  0 bit to 1 said support digital type, 1 bit to 1 said support	simulated type, 2 bit to 1 said support mix(digit and simulation) 			
	bool				bSupportMultiSceneSwitch;                               // Whether to Support More Scene Switching
	CFG_VACAP_SUPPORTEDSCENES  stSupportScenes;                                 // Supported Scene capacity collection
	int 				nSupportedComp; 										// the counts of supported scene comparis
	CFG_SUPPORTED_COMP	stuSupportedComp[MAX_SUPPORTED_COMP_SIZE];				// the list of supported scene comparis
	
} CFG_CAP_ANALYSE_INFO;

// Calibrate box info
typedef struct tagCFG_CALIBRATEBOX_INFO
{
	CFG_POLYGON         stuCenterPoint;                       // Calibrate box center point(0,8191)
	float               fRatio;                               // The relative ratio of the calibrate box(such as 1 means the calibrate box,0.5 means the half size of the calibrate box)
}CFG_CALIBRATEBOX_INFO;

// Calibrate area info 
typedef struct tagCFG_CALIBRATEAREA_INFO
{
	int               nLinePoint;                             // Horizontal staff points number
	CFG_POLYGON       stuLine[MAX_POLYLINE_NUM];              // Horizontal staff points
	float             fLenth;                                 //Actual lenth
	CFG_REGION        stuArea;                                // Area
	int                 nStaffNum;                            // Vertical staff points number
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];             // Vertical staff points         
	EM_CALIBRATEAREA_TYPE emType;							  // Region type
}CFG_CALIBRATEAREA_INFO;

// Facial recognition scene
typedef struct tagCFG_FACERECOGNITION_SCENCE_INFO
{
	double				dbCameraHeight;							// Camera height, meter
	double				dbCameraDistance;						// Camera distance, meter
	int                 nMainDirection;                         // Crowd main direction points number
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // Crowd main direction ,first point is start point,the secend point is end point
	char                byFaceAngleDown;                        // -45~45
	char                byFaceAngleUp;                          // -45~45
 	char                byFaceAngleLeft;                        // -45~45
	char                byFaceAngleRight;                       // -45~45
	EM_FACEDETECTION_TYPE	emDetectType;						//Face detect type
}CFG_FACERECOGNITION_SCENCE_INFO;

// Face detection scene
typedef struct tagCFG_FACEDETECTION_SCENCE_INFO
{
	double				dbCameraHeight;							// Camera height, meter
	double				dbCameraDistance;						// Camera distance, meter
	int                 nMainDirection;                         // Crowd main direction points number
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // Crowd main direction ,first point is start point,the secend point is end point
	char                byFaceAngleDown;                        // -45~45
	char                byFaceAngleUp;                          // -45~45
	char                byFaceAngleLeft;                        // -45~45
	char                byFaceAngleRight;                       // -45~45
	EM_FACEDETECTION_TYPE	emDetectType;						//Face detect type
}CFG_FACEDETECTION_SCENCE_INFO;


// Traffic light color correction configuration, sub-project
typedef struct tagADJUST_LEVEL_SEP
{
    int                 nType;                                  // 0: Undefined, 1: Video 2: Photo
    int                 nTime;                                  // 0: Undefined, 1: Day 2: Night
    int                 nLevel;                                 // range of 0 to 100, the greater the value, the more obvious correction
} ADJUST_LEVEL_SEP;

// Traffic light color correction configuration
typedef struct tagCFG_ADJUST_LIGHT_COLOR
{
    int                 nMode;                                  // traffic light color correction mode 0:undefined 1:traffic light corrected 2:always correct
    BOOL                bEnable;                                // whether allow correction of traffic color in picture
    int                 nLevel;                                 // correction level range 0~100 the higher the value, the more obvious the correction will be
    BOOL                bVideoEnable;                           // Whether enable video red paint function, when this option exists, level value uses Level value under LevelSeparate                               
    ADJUST_LEVEL_SEP    stLevelSep[4];                          // separate level, currently there are 4
} CFG_ADJUST_LIGHT_COLOR;

#define  MAX_PARKING_SPACE_NUM          6       // max config 6 parking info
#define  MAX_SHIELD_AREA_NUM            16      // 1 parking max corresponds to 16 shield zone
typedef struct tagCFG_PARKING_SPACE
{
    int             nNumber;                                     // parking no
    CFG_REGION      stArea;                                      // detection zone
    int             nShieldAreaNum;                              // valid shield zone number
    CFG_REGION      stShieldArea[MAX_SHIELD_AREA_NUM];           // shield zone
}CFG_PARKING_SPACE;

//  Traffic Scene
typedef struct tagCFG_TRAFFIC_SCENE_INFO 
{
	BOOL                abCompatibleMode;	
	int                 nCompatibleMode;                        // 0:"OldTrafficRule" : Traffic Old Rules Compatibility Mode;1:"NewTrafficRule" :  Traffic New Rules Compatibility Mode;-1:String Error
	float				fCameraHeight;							// The Camera Height from the Ground	Unit?êometer
	float				fCameraDistance;						// Camera Horizontal distance from the Center of a Ground Test Area	Unit?êometer
	char                szSubType[MAX_NAME_LEN];                // Traffic Scene Subtypes,"Gate" Bayonet Type,"Junction" Intersection Type 
																// "Tunnel"Tunnel Type , "ParkingSpace"Parking Space Detection Type
																// "Bridge"Bridge Type
																// "Freeway"Freeway Type                 
	CFG_POLYGON         stuNearDetectPoint;                     // Near Detect Point
	CFG_POLYGON         stuFarDectectPoint;                     // Far Dectect Point
	int                 nNearDistance;                          // NearDetectPoint,Conversion to the Actual Scene,The horizontal distance from the camera perpendicular line
	int                 nFarDistance;                           // FarDectectPoint,Conversion to the Actual Scene,The horizontal distance from the camera perpendicular line
	int                 nPlateHintNum;                          // Plate Characters Hint Number
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // Plate Characters Hint Array When you take a picture of poor quality and license plate recognition uncertain?ê?According to this array of characters to match?ê?The smaller array subscript?ê?the higher the match priority
	int                 nLaneNum;                               // Lane Number
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // Lane Information
    int                 nLightGroupNum;                         // Light group
	CFG_LIGHTGROUPS     stLightGroups[MAX_LIGHTGROUP_NUM];      // Light group config info
    BOOL                bHangingWordPlate;                      // whether recognize work plate
    BOOL                bNonStdPolicePlate;                     // whether recognize non-standard police plate
    BOOL                bYellowPlateLetter;                     // whether recognize yellow plate letter
    int                 nReportMode;                            // report mode, 0:undefined, 1:report all violation vehicles, 2: report plate successfully recognized violation vehicle
    int                 nPlateMatch;                            // plate matching rate. 0~100, multi-recognition of plate use, means required identification of repeated plate recognition and previous plate recognition
    int                 nJudgment;                              // violation judgment basis, 1:undefined, 1:by lane, 2: by driving direction, 3: by lane and driving direction
    int                 nLeftDivisionPtCount;                   // left turn boundary point
    CFG_POLYLINE        stLeftDivisionLine[MAX_POLYLINE_NUM];   // left turn boundary line
    int                 nRightDivisionPtCount;                  // right turn boundary point
    CFG_POLYLINE        stRightDivisionLine[MAX_POLYLINE_NUM];  // right turn boundary line
    CFG_ADJUST_LIGHT_COLOR  stAdjustLightColor;                 // traffic light color correction config
    int                 nParkingSpaceNum;                       // number of parking spaces
    CFG_PARKING_SPACE   stParkingSpaces [MAX_PARKING_SPACE_NUM];// parking configuration information, each element represents a parking space
} CFG_TRAFFIC_SCENE_INFO;

// Common Scene
typedef struct tagCFG_NORMAL_SCENE_INFO
{
	float				fCameraHeight;							// Camera distance to ground	unit?êom
	float				fCameraAngle;							// Camera and vertical direction angle	unit degree?ê?0~90?ê?
	float				fCameraDistance;						// Camera distance to ground center??￥s horizontal distance	unit?êom
	CFG_POLYGON			stuLandLineStart;						// Horizon line starting point(Point coordinate normalized to [0,8192) zone)
	CFG_POLYGON			stuLandLineEnd;							// Horizon line terminal(Point coordinate normalized to [0,8192)zone)
} CFG_NORMAL_SCENE_INFO;

//  Traffic Patrol Scene
typedef struct tagCFG_TRAFFIC_TOUR_SCENE_INFO 
{
	int                 nPlateHintNum;                          // Plate Characters Hint Number
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // late Characters Hint Array?ê?Plate Characters Hint Array When you take a picture of poor quality and license plate recognition uncertain?ê?According to this array of characters to match?ê?The smaller array subscript?ê?the higher the match priority
} CFG_TRAFFIC_TOUR_SCENE_INFO;

// the depth of scene
typedef enum tagEM_DEPTH_TYPE
{
	EM_DEPTH_UNKNOWN,		// unknown
	EM_DEPTH_NORMAL,		// "Normal" 
	EM_DEPTH_FAR,			// "Far" 
	EM_DEPTH_MIDDLE,		// "Middle" 
	EM_DEPTH_NEAR			// "Near" 
}EM_DEPTH_TYPE;


// the config of uniform scene
typedef struct tagCFG_INTELLI_UNIFORM_SCENE{
	char                szSubType[MAX_NAME_LEN];                // the sub type of traffic scene,"Gate" ,"Junction"  
																// "Tunnel", "ParkingSpace" "Bridge""Freeway"                
	int                 nPlateHintNum;                          // Plant hints chars number
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // Plant hints char info,when the pictrue was bad to recognize the plant,then it will use these hints for the plant,the litter index, the higher priority
	int                 nLaneNum;                               // Road number
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // Road info
}CFG_INTELLI_UNIFORM_SCENE;



//  Global Configuration Scenes Video Analysis
typedef struct tagCFG_ANALYSEGLOBAL_SCENE
{
	char				szSceneType[MAX_NAME_LEN];				// Application Scenes,See"Scene List of Supported"

	// The Following Information in Detail for Scene,According to szSceneType to Decide which Scene is Effective
	union
	{
		CFG_FACEDETECTION_SCENCE_INFO	stuFaceDetectionScene;	// Face Detection Scene/Face Recognition to Check
		CFG_TRAFFIC_SCENE_INFO			stuTrafficScene;		// Traffic Scene 
		CFG_NORMAL_SCENE_INFO			stuNormalScene;			// Common scenario/Vision Scene/Middle Scene /Close shot the Scene/Indoor Scene/People Counting Scene
		CFG_TRAFFIC_TOUR_SCENE_INFO		stuTrafficTourScene;	// Traffic Patrol Scene
	};

	EM_DEPTH_TYPE		emDepthType;							// picture depth of field
	int					nPtzPresetId;							// preset positions of ptz,0~255
	int					nSceneListCount;						//  the count of scene
	char				szSceneTypeList[MAX_SCENE_TYPE_LIST_SIZE][CFG_COMMON_STRING_16];//  the list of scene
	// The Following Information in Detail for Scene,According to szSceneTypeList to Decide which Scene is Effective
	CFG_INTELLI_UNIFORM_SCENE 	stuUniformScene; 				// the config of uniform scene
} CFG_ANALYSEGLOBAL_SCENE;

typedef struct tagCFG_TIME
{
	DWORD				dwHour;					//Hour
	DWORD				dwMinute;				//Minute
	DWORD				dwSecond;				// Second
}CFG_TIME;

typedef struct tagCFG_TIME_PERIOD
{
	CFG_TIME	stuStartTime;				
	CFG_TIME	stuEndTime;			
}CFG_TIME_PERIOD;

//  Many Scene Calibration Area Basic Unit Configuration
typedef struct tagCFG_CALIBRATEAREA_SCENE_UNIT
{
	unsigned int           nCalibrateAreaNum;                                // Calibrate Area Number
	CFG_CALIBRATEAREA_INFO stuCalibrateArea[MAX_CALIBRATEBOX_NUM];           // Calibrate Area(If the field does not exist?ê?the whole scene is the calibrate Area)
}
CFG_CALIBRATEAREA_SCENE_UNIT;

// Many Scene calibrate Area Configuration
typedef struct tagCFG_CALIBRATEAREA_SCENE_INFO
{
	DWORD                        dwMaxSceneCalibrateAreaNum;                // Many Scene Calibrate Area Maximum Number(Need to apply for the size of memory)
	DWORD                        dwRetSceneCalibrateAreaNum;                 // Actually Contains Many Scene Calibrate Area Number
	CFG_CALIBRATEAREA_SCENE_UNIT *pstuCalibrateArea;                         //  Many Scene Calibration Area unit
}
CFG_CALIBRATEAREA_SCENE_INFO;

// PTZ control coordinates unit
typedef struct tagCFG_PTZ_SPACE_UNIT
{
	int                    nPositionX;           //PTZ Horizontal Motion Position, the effective range ?êo[0,3600]
	int                    nPositionY;           //PTZ Vertical Position, the effective range: [-1800,1800]
	int                    nZoom;                //PTZ Iris Position Changes, effective range: [0,128]
}CFG_PTZ_SPACE_UNIT;

// Calibrate Area Configuration
typedef struct tagCFG_CALIBRATEAREA_UNIT
{
	int                          nSceneID;                                 // Scene ID
	int                          nPtzPresetID;                             // Preset ID
	BOOL                         abCalibrateArea;                          // Whether Calibrate Area exists;
	CFG_CALIBRATEAREA_SCENE_UNIT stuCalibrateArea;                         // Calibrate Area
	CFG_PTZ_SPACE_UNIT           stuPtzPosition;                           // Marked PTZ Position
}
CFG_VIDEO_ANALYSE_CALIBRATEAREA_UNIT;

// Calibrate Area Configuration
typedef struct tagCFG_VIDEO_ANALYSE_CALIBRATEAREA
{

	DWORD                                dwMaxSceneCalibrateNum;           //  Many Scene Calibrate Area Maximum Number(Need to apply for the size of memory
	DWORD                                dwRetSceneCalibrateNum;           // Actually Contains Many Scene Calibrate Area Number
	CFG_VIDEO_ANALYSE_CALIBRATEAREA_UNIT *pstuCalibrateAreaUnit;           //  Calibrate Area
}
CFG_VIDEO_ANALYSE_CALIBRATEAREA;

//Day and Night Algorithm Switching Mode
typedef enum tagCFG_TIMEPERIOD_SWITCH_MODE
{
	CFG_TIMEPERIOD_SWITCH_MODE_UNKNOWN,                                     // Unknown
	CFG_TIMEPERIOD_SWITCH_MODE_BYCOLOR,                                    // By Color Switch                      
	CFG_TIMEPERIOD_SWITCH_MODE_BYBRIGHTNESS,                               // By Brightness Switch
}CFG_TIMEPERIOD_SWITCH_MODE;

// Many Scene  Calibrate Day and night Basic Unit Configuration
typedef struct tagCFG_TIME_PERIOD_SCENE_UNIT
{
	CFG_TIME_PERIOD        stuDayTimePeriod;                                // Calibratie period during the day.(8,20), indicate from 8am to 20pm is for day time  
	CFG_TIME_PERIOD        stuNightTimePeriod;                              // Calibrate period during the night.(20,7), indicate from 8pm to 7am  is for night time  
	CFG_TIMEPERIOD_SWITCH_MODE emSwitchMode;                                // Day and night algorithm switching mode, see CFG_TIMEPERIOD_SWITCH_MODE
}
CFG_TIME_PERIOD_SCENE_UNIT;

//  Many Scene  Calibrate Day and night  Configuration
typedef struct tagCFG_TIME_PERIOD_SCENE_INFO
{
	DWORD                        dwMaxTimePeriodSceneNum;                   //  Many Scene calibration  Day and night configuration Maximum number(Need to apply for the size of memory)
	DWORD                        dwRetTimePeriodSceneNum;                   //  Actually Contains Many  Scene Calibrate  Day and Night Configuration Number
	CFG_TIME_PERIOD_SCENE_UNIT   *pstuTimePeriodScene;                      // Many  Scene Calibrate  Day and Night Configuration Domain  Unit
}CFG_TIME_PERIOD_SCENE_INFO;


// Video analyse global configration
typedef struct tagCFG_ANALYSEGLOBAL_INFO
{
		// Info
	char				szSceneType[MAX_NAME_LEN];				// Scene,see "supported scene list"

	// Traffic scene info
	double				CameraHeight;							// Camera height, meter
	double				CameraDistance;							// Camera distance, meter
	CFG_POLYGON         stuNearDetectPoint;                     // Near Detect Points
	CFG_POLYGON         stuFarDectectPoint;                     // Far Dectect Points
	int                 nNearDistance;                          // The distance between NearDetectPoint and camera
	int                 nFarDistance;                           // The distance between FarDectectPoint and camera
	char                szSubType[MAX_NAME_LEN];                // Traffic sence's sub type, such as "Gate","Junction"
	int                 nLaneNum;                               //Road numberC
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // Road info
	int                 nPlateHintNum;                          // Plant hints chars number
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // Plant hints char info,when the pictrue was bad to recognize the plant,then it will use these hints for the plant,the litter index, the higher priority
	int                 nLightGroupNum;                         // Light group number
	CFG_LIGHTGROUPS     stLightGroups[MAX_LIGHTGROUP_NUM];      // Light group info
    BOOL                bHangingWordPlate;                      // whether recognize work plate
    BOOL                bNonStdPolicePlate;                     // whether recognize non-standard police plate
    BOOL                bYellowPlateLetter;                     // whether recognize yellow plate letter
    int                 nReportMode;                            // report mode, 0:undefined, 1:report all violation vehicles, 2: report plate successfully recognized violation vehicle
    int                 nPlateMatch;                            // plate matching rate. 0~100, multi-recognition of plate use, means required identification of repeated plate recognition and previous plate recognition
    int                 nJudgment;                              // violation judgment basis, 0: undefined, 1: by lane, 2:by driving direction, 3: by lane and driving direction
    int                 nLeftDivisionPtCount;                   // left turn boundary point
    CFG_POLYLINE        stLeftDivisionLine[MAX_POLYLINE_NUM];   // left turn boundary line
    int                 nRightDivisionPtCount;                  // right turn boundary point
    CFG_POLYLINE        stRightDivisionLine[MAX_POLYLINE_NUM];  // right turn boundary line
    CFG_ADJUST_LIGHT_COLOR stAdjustLightColor;					// traffic light color correction config
    int                 nParkingSpaceNum;                       // parking number                             
    CFG_PARKING_SPACE   stParkingSpaces[MAX_PARKING_SPACE_NUM]; // parking config info, each element represents a parking

	// norml scene info 
	int                 nStaffNum;                              // Staff number
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];               // Staff
	
	unsigned int        nCalibrateAreaNum;                         // Calibrate Area Number
	CFG_CALIBRATEAREA_INFO stuCalibrateArea[MAX_CALIBRATEBOX_NUM]; // The calibrate area(if there is no calibrate area, then the whole sence will be the calibrate area)

	BOOL                bFaceRecognition;                          
	CFG_FACERECOGNITION_SCENCE_INFO stuFaceRecognitionScene;    // Face recognition info     
	bool                abJitter;
	bool                abDejitter;	
	BYTE                bReserved[2];                           // Reserved field

	int					nJitter;								// Camera jitter frequency,0-100. It is to reflect camera's jitter level, more jitter, higher value 
	BOOL                bDejitter;                              //  Turn on dejitter module or not   unrealistic for now 

	BOOL                abCompatibleMode;	
	int                 nCompatibleMode;                        // 0:"OldTrafficRule" : Previous  traffic rule compatible mode;1:"NewTrafficRule" :  new traffic rule compatible mode:-1:string error
    int                 nCustomDataLen;                         // Real data length, less than 1024
	BYTE                byCustomData[1024];                     // Config data
	double			    CameraAngle;						    // Camera angle
	CFG_POLYGON		    stuLandLineStart;					    //Start land line,in [0,8192)
	CFG_POLYGON		    stuLandLineEnd;					        // End land line,in [0,8192)
	BOOL				bFaceDetection;							// Face detection efficiency or not
	CFG_FACEDETECTION_SCENCE_INFO	stuFaceDetectionScene;		//Face detection scene
	CFG_TIME_PERIOD		stuDayTimePeriod;						// Calibrate Time of Day.(8,20),Indicate from 8am to 8pm  is daytime
	CFG_TIME_PERIOD		stuNightTimePeriod;						// Calibrate Time of Night.(20,7)?ê?Indicate from 8 pm to 7am is night
	CFG_TIME_PERIOD_SCENE_INFO      stuTimePeriodSceneInfo;     // MultiScenario Calibrate Day and night time
	CFG_CALIBRATEAREA_SCENE_INFO    stuCalibrateAreaSceneInfo;  // MultiScenario Calibrate Area  Configuration
	CFG_TIMEPERIOD_SWITCH_MODE emSwitchMode;                    // Day and Night Algorithm Switching Mode,See CFG_TIMEPERIOD_SWITCH_MODE

	int					nSceneNum;									// Scene Number, When >0 ,indicate that it support Mult-Scene, stuMultiScenario effective 
	CFG_ANALYSEGLOBAL_SCENE	stuMultiScene[MAX_ANALYSE_SCENE_NUM];	// MultiScenario Configuration

	int					nSceneCount;								//  the count of scene
	char				szSceneTypeList[MAX_SCENE_TYPE_LIST_SIZE][CFG_COMMON_STRING_16];//  the list of scene
	EM_DEPTH_TYPE		emDepthType;								// the depth of scene
	int					nPtzPresetId;								// PTZ preset Id 0~255

} CFG_ANALYSEGLOBAL_INFO;

// Size filter
typedef struct tagCFG_SIZEFILTER_INFO
{
	int                   nCalibrateBoxNum;                       // Calibration pane number
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM]; //  Calibration box (far and near-end calibration mode only)
	bool                bMeasureModeEnable;                       // Measurement mode enabled or not 
	BYTE                bMeasureMode;                             // Measurement mode, 0-pixel, far and near-end calibration not necessary, 1- real length, unit: meter, 2- pixel after far and near-end calibration
	bool                bFilterTypeEnable;                        // Filter type enabled or not 
	//  ByArea,ByRatio as compatible only, with independent ByArea and ByRatio alternatives as substitute 2012/03/06
	BYTE				bFilterType;			 				  //  Filter type:0:"ByLength",1:"ByArea", 2"ByWidthHeight"
	BYTE                bReserved[2];                             // Reserved field
	bool                bFilterMinSizeEnable;                     // Min object size parameter is valid or not  
	bool                bFilterMaxSizeEnable;                     // Max object size parameter is valid or not 
	CFG_SIZE			stuFilterMinSize;						  // Min object size      size of length ratio under "ByLength" Mode,size of area under "ByArea" mode, invalid height (size of standard box lengths under far and near-end calibration mode)
	CFG_SIZE			stuFilterMaxSize;				          // Max object size size of length ratio under "ByLength" mode, size of area under "ByArea" mode", invalid height (size of standard box lengths under far and near-end calibration mode)
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByArea;                                  // Filter by area or not. You can use ComplexSizeFilter to see it works or not. 
	bool                bReserved1[2];
	float               nMinArea;                                 // Min area
	float               nMaxArea;                                 // Max area
	CFG_SIZE            stuMinAreaSize;                           // Min area rectangle box.   When  "measurement method" is "pixel", it represents its sizes of lengths; when "measurement method" is "far and near-end calibration mode", it represents the min sizes of lengths of standard box
	CFG_SIZE            stuMaxAreaSize;                           // Max area rectangle box, same as above
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByRatio;                                 //  Filter by length ratio or not   . You can use ComplexSizeFilter to see it works or not. 
	bool                bReserved2[2];
	double              dMinRatio;                                // Min W/H ratio
	double              dMaxRatio;                                // Max W/H ratio
	CFG_SIZE            stuMinRatioSize;                          // Min W/H ratio rectangle box size, min W/H ratio corresponding to sizes of lengths of rectangle box
	CFG_SIZE            stuMaxRatioSize;                          // Max W/H ratio rectangle box size. See above information.
	
	int                 nAreaCalibrateBoxNum;                     // Area calibration box number
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// Area calibration box
	int                 nRatioCalibrateBoxs;                      // W/H calibration box number
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// W/H calibration box number
	
	bool                abBySize;                                 // Valid filter by L/H ration parameter enabled or not 
	bool                bBySize;                                  // L/W filter enabled
}CFG_SIZEFILTER_INFO;

// Filter for all specified objects
typedef struct tagCFG_OBJECT_SIZEFILTER_INFO
{
	char				szObjectType[MAX_NAME_LEN];              //Object type
	CFG_SIZEFILTER_INFO stSizeFilter;                            //  Corresponding size filter
}CFG_OBJECT_SIZEFILTER_INFO;

// Special detect region, refers to distinguish from the testing area, with special detection properties area
typedef struct tagCFG_SPECIALDETECTREGION_INFO
{
	int                nDetectNum;                              // Detect num
	CFG_POLYGON        stDetectRegion[MAX_POLYGON_NUM];         // Detect region 
	int                nPropertyNum;                            // Special detect attribute num
	int                nPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM];      // Special detect attribute
}CFG_SPECIALDETECT_INFO;

//Type of category
typedef enum tagCFG_CATEGORY_TYPE
{
    CFG_CATEGORY_TYPE_UNKNOW,                            // Unknown type
    // Related sub categories of vehicles
    CFG_CATEGORY_VEHICLE_TYPE_MOTOR,                     // "Motor"         
    CFG_CATEGORY_VEHICLE_TYPE_NON_MOTOR,                 // "Non-Motor"       
    CFG_CATEGORY_VEHICLE_TYPE_BUS,                       // "Bus"   
    CFG_CATEGORY_VEHICLE_TYPE_BICYCLE,                   // "Bicycle"     
    CFG_CATEGORY_VEHICLE_TYPE_MOTORCYCLE,                // "Motorcycle"     
    CFG_CATEGORY_VEHICLE_TYPE_UNLICENSEDMOTOR,           // "UnlicensedMotor"
    CFG_CATEGORY_VEHICLE_TYPE_LARGECAR,                  // "LargeCar"  
    CFG_CATEGORY_VEHICLE_TYPE_MICROCAR,                  // "MicroCar" 
    CFG_CATEGORY_VEHICLE_TYPE_EMBASSYCAR,                // "EmbassyCar" 
    CFG_CATEGORY_VEHICLE_TYPE_MARGINALCAR,               // "MarginalCar" 
    CFG_CATEGORY_VEHICLE_TYPE_AREAOUTCAR,                // "AreaoutCar" 
    CFG_CATEGORY_VEHICLE_TYPE_FOREIGNCAR,                // "ForeignCar" 
    CFG_CATEGORY_VEHICLE_TYPE_DUALTRIWHEELMOTORCYCLE,    // "DualTriWheelMotorcycle"
    CFG_CATEGORY_VEHICLE_TYPE_LIGHTMOTORCYCLE,           // "LightMotorcycle" 
    CFG_CATEGORY_VEHICLE_TYPE_EMBASSYMOTORCYCLE,         // "EmbassyMotorcycle"
    CFG_CATEGORY_VEHICLE_TYPE_MARGINALMOTORCYCLE,        // "MarginalMotorcycle"
    CFG_CATEGORY_VEHICLE_TYPE_AREAOUTMOTORCYCLE,         // "AreaoutMotorcycle" 
    CFG_CATEGORY_VEHICLE_TYPE_FOREIGNMOTORCYCLE,         // "ForeignMotorcycle "
    CFG_CATEGORY_VEHICLE_TYPE_FARMTRANSMITCAR,           // "FarmTransmitCar" 
    CFG_CATEGORY_VEHICLE_TYPE_TRACTOR,                   // "Tractor"
    CFG_CATEGORY_VEHICLE_TYPE_TRAILER,                   // "Trailer" 
    CFG_CATEGORY_VEHICLE_TYPE_COACHCAR,                  // "CoachCar"
    CFG_CATEGORY_VEHICLE_TYPE_COACHMOTORCYCLE,           // "CoachMotorcycle "
    CFG_CATEGORY_VEHICLE_TYPE_TRIALCAR,                  // "TrialCar"
    CFG_CATEGORY_VEHICLE_TYPE_TRIALMOTORCYCLE,           // "TrialMotorcycle "
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYENTRYCAR,         // "TemporaryEntryCar"
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYENTRYMOTORCYCLE,  // "TemporaryEntryMotorcycle"
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYSTEERCAR,         // "TemporarySteerCar"
    CFG_CATEGORY_VEHICLE_TYPE_PASSENGERCAR,              // "PassengerCar"
    CFG_CATEGORY_VEHICLE_TYPE_LARGETRUCK,                // "LargeTruck"
    CFG_CATEGORY_VEHICLE_TYPE_MIDTRUCK,                  // "MidTruck"
    CFG_CATEGORY_VEHICLE_TYPE_SALOONCAR,                 // "SaloonCar" 
    CFG_CATEGORY_VEHICLE_TYPE_MICROBUS,                  // "Microbus"
    CFG_CATEGORY_VEHICLE_TYPE_MICROTRUCK,                // "MicroTruck"
    CFG_CATEGORY_VEHICLE_TYPE_TRICYCLE,                  // "Tricycle"
    CFG_CATEGORY_VEHICLE_TYPE_PASSERBY,                  // "Passerby"

    // Related sub categories of licence plate
    CFG_CATEGORY_PLATE_TYPE_NORMAL,                      // "Normal" 
    CFG_CATEGORY_PLATE_TYPE_YELLOW,                      // "Yellow"
    CFG_CATEGORY_PLATE_TYPE_DOUBLEYELLOW,                // "DoubleYellow" 
    CFG_CATEGORY_PLATE_TYPE_POLICE,                      // "Police" 
    CFG_CATEGORY_PLATE_TYPE_ARMED,                       // "Armed" 
    CFG_CATEGORY_PLATE_TYPE_MILITARY,                    // "Military" 
    CFG_CATEGORY_PLATE_TYPE_DOUBLEMILITARY,              // "DoubleMilitary" 
    CFG_CATEGORY_PLATE_TYPE_SAR,                         // "SAR"    
    CFG_CATEGORY_PLATE_TYPE_TRAINNING,                   // "Trainning" 
    CFG_CATEGORY_PLATE_TYPE_PERSONAL,                    // "Personal" 
    CFG_CATEGORY_PLATE_TYPE_AGRI,                        // "Agri"
    CFG_CATEGORY_PLATE_TYPE_EMBASSY,                     // "Embassy"
    CFG_CATEGORY_PLATE_TYPE_MOTO,                        // "Moto" 
    CFG_CATEGORY_PLATE_TYPE_TRACTOR,                     // "Tractor"
    CFG_CATEGORY_PLATE_TYPE_OFFICIALCAR,                 // "OfficialCar "
    CFG_CATEGORY_PLATE_TYPE_PERSONALCAR,                 // "PersonalCar" 
    CFG_CATEGORY_PLATE_TYPE_WARCAR,                      // "WarCar"  
    CFG_CATEGORY_PLATE_TYPE_OTHER,                       // "Other" 
    CFG_CATEGORY_PLATE_TYPE_CIVILAVIATION,               // "Civilaviation" 
    CFG_CATEGORY_PLATE_TYPE_BLACK,                       // "Black" 
}CFG_CATEGORY_TYPE;

//Different region all kinds of module type's configuration
typedef struct tagCFG_MODULE_INFO
{
	// Info
	char				szObjectType[MAX_NAME_LEN];				// Module type,see "supported detect module type list"
	bool				bSnapShot;								// Enable snap shot
	BYTE                bSensitivity;                           // Sensitivity, 0-2,little value instruct high sensitivity
	bool                bMeasureModeEnable;                     // Measure mode enable
	BYTE                bMeasureMode;                           // Measure mode,0-pixel,1-actual lenth, meter, 2- pixel that has set the near point and far point
	int					nDetectRegionPoint;						// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// Detect region
	int					nTrackRegionPoint;						// Track region point number
	CFG_POLYGON			stuTrackRegion[MAX_POLYGON_NUM];		// Track region
	bool                bFilterTypeEnable;                      // Filter type enable
	BYTE				nFilterType;							// Filter type:0:"ByLength",1:"ByArea", 2"ByWidthHeight"
	bool                bBackgroudEnable;                       // Back ground enable
	BYTE                bBackgroud;                             // Back ground type, 0-normal, 1- high light
	bool                abBySize;                               // Valid filter by size enabled parameter or not 
	bool                bBySize;                                // Filter by size enabled
	bool                bFilterMinSizeEnable;                   // Module minmal size enable
	bool                bFilterMaxSizeEnable;                   // Module maxmal size enable
	CFG_SIZE			stuFilterMinSize;						// Module minmal size "ByLength": indecate width and height,"ByArea"width indecate area,height indecate nothing
	CFG_SIZE			stuFilterMaxSize;						// Module maxmal size "ByLength": indecate width and height,"ByArea"width indecate area,height indecate nothing
	int                 nExcludeRegionNum;                      // Exclude region number
	CFG_REGION          stuExcludeRegion[MAX_EXCLUDEREGION_NUM];// Exclude region
	int                 nCalibrateBoxNum;                       // Calibrate box number
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// calibrate box
	bool                bAccuracy;                               // Test accuracy enable
	BYTE                byAccuracy;                              // Test accuracy
	bool                bMovingStep;                             // Moving step enable                        
	BYTE                byMovingStep;                            // Moving step
	bool                bScalingFactor;							 // Scaling factor enable
	BYTE                byScalingFactor;						 // Scaling factor
	BYTE                bReserved2[1];                           // Reserved field
	bool                abDetectBalance;						 //Miss detect and error detect balance paramter is valid or not. parameter or not 
	int					nDetectBalance;							 // Miss detect and error detect balance  0-compromise mode (default) 1-less miss detection  2- less error detection
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByRatio;                                //  Filter by W/H ratio or not. You can use ComplexSizeFilte to see it works or not. You can use  nFilterType at the same time. 
	bool                bReserved1[2];
	double              dMinRatio;                               // Min W/H ratio
	double              dMaxRatio;                               // Max W/H ratio
	CFG_SIZE            stuMinAreaSize;                           //Min area rectangle box    When  "measurement method" is "pixel", it represents its sizes of lengths; when "measurement method" is "far and near-end calibration mode", it represents the min sizes of lengths of standard box

	CFG_SIZE            stuMaxAreaSize;                           // Max area rectangle box, same as above
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByArea;                                 // Filter by area ratio or not.You can use ComplexSizeFilte to see it works or not. You can use  nFilterType at the same time.    
	bool                bReserved3[2];
	float                 nMinArea;                                // Min area
	float                 nMaxArea;                                // Max area
	CFG_SIZE            stuMinRatioSize;                          // Min W/H ratio rectangle box size, min W/H ratio corresponding to sizes of lengths of rectangle box
	CFG_SIZE            stuMaxRatioSize;                          // Max W/H ratio rectangle box size

	
	int                 nAreaCalibrateBoxNum;                    // Area calibration box number
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];//  Area calibration pane
	int                 nRatioCalibrateBoxs;                      // Ratio calibration pane number
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// Ratio calibration pane number

	bool                bAntiDisturbance;                        // Turn on anti-disturbance module or not 
	bool                bBacklight;                              // There is backlight or not
	bool                bShadow;                                 // There is shadow or not?
	bool                bContourAssistantTrack;                  // Turn on contour assistant track or not   For example, for facial identification, it can identify face by tracking human body  
	int                 nPtzPresetId;                            // PTZ preset, 0~255, 0=stationary scene, ignored preset.

	int                 nObjectFilterNum;                        //  Object specified filter number
	CFG_OBJECT_SIZEFILTER_INFO stObjectFilter[MAX_OBJECT_LIST_SIZE]; //Object specified filter info

	BOOL                abObjectImageSize;                        
	CFG_SIZE            stObjectImageSize;                       // Ensure same size of object image, unit is pixel, nonsupport of decimal, take: >=0, 0 is automatic adjustion
	int                 nSpecailDetectNum;                                // Special detect num
	CFG_SPECIALDETECT_INFO stSpecialDetectRegions[MAX_SPECIALDETECT_NUM];  // Special detect region info

	unsigned int        nAttribute;                              // Number of attributes in the need to identitu objects
	char                szAttributes[MAX_OBJECT_ATTRIBUTES_SIZE][MAX_NAME_LEN];   // need to identify the object's attribute list,"Category" "Size" "Color" "Speed" "Sign" ,"Action" 
	
	BOOL                abPlateAnalyseMode;                      // nPlateAnalyseMode enable
	int                 nPlateAnalyseMode;                       //  License plate recognition model,0-only identify car license plate 1-only identify the rear license plate, 2-car license plate is preferred,3-the rear license plate is preferred

//szAttributes properties work when stored in "Category"
    unsigned int        nCategoryNum;                            // The total number of category types    CFG_CATEGORY_TYPE   emCategoryType[MAX_CATEGORY_TYPE_NUMBER]; // Sub type information
    CFG_CATEGORY_TYPE   emCategoryType[MAX_CATEGORY_TYPE_NUMBER]; // Category type
    char				szSceneType[CFG_COMMON_STRING_16];		// the type of scene

} CFG_MODULE_INFO;


typedef struct tagCFG_ANALYSEMODULES_INFO
{
	int					nMoudlesNum;							// Detect module number
	CFG_MODULE_INFO     stuModuleInfo[MAX_ANALYSE_MODULE_NUM];			// Each video channel's kinds of object's configration of detect module

} CFG_ANALYSEMODULES_INFO;

// Video analysis the event rule configuration
enum CFG_EM_DETECTMODE_T{
	CFG_EM_DETECTMODE_NONE,            // None
	CFG_EM_DETECTMODE_BY_VIDEO,        // Video detect mode
	CFG_EM_DETECTMODE_BY_BYAUDIO,      // Audio detect mode
	CFG_EM_DETECTMODE_BY_BOTH,         // Both of detect mode
	CFG_EM_DETECTMODE_ERR=255          // Data error
};

// Video analyse rule configuration
// Rule type:EVENT_IVS_CROSSLINEDETECTION configuration
typedef struct tagCFG_CROSSLINE_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								//Rule enable
    BYTE                bTrackEnable;                                           // Trigger tracking enabled, only the tripwire, intrusion rule is valid
	BYTE                bReserved[2];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nDirection;								// Detect direction:0:lefttoright;1:righttoleft;2:both
	int					nDetectLinePoint;						// Detect line point number
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];		// Detect line
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
 	BOOL                bDisableTimeSection;                           // stuTimeSection ,default FALSE:not disable,TRUE:disable,user control
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	int					nTrackDuration;											// 跟踪持续时间,0秒:一直跟踪,1~300秒:跟踪持续时?
} CFG_CROSSLINE_INFO;

//Rule type:EVENT_IVS_CROSSFENCEDETECTION configuration
typedef struct tagCFG_CROSSFENCEDETECTION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bTrackEnable;                                           // Trigger tracking enabled, only the tripwire, intrusion rule is valid
	BYTE                bReserved[2];                                           // Reserved
	int					nObjectTypeNum;											//Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nDirection;												// Cross fence direction:0:left to right;1:right to left;2:both
	int					nUpstairsLinePointNumber;								// Fence upstairs line point number
	CFG_POLYLINE		stuUpstairsLine[MAX_POLYLINE_NUM];						// Fence upstairs line points
	int					nDownstairsLinePointNumber;								// Fence downstairs line point number
	CFG_POLYLINE		stuDownstairsLine[MAX_POLYLINE_NUM];					// Fence downstairs line point
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int					nTrackDuration;											// the duration of track
} CFG_CROSSFENCEDETECTION_INFO;

//Rule type:EVENT_IVS_CROSSREGIONDETECTION configuration
typedef struct tagCFG_CROSSREGION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								//Rule enable
    BYTE                bTrackEnable;                                           // Trigger tracking enabled, only the tripwire, intrusion rule is valid
	BYTE                bReserved[2];                                           //Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nDirection;								// Detect direction:0:Enter;1:Leave;2:Both
	int					nDetectRegionPoint;						// Detect line point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// Detect line
		CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
 	BOOL                bDisableTimeSection;                           // stuTimeSection ,default FALSE:not disable,TRUE:disable,user control
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int                 nActionType;                                            // Action type number
	BYTE                bActionType[4];                                         // Action type list,0-apaer 1-disapaer 2-in area 3-cross area
	int                 nMinTargets;                                            // The min object number(it will work when bActionType = 2 )
	int                 nMaxTargets;                                            // The max object number(it will work when bActionType = 2 )
	int                 nMinDuration;                                           // Min duration, s(it will work when bActionType = 2 )
	int                 nReportInterval;                                        // Report interval time, s(it will work when bActionType = 2 )
	int					nTrackDuration;											// the duration of track
} CFG_CROSSREGION_INFO;

// Rule type:EVENT_IVS_PASTEDETECTION configuration
typedef struct tagCFG_PASTE_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
    int                 nSensitivity;                                           // sensitivity, range [1,10], the higher the sensitivity, the easier to detect	
} CFG_PASTE_INFO;

// Rule type:EVENT_IVS_LEFTDETECTION configuration
typedef struct tagCFG_LEFT_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int					nTrackDuration;											// the duration of track
} CFG_LEFT_INFO;

// Rule type:EVENT_IVS_TAKENAWAYDETECTION configuration
typedef struct tagCFG_TAKENAWAYDETECTION_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;											// Min duration, s,0~65535
	int					nDetectRegionPoint;										//Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			//Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int					nTrackDuration;											// the duration of track
} CFG_TAKENAWAYDETECTION_INFO;

//Rule type: EVENT_IVS_PARKINGDETECTION configuration
typedef struct tagCFG_PARKINGDETECTION_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;											// Min duration, s,0~65535
	int					nDetectRegionPoint;										// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerPosition;                                       // Trigger position number
	BYTE                bTriggerPosition[8];                                    // Trigger position,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int					nTrackDuration;											//  the duration of track
} CFG_PARKINGDETECTION_INFO;


//Rule type:EVENT_IVS_PRESERVATION configuration
typedef struct tagCFG_PRESERVATION_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           //Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535

} CFG_PRESERVATION_INFO;

// Rule type:EVENT_IVS_STAYDETECTION configuration
typedef struct tagCFG_STAY_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								//Rule enable
	BYTE                bReserved[3];                                           //Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			//Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	int                 nTriggerTargetsNumber;                                  // The people number that trigger alarm 
	int                 nReportInterval;                                        // Report interval time, s
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int					nTrackDuration;											// the duration of track
} CFG_STAY_INFO;

//Rule type:EVENT_IVS_WANDERDETECTION configuration
typedef struct tagCFG_WANDER_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								//Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	int                 nTriggerTargetsNumber;                                  // The people number that trigger alarm 
	int                 nReportInterval;                                        // Report interval time, s
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int					nTrackDuration;											// the duration of track
} CFG_WANDER_INFO;

// Rule type:EVENT_IVS_MOVEDETECTION configuration
typedef struct tagCFG_MOVE_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bSensitivity;                                           // Sensitivity(1-10), lower value, lower sensitivity
	BYTE                bReserved[2];    
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nTriggerSpeed;                                          // Trigger speed, km/h
	int                 nTriggerPosition;                                       // Trigger alarm position number
	BYTE                bTriggerPosition[8];                                    // Trigger alarm position, 0-target external box centre, 1- target external box left centre, 2- target external box top centre, 3- target external box right centre
	BOOL                bSizeFileter;                                           // Specified size filter of the rule is valid or not 
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Specified size filter of the rule
	int                 nTypeNumber;                                            // Detection type number
	BYTE                bDetectType[4];                                         // Detection action list, 0-fast, 1-abrupt speed up 2- abrupt slow down
	int					nTrackDuration;											// the duration of track
} CFG_MOVE_INFO;

//Rule type:EVENT_IVS_TAILDETECTION configuration
typedef struct tagCFG_TAIL_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           //Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535

} CFG_TAIL_INFO;

// Rule type:EVENT_IVS_RIOTERDETECTION configuration
typedef struct tagCFG_RIOTER_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bAreaPercent;                                           // The area percent that rioter has coverd
	BYTE                bSensitivity;                                           // Sensitivity(1-10). lower value, lower sensitivity, higher density of targeted group (replace bAreapercent)
	BYTE                bReserved;                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535

	int                 nReportInterval;							// Alarm report interval. Unit is second. [1,600].Default value is 0 means do not alarm repeatedly.                        
	CFG_POLYGON         stuMinDetectRect[2];						// Min gathering rectangle. Corresponding to the top left and right bottom of the rectangle. The actual area of the rectangle stands for the min person gathering area of the alarm activation. 
	int					nTrackDuration;								// the duration of track
} CFG_RIOTER_INFO;

// Event type  EVENT_IVS_DENSITYDETECTION (Group density detection event) corresponding rule configuration
typedef struct tagCFG_DENSITYDETECTION_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule 
	bool				bRuleEnable;											//Rule enable
	BYTE                bReserved1;                                             // Reserve field
	BYTE                bSensitivity;                                           // Sensitivity (1-10), lower value, lower sensitivity, higher density of targeted group 
	BYTE                bReserved2;                                             // Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int					nMinDuration;											// Min duration period   unit: second, 0~65535
	int					nDetectRegionPoint;										// Detection region acme amount
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detection region
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond period
	int                 nPtzPresetId;											// Preset number 0~65535
	
} CFG_DENSITYDETECTION_INFO;

//Rule type:EVENT_IVS_FIGHTDETECTION configuration
typedef struct tagCFG_FIGHT_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								//Rule enable
	BYTE                bReserved[3];                                           //Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nSensitivity;											// Sensitivity, 1-10
    CFG_EM_DETECTMODE_T emDetectMode;                                           // Detect mode

} CFG_FIGHT_INFO;

//Rule type:EVENT_IVS_FIREDETECTION configuration
typedef struct tagCFG_FIRE_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nSensitivity;											// Sensitivity 1~10
} CFG_FIRE_INFO;

//Add by lihu 2011/8/8 begin
//Rule type:EVENT_IVS_ELECTROSPARKDETECTION configuration
typedef struct tagCFG_ELECTROSPARK_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                               // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;								// PTZ preset Id 0~65535
	
} CFG_ELECTROSPARK_INFO;
// Add by lihu 2011/8/8 end
// Rule type:EVENT_IVS_SMOKEDETECTION configuration
typedef struct tagCFG_SMOKE_INFO 
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nMinDuration;								// Minimal duration,	0~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nSensitivity;											// Sensitivity 1~10
} CFG_SMOKE_INFO;

// Rule type EVENT_IVS_FLOWSTAT configuration
typedef struct tagCFG_FLOWSTAT_INFO
{
	//Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nUpperLimit;								// Flow stat upper limit, 1~65535(/s)
	int					nPeriod;									// Period,1~65535(s)
	int					nDetectLinePoint;							//Detect line point number
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];			// Detect line
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
		
} CFG_FLOWSTAT_INFO;

enum NET_NUMBERSTAT_TYPE
{
	NET_EM_NUMSTAT_TYPE_REGION,                  // "Region" Region type
		NET_EM_NUMSTAT_TYPE_ENTRANCE,            // "Entrance"  Entrance type
		NET_EM_NUMSTAT_TYPE_OTHER,               // Other
};
// Rule type EVENT_IVS_NUMBERSTAT configuration
typedef struct tagCFG_NUMBERSTAT_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								//Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nUpperLimit;								// Number stat upper limit, 1~65535
	int					nPeriod;									// Period,1~65535(s)
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	NET_NUMBERSTAT_TYPE emType;                                                 //  Numbers statistic type. It supports: "Region" type and "Entrance" type
	CFG_POLYGON         stDirection[2];                                         // Normal moving direction, this direction is correct, opposition is inverse. It is for entrance type only. First point is starting point, second point if end point, coordinates of all points are in [0,8191] region
    int                 nRecordInterval;                                        // Record period(1-10), unit: minute
	int					nEnterThreshold;										// the enter alarm Threshold,  0--no alarm
	int					nExitThreshold;											// the exit alarm Threshold, 0--no alarm
	int					nInsideThreshold;										// the inside alarm Threshold, 0--no alarm		
} CFG_NUMBERSTAT_INFO;

//Rule type EVENT_IVS_RETROGRADEDETECTION configuration
typedef struct tagCFG_RETROGRADEDETECTION_INFO
{
	//Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bSensitivity;                                           // Sensitivity, 1-10,the lower value the lower sensitivity
	BYTE                bReserved[2];                                           // Reserved 
	int					nObjectTypeNum;											//Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nDetectRegionPoint;										// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	int                 nDirectionPoint;                                        // Normal drive direction point number
	CFG_POLYGON			stuDirection[MAX_POLYLINE_NUM];					      	// Normal drive direction, (first point is start point,sencend point is end point,[0,8191])
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	CFG_ALARM_MSG_HANDLE stuEventHandler;										//Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
} CFG_RETROGRADEDETECTION_INFO;

//Rule type EVENT_IVS_ABNORMALRUNDETECTION configuration
typedef struct tagCFG_ABNORMALRUNDETECTION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bSensitivity;                                           // Sensitivity, 1-10,the lower value the lower sensitivity
	BYTE                bReserved[2];                                           // Reserved 
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nDetectRegionPoint;										// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region 
	BOOL                bSizeFileter;                                           // Size filter enable
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Size filter info
	int                 nTriggerPosition;                                       // Trigger possition number
	BYTE                bTriggerPosition[8];                                    // Trigger possition,0-object out frame center, 1-object out frame left center, 2-object out frame top center, 3-object out frame right center, 4-object out frame bottom center
	int                 nDetectType;                                            // Detect type 
	BYTE                bDetectType[4];                                         // Detect type,0-run fast, 1-sudden accelerate, 2-sudden decelerate
	int                 nTriggerSpeed;                                          // It will trigger alarm when speed exceed trigger speed, km/h
	int                 nMinDuration;                                           // Min duration s 0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
} CFG_ABNORMALRUNDETECTION_INFO;

//Rule type EVENT_IVS_VIDEOABNORMALDETECTION configuration
typedef struct tagCFG_VIDEOABNORMALDETECTION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bSensitivity;                                           // Sensitivity, 1-10,the lower value the lower sensitivity)
	BYTE                bReserved[2];                                           // Reserved 
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nDetectType;                                            // Detect type
	BYTE                bDetectType[MAX_ABNORMAL_DETECT_TYPE];                  // Detect type,0-video lost, 1-video blind, 2-video freeze, 3- too light, 4-too dark, 5-sence change
                                                                                // 6-stripe detect , 7-noise detect , 8-??é??ì2a , 9-êó?μ?￡oy?ì2a , 10-constrast abnormal
                                                                                // 11-êó?μ???ˉ , 12-video flash , 13-video color , 14-Dé?1?ì2a , 15-over expose
	int					nMinDuration;											// Min duration s 0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region 
	int					nThresholdNum;											// the counts of threshold 
	int					nThreshold[MAX_ABNORMAL_THRESHOLD_LEN];					// the threshold data, 1~100
	
} CFG_VIDEOABNORMALDETECTION_INFO;

// Rule type EVENT_IVS_FACERECOGNITION configuration
typedef struct tagCFG_FACERECOGNITION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[2];                                           // Reserved 
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	BYTE                 bySimilarity;                                          // Similarity,it will report when over this similarity(1~100)
	BYTE                 byAccuracy;                                            // Accuracy(1~10,the higher value,the higher accuracy,the lower speed. when be valued 1 means speed first, when be valued 10 means accuracy first)
	BYTE                 byMode;                                                // Mode, 0-normal, 1-area compounding, 2-aptitude mode
	BYTE                 byImportantRank;                                       // Important rank(1~10,the higher value the higher important)
	int                  nAreaNum;                                              //Area number  
	BYTE                 byAreas[8];                                            // Area compounding, 0-eyebrow,1-eye,2-nose,3-mouth,4-face(it work when mode = 1)
	int                  nMaxCandidate;                                         // The max pictrue number that fixed
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
} CFG_FACERECOGNITION_INFO;

// Rule type EVENT_IVS_TRAFFICCONTROL configuration
typedef struct tagCFG_TRAFFICCONTROL_INFO 
{
	// Info
	char				szRuleName[MAX_NAME_LEN];									// Rule name,different rule mast have different name
	bool				bRuleEnable;												// Rule enable
	BYTE                bReserved[3];                                               // Reserved
	int					nObjectTypeNum;												// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];			// Current object list
	int					nDetectLinePoint;							            	// Detect line point number
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];			            	// Detect line
	CFG_TIME_SECTION	stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];           	//Time schedule
	int					nVehicleSizeNum;							            	// Vehicle size number
	char				szVehicleSizeList[MAX_VEHICLE_SIZE_LIST][MAX_NAME_LEN];		// Vehicle size type list
	int					nPlateTypeNum;												// Plate type number
	char				szPlateTypesList[MAX_PLATE_TYPE_LIST][MAX_NAME_LEN];		// Plate type list
	int					nPlateNumber;												// Plate muber 0:odd; 1:even; 2:both;
	CFG_ALARM_MSG_HANDLE stuEventHandler;											// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];				// Event respond time section
	int                 nPtzPresetId;												// PTZ preset Id 0~65535
} CFG_TRAFFICCONTROL_INFO;

// Rule type EVENT_IVS_TRAFFICACCIDENT configuration
typedef struct tagCFG_TRAACCIDENT_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nDetectRegionPoint;							// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// Detect region
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	
} CFG_TRAACCIDENT_INFO;

// Rule type EVENT_IVS_TRAFFICJUNCTION configuration
typedef struct tagCFG_TRAJUNCTION_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];				// Rule name,different rule mast have different name
	bool				bRuleEnable;							// Rule enable
	int					nObjectTypeNum;							// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nLane;									// Road number
	int                 nDirection;                             // Road direction
	int					nPreLinePoint;							// Pre-line point number
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			// Pre-line 
	int					nMiddleLinePoint;						// Middle line point number
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		// Middle line 
	int					nPostLinePoint;							// Post-line point number
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			// Post-line 
	int                 nFlowLimit;                             // Flow up limit, one/s
	int                 nSpeedDownLimit;                        // Speed low limit,if it valued 0 means there's no low limit,km/h
	int                 nSpeedUpLimit;                          // Speed up limit,if it valued 0 means there's no up limit,km/h
	int                 nTriggerModeNum;                        // Trigger mode number
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];  // Trigger mode "Passing" : (set the line in the Middle as trigger,it can only be used separately),"RunRedLight" 
																// "Overline","OverYellowLine", "Retrograde"
																// "TurnLeft", "TurnRight", "CrossLane"
																// "U-Turn" , "Parking", "WaitingArea" 
																// "OverSpeed","UnderSpeed","Overflow"
																// "Human","NoMotor"
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	BOOL                bMaskRetrograde;         	             // Wether mask retrograde
			
} CFG_TRAJUNCTION_INFO;

// Rule type EVENT_IVS_TRAFFICGATE configuration
typedef struct tagCFG_TRAFFICGATE_INFO
{
	// Info
	char				szRuleName[MAX_NAME_LEN];					// Rule name,different rule mast have different name
	bool				bRuleEnable;								// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;								// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nLane;									// Road number
	int					nDetectLinePoint1;						// Detect line1 point number
	CFG_POLYLINE		stuDetectLine1[MAX_POLYLINE_NUM];		// Detect line1
	int					nDetectLinePoint2;						// Detect line2 point number
	CFG_POLYLINE		stuDetectLine2[MAX_POLYLINE_NUM];		// Detect line2
	int					nLeftLinePoint;							// Left road line point number
	CFG_POLYLINE		stuLeftLine[MAX_POLYLINE_NUM];			// Left road line
	int					nRightLinePoint;						// Right road line point number
	CFG_POLYLINE		stuRightLine[MAX_POLYLINE_NUM];			// Right road line
	int					nSpeedWeight;							// Speed weight (finale speed =detect dspeed*weight)
	double				MetricDistance;							// Two detect line distance,m
	int					nSpeedUpperLimit;						// Speed upper limit 0 indecate no upper limit,km/h
	int					nSpeedLowerLimit;						// Speed lower limit 0 indecate no lower limit,km/h
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// Event respond time section
	int                 nDirection;                                 // Road diretion(the direction the car go),0-north 1-east north 2-east 3-east south 4-south 5-west south 6-west south 7-west north
	int                 nTriggerModeNum;                            // Trigger mode number
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];  // Trigger mode,"OverLine","Retrograde","OverSpeed","UnderSpeed"
	                                                                       // "Passing", "WrongRunningRoute"(be used alone),"YellowVehicleInRoute"
	                                                                       // "OverYellowLine"
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	BOOL                bMaskRetrograde;         	             //  Wether mask retrograde
} CFG_TRAFFICGATE_INFO;

//  Event type EVENT_IVS_TRAFFIC_TOLLGATE ( Traffic ANPR new rule event) Corresponding rule configuration
typedef struct tagCFG_TRAFFICTOLLGATE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								//  Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											// Corresponding object type
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset (0~65535)

	int					nLane;													//  Lane number
	int					nDetectLinePoint;										// ANPR alarm acme amount
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// ANPR alarm line

	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond period
} CFG_TRAFFICTOLLGATE_INFO;

// Rule type EVENT_IVS_FACEDETECT configuration
typedef struct tagCFG_FACEDETECT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int					nDetectRegionPoint;										// Detect region point number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	int                 nHumanFaceTypeCount;                                    // Current face's number
	char                szHumanFaceType[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // Current face list
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int                 nMinDuration;                                           // Minimum Triggering Time, Unit: Second 
    int                 nSensitivity;                                           // sensitivity, range [1,10], the higher the sensitivity, the easier to detect
    int                 nReportInterval;                                        // repeat alarm interval, unit:s, [0,600] (when it is 0, it means no repeated alarm)
    BOOL                bSizeFileter;                                           // whether rule special dimension filter is valid or not
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // rule special dimension filter
}CFG_FACEDETECT_INFO;

//Rule type EVENT_IVS_TRAFFIC_NOPASSING configuration
typedef struct tagCFG_NOPASSING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
}CFG_NOPASSING_INFO;

// Rule type EVENT_IVS_TRAFFICJAM configuration
typedef struct tagCFG_TRAFFICJAM_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bJamLineMargin;                                         // The line's busy limit, congestion length lane share value ,0-100
	BYTE                bReserved[2];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	int                 nDelayTime;                                             // Start report time, s, 1~65535
	int                 nIntervalTime;                                          // Alarm interval time, s, 1~65535
	int                 nReportTimes;                                           // Report time, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int		            nDetectRegionPoint;                                     // Detect region point
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detect region 
}CFG_TRAFFICJAM_INFO;

// Rule typeEVENT_IVS_TRAFFIC_IDLE (traffic free events)configuration
typedef struct tagCFG_TRAFFIC_IDLE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bJamLineMargin;                                         // The line's busy limit, congestion length lane share value ,0-100
	BYTE                bReserved[2];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id	0~65535
	int					nLane;													// Road number
	int                 nDelayTime;                                             // Start report time, s, 1~65535
	int                 nIntervalTime;                                          // Alarm interval time, s, 1~65535
	int                 nReportTimes;                                           // Report time, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										//Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int		            nDetectRegionPoint;                                     // Detect region point
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detect region
}CFG_TRAFFIC_IDLE_INFO;


// Rule type EVENT_IVS_TRAFFIC_PARKING configuration
typedef struct tagCFG_TRAFFIC_PARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    bool                bTrackEnable;                                           // trigger tricking enable, track tripwire, intrusion object
    BYTE                bSensitivity;                                           // sensitivity, value 1-10, the lower the value, the lower the sensitivity (only detect video tampering, too bright, too dark, scene change)
	BYTE                bReserved;                                              // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	int                 nDelayTime;                                             // Start report time, s, 1~65535
	int                 nParkingAllowedTime;                                    // Alarm interval time, s, 1~65535
	int                 nReportTimes;                                           // Report time, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int					nDetectRegionPoint;										//Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	
}CFG_TRAFFIC_PARKING_INFO;

// Rule type EVENT_IVS_TRAFFIC_RUNREDLIGHT configuration
typedef struct tagCFG_TRAFFIC_RUNREDLIGHT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	int                 nDirection;                                             // Road direction, 0-north 1-east north 2-east 3-east south 4-south 5-west south 6-west 7-west north
	int					nPreLinePoint;							                // Pre detect line point number
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			                // Pre detect line info
	int					nMiddleLinePoint;						                // Mid detect line point number
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		                // Mid detect line info
	int					nPostLinePoint;							                // Post detect line point number
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			                // Post detect line info
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
}CFG_TRAFFIC_RUNREDLIGHT_INFO;

// Event type EVENT_IVS_TRAFFIC_PEDESTRAINRUNREDLIGHT (traffic violation-pedestrian run red light) corresponding rule config
typedef struct tagCFG_TRAFFIC_PEDESTRAINRUNREDLIGHT_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// rule name, different rule cannot have same name
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];                                           // reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no.	0~65535
    int					nLane;													// lane no.
    int                 nDirection;                                             // lane direction(driving direction) 0-N 1-NE 2-E 3-SE 4-S 5-SW 6-W 7-NW
    int					nPreLinePoint;							                // front detection line top number
    CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			                // front detection line
    int					nMiddleLinePoint;						                // central detection line top number
    CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		                // central detection line
    int					nPostLinePoint;							                // rear detection line top number
    CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			                // rear detection line
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period
}CFG_TRAFFIC_PEDESTRAINRUNREDLIGHT_INFO;

// Rule type EVENT_IVS_TRAFFIC_WRONGROUTE configuration
typedef struct tagCFG_TRAFFIC_WRONGROUTE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity(value 1-10)the higher the value the higher the sensitivity
    bool                bTrackEnable;                                           // trigger tracking enable, for tripwire, intrusion object tracking
    BYTE                bReserved;												// reserved field
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal driving direction top
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal driving direction?ê?first point is starting point?ê?last point is end point
	
}CFG_TRAFFIC_WRONGROUTE_INFO;

// Rule type EVENT_IVS_TRAFFIC_CROSSLANE configuration
typedef struct tagCFG_TRAFFIC_CROSSLANE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal driving direction top
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point	
}CFG_TRAFFIC_CROSSLANE_INFO;

// Rule type EVENT_IVS_TRAFFIC_OVERLINE configuration
typedef struct tagCFG_TRAFFIC_OVERLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal driving direction top
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point

	
}CFG_TRAFFIC_OVERLINE_INFO;

// Rule type EVENT_IVS_TRAFFIC_OVERYELLOWLINE configuration
typedef struct tagCFG_TRAFFIC_OVERYELLOWLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
}CFG_TRAFFIC_OVERYELLOWLINE_INFO;

// Rule type EVENT_IVS_TRAFFIC_RETROGRADE configuration
typedef struct tagCFG_TRAFFIC_RETROGRADE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    bool                bTrackEnable;                                           // Trigger tracking enabled for tripwire, invasion of object tracking
	BYTE                bReserved[2];                                           // Reserved field
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	BOOL                bLegal;                                                 // TRUE: Legel opposition;FALSE:Illegal opposition
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	int                 nDirectionLinPoint;                                     // Normal driving direction point
	CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal driving direction,the first point is starting,the last point is the end
	int					nMinDuration;											// Minimum Triggering Time, Unit: Second
}CFG_TRAFFIC_RETROGRADE_INFO;

// Rule type EVENT_IVS_TRAFFIC_TURNLEFT configuration
typedef struct tagCFG_TRAFFIC_TURNLEFT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal direction top 
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point

	
}CFG_TRAFFIC_TURNLEFT_INFO;

// Rule type EVENT_IVS_TRAFFIC_TURNRIGHT configuration
typedef struct tagCFG_TRAFFIC_TURNRIGHT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal direction top 
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point
}CFG_TRAFFIC_TURNRIGHT_INFO;

// Rule type EVENT_IVS_TRAFFIC_UTURN configuration
typedef struct tagCFG_TRAFFIC_UTURN_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    bool                bTrackEnable;                                           // Trigger tracking enabled for tripwire, invasion of object tracking
	BYTE                bReserved[2];                                           // Reserved field
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
	int					nTriggerAngle;											// Turn around the trigger angle,range(90,180),the target head angle before and after
	BOOL                abSizeFileter;                                          // Regulatons specific the size of the filter is efficiency or not
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Regulatons specific the size of the filter
	
}CFG_TRAFFIC_UTURN_INFO;

// Rule type EVENT_IVS_TRAFFIC_OVERSPEED configuration
typedef struct tagCFG_TRAFFIC_OVERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	int                 nSpeedUpperLimit;                                       // Speed Upper Limit
	int                 nSpeedLowerLimit;                                       // Speed Lower Limit
	int					nMinDuration;											// Minimum Triggering Time, Unit: Second
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
}CFG_TRAFFIC_OVERSPEED_INFO;

// Rule type EVENT_IVS_TRAFFIC_UNDERSPEED configuration
typedef struct tagCFG_TRAFFIC_UNDERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	int                 nSpeedUpperLimit;                                       // Speed Upper Limit
	int                 nSpeedLowerLimit;                                       // Speed Lower Limit
	int					nMinDuration;											// Minimum Triggering Time, Unit: Second
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm event handler
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
	
}CFG_TRAFFIC_UNDERSPEED_INFO;

// Rule type EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE configuration
typedef struct tagCFG_TRAFFIC_YELLOWPLATEINLANE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name,different rule mast have different name
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											// Current object's number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Current object list
	int                 nPtzPresetId;											// PTZ preset Id 0~65535
	int					nLane;													// Road number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Speed Upper Limit
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time section
    
    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal direction top 
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point

}CFG_TRAFFIC_YELLOWPLATEINLANE_INFO;
// Event type EVENT_IVS_TRAFFIC_VEHICLEINROUTE (Traffic law violation- vehicle lane occupation ) corresponding rule configuration
typedef struct tagCFG_TRAFFIC_VEHICLEINROUTE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								//  Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bReserved[2];                                           // Reserved text
	int					nObjectTypeNum;											//Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list

	int                 nPtzPresetId;											// PTZ preset number 0~65535
	int					nLane;													//Lane number
	CFG_ALARM_MSG_HANDLE stuEventHandler;										//Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			//Event responding period
    
    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal direction top 
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point
	
}CFG_TRAFFIC_VEHICLEINROUTE_INFO;

// Event type EVENT_IVS_PRISONERRISEDETECTION (Prisoner raise detection in the jail event) corresponding rule configuration
typedef struct tagCFG_PRISONRISEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											//Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ number 0~65535 	 
	int					nDetectRegionPoint;										//Warning zome acme 
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM10];						//Warning zone
	CFG_POLYGON			stDirection[2];											//  Direction of sleeping.  First point is starting point, second point is end point, coordinates of all points are in [0,8191] region
	CFG_POLYGON			stBedMiddleLine[2];										// Bed middle line. Coordinates of all points are in [0,8191] region
	int					nBedSide;												// Bed Side 1:Left bed, 2: right bed
	int					nMinDuration;											// Min trigger time  unit:second
	int					nReportInterval;										// Repeated alarm report interval  unit:second
	BOOL                bSizeFileter;                                           // Specified size filter of the rule is valid or not. 
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Specified size filter of the rule
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time
}CFG_PRISONRISEDETECTION_INFO; 

// Event type EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY (Event of pedestrian priority at crossing line) corresponding rule configuration
typedef struct tagCFG_TRAFFIC_PEDESTRAINPRIORITY_INFO
{
	char                szRuleName[MAX_NAME_LEN];                               // Rule name, different name apply to seperate rule
	bool                bRuleEnable;                                            // Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int                 nObjectTypeNum;                                         // Corresponding object type number
	char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object type list
	int                 nPtzPresetId;                                           // PTZ preset number 0~65535 
	int                 nLane;                                                  // Lane number
	CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm linkage
	CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];            // Event respond time
}CFG_TRAFFIC_PEDESTRAINPRIORITY_INFO;

// Event type EVENT_IVS_QUEUEDETECTION (Event of Queue detection over length) corresponding rule configuration
typedef struct tagCFG_IVS_QUEUEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number 0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time
	
	CFG_POLYLINE		stuDetectLine[2];						// Detect Line
	int                 nOccupyLineMargin;                      // Occupy Line Margin
	int                 nTriggerTime;                           // Over the time to alarm
}CFG_IVS_QUEUEDETECTION_INFO;

// Event type EVENT_IVS_CLIMBDETECTION (Event of climb detection)corresponding rule configuration
typedef struct tagCFG_IVS_CLIMBDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           //  Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number 	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time

	int                 nDetectLine;                                            // number of detect line
	CFG_POLYLINE        stuDetectLine[MAX_POLYLINE_NUM];                        // Detect line,[0,8192)
	BOOL                bSizeFileter;                                           // Specified size filter of the rule is valid or not. 
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Specified size filter of the rule
}CFG_IVS_CLIMBDETECTION_INFO;

// Event type EVENT_IVS_LEAVEDETECTION (Event of leave detection)corresponding rule configuration
enum CFG_EM_LEAVEDETECTION_MODE{
	CFG_EM_LEAVEDETECTION_MODE_NONE,
	CFG_EM_LEAVEDETECTION_MODE_PATROL,    // Patrol mode
	CFG_EM_LEAVEDETECTION_MODE_SENTRY,    // Sentry mode
	CFG_EM_LEAVEDETECTION_MODE_ERR=255
};

typedef enum EM_CFG_LEAVEDETECTION_TRIGGERMODE{
    CFG_LEAVEDETECTION_TRIGGERMODE_UNKNOWN,
    CFG_LEAVEDETECTION_TRIGGERMODE_NOPERSON,
    CFG_LEAVEDETECTION_TRIGGERMODE_LEAVE,
    CFG_LEAVEDETECTION_TRIGGERMODE_STATIC,
}CFG_LEAVEDETECTION_TRIGGERMODE;

typedef struct tagCFG_IVS_LEAVEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											//  Rule enable
	BYTE                bReserved[3];                                           //  Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		//Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number 	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time

	CFG_EM_LEAVEDETECTION_MODE emMode;                                          // Detection mode
	unsigned int        nMinDuration;                                           // The sortest duration, (s)
	unsigned int        nReportInterval;                                        // Report time interval,(s)
	BOOL                bSizeFileter;                                           // Specified size filter of the rule is valid or not. 
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // Specified size filter of the rule

	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region 
    int                 nTriggerModeCount;
    CFG_LEAVEDETECTION_TRIGGERMODE  emTriggerMode[MAX_TRIGGER_MODE_NUMBER];   
}CFG_IVS_LEAVEDETECTION_INFO;

//Event type EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX(Event of parking on yellowbox)corresponding rule configuration
typedef struct tagCFG_TRAFFIC_PARKINGONYELLOWBOX_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time

	int					nLane;													// Track num
	int					nInterval1;												//The first and second time interval(s)
	int					nInterval2;												// The thrid and second time interval(s)
	int					nFollowTime;											// Follow time,if a car and a car before entering the pornographic websites,is less than this value,just as with car to enter, to enter the case if the parkingis not illegal

}CFG_TRAFFIC_PARKINGONYELLOWBOX_INFO;

//Event type	EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING(Event of parking space parking)corresponding rule configuration
typedef struct tagCFG_TRAFFIC_PARKINGSPACEPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time
	
	int					nLane;													// Rack num
	int                 nDelayTime;                                             // Detection to alarm to report the time interval (s),range 1~65535
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
}CFG_TRAFFIC_PARKINGSPACEPARKING_INFO;

//Event type	EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING(Event of parking space no parking)corresponding rule configuration
typedef struct tagCFG_TRAFFIC_PARKINGSPACENOPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule name, different name apply to seperate rule
	bool				bRuleEnable;											// Rule enable
	BYTE                bReserved[3];                                           // Reserved field
	int					nObjectTypeNum;											// Corresponding object type number
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
	int                 nPtzPresetId;											// PTZ preset number	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event respond time
	
	int					nLane;													//Rack num
	int                 nDelayTime;                                             // Detection to alarm to report the time interval (s),range 1~65535
	int					nDetectRegionPoint;										// Detect region point
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// Detect region
}CFG_TRAFFIC_PARKINGSPACENOPARKING_INFO;

//Event Type: EVENT_IVS_TRAFFIC_PARKINGSPACEOVERLINE(TrafficParkingSpaceOverLine) and Its Corresponding Rule Configuration
typedef struct tagCFG_TRAFFIC_PARKINGSPACEOVERLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// Rule Name, Different Rules Must Be Unique
	bool				bRuleEnable;											// Rule Enable
	bool                bAllowParkingSpaceParkingSnap;                          // Whether to Allow Parking Space to Upload Snapshot?ê?True-Allowed(Default-Not Allowed)
	BYTE                byReserved[2];                                           // Reserved Fields
	int					nObjectTypeNum;											// The Number of the Corresponding Object Type
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// List of the Corresponding Object Type
	int                 nPtzPresetId;											// The Number of PTZ Presetting Point 0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm and Joint-Act
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Duration of the Incident Response
	
	int					nLane;													// Parking Space Number
}CFG_TRAFFIC_PARKINGSPACEOVERLINE_INFO;

//Event type EVENT_IVS_TRAFFIC_PEDESTRAIN (Event of goer)corresponding rule configuration
typedef struct tagCFG_TRAFFIC_PEDESTRAIN_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different name apply to seperate rule
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserved field
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object type list
    int                 nPtzPresetId;                                           // PTZ preset number 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm linkage
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event respond time
    
    int                 nLane;                                                  // Rack num
    int                 nDetectRegionPoint;                                     // Detect region point
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detect region
    int                 nMinDuration;                                           // Trigger the shortest time (s)
}CFG_TRAFFIC_PEDESTRAIN_INFO;

//Event type EVENT_IVS_TRAFFIC_THROW (Event of away)corresponding rule configuration
typedef struct tagCFG_TRAFFIC_THROW_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different name apply to seperate rule
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserved field
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object type list
    int                 nPtzPresetId;                                           // PTZ preset number 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm linkage
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event respond time
    
    int                 nLane;                                                  //  Rack num
    int                 nDetectRegionPoint;                                     // Detect region point
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detect region
    int                 nMinDuration;                                           // Trigger the shortest time (s)
}CFG_TRAFFIC_THROW_INFO;

// Event type EVENT_IVS_TRAFFIC_BACKING (back up event) corresponding rule config
typedef struct tagCFG_TRAFFIC_BACKING_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// Rule name, different rule cannot be repeated
    bool				bRuleEnable;											// Rule enable
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    bool                bTrackEnable;                                           // Trigger tracking enabled for tripwire, invasion of object tracking
    BYTE                bReserved;                                              // Reserved field
    int					nObjectTypeNum;											// Corresponding object type
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no.	0~65535
    int					nLane;													// Lane no. 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm link
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event corresponding period

    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    int                 nDirectionLinPoint;                                     // Normal direction top 
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// Normal direction?ê?first point is starting point?ê?last point is end point

}CFG_TRAFFIC_BACKING_INFO;

// Event type  EVENT_IVS_TRAFFIC_VEHICLEINBUSROUTE(occupy bus lane)corresponding rule config
typedef struct tagCFG_TRAFFIC_VEHICLEINBUSROUTE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// Rule name, different rule cannot be repeated
    bool				bRuleEnable;											// Rule eanble
    BYTE                byCarType;                                              // Snapshot vehicle type?ê?0?êonon-yellow plate 1?êoblue plate 2?êonon-truck
    BYTE                bSensitivity;                                           // Sensitivity?ê?value 1-10?ê?the higher the value the higher the sensitivity
    BYTE                bEnclosure;                                             // e-fence function, 1-open, 0-close
    bool                bTrackEnable;                                           // trigger tracking enable, for tripwire, intrusion object tracking
    int					nObjectTypeNum;											// Corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// Corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no.	0~65535
    int					nLane;													// Lane no. 
    int                 nDetectRegionPoint;                                     // Detection zone top 
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // Detection zone
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// Alarm link
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// Event response period
}CFG_TRAFFIC_VEHICLEINBUSROUTE_INFO;

typedef enum tagCFG_SAFEBELT_SEAT
{
    CSS_UNKNOW ,
    CSS_MAIN_SEAT     ,         //Main driver seat
    CSS_SLAVE_SEAT    ,         //Co-drvier seat
}CFG_SAFEBELT_SEAT;

// Event type EVENT_IVS_TRAFFIC_WITHOUT_SAFEBELT(traffic unfastened seat belt event)corresponding to rule config
typedef struct tagCFG_TRAFFIC_WITHOUT_SAFEBELT
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different rules cannot have same name
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserved text
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding obnect type list
    int                 nPtzPresetId;                                           // PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm link
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event response period

    int                 nLane;                                                  // Lane no.
    int                 nSeatNum;                                               // Get seat number
    CFG_SAFEBELT_SEAT   emSnapSeat[MAX_SEAT_NUM];                               // Driver seat to be snapshoted
}CFG_TRAFFIC_WITHOUT_SAFEBELT;

// Event type EVENT_IVS_GETOUTBEDDETECTION(detention leave bed event)corresponding rule config
typedef struct tagCFG_IVS_GETOUTBEDDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// rule name, different rules cannot have the same name
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];											// reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ presser no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period

    int					nDetectRegionPoint;										// detection zone top number
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// detection zone, polygontype, in polygon each coordinate top point coordinate are within [0,8192) zone
    unsigned int        nMinDuration;                                           // min duration, unit:s
    unsigned int        nReportInterval;										// report time interval, unit :s
    int                 nAssisDectLinePointNum;									// AUX detection line point
    CFG_POLYLINE        stuAssisDectLine[MAX_POLYLINE_NUM];						// AUX detection line
}CFG_IVS_GETOUTBEDDETECTION_INFO;


// Event type EVENT_IVS_PATROLDETECTION (patrol detection event) corresponding rule config
typedef struct tagCFG_IVS_PATROLDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// rule name, different rules cannot have same name
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];                                           // reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no.
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period
    
    int					nDetectRegionPoint;										// warning zone top number
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// warning zone, polygon type, in polygon each top coordinate are within [0,8192) zone
    unsigned int        nMinDuration;                                           // min duration time, unit:s
    unsigned int        nReportInterval;                                        // report time interval, unit:s
    unsigned int        nPatrolTime;											// patrol time, unit:s
	BOOL                bSizeFileter;											// whether rule special dimension filter is valid or not
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // rule special dimension filter
}CFG_IVS_PATROLDETECTION_INFO;

//Event type EVENT_IVS_ONDUTYDETECTION (stand detection event) corresponding rule config
typedef struct tagCFG_IVS_ONDUTYDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// rule name, different rule cannot have same name				
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];                                           // reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period
    
    int					nDetectRegionPoint;										// warning zone top number
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// warning zone, polygon type, in polygon each top coordinate are within [0,8192) zone
    unsigned int        nMinDuration;                                           // min duration time, unit:s
    unsigned int        nReportInterval;										// report time interval, unit:s
    int                 nTemplateRegionPointPairNum;							// template area info point pair number
    CFG_POLYGON         stuTemplateRegion[MAX_TEMPLATEREGION_NUM][POINT_PAIR_NUM];	// template area info, number corresponding template picture number
}CFG_IVS_ONDUTYDETECTION_INFO;

// Event type EVENT_IVS_TRAFFIC_DRIVER_SMOKING(driver smoking event)corresponding to rule config
typedef struct tagCFG_TRAFFIC_DRIVER_SMOKING
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different rule cannot have same name
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserved text
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object type list
    int                 nPtzPresetId;                                           // PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm link
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event response period
    
    int                 nLane;                                                  // Lane no.
}CFG_TRAFFIC_DRIVER_SMOKING;

// Event type EVNET_IVS_TRAFFIC_DRIVER_CALLING(driver call event)corresponding to rule config
typedef struct tagCFG_TRAFFIC_DRIVER_CALLING
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different rules cannot have same name
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserve text
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object tyoe list
    int                 nPtzPresetId;                                           // PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm link
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event responsing period
    
    int                 nLane;                                                  // Lane no.
}CFG_TRAFFIC_DRIVER_CALLING;

// Event type EVENT_IVS_TRAFFIC_PASSNOTINORDER(Pass not in order)corresponding to rule config
typedef struct tagCFG_TRAFFIC_PASSNOTINORDER_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // Rule name, different rules cannot have same name
    bool                bRuleEnable;                                            // Rule enable
    BYTE                bReserved[3];                                           // Reserve text
    int                 nObjectTypeNum;                                         // Corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // Corresponding object tyoe list
    int                 nPtzPresetId;                                           // PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // Alarm link
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // Event responsing period
    
    int                 nLane;                                                  // Lane Number
    int                 nFollowTime;                                            // The threshold value of follow time,it is not illegal when follow time more than this value. unit:millisecond
}CFG_TRAFFIC_PASSNOTINORDER_INFO;

// Event type EVENT_IVS_HEATMAP heat image corresponding rule config
typedef struct tagCFG_IVS_HEATMAP_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// rune name, different rule cannot have same name
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];                                           // reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period
    
    int					nDetectRegionPoint;										// warning zone top number
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// warning zone, polygon type, in polygon each top coordinate are within [0,8192) zone
    BOOL                bSizeFileter;                                           // whether rule special dimension filter is valid or not
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // rule special dimension filter
}CFG_IVS_HEATMAP_INFO;

typedef struct tagCFG_REGION_FILTER
{
    CFG_RECT			stuMaxRect;												// Max region of head 
    CFG_RECT			stuMinRect;												// Min region of head
}CFG_REGION_FILTER;

// event type EVENT_IVS_STANDUPDETECTION (the detecting event of standing up) corresponding to rule config
typedef struct tagCFG_IVS_STANDUPDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// Rule name, different rules cannot have same name
    bool				bRuleEnable;											// rule enable
    BYTE                bReserved[3];                                           // reserved field
    int					nObjectTypeNum;											// corresponding object type number
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// corresponding object type list
    int                 nPtzPresetId;											// PTZ preset no. 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm link
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// event response period
    
    CFG_REGION			stuHumanRegion;											// detect region	
    int					nStandUpDirectionNum;									// standup direction points number
    CFG_POLYLINE		stuStandUpDirection[MAX_POLYLINE_NUM];					// standup direction. first point is starting point, last point is end point
    CFG_REGION_FILTER	stuRegionFilter;										// rule special dimension filter
}CFG_IVS_STANDUPDETECTION_INFO;

// event type EVENT_IVS_VEHICLEANALYSE(the checking event of traffic feature)corresponding to rule config
typedef struct tagCFG_IVS_VEHICLEANALYSE_INFO
{
	char                szRuleName[MAX_NAME_LEN];                               //  Rule name, different rules cannot have same name
    bool                bRuleEnable;                                            // rule enable
	BYTE                bReserved[3];                                           // reserved field
    int                 nObjectTypeNum;                                         // corresponding object type number
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // corresponding object type list
	int                 nPtzPresetId;											// PTZ preset no. 0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;									    // alarm link
	CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];		    // event response period

	int					nDetectRegionPoint;										// warning zone top number
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// warning zone, polygon type, in polygon each top coordinate are within [0,8192) zone
	BOOL                bSizeFileter;                                           // whether rule special dimension filter is valid or not
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // rule special dimension filter
	
} CFG_IVS_VEHICLEANALYSE_INFO;

// rule common info 
typedef struct tagCFG_RULE_COMM_INFO
{
	EM_SCENE_TYPE		emClassType;						// the scene of  rule 
}CFG_RULE_COMM_INFO;

typedef struct tagCFG_RULE_INFO
{
	DWORD				dwRuleType;							// Event type,see "intelligent analyse event type" in dhnetsdk.h 
	int					nRuleSize;							// This envent type rule configuration struct size
	CFG_RULE_COMM_INFO		stuRuleCommInfo;				// the common of the tule
} CFG_RULE_INFO;

// Each video channel respond envent rule: pRuleBuf point to a buffer with multiple event rule info, each event rule info contain CFG_RULE_INFO + stucte of respond rule configuration struct
typedef struct tagCFG_ANALYSERULES_INFO
{
	int					nRuleCount;							// Video analyse rule number
	char*				pRuleBuf;							// Ach video input chennel's rule configuration buffer
	int					nRuleLen;							// Buffer size

} CFG_ANALYSERULES_INFO;

// Video Analysis Resource Type
typedef enum tagCFG_VIDEO_SOURCE_TYPE
{
	CFG_VIDEO_SOURCE_REALSTREAM,                            // Live Stream
	CFG_VIDEO_SOURCE_FILESTREAM,                            // File Stream
}CFG_VIDEO_SOURCE_TYPE;

// Analysis of The Source File Type
typedef enum tagCFG_SOURCE_FILE_TYPE
{
	CFG_SOURCE_FILE_UNKNOWN,                                // Unknown Type
	CFG_SOURCE_FILE_RECORD,                                 // Video Files
	CFG_SOURCE_FILE_PICTURE,                                    // Picture File
}CFG_SOURCE_FILE_TYPE;

// Video Analysis of The Source File Information
typedef struct tagCFG_SOURCE_FILE_INFO
{
	char                szFilePath[MAX_PATH];               // File Path
	CFG_SOURCE_FILE_TYPE emFileType;                        // Refer to CFG_SOURCE_FILE_TYPE File Type for Detail
}CFG_SOURCE_FILE_INFO;

// every video input chennel's video analyse source configuration
typedef struct tagCFG_ANALYSESOURCE_INFO
{
	bool				bEnable;								// Video analyse enable
	BYTE				bReserved[3];							// Reserved
	int					nChannelID;								// Intelligent analyse former video channel number
	int					nStreamType;							// Intelligent analyse former stream type,0:snap; 1:main; 2:sub1; 3:sub2; 4:sub3;(sustain 0)
	char				szRemoteDevice[MAX_NAME_LEN];			// Device name
	BOOL				abDeviceInfo;				        	// Device info is efficiency or not
	AV_CFG_RemoteDevice stuDeviceInfo;					        // Device info
	CFG_VIDEO_SOURCE_TYPE emSourceType;                         // The Source Type of Video Analysis?ê?Refer to CFG_VIDEO_SOURCE_TYPE for Detail
	CFG_SOURCE_FILE_INFO stuSourceFile;                         // Valid When The Source Type of Video Analysis is CFG_VIDEO_SOURCE_FILESTREAM
} CFG_ANALYSESOURCE_INFO;  
//Overall configuration video analysis, the equipment or the server action as a whole
typedef struct tagCFG_ANALYSEWHOLE_INFO
{	
	unsigned  int nVideoChannelType;		// Video channel choose 0:digital,1:simulation,2:mix
	
}CFG_ANALYSEWHOLE_INFO;

typedef struct tagCFG_RAINBRUSH_INFO
{
	bool                bEnable;                                 // Rain brush enable
	BYTE                bSpeedRate;                              // Rain brush speed,1:fast;2:middle;3:slow
	BYTE                bReserved[2];                            // Reserved
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event happening time schedule

}CFG_RAINBRUSH_INFO;

// BreakingSnapTimes
typedef struct tagBREAKINGSNAPTIMES_INFO
{
	int               nNormal;                          // Normal
	int               nRunRedLight;                     // Run redlight
	int			      nOverLine;						// Over line
	int				  nOverYellowLine;			  	    // Over yellow line
	int				  nRetrograde;			    	    // Retrograde
	int				  nUnderSpeed;					    // Under speed
    int				  nOverSpeed;						// Over speed
	int			      nWrongRunningRoute;				// Wrong runing route
	int			      nYellowInRoute;					// Yellow plant in route
	int		    	  nSpecialRetrograde;				// Special retrograde
	int			      nTurnLeft;						// Turn left
	int			      nTurnRight;						// Turn right
	int			      nCrossLane;						// Cross lane
	int			      nU_Turn;						    // U_turn
	int			      nParking;						    //Parking
	int               nWaitingArea;						// Waiting area
	int			      nWrongRoute;					    // Wrong route
	int               nParkingSpaceParking;             // Parking space parkig
	int               nParkingSpaceNoParking;           // Parking space no parking

	int               nRunYellowLight;					// Run the Yellow Light
	int               nStay;							// Illegal Parking
	int               nPedestrainPriority;	            // Crosswalk Pedestrain Priority
	int               nVehicleInBusRoute;               // Illegal Lane Occupation
	int               nBacking;                         // Illegal Back Up
	int				  nOverStopLine;					// Cross Stop Line
	int               nParkingOnYellowBox;           	// Yellow Grid Parking	
	int               nRestrictedPlate;					// Limited Plate	
	int               nNoPassing;						// No Entry	
    int               nWithoutSafeBelt;                 // Unfasten seat belt
    int               nDriverSmoking;                   // Driver smoking
    int               nDriverCalling;                   // Driver call
    int               nPedestrianRunRedLight;           // pedestrian run red light
    int               nPassNotInOrder;                  // pass not in order
}BREAKINGSNAPTIMES_INFO;


//OSD Black Border
typedef struct tagBLACK_REGION_INFO
{
	int nHeight;			//Black border height, range?êo0 ~ ( 8192-original height)
	int nOSDPosition;		//Black border 0=unknown , 1=top , 2=bottom
}BLACK_REGION_INFO;

#define MAX_OSD_CUSTOM_SORT_NUM       8
#define MAX_OSD_CUSTOM_SORT_ELEM_NUM  8
#define MAX_OSD_CUSTOM_GENERAL_NUM    8
#define MAX_OSD_ITEM_ATTR_NUM         8 
#define MAX_PRE_POX_STR_LEN           32
#define MAX_OSD_CUSTOM_NAME_LEN       32
#define MAX_OSD_CUSTOM_VALUE_LEN      256

//All OSD Item Public Property
typedef struct tagOSD_WHOLE_ATTR
{
    BOOL        bPositionAsBlackRegion;     //If position is same with black border ,true?ê?following Position is invalid
    CFG_RECT    stPostion;                  //Position, cannot exceed picture range
    BOOL        bNewLine;                   //Exceed rectangle range, if change line ,bPositionAsBlackRegion is true valid
    BOOL        bLoneVehicle;                //Vehicle info independent display, true one line displays vehicle info,false allows multiple vehicle info display in one line
}OSD_WHOLE_ATTR;

typedef union tagOSD_ATTR_SCHEME
{
    OSD_WHOLE_ATTR stWholeAttr;
}OSD_ATTR_SCHEME;

//OSD Overlay Element
typedef struct tagOSD_CUSTOM_ELEMENT
{
    int  nNameType;                          //Name Type,	0:szName text definition refer to szOSDOrder text definition item
                                             //             1:"Name" text meanscustom item, no analysis
    char szName[MAX_OSD_CUSTOM_VALUE_LEN];                           // Item Name
    char szPrefix[MAX_PRE_POX_STR_LEN];      // Overlay Prefix String	
    char szPostfix[MAX_PRE_POX_STR_LEN];     //Overlay Suffix String
    int  nSeperaterCount;                    //Suffix Add Seperator Quantity
    
}OSD_CUSTOM_ELEMENT;

//OSD Overlay Content Custom Sequence
typedef struct tagOSD_CUSTOM_SORT
{
    OSD_CUSTOM_ELEMENT   stElements[MAX_OSD_CUSTOM_SORT_ELEM_NUM];     //Detail Overlay Element
    int                  nElementNum;
}OSD_CUSTOM_SORT;


typedef struct tagOSD_CUSTOM_GENERAL_INFO
{
    BOOL    bEnable;            // overlay or not
}OSD_CUSTOM_GENERAL_INFO;

//OSD custom option
typedef struct tagOSD_CUSTOM_INFO
{
    OSD_CUSTOM_GENERAL_INFO  stGeneralInfos[MAX_OSD_CUSTOM_GENERAL_NUM];     //Detailed overlay element
    int                      nGeneralInfoNum;
}OSD_CUSTOM_INFO;
#define  MAX_CONF_CHAR 256
//OSD Property
typedef struct tagOSD_INFO
{
	BLACK_REGION_INFO	stBackRegionInfo;		//OSD Black Border Property
	int					nOSDAttrScheme;		    //OSD property , 1=all OSD item public property , 2=each OSD item has one property
	OSD_ATTR_SCHEME		stOSDAttrScheme;		//OSD Property Config Scheme Content
    OSD_CUSTOM_SORT     stOSDCustomSorts[MAX_OSD_CUSTOM_SORT_NUM];    //OSD Overlay Custom Sequence
    int                 nOSDCustomSortNum;
    int                 nRedLightTimeDisplay;   //OSD red light time config 0=unknow,1=violation last ,2=all
    char                cSeperater;             //OSD different item seperator
    BYTE		        bReserved[3];           //Text Align
    char                szOSDOrder[MAX_CONF_CHAR];    
    int                 nOSDContentScheme;      //0=unknown, 1=Mask , 2=CustomizeSort
    OSD_CUSTOM_INFO     stOSDCustomInfo;        //OSD custom option
}OSD_INFO;

// Detector -- BEGIN
// CoilConfig
typedef struct tagCOILCONFIG_INFO
{
	int               nDelayFlashID;                 // Delay flash id, 0~5,0 means not delay any flash 
	int               nFlashSerialNum;               // Flash serial number,0~5,0 means not open the flash
	int               nRedDirection;                 // Red light direction,0-not bonding,1-turn left,2-straight,3-turn right,4-wait left,5-wait straight,6-wait right, 
	int               nTriggerMode ;                 // Trigger mod	0-in 1-out
    int				  nFlashSerialNum2;				 //Snapshot 2nd corresponding to flashlight no. range 0~5?ê?0 means do not open flashlight
    int				  nFlashSerialNum3;				 //Snapshot third corresponding to flashlight no. range 0~5?ê?0 means do not oen flashlight
}COILCONFIG_INFO;

typedef struct tagDETECTOR_INFO
{
	int                nDetectBreaking;                  // Breaking info, low bit to high bit means 0-normal 1-RunRedLight 2-OverLine 3-Retrograde 4-UnderSpeed 5-OverSpeed 6-OverLine 7-YellowPlateInLane
	COILCONFIG_INFO    arstCoilCfg[MAX_COILCONFIG];      // Coil info
	int				   nRoadwayNumber;				     // Road number	0-16 
	int                nRoadwayDirection;                // Road direction	0-south to north 1-west south to east north 2-east 3-west north to east south 4-north to south 5-east north to west south 6-east to west 7-east south to west north 8-ignore
	int                nRedLightCardNum;                 // Gate picture number,0 means not use,1~3,means use this number picture
	int                nCoilsNumber;                     // Coil number	1-3
	int                nOperationType;                   // Operation type 0-gate and electronical police 1-electronical police 2-gate
	int                arnCoilsDistance[3];              // Distance between coils, 0-1000, cm
	int                nCoilsWidth;                      // Coils width 0~200, cm
	int                arnSmallCarSpeedLimit[2];         // Small car speed limit. 0~255km/h
	int				   arnBigCarSpeedLimit[2];           // Big car speed limit. 0~255km/h 
	int				   nOverSpeedMargin;			     // Over speed margin, km/h
	int                nBigCarOverSpeedMargin;           // Big car over speed margin, km/h 
	int				   nUnderSpeedMargin;			     // Under speed margin, km/h
	int                nBigCarUnderSpeedMargin;          // Big car under speed margin, km/h 
	bool               bSpeedLimitForSize;               // Big and small car speed limimt enable
	bool			   bMaskRetrograde;				     // Mask retrograde enable
	BYTE               byReserved[2];                    // Reserved
	char               szDrivingDirection[3][MAX_DRIVINGDIRECTION]; //
													     // DrivingDirection: for example ["Approach", "Shanghai", " Hangzhou"]
													     // "Approach" means driving direction,where the car is more near;"Leave"-means where if mor far to the car
														 // The scend and third param means the location of the driving direction
	int                nOverPercentage;                  // Overspeed  percentage, Snapshot taken when exceed speed limit

	int                nCarScheme;                       // Detailed plan Index. Refer to pack environment local.png for definition. The working area is depending on the string of RAFFICSNAPSHOT_INFO.abSchemeRange.
	int                nSigScheme;                       //Same as above, For none ANPR (Auto Plate Number Recognition)use only
	BOOL               bEnable;                          // The validity of lane, can only capture is valid
	int				   nYellowSpeedLimit[2];			 //Yellow plate max and min speed range 0~255km/h
	int				   nRoadType;						 //Working section 0 normal 1 high way
	int				   nSnapMode;						 //Snapshot mode 0-all snapshot 1-overspeed 2-retrogradation snapshot
    int                nDelayMode;						 //Delay snapshot scheme 0-make DelaySnapshotDistance?ê?1-use DelayTime
	int                nDelayTime;						 //Delay snapshot time run red light 3rd snapshot location distance to last coil time?ê?unit is ms
	int				   nTriggerMode;					 //Trigger mode  0-in coil trigger 1-out coil trigger 2-exit/enter snapshot 3-off
	int			       nErrorRange;						 //Speed error?ê?in coil 2 and in coil 3 speed different?ê?if actual different is greater than this value, then speed is invalid, otherwise use average speed 0-20
	double			   dSpeedCorrection;				 //Speed calibration coefficient?ê?as measured value times this coefficient 
    int                nDirection[2];                    //Corresponding lane directionneed to report vehicle direction,nDirection[0] 0--null 1--right ; nDirection[1] 0--null 1--opposite	
    char               szCustomParkNo[CFG_COMMON_STRING_32 + 1]; // self defined parking space number￡¨for parking￡?
    BYTE               btReserved[3];
}DETECTOR_INFO;
// Detector -- END

typedef struct tagRADAR_INFO
{
    int     nAngle;                 //Angle,used to modify radar angle cuased speed error, range[0,90]
    int     nAntiJammingValue;      //Anti-inteference threshold
    int     nComeInValue;           //Right direction enter threshold, range [0,65535]
    int     nComeOutValue;          //Opposite direction threshold value
    int     nDelayTime;             //Radar delay, unit ms?ê?range [0,255]
    DWORD   nDetectBreaking;        //Violation type mask, from low to high bit as:
                                    //0-normal,1-run the red light, 2-cross line, 3-retrogradation,4-low speed
                                    //5-over speed,6-occupied lane,7-yellow-plate in lane,8-run the yellow light,9-occupied bus lane
    int     nDetectMode;            //Detection mode  0-head detect 1-tail detect 2-dual
    int     nInstallMode;           //Redar installaton  0-side 1-top
    int     nLevel;                 //Sensitivity,0 is highest, range [0,5]
    int     nMultiTargetFilter;     //Multiple target filter mode,0-normal 1-filter
    int     nWentEndValue;          //Opposite direction signal end threshold
    int     nWentInValue;           //Right direction enter threshold
    int     nWentOutValue;          //Opposite direction unlock threshold
}RADAR_INFO;

// CFG_CMD_INTELLECTIVETRAFFIC
typedef struct tagCFG_TRAFFICSNAPSHOT_INFO
{
	char                     szDeviceAddress[MAX_DEVICE_ADDRESS];  // Device address
	DWORD                    nVideoTitleMask;                      // OSD title mask,low bit to high bit means:0-time 1-address 2-plant 3-car lenth 4-car speed 5-speed limit 6-big car speed limit 7-small car speed limit 8-over speed  9-breaking code 10-road number 11-vihicl color 12-plant type 13-plant color 14-red light on time 15-breaking type 16-radar direction 17-device number 18-mature time 19-car type 20-driving direction
	int                      nRedLightMargin;                      // Red light margin, it means run red light will not break rule when in this time, s
	float				     fLongVehicleLengthLevel;              // Long vehicle length level,m
	float					 arfLargeVehicleLengthLevel[2];        // Big vehicle length level, m
	float					 arfMediumVehicleLengthLevel[2];       // Medium vehicle length level, m
	float					 arfSmallVehicleLengthLevel[2];        // Small vehicle length level, m
	float					 fMotoVehicleLengthLevel;              // Moto lenth level, m
	BREAKINGSNAPTIMES_INFO   stBreakingSnapTimes;                  // Breaking snap times
	DETECTOR_INFO            arstDetector[MAX_DETECTOR];           // Detector configuration
	int 					 nCarType;			               	   // Car type, 0-both snap 1-snap small car 2-snap big car 3-both not snap
	int						 nMaxSpeed;			               	   // Max speed, 0~255km/h
	int						 nFrameMode;		               	   // Frame mode	1-speed adaptive 2-depend on eventhandler
	int                      arnAdaptiveSpeed[2];                  // Adaptive speed
	CFG_ALARM_MSG_HANDLE     stuEventHandler;	                   // Snap event handler
	BOOL                     abSchemeRange;                        // True: Scheme for camera, please take the value between vehicle and 0 as standard; False: scheme for lane. Cannot modify the data, internal use only

    DWORD                    nVideoTitleMask1;					   // From low to high means?êo0-mark 1-red light end time 2-device manufacturer  3-small car low speed 4-truck speed limit 5-car max speed 6-truck max speed 7-device working mode 8-general custom 11-parking lot(van, car and etc.) 13-midium car min speed 14-medium car max speed 15-road direction  16-GPS info
    DWORD				     nMergeVideoTitleMask;                 // Combine picture OSD overlay type mask	refer to nVideoTitleMask text
    DWORD				     nMergeVideoTitleMask1;				   // Combine picture OSD overlay type mask	refer to nVideoTitleMask1 text
    int                      nTriggerSource;					   // Trigger source mask code 0-RS232 1-RS485 2-IO 3-Video 4-Net
    int						 nSnapMode;							   // Snapshot mode 0-all 1-over speed 2-retrogradation 3-PK mode
    int                      nWorkMode;							   // Working mode 0-auto?ê?1-coil snapshot?ê?2-coil snapshot recignize?ê?3-video snapshot?ê?4-video recognition, 5-mixed?ê?§with recognition?ê?
    int                      nCarThreShold;						   // Lane threshold  distinguish size lane threshold?ê?unit : cm
    int                      nSnapType;							   // Snapshot or record selection 0-normal snapshot mode 1-video snapshot mode 2-black screen mode
    int                      nCustomFrameInterval[3];			   // Custom snapshot interval first element is speed lower than self-adaptive limit interval of snapshot, and so on 
    int                      nKeepAlive;				           // Alive period withrador, vehicle detector, unit is s
    OSD_INFO				 stOSD;								   // Original picture OSD parameter config
    OSD_INFO                 stMergeOSD;                           // Combine picture OSD parameter config
    CFG_NET_TIME             stValidUntilTime;					   // Mark expirationtime, snaoshot is valid before this time
    RADAR_INFO               stRadar;
    char                     szRoadwayCode[MAX_ROADWAYNO];         // Road code
}CFG_TRAFFICSNAPSHOT_INFO;

typedef struct tagCFG_TRAFFICSNAPSHOT_NEW_INFO
{
	int							nCount;								// Valid members
	CFG_TRAFFICSNAPSHOT_INFO	stInfo[8];							// Traffic snapshot info group
}CFG_TRAFFICSNAPSHOT_NEW_INFO;

//  General configuration(CFG_CMD_DEV_GENERRAL) General 
typedef struct tagCFG_DEV_DISPOSITION_INFO
{
	int                      nLocalNo;              // Device number,0~998
	char                     szMachineName[256];    // Machine name
	char                     szMachineAddress[256]; // Machine instal address,such as road number
	char                     szMachineGroup[256];   // Machine group, it instal as null,
	char					 szMachineID[64];		// The machine serial number exclusive
	
	BYTE		             bReserved[960];       // Reserved
}CFG_DEV_DISPOSITION_INFO;

typedef struct tagOVERSPEED_INFO
{
	int                      nSpeedingPercentage[2];                        // Percentage, these percentages not allow cross, >=0 and -1, -1 means infinite
	char                     szCode[MAX_VIOLATIONCODE];                     // Violation code
	char                     szDescription[MAX_VIOLATIONCODE_DESCRIPT];     // Violation description

}CFG_OVERSPEED_INFO;

typedef CFG_OVERSPEED_INFO CFG_OVERSPEED_HIGHWAY_INFO;
typedef CFG_OVERSPEED_INFO CFG_UNDERSPEED_INFO;

//ViolationCode configuration
typedef struct tagVIOLATIONCODE_INFO
{
    char                szRetrograde[MAX_VIOLATIONCODE];			//Retrograde
	char                szRetrogradeDesc[MAX_VIOLATIONCODE_DESCRIPT];              // Violation code
    char                szRetrogradeShowName[MAX_VIOLATIONCODE_DESCRIPT]; //Display name

	char				szRetrogradeHighway[MAX_VIOLATIONCODE];		// Retrograde - high speed way
	char				szRetrogradeHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];		// Violation code

	char                szRunRedLight[MAX_VIOLATIONCODE];			// Run red light
	char                szRunRedLightDesc[MAX_VIOLATIONCODE_DESCRIPT];			   //Violation code

	char                szCrossLane[MAX_VIOLATIONCODE];				// Cross lane
	char                szCrossLaneDesc[MAX_VIOLATIONCODE_DESCRIPT];			   // Violation code
    char                szCrossLaneShowName[MAX_VIOLATIONCODE_DESCRIPT];    // Violation lane change display name

	char                szTurnLeft[MAX_VIOLATIONCODE];				// Turn left
	char                szTurnLeftDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // Violation code

	char                szTurnRight[MAX_VIOLATIONCODE];				// Turn right
	char                szTurnRightDesc[MAX_VIOLATIONCODE_DESCRIPT];				// Violation code

	char                szU_Turn[MAX_VIOLATIONCODE];				// U_turn
	char                szU_TurnDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // Violation code
    char                szU_TurnShowName[MAX_VIOLATIONCODE_DESCRIPT]; //Display info 

	char                szJam[MAX_VIOLATIONCODE];					// Jam
	char                szJamDesc[MAX_VIOLATIONCODE_DESCRIPT];					   // Violation code

	char                szParking[MAX_VIOLATIONCODE];				// Parking
	char                szParkingDesc[MAX_VIOLATIONCODE_DESCRIPT];			      	// Violation code
    char                szParkingShowName[MAX_VIOLATIONCODE_DESCRIPT];   // Illegal parking display name

	// Only need one between over speed and over speed proportion
	char                szOverSpeed[MAX_VIOLATIONCODE];				// Over speed
	char                szOverSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];				// Violation code
	CFG_OVERSPEED_INFO  stOverSpeedConfig[5];                       // Over speed proportion code

	// Only need one between over speed(high speed way) and over speed proportion(high speed way)
	char                szOverSpeedHighway[MAX_VIOLATIONCODE];		// Over speed(high speed way)
	char                szOverSpeedHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];	      	// Over speed-violation code
	CFG_OVERSPEED_HIGHWAY_INFO stOverSpeedHighwayConfig[5];         // Over speed proportion code

	// Only need one between under speed and under speed proportion
	char                szUnderSpeed[MAX_VIOLATIONCODE];	        // Under speed
	char                szUnderSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];	            // Violation code
	CFG_UNDERSPEED_INFO stUnderSpeedConfig[5];                            // Under speed proportion, diffrent under speed proportion has diffrent violation code

	char                szOverLine[MAX_VIOLATIONCODE];				// Over line
	char                szOverLineDesc[MAX_VIOLATIONCODE_DESCRIPT];			    	// Violation code
    char                szOverLineShowName[MAX_VIOLATIONCODE_DESCRIPT];  //Cross line display name

	char                szOverYellowLine[MAX_VIOLATIONCODE];	    // Over yellow line
	char                szOverYellowLineDesc[MAX_VIOLATIONCODE_DESCRIPT];	    	// Violation code

	char                szYellowInRoute[MAX_VIOLATIONCODE];			// Yellow in route
	char                szYellowInRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];			// Violation code

	char                szWrongRoute[MAX_VIOLATIONCODE];			// Wrong route
	char                szWrongRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];				// Violation code

	char                szDrivingOnShoulder[MAX_VIOLATIONCODE];		// Driving on shoulder
	char                szDrivingOnShoulderDesc[MAX_VIOLATIONCODE_DESCRIPT];		// Violation code

	char                szPassing[MAX_VIOLATIONCODE];               // Normal passing
	char                szPassingDesc[MAX_VIOLATIONCODE_DESCRIPT];               	// Violation code

	char                szNoPassing[MAX_VIOLATIONCODE];             // No passing
	char                szNoPassingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// Violation code

	char                szFakePlate[MAX_VIOLATIONCODE];              // Fake plate
	char                szFakePlateDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// Violation code
	
	char                szParkingSpaceParking[MAX_VIOLATIONCODE];              // Parking space parking 
	char                szParkingSpaceParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// Description information in violation 

	char                szParkingSpaceNoParking[MAX_VIOLATIONCODE];              //Parking space no parking
	char                szParkingSpaceNoParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				//Description information in violation

    char                szWithoutSafeBelt[MAX_VIOLATIONCODE];                       // Unfasten seat belt
    char                szWithoutSafeBeltShowName[MAX_VIOLATIONCODE_DESCRIPT];      //Unfasten seat belt display name
    char                szWithoutSafeBeltDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	         // Unfasten seat belt violation description

    char                szDriverSmoking[MAX_VIOLATIONCODE];                          // Driver smaoking
    char                szDriverSmokingShowName[MAX_VIOLATIONCODE_DESCRIPT];         //Driver smoking display name
    char                szDriverSmokingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	         // Driver smoking with violation description

    char                szDriverCalling[MAX_VIOLATIONCODE];                         // Driver  call
    char                szDriverCallingShowName[MAX_VIOLATIONCODE_DESCRIPT];        //  Driver call display name
    char                szDriverCallingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	        // Driver call violation description

    char                szBacking[MAX_VIOLATIONCODE];                               // violation backing
    char                szBackingShowName[MAX_VIOLATIONCODE_DESCRIPT];	            // violation backing display name
    char                szBackingDesc[MAX_VIOLATIONCODE_DESCRIPT];                  // violation backing description info 
    char                szVehicleInBusRoute[MAX_VIOLATIONCODE];                     // illegal in lane
    char                szVehicleInBusRouteShowName[MAX_VIOLATIONCODE_DESCRIPT];    // illegal in lane display name
    char                szVehicleInBusRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];        // illegal in lane description info

    char                szPedestrianRunRedLight[MAX_VIOLATIONCODE];                     // pedestrian run red light
    char                szPedestrianRunRedLightShowName[MAX_VIOLATIONCODE_DESCRIPT];    // pedestrian run red light display name
    char                szPedestrianRunRedLightDesc[MAX_VIOLATIONCODE_DESCRIPT];        // pedestrian run red light description info

    char                szPassNotInOrder[MAX_VIOLATIONCODE];                            // Pass not in order
    char                szPassNotInOrderShowName[MAX_VIOLATIONCODE_DESCRIPT];           // Pass not in order display name
    char                szPassNotInOrderDesc[MAX_VIOLATIONCODE_DESCRIPT];               // Pass not in order description info

}VIOLATIONCODE_INFO;

// Lane dection type
typedef enum tagEmCheckType
{
    EM_CHECK_TYPE_UNKNOWN,             // Unrecognized detection type
    EM_CHECK_TYPE_PHYSICAL,            // Physical detection 
    EM_CHECK_TYPE_VIDEO,               // Video detection 
}EM_CHECK_TYPE;

typedef struct tagTrafficEventCheckInfo
{
    BOOL                abTrafficGate;                  // Carry ANPR info or not
    EM_CHECK_TYPE       emTrafficGate;                  // ANPR detection type 

    BOOL                abTrafficJunction;              // Carry intersection info 
    EM_CHECK_TYPE       emTrafficJunction;              // Intersection detection type 

    BOOL                abTrafficTollGate;              // Carry new ANPR info or not
    EM_CHECK_TYPE       emTrafficTollGate;              // New ANPR detection type 

    BOOL                abTrafficRunRedLight;           // Carry traffic run the red light info 
    EM_CHECK_TYPE       emTrafficRunRedLight;           // Traffic run the red light detection type 
    
    BOOL                abTrafficRunYellowLight;        // Carry traffic run the yellow light info 
    EM_CHECK_TYPE       emTrafficRunYellowLight;        // Traffic run the yellow light detection type 

    BOOL                abTrafficOverLine;              // Carry traffic cross-line info 
    EM_CHECK_TYPE       emTrafficOverLine;              // Traffic cross-line detection type 

    BOOL                abTrafficOverYellowLine;        // Carry traffic cross yellow line info 
    EM_CHECK_TYPE       emTrafficOverYellowLine;        // Traffic cross yellow line detection type 

    BOOL                abTrafficRetrograde;            // Carry traffic retrogradation info 
    EM_CHECK_TYPE       emTrafficRetrograde;            // Traffic retrograation detection type 

    BOOL                abTrafficTurnLeft;              // Carry traffic violation left turn info 
    EM_CHECK_TYPE       emTrafficTurnLeft;              // Traffic violation left turn detection type 

    BOOL                abTrafficTurnRight;             // Carry traffic violation right turn info 
    EM_CHECK_TYPE       emTrafficTurnRight;             // Traffic intersection violation right turn type 

    BOOL                abTrafficU_Turn;                // Carry traffic violation u-turn info 
    EM_CHECK_TYPE       emTrafficU_Turn;                // Traffic violation u-turn  detection type 

    BOOL                abTrafficCrossLane;             // Carry traffic violation change lane info 
    EM_CHECK_TYPE       emTrafficCrossLane;             // Traffic violation change lane detection type 

    BOOL                abTrafficParking;               // Carry traffic violation parking info 
    EM_CHECK_TYPE       emTrafficParking;               // Traffic violation parking detection type 

    BOOL                abTrafficJam;                   // Carry traffic jam info 
    EM_CHECK_TYPE       emTrafficJam;                   // Traffic jam detection type 

    BOOL                abTrafficIdle;                  // Carry traffic  idle info 
    EM_CHECK_TYPE       emTrafficIdle;                  // Traffic  idle detection type 

    BOOL                abTrafficWaitingArea;           // Carry traffic violation waiting zone info 
    EM_CHECK_TYPE       emTrafficWaitingArea;           // Traffic violation enter waiting detection type 

    BOOL                abTrafficUnderSpeed;            // Carry traffic under speed info 
    EM_CHECK_TYPE       emTrafficUnderSpeed;            // Traffic under speed detection type 

    BOOL                abTrafficOverSpeed;             // Carry traffic over speed info 
    EM_CHECK_TYPE       emTrafficOverSpeed;             // Traffic over speed  detection type 

    BOOL                abTrafficWrongRoute;            // Carry traffic driving not by lane info 
    EM_CHECK_TYPE       emTrafficWrongRoute;            // Traffic driving not by lane detection type 

    BOOL                abTrafficYellowInRoute;         // Carry traffic yellow-plate in lane info 
    EM_CHECK_TYPE       emTrafficYellowInRoute;         // Traffic yellow-plate in lane detection type 

    BOOL                abTrafficVehicleInRoute;        // Carry traffic car in lane info 
    EM_CHECK_TYPE       emTrafficVehicleInRoute;        // Traffic car in lane detection type 

    BOOL                abTrafficControl;               // Carry traffic control info 
    EM_CHECK_TYPE       emTrafficControl;               // Traffic control detection type 

    BOOL                abTrafficObjectAlarm;           // Carry traffic specific type snapshot info 
    EM_CHECK_TYPE       emTrafficObjectAlarm;           // Traffic specific type snapshot detection type 

    BOOL                abTrafficAccident;              // Carry traffic accident info 
    EM_CHECK_TYPE       emTrafficAccident;              // Traffic accident detection type 

    BOOL                abTrafficStay;                  // Carry traffic stay/retention info 
    EM_CHECK_TYPE       emTrafficStay;                  // Traffic stay/retention detection type 

    BOOL                abTrafficPedestrainPriority;    // Carry traffic crosswalk pedestrian first info 
    EM_CHECK_TYPE       emTrafficPedestrainPriority;    // Traffic crosswalk pedestrian first detection type 

    BOOL                abTrafficPedestrain;            // Carry traffic pedestrian event info 
    EM_CHECK_TYPE       emTrafficPedestrain;            // Traffic pedestrian event detection type 

    BOOL                abTrafficThrow;                 // Carry traffic drop object event info 
    EM_CHECK_TYPE       emTrafficThrow;                 // Traffic drop pbject event detection type 

    BOOL                abTrafficVehicleInBusRoute;     // Carry traffic violation occupied lane info 
    EM_CHECK_TYPE       emTrafficVehicleInBusRoute;     // Traffic violation occupied lane detection type 

    BOOL                abTrafficBacking;               // Carry traffic violation back up info 
    EM_CHECK_TYPE       emTrafficBacking;               // Traffic violation back up detection type 

    BOOL                abTrafficOverStopLine;          // Carry traffic cross stop line info 
    EM_CHECK_TYPE       emTrafficOverStopLine;          // Traffic cross stop line detection type 

    BOOL                abTrafficParkingOnYellowBox;    // Carry traffic yellow grid snapshpt info 
    EM_CHECK_TYPE       emTrafficParkingOnYellowBox;    // Traffic yellow grid snapshot detection type 

    BOOL                abTrafficParkingSpaceParking;   // Carry traffic car in parking info 
    EM_CHECK_TYPE       emTrafficParkingSpaceParking;   // Traffic car in parking detection type 

    BOOL                abTrafficParkingSpaceNoParking; // Carry traffic no car parking info 
    EM_CHECK_TYPE       emTrafficParkingSpaceNoParking; // Traffic no card parking detection type 

    BOOL                abTrafficParkingSpaceOverLine;  // Carry traffic  car cross line info 
    EM_CHECK_TYPE       emTrafficParkingSpaceOverLine;  // Traffic  car cross line detection type 

    BOOL                abParkingSpaceDetection;        // Carry traffic multi-parking status detection info 
    EM_CHECK_TYPE       emParkingSpaceDetection;        // Traffic multi-parking status detection type 

    BOOL                abTrafficRestrictedPlate;       // Carry traffic limit plate info 
    EM_CHECK_TYPE       emTrafficRestrictedPlate;       // Traffic limit plate detection type 

    BOOL                abTrafficWithoutSafeBelt;       // Carry traffic unfasten seat belt info 
    EM_CHECK_TYPE       emTrafficWithoutSafeBelt;       // Traffic unfasten seat belt detection type 

    BOOL                abTrafficNoPassing;             // Carry traffic closed info 
    EM_CHECK_TYPE       emTrafficNoPassing;             // Traffic closed detection type 

    BOOL                abVehicleAnalyse;               // Carry traffic vehicle feature detection analysis info 
    EM_CHECK_TYPE       emVehicleAnalyse;               // Traffic vehicle feature detection type 

    BOOL                abCrossLineDetection;           // Carry traffic warning line info 
    EM_CHECK_TYPE       emCrossLineDetection;           // Traffic warning line detection type 

    BOOL                abCrossFenceDetection;          // Carry traffic perimeter protection info 
    EM_CHECK_TYPE       emCrossFenceDetection;          // Traffic perimeter protection detection type 

    BOOL                abCrossRegionDetection;         // Carry traffic warning zone info 
    EM_CHECK_TYPE       emCrossRegionDetection;         // Traffic warning zone detection type 

    BOOL                abPasteDetection;               // Carry traffic ATM stripe info 
    EM_CHECK_TYPE       emPasteDetection;               // Traffic ATM stripe detection type 

    BOOL                abLeftDetection;                // Carry traffic abandoned object info 
    EM_CHECK_TYPE       emLeftDetection;                // Traffic abandoned object detection type 

    BOOL                abPreservation;                 // Carry traffic object protection info 
    EM_CHECK_TYPE       emPreservation;                 // Traffic object protection detection type 

    BOOL                abTakenAwayDetection;           // Carry traffic missing object detection info 
    EM_CHECK_TYPE       emTakenAwayDetection;           // Traffic missing object detection detection type 

    BOOL                abStayDetection;                // Carry traffic stay/retention info 
    EM_CHECK_TYPE       emStayDetection;                // Traffic stay/retention detection type 

    BOOL                abParkingDetection;             // Carry traffic illegal parking info 
    EM_CHECK_TYPE       emParkingDetection;             // Traffic illegal parking detection type 

    BOOL                abWanderDetection;              // Carry traffic loitering info 
    EM_CHECK_TYPE       emWanderDetection;              // Traffic loitering detection type 

    BOOL                abMoveDetection;                // Carry traffic moving info 
    EM_CHECK_TYPE       emMoveDetection;                // Traffic moving detection type 

    BOOL                abTailDetection;                // Carry traffic trailing info 
    EM_CHECK_TYPE       emTailDetection;                // Traffic trailing detection type 

    BOOL                abRioterDetection;              // Carry traffic focus info 
    EM_CHECK_TYPE       emRioterDetection;              // Traffic focus detection type 

    BOOL                abFightDetection;               // Carry traffic fight info 
    EM_CHECK_TYPE       emFightDetection;               // Traffic fight detection type 

    BOOL                abRetrogradeDetection;          // Carry traffic retrogradation info 
    EM_CHECK_TYPE       emRetrogradeDetection;          // Traffic retrogradation detection type 

    BOOL                abFireDetection;                // Carry traffic fire info 
    EM_CHECK_TYPE       emFireDetection;                // Traffic fire detection type 

    BOOL                abSmokeDetection;               // Carry traffic smog info 
    EM_CHECK_TYPE       emSmokeDetection;               // Traffic smog detection type 

    BOOL                abNumberStat;                   // Carry traffic quantity statistics  info 
    EM_CHECK_TYPE       emNumberStat;                   // Traffic quantity statistics detection type 

    BOOL                abVideoAbnormalDetection;       // Carry traffic abnormal video info 
    EM_CHECK_TYPE       emVideoAbnormalDetection;       // Traffic abnormal video detection type 

    BOOL                abPrisonerRiseDetection;        // Carry prisoner rise detection info 
    EM_CHECK_TYPE       emPrisonerRiseDetection;        // Prisoner rise detection detection type 

    BOOL                abFaceDetection;                // Carry face detection info 
    EM_CHECK_TYPE       emFaceDetection;                // Face detection type 

    BOOL                abFaceRecognition;              // Carry face recognition info 
    EM_CHECK_TYPE       emFaceRecognition;              // Face recognition detection type 

    BOOL                abDensityDetection;             // Carry intensity detection info 
    EM_CHECK_TYPE       emDensityDetection;             // Intensity detection detection type 

    BOOL                abQueueDetection;               // Carry line detection info 
    EM_CHECK_TYPE       emQueueDetection;               // Line detection type 

    BOOL                abClimbDetection;               // Carry climbing detection info 
    EM_CHECK_TYPE       emClimbDetection;               // Climbing detection type 

    BOOL                abLeaveDetection;               // Carry off-duty detection info 
    EM_CHECK_TYPE       emLeaveDetection;               // Off-duty detection type 

    BOOL                abVehicleOnPoliceCar;           // Carry mobile police info 
    EM_CHECK_TYPE       emVehicleOnPoliceCar;           // Mobile police detection type 

    BOOL                abVehicleOnBus;                 // Carry mobile bus info 
    EM_CHECK_TYPE       emVehicleOnBus;                 // Mobile bus detection type 

    BOOL                abVehicleOnSchoolBus;           // Carry Mobile school bus info 
    EM_CHECK_TYPE       emVehicleOnSchoolBus;           // Mobile school bus detection type   

    BOOL				abStandUpDetection;				// Carry stand up detection info
    EM_CHECK_TYPE		emStandUpDetection;				// Stand up detection type

}TRAFFIC_EVENT_CHECK_INFO;  

typedef struct tagTrafficEventCheckMask
{
    BOOL                abTrafficGate;                  // Carry traffic ANPR info 
    int                 nTrafficGate;                   // Traffic ANPR detection mode mask

    BOOL                abTrafficJunction;              // Carry traffic intersection info 
    int                 nTrafficJunction;               // Traffic intersection detection mode mask

    BOOL                abTrafficTollGate;              // Carry new traffic ANPR info 
    int                 nTrafficTollGate;               // New traffic ANPR detection mode mask

    BOOL                abTrafficRunRedLight;           // Carry traffic run the red light info 
    int                 nTrafficRunRedLight;            // Traffic run the red light detection mode mask
    
    BOOL                abTrafficRunYellowLight;        // Carry traffic run the yellow light  info 
    int                 nTrafficRunYellowLight;         // Traffic  run the yellow light  detection mode mask

    BOOL                abTrafficOverLine;              // Carry traffic cross line info 
    int                 nTrafficOverLine;               // Traffic cross line Detection mode mask

    BOOL                abTrafficOverYellowLine;        // Carry traffic cross yellow line info 
    int                 nTrafficOverYellowLine;         // Traffic cross yellow line detection mode mask

    BOOL                abTrafficRetrograde;            // Carry traffic retrogradation info 
    int                 nTrafficRetrograde;             // Traffic retrogradation detection mode mask

    BOOL                abTrafficTurnLeft;              // Carry traffic violation left turn info 
    int                 nTrafficTurnLeft;               // Traffic violation left turn detection mode mask

    BOOL                abTrafficTurnRight;             // Carry traffic violation right turn info 
    int                 nTrafficTurnRight;              // Traffic intersection violation right turn type 

    BOOL                abTrafficU_Turn;                // Carry traffic violation u-turn info 
    int                 nTrafficU_Turn;                 // Traffic violation u-turn detection mode mask

    BOOL                abTrafficCrossLane;             // Carry traffic violation change lane info 
    int                 nTrafficCrossLane;              // Traffic violation change lane detection mode mask

    BOOL                abTrafficParking;               // Carry traffic violation parking info 
    int                 nTrafficParking;                // Traffic violation parking detection mode mask

    BOOL                abTrafficJam;                   // Carry traffic jam info 
    int                 nTrafficJam;                    // Traffic jam detection mode mask

    BOOL                abTrafficIdle;                  // Carry traffic idle info 
    int                 nTrafficIdle;                   // Traffic idle detection mode mask

    BOOL                abTrafficWaitingArea;           // Carry traffic violation enter waiting zone info 
    int                 nTrafficWaitingArea;            // Traffic violation enter waiting zone detection mode mask

    BOOL                abTrafficUnderSpeed;            // Carry traffic below speed info 
    int                 nTrafficUnderSpeed;             // Traffic below speed detection mode mask

    BOOL                abTrafficOverSpeed;             // Carry traffic over speed info 
    int                 nTrafficOverSpeed;              // Traffic over speed detection mode mask

    BOOL                abTrafficWrongRoute;            // Carry traffic driving not by lane  info 
    int                 nTrafficWrongRoute;             // Traffic driving not by lane  detection mode mask

    BOOL                abTrafficYellowInRoute;         // Carry traffic yellow-plate in lane  info 
    int                 nTrafficYellowInRoute;          // Traffic yellow-plate in lane  detection mode mask

    BOOL                abTrafficVehicleInRoute;        // Carry traffic car in lane info 
    int                 nTrafficVehicleInRoute;         // Traffic car in lane detection mode mask

    BOOL                abTrafficControl;               // Carry traffic control info 
    int                 nTrafficControl;                // Traffic control detection mode mask

    BOOL                abTrafficObjectAlarm;           // Carry traffic specific type snapshot info 
    int                 nTrafficObjectAlarm;            // Traffic specific type snapshot detection mode mask

    BOOL                abTrafficAccident;              // Carry traffic accident info 
    int                 nTrafficAccident;               // Traffic accident detection mode mask

    BOOL                abTrafficStay;                  // Carry traffic stay/retention info 
    int                 nTrafficStay;                   // Traffic stay/retention detection mode mask

    BOOL                abTrafficPedestrainPriority;    // Carry traffic crosswalk pedestrian first info 
    int                 nTrafficPedestrainPriority;     // Traffic crosswalk pedestrian first detection mode mask

    BOOL                abTrafficPedestrain;            // Carry traffic pedestrian event info 
    int                 nTrafficPedestrain;             // Traffic pedestrian event detection mode mask

    BOOL                abTrafficThrow;                 // Carry traffic drop object event info 
    int                 nTrafficThrow;                  // Traffic  drop object event detection mode mask

    BOOL                abTrafficVehicleInBusRoute;     // Carry traffic violation in lane info 
    int                 nTrafficVehicleInBusRoute;      // Traffic violation in lane detection mode mask

    BOOL                abTrafficBacking;               // Carry traffic violation back up info 
    int                 nTrafficBacking;                // Traffic violation back up detection mode mask

    BOOL                abTrafficOverStopLine;          // Carry traffic cross stop line info 
    int                 nTrafficOverStopLine;           // Traffic cross stop line detection mode mask

    BOOL                abTrafficParkingOnYellowBox;    // Carry traffic yellow grid snapshot info 
    int                 nTrafficParkingOnYellowBox;     // Traffic yellow grid snapshot detection mode mask

    BOOL                abTrafficParkingSpaceParking;   // Carry traffic car in parking info 
    int                 nTrafficParkingSpaceParking;    // Traffic car in parking detection mode mask

    BOOL                abTrafficParkingSpaceNoParking; // Carry traffic no card in parking info 
    int                 nTrafficParkingSpaceNoParking;  // Traffic no card in parking detection mode mask

    BOOL                abTrafficParkingSpaceOverLine;  // Carry traffic  car cross line info 
    int                 nTrafficParkingSpaceOverLine;   // Traffic  car cross line detection mode mask

    BOOL                abParkingSpaceDetection;        // Carry traffic multi-parking status detection info 
    int                 nParkingSpaceDetection;         // Traffic multi-parking status detection  mode mask

    BOOL                abTrafficRestrictedPlate;       // Carry traffic limit plate info 
    int                 nTrafficRestrictedPlate;        // Traffic limit plate detection mode mask

    BOOL                abTrafficWithoutSafeBelt;       // Carry traffic unfasten seat belt info 
    int                 nTrafficWithoutSafeBelt;        // Traffic unfasten seat belt detection mode mask

    BOOL                abTrafficNoPassing;             // Carry traffic closed info 
    int                 nTrafficNoPassing;              // Traffic closed detection mode mask

    BOOL                abVehicleAnalyse;               // Carry traffic vehicle feature detection analysis info 
    int                 nVehicleAnalyse;                // Traffic vehicle feature detection mode mask

    BOOL                abCrossLineDetection;           // Carry traffic warning line info 
    int                 nCrossLineDetection;            // Traffic warning line detection mode mask

    BOOL                abCrossFenceDetection;          // Carry traffic perimeter protection info 
    int                 nCrossFenceDetection;           // Traffic perimeter protection detection mode mask

    BOOL                abCrossRegionDetection;         // Carry traffic warning zone info 
    int                 nCrossRegionDetection;          // Traffic warning zone detection mode mask

    BOOL                abPasteDetection;               // Carry traffic ATM stripe info 
    int                 nPasteDetection;                // Traffic ATM stripe detection mode mask

    BOOL                abLeftDetection;                // Carry traffic abandoned object info 
    int                 nLeftDetection;                 // Traffic abandoned object detection mode mask

    BOOL                abPreservation;                 // Carry traffic object protection info 
    int                 nPreservation;                  // Traffic object protection detection mode mask

    BOOL                abTakenAwayDetection;           // Carry traffic missing object detection info 
    int                 nTakenAwayDetection;            // Traffic missing object detection detection mode mask

    BOOL                abStayDetection;                // Carry traffic stay/retention info 
    int                 nStayDetection;                 // Traffic stay/retention detection mode mask

    BOOL                abParkingDetection;             // Carry traffic illegal parking info 
    int                 nParkingDetection;              // Traffic illegal parking detection mode mask

    BOOL                abWanderDetection;              // Carry traffic loitering info 
    int                 nWanderDetection;               // Traffic loitering detection mode mask

    BOOL                abMoveDetection;                // Carry traffic moving info 
    int                 nMoveDetection;                 // Traffic moving detection mode mask

    BOOL                abTailDetection;                // Carry traffic trailing info 
    int                 nTailDetection;                 // Traffic trailing detection mode mask

    BOOL                abRioterDetection;              // Carry traffic focus info 
    int                 nRioterDetection;               // Traffic focus detection mode mask

    BOOL                abFightDetection;               // Carry traffic fight info 
    int                 nFightDetection;                // Traffic fight detection mode mask

    BOOL                abRetrogradeDetection;          // Carry traffic retrogradation info 
    int                 nRetrogradeDetection;           // Traffic retrogradation detection mode mask

    BOOL                abFireDetection;                // Carry traffic fire info 
    int                 nFireDetection;                 // Traffic fire detection mode mask

    BOOL                abSmokeDetection;               // Carry traffic smog info 
    int                 nSmokeDetection;                // Traffic smog detection mode mask

    BOOL                abNumberStat;                   // Carry traffic quantity statistics  info 
    int                 nNumberStat;                    // Traffic quantity statistics  detection mode mask

    BOOL                abVideoAbnormalDetection;       // Carry traffic abnormal video info 
    int                 nVideoAbnormalDetection;        // Traffic abnormal video detection mode mask

    BOOL                abPrisonerRiseDetection;        // Carry  prisoner rise detection  info 
    int                 nPrisonerRiseDetection;         //  Prisoner rise detection  detection mode mask

    BOOL                abFaceDetection;                // Carry face detection  info 
    int                 nFaceDetection;                 // Face detection  detection mode mask

    BOOL                abFaceRecognition;              // Carry face recognition info 
    int                 nFaceRecognition;               // Face recognition detection mode mask

    BOOL                abDensityDetection;             // Carry  intensity  detection  info 
    int                 nDensityDetection;              //  Intensity  detection  detection mode mask

    BOOL                abQueueDetection;               // Carry line detection info 
    int                 nQueueDetection;                // Line detection  mode mask

    BOOL                abClimbDetection;               // Carry climbing detection  info 
    int                 nClimbDetection;                // Climbing detection mode mask

    BOOL                abLeaveDetection;               // Carry off-duty detection  info 
    int                 nLeaveDetection;                // Off-duty detection mode mask

    BOOL                abVehicleOnPoliceCar;           // Carry mobile police car info 
    int                 nVehicleOnPoliceCar;            // Mobile police car detection mode mask

    BOOL                abVehicleOnBus;                 // Carry Mobile bus info 
    int                 nVehicleOnBus;                  // Mobile bus detection mode mask

    BOOL                abVehicleOnSchoolBus;           // Carry Mobile school bus info 
    int                 nVehicleOnSchoolBus;            // Mobile school bus detection mode mask  

}TRAFFIC_EVENT_CHECK_MASK;  

// Violation snapshot time config chart
typedef struct tagTimeScheduleInfo
{
    BOOL                bEnable;                                              // Enable time chart or not
    CFG_TIME_SECTION    stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];         // Time chart
}TIME_SCHEDULE_INFO;

// Violation snapshot custom time config
typedef struct tagViolationTimeSchedule
{
    BOOL                abTrafficGate;                  // Carry traffic ANPR info 
    TIME_SCHEDULE_INFO  stTrafficGate;                  // Traffic ANPR time config 

    BOOL                abTrafficJunction;              // Carry traffic intersection info 
    TIME_SCHEDULE_INFO  stTrafficJunction;              // Traffic intersection time config 

    BOOL                abTrafficTollGate;              // Carry new traffic ANPR info 
    TIME_SCHEDULE_INFO  stTrafficTollGate;              // New traffic ANPR time config 

    BOOL                abTrafficRunRedLight;           // Carry traffic run the red light info 
    TIME_SCHEDULE_INFO  stTrafficRunRedLight;           // Traffic run the red light time config 
    
    BOOL                abTrafficRunYellowLight;        // Carry traffic  run the yellow light  info 
    TIME_SCHEDULE_INFO  stTrafficRunYellowLight;        // Traffic  run the yellow light  time config 

    BOOL                abTrafficOverLine;              // Carry traffic cross line info 
    TIME_SCHEDULE_INFO  stTrafficOverLine;              // Traffic cross line time config 

    BOOL                abTrafficOverYellowLine;        // Carry traffic cross yellow line info 
    TIME_SCHEDULE_INFO  stTrafficOverYellowLine;        // Traffic cross yellow line time config 

    BOOL                abTrafficRetrograde;            // Carry traffic retrogradation info 
    TIME_SCHEDULE_INFO  stTrafficRetrograde;            // Traffic retrogradation time config 

    BOOL                abTrafficTurnLeft;              // Carry traffic violation left turn info 
    TIME_SCHEDULE_INFO  stTrafficTurnLeft;              // Traffic violation left turn time config 

    BOOL                abTrafficTurnRight;             // Carry traffic violation right turn info 
    TIME_SCHEDULE_INFO  stTrafficTurnRight;             // Traffic intersectionviolation right turntype 

    BOOL                abTrafficU_Turn;                // Carry traffic violation u-turn info 
    TIME_SCHEDULE_INFO  stTrafficU_Turn;                // Traffic violation u-turn time config 

    BOOL                abTrafficCrossLane;             // Carry traffic violation change lane info 
    TIME_SCHEDULE_INFO  stTrafficCrossLane;             // Traffic violation change lane time config 

    BOOL                abTrafficParking;               // Carry traffic violation parking info 
    TIME_SCHEDULE_INFO  stTrafficParking;               // Traffic violation parking time config 

    BOOL                abTrafficJam;                   // Carry traffic jam info 
    TIME_SCHEDULE_INFO  stTrafficJam;                   // Traffic jam time config 

    BOOL                abTrafficIdle;                  // Carry traffic  idle info 
    TIME_SCHEDULE_INFO  stTrafficIdle;                  // Traffic  idle time config 

    BOOL                abTrafficWaitingArea;           // Carry traffic violation enter waiting zone info 
    TIME_SCHEDULE_INFO  stTrafficWaitingArea;           // Traffic violation enter waiting zone time config 

    BOOL                abTrafficUnderSpeed;            // Carry traffic below speed info 
    TIME_SCHEDULE_INFO  stTrafficUnderSpeed;            // Traffic below speed time config 

    BOOL                abTrafficOverSpeed;             // Carry traffic over speed info 
    TIME_SCHEDULE_INFO  stTrafficOverSpeed;             // Traffic over speed time config 

    BOOL                abTrafficWrongRoute;            // Carry traffic driving not by lane  info 
    TIME_SCHEDULE_INFO  stTrafficWrongRoute;            // Traffic driving not by lane  time config 

    BOOL                abTrafficYellowInRoute;         // Carry traffic yellow-plate in lane  info 
    TIME_SCHEDULE_INFO  stTrafficYellowInRoute;         // Traffic yellow-plate in lane  time config 

    BOOL                abTrafficVehicleInRoute;        // Carry traffic car in lane info 
    TIME_SCHEDULE_INFO  stTrafficVehicleInRoute;        // Traffic car in lane time config 

    BOOL                abTrafficControl;               // Carry traffic  control info 
    TIME_SCHEDULE_INFO  stTrafficControl;               // Traffic  control time config 

    BOOL                abTrafficObjectAlarm;           // Carry traffic specific type snapshot info 
    TIME_SCHEDULE_INFO  stTrafficObjectAlarm;           // Traffic specific type snapshot time config 

    BOOL                abTrafficAccident;              // Carry traffic  accident info 
    TIME_SCHEDULE_INFO  stTrafficAccident;              // Traffic  accident time config 

    BOOL                abTrafficStay;                  // Carry traffic  stay/retention info 
    TIME_SCHEDULE_INFO  stTrafficStay;                  // Traffic  stay/retention time config 

    BOOL                abTrafficPedestrainPriority;    // Carry traffic crosswalk pedestrian first info 
    TIME_SCHEDULE_INFO  stTrafficPedestrainPriority;    // Traffic crosswalk pedestrian first time config 

    BOOL                abTrafficPedestrain;            // Carry traffic  pedestrian event info 
    TIME_SCHEDULE_INFO  stTrafficPedestrain;            // Traffic  pedestrian event time config 

    BOOL                abTrafficThrow;                 // Carry traffic  drop object event info 
    TIME_SCHEDULE_INFO  stTrafficThrow;                 // Traffic  drop object event time config 

    BOOL                abTrafficVehicleInBusRoute;     // Carry traffic violation in lane info 
    TIME_SCHEDULE_INFO  stTrafficVehicleInBusRoute;     // Traffic violation in lane time config 

    BOOL                abTrafficBacking;               // Carry traffic violation back up info 
    TIME_SCHEDULE_INFO  stTrafficBacking;               // Traffic violation back up time config 

    BOOL                abTrafficOverStopLine;          // Carry traffic cross stop line info 
    TIME_SCHEDULE_INFO  stTrafficOverStopLine;          // Traffic cross stop line time config 

    BOOL                abTrafficParkingOnYellowBox;    // Carry traffic yellow grid snapshot info 
    TIME_SCHEDULE_INFO  stTrafficParkingOnYellowBox;    // Traffic yellow grid snapshot time config 

    BOOL                abTrafficParkingSpaceParking;   // Carry traffic car in parking info 
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceParking;   // Traffic car in parking time config 

    BOOL                abTrafficParkingSpaceNoParking; // Carry traffic no card in parking info 
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceNoParking; // Traffic no card in parking time config 

    BOOL                abTrafficParkingSpaceOverLine;  // Carry traffic  car cross line info 
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceOverLine;  // Traffic car in parkingcross line time config 

    BOOL                abParkingSpaceDetection;        // Carry traffic multi-parking status detection  info 
    TIME_SCHEDULE_INFO  stParkingSpaceDetection;        // Traffic multi-parking status detection  time config 

    BOOL                abTrafficRestrictedPlate;       // Carry traffic limit plate info 
    TIME_SCHEDULE_INFO  stTrafficRestrictedPlate;       // Traffic limit plate time config 

    BOOL                abTrafficWithoutSafeBelt;       // Carry traffic unfasten seat belt info 
    TIME_SCHEDULE_INFO  stTrafficWithoutSafeBelt;       // Traffic unfasten seat belt time config 

    BOOL                abTrafficNoPassing;             // Carry traffic closed info 
    TIME_SCHEDULE_INFO  stTrafficNoPassing;             // Traffic closed time config 

    BOOL                abVehicleAnalyse;               // Carry traffic vehicle feature detection analysis info 
    TIME_SCHEDULE_INFO  stVehicleAnalyse;               // Traffic vehicle feature time config 

    BOOL                abCrossLineDetection;           // Carry traffic warning line info 
    TIME_SCHEDULE_INFO  stCrossLineDetection;           // Traffic warning line time config 

    BOOL                abCrossFenceDetection;          // Carry traffic perimeter protection info 
    TIME_SCHEDULE_INFO  stCrossFenceDetection;          // Traffic perimeter protection time config 

    BOOL                abCrossRegionDetection;         // Carry traffic warning zone info 
    TIME_SCHEDULE_INFO  stCrossRegionDetection;         // Traffic warning zone time config 

    BOOL                abPasteDetection;               // Carry traffic ATM stripe info 
    TIME_SCHEDULE_INFO  stPasteDetection;               // Traffic ATM stripe time config 

    BOOL                abLeftDetection;                // Carry traffic abandoned object info 
    TIME_SCHEDULE_INFO  stLeftDetection;                // Traffic abandoned object time config 

    BOOL                abPreservation;                 // Carry traffic object protection info 
    TIME_SCHEDULE_INFO  stPreservation;                 // Traffic object protection time config 

    BOOL                abTakenAwayDetection;           // Carry traffic missing object detection info 
    TIME_SCHEDULE_INFO  stTakenAwayDetection;           // Traffic missing object detection time config 

    BOOL                abStayDetection;                // Carry traffic stay/retention info 
    TIME_SCHEDULE_INFO  stStayDetection;                // Traffic stay/retention time config 

    BOOL                abParkingDetection;             // Carry traffic illegal parking info 
    TIME_SCHEDULE_INFO  stParkingDetection;             // Traffic illegal parking time config 

    BOOL                abWanderDetection;              // Carry traffic loitering info 
    TIME_SCHEDULE_INFO  stWanderDetection;              // Traffic loitering time config 

    BOOL                abMoveDetection;                // Carry traffic moving info 
    TIME_SCHEDULE_INFO  stMoveDetection;                // Traffic moving time config 

    BOOL                abTailDetection;                // Carry traffic trailing info 
    TIME_SCHEDULE_INFO  stTailDetection;                // Traffic trailing time config 

    BOOL                abRioterDetection;              // Carry traffic focus info 
    TIME_SCHEDULE_INFO  stRioterDetection;              // Traffic focus time config 

    BOOL                abFightDetection;               // Carry traffic fight info 
    TIME_SCHEDULE_INFO  stFightDetection;               // Traffic fight time config 

    BOOL                abRetrogradeDetection;          // Carry traffic retrogradation info 
    TIME_SCHEDULE_INFO  stRetrogradeDetection;          // Traffic retrogradation time config 

    BOOL                abFireDetection;                // Carry traffic fire info 
    TIME_SCHEDULE_INFO  stFireDetection;                // Traffic fire time config 

    BOOL                abSmokeDetection;               // Carry traffic smog info 
    TIME_SCHEDULE_INFO  stSmokeDetection;               // Traffic smog time config 

    BOOL                abNumberStat;                   // Carry traffic quantity statistics  info 
    TIME_SCHEDULE_INFO  stNumberStat;                   // Traffic quantity statistics  time config 

    BOOL                abVideoAbnormalDetection;       // Carry traffic abnormal video info 
    TIME_SCHEDULE_INFO  stVideoAbnormalDetection;       // Traffic abnormal video time config 

    BOOL                abPrisonerRiseDetection;        // Carry  prisoner rise detection  info 
    TIME_SCHEDULE_INFO  stPrisonerRiseDetection;        //  Prisoner rise detection  time config 

    BOOL                abFaceDetection;                // Carry face detection  info 
    TIME_SCHEDULE_INFO  stFaceDetection;                // Face detection  time config 

    BOOL                abFaceRecognition;              // Carry face recognition info 
    TIME_SCHEDULE_INFO  stFaceRecognition;              // Face recognition time config 

    BOOL                abDensityDetection;             // Carry  intensity  detection  info 
    TIME_SCHEDULE_INFO  stDensityDetection;             //  Intensity  detection  time config 

    BOOL                abQueueDetection;               // Carry line detection  info 
    TIME_SCHEDULE_INFO  stQueueDetection;               // Line detection  time config 

    BOOL                abClimbDetection;               // Carry climbing detection  info 
    TIME_SCHEDULE_INFO  stClimbDetection;               // Climbing time config 

    BOOL                abLeaveDetection;               // Carry off-duty detection  info 
    TIME_SCHEDULE_INFO  stLeaveDetection;               // Off-duty time config 

    BOOL                abVehicleOnPoliceCar;           // Carry mobile police car info 
    TIME_SCHEDULE_INFO  stVehicleOnPoliceCar;           // Mobile police car time config 

    BOOL                abVehicleOnBus;                 // Carry Mobile bus info 
    TIME_SCHEDULE_INFO  stVehicleOnBus;                 // Mobile bus time config 

    BOOL                abVehicleOnSchoolBus;           // Carry Mobile school bus info 
    TIME_SCHEDULE_INFO  stVehicleOnSchoolBus;           // Mobile school bus time config   
}VIOLATION_TIME_SCHEDULE;

// MixModeConfig about lane config info 
typedef struct tagMixModeLaneInfo
{
    unsigned int                nLaneNum;                           // Lane config number
    TRAFFIC_EVENT_CHECK_INFO    stCheckInfo[MAX_LANE_CONFIG_NUMBER];     // Lane config corresponding to event detection  info 
}MIX_MODE_LANE_INFO;

// MixModeConfig mic mode violation config
typedef struct tagMIX_MODE_CONFIG
{
	BOOL                        bLaneDiffEnable;                    // Distinguish by lane or not
	MIX_MODE_LANE_INFO          stLaneInfo;
    TRAFFIC_EVENT_CHECK_INFO    stCheckInfo;
}MIX_MODE_CONFIG;

typedef struct tagPeriodOfValidity
{
    CFG_NET_TIME            stBeginTime;                    // Mark start time 
    CFG_NET_TIME            stEndTime;                      // Mark end time
}PERIOD_OF_VALIDITY;

// Traffic global config corresponding to mark related config
typedef struct tagTrafficCalibrationInfo
{
    char                    szUnit[CFG_COMMON_STRING_256];              // Mark unit
    char                    szCertificate[CFG_COMMON_STRING_256];       // Mark certificate
    PERIOD_OF_VALIDITY      stPeriodOfValidity;                         // Mark validity
}TRAFFIC_CALIBRATION_INFO;

// Traffic config corresponding to transmission strategy
typedef enum tagEmTransferPolicy
{
    EM_TRAFFIC_TRANSFER_UNKNOWN,            // Unknown strategy
    EM_TRAFFIC_TRANSFER_REALTIME,           // "RealtimePriority" real time first
    EM_TRAFFIC_TRANSFER_SEQUENCE,           // "SequencePriority" sequence first

}EM_TRANSFER_POLICY;

// Traffic global config corresponding to picture naming format parameter config
typedef struct tagTrafficNamingFormat
{
    char                    szFormat[CFG_COMMON_STRING_256];            // Picture firmat
}TRAFFIC_NAMING_FORMAT;

// Traffic global config corresponding to light group status config
typedef struct tagEnableLightStateInfo
{
    BOOL                    bEnable;      // Enable application layer received light group status to bottom or not
}ENABLE_LIGHT_STATE_INFO;

// traffic globle configuration
typedef struct tagCFG_TRAFFICGLOBAL_INFO
{
	VIOLATIONCODE_INFO   stViolationCode;       // Violation code configuration
	BOOL                 bEnableRedList;       // Red List Enable Detection Is Enabled, Vehicle Violation in The List Does Not Be Reported 

    BOOL                    abViolationTimeSchedule;                    // Carry violation snapshot custom time config 
    VIOLATION_TIME_SCHEDULE stViolationTimeSchedule;                    // Violation snapshot custom time config 
    
    BOOL                    abEnableBlackList;                          // Carry enable black list detection  info 
    BOOL                    bEnableBlackList;                           // Enable black list detection 

    BOOL                    abPriority;                                 // Carry violation priority parameter
    unsigned int            nPriority;                                  // Violation priority level number
    char                    szPriority[MAX_PRIORITY_NUMBER][CFG_COMMON_STRING_256]; // Violation priority level, 0 as highest priority    

    BOOL                    abNamingFormat;                             // Carry picture naming format parameter
    TRAFFIC_NAMING_FORMAT   stNamingFormat;                             // Picture naming format parameter config

    BOOL                    abVideoNamingFormat;                        // Carry Record naming format parameter
    TRAFFIC_NAMING_FORMAT   stVideoNamingFormat;                        // Record naming format parameter config

    BOOL                    abCalibration;                              // Carry mark info 
    TRAFFIC_CALIBRATION_INFO stCalibration;                             // Mark  info 
    
    BOOL                    abAddress;                                  // Carry search address parameter
    char                    szAddress[CFG_COMMON_STRING_256];           // Search address?ê?UTF-8 code

    BOOL                    abTransferPolicy;                           // Carry transmission strategy parameter
    EM_TRANSFER_POLICY      emTransferPolicy;                           // Transmission strategy

    BOOL                    abSupportModeMaskConfig;                    // Carry violation mask 
    TRAFFIC_EVENT_CHECK_MASK stSupportModeMaskConfig;                   // Violation type supported detection mode mask config

    BOOL                    abIsEnableLightState;                       // Carry light group status
    ENABLE_LIGHT_STATE_INFO stIsEnableLightState;                       // Traffic global config corresponding to picture naming format parameter config
    
    BOOL                    abMixModeInfo;                              // Include mix mode config or not
    MIX_MODE_CONFIG         stMixModeInfo;                              // Mix mode config
}CFG_TRAFFICGLOBAL_INFO;
// Add by lihu 2011/8/26 end

// CFG_CMD_VIDEOENCODEROI Region of Intrest configuration
#define DH_MAX_QUALITY_REGION_NUM 8
typedef struct tagCFG_VIDEOENCODEROI_INFO
{
	int      nRegionNum;                               // Region number
	CFG_RECT stRegions[DH_MAX_QUALITY_REGION_NUM];     // Optimize region, 0~8191
	BYTE     byQuality;        // Pic quality, 1~6,the higher value the better quality
	bool     bMain;            // Optimize main stream encode
	bool     bExtra1;          // Optimize extra stream 1 encode	
	bool     bExtra2;          // Optimize extra stream 2 encode
	bool     bExtra3;          // Optimize extra stream 3 encode
	bool     bSnapshot;        // Optimize extra snap pictrue encode
	BYTE     byReserved2[2];   // Reserved
}CFG_VIDEOENCODEROI_INFO;

typedef struct tagCFG_ATMMOTION_INFO
{
	int nTimeLimit;
}CFG_ATMMOTION_INFO;

typedef struct tagCFG_SNAPSOURCE_INFO_SINGLE_CHANNEL
{
	bool		bEnable;			//Enable
	BYTE		bReserved1[3];		//Reserved
	BYTE		bDevice[64];		//Device name
	DWORD		dwChannel;			//Video channel number
	DWORD		dwLinkVideoChannel; //Link video channel
	BYTE		bReserved[512];		//Reserved
}SNAPSOURCE_INFO_SINGLE_CHANNEL;

typedef struct tagCFG_SNAPSOURCE_INFO
{
	DWORD dwCount;												// Channel number
	SNAPSOURCE_INFO_SINGLE_CHANNEL singleChnSanpInfo[MAX_VIDEO_CHANNEL_NUM];	// Snap source configuration
}CFG_SNAPSOURCE_INFO;

typedef struct tagDEVICE_STATUS
{
	char	szDeviceName[MAX_REMOTEDEVICENAME_LEN];	// Remoute device name
	BYTE	bDeviceStatus;							// Remoute device state 0:not on line 1:on line
	BYTE	bReserved[63];							// Reserved
}DEVICE_STATUS;

typedef struct tagCFG_REMOTE_DEVICE_STATUS
{
	DEVICE_STATUS devStatus[MAX_REMOTE_DEV_NUM]; // Device state
	DWORD		  dwDevCount;					 // Device number
	BYTE		  bReserved[1024];				 // Reserved
}CFG_REMOTE_DEVICE_STATUS;


//-----------------------------Audio analyse configuration------------------------------
// event type EVENT_IVS_AUDIO_ABNORMALDETECTION (Event of aduio abnormal detection)corresponding rule configuration
typedef struct tagCFG_IVS_AUDIO_ABNORMALDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// name of rule,don't wish
	bool				bRuleEnable;											// enable
	BYTE                bReserved[3];                                           // reserve
	int                 nDecibel;                                               // decibel of audio, (db)
	int                 nFrequency;                                             // frequency of audio,(Hz)
	int                 nMinDuration;                                           // the shortest duration(s)
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// alarm linkage
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// respond time
}CFG_IVS_AUDIO_ABNORMALDETECTION_INFO;

typedef struct tagCFG_CAP_AUDIO_ANALYSE_INFO
{
	int                 nSupportedRuleNum;                                      // number of support rule
	DWORD               dwSupportedRules[MAX_RULE_LIST_SIZE];                   // supprot rule type
}CFG_CAP_AUDIO_ANALYSE_INFO;
//-------------------------IPS && SVR------------------------------

// device state info
typedef struct tagCFG_DEVICESTATUS_INFO
{
	int                 nPowerNum;                               // power number
	BYTE                byPowerStatus[MAX_POWER_NUM];            // power state,1:normal 2:exception 3:unknown
	int                 nCPUNum;                                 // CPU number
	int                 nCPUTemperature[MAX_CPU_NUM];            // CPU temperature
	int                 nFanNum;                                 // fun number
	int                 nRotatoSpeed[MAX_FUN_NUM];               // fun speed
}CFG_DEVICESTATUS_INFO;

// hard disk number
typedef struct tagCFG_HARDDISK_INFO 
{
	int                     nChannel;                        // channel id
	int                     nCapacity;                       // disk capacity
	BYTE                    byStatus;                        // disk state,0:unknown 1:running 2:fail
	BYTE                    byUsedStatus;                    // used state,1.idle 2.be on use 3.unknown
    BYTE                    byHotBack;                       // wether be hot back,0:be 1:not be
	BYTE                    byReserved;                      // reserved
	char                    szRaidName[MAX_NAME_LEN];        // disk group number
	char                    szType[32];                      // disk type
	int                     nTank;                           // tank, 0:host;1:tank1; 2:tank2 ...
	int						nRemainSpace;					 // Space remained, unit M
}CFG_HARDDISK_INFO;

typedef struct tagCFG_HARDDISKTANK_INFO
{
	char                    szTankName[MAX_NAME_LEN];           // tank name
	int                     nHardDiskNum;                       // disk number
	CFG_HARDDISK_INFO       stuHarddiskInfo[MAX_HARDDISK_NUM];  // disk info
}CFG_HARDDISKTANK_INFO;

typedef struct tagCFG_HARDISKTANKGROUP_INFO
{
	int                      nTankNum;                       // disk tank number
	CFG_HARDDISKTANK_INFO    stuHarddisktank[MAX_TANK_NUM];  // disk tanks info
}CFG_HARDISKTANKGROUP_INFO;

// Raid group information
typedef struct tagCFG_RAID_INFO
{
	char                    szRaidName[MAX_NAME_LEN];         // Raid name
	BYTE                    byType;                           // type 1:Jbob, 2:Raid0, 3:Raid1, 4:Raid5
	BYTE                    byStatus;                         // state 0:unknown, 1:active, 2:degraded, 3:inactive
	BYTE                    byStatusCount;                    // count of status, if the count >= 1, use byStatusGroup
	BYTE                    byReserved;		                  // reserved
	int                     nMember[MAX_CHAN_NUM];            // disk member
	int                     nDiskNUM;                         // disk number
	int                     nCapacity;                        // capacity
	int                     nTank;                            // tank number
	int						nRemainSpace;					 // Space remained, unit M
	BYTE					byStatusGroup[MAX_STATUS_NUM];	 //  state of the array, the same as byStatus
}CFG_RAID_INFO;

typedef struct tagCFG_RAIDGROUP_INFO
{
	int                     nRaidNum;                         // Raid number
	CFG_RAID_INFO           stuRaidInfo[MAX_RAID_NUM];        // Raid group info
}CFG_RAIDGROUP_INFO;

// storage pool info
typedef struct tagCFG_STORAGEPOOL_INFO
{
	char                   szName[MAX_NAME_LEN];               // storage pool name
	int                    nMemberNum;                         // device member number
	char                   szMember[MAX_DEV_NUM][MAX_NAME_LEN];// device member name
	int                    nUsed;                              // used capacity
    int                    nCapacity;                          // total capacity
    int                    nStatus;                            // state 0:unknown 1:active 2:degraded 3:inactive
    int                    nTank;                              // tank 0:host, 1:tank1, 2:tank2 ...
}CFG_STORAGEPOOL_INFO;

typedef struct tagCFG_STORAGEPOOLGROUP_INFO
{
	int                     nStroagePoolNum;                           // storage pool number
	CFG_STORAGEPOOL_INFO    stuStoragePoolInfo[MAX_STORAGEPOOL_NUM];   // storage pool information
}CFG_STORAGEPOOLGROUP_INFO;

// file system group info
typedef struct tagCFG_STORAGEPOSITION_INFO
{
	char                   szName[MAX_NAME_LEN];               // storage position name
    char                   szStoragePoolName[MAX_NAME_LEN];    // storage pool name	
    int                    nUsedCapacity;                      // used capacity(G)	
    int                    nTotalCapacity;                     // totao capacity(G)	
	BYTE                   byStatus;                           // state:0.unknown 1.normal 2.configuration exception 3.mount exception
    BYTE                   byReserved[3];                      // reserved
}CFG_STORAGEPOSITION_INFO;

typedef struct tafCFG_STORAGEPOSITIONGROUP_INFO
{
	int                      nStoragePositionNum;                         // strorage position
	CFG_STORAGEPOSITION_INFO stuStoragePositionInfo[MAX_STRORAGEPOS_NUM]; // file system group information      
}CFG_STORAGEPOSITIONGROUP_INFO;

// remote device group info
typedef struct tagCFG_VIDEOINDEV_INFO
{
	char                   szDevName[MAX_NAME_LEN];             // remote device name
    char                   szDevID[MAX_NAME_LEN];               // device ID	
    char                   szDevType[MAX_NAME_LEN];             // device type
    int                    nTotalChan;                          // total channel number
	int                    nTotalAlarmChan;                     // total alarm channel number
    char                   szIP[MAX_ADDRESS_LEN];               // device IP
	BYTE                   byStatus;                            // state 0:unknown 1:on line 2:off line
	BYTE                   byReserved[3];                       // reserved
}CFG_VIDEOINDEV_INFO;

typedef struct tafCFG_VIDEOINDEVGROUP_INFO
{
	int                    nVideoDevNum;                              // remote device number
	CFG_VIDEOINDEV_INFO    stuVideoInDevInfo[MAX_VIDEODEV_NUM];       // file system group info      
}CFG_VIDEOINDEVGROUP_INFO;

// channel record group state
typedef struct tagCFG_DEVRECORD_INFO
{
	char                   szDevName[MAX_NAME_LEN];               // device name
	char                   szIP[MAX_ADDRESS_LEN];                 // device IP	
	char                   szChannel[MAX_NAME_LEN];               // channel number
    char                   szChannelName[MAX_NAME_LEN];           // channel name	
    char                   szStoragePosition[MAX_NAME_LEN];       // storage position info
	BYTE                   byStatus;                              // state 0:unknown 1:record 2:stop
	BYTE                   byReserved[3];                         // reserved
}CFG_DEVRECORD_INFO;

typedef struct tagCFG_DEVRECORDGROUP_INFO
{
	int                    nChannelNum;                          // channnel number
	CFG_DEVRECORD_INFO     stuDevRecordInfo[MAX_CHAN_NUM];       // channel record state info
}CFG_DEVRECORDGROUP_INFO;

#define byDahuaII byPrivateII
#define byDahuaIId byPrivateIId

// server state
typedef struct tagCFG_IPSERVER_STATUS
{
	int                    nSupportedServerNum;                  // support server number
	char                   szSupportServer[MAX_SEVER_NUM][MAX_NAME_LEN];              // support server name: Svr Svrd, DataBase DataBased, NtpServer NtpServerd,DahuaII DahuaIId, Samba Nfs Ftp iScsi 
	int                    nSvrSuppSubServerNum;                                      // Svr support sub server number
	char                   szSvrSuppSubServer[MAX_SEVER_NUM][MAX_NAME_LEN];           // Svr support sub server info CMS DMS	MTS	SS RMS DBR
	BYTE                   byCMS;                                // 0:unknown 1:run 2:not run
	BYTE                   byDMS;                                // 0:unknown 1:run 2:not run
	BYTE                   byMTS;                                // 0:unknown 1:run 2:not run
	BYTE                   bySS;                                 // 0:unknown 1:run 2:not run
	BYTE                   byRMS;                                // 0:unknown 1:run 2:not run
	BYTE                   byDBR;                                // 0:unknown 1:run 2:not run
	BYTE                   bySvrd;                               // 0:unknown 1:run 2:not run
	BYTE                   byDataBase;                           // 0:unknown 1:run 2:not run
	BYTE                   byDataBased;                          // 0:unknown 1:run 2:not run
	BYTE                   byNtpServer;                          // 0:unknown 1:run 2:not run
	BYTE                   byNtpServerd;                         // 0:unknown 1:run 2:not run
	BYTE                   byPrivateII;                            // 0:unknown 1:run 2:not run
	BYTE                   byPrivateIId;                           // 0:unknown 1:run 2:not run
	BYTE                   bySAMBA;                              // 0:unknown 1:run 2:not run
	BYTE                   byNFS;                                // 0:unknown 1:run 2:not run
	BYTE                   byFTP;                                // 0:unknown 1:run 2:not run
	BYTE                   byISCSI;                              // 0:unknown 1:run 2:not run
	BYTE                   byReserved[3];                        // reserved
}CFG_IPSERVER_STATUS;

//---------------------------video matrix-----------------------------------
#define MAX_SUPPORT_SPLIT_MODE_NUM    16             // support split mode max number
#define MAX_MATRIX_PLAN               4              // max matrix plan number
#define MAX_TOUR_MODE                 16             // max tour mode number

typedef enum tagMATRIX_VIEW_SPLITMODE
{
	MATRIX_VIEW_SPLIT1 = 0,
	MATRIX_VIEW_SPLIT2,	
	MATRIX_VIEW_SPLIT4,
	MATRIX_VIEW_SPLIT8,
	MATRIX_VIEW_SPLIT9,	
	MATRIX_VIEW_SPLIT16,
	MATRIX_VIEW_SPLITPIP,
	MATRIX_VIEW_SPLIT6,
	MATRIX_VIEW_SPLIT12,
	MATRIX_VIEW_SPLIT25,
	MATRIX_VIEW_SPLIT36,
	MATRIX_VIEW_SPLIT_NR,
}MATRIX_VIEW_SPLITMODE;

// tour mode
typedef struct tagCFG_TOUR_MODE
{
	int               nViewMode;                                    // video split mode,see MATRIX_VIEW_SPLITMODE
	unsigned int      dwViewSplitMask;                     // as the ViewMode instruct mode,use mask instruct the split enable
													       // for example:0x00000007:means split 1,2,3's enable is opened,other not open,0x0000000F means 1,2,3,4's enable is opened
}CFG_TOUR_MODE;

// SPOT video matrix plan
typedef struct tagCFG_VIDEO_MATRIX_PLAN
{
	BOOL            bEnable;                                          // matrix plan configuration
	int             nTourPeriod;                                      // matrix tour internal(s),>=1
	int             nTourModeNum;                                     // tour list number
	CFG_TOUR_MODE   stuTourMode[MAX_TOUR_MODE];                       // tuor list
}CFG_VIDEO_MATRIX_PLAN;

// SPOT matix configuration
typedef struct tagCFG_VIDEO_MATRIX
{
	int                         nSupportSplitModeNumber;         // support split mode number
	BYTE                        bySupportSplitMode[MAX_SUPPORT_SPLIT_MODE_NUM];          // support split mode
	int                         nMatrixPlanNumber;               // matrix plan number
	CFG_VIDEO_MATRIX_PLAN       stuMatrixPlan[MAX_MATRIX_PLAN];                // matrix plan
}CFG_VIDEO_MATRIX;

/////////////////////////////////// Video diagnosis configuration/////////////////////////////////////// 
// Video jitter detection
typedef struct tagCFG_VIDEO_DITHER_DETECTION
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second
	BYTE							byThrehold1;								// Warning threshold (1-100)

	BYTE							byThrehold2;								// Alarm threshold(1-100)
}CFG_VIDEO_DITHER_DETECTION;
// Stripe detection
typedef struct tagCFG_VIDEO_STRIATION_DETECTION 
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre-warning threshold (1-100)
	BYTE							byThrehold2;								// Alarm threshold (1-100)
	BYTE							byReserved1[2];								//Byte alignment
	BOOL							bUVDetection;								// VV Detection or not 					
}CFG_VIDEO_STRIATION_DETECTION;
// Video loss detection
typedef struct tagCFG_VIDEO_LOSS_DETECTION
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								//Min duration   unit: second 0~65535
}CFG_VIDEO_LOSS_DETECTION;
// Camera masking detection
typedef struct tagCFG_VIDEO_COVER_DETECTION
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre-warning threshold (1-100)
	BYTE							byThrehold2;								// Alarm threshold (1-100)
}CFG_VIDEO_COVER_DETECTION;
// Video frozen detection
typedef struct tagCFG_VIDEO_FROZEN_DETECTION
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
}CFG_VIDEO_FROZEN_DETECTION;
// Brightness detection
typedef struct tagCFG_VIDEO_BRIGHTNESS_DETECTION
{	
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							bylowerThrehold1;							// Pre-warning threshold (1-100)
	BYTE							bylowerThrehold2;							// Alarm threshold (1-100)
	BYTE							byUpperThrehold1;							// Pre-warning threshold (1-100)
	BYTE							byUpperThrehold2;							// Alarm threshold (1-100)
}CFG_VIDEO_BRIGHTNESS_DETECTION;
// Contrast abnormal detect
typedef struct tagCFG_VIDEO_CONTRAST_DETECTION
{	
	BOOL							bEnable;									// Enable configuration

	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							bylowerThrehold1;							// Pre-warning threshold (1-100)
	BYTE							bylowerThrehold2;							// Alarm threshold (1-100)
	BYTE							byUpperThrehold1;							// Pre-warning threshold  (1-100)
	BYTE							byUpperThrehold2;							// Alarm threshold  (1-100)
}CFG_VIDEO_CONTRAST_DETECTION;
// Color cast detection
typedef struct tagCFG_VIDEO_UNBALANCE_DETECTION
{	
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre-warning threshold  (1-100)
	BYTE							byThrehold2;								// Alarm threshold  (1-100)
}CFG_VIDEO_UNBALANCE_DETECTION;
// Noise detection
typedef struct tagCFG_VIDEO_NOISE_DETECTION
{	
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre=warning threshold  (1-100)
	BYTE							byThrehold2;								// Alarm threshold  (1-100)
}CFG_VIDEO_NOISE_DETECTION;
// Fuzzy detection
typedef struct tagCFG_VIDEO_BLUR_DETECTION
{
	BOOL							bEnable;									// Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre-warning threshold  (1-100)
	BYTE							byThrehold2;								// Alarm threshold  (1-100)

}CFG_VIDEO_BLUR_DETECTION;
// Scene change detection
typedef struct tagCFG_VIDEO_SCENECHANGE_DETECTION
{	
	BOOL							bEnable;									//Enable configuration
	int								nMinDuration;								// Min duration   unit: second 0~65535
	BYTE							byThrehold1;								// Pre-warning threshold  (1-100)
	BYTE							byThrehold2;								// Alarm threshold  (1-100)
}CFG_VIDEO_SCENECHANGE_DETECTION;
typedef struct tagCFG_VIDEO_DIAGNOSIS_PROFILE
{
	char							szName[MAX_PATH];							// Name

	CFG_VIDEO_DITHER_DETECTION*		pstDither;									// Video dither detection
	CFG_VIDEO_STRIATION_DETECTION*	pstStriation;								//Video stripe detection
	CFG_VIDEO_LOSS_DETECTION*		pstLoss;									//  Video loss detection
	CFG_VIDEO_COVER_DETECTION*		pstCover;									// Camera masking detection
	CFG_VIDEO_FROZEN_DETECTION*		pstFrozen;									// Video frozen detection
	CFG_VIDEO_BRIGHTNESS_DETECTION*	pstBrightness;								// Video brightness detection
	CFG_VIDEO_CONTRAST_DETECTION*	pstContrast;								// Video contrast abnormal detection
	CFG_VIDEO_UNBALANCE_DETECTION*	pstUnbalance;								// Video color cast detection
	CFG_VIDEO_NOISE_DETECTION*		pstNoise;									// Video noise detection
	CFG_VIDEO_BLUR_DETECTION*		pstBlur;									// Fussy detection
	CFG_VIDEO_SCENECHANGE_DETECTION* pstSceneChange;							// Video Scene change detection
}CFG_VIDEO_DIAGNOSIS_PROFILE;
// Video diagnosis profile(CFG_CMD_VIDEODIAGNOSIS_PROFILE),support multi-paprameter list, index by name. User apply for memory and initialize
typedef struct tagCFG_VIDEODIAGNOSIS_PROFILE
{
	int								nTotalProfileNum;							// User allocates total parameter number depending on capacity collection
	int								nReturnProfileNum;							// Returned real parameter number
	CFG_VIDEO_DIAGNOSIS_PROFILE*	pstProfiles;								//  User allocate nProfileCount  countVIDEO_DIAGNOSIS_PROFILE
}CFG_VIDEODIAGNOSIS_PROFILE;

/////Video diagnosis task
enum CFG_EM_STREAM_TYPE
{
	CFG_EM_STREAM_ERR,                  //Others
	CFG_EM_STREAM_MAIN,					// "Main"-Main stream
	CFG_EM_STREAM_EXTRA_1,				// "Extra1"-Extra stream 1
	CFG_EM_STREAM_EXTRA_2,				// "Extra2"-Extra stream 2 
	CFG_EM_STREAM_EXTRA_3,				// "Extra3"-Extra stream 3
	CFG_EM_STREAM_SNAPSHOT,				// "Snapshot"-Snapshot bit stream
	CFG_EM_STREAM_OBJECT,				// "Object"-Object stream
};

// detailed device info
typedef struct tagCFG_TASK_REMOTEDEVICE
{
	char                            szAddress[MAX_PATH];                        // Device address or domain name
	unsigned int                    dwPort;                                     // Port number
	char                            szUserName[MAX_PATH];                       // User name
	char                            szPassword[MAX_PATH];                       // Password without encription
	char                            szProtocolType[MAX_PATH];                   // Connect device protocol type
	CFG_RemoteDeviceVideoInput      *pVideoInput;                               // video input channel,apply nMaxVideoInputs * CFG_RemoteDeviceVideoInput space
	int				                nMaxVideoInputs;					        // maximum number of video input channel
	int				                nRetVideoInputs;					        // return to the video input channel number
}CFG_TASK_REMOTEDEVICE;

typedef struct tagCFG_TAST_SOURCES
{
	// Capacity
	bool							abDeviceID;
	bool							abRemoteDevice;

	char							szDeviceID[MAX_PATH];						// Device ID
	CFG_TASK_REMOTEDEVICE           stRemoteDevice;                             // Detailed device info
	int								nVideoChannel;								// Video channel number
	CFG_EM_STREAM_TYPE				emVideoStream;								// Video stream type
	int								nDuration;									// Diagnosis duration
    BOOL                            abStartTime;                                // FALSE means source is real-time stream, stuStartTime field invalid, TRUE means source is record file, stuStartTime field valid
    CFG_NET_TIME                    stuStartTime;                               // when abStartTime is true, means source is not real-time stream, but it is record file, and the time means the start time of record to analyze
}CFG_TAST_SOURCES;
typedef struct tagCFG_DIAGNOSIS_TASK
{
	char							szTaskName[MAX_PATH];						// Task name
	char							szProfileName[MAX_PATH]; 				//Diagnosis paramter list name of the task
	int								nTotalSourceNum;						    // User allocates total sources number depending on capacity collection
	int								nReturnSourceNum;							// Returned real task sources number
	CFG_TAST_SOURCES*				pstSources;									// Task sources  User allocates nTotalSourceNum  
}CFG_DIAGNOSIS_TASK;
// Video diagnosis task list (CFG_CMD_VIDEODIAGNOSIS_TASK). Separate task indexed by name.  User applies for memory and initialize
typedef struct tagCFG_VIDEODIAGNOSIS_TASK
{
	int								nTotalTaskNum; 								// User allocation amount depending on capacity collection
	int								nReturnTaskNum; 							// Returned actual task number
	CFG_DIAGNOSIS_TASK*				pstTasks;									// Task configuration.  User allocate memory nTotalTaskNum
}CFG_VIDEODIAGNOSIS_TASK;

// Video diagnosis project
typedef struct tagPROJECT_TASK
{
	BOOL							bEnable;									//  Task enable or not 
	char							szTaskName[MAX_PATH];						// Task name
	CFG_TIME_SECTION				stTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	//  Task period
	BOOL                            bIsCycle;                                   // Whether The Task Cycle Is Allowed, TRUE: Cycle, FALSE: No Cycle
}CFG_PROJECT_TASK;
typedef struct tagDIAGNOSIS_PROJECT
{
	char							szProjectName[MAX_PATH];					// Project name
	int								nTotalTaskNum;								// User allocates total task number depending on capacity collection
	int								nReturnTaskNum;					    		//Returned actual task amount
	CFG_PROJECT_TASK*				pstProjectTasks;								//Total task list.  User allocates memory nTotalTaskNum 
}CFG_DIAGNOSIS_PROJECT;
// Video diagnosis plan list (CFG_CMD_VIDEODIAGNOSIS_PROJECT). User applies for memory and initialize
typedef struct tagCFG_VIDEODIAGNOSIS_PROJECT
{
	int								nTotalProjectNum;							// User allocates total project number depending on capacity collection
	int								nReturnProjectNum;							// Return actual project amount.											// Project configuration  User allocate memory nTotalProjectNum
	CFG_DIAGNOSIS_PROJECT*			pstProjects;									// Project config. User allocates memory nTotalProjectNum
}CFG_VIDEODIAGNOSIS_PROJECT;

// Planing The Related Information in Real Time
typedef struct tagCFG_DIAGNOSIS_REALPROJECT
{
	char							szProjectName[MAX_PATH];					// Encoding Plan Name According to Ansi
	CFG_DIAGNOSIS_TASK			    stProjectTask;							    // Task Information
}CFG_DIAGNOSIS_REALPROJECT;

// Real-Time Video Diagnostics Schedule
typedef struct tagCFG_VIDEODIAGNOSIS_REALPROJECT 
{
	int								nProjectNum;							    // The Number of Real Time Plan
	CFG_DIAGNOSIS_REALPROJECT*		pstProjects;							    // Plan Configuration, Caller to Allocate nProjectNum Memory Units
}CFG_VIDEODIAGNOSIS_REALPROJECT;

// Video diagnosis global list(CFG_CMD_VIDEODIAGNOSIS_GLOBAL).each channel supports one diagnosis configuration
typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
{
	BOOL                            abProjectName;                              // Whether To Be Valid for The Plan Name
	char							szProjectName[MAX_PATH];					// Ansi Encoding for The Plan Name
	BOOL                            abRealProjectName;                          // Whether To Be Valid for The Real Time Plan Name
	char                            szRealProjectName[MAX_PATH];                // Ansi Encoding for The Real Time Plan Name 
}CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL;
typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL
{
	int								nTotalGlobalNum;							// User allocate global number depending on capacity set
	int								nReturnGlobalNum;							// Return actual global config number
	CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL	*pstGlobals;									// Video diagnosis global config.  User allocates memory
}CFG_VIDEODIAGNOSIS_GLOBAL;

// Video diagnosis service capacity set(CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER)
typedef struct tagCFG_VIDEODIAGNOSIS_CAPS_INFO
{
	int								nTypeCount;									// Supported video diagnosis types. Amount
	char						    szSupportedType[MAX_VIDEODIAGNOSIS_DETECT_TYPE][MAX_PATH];// Supported video diagnosis type
	int								nMaxProfiles;								// Max parameter list amount
	int								nMaxTasks;									// Max task amount
	int								nMaxSourcesOfTask;							// Max video source of single task
	int								nMaxProjects;								// Max project amount
}CFG_VIDEODIAGNOSIS_CAPS_INFO;

// Get video diagnosis channel amount( CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT )corresponding structure
typedef struct tagCFG_VIDEODIAGNOSIS_COLLECT_INFO
{
	int                             nDiagnosisChannels;                                   // Video diagnosis channel number
}CFG_VIDEODIAGNOSIS_COLLECT_INFO;

// Get video diagnosis current state( CFG_CMD_VIDEODIAGNOSIS_GETSTATE ) 
typedef struct tagCFG_VIDEODIAGNOSIS_STATE_INFO
{
	BOOL                            bEnable;                                     // Enable or not 
	BOOL                            bRunning;                                    // Running or not. Enabled.There is task in process and there is no error.
	char                            szCurrentProject[MAX_PATH];                  // Current project name
	char                            szCurrentTask[MAX_PATH];                     // Current task name
	char                            szCurrentProfile[MAX_PATH];                  // Current task parameter list name
	int                             nCurrentSourceCount;                         // Current task tour video sources amount
	int                             nCurrentSourceIndex;                         // Current task video source number. Starts from 0
	CFG_TIME_SECTION                stCurrentTimeSection;                        // Current project period
	int                             nTaskCountOfProject;                         // Current task amount of project
	int                             nIndexOfCurrentTask;                         // Current project SN.Starts from 0
}CFG_VIDEODIAGNOSIS_STATE_INFO;

// supported by the server list
typedef struct tagCFG_DEV_SERVICE_LIST
{
	int                             nServiceNum;                                 // number of the service support
	char                            szService[MAX_SERVICE_NUM][MAX_NAME_LEN];    // support for specific server
}CFG_DEV_SERVICE_LIST;

//for master-slave tracker number 
typedef struct tagCFG_MASTERSLAVETRACKER_INFO
{
        int                nStructSize;
	    int                nChannels;	// master-slave tracker channel number 
}CFG_MASTERSLAVETRACKER_INFO;

#define  MAX_CAMERA_TYPE	64
#define	 MAX_TYPE_STRING	64

typedef struct tagCFG_CAMERA_PER_TYPE_INFO
{
	char				szCameraType[MAX_TYPE_STRING];	//Camera Type
	char				szLensType[MAX_TYPE_STRING];	//The Type of Camera Lens, It Is Related to the Camera Type, Null Is Allowed 
}CFG_CAMERA_PER_TYPE_INFO;

typedef struct tagCFG_CAMERA_TYPE_INFO
{
	int							nCameraTypeNum;						// The Number of Different Types of The Camera
	CFG_CAMERA_PER_TYPE_INFO	stCameraTypeInfos[MAX_CAMERA_TYPE]; // Detailed Information of Camera Type
}CFG_CAMERA_TYPE_INFO;

// zoom type
typedef enum tagCFG_ZOOM_TYPE
{
	ZOOM_TYPE_EXPECTMULTIPLE =0,     // fixed expect multiple
	ZOOM_TYPE_IVSADAPTIVE,           // according to the adaptive multiple intelligent device output
	ZOOM_TYPE_MULTIPLEADAPTIVE,      // adaptive multiple
	ZOOM_TYPE_NUM
}CFG_ZOOM_TYPE;

// tracking mode
typedef enum tagCFG_TRACKING_MODE
{
    TRACKING_MODE_ALARM=0,        // alarm of track
	TRACKING_MODE_MANUALOBJECT,   // manually select the object tracking
	TRACKING_MODE_AUTOOBJECT,     // automatically select the object tracking
	TRACKING_MODE_SELECTPOINT,    // points tracking
	TRACKING_MODE_MIX,            // mix-tracking(support the above four patterns at the same time)
	TRACKING_MODE_SLAVESELF,      // the ball machine control( mainly used for the userto control the ball machine)
	TRACKING_MODE_NUM
}CFG_TRACKING_MODE;

// the master-slave tracker global configuration
typedef struct tagCFG_MASTERSLAVE_GLOBAL_INFO
{
	int                nStructSize;
	float              fMaxZoom;                    // max zoom, use as int, ignore decimal
	float              fMinZoom;                    // min zoom, use as int, ignore decimal
	float              fExpectMultiple;             // expect multiple, fMaxZoom < fExpectMultiple < fMaxZoom, use as int, ignore decimal
	float              fPollTrackTime;              // poll track time(s),>0.0
	float              fPointTrackTime;             // point track time(s),>0.0, in automatically tracking ,alarm tracking,mix-tracking is effective
    float              fObjectTrackTime;            // time of manually select the object tracking(s),>0.0, in automatically tracking ,alarm tracking,mix-tracking is effective
	float              fExpectAngleX;               // expect angle x(level), use as int, ignore decimal
    float              fExpectAngleY;               // expect angle y(aplomb), use as int, ignore decimal
	CFG_SIZE           stTargetFaceSize;            // target face size(mm) ball device parameter, associated with the ball device, use as int, ignore decimal
	float              fMinFocus;                   // min focus(mm), use as int, ignore decimal
	float              fMaxFocus;                   // max focus(mm), use as int, ignore decimal
	CFG_ZOOM_TYPE      emZoomType;                  // zoom type
	CFG_TRACKING_MODE  emTrackingMode;              // tracking mode
	CFG_CAMERA_TYPE_INFO	stCameraInfo;           // The Gun Type Camera
	CFG_CAMERA_TYPE_INFO	stDomeInfo;	            // The Ball Type Camera
	int						nTrackZoomLevel;        // Grade of Tracking Multiple  -5 <= TrackZoomLevel <= 5 0 Is Represented by The Default Algorithm Approach
	BOOL					bReturnPtzPreset;       // TRUE: The Return to The Presetting Point Tracking, FALSE: Do not Return after The Presetting Tracking
}CFG_MASTERSLAVE_GLOBAL_INFO;

// get master-slave device capacity
typedef struct tagCFG_CAP_MASTERSLAVE_INFO
{
	int                     nStructSize;
	BYTE                    byTrackingMode[TRACKING_MODE_NUM]; // saod CFG_TRACKING_MODE enum corresponding mode,1 meas support
	CFG_CAMERA_TYPE_INFO	stCameraInfo;            // The Gun Type Camera
	CFG_CAMERA_TYPE_INFO	stDomeInfo;              // The Ball Type Camera
}CFG_CAP_MASTERSLAVE_INFO;


// get service event handler capacity
typedef struct tagCFG_CAP_EVENTHANDLER_INFO
{
	BOOL				bTimeSectionEnable;                                      // 
	BOOL				bRecordEnable;                                           // support recode or not
	BOOL				bAlarmOutEnable;                                         // support alarm output or not
	BOOL				bPtzLinkEnable;                                          // support ptz link output or not
	BOOL				bSnapshotEnable;                                         // support snap shot or not
	BOOL				bMailEnable;                                             // support send mail or not
	BOOL				bBeepEnable;                                             // support beep or not
	BOOL				bDejitterEnable;                                         // support dejitter or not
	BOOL                bTipEnable;                                              // support tip or not
	BOOL                bMonitorTourEnable;                                      // support monitor tour or not
}CFG_CAP_EVENTHANDLER_INFO;

//----------------------------------Video input configuration------------------------------------------  
#define DH_MAX_INMETERING_REGION_NUM 8

typedef struct tagVIDEO_INMETERING_INFO_CHANNEL
{
	// Capacity
	bool            bRegion;
	bool            bMode;
	BYTE			bReserved1[2];					         // Reserved field 1
	
	int				nRegionNum;                                 // Light detection region number
	CFG_RECT    	stuRegions[DH_MAX_INMETERING_REGION_NUM];   // Light detection region, partial detect mode only. Support multi-test region, use relative coordinates system(0~8191)
	BYTE  			byMode;				                     //Light detection mode. 0: average, 1:partial test
	BYTE  			bReserved2[3];				             // Reserved field 2
	BYTE			bReserved3[32];					         // Resrved field 3
}VIDEO_INMETERING_INFO_CHANNEL;

// Light detection setup (CFG_CMD_VIDEO_INMETERING) is an array. Each video input channel has specified configuration
typedef struct tagCFG_VIDEO_INMETERING_INFO
{
	int				nChannelNum; // Channel number
	VIDEO_INMETERING_INFO_CHANNEL	stuMeteringMode[MAX_VIDEO_CHANNEL_NUM]; // Light detection info of each channel, subscription is chaneel number
}CFG_VIDEO_INMETERING_INFO;

// Video input capacity set (CFG_CAP_CMD_VIDEOINPUT) 
typedef struct tagCFG_CAP_VIDEOINPUT_INFO
{
	int				nMeteringRegionCount;                   //Max light metering region amount
	BOOL            bFishEye;                               // support fish eye or not
	BOOL			bElectricFocus;							// support electic focus or not
	DWORD			dwExposureMode;							// support exposure mode or not, from low to high in turn means:0.exposure,1.low noise is prefered(plus),2.weak ghosting priority(shutter),3-50HZ prevent flashing.4-60HZ prevent flashing
	int             nWideDynamicRange;						// support wide motion range or not, 0-not support, 1- support digital wid dynamic
	int			    nGlareInhibition;						// support glare inhibition,0-disable,1-able
}CFG_CAP_VIDEOINPUT_INFO;

// Traffic flow statistic alarm info
typedef struct tagCFG_TRAFFIC_FLOWSTAT_ALARM_INFO
{
	bool                            bEnable;                              // Enable or not 
	int                             nPeriod;                              // Statistic period, unit:minute
	int                             nLimit;                               // Vehicle max and min limit during the statistics period, unit: vehicle
	int                             nRestore;                             // Alarm resume vehicle number during the statistics period, unit: vehicle
    int                             nDelay;                               // Period from the alarm detection to the alarm upload. Unit:second range 1~65535
	int                             nInterval;                            // Alarm interval, unit:second, range value 1~65535
	int                             nReportTimes;                         //  Report times:1~255
	CFG_TIME_SECTION                stCurrentTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX]; // Current schedule period
	CFG_ALARM_MSG_HANDLE            stuEventHandler;					  // Alarm linkage 
}CFG_TRAFFIC_FLOWSTAT_ALARM_INFO;

typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO_CHNL
{
	// Capacity
	bool	                		 abEnable;

	bool			                 bEnable;								// Enable or not 
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmUpperInfo;                     // Alarm max limit
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmLowInfo;                       // Alarm min limit
    int                              nDetectRegionPoint;                    // detect region point
    CFG_POLYGON                      stuDetectRegion[MAX_POLYGON_NUM];      // detect region
	char                             szName[MAX_NAME_LEN];                  // lane rule name,not repeat
	int								 nPresetID;								// PTZ in the preset point number (ball machine effectively only) 
}CFG_TRAFFIC_FLOWSTAT_INFO_LANE;

// Traffic flow statistic configuration(CFG_CMD_TRAFFIC_FLOWSTAT) 
typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO
{
	// Capacity
	bool							abPeriod;
	BYTE							bReserved1[3];						        // Reserved field 1

	int								nPeriod;									// Statistic period, unit: minute
	int								nLaneNum;									// Lane number
	CFG_TRAFFIC_FLOWSTAT_INFO_LANE	stuTrafficFlowstat[MAX_LANE_NUM];			// Traffic flow setup of each lane, subscription is lane number
	DWORD                           dwLaneExtraMaxNum;                          // Lane number expanded maximum (used in application memory), more application scenario extra lane information needs 
	DWORD                           dwLaneExtraRetNum;                          // Multi-application scenarios actual number of extra lanes
	CFG_TRAFFIC_FLOWSTAT_INFO_LANE  *pstuTrafficFlowstat;                       // Scene on the number of lanes, stuTrafficFlowstat array put don't open lane here continue to save, the serial number starting from the driveway MAX_LANE_NUM + 1 
}CFG_TRAFFIC_FLOWSTAT_INFO;

// Video concentrate Rules Configuration (CFG_CMD_SYNOPSISANALYSE_RULE_INFO)
typedef struct tagCFG_VIDOE_SYNOPSIS_ANALYSE_RULE_INFO
{
    CFG_ANALYSERULES_INFO   stDetailRuleInfo;       // Detailed rules                       
}CFG_VIDOE_SYNOPSIS_ANALYSE_RULE_INFO;

//-----------------------------------Video input front-end option------------------------------------------- 

// Video input nigh special configuration, automatically switch to night configuration when dark
typedef struct tagCFG_VIDEO_IN_NIGHT_OPTIONS
{
	BYTE				bySwitchMode;			// abandoned, replaced by bySwitchMode in CFG_VIDEO_IN_OPTIONS
                                                // 0- do not switch, 1- switch by brightness, 2- switch by time
	BYTE				byProfile;				// The current use of configuration files. 
												// 0 - day
												// 1 - night
												// 2-Normal
												// 0,1,2 are temporary configuration,make the image effect, easy to debug view image effect, do not click ok to leave the page is not saved to the device. 
												///3 - Non-temporary configuration, and click OK to save to your device, used in conjunction with SwitchMode, decided to configure the final effect under SwitchMode.
												// SwitchMode=0?ê?Profile=3?ê?Set the configuration to the device during the day;
												// SwitchMode=1?ê?Profile=3?ê?Set the night configuration to the device 
												// SwitchMode=2?ê?Profile=3?ê?According to sunrise and sunset time switch, use during the day time configuration during the day and night time use night configuration, save to equipment; 
												// SwitchMode=4?ê?Profile=3?ê?Use common configuration ,saved to the device
	BYTE				byBrightnessThreshold ;	// Brightness Threshold	 0~100
	BYTE				bySunriseHour;			// Sunrise and sunset time, night mode is on before sunrise and after sunset 
	BYTE				bySunriseMinute;		// 00:00:00 ~ 23:59:59
	BYTE				bySunriseSecond;
	BYTE				bySunsetHour;
	BYTE				bySunsetMinute;
	BYTE				bySunsetSecond;  
	BYTE				byGainRed;				//Red gain red. Valid when WB is "Custom" mode (0~100)
	BYTE				byGainBlue;				//Green gain. Valid when WB is "Custom" mode  (0~100)
	BYTE				byGainGreen;			// Blue gain setup. Valid when WB is "Custom" mode (0~100)
	BYTE				byExposure;				//Exposure mode; range value depends on device capacity set; 0-automatic, 1- exposure level1,2-exposure level 2.  Mn-1:Max exposure level  n auto exposure of max and min time. n+1 custom exposure time (n==byExposureEn)
	float				fExposureValue1;		//  Auto exposure value min limit or manual axposure custom, unit is millisecond (0.1ms~80ms).
	float				fExposureValue2;		// Auto exposure time max limit, unit is millisecond (0.1ms~80ms)
	BYTE				byWhiteBalance ;		// WB. White 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					//  When gainAuto is true, it is max auto gain limit, otherwise, it is fixed value gain.
	bool				bGainAuto;				// Auto Gain 
	bool				bIrisAuto;				// Auto Iris 
	float               fExternalSyncPhase;     // 0~360 LL Phase
	BYTE				byGainMin;				// gain min
	BYTE				byGainMax;				// gain max
	BYTE				byBacklight;			// backlight:ability to set value range depends on the device,0-close 1-open 2-backlingt compensation specified area
	BYTE				byAntiFlicker;			// prevent flashing mode,0- out door, 1-50HZ prevent flashing,2-60HZ prevent flashing
	BYTE				byDayNightColor;		// day or night,0-colour,1-according to the brightness auromatically switches,2-black and white
	BYTE				byExposureMode;         // exposure mode, effective exposure levels for automatic exposure,1-auto,2-plus,2-shutter
	BYTE				byRotate90;				// 0-not rotate,1-deasil 90,2-deasil 90
	bool				bMirror;				// mirror
	BYTE                byWideDynamicRange;     // wide dynamic range[1~100],0-close
	BYTE                byGlareInhibition;		// glare inhibition,0-close,[1-100]
	CFG_RECT			stuBacklightRegion;     // backlight region
	BYTE                byFocusMode;            // 0-close?ê?1-aux focus?ê?2-auto focus
	bool				bFlip;					// flip
	BYTE				reserved[74];			// Reserved
} CFG_VIDEO_IN_NIGHT_OPTIONS;

typedef struct tagCFG_VIDEO_IN_NORMAL_OPTIONS
{
	BYTE				byGainRed;				// Red gain red. Valid when WB is "Custom" mode (0~100)
	BYTE				byGainBlue;				// Green gain. Valid when WB is "Custom" mode  (0~100)
	BYTE				byGainGreen;			// Blue gain setup. Valid when WB is "Custom" mode (0~100)
	BYTE				byExposure;				// Exposure mode; range value depends on device capacity set; 0-automatic, 1- exposure level1,2-exposure level 2.  Mn-1:Max exposure level  n auto exposure of max and min time. n+1 custom exposure time (n==byExposureEn)
	float				fExposureValue1;		// Auto exposure value min limit or manual axposure custom, unit is millisecond (0.1ms~80ms).
	float				fExposureValue2;		// Auto exposure time max limit, unit is millisecond (0.1ms~80ms)
	BYTE				byWhiteBalance ;		// WB. White 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					// When gainAuto is true, it is max auto gain limit, otherwise, it is fixed value gain.
	bool				bGainAuto;				// Auto Gain
	bool				bIrisAuto;				// Auto Iris
	float               fExternalSyncPhase;     // 0~360 LL Phase
	BYTE				byGainMin;				// gain min
	BYTE				byGainMax;				// gain max
	BYTE				byBacklight;			// backlight:ability to set value range depends on the device,0-close 1-open 2-backlingt compensation specified area
	BYTE				byAntiFlicker;			// prevent flashing mode,0- out door, 1-50HZ prevent flashing,2-60HZ prevent flashing
	BYTE				byDayNightColor;		// day or night,0-colour,1-according to the brightness auromatically switches,2-black and white
	BYTE				byExposureMode;         // exposure mode, effective exposure levels for automatic exposure,0-auto,1-plus,2-shutter
	BYTE				byRotate90;				// 0-not rotate,1-deasil 90,2-deasil 90
	bool				bMirror;				// mirror
	BYTE                byWideDynamicRange;     // wide dynamic range[1~100],0-close
	BYTE                byGlareInhibition;		// glare inhibition,0-close,[1-100]
	CFG_RECT			stuBacklightRegion;     // backlight region
	BYTE                byFocusMode;            // 0-off?ê?1-easy focus?ê?2-auto focus
	bool				bFlip;					// flip
	BYTE				reserved[74];			// Reserved
}CFG_VIDEO_IN_NORMAL_OPTIONS;



// Flashlight control
typedef struct tagCFG_FLASH_CONTROL
{
	BYTE				byMode;					// Working mode, 0-flash prohibited, 1- always flash, 2- automatic flash
	BYTE				byValue;				// Working value,0-0us, 1-64us, 2-128us, 3-192...15-960us 
	BYTE				byPole;					// Trigger mode, 0-low level, 1- high level, 2- upper edge 3- lower edge
	BYTE                byPreValue;				// Brightness pre-set value range (0~100)
	BYTE				byDutyCycle;			// Duty ratio, 0~100  
	BYTE				byFreqMultiple;			// Frenquency multiple, 0~10 
	BYTE				reserved[122];			// Reserved
}CFG_FLASH_CONTROL;

// Snapshot special config
typedef struct tagCFG_VIDEO_IN_SNAPSHOT_OPTIONS
{
	BYTE				byGainRed;				// Red gain red. Valid when WB is "Custom" mode (0~100)
	BYTE				byGainBlue;				// Green gain. Valid when WB is "Custom" mode  (0~100)
	BYTE				byGainGreen;			// Blue gain setup. Valid when WB is "Custom" mode (0~100)
	BYTE				byExposure;				// Exposure mode; range value depends on device capacity set; 0-automatic, 1- exposure level1,2-exposure level 2.  Mn-1:Max exposure level  n auto exposure of max and min time. n+1 custom exposure time (n==byExposureEn)
	float				fExposureValue1;		// Auto exposure value min limit or manual axposure custom, unit is millisecond (0.1ms~80ms).
	float				fExposureValue2;		// Auto exposure time max limit, unit is millisecond (0.1ms~80ms)
	BYTE				byWhiteBalance;			// WB. 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// Color temperature level. valid when WB is "CustomColorTemperature" . 
	bool				bGainAuto;				// Auto gain 
	BYTE				byGain;					// When GainAuto is true, it is max auto gain limit, otherwise, it is fixed value gain
	BYTE				reversed[112];			// Reserved
} CFG_VIDEO_IN_SNAPSHOT_OPTIONS;

// fish eye mode
typedef enum
{
    CFG_CALIBRATE_MODE_UNKOWN,                  // unknown mode 
    CFG_CALIBRATE_MODE_ORIGIAL,                 // original image mode
    CFG_CALIBRATE_MODE_CONFIG,                  // config mode
    CFG_CALIBRATE_MODE_PANORAMA,                // panorama mode
    CFG_CALIBRATE_MODE_DOUBLEPANORAMA,          // dual panorama mode
    CFG_CALIBRATE_MODE_ORIGIALPLUSTHREEEPTZREGION, // 1+3 mode?ê?§one original fish eyeimage plus 3 EPtz images?ê?
    CFG_CALIBRATE_MODE_SINGLE,                  // single image EPtz mode?ê?§only one EPtz image?ê?
    CFG_CALIBRATE_MODE_FOUREPTZREGION,          // 4 image mode?ê?§4 EPtz control images?ê?
    CFG_CALIBRATE_MODE_NORMAL,                  // normal mode
}CFG_CALIBRATE_MODE;

// fish eye configuration
typedef struct tagCFG_FISH_EYE
{
    CFG_POLYGON         stuCenterPoint;         // center point[0,8192]
	unsigned int        nRadius;                // radius [0,8192]
	float               fDirection;             // direction[0,360.0]
	BYTE                byPlaceHolder;          // place holder	1 roof loading,2 wall loading,3 earth loading.,default 1
    BYTE                byCalibrateMode;        // fish eye mode, see CFG_CALIBRATE_MODE enumeration value
	BYTE				reversed[31];			// reversed
}CFG_FISH_EYE;
// Video input options
typedef struct tagCFG_VIDEO_IN_OPTIONS
{
	BYTE				byBacklight;			// BLC:Range value depends on device capacity set, 0-off, 1-BLC level 1, 2- BLC level 2...n-max BLC level
	BYTE				byDayNightColor;		// Day/night mode; 0-color.1-automatic switch according to the brightness.2- black/white
	BYTE				byWhiteBalance;			// WB. 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// Color temperature level. valid when WB is "CustomColorTemperature" .
	bool				bMirror;				// Mirror
	bool				bFlip;					// Flip
	bool				bIrisAuto;				// Iris automatic
	bool				bInfraRed;				// Auto enable IR compensation light according to the environment.
	BYTE				byGainRed;				// Red gain red. Valid when WB is "Custom" mode (0~100)
	BYTE				byGainBlue;				// Green gain. Valid when WB is "Custom" mode  (0~100)
	BYTE				byGainGreen;			// Blue gain setup. Valid when WB is "Custom" mode (0~100)
	BYTE				byExposure;				// Exposure mode; range value depends on device capacity set; 0-automatic, 1- exposure level1, 2-exposure level 2.  Mn-1:Max exposure level  n auto exposure of max and min time. n+1 custom exposure time (n==byExposureEn)
	float				fExposureValue1;		// Auto exposure value min limit or manual axposure custom, unit is millisecond (0.1ms~80ms).
	float				fExposureValue2;		// Auto exposure time max limit, unit is millisecond (0.1ms~80ms)
	bool				bGainAuto;				// Auto gain 
	BYTE				byGain;					// When gainAuto is true, it is max gain automatic limit, otherwise, it is fixed value gain
	BYTE				bySignalFormat;			// Signal format, 0-Inside (internal input).1-BT656 2-720p 3-1080p  4-1080i  5-1080sF 
	BYTE				byRotate90;				// 0-non-rotate, 1- rotate 90 clockwise, 2-rotate 90 counterclockwise
	float               fExternalSyncPhase;		// External sych phase set up.0~360	
	BYTE                byExternalSync;			// External sync signal input, 0-INT. 1- LL
	BYTE				bySwitchMode;	
	BYTE				byDoubleExposure;		// Double exposure, 0-not use, 1-double exposure with full frame, as image and video differentiated only in parameter  2- double  exposure with half frame, as image and and video differentiated completely
	BYTE                byWideDynamicRange;     // WDR value
	CFG_VIDEO_IN_NIGHT_OPTIONS stuNightOptions;	// Night config
	CFG_FLASH_CONTROL	stuFlash;				// Flashling config 
	CFG_VIDEO_IN_SNAPSHOT_OPTIONS stuSnapshot;	// Snapshot option, doule exposure only
	CFG_FISH_EYE        stuFishEye;             // fish eye
	BYTE                byFocusMode;            // 0-off?ê?1-easy focus?ê?2-auto focus
	BYTE                reserved[28];           // Reserved
	BYTE				byGainMin;				// min gain
	BYTE				byGainMax;				// max gain
	BYTE				byAntiFlicker;			// prevent flashing mode 0-Outdoor 1-50Hz prevent flashing 2-60Hz prevent flashing
	BYTE				byExposureMode;         // exposure mode, effective exposure levels for automatic exposure,0-auto,1-plus,4-manual
	BYTE                byGlareInhibition;		// glare inhibition[1~100] 0-close
	CFG_RECT			stuBacklightRegion;     // back light region          
	CFG_VIDEO_IN_NORMAL_OPTIONS stuNormalOptions;//normal option
} CFG_VIDEO_IN_OPTIONS;

// RTSP input parameter and output configuration structure
typedef struct tagCFG_MULTICAST_INFO
{
	int  nStructSize;
	bool abStreamType;
	BYTE byReserved[3];
	BOOL bEnable;      // Enable or not 
	char szMulticastAddr[MAX_ADDRESS_LEN]; //Multicast address
	int  nPort;        //Multicast Port
	char szLocalAddr[MAX_ADDRESS_LEN];   //Single cast address. It is to pecify an detailed network card.
	int  nChannelID;   //Channel ID
	int  nStreamType;  // Stream type  0-main stream, 1- extra stream1, 2-extra stream2, 3- extra stream3
}CFG_MULTICAST_INFO;

typedef struct tagCFG_MULTICASTS_INFO
{
	int nStructSize;
	CFG_MULTICAST_INFO stuMultiInfo[MAX_CHAN_NUM]; //Max multcast channel number
	int nCount;                                    //Valid array amount
}CFG_MULTICASTS_INFO;

typedef struct tagCFG_RTSP_INFO_IN
{
	int         nStructSize;
	BOOL        bEnable;       // Whole function enabled or not 
	int         nPort;         // RTSP service ort
	int         nRtpStartPort; // RTP start port
	int         nRtpEndPort;   // RTP end port
	BOOL        bHttpEnable;   // RtspOverHttp enable
	int         nHttpPort;     // RtspOverHttp pOrt
}CFG_RTSP_INFO_IN;

typedef struct tagCFG_RTSP_INFO_OUT
{
	int         nStructSize;
	BOOL        bEnable;       // Whole function enabled or not 
	int         nPort;         // RTSP port
	int         nRtpStartPort; // RTP start port
	int         nRtpEndPort;   // RTP end port
	BOOL        bHttpEnable;   // RtspOverHttp Enable
	int         nHttpPort;     // RtspOverHttp port
}CFG_RTSP_INFO_OUT;

typedef struct tagCFG_MULTICASTS_INFO_IN
{
	int                  nStructSize;
	CFG_MULTICAST_INFO   *pTSMulticast;   //TS multicast config
	int                  nTSCount;        //Valid TS array amount
	CFG_MULTICAST_INFO   *pRTPMulticast;  //RTP multicast config
	int                  nRTPCount;       //Valid RTP amount
	CFG_MULTICAST_INFO   *pDHIIMulticast; //DHII multicast config
	int                  nDHIICount;      //Valid DHII array amount
    CFG_MULTICAST_INFO   *pRTPAudio;      //RTP audio group multi-cast config
    int                  nRTPAudioCount;  //valid RTP audio group number
}CFG_MULTICASTS_INFO_IN;

typedef struct tagCFG_MULTICASTS_INFO_OUT
{
	int                  nStructSize;
	CFG_MULTICASTS_INFO  stuTSMulticast;   //TS multicast config
	CFG_MULTICASTS_INFO  stuRTPMulticast;  //RTP multicast config
	CFG_MULTICASTS_INFO  stuDHIIMulticast; //DHII multicast config
    CFG_MULTICASTS_INFO  stuRTPAudioMulticast; // Audio RTP Multicast Configuration
}CFG_MULTICASTS_INFO_OUT;

typedef struct tagCFG_ACTIVEUSER_INFO
{
	int nStructSize;
	int nUserID;                         //Active user ID, normally dialogue ID
	char szUser[MAX_USERNAME_LEN];       //Username
	char szGroupName[MAX_USERNAME_LEN];  //Group name
	int  nGroupLevel;                    // Group level
	char szClientType[MAX_USERNAME_LEN]; // Client-end type
	char szClientAddr[MAX_ADDRESS_LEN];  // Client-end IP address
	CFG_NET_TIME  stuLoginTime;              // Login time
}CFG_ACTIVEUSER_INFO;

typedef struct tagCFG_ACTIVEALLUSER_INFO
{
	int nStructSize;
	int nCount;                                                //Valid group number
	CFG_ACTIVEUSER_INFO stuActiveUserInfo[MAX_ACTIVEUSER_NUM]; // Max active user list
}CFG_ACTIVEALLUSER_INFO;

typedef struct tagCFG_NET_TIME_EX
{
	DWORD				dwYear;					// YEAR
	DWORD				dwMonth;				// month
	DWORD				dwDay;					// day
	DWORD				dwHour;					// hour
	DWORD				dwMinute;				// minute
	DWORD				dwSecond;				// second
	DWORD               dwMillisecond;          // millisecond
	DWORD               dwReserved[2];          // reserved field
} CFG_NET_TIME_EX;

//Get video statistic summary info structure
typedef struct tagCFG_CFG_VIDEOSATA_SUMMARY_INFO
{
	int         nStructSize;
	int         nChannelID;               //Statistics Channel ID
	char        szRuleName[MAX_NAME_LEN]; //rule name
	CFG_NET_TIME_EX stuStatTime;          // statistic time, converse to UTC
	int         nEnteredTotal;            //Go to total
	int         nEnteredToday;            //Entered in current today
	int         nEnteredMonth;            //Entered in current month
	int         nEnteredYear;             //Entered in current year
	int         nEnteredDaily;            //Max Entered daily
	int         nExitedTotal;             //Exited total
	int         nExitedToday;             //Exited in today
	int         nExitedMonth;             //Exited in current month
	int         nExitedYear;              //Exited in current year
	int         nExitedDaily;             //Max exited daily
	int         nAvgTotal;                //average total(excluding 0)
	int         nAvgToday;                //average in current today
	int         nAvgMonth;                //average in current month
	int         nAvgYear;                 //average in current year         
	int         nMaxTotal;                //Max in total(excluding 0)
	int         nMaxToday;                //Max in today
	int         nMaxMonth;                //Max in current month
	int         nMaxYear;                 //Max in current year
}CFG_VIDEOSATA_SUMMARY_INFO;

// Single scene track structure
typedef struct tagCFG_SINGLESCENE
{
	int                 nStructSize;
	int					nSingleAlarmDelay;					//Alarm delay  1~600s  
	int					nSinglePresetID;					// Preset ID 1~255(-1 means there is no definition)
}CFG_SINGLESCENE;
// Tour structure
typedef struct tagCFG_TOURPATH
{
	int                 nStructSize;
	int					nMultiPresetID;						//scene preset ID
	int					nMultiDuration;						//tay duration 30~900s
}CFG_TOURPATH;

//multi-scene tracking priority mode
typedef enum tagCFG_MULTSCENE_PRIOR_MODE
{
    EM_MULTSCENE_PRIOR_MODE_UNKNOW = 0  , 
    EM_MULTSCENE_PRIOR_MODE_DETECT      , // detection first, wait until system detection is complete and switch scene
    EM_MULTSCENE_PRIOR_MODE_SWITCH      , // switch first, directly stop system detection, switch to next scene
}CFG_MULTSCENE_PRIOR_MODE;

// Multiscene track structure
typedef struct tagCFG_MULTISCENE
{
	int                 nStructSize;
	int					nMultiAlarmDelay;					    //Alarm delay: 1~600s
	int					nTourPathCount;						    //Tour path count
	CFG_TOURPATH	    stuMultiTourPath[MAX_TRACKSCENE_NUM];   //Tour 
    CFG_MULTSCENE_PRIOR_MODE    emPriorMode;                            // Priority mode
}CFG_MULTISCENE;
// Full scene track structure
typedef struct tagCFG_FULLSCENE
{
	int                 nStructSize;
	int					nFullAlarmDelay;					//Alarm delay 1~600s
	int					nFullPresetID;						//Preset ID, full scene track preset is 0, user cannot set
	int					nFullDuration;						// Full scene track duration, 0s: track all along; 1~300: tracking duration
}CFG_FULLSCENE;
// Limited parameter structure
typedef struct tag_CFG_POSITION_LIMIT
{
	int                 nStructSize;
	BOOL				bEnable;							//limited parameter enabled
	int					nType;								//Limited value representation: 0: saved with limit set up by PTZ, limit is meaningless 
	                                                        //1: Limit by angle (unit0.1), used in scene limit
	int					nTop;								//Top limit,0~900:(unit 0.1 degree) 
	int					nBottom;							//Bottom limit,0~900:(unit 0.1 degree) 
	int					nLeft;								//Left limit,0~3600:(unit 0.1 degree) 
	int					nRight;								//Right limit,0~3600:(unit 0.1 degree) 
}CFG_POSITION_LIMIT;

// Self-set mark direction 
typedef enum tagCFG_SCENE_DIRECTION_INFO
{
    EM_SCENE_DIRECTION_UNKNOW =0    , 
    EM_SCENE_DIRECTION_APPROACH     ,   //up
    EM_SCENE_DIRECTION_LEAVE        ,   //down
    EM_SCENE_DIRECTION_BOTH         ,   //dual-way
    EM_SCENE_DIRECTION_EAST2WEST    ,   //from E to W
    EM_SCENE_DIRECTION_WEST2EAST    ,   //from W to E
    EM_SCENE_DIRECTION_SOUTH2NORTH  ,   //from S to N
    EM_SCENE_DIRECTION_NORTH2SOUTH  ,   //from N to S
    EM_SCENE_DIRECTION_OTHER        ,   //other
}CFG_SCENE_DIRECTION_INFO;

//  Scene info structure
typedef struct tagCFG_SCENE
{
	int                    nStructSize;
	int					   nScenePresetID;						//Scene preset, 1~255, use preset ID to connect corresponding rule
	char			       szSceneName[MAX_NAME_LEN];		    //Scene name
	int					   nSceneDuration;						//Track duration: 0s: track all along; 1~300: track duration
	double		           dSceneMaxZoom;					    //All in 0~1, null require global MaxZoom value
	CFG_POSITION_LIMIT	   stuPositionLimit;                    //limit profile
 	int                    nSceneRegression;       
    CFG_SCENE_DIRECTION_INFO    emDirectionInfo;                    /// Mark set their own direction
}CFG_SCENE;
// Intelligence track scene config structure
typedef enum tagCFG_INTELLI_TRACE_MODE
{
    EM_INTELLI_TRACE_MODE_UNKNOW = 0 ,
    EM_INTELLI_TRACE_MODE_INDOOR     , //indoor tracking (short time)
    EM_INTELLI_TRACE_MODE_OUTDOOR    , //ourdoor tracking
    EM_INTELLI_TRACE_MODE_CLASSROOM  , //classroom tracking(long time and need to mark object)
}CFG_INTELLI_TRACE_MODE;
typedef struct tagCFG_INTELLITRACKSCENE_INFO
{
	int               nStructSize;
	BOOL		      bEnableTrack;				         //intelligence track enabled
	int				  nTrackType;						 //0, alarm track; 1, manual track
	double			  dMaxZoom;							 //Max track rate, all in 0~1, null mean no limit
	char			  szCategory[MAX_NAME_LEN];		     //Current track type "SingleScene": single scene track; "MultiScene": multiscene track; "FullScene": full scene track
	CFG_SINGLESCENE   stuSingleTrack;					 //single scene track
	CFG_MULTISCENE	  stuMultiTrack;	                 //multiscene track
	CFG_FULLSCENE	  stuFullTrack;						 //full scene track
	int				  nSceneCount;						 //Supported scene amount
	CFG_SCENE		  stuScene[MAX_TRACKSCENE_NUM];	     //Scene list
    double                  dCameraHeight;                     //vertical distance from camera to ground, unit: meter
    int                     nIdleDelay;                        //idle waiting time, unit:s (as when user stops device operation, idle delay time until intelligence continue to be effective)
    CFG_INTELLI_TRACE_MODE  emTraceMode;                       //tracking mode
}CFG_INTELLITRACKSCENE_INFO;

// fish eye detailed config

#define   CFG_MAX_FISHEYE_WINDOW_NUM               8         // max fish eye window number
#define   CFG_MAX_FISHEYE_MODE_NUM                 8         // max fish eye mode number  
// fish eye window location info
typedef struct tagCFG_FISHEYE_WINDOW_INFO
{
    DWORD             dwWindowID;                        // window ID
    int               nFocusX;                           // EPtz?ê?§e-PTZ?ê?focus x axis
    int               nFocusY;                           // EPtz (e-PTZ?ê?focus y axis   
    int               nHorizontalAngle;                  // EPtz h-angle
    int               nVerticalAngle;                    // EPtz v-angle
}CFG_FISHEYE_WINDOW_INFO;

// fish eye mode window location info
typedef struct tagCFG_FISHEYE_MODE_INFO
{
    int                nModeType;                        // mode type?ê?see CFG_CALIBRATE_MODE
    int                nWindowNum;                       // current mode window number
    CFG_FISHEYE_WINDOW_INFO stuWindwos[CFG_MAX_FISHEYE_WINDOW_NUM]; // see window info 
}CFG_FISHEYE_MODE_INFO;

typedef struct tagCFG_FISHEYE_DETAIL_INFO
{
    int                nModeNum;                         // module number
    CFG_FISHEYE_MODE_INFO stuModes[CFG_MAX_FISHEYE_MODE_NUM]; // detailed module info  
}CFG_FISHEYE_DETAIL_INFO;

// Platform issue call no-response transfer config list
#define   CFG_MAX_NOANSWER_FORWARD_GROUP_NUM                    32         // Max no-response front list number
#define   CFG_MAX_FORWARD_NUMBERS_NUM                           32         // Max no-response transfer number

// No-response transfer config
typedef struct tagCFG_VT_NOANSWER_FORWARD_GROUP
{
    char                    szRoomNumber[CFG_COMMON_STRING_32];          // Called number
    int                     nForwardNumbersNum;                          // No-response transfer number
    char                    szForwardNumbers[CFG_MAX_FORWARD_NUMBERS_NUM][CFG_COMMON_STRING_64]; // No-response transfer number list  
}CFG_VT_NOANSWER_FORWARD_GROUP;

// Platform issue call no-response transfer config list info 
typedef struct tagCFG_VT_NOANSWER_FORWARD_INFO
{
    BOOL                            bEnable;                                        // No-response transfer enable
    int                             nGroupNum;                                      // No-response transfer config list valid number?ê?range?êo0 ~ CFG_MAX_NOANSWER_FORWARD_GROUP_NUM
    CFG_VT_NOANSWER_FORWARD_GROUP   stuGroups[CFG_MAX_NOANSWER_FORWARD_GROUP_NUM];  // No-response transfer config list  
}CFG_VT_NOANSWER_FORWARD_INFO;

// VTO call config
typedef struct tagCFG_VTO_CALL_INFO
{
    BOOL                            bAreaEnable;                                        // Cross-zone network enable
    char                            szAreaNumber[CFG_COMMON_STRING_32];                  // Zone encode
    BOOL                            bMiddleNumberCallEnable;                            // Middle no. call switch
    char                            szVTHMiddleNumberPrefix[CFG_COMMON_STRING_16];       // VTH middle no. prefix?ê?fixed length 4 bits
    char                            szVTHLongNumberPrefix[CFG_COMMON_STRING_32];         // VTH long no. prefix?ê?fixed length 8 bits
    char                            szVTOShortNumber[CFG_COMMON_STRING_16];              // VTO short no.?ê?fixed length 4 bits
    char                            szVTOMiddleNumberPrefix[CFG_COMMON_STRING_16];       // VTO middle no. prefix?ê?fixed length 4 bits
    char                            szVTOLongNumbrPrefix[CFG_COMMON_STRING_32];          // VTO long no. prefix?ê?fixed length 12 bits    
	char                            szVTSLongNumber[CFG_COMMON_STRING_32];               // VTS long no.?ê?fixed length 18 bits
    char                            szVillaCallVTHNum[CFG_COMMON_STRING_32];             // Villa station call no.
}CFG_VTO_CALL_INFO;

/************************Work state**********************************/

// Snapshot mode
typedef enum tagCFG_TRAFFIC_SNAP_MODE
{
	TRAFFIC_SNAP_MODE_AUTO = 0,				       // Automatic snapshot
	TRAFFIC_SNAP_MODE_COIL,				           // Loop snapshot
	TRAFFIC_SNAP_MODE_COIL_PICANALYSIS,		       // Loop snapshot, image analysis
	TRAFFIC_SNAP_MODE_STREAM,				       // Video snapshot
	TRAFFIC_SNAP_MODE_STREAM_IDENTIFY,		       // Video snapshot and identify
	TRAFFIC_SNAP_MODE_MIX_IDENTIFY,		           // mix snapshot and identify
} CFG_TRAFFIC_SNAP_MODE;

// Device work state info
typedef struct tagCFG_TRAFFIC_WORKSTATE_INFO
{
	int                     nChannelID;  // Channel ID
	CFG_TRAFFIC_SNAP_MODE   emSnapMode;  // Snapshot mode
	int                     nMatchMode;  // Snapshot match mode: 0-non real time, alarm before snapshot, snapshot frame is not same as alarm frame; 1- real time match, snapshot frame is same as alarm frame
}CFG_TRAFFIC_WORKSTATE_INFO; 

// get device working state(CFG_CAP_CMD_DEVICE_STATE corresponding structure)
typedef struct tagCFG_TRAFFIC_DEVICE_STATUS
{
	char                 szType[MAX_PATH];          // device type	support:"Radar","Detector","SigDetector","StroboscopicLamp"," FlashLamp"
	char                 szSerialNo[MAX_PATH];      // device num
	char                 szVendor[MAX_PATH];        // vendor
	int                  nWokingState;              // working state	0-fault,1-natural
}CFG_TRAFFIC_DEVICE_STATUS;

typedef struct tagCFG_CAP_TRAFFIC_DEVICE_STATUS
{
	int                        nStatus;             // stuStatus the actual number
	CFG_TRAFFIC_DEVICE_STATUS  stuStatus[MAX_STATUS_NUM];
}CFG_CAP_TRAFFIC_DEVICE_STATUS;

/************************Record group config**********************************/

//Storage group info
typedef struct tagCFG_STORAGEGROUP_INFO
{
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];   // Storage group name
	BYTE*                 byDisks;                                 // Disk SN buffer
	int                   nBufSize;                                // Buffer byDisks length
	int                   nDiskNum;                                // Storage Disk number
	int                   nGroupIndex;                             // Storage Group SN(1~max group)
}CFG_STORAGEGROUP_INFO;

// Record-Storage group  corresponding info
typedef struct tagCFG_RECORDTOGROUP_INFO
{
	int                   nChannelID;                               //  Channel ID
	BOOL                  bEnable;                                  //  Enable                    
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];    // Storage group name, read only
	int                   nGroupIndex;                              // Storage group SN (1~max group, 0~none), via profile connection with CFG_STORAGE_GROUP_INFO
}CFG_RECORDTOGROUP_INFO; 

enum EM_STORAGEPOINT_TYPE
{
       	EM_STORAGE_TIMINGRECORD,        //Schedule record storage point type
		EM_STORAGE_MANUALRECORD,        //Manual record  storage point type
		EM_STORAGE_VIDEODETECTRECORD,   //Video detection record  storage point type
		EM_STORAGE_ALARMRECORD,         //Alarm record storage point type
		EM_STORAGE_CARDRECORD,          //Card record storage point type
		EM_STORAGE_EVENTRECORD,         // Other event record storage point type             
		EM_STORAGE_TIMINGSNAPSHOT,      // Schedule snapshot storage point type
		EM_STORAGE_MANUALSNAPSHOT,      // Manual snapshot storage point type
		EM_STORAGE_VIDEODETECTSNAPSHOT, // Video detection snapshot storage point type
		EM_STORAGE_ALARMSNAPSHOT,       // Alarm snapshot storage point type
		EM_STORAGE_CARDSNAPSHOT,        // Card snapshot storage point type
		EM_STORAGE_EVENTSNAPSHOT,       // Other vent snapshot storage point type
};
// Storage point info
typedef struct tagCFG_STORAGEPOINT_INFO
{
	DWORD dwSize;
	EM_STORAGEPOINT_TYPE emStoragePointType;// storage point type
	char nLocalDir;     					//local work directory name, vacancy means does not login the local-end. 
	char szCompressDir[MAX_DIRECTORY_LEN];  //real compress directory, vacancy means do not use real-time compression. 
	char szRedundantDir[MAX_DIRECTORY_LEN]; //redundant work directory name, vacancy means there is no redundancy record.  
	char szRemoteDir[MAX_DIRECTORY_LEN];   //remote work directory name, vacancy means  do not login the remote path. 
	BOOL bAutoSync;                         //After remote storage net failure resumed, automatically synchronize local data to remote storage or not 
	UINT nAutoSyncRange;                    //Starting when net resumed,  it is the data synchronization period forward. 0 represents synchronize all data
	BOOL bLocalEmergency;                   //When remote directory cannot be accessed, save to local directory or not  
	UINT nCompressBefore;                   //Set to compress file before which date. 
}CFG_STORAGEPOINT_INFO;

//Video storage point mapping info
typedef struct tagCFG_RECORDTOSTORAGEPOINT_INFO
{
	int	nStoragePointNum;                                        //storage point number
	CFG_STORAGEPOINT_INFO stStoragePoints[MAX_STORAGEPOINT_NUM]; // storage point info
}CFG_RECORDTOSTORAGEPOINT_INFO;

//iscsi direct storage, metadata server interface
typedef struct __tagCFG_METADATA_SERVER
{
	DWORD       nStructSize;
	BOOL        bEnable;                              //Enable button
	char        szAddress[MAX_ADDRESS_LEN];           //IP afddress or network name
	DWORD       dwPort;                               // port number
	char        szUserName[MAX_USERNAME_LEN];         // Username
	char        szPassword[MAX_PASSWORD_LEN];         // password
	char        szDeviceID[MAX_REMOTEDEVICENAME_LEN]; //Allocate ID to all metadata server, device identified by this ID
}CFG_METADATA_SERVER;

// good weight configuration
typedef struct __tagCFG_GOOD_WEIGHT_INFO
{
	DWORD		dwMaxGoodsWeight;					// max goods weight(kg)
	DWORD		dwMinGoodsWeight;					// max goods weight(kg)
	DWORD		dwSelfWeight;						// self weight(kg)
	DWORD		dwStandardWeight;					// standard weight(kg)
	DWORD		dwAlarmWeight;						// alarm weight(kg)
	int			nCheckTime;							// check time(s)
} CFG_GOOD_WEIGHT_INFO;

// cap focus info
typedef struct tagCFG_CAP_FOCUS_STATUS
{
	int					nAutofocusPeak;							// peak crrent AF, auxiliary focus on effective
	double		        dFocus;									// focus position,normalized to 0~1
	double		        dZoom;									// magnification,normalized to 0~1
	int					nStatus;								// focus status, 0 able 1 is af
}CFG_CAP_FOCUS_STATUS;

//support ptz capacity
typedef struct tagCFG_CAP_PTZ_ENABLEINFO 
{
	BOOL bEnable;												//the channel support ptz or not
	
}CFG_CAP_PTZ_ENABLEINFO;


// net app capacity
typedef struct tagCFG_CAP_NETAPP
{
	int                nNetCardCount;                           // card count
	int                nNetTypeNumber;                          // number of net type
	char               szNetType[MAX_NET_TYPE_NUM][MAX_NET_TYPE_LEN]; // net type, "PPPoE","WIFI","3G","LAN"
}CFG_CAP_NETAPP;

///////////////////////////////////The 3rd protocol newly added contents/////////////////////////////////////// 
// Record mode
struct AV_CFG_RecordMode
{
	AV_int32			nStructSize;
	AV_int32			nMode;							// record mode, 0-schedule, 1- manual, 2- off
    AV_int32			nModeExtra1;					// Sub stream record mode, 0-auto, 1-manual, 2-OFF
};

// Channel name
struct AV_CFG_ChannelName
{
	AV_int32			nStructSize;
	AV_int32			nSerial;						// Camera unique SN
	char				szName[CFG_MAX_CHANNEL_NAME_LEN];//Channel name
};

// Video output attribute
struct AV_CFG_VideoOutAttr
{
	AV_int32			nStructSize;
	AV_int32			nMarginLeft;					// left margin, ratio 0~100
	AV_int32			nMarginTop;						// 0~100 upper margin, ratio 0~100
	AV_int32			nMarginRight;					// right margin, ratio 0~100
	AV_int32			nMarginBottom;					// lower margin, ratio 0~100
	AV_int32			nBrightness;					// brightness 0~100
	AV_int32			nContrast;						// Contrast 0~100
	AV_int32			nSaturation;					// Saturation 0~100
	AV_int32			nHue;							// Hue 0~100
	AV_int32			nWidth;							// Pan resolution 0~100
	AV_int32			nHeight;						// Vertical resolution  0~100
	AV_int32			nBPP;							// Color depth 0~100
	AV_int32			nFormat;						// 0-Auto, 1-TV, 2-VGA, 3-DVI 
	AV_int32			nRefreshRate;					// Refresh frequency
	AV_BOOL				bIQIMode;						// Output image enhancement
	AV_int32			nScanFormat;					// Scanning mode, 0 - Progressive ,1 - interlaced
};

//Period
struct AV_CFG_TimeSection
{
	AV_int32			nStructSize;
	AV_int32			nMask;							// Sub Mask
	AV_int32			nBeginHour;						// Begin hour
	AV_int32			nBeginMinute;
	AV_int32			nBeginSecond;
	AV_int32			nEndHour;						// End hour
	AV_int32			nEndMinute;
	AV_int32			nEndSecond;
};

//Remote channel
struct AV_CFG_RemoteChannel 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// enable
	char				szDeviceID[AV_CFG_Device_ID_Len];	// device ID
	AV_int32			nChannel;						// channel number
};

//Display source 
struct AV_CFG_DisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowID;						// window ID
	AV_BOOL				bEnable;						// enable
	char				szDeviceID[AV_CFG_Device_ID_Len];//device ID
	AV_int32			nVideoChannel;					// video channel
	AV_int32			nVideoStream;					// video bit stream
	AV_int32			nAudioChannle;					// audio channel
	AV_int32			nAudioStream;					// audio bit stream
	AV_BOOL				bVideoEnable;			        // means that the window is valid
};

// Channel display source
struct AV_CFG_ChannelDisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowNum;						// split Window number
	AV_CFG_DisplaySource stuSource[AV_CFG_Max_Split_Window];// split Window source
};

// Group enabled state of split mode under tour 
struct AV_CFG_MonitorTourMask
{
	AV_int32			nStructSize;
	CFG_SPLITMODE		emSplitMode;					// split mode
	AV_int32			nGroupNum;						// group number
	AV_int32			nGroup[AV_CFG_Max_Split_Group];	// tour group  under split mode 
};

// Monitor Tour 
struct AV_CFG_MonitorTour 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// enable
	AV_int32			nInterval;						// interval, 5~120s
	AV_int32			nSplitMaskNum;					// split and group enable amount
	AV_CFG_MonitorTourMask	stuSplitMask[AV_CFG_Max_Split_Mode];// group enabled state under each split mode
	AV_int32			nCollectionNum;					// favorite number
	char				szCollection[AV_CFG_Monitor_Favorite_In_Channel][AV_CFG_Monitor_Favorite_Name_Len];// favorite name
};

// Monitor favorite number
struct AV_CFG_MonitorFavorite 
{
	AV_int32			nStructSize;
	AV_BOOL				bDir;										// be directory or not	
	char				szName[AV_CFG_Monitor_Favorite_Name_Len];	//Name
	char				szPath[AV_CFG_Max_Path];					// Path to directory, format as : .name1.name2.name3
	CFG_SPLITMODE	emMode;										// split mode
	AV_int32			nWindowNum;									// window number
	AV_CFG_DisplaySource stuWindow[AV_CFG_Max_Monitor_Favorite_Window];	// Window display source
};

// Monitor channel favorite collection
struct AV_CFG_MonitorCollection 
{
	AV_int32			nStructSize;
	AV_CFG_MonitorFavorite*	pstuFavorite;				// Video favorite group
	AV_int32			nMaxCount;						// Video favorite group size
	AV_int32			nRetCount;						// return video favorite number
};

// Raid info
struct AV_CFG_Raid 
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Raid_Name_Len];	// name
	AV_int32			nLevel;							// level
	AV_int32			nMemberNum;						// disk member number
	char				szMembers[AV_CFG_Max_Rail_Member][AV_CFG_Max_Path];	// disk member
};

// Record source
struct AV_CFG_RecordSource
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// enable
	char				szDeviceID[AV_CFG_Device_ID_Len];// device ID
	AV_int32			nVideoChannel;					// video channel
	AV_int32			nVideoStream;					// video stream
	AV_int32			nAudioChannle;					// audio channel
	AV_int32			nAudioStream;					// audio stream
};

// Encode format, include audio and video
struct AV_CFG_EncodeFormat
{
	AV_int32			nStructSize;
	AV_BOOL				bAudioEnable;					// audio enable
	AV_int32			nAudioBitRate;					// audio Bit rate
	CFG_AUDIO_FORMAT	emAudioCompression;				// Audio compression format
	AV_int32			nAudioDepth;					// audio sampling depth
	AV_int32			nAudioFrequency;				// audio sampling frenquency
	AV_int32			nAudioMode;						// audio encode mode
	AV_int32			nAudioPack;						// audio pack mode. 0-DHAV, 1-PS 

	AV_BOOL				bVideoEnable;					// video enable
	AV_int32			nVideoBitRate;					// video Bit rate
	CFG_BITRATE_CONTROL	emVideoBitRateControl;			// Bit Rate Control mode
	CFG_VIDEO_COMPRESSION emVideoCompression;			// video compression mode
	AV_int32			nVideoFPS;						// video frame rate
	AV_int32			nVideoGOP;						// video I frame interval
	AV_int32			nVideoWidth;					// Video width
	AV_int32			nVideoHeight;					// video height
	CFG_IMAGE_QUALITY	emVideoQuality;					// video quality
	AV_int32			nVideoPack;						//  video pack mode. 0-DHAV, 1-PS	
};

// Encode Config
struct AV_CFG_Encode 
{
	AV_int32			nStructSize;
	AV_CFG_EncodeFormat stuMainFormat[AV_CFG_Max_Encode_Main_Format];	// Main stream:general encode, motion detect encode, alarm encode.  
	AV_CFG_EncodeFormat	stuExtraFormat[AV_CFG_Max_Encode_Extra_Format];	// Extra stream:extram stream 1,extra stream 2, extra stream 3.
	AV_CFG_EncodeFormat	stuSnapFormat[AV_CFG_Max_Encode_Snap_Format];	// Snap:general snap,motion detect snap,alarm snap. 
};

// Video input color config. Each input video has several corresponding color setups. 
struct AV_CFG_VideoColor 
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection	stuTimeSection;					// Period
	AV_int32			nBrightness;					// Brightness, 1~100
	AV_int32			nContrast;						// Contrastness, 1~100
	AV_int32			nSaturation;					// Saturation, 1~100
	AV_int32			nHue;							// Hue, 1~100
	AV_int32			nGamma;							// plus, 0~100
};


// Channel video input color config 
struct AV_CFG_ChannelVideoColor 
{
	AV_int32			nStructSize;
	AV_int32			nColorNum;						// Channel color config amount
	AV_CFG_VideoColor	stuColor[AV_CFG_Max_VideoColor];// Channel color config. Each input video has several corresponding color setups.
};

// Color 
struct AV_CFG_Color
{
	AV_int32			nStructSize;
	AV_int32			nRed;							// Red
	AV_int32			nGreen;							// Green
	AV_int32			nBlue;							// Blue
	AV_int32			nAlpha;							// Transparent 
};

// Zone
struct AV_CFG_Rect 
{
	AV_int32			nStructSize;
	AV_int32			nLeft;
	AV_int32			nTop;
	AV_int32			nRight;
	AV_int32			nBottom;	
};

// Encode widget-Privacy mask setup
struct AV_CFG_VideoWidgetCover 
{
	AV_int32			nStructSize;	
	AV_BOOL				bEncodeBlend;					// Overlay to main stream 
	AV_BOOL				bEncodeBlendExtra1;				// Overlay to extra stream 1
	AV_BOOL				bEncodeBlendExtra2;				// Overlay to extra stream 2
	AV_BOOL				bEncodeBlendExtra3;				// Overlay to extra stream 3
	AV_BOOL				bEncodeBlendSnapshot;			// Overlay to snap
	AV_CFG_Color		stuFrontColor;					// Foreground color
	AV_CFG_Color		stuBackColor;					// Background color 
	AV_CFG_Rect			stuRect;						// Zone. The coordinates value ranges from  0 to 8191
	AV_BOOL				bPreviewBlend;					// Overlay to preview mode
};

// Channel title alignment info 
typedef enum tagEM_TITLE_TEXT_ALIGN
{
    EM_TEXT_ALIGN_INVALID,                              // Invalid alignment mathod
    EM_TEXT_ALIGN_LEFT,                                 // Left alignment 
    EM_TEXT_ALIGN_XCENTER,                              // X coordinate alignment 
    EM_TEXT_ALIGN_YCENTER,                              // Y coordinate alignment 
    EM_TEXT_ALIGN_CENTER,                               // Center
    EM_TEXT_ALIGN_RIGHT,                                // Right alignment 
    EM_TEXT_ALIGN_TOP,                                  // By top alignment 
    EM_TEXT_ALIGN_BOTTOM,                               // By bottom alignment 
    EM_TEXT_ALIGN_LEFTTOP,                              // By upper left alignment 
    EM_TEXT_ALIGN_CHANGELINE,                           // Next row alignment 
}EM_TITLE_TEXT_ALIGN;

// Encode widget-channel title 
struct AV_CFG_VideoWidgetChannelTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// Overlay to main stream 
	AV_BOOL				bEncodeBlendExtra1;				// Overlay to extra stream 1
	AV_BOOL				bEncodeBlendExtra2;				// Overlay to extra stream 2
	AV_BOOL				bEncodeBlendExtra3;				// Overlay to extra stream 3
	AV_BOOL				bEncodeBlendSnapshot;			// Add to snap
	AV_CFG_Color		stuFrontColor;					// Foreground color
	AV_CFG_Color		stuBackColor;					// Background color 
	AV_CFG_Rect			stuRect;						// Zone. The coordinates value ranges from  0 to 8191. Only use left value and top value.The point (left,top) shall be the same as the point(right,bottom).
	AV_BOOL				bPreviewBlend;					// Overlay to preview mode
};

// Encode widget-Time title 
struct AV_CFG_VideoWidgetTimeTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// Overlay to main stream 
	AV_BOOL				bEncodeBlendExtra1;				// Overlay to extra stream 1
	AV_BOOL				bEncodeBlendExtra2;				// Overlay to extra stream 2
	AV_BOOL				bEncodeBlendExtra3;				// Overlay to extra stream 3
	AV_BOOL				bEncodeBlendSnapshot;			// Overlay to snap
	AV_CFG_Color		stuFrontColor;					// Foreground color
	AV_CFG_Color		stuBackColor;					// Background color 
	AV_CFG_Rect			stuRect;						// Zone. The coordinates value ranges from  0 to 8191. Only use left value and top value.The point (left,top) shall be the same as the point(right,bottom).
	AV_BOOL				bShowWeek;						// Display week or not 
	AV_BOOL				bPreviewBlend;					// Overlay to preview mode
};
	
// Encode widget-Self-defined title
struct AV_CFG_VideoWidgetCustomTitle 
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// Overlay to main stream 
	AV_BOOL				bEncodeBlendExtra1;				// Overlay to extra stream 1
	AV_BOOL				bEncodeBlendExtra2;				// Overlay to extra stream 2
	AV_BOOL				bEncodeBlendExtra3;				// Overlay to extra stream 3
	AV_BOOL				bEncodeBlendSnapshot;			// Overlay to snap
	AV_CFG_Color		stuFrontColor;					//Foreground color
	AV_CFG_Color		stuBackColor;					// Background color 
	AV_CFG_Rect			stuRect;						// Zone. The coordinates value ranges from  0 to 8191. Only use left value and top value.The point (left,top) shall be the same as the point(right,bottom).
	char				szText[AV_CFG_Custom_Title_Len];// Title contents
	AV_BOOL				bPreviewBlend;					// Overlay to preview mode
    char                szType[AV_CFG_Custom_TitleType_Len];// Title type "Rtinfo" real-time recorder information, "Custom" custom overlay, temperature and humidity overlay, "Title": credit information "Check" check code
                                                            // Geography info "Geography"  ATM card info "ATMCardInfo" Camera ID "CameraID" 
    EM_TITLE_TEXT_ALIGN emTextAlign;                    // Title alignment method
};

//  Encoding object - overlay sensor information - superimposed Description
struct AV_CFG_VideoWidgetSensorInfo_Description 
{
	AV_int32			nStructSize;
	AV_int32			nSensorID;						// Need to describe the sensor ID (analog alarm channel number) 
};

// Encoding object - overlay sensor information
struct AV_CFG_VideoWidgetSensorInfo
{
	AV_int32			nStructSize;
	AV_BOOL				bPreviewBlend;					// Overlay the preview video 
	AV_BOOL				bEncodeBlend;					// Stack to the main stream of video coding 
	AV_CFG_Rect			stuRect;						//Area, coordinates ranging from 0 to 8191
	AV_int32			nDescriptionNum;				// The Description number of stacking area 
	AV_CFG_VideoWidgetSensorInfo_Description stuDescription[AV_CFG_Max_Description_Num];// Stacking area description information 
};

// Video encode widget config
struct AV_CFG_VideoWidget 
{
	AV_int32						nStructSize;
	AV_CFG_VideoWidgetChannelTitle	stuChannelTitle;	// Channel title
	AV_CFG_VideoWidgetTimeTitle		stuTimeTitle;		// Time title
	AV_int32						nConverNum;			// Privacy mask zone amount
	AV_CFG_VideoWidgetCover			stuCovers[AV_CFG_Max_Video_Widget_Cover];				// Privacy mask zone
	AV_int32						nCustomTitleNum;	// Self-defined title amount
	AV_CFG_VideoWidgetCustomTitle	stuCustomTitle[AV_CFG_Max_Video_Widget_Custom_Title];	// Self-defined title
	AV_int32						nSensorInfo;		// The number of sensor information overlay area
	AV_CFG_VideoWidgetSensorInfo	stuSensorInfo[AV_CFG_Max_Video_Widget_Sensor_Info];		// Sensor information overlay zone information
    double                          fFontSizeScale;            //overlay font size scale
    AV_int32                        nFontSize;                 //global font size overlay to main stream, unit px.
    AV_int32                        nFontSizeExtra1;           //global font size overlay to sub stream 1, unit px.
    AV_int32                        nFontSizeExtra2;           //global font size overlay to sub stream 2, unit px.
    AV_int32                        nFontSizeExtra3;           //global font size overlay to sub stream 3, unit px.
    AV_int32                        nFontSizeSnapshot;         //global font size overlay to snapshot stream, unit px
    AV_int32                        nFontSizeMergeSnapshot;    //combination picture overlay to snapshot stream, unit px
};

// Storage group channel corresponding config 
struct AV_CFG_StorageGroupChannel 
{
	AV_int32			nStructSize;
	AV_int32			nMaxPictures;					// Picture storage threshold of each channel folder. System overwrites once it reaches the threshold. 
	char				szPath[AV_CFG_Max_ChannelRule];	// The string of the channel in the Name Rule. The corresponding contents of %c.
};

// Storage group config 
struct AV_CFG_StorageGroup 
{
	AV_int32			nStructSize;	
	char				szName[AV_CFG_Group_Name_Len];	// Group name
	char				szMemo[AV_CFG_Group_Memo_Len];	// Group note 
	AV_int32			nFileHoldTime;					// File save time
	AV_BOOL				bOverWrite;						// Overwrite or not when the storage space is full. 
	char				szRecordPathRule[AV_CFG_Max_Path];	// Record file path name rule
	char				szPicturePathRule[AV_CFG_Max_Path];	// Picture file path name rule
															// %y=Y, %M=M, %d=D, %h=H, %m=M, %s=S, %c=Channel path
															// If the Y-M-D-M-S appears twice, the first one stands for the start time and the second one stands for the end time. 
	AV_CFG_StorageGroupChannel	stuChannels[AV_CFG_Max_Channel_Num];// Channel corresponding config
	AV_int32				nChannelCount;				// Channel config amount
};

// DST Time 
struct AV_CFG_DSTTime 
{
	AV_int32			nStructSize;
	AV_int32			nYear;							// Year, 2000~2038
	AV_int32			nMonth;							// Month, 1~12
	AV_int32			nWeek;							// The week, 1-The 1st,2-The 2nd,...,-1-The last,0-calculate by date
	AV_int32			nDay;							// Week or date
														//By week,  0-Sunday, 1-Monday,..., 6-Saturday
														// By date. It stands for which date.  1~31
	AV_int32			nHour;							// Hour 
	AV_int32			nMinute;						// Minute 
};

// ZOne config 
struct AV_CFG_Locales 
{
	AV_int32			nStructSize;
	char				szTimeFormat[AV_CFG_Time_Format_Len];	// Time format
	AV_BOOL				bDSTEnable;						// DST enable
	AV_CFG_DSTTime		stuDstStart;					// DST start time
	AV_CFG_DSTTime		stuDstEnd;						// DST end time 
};

// Language type
enum AV_CFG_LanguageType
{
	AV_CFG_Language_English,							// English
	AV_CFG_Language_SimpChinese,						// SimpChinese
	AV_CFg_Language_TradChinese,						// TradChinese
	AV_CFG_Language_Italian,							// Italian
	AV_CFG_Language_Spanish,							// Spanish
	AV_CFG_Language_Janpanese,							// Janpanese
	AV_CFG_Language_Russian,							// Russian
	AV_CFG_Language_French,								// French
	AV_CFG_Language_German,								// German
    AV_CFG_Language_Portugal,							// Portuguese
    AV_CFG_Language_Turkey,								// Turkish
    AV_CFG_Language_Poland,								// Polish
    AV_CFG_Language_Romanian,							// Romanian
    AV_CFG_Language_Hungarian,							// Hungarian
    AV_CFG_Language_Finnish,							// Finnish
    AV_CFG_Language_Estonian,                           // Estonian        
    AV_CFG_Language_Korean,                             // Korean        
    AV_CFG_Language_Farsi,                              // Farsi          
    AV_CFG_Language_Dansk,                              // Danish
    AV_CFG_Language_Czechish,                           // Czech
    AV_CFG_Language_Bulgaria,                           // Bulgarian
    AV_CFG_Language_Slovakian,                          // Slovak
    AV_CFG_Language_Slovenia,                           // Slovenian
    AV_CFG_Language_Croatian,                           // Croatian
    AV_CFG_Language_Dutch,                              // Dutch
    AV_CFG_Language_Greek,                              // Greek
    AV_CFG_Language_Ukrainian,                          // Ukrainian
    AV_CFG_Language_Swedish,                            // Swedish
    AV_CFG_Language_Serbian,                            // Serbian
    AV_CFG_Language_Vietnamese,                         // Vietnamese
    AV_CFG_Language_Lithuanian,                         // Lithuanian
    AV_CFG_Language_Filipino,                           // Filipino
    AV_CFG_Language_Arabic,                             // Arabic
    AV_CFG_Language_Catalan,                            // Catalan
    AV_CFG_Language_Latvian,                            // Latvian
    AV_CFG_Language_Thai,                               // Thai
    AV_CFG_Language_Hebrew,                             // Hebrew
    AV_CFG_Language_Bosnian,                            // Bosnian
};

// Language config 
struct AV_CFG_Language 
{
	AV_int32			nStructSize;
	AV_CFG_LanguageType emLanguage;						// Current language
};

// Access address filter
struct AV_CFG_AccessFilter
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// Enable
	AV_int32			nType;							// Type, 0-Blacklist, 1-Whitelist
	AV_int32			nWhiteListNum;					// Whitelist IP amount
	char				szWhiteList[AV_CFG_Max_White_List][AV_CFG_Filter_IP_Len];	// Whitelist
	AV_int32			nBlackListNum;					// Blacklist IP or IP section amount
	char				szBlackList[AV_CFG_Max_Black_List][AV_CFG_Filter_IP_Len];	// Blacklist
    AV_BOOL             bIndividual[AV_CFG_Max_White_List];   // white list:for individual IP control
                                                              // goto CLIENT_GetDevCaps/NET_USER_MNG_CAPS to see whether it is supported
															  // if supported, you can set and get the filed;if not ,the filed invalid
															  
	AV_BOOL				bIndividualInBlackList[AV_CFG_Max_Black_List];  //black list:for individual IP control                                                         
															  // goto CLIENT_GetDevCaps/NET_USER_MNG_CAPS to see whether it is supported
															  // if supported, you can set and get the filed;if not ,the filed invalid
};

// Auto maintain
struct AV_CFG_AutoMaintain 
{
	AV_int32			nStructSize;
	AV_int32			nAutoRebootDay;					// Auto reboot date. -1=Never, 0~6=Sunday to Saturday, 7=Every day
	AV_int32			nAutoRebootHour;				// Auto reboot hour, 0~23
	AV_int32			nAutoRebootMinute;				// Auto reboot minute, 0~59
	AV_int32			nAutoShutdownDay;				// Auto shutdown date
	AV_int32			nAutoShutdownHour;				// Auto shutdown hour
	AV_int32			nAutoShutdownMinute;			// Auto shutdown minute
	AV_int32			nAutoStartupDay;				// Auto boot up date
	AV_int32			nAutoStartupHour;				// Auto boot up hour
	AV_int32			nAutoStartupMinute;				// Auto boot up minute
	AV_BOOL				bAutoRebootEnable;				// True said open automatically restart, false said shut down automatically restart 
};

#define AV_CFG_Monitor_Name_Len		64			// Video wall name length 
#define AV_CFG_Max_TV_In_Block		128			// TV max amount in the zone
#define AV_CFG_Max_Block_In_Wall	128			// The zone max amount in the video wall. 

// Video wall output channel info
struct AV_CFG_MonitorWallTVOut
{
	AV_int32		nStructSize;
	char			szDeviceID[AV_CFG_Device_ID_Len];	// Device ID. It is "null" or "Local"(local device)
	AV_int32		nChannelID;							// Channel ID
	char			szName[AV_CFG_Channel_Name_Len];	// Screen name
};

// Video wall zone
struct AV_CFG_MonitorWallBlock 
{
	AV_int32				nStructSize;
	AV_int32				nLine;				// Row amount of each TV
	AV_int32				nColumn;			// Column amount of each TV
	AV_CFG_Rect				stuRect;			// Coordinates of the zone
	AV_int32				nTVCount;			// TV amount
	AV_CFG_MonitorWallTVOut	stuTVs[AV_CFG_Max_TV_In_Block];	// TV array
	CFG_TIME_SECTION		stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	// open or close time
	char					szName[AV_CFG_Channel_Name_Len];				// region name
	char					szCompositeID[AV_CFG_Device_ID_Len];			// composite ID
};

// Video wall
struct AV_CFG_MonitorWall
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Monitor_Name_Len];	// Name
	AV_int32			nLine;								// Network row amount 
	AV_int32			nColumn;							// Network column amount 
	AV_int32			nBlockCount;						// Zone amount
	AV_CFG_MonitorWallBlock stuBlocks[AV_CFG_Max_Block_In_Wall];// Zone array 
    BOOL                bDisable;                           // Disable or not, 0-this TV wall is valid, 1-The TV wall is invalid
    char                szDesc[CFG_COMMON_STRING_256];      // TV wall description info 
};

// Splicing screen 
struct AV_CFG_SpliceScreen
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Channel_Name_Len];	// Screen name	
	char				szWallName[AV_CFG_Monitor_Name_Len];// Belonging video wall name
	AV_int32			nBlockID;							// Belonging zone SN
	AV_CFG_Rect			stuRect;							// Coordinates (0~8191)
};

// PTZ activation type
typedef enum tagAV_CFG_PtzLinkType
{
	AV_CFG_PtzLink_None,				// No activation
	AV_CFG_PtzLink_Preset,				// Activate preset 
	AV_CFG_PtzLink_Tour,				// Activate tour
	AV_CFG_PtzLink_Pattern,				// Activate pattern
} AV_CFG_PtzLinkType;

// PTZ activation  info
typedef struct tagAV_CFG_PtzLink
{
	AV_int32            nStructSize;
	AV_CFG_PtzLinkType	emType;				// Activation type
	AV_int32			nParam1;			// Activation parameter 1
	AV_int32			nParam2;            // Activation parameter 2
	AV_int32			nParam3;            // Activation parameter 3
	AV_int32			nChannelID;         // Activation PTZ channel
} AV_CFG_PtzLink;

// Coordinates
typedef struct tagAV_CFG_Point
{
	AV_int32			nStructSize;
	AV_int32			nX;
	AV_int32			nY;
} AV_CFG_Point;

// Width and height
typedef struct tagAV_CFG_Size
{
	AV_int32			nStructSize;
	AV_uint32			nWidth;
	AV_uint32			nHeight;
} AV_CFG_Size;	

// Event title contents
typedef struct tagAV_CFG_EventTitle
{
	AV_int32			nStructSize;
	char				szText[AV_CFG_Channel_Name_Len];	// Title text
	AV_CFG_Point		stuPoint;			// The title top corner coordinates. It adopts 0-8191 relative coordinates. 
	AV_CFG_Size			stuSize;			// The width and the height of the title. It adopts 0-8191 relative coordinates. if there is a 0 or two o, it means the self-adaptive width and height according to the font
    AV_CFG_Color		stuFrontColor;		// Foreground color
    AV_CFG_Color		stuBackColor;		// background color
} AV_CFG_EventTitle;


// Tour activation config 
typedef struct tagAV_CFG_TourLink
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;			// Tour enable
	CFG_SPLITMODE		emSplitMode;		// Tour split mode
	AV_int32			nChannels[AV_CFG_Max_Channel_Num];  // Tour channel list 
	AV_int32			nChannelCount;		//Tour channel amount
} AV_CFG_TourLink;

// Alarm activation 
typedef struct tagAV_CFG_EventHandler
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection  stuTimeSect[AV_CFG_Weekday_Num][AV_CFG_Max_TimeSection]; // Event respond schedule 
	AV_BOOL             bRecordEnable;		// Record enable
	AV_uint32           nRecordMask[AV_CFG_Max_Channel_Num];	// Record channel No. list
	AV_BOOL             abRecordLatch;		// Capacity set. It is to mark nRecordLatch is valid or not. 
	AV_int32            nRecordLatch;		// Record delay time(10~300s)
	AV_BOOL				bAlarmOutEn;		// Alarm output enable
	AV_uint32			nAlarmOutMask[AV_CFG_Max_Channel_Num];	// Alarm output channel No. list
	AV_BOOL             abAlarmOutLatch;	// Capacity set. it is to makr  nAlarmOutLatch is valid or not. 
	AV_int32			nAlarmOutLatch;		// Alarm output delay time. (10~300s)
	AV_BOOL				bExAlarmOutEn;		// Extension alarm output enable
	AV_uint32			nExAlarmOutMask[AV_CFG_Max_Channel_Num]; // Extension alarm output channel list
	AV_BOOL				bPtzLinkEn;			// PTZ activation enable
	AV_int32            nPtzLinkNum;		// Valid activation amount
	AV_CFG_PtzLink		stuPtzLink[AV_CFG_Max_Channel_Num];		// PTZ activatiom item
	AV_BOOL				bSnapshotEn;		// Snap enable
	AV_uint32			nSnapshotMask[AV_CFG_Max_Channel_Num];  // Snap channel No. list	
	AV_BOOL             abSnapshotPeriod;	// Capacity set. It is to mark  nSnapshotPeriod is valid or not. 
	AV_int32			nSnapshotPeriod;	// Frame interval. Snap at what frame. The snap amount in the specified period also has relationship with the snap frame rate. 0=There is no interval frame and snap continuesly. 
	AV_BOOL             abSnapshotTimes;	//Capacity set. nSnapshotTimes validity
	AV_int32			nSnapshotTimes;		// Snap times. When SnapshotEnable is true,system snaps continuesly when SnapshotTimes is 0 until the event ends. 
	AV_BOOL             bSnapshotTitleEn;	// Overlay picture title or not. 
	AV_int32            nSnapTitleNum;      // Valid picture title amount
	AV_CFG_EventTitle   stuSnapTitles[AV_CFG_Max_Event_Title_Num]; // Picture title contents 
	AV_BOOL				bTipEnable;			//Local info prompt dialogue box  
	AV_BOOL				bMailEnable;		// Send email. Attach picture if there is any. 
	AV_BOOL				bMessageEnable;		// Upload to alarm server 
	AV_BOOL				bBeepEnable;		// Buzzer
	AV_BOOL				bVoiceEnable;		// Auido prompt 
	AV_BOOL             abDejitter;			// Capacity set.  nDejitter validity.
	AV_int32            nDejitter;			// Signal anti-dither time.0~100s
	AV_BOOL             bLogEnable;			// Record log or not. 
	AV_BOOL             abDelay;			// nDelay validity 
	AV_int32            nDelay;				// Delay and then become valid when set. The unit is second. 
	AV_BOOL             bVideoTitleEn;		// Overlay video title or not. It mainly refers to the main stream. 
	AV_int32            nVideoTitleNum;		// Valid video title amount 
	AV_CFG_EventTitle	stuVideoTitles[AV_CFG_Max_Event_Title_Num]; // Video title contents 
	AV_BOOL				bMMSEnable;			// MMS enable
	AV_int32            nTourNum;			// Tour activation amount. It is the same as the video output. 
	AV_CFG_TourLink	    stuTour[AV_CFG_Max_Tour_Link_Num];		// Tour activation setup. Each video output has one setup. 
	AV_int32            nDBKeysNum;			// Key word amount
	char	            szDBKeys[AV_CFG_Max_DBKey_Num][AV_CFG_DBKey_Len]; //Key word 
	AV_BOOL             abJpegSummary;		// Capacity set. It is to mark byJpegSummary is valid or not. 
	AV_BYTE             byJpegSummary[AV_CFG_Max_Summary_Len]; //Abstract info overlay to the JPEG picture. 
} AV_CFG_EventHandler;

#define AV_CFG_Event_Code_Len	64		// Event code length 

// Remote device event process 
struct AV_CFG_RemoteEvent 
{
	AV_int32            nStructSize;
	AV_BOOL             bEnable;						// Enable
	char                szDeviceID[AV_CFG_Device_ID_Len];// Device ID
	char                szCode[AV_CFG_Event_Code_Len];	//Event code 
	AV_int32            nIndex;							// SN
	AV_BOOL             abSensorType;                   // nSensorType is valid or not
	AV_uint32           nSensorType;                    // Sensor type.  NO:1 or NC:0
	AV_CFG_EventHandler stuEventHandler;				// Alarm activation 
};

//Temperature alarm config 
typedef struct tagAV_CFG_TemperatureAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// Alarm enable 
	char				szName[AV_CFG_Device_Name_Len];		// Sensor name
	AV_float			fNormalTempMin;						// Min normal temperature 
	AV_float			fNormalTempMax;						// Max normal temperature 
	AV_CFG_EventHandler stuEventHandler;					// Alarm activation 
} AV_CFG_TemperatureAlarm;

//Fan speed alarm config 
typedef struct tagAV_CFG_FanSpeedAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// Alarm enable
	char				szName[AV_CFG_Device_Name_Len];		// Sensor name
	AV_uint32			nNormalSpeedMin;					// Min normal speed 
	AV_uint32			nNormalSpeedMax;					// Max normal speed
	AV_CFG_EventHandler stuEventHandler;					// Alarm activation 
} AV_CFG_FanSpeedAlarm;

// hard disk flow alarm configuration
typedef struct tagCFG_DISK_FLUX_INFO 
{
	BOOL				bEnable;							// Alarm enable
	unsigned int		nNormalFluxMin;						// min of normal flux(KB)
	unsigned int		nNormalFluxMax;						// max of normal flux(KB)
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// Alarm activation 
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// incident response time
} CFG_DISK_FLUX_INFO;

// net flow alarm configuration
typedef struct tagCFG_NET_FLUX_INFO
{
	BOOL				bEnable;							// Alarm enable
	unsigned int		nNormalFluxMin;						// min of normal flux(KB)
	unsigned int		nNormalFluxMax;						// max of normal flux(KB)
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// Alarm activation 
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// incident response time
} CFG_NET_FLUX_INFO;

// service
typedef struct tagCFG_SERVER_INFO
{
	int                 nPort;                             // service port
	char                szAddress[MAX_ADDRESS_LEN];        // IP address or 
}CFG_SERVER_INFO;

// initiative register configuration
typedef struct tagCFG_REGISTER_SERVER_INFO
{
	BOOL                bEnable;                            // initiative register enable
	char                szDeviceID[MAX_ADDRESS_LEN];        // device ID
	int                 nServersNum;                        // server num
	CFG_SERVER_INFO     stuServers[MAX_SERVER_NUM];         // servers
}CFG_REGISTER_SERVER_INFO;

// Bit stream strategy when bandwitch is insufficient
typedef enum tagSTREAM_POLICY
{
    STREAM_POLICY_UNKNOWN,
    STREAM_POLICY_NONE = 1,								// No strategy, diable "None"
    STREAM_POLICY_QUALITY,                              // Qualiy first "Quality"  
    STREAM_POLICY_FLUENCY,                              // Fliency first"Fluency"
    STREAM_POLICY_AUTOADAPT,                            // Auto "AutoAdapt"
}EM_STREAM_POLICY;

// network protocol configuration
typedef struct tagCFG_DVRIP_INFO
{
	int                 nTcpPort;                           // TCP server port,1025~65535
	int                 nSSLPort;                           // SSL server port,1025~65535
	int                 nUDPPort;                           // UDP server port,1025~65535
	int                 nMaxConnections;                    // max connections 
	BOOL                bMCASTEnable;                       // multicast enable
	int                 nMCASTPort;                         // multicast port
	char                szMCASTAddress[MAX_ADDRESS_LEN];    // multicast address
	int                 nRegistersNum;                      // number of initiative register configuration
	CFG_REGISTER_SERVER_INFO stuRegisters[MAX_REGISTER_NUM];// initiative register configuration
    EM_STREAM_POLICY    emStreamPolicy;                     // Bit stream strategy when bandwitch is insufficient
}CFG_DVRIP_INFO;

// video holiday plan
typedef struct tagCFG_HOLIDAY_SCHEDULE
{
	BOOL				bEnable;
	int					nChannel;
	DWORD				dwMonthSchedule[MONTH_OF_YEAR];		// every month of the holiday arrangement,each element represents a month 
															// mask from low to high according to each month 1-28/29/30/31 if there is holiday
															// 0:haven't holiday, 1: have holiday
	CFG_TIME_SECTION	stuTimeSection[MAX_REC_TSECT];		// video schedule
} CFG_HOLIDAY_SCHEDULE;

// Record backup config 
typedef struct tagAV_CFG_RecordBackup
{
	AV_int32			nStructSize;
	AV_uint32			nBitrateLimit;						// Max flux setup. Unit is Kbps.
	AV_CFG_RemoteDevice	*pstuDevices;						// backup device array, allocate memory for users
	int					nMaxDeviceCount;					// backup device array size, user fill out
	int					nRetDeviceCount;					// return device number
} AV_CFG_RecordBackup;

typedef struct tagALARM_EVENT_INFO
{
	DWORD	        	dwEventType;					    // Event type. Please refer to the Intelligent Analysis Event Type in dhnetsdk.h
	int		         	nEventSize;							// The configuration structure size of current event type. 
} ALARM_EVENT__INFO;

// All events of each video input channel. Fill in several event info in the buffer pEventBuf. The rule info contents of each event is ALARM_EVENT_INFO+"corresponding rule configuration structure of the event type".
typedef struct tagALARM_ANALYSEEVENTS_INFO
{
	int	         		nEventCount;						// Event amount
	char*				pEventBuf;							// Video analysis event buffer of each video input channel.
	int		        	nEventBufLen;						// Buffer size 
	
} ALARM_ANALYSEEVENTS_INFO;

// COM info 
typedef struct tagCFG_COMM_INFO
{
	char				szProtocolName[MAX_PROTOCOL_NAME_LEN];	// COM protocol 
	CFG_COMM_PROP		stuAttribute;							// COM property 
	int					nAddress;								// Device address
} CFG_COMM_INFO;

// COM config 
typedef struct tagCFG_COMMGROUP_INFO
{
	int					nCommNum;						// COM amount
	CFG_COMM_INFO		stuComms[MAX_COMM_NUM];			// COM array
} CFG_COMMGROUP_INFO;

// Network interface
typedef struct tagCFG_NETWORK_INTERFACE 
{
	char				szName[MAX_NAME_LEN];			// Network address name
	char				szIP[MAX_ADDRESS_LEN];			// IP address
	char				szSubnetMask[MAX_ADDRESS_LEN];	// Subnet mask
	char				szDefGateway[MAX_ADDRESS_LEN];	// Default gateway
	BOOL				bDhcpEnable;					// Enable DHCP or not. 
	BOOL				bDnsAutoGet;					// DNS get way.,It is true if the dhcp is enabled. Support DHCP. 
	char				szDnsServers[MAX_DNS_SERVER_NUM][MAX_ADDRESS_LEN];	// DNS address
	int					nMTU;							// Network max transmission unit.
} CFG_NETWORK_INTERFACE;

// Network interface config 
typedef struct tagCFG_NETWORK_INFO 
{
	char				szHostName[MAX_NAME_LEN];		// Host name
	char				szDomain[MAX_NAME_LEN];			// Belonging domain
	char				szDefInterface[MAX_NAME_LEN];	// Default network card 
	int					nInterfaceNum;					// Network card amount
	CFG_NETWORK_INTERFACE	stuInterfaces[MAX_NETWORK_INTERFACE_NUM];	// Network card list 
} CFG_NETWORK_INFO;

// Cloud storage protocol type 
typedef enum tagEM_CFG_NAS_CLOUDPROTOCOL_TYPE
{
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_UNKNOWN,              // Unknown
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_BAIDU_CLOUD,          // "BaiduCloud"
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_GOOGLE_DRIVE,         // "GoogleDrive"
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_DROPBOX,              // "Dropbox"
}EM_CFG_NAS_CLOUDPROTOCOL_TYPE;

// Network storage config 
typedef struct tagCFG_NAS_INFO_NEW
{
	BOOL				bEnable;						// Enable
	char				szName[MAX_NAME_LEN];			// Name
	int					nPortocol;						// Protocol type, 0-FTP, 1-SMB, 2-ISCSI
	char				szAddress[MAX_ADDRESS_LEN];		// IP address or website
	int					nPort;							//Port 
	char				szUser[MAX_USERNAME_LEN];		// User name
	char				szPassword[MAX_PASSWORD_LEN];	// Password 
	char				szDirectory[MAX_NAME_LEN];		// Share folder name. 
	int					nCharEncoding;					// String encode format.  0-UTF8, 1-GB2312
	int					nTimeOut;						// Timeout, the unit milliseconds 
	unsigned int		nStreamID;						// The data stream ID 
	CFG_NET_TIME_EX		stuUpdateTime;					// Update time, after the field values change, need to re-initialize the iSCSI function 
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE   emCloudProtocol;    // Cloud storage protocol type 
    char                            szSubDirectory[CFG_COMMON_STRING_256];               // Client device on server storage sub directory?ê?may be IP address?ê?device SN?ê?device machine no?ê?as null used device machine no.
} CFG_NAS_INFO_NEW;

// NVS config. It includes several servers. 
typedef struct tagCFG_NAS_GROUP_INFO
{
	int					nNasNum;						// Storage server amount
	CFG_NAS_INFO_NEW	stuNasInfo[MAX_NAS_NUM];		// Storage server array	
} CFG_NAS_GROUP_INFO;

// Network storage server config 
typedef struct tagCFG_NAS_INFO_EX 
{
	int					nVersion;						// 0, 1, depends on the capacity set. Read-only.
	CFG_NAS_INFO		stuNasOld;						// Valid when nVersion == 0. Support one server only.  
	CFG_NAS_GROUP_INFO	stuNasGroup;					// Valid when nVersion == 1. Support several servers.  
} CFG_NAS_INFO_EX;

// input channel configuration
typedef enum _EM_CFG_VIDEO_SIGNAL_TYPE
{
    EM_CFG_VIDEO_SIGNAL_UNKNOWN, 
    EM_CFG_VIDEO_SIGNAL_CVBS, 
    EM_CFG_VIDEO_SIGNAL_SDI, 
    EM_CFG_VIDEO_SIGNAL_VGA, 
    EM_CFG_VIDEO_SIGNAL_DVI, 
    EM_CFG_VIDEO_SIGNAL_HDMI, 
    EM_CFG_VIDEO_SIGNAL_YPBPR, 
    EM_CFG_VIDEO_SIGNAL_SFP, 
    EM_CFG_VIDEO_SIGNAL_HDCVI, 
} EM_CFG_VIDEO_SIGNAL_TYPE;

// Video input basic config
typedef struct tagCFG_VIDEO_IN_INFO 
{
	char				szDevType[MAX_NAME_LEN];		// channel type(refers to the channel connection device type)
	char				szDevID[MAX_NAME_LEN];			// number of camera
	char				szChnName[MAX_NAME_LEN];		// channel name
	char				szManufacturer[MAX_NAME_LEN];	// manufacturer
	char				szModel[MAX_NAME_LEN];			// device model
	char				szAddress[MAX_ADDRESS_LEN];		// setting address
	char				szCivilCode[MAX_NAME_LEN];		// administrative areas
	char				szOwner[MAX_NAME_LEN];			// device owner
	BOOL				bParental;						// is parent or not
	BOOL				bEnable;						// channel enable
	int					nRegisterWay;					// register way
														// 0-fits a pattern of sip3261standard certification
														// 1-Two-way authentucation based on password registered model
														// 2-Two-way authentication registered mode based on digital certificate
	BOOL				bSecrecy;						// secrecy, FALSE is not classified, TRUE is classified
	char				szUpperDevID[MAX_NAME_LEN];		// superior connection device ID
	int					nUpperDevOutChn;				// superior connection device output channel num 
    char				szRemoteName[MAX_NAME_LEN];		// Remote channel name
	EM_CFG_VIDEO_SIGNAL_TYPE emSignalType;    
} CFG_VIDEO_IN_INFO;

// burn CD coding plan (corresponding command is CFG_CMD_ENCODEPLAN),each channel a configuration(include picinpic channel)
typedef struct tagCFG_ENCODE_PLAN_INFO
{
	BOOL                bEnable;                        // the channel is able or not,FALSE:without this channel,TRUE:this channel is available
	unsigned int        nExpectTime;                    // the business forecast time,int(s)
	CFG_CAPTURE_SIZE    emResolution;                   // video resolution
	unsigned int        nBitRate;                       // vide bit rate(kbps)
}CFG_ENCODE_PLAN_INFO;

//////////////////////////////////////////////////////////////////////////
// the judicial interrogation demand picinpic
// small picture information window
typedef struct tagCFG_SMALLPIC_INFO
{
	char                szDeviceID[AV_CFG_Device_ID_Len];// device ID
	int                 nChannelID;						 // channel ID(from 0)
	BOOL                bAudio;                          // whether the big picture mixes small picture's aduio
    CFG_RECT            stuPosition;                     // the relative coordinate system,range from 0 to 8192
}CFG_SMALLPIC_INFO;

// split channel
typedef struct tagCFG_SPLIT_CHANNEL_INFO
{
	BOOL                bEnable;                         // enable
	char                szDeviceID[AV_CFG_Device_ID_Len];// device ID
	int                 nChannelID;						 // channel ID(from 0)
	unsigned int        nMaxSmallChannels;               // number of small picture,each channel has a CFG_SMALLPIC_INFO, maxinum device channel number - 1
	unsigned int        nReturnSmallChannels;            // parses the returned or packaging to send small picture of the channel number
	CFG_SMALLPIC_INFO  *pPicInfo;                        // small picture info 
}CFG_SPLIT_CHANNEL_INFO;

// split project
typedef struct tagCFG_SPLIT_INFO
{
	CFG_SPLITMODE       emSplitMode;        // split mode, through the CLIENT_GetSplitCaps interface to get,see emSplitMode
	unsigned int        nMaxChannels;       // applied for CFG_SPLIT_CHANNEL_INFO number of memory,such as 16 channels,nMaxChannels = 16,SPLITMODE_4 mode,in order is divided into four groups
	unsigned int        nReturnChannels;    // parsing the return channel number,need to packaging to send the channel number
	CFG_SPLIT_CHANNEL_INFO* pSplitChannels; // split channel info
}CFG_SPLIT_INFO;

// picinpic project
typedef struct tagCFG_PICINPIC_INFO
{
	unsigned int        nMaxSplit;          // applied for CFG_SPLIT_INFO number of memory,the value through the CLIENT_GetSplitCaps interface to get,see nModeCount
	unsigned int        nReturnSplit;       // parsing for actual use or encapsulation send CFG_SPLIT_INFO number
	CFG_SPLIT_INFO     *pSplits;            // split project
}CFG_PICINPIC_INFO;

// analog matrix external input source
typedef struct tagCFG_ANALOG_MATRIX_INPUT_CHN_SRC 
{
	char				szName[MAX_NAME_LEN];			// input channel name
	char				szControlID[MAX_NAME_LEN];		// control ID
	BOOL				bActive;						// active or not
	int					nFormat;						// format, 0-VGA
} CFG_ANALOG_MATRIX_INPUT_CHN_SRC;

// com
typedef struct tagCFG_COM_PORT 
{
	int					nPortIndex;						// com index number
	int					nAddress;						// device address
	CFG_COMM_PROP		stComProp;						// com attribute
} CFG_COM_PORT;

// analog matrix 
typedef struct tagCFG_ANALOG_MATRIX_INFO
{
	char				szDevID[MAX_NAME_LEN];			// device ID
	char				szName[MAX_NAME_LEN];			// device name
	char				szModel[MAX_MODEL_LEN];			// mode
	char				szUserName[MAX_USERNAME_LEN];	// user name
	char				szPassword[MAX_PASSWORD_LEN];	// password
	int					nChnInCount;					// count of input channel
	int					nChnOutCount;					// count of output channel
	CFG_ANALOG_MATRIX_INPUT_CHN_SRC* pstuChnInSrc;		// external input source array, allocated memory
	int					nChnInSrcCount;					// external input source array size
	int					nRetChnInSrcCount;				// actual number of external input source returns ,usually with nChnInCount
	CFG_COM_PORT		stComPort;						// associated com
	char				szProtocol[MAX_NAME_LEN];		// protocol name
} CFG_ANALOG_MATRIX_INFO;

// analog matrix protocol configuration
typedef struct tagCFG_ANALOG_MATRIX_PROTOCOL 
{
	char				szName[MAX_NAME_LEN];			// protocol name
	char				szProtocolRule[MAX_NAME_LEN];	// content of protocol, the rule:%A-address code,%I-input number,%O-output number
} CFG_ANALOG_MATRIX_PROTOCOL;

// video output title
typedef struct tagCFG_VIDEO_OUT_TITLE 
{
	char				szName[MAX_NAME_LEN];			// channel name
} CFG_VIDEO_OUT_TITLE;

// display source
typedef struct tagCFG_DISPLAY_SOURCE
{
	BOOL				bEnable;						// enable
	char				szDeviceID[MAX_NAME_LEN];		// device ID
	char				szControlID[MAX_NAME_LEN];		// control ID
	int					nVideoChannel;					// video channel 
	int					nVideoStream;					// stream of video, -1-auto. 0-main stream, 1-extra stream 1, 2-extra stream 2, 3-extra stream 3
	int					nAudioChannel;					// audio channel
	int					nAudioStream;					// stream of audio, -1-auto. 0-main stream, 1-extra stream 1, 2-extra stream 2, 3-extra stream 3
	BOOL				abDeviceInfo;					// whether device info effect 
	AV_CFG_RemoteDevice stuDeviceInfo;					// devide info
} CFG_DISPLAY_SOURCE;

// position of split window
typedef struct tagCFG_SPLIT_WINDOW_POSITION 
{
	CFG_RECT			stuRect;						// window rect
	BOOL				bDirectable;					// whether meet the road conditions, the pass-through refers to splice screen mode,the window just as the physical screen area
	int					nZorder;						// order of Z
} CFG_SPLIT_WINDOW_POSITION;

// split window info
typedef struct tagCFG_SPLIT_WINDOW 
{
	BOOL				bEnable;						// whether the window has video source, the FALSE is means have not,don't have to deal with Source
	int					nWindowID;						// window ID
	char				szControlID[MAX_NAME_LEN];		// control ID
	CFG_SPLIT_WINDOW_POSITION stuPosition;				// window position 
	CFG_DISPLAY_SOURCE	stuSource;						// video source
} CFG_SPLIT_WINDOW;

// split window scene
typedef struct tagCFG_BLOCK_COLLECTION 
{
	char				szBlockID[MAX_NAME_LEN];		// split windowID
	char				szControlID[MAX_NAME_LEN];		// control ID
	CFG_SPLITMODE		emSplitMode;					// split mode
	CFG_SPLIT_WINDOW*	pstuWnds;						// of window info array , allocated memory
	int					nMaxWndCount;					// size of window info array ,user fill in
	int					nRetWndCount;					// return counts of window
} CFG_BLOCK_COLLECTION;

// one of monitor wall plan configuration
typedef struct tagCFG_MONITORWALL_COLLECTION_SINGLE
{
	char				szName[MAX_NAME_LEN];			// name
	char				szControlID[MAX_NAME_LEN];		// control ID
	AV_CFG_MonitorWall	stuMonitorWall;					// monitor wall configuration
	CFG_BLOCK_COLLECTION* pstuBlockCollections;			// splicing screan scene information array, allocated memory
	int					nMaxBlockCollectionCount;		// size of splicing screan scene information array, user fill in
	int					nRetBlockCollectionCount;		// returns the number of splicing screan scene
} CFG_MONITORWALL_COLLECTION_SINGLE;

// monitor wall plan list, means a monitor wall corresponding to multiple plans
typedef struct tagCFG_MONITORWALL_COLLECTION_LIST
{
	CFG_MONITORWALL_COLLECTION_SINGLE* pstuCollections;	// array of window info, allocated memory
	int					nMaxCollectionCount;			// size of plan array,user fill in
	int					nRetCollectionCount;			// returns the number of plan 
} CFG_MONITORWALL_COLLECTION;

// video input boundary configuration
typedef struct tagCFG_VIDEO_IN_BOUNDARY 
{
	CFG_RECT			stuBoundary;					// boundary
} CFG_VIDEO_IN_BOUNDARY;

// and camera docking area screen configuration,is array,max of element is DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen
typedef struct tagCFG_PARKINGSPACE_SCREEN_INFO
{
	char                szAddress[MAX_PATH];            // regional screen adress or domain name
	int                 nPort;                          // regional screen port
	char                szAuthorization[MAX_PATH];      // authorization
    char                szDeviceNo[MAX_PATH];           // device no.
	BOOL                bEnable;                        // whether to enable the screen settings
} CFG_PARKINGSPACE_SCREEN_INFO;

// parking set(common spaces or dedicated parking spaces),is array,max of element is DH_PRODUCTION_DEFNITION.nMaxRoadWays
typedef struct tagCFG_PARKINGSPACE_STATUS_INFO
{
	int                  nLaneID;                        // lane ID
	int                  nLaneType;                      // 0:common spaces,1: dedicated parking spaces
} CFG_PARKINGSPACE_STATUS_INFO;

#define CFG_MAX_BINARY_NUM      128						// Max valid count of custom data

// information platform for the custom
typedef struct tagCFG_CLIENT_CUSTOM_INFO
{
	char                 szDescription[MAX_PATH];        // describing information,different custom description information platform,currently supported "LiFang"
	char*                pData;                          // custom data bbuffer, the data cann't exist between binary 0,is the '\0'
	int                  nDataLen;                       // data length,diffent platfrms themselves
    bool                abBinary;                       // false: pData and nDataLen are enabled, while nBinaryNum and dwBinary are disabled
                                                        // true: pData and nDataLen are disabled, while nBinaryNum and dwBinary are enabled
    BYTE                byReserved[3];
    int                 nBinaryNum;                     // valid count of dwBinary array
    DWORD               dwBinary[CFG_MAX_BINARY_NUM];   // custom data array
} CFG_CLIENT_CUSTOM_INFO;

// burn record format configuration,compatibility considerations,without this configuration DHAV format by default
typedef struct tagCFG_BURN_RECORD_FORMAT
{
	char                 szRecordPack[MAX_PATH];         // stream packaging mode:currently supported "DHAV","PS"
}CFG_BURN_RECORD_FORMAT;

// synchronous burn CD(corresponding to CFG_MULTIBURN_INFO) is array,each element repressents a group of burning and checking 
typedef struct tagCFG_MULTIBURN_INFO
{
	BOOL                 bEnable;                        // enable
    BOOL                 bDataCheck;                     // data chek enable
    char                 szDataCheckSpeed[MAX_PATH];     // speed of checking "High":high speed(check head and tail),"Normal":(random data checking),"Low":(all date checking)
}CFG_MULTIBURN_INFO;

// Single network storage server configuration restrictions
typedef struct tagCFG_REMOTE_STORAGE_LIMIT
{
    char				        szName[MAX_NAME_LEN];                       // Name
    int							nFileLen;									// File length unit, MB 
	int							nInterval;									// Adjacent file time interval unit,  seconds 
	CFG_CHANNEL_TIME_SECTION	*pstuChnTime;        	                    // Storage time array, the user allocates memory 
	int                         nMaxChnCount;                               // The maximum number of channels, users fill
    int                         nRetChnCount;                               // Returns the number of channels, save Settings when the effective channel number 
}CFG_REMOTE_STORAGE_LIMIT;

// Network storage server limit configuration 
typedef struct tagCFG_REMOTE_STORAGELIMIT_GROUP
{
	CFG_REMOTE_STORAGE_LIMIT    stuRemoteStorageLimit[MAX_NAS_NUM];         // Network storage server configuration array
    int                         nLimitCount;                                // The number of effective network server
}CFG_REMOTE_STORAGELIMIT_GROUP;

// get burn management capacity
typedef struct tagCFG_CAP_BURN_MANAGER	
{
    BOOL                 bSupportMultiBurn;              // support multiburn or not
    int                  nMultiBurnGroups;               // support multiburn groups
}CFG_CAP_BURN_MANAGER;

// ability of record information
typedef struct tagCFG_CAP_RECORD_INFO	
{
	BOOL  bSupportHoliday;				                 //video does plan to support the holidat function
	BOOL  bSupportExtraRecordMode;						 //whether to support setting extra stream video mode
	DWORD dwMaxPreRecordTime;							 //max record time
	DWORD dwMaxRemoteBitrate;							 //total access code stream(kbps)
	DWORD dwMaxRemoteRawBitrate;						 //maximum access to the bare code stream (include decause,resolution,frame rate,deep calculated on 16bpp)
    DWORD dwMaxStreams;                                  //Maximum number of video stream 
} CFG_CAP_RECORD_INFO;

//-------------------------------Code Encryption---------------------------------
typedef  enum tagCFG_ENCRYPT_ALGO_TYPE
{
	ALGO_TYPE_AES	 , 
	ALGO_TYPE_UNKNOW ,
}CFG_ENCRYPT_ALGO_TYPE;

// Stream encryption algorithm working mode 
typedef enum  tagCFG_ENCRYPT_ALGO_WORKMODE
{
	ENCRYPT_ALGO_WORKMODE_ECB,     // ECB mode
	ENCRYPT_ALGO_WORKMODE_CBC,     // CBC mode
	ENCRYPT_ALGO_WORKMODE_CFB,     // CFB mode
	ENCRYPT_ALGO_WORKMODE_OFB,     // OFB mode
	ENCRYPT_ALGO_WORKMODE_UNKNOW ,
}CFG_ENCRYPT_ALGO_WORKMODE;

typedef union tagCFG_ENCRYPT_KEY_INFO
{
	BYTE byAesKey[AES_KEY_LEN];							// aes key
}CFG_ENCRYPT_KEY_INFO;

//Stream encryption configuration information 
typedef struct tagCFG_STREAM_ENCRYPT_INFO
{
	BOOL						bEncryptEnable;		// Whether the encryption 
	CFG_ENCRYPT_ALGO_TYPE		emEncrptAlgoType;	// Encryption Algorithm Type: See enumerated type CFG_ENCRYPT_ALGO_TYPE
	CFG_ENCRYPT_ALGO_WORKMODE	emAlgoWorkMode;		// Working mode, the reference enumerated type CFG_ENCRYPT_ALGO_WORKMODE
	WORD						wEncryptLenth;		// The key length, the current is AES algorithm type?ê? which means that key bits(currently support 128,192,256 three kinds, such as: wEncryptLenth was : wEncryptLenth is 128?ê?the key information in ENCRYPT_KEY_INFO byAesKey [0] to [15]) )
	CFG_ENCRYPT_KEY_INFO		stuEncryptKeys;		// Key information channel 
	CFG_NET_TIME				stuPreTime;			// Encryption program start time 
}CFG_STREAM_ENCRYPT_INFO;

//Stream encryption configuration channel information 
typedef struct tagCFG_ENCODE_ENCRYPT_CHN_INFO
{
	int						 nChannelID;					// Channel number (starting from 0)
	CFG_STREAM_ENCRYPT_INFO *pstEncodeEncryptInfo;			// Each channel configuration list, the user must be configured
												            // nMaxEncryptInputs??CFG_STREAM_ENCRYPT
	BYTE					 nMaxEncryptInputs; 
	BYTE					 nRetEncryptOutputs;			// Parse out the number of CFG_STREAM_ENCRYPT
}CFG_ENCODE_ENCRYPT_CHN_INFO;


//Adaptive coding strategy type
typedef  enum tagCFG_ENCRYPT_POLICY_TYPE
{
	ENCRYPT_POLICY_UNKNOWN ,		//Unknown
	ENCRYPT_POLICY_NONE ,		//No strategy, do not open the adaptive function
	ENCRYPT_POLICY_QUALITY ,    //Quality priority, priority to ensure resolution, frame rate lower
	ENCRYPT_POLICY_FLUENCY ,	//Smooth priority, priority to ensure fluency, reduced resolution
}CFG_ENCRYPT_POLICY_TYPE;

//Coding smooth priority strategy
typedef enum tagCFG_ENCRYPT_FLUENCY_MODE
{
	ENCRYPT_FLUENCY_UNKNOWN ,		//Unknown
	ENCRYPT_FLUENCY_FAST ,			//Fast recovery (speed getting better, immediately restored)
	ENCRYPT_FLUENCY_SLOW ,			//Slow recovery (at the same time there can be only one channel recovery) 
	ENCRYPT_FLUENCY_SYNC ,			//Synchronization recovery (if any channel decreases, the other channels are not restored)
	ENCRYPT_FLUENCY_SLOWSYNC ,		//Slow synchronization recovery (combined with slow recovery and synchronization recovery)
}CFG_ENCRYPT_FLUENCY_MODE;

//Coding Adaptive Configuration
typedef struct tagCFG_ENCODE_ADAPT_INFO
{
	CFG_ENCRYPT_POLICY_TYPE		emPolicyType;		//Adaptive strategy type
	CFG_ENCRYPT_FLUENCY_MODE	emFluencyMode;		//Smooth priority strategy 
}CFG_ENCODE_ADAPT_INFO;

// Zoom set the basic information unit
typedef struct tagCFG_VIDEO_IN_ZOOM_UNIT
{
	int         nSpeed;									 //Speed ??variator (0-7)
	BOOL		bDigitalZoom;							 //Whether digital zoom
	int			nZoomLimit;								 //Under the current rate ,the upper limit of maximum zoom(0 to 13)??ê
} CFG_VIDEO_IN_ZOOM_UNIT;

// Single-channel zoom setting basics information
typedef struct tagCFG_VIDEO_IN_ZOOM	
{
	int						nChannelIndex;				 //Channel number 
	int						nVideoInZoomRealNum;		 //Configure the number of useing
	CFG_VIDEO_IN_ZOOM_UNIT  stVideoInZoomUnit[MAX_VIDEO_IN_ZOOM];		 //Channel variable speed configuration unit Information
	
} CFG_VIDEO_IN_ZOOM;

// Grab Configuration
typedef struct tagCFG_SNAP_INFO 
{
	CFG_TIME_SCHEDULE		stuTimeSchedule;			// Schedule, the mask bit for each time period is defined as follows:
														// Bit0-timed shots
														// Bit1-dynamic detection capture
														// Bit2-alarm capture
														// Bit3-card capture 
														// Bit4 ~ Bit31 - remain 

} CFG_SNAP_INFO;

//PTZ rotation angle range, unit: degree
typedef struct tagCFG_PTZ_MOTION_RANGE
{
	int                 nHorizontalAngleMin;       // Minimum level angle range, unit: degree
	int                 nHorizontalAngleMax;       // The maximum horizontal angle range, unit: degree
	int                 nVerticalAngleMin;          // Vertical angle range minimum, unit: degree
	int                 nVerticalAngleMax;          // Maximum vertical angle range, unit: degree
}CFG_PTZ_MOTION_RANGE;

//Supported Focus mode corresponding enumeration
typedef enum tagSUPPORT_FOCUS_MODE
{
    ENUM_SUPPORT_FOCUS_CAR        = 1,                // See the car model         
	ENUM_SUPPORT_FOCUS_PLATE      = 2,                // See the license plate model 
	ENUM_SUPPORT_FOCUS_PEOPLE     = 3,                // see people mode      
	ENUM_SUPPORT_FOCUS_FACE       = 4,                // See the face model      
}EM_SUPPORT_FOCUS_MODE;

//PTZ rotation angle range, unit: degree
typedef struct tagCFG_PTZ_LIGHTING_CONTROL
{
	char                szMode[CFG_COMMON_STRING_32];  // Manual Lighting Control Mode 
	                                                   // On - off ": Direct Switch Mode, 
	                                                   // "adjustLight"?êoManually Adjust Brightness Mode 

	DWORD               dwNearLightNumber;             // The number of near light group
	DWORD               dwFarLightNumber;              // The number of beam group
}CFG_PTZ_LIGHTING_CONTROL;

//Get PTZ capability set information
typedef struct tagCFG_PTZ_PROTOCOL_CAPS_INFO
{
	int                 nStructSize;
    BOOL                bPan;                       // Whether to support PTZ horizontal swing 
	BOOL                bTile;                      // Whether to support PTZ vertical swinging 
	BOOL                bZoom;                      // Whether to support PTZ changed times 
	BOOL                bIris;                      // Whether to support PTZ aperture adjustment
	BOOL                bPreset;                    // Whether to support the preset point 
	BOOL                bRemovePreset;              // Whether to support removal of preset point 
	BOOL                bTour;                      // Whether to support automatic cruise lines
	BOOL                bRemoveTour;                // Whether to support Clear cruise
	BOOL                bPattern;                   // Whether to support the track line
	BOOL                bAutoPan;                   // Whether to support automatic level swing
	BOOL                bAutoScan;                  // Whether to support automatic scanning
	BOOL                bAux;                       // Whether to support accessibility
	BOOL                bAlarm;                     // Support alarm function 
	BOOL                bLight;                     // Whether or not support the lighting, the contents see below "stuPtzLightingControl", this member is invalid
	BOOL                bWiper;                     // Whether or not support the wipers
	BOOL                bFlip;                      // Whether or not support Flip camera
	BOOL                bMenu;                      // Whether or not support PTZ built-in menus 
	BOOL                bMoveRelatively;            // Whether or not support the PTZ by a relative coordinate positioning
	BOOL                bMoveAbsolutely;            // Whether or not support PTZ in absolute coordinates 
    BOOL                bMoveDirectly;              // Whether or not support ptz 3D point direct motion
	BOOL                bReset;                     // Whether or not support PTZ reset 
	BOOL                bGetStatus;                 // Whether or not support Get the state of motion and orientation coordinates of PTZ
	BOOL                bSupportLimit;              // Whether or not support the limit
	BOOL                bPtzDevice;                 // Whether or not support PTZ equipment 
	BOOL                bIsSupportViewRange;        // Whether or not support PTZ visible range 
	WORD				wCamAddrMin;		    	// The minimum channel address 
	WORD				wCamAddrMax;			    // The maximum number of channel address 
	WORD				wMonAddrMin;    			// Minimum monitoring addresses
	WORD				wMonAddrMax;	    		//The maximum number of monitoring the address 
	WORD				wPresetMin;			    	// Minimum preset points
	WORD				wPresetMax;				    // The maximum preset points
	WORD				wTourMin;    				// The minimum value of automatic cruise lines 
	WORD				wTourMax;	    			// The maximum number of automatic cruise lines 
	WORD				wPatternMin;	    		// The minimum value of track circuit 
	WORD				wPatternMax;		    	// The maximum number of track circuit 
	WORD				wTileSpeedMin;			    // The minimum value of vertical speed 
	WORD				wTileSpeedMax;    			// The maximum vertical speed 
	WORD				wPanSpeedMin;	    		// The minimum value of horizontal velocity
	WORD				wPanSpeedMax;		    	// The maximum horizontal velocity 
	WORD				wAutoScanMin;			    // The minimum value of automatic scanning 
	WORD				wAutoScanMax;    			// The maximum number of automatic scanning
	WORD				wAuxMin;		    		// The minimum value of auxiliary functions 
	WORD				wAuxMax;			    	// The maximum number of auxiliary functions 

	DWORD				dwInterval;				    // Send the command time interval 
	DWORD				dwType;				        // The type of agreement, 0 - Local PTZ 1 - Remote PTZ
	DWORD				dwAlarmLen;				    // The length of the alarm of the agreement 
	DWORD				dwNearLightNumber;		    // The number of near light group, 0-4, 0 means not supported
	DWORD				dwFarLightNumber;		    // The number of beam group, 0-4, 0 means not supported
	DWORD               dwSupportViewRangeType;     // Visual field data acquisition mode supported by the mask, from low to high depending on the number , currently supported
	                                                // The first 1: 1 expressed support the "ElectronicCompass" electronic compass mode
	DWORD               dwSupportFocusMode;         // Supported Focus mode mask, from low to high depending on the number, see # EM_SUPPORT_FOCUS_MODE
	                  
	char				szName[MAX_PROTOCOL_NAME_LEN];                       // The name of the protocol operations 
	char                szAuxs[CFG_COMMON_STRING_32][CFG_COMMON_STRING_32];  //PTZ auxiliary function names list

	CFG_PTZ_MOTION_RANGE stuPtzMotionRange;         // PTZ rotation angle range, unit: degree
	CFG_PTZ_LIGHTING_CONTROL stuPtzLightingControl; // Lighting control content, this member is invalid
	BOOL				bSupportPresetTimeSection;	// Whether to support the function of the preset point time configuration 
    BOOL                bFocus;                     // Whether to support to Ptz focus
}CFG_PTZ_PROTOCOL_CAPS_INFO;
// The definition of special purpose directories 
typedef struct tagCFG_SPECIAL_DIR_INFO 
{
	char				szBackgroudImageDir[MAX_PATH];	// Screen basemap directory
	char				szWindowIconDir[MAX_PATH];		// Window icon directory 
	char				szEventVoiceDir[MAX_PATH];		// Voice prompts alarm audio file storage directory
} CFG_SPECIAL_DIR_INFO;


// After the shutdown, delay automatic boot configuration
typedef struct tagCFG_AUTO_STARTUP_DELAY_INFO
{
	BOOL	bEnable;		//Whether the function is turned on           
	int		nDelay;			//Delay on time after shutdown, the unit: minutes (range [30, 255]) 
}CFG_AUTO_STARTUP_DELAY_INFO;

// Video input capability sets (CFG_CAP_CMD_VIDEOINPUT_EX) extension configuration 
typedef struct tagCFG_CAP_VIDEOINPUT_INFO_EX
{
	BOOL            bSupportDefog;                          // Whether to support the function to penetrate the fog 
	BOOL			bSupportABFFunction;					// Whether to support the auto-focus function
	BOOL			bSupportImageStabilization;				// Whether to support the electronic image stabilization function 
	BOOL			bSupportKillShutLine;					// Whether to support the elimination of shutter function
	int             nMinKillShutLine;						// The minimum value can match 
	int			    nMaxKillShutLine;						// The maximum Can match 

    BOOL            bSupportVideoInColor;	                //Support image setup capacity or not		 
    BOOL            bSupportBrightness;                 	//Support brightness or not	
    BOOL            bSupportContrast;                       //Support contrast ot not       	
    BOOL            bSupportSaturation;                     //Support saturation or not	
    BOOL            bSupportHue;                            //Support HUE or not	
    BYTE            bReserved[3];                           //Field alignment 

}CFG_CAP_VIDEOINPUT_INFO_EX;

// CAN filter configuration 
#define MAX_CAN_COUNT	16			// The maximum number of CAN

// CAN filtering strategy 
typedef enum tagCFG_CAN_POLICY_METHOD
{
	CFG_CAN_POLICY_METHOD_UNKONW,		// Unknown Strategy
	CFG_CAN_POLICY_METHOD_NONE,			// No Filter 
	CFG_CAN_POLICY_METHOD_WHITE,		// White List
	CFG_CAN_POLICY_METHOD_BLACK,		// The blacklist 
}CFG_CAN_POLICY_METHOD;

typedef struct tagCFG_CANFILTER_INFO
{
    int                     nResponseTimeout;           // Wait for the reply timeout (unit: ms), after sending data, wait for after 3000 milliseconds, end the Reuters 
    int	                    nRequestTimeout;            // Receives the request response timeout (unit: ms), more than a specified time not yet received data, think end of the request 
    int	                    nFilterPIDCount;            // Number of data, 
    int	                    nRetFiterPIDCount;          // Returns the number of data number
    int*                    pnFilterPID;                // Filter the number of data, 
    CFG_CAN_POLICY_METHOD   emPolicy;                   // Filtering policy														
                                                        // If it is a white list, report contains the data of PID 
                                                        // If it is a blacklist, report does not contain the data of PID 
                                                        // All data reported if no filter																
}CFG_CANFILTER_INFO;

typedef struct tagCFG_CANFILTER_LIST
{
	int						nCANCount;			// The number of CAN
	int						nRetCANCount;		// Equipment Return CAN Count 
	CFG_CANFILTER_INFO		stuCANFilter[MAX_CAN_COUNT];			
}CFG_CANFILTER_LIST;

// Focus limit corresponding enumeration
typedef enum tagEM_FOCUS_LIMIT_SELECT_MODE
{
    EM_FOCUS_LIMIT_MODE_MANUAL,                // "Manual" Automatic
    EM_FOCUS_LIMIT_MODE_AUTO,                  // "Auto"Manual
    EM_FOCUS_LIMIT_MODE_INVALID
}EM_FOCUS_LIMIT_SELECT_MODE;

// Focus on setting the basic information unit 
typedef struct tagCFG_VIDEO_IN_FOCUS_UNIT
{
	int                        nMode;                   // Focused mode, 0 - closed, auxiliary focus, 1-2 - automatic focusing, 3 - semi-automatic focus, 4 - manual focusing 
	int                        nSensitivity;            // Focus Sensitivity, 0 - High 1 - default 2 - Low
	int                        nIRCorrection;           // Infrared light is focused on the modification, 0 - no correction, 1 -Fixed, 2 - automatic correction 
	EM_FOCUS_LIMIT_SELECT_MODE emFocusMode;             // Focus Limit
	int	                       nFocusLimit;				// Focusing on the limit, the unit mm 
} CFG_VIDEO_IN_FOCUS_UNIT;

// Single-channel focus setting basic information
typedef struct tagCFG_VIDEO_IN_FOCUS	
{
	int						 nChannelIndex;				             // Channel Number
	int						 nVideoInFocusRealNum;		             //Configure the number of use
	CFG_VIDEO_IN_FOCUS_UNIT  stVideoInFocusUnit[MAX_VIDEO_IN_FOCUS]; //Channel Focus configuration unit Information	
} CFG_VIDEO_IN_FOCUS;

typedef enum tagEM_ANALYSE_MODE
{
	EM_ANALYSE_MODE_REAL_STREAM,                            // Real-time Streaming Mode     
	EM_ANALYSE_MODE_RECORDFILE_STREAM,                      // Video Files Streaming Mode
	EM_ANALYSE_MODE_PICFILE_STREAM,                         // Picture File Streaming Mode
}EM_ANALYSE_MODE;

// Intelligent analysis mode
typedef struct tagCFG_ANALYSE_MODE
{
	EM_ANALYSE_MODE emMode;                                 // Analysis mode, see EM_ANALYSE_MODE
}CFG_ANALYSE_MODE;

// PTZ preset point structure
typedef struct tagPTZ_PRESET
{
	BOOL                 bEnable;                             // Whether the preset points to take effect 
	char                 szName[MAX_PTZ_PRESET_NAME_LEN];     // Preset Point Name
	CFG_PTZ_SPACE_UNIT   stPosition;                          // Coordinates and magnification preset points
}PTZ_PRESET;

// PTZ preset configuration corresponds to the structure
typedef struct tagPTZ_PRESET_INFO
{
	DWORD              dwMaxPtzPresetNum;                     // The maximum number of Preset point
	DWORD              dwRetPtzPresetNum;                     // Actual Use Preset Number 
	PTZ_PRESET         *pstPtzPreset;                         // Preset Point Information (according to the maximum number of application memory) 
}PTZ_PRESET_INFO;

// Voice-activated audio channel configuration
typedef struct tagCFG_AUDIO_SPIRIT_CHANNE
{
	int				nChannel;				// Voice incentives linked video channel number
	int				nPriority;				// Voice incentive priorities, 1 ~ 10 
	int				nPreset;				// Corresponding video camera preset point, consistent with the 0 to 255 PTZ
} CFG_AUDIO_SPIRIT_CHANNEL;

// Voice incentive linkage 
typedef struct tagCFG_AUDIO_SPIRIT_LINKAGE 
{
	int				nOutputNum;				// Number of matrix output port
	int				nOutputChanel[CFG_MAX_LOWER_MATRIX_OUTPUT];	// Synchronous output the big screen to (multiple) matrix output port
} CFG_AUDIO_SPIRIT_LINKAGE;

// Voice incentive 
typedef struct tagCFG_AUDIO_SPIRIT 
{
	BOOL				bEnable;			// Enable
	int					nAudioLimit;		// Excitation volume threshold, 0 ~ 100
	int					nDelayTime;			// Incentive delay time, unit: seconds
	CFG_AUDIO_SPIRIT_CHANNEL* pstuChannels;	// Speech excitation audio channel properties 
	int					nChannelCount;		// Number of audio channels 
	CFG_AUDIO_SPIRIT_LINKAGE stuLinkage;	// Encourage collaboration entry
} CFG_AUDIO_SPIRIT;

// the info of input channels on a output channel
typedef struct tagCFG_AUDIO_OUT_CHN
{
	BOOL	bEnable;									// the output channel is effective or not
	int		nInputChn;									// the count of input channels on this output channel(when bEnable is TRUE)
	short	snInputChannels[CFG_MAX_AUDIO_MATRIX_INPUT];//the data of input channels on this output channel(when bEnable is TRUE)
} CFG_AUDIO_OUT_CHN;

// the output channels info on a audio matrix
typedef struct tagCFG_AUDIO_MATRIX_INFO
{
	BOOL				bEnable;										// the audio matrix is effective or not
	int 				nAudioOutChn;									// the counts of outut channels under this audio matrix(when bEnable is TRUE)
	CFG_AUDIO_OUT_CHN	stuAudioOutChn[CFG_MAX_AUDIO_MATRIX_OUTPUT];	// the data of output channels under this audio matrix(when bEnable is TRUE)
} CFG_AUDIO_MATRIX_INFO;

// the config of audio matrix
typedef struct tagCFG_AUDIO_MATRIX
{
	int						nAudioMatrix;	// get/set counts of audio matrix(at most 4)
	CFG_AUDIO_MATRIX_INFO	stuAudioMatrix[CFG_MAX_AUDIO_MATRIX_NUM];	// the config of audio matrix
} CFG_AUDIO_MATRIX;


//the info of inputchannels
typedef struct tagCFG_AUDIO_SILENCE_INPUTCHN
{
	int 		nMatrix;		//the index of matrix, start from 0
	int 		nOutChannel;	//the output channel, start from 0
	int 		nInputChnConut;	//the counts of input channels
	short  		snInputChannel[CFG_MAX_AUDIO_MATRIX_INPUT]; // the data of these input channels
}CFG_AUDIO_SILENCE_INPUT_CHN;


//the configuration of audio matrix silence
typedef struct tagCFG_AUDIO_MATRIX_SILENCE
{
	int 						 nMaxInputListCount;	// the max numbers of input channels lists
	int							 nRetInputListCountOut;	// the numbers of  effective input channels lists
	CFG_AUDIO_SILENCE_INPUT_CHN *pstSilenceInputChn; 	//the input channels lists which is need to set silence
} CFG_AUDIO_MATRIX_SILENCE;


// Synthetic channel configuration
typedef struct tagCFG_COMPOSE_CHANNEL 
{
	CFG_SPLITMODE	emSplitMode;			// Segmentation mode
	int				nChannelCombination[MAX_VIDEO_CHANNEL_NUM]; // Each child window display content  in segmentation mode 
	int				nChannelCount;			// Split Window Number 
} CFG_COMPOSE_CHANNEL;

// Lower output configuration matrix 
typedef struct tagCFG_LOWER_MATRIX_OUTPUT
{
	char					szName[CFG_COMMON_STRING_128]; // Output Channel Name
	CFG_SPLITMODE			emSplitMode;		// Split mode
	int						nInputs[CFG_MAX_LOWER_MATRIX_INPUT]; // Input Channel Group 
	int						nInputCount;		// Input Channel Number 
} CFG_LOWER_MATRIX_OUTPUT;

// Lower matrix information
typedef struct tagCFG_LOWER_MATRIX_INFO 
{
	int						nOutputCount;			// Output Channel Number 
	CFG_LOWER_MATRIX_OUTPUT	stuOutputs[CFG_MAX_LOWER_MATRIX_OUTPUT]; // Output Channel Configuration 
} CFG_LOWER_MATRIX_INFO;

// Lower matrix configurations
typedef struct tagCFG_LOWER_MATRIX_LIST
{
	int						nMatrixCount;		// The number of lower matrix
	CFG_LOWER_MATRIX_INFO	stuMatrix[CFG_MAX_LOWER_MATRIX_NUM]; // Lower matrix array
} CFG_LOWER_MATRIX_LIST;

// Start and end dates 
typedef struct tagCFG_DAYTIME_INFO
{
	int					nBeginMonth;		// Start Time Month
	int					nBeginDay;			// Start date 
	int					nEndMonth;			// End Time Month
	int					nEndDay;			// End time Date 
}CFG_DAYTIME_INFO;

// Time rate limit configuration
typedef struct tagCFG_TIMESPEEDLIMIT_INFO
{
	BOOL				bEnable;			// Speed limit open
	CFG_DAYTIME_INFO	stuDayTime;			// Time start and end dates 
	int					nDaySpeedLimit;		// The values of speed limit in the daytime, the unit km/h 
	int					nNightSpeedLimit;	// The values of speed limit in the night, the unit km/h 
	CFG_TIME_SECTION	stuTimeSection;		// During the day time range, the mask is invalid
}CFG_TIMESPEEDLIMIT_INFO;

typedef struct tagCFG_TIMESPEEDLIMIT_LIST
{
	int						nTimeSpeedLimitCount;		// The speed limit number of periods 
	CFG_TIMESPEEDLIMIT_INFO stuTimeSpeedLimit[MAX_TIMESPEEDLIMIT_NUM];
}CFG_TIMESPEEDLIMIT_LIST;

// Voice prompt time 
typedef struct tagCFG_ALERTTIME_INFO
{
	int				nHour;				// Hour
	int				nMinute;			// Minute
}CFG_ALERTTIME_INFO;

// Voice prompt configuration 
typedef struct tagCFG_VOICEALERT_INFO
{
	CFG_ALERTTIME_INFO	stuAlertTime;							// Voice reminder time points?ê?timed reminder
	int					nIntervalTime;							// When the reminder interval in seconds
	char				szWarnText[CFG_COMMON_STRING_256];		// Voice reminders content, user-defined
}CFG_VOICEALERT_INFO;

typedef struct tagCFG_VOICEALERT_LIST
{
	int					nVoiceAlertCount;					// The number of voice prompt 
	CFG_VOICEALERT_INFO stuVoiceAlert[MAX_VOICEALERT_NUM];
}CFG_VOICEALERT_LIST;

// Infrared panel buttons
typedef struct tagCFG_INFRARED_KEY 
{
	char			szName[CFG_COMMON_STRING_32];	// Panel buttons name
	char			szText[CFG_COMMON_STRING_64];	// Panel buttons to display text, buttons label
} CFG_INFRARED_KEY;

// Infrared panel template 
typedef struct tagCFG_INFRARED_BOARD_TEMPLATE 
{
	unsigned int	nID;							// Panel template ID
	char			szName[CFG_COMMON_STRING_64];	// Panel Brand Model definitions
	unsigned int	nCategory;						// Panel type, categories, 0 - DVD, TV 
	int				nKeyNum;						// Panel key number 
	CFG_INFRARED_KEY stuKeys[CFG_MAX_INFRARED_KEY_NUM];	// Panel buttons
} CFG_INFRARED_BOARD_TEMPLATE;

// Infrared panel template group 
typedef struct tagCFG_INFRARED_BOARD_TEMPLATE_GROUP 
{
	int			nTemplateNum;		// Number of template 
	CFG_INFRARED_BOARD_TEMPLATE stuTemplates[CFG_MAX_INFRARED_BOARD_TEMPLATE_NUM];	// Infrared panel template 
} CFG_INFRARED_BOARD_TEMPLATE_GROUP;

// Infrared panel 
typedef struct tagCFG_INFRARED_BOARD 
{
	unsigned int	nID;							// Panel number, unique identifier
	char			szName[CFG_COMMON_STRING_64];	// Panel control peripherals name, user-defined 
	unsigned int	nCategory;						// Panel type, 0 to DVD, TV 
	int				nCommPort;						// Infrared communication port 
	unsigned int	nTemplateID;					// The associated template ID 
} CFG_INFRARED_BOARD;

//Infrared panel group 
typedef struct tagCFG_INFRARED_BOARD_GROUP
{
	int				nBoardNum;						// The number of infrared panel
	CFG_INFRARED_BOARD stuBoards[CFG_MAX_INFRARED_BOARD_NUM];	// Infrared panel information 	
} CFG_INFRARED_BOARD_GROUP;

// Device keep alive configuration
typedef struct tagCFG_DEVICEKEEPALIVE_INFO
{
	BOOL	bEnable;		// Open the keep-alive enabled
	int		nInterval;		// Keep alive interval, must be > = 10 the value of the unit: second 
	int		nFailTimes;		// The number of Keep alive failures,?ê?failures to reach the keep-alive value assumes that the device disconnected
	int		nWaitBootTime;	// Wait peripherals start after power detect the keep alive heartbeat  unit: seconds
}CFG_DEVICEKEEPALIVE_INFO;

// Device exposure the basic configuration information 
typedef struct tagCFG_VIDEOIN_EXPOSURE_BASE
{
    BOOL        bSlowShutter;           // Slow shutter enabled

    BYTE        byExposureMode;         // Exposure mode adjustment
    BYTE        byAntiFlicker;			// Anti-flicker mode 0-Outdoor 1-50Hz A.FLK 2-60Hz flicker prevention
    BYTE        byCompensation;         // Exposure compensation, [0-14]
    BYTE        byAutoGainMax;          // Automatic gain limit, [0, 2) 
    BYTE        byGain;                 // Gain gear, [0, 15] 
    BYTE        bySlowAutoExposure;     // Slow exposure, [0, 15] 
    BYTE        bybyReserv[2];          // reserved
    int         byExposureSpeed;        // Exposure level of speed: 0 - Auto Exposure 1 - Exposure Level 1,2 - Exposure Level 2 ... n-1 the maximum exposure level, n the time limit with automatic exposure, n +1 custom time manual exposure (n means support the exposure level)
    BYTE        bySlowSpeed;            // Slow exposure level 
    BYTE        byIris;                 // Aperture Settings, [0 ~ 17] 
    BYTE        byBacklight;            // BLC: The range depends on the device capability set: 0 - off 1 - Enable 2 - designated areas BLC
    BYTE        byWideDynamicRange;     // Wide dynamic value 0 - closed, range 1-100 - for real value 
    BYTE        byWideDynamicRangeMode; // Wide dynamic mode 0: off; 1: manual adjustment; 2: automatic adjustment
    BYTE        byGlareInhibition;      // Light inhibition 0: Off; 1: weak; 2: Medium; 3: Strong
    BYTE        byDoubleExposure;       // Dual shutter support, 0: not supported; 1: Support Dual Shutter full frame rate; 2: supports dual shutter half frame rate; 3: supports dual shutter half full frame rate and frame rate
    BYTE        byReserved;             // Byte alignment
    int         nRecoveryTime;          // Automatic exposure recovery, 0 - said they did not recover, others said recovery time, in seconds

    float       fValue1;                // Automatic exposure time limit or manual custom time, [0.1 ~ 80 ms] 
    float       fValue2;                // Automatic exposure time limit, to be not less than the lower limit, [0.1 ~ 80ms]
    CFG_RECT    stuBacklightRegion;     // BLC area
}CFG_VIDEOIN_EXPOSURE_BASE;

// Device exposure configuration
typedef struct tagCFG_VIDEOIN_EXPOSURE_INFO
{
    DWORD                       dwMaxExposureNum;       // the maximum number of Configure
    DWORD                       dwRetExposureNum;       // The maximum number of actual use(query returns the actual number parsing, according to the number of this value when the packaging) 
    CFG_VIDEOIN_EXPOSURE_BASE   *pstuVideoInExposure;   // Exposure configuration information
}CFG_VIDEOIN_EXPOSURE_INFO;

//////////////////////////////////////////////////////////////////////////
// Access Basic Configuration

// Customize to open the door
typedef enum tagCFG_DOOR_OPEN_METHOD
{
	CFG_DOOR_OPEN_METHOD_UNKNOWN                        = 0,
	CFG_DOOR_OPEN_METHOD_PWD_ONLY,                              // Allowing only password lock
	CFG_DOOR_OPEN_METHOD_CARD,                                  // Only allow swipe to unlock
	CFG_DOOR_OPEN_METHOD_PWD_OR_CARD,                           // Password or swipe to unlock 
	CFG_DOOR_OPEN_METHOD_CARD_FIRST,                            // Firstly swipe then password to unlock
    CFG_DOOR_OPEN_METHOD_PWD_FIRST,	                            // Firstly passwords,then swipe to unlock
	CFG_DOOR_OPEN_METHOD_SECTION,                               // Period of time to open the door 
    CFG_DOOR_OPEN_METHOD_FINGERPRINTONLY                = 7,    // Only allow finger print to unlock
    CFG_DOOR_OPEN_METHOD_PWD_OR_CARD_OR_FINGERPRINT     = 8,    // Allow passwords or card or finger print to unlock
    CFG_DOOR_OPEN_METHOD_PWD_AND_CARD_AND_FINGERPINT    = 9,    // Password and swip and finger print combined to unlock
    CFG_DOOR_OPEN_METHOD_PWD_AND_FINGERPRINT            = 10,   // Password and finger print combined to unlock
    CFG_DOOR_OPEN_METHOD_CARD_AND_FINGERPRINT           = 11,   // Allow card and finger print to unlock
    CFG_DOOR_OPEN_METHOD_MULTI_PERSON                   = 12,   // Only allow multi persons together to unlock
}CFG_DOOR_OPEN_METHOD;


// access control one/two way config type
typedef enum tagCFG_ACCESS_PROPERTY_TYPE
{
    CFG_ACCESS_PROPERTY_UNKNOWN = 0,
    CFG_ACCESS_PROPERTY_BIDIRECT,       // dual way access control
    CFG_ACCESS_PROPERTY_UNIDIRECT,      // one way access control
}CFG_ACCESS_PROPERTY_TYPE;

#define CFG_MAX_ABLOCK_DOORS_NUM        4                       // Max access control door lock channel number

// Access control AB lock group
typedef struct tagCFG_ABLOCK_DOOR_INFO 
{
    int                 nDoor;                                  // Valid lock number
    int                 anDoor[CFG_MAX_ABLOCK_DOORS_NUM];       // Lock door channel no.
}CFG_ABLOCK_DOOR_INFO;

#define CFG_MAX_ABLOCK_GROUP_NUM        8                       // Max lock group

// Access control AB lock function, multi-door channel?ê?only other B channel close?ê?only A channel can open
typedef struct tagCFG_ABLOCK_INFO 
{
    BOOL                bEnable;                                // Enable
    int                 nDoors;                                 // Valid lock group
    CFG_ABLOCK_DOOR_INFO stuDoors[CFG_MAX_ABLOCK_GROUP_NUM];    // Lock group info 
}CFG_ABLOCK_INFO;

// Access Basic Configuration
typedef struct tagCFG_ACCESS_GENERAL_INFO
{
	char                szOpenDoorAudioPath[MAX_ADDRESS_LEN];   // Open the audio file path 
	char                szCloseDoorAudioPath[MAX_ADDRESS_LEN];  // Shut down the audio file path 
	char                szInUsedAuidoPath[MAX_ADDRESS_LEN];     // Some audio file path
	char                szPauseUsedAudioPath[MAX_ADDRESS_LEN];  // Suspension of the audio file path 
	char                szNotClosedAudioPath[MAX_ADDRESS_LEN];  // The door is not closed audio file path
	char                szWaitingAudioPath[MAX_ADDRESS_LEN];    // Wait for the prompt audio file path
	int                 nUnlockReloadTime;                      // Unlock command response interval, in seconds, the value 10,15 (default), 20
	int                 nUnlockHoldTime;                        // Unlock Output hold time, in seconds, the value 1,2 (default), 3,4,5,6,9,15.

	// Capacity.
	bool                abProjectPassword;
    bool                abAccessProperty;
    bool                abABLockInfo;
	BYTE				byReserved;

	char				szProjectPassword[MAX_PASSWORD_LEN];	// Project Password
    CFG_ACCESS_PROPERTY_TYPE emAccessProperty;                  // access control channel one/two way config
    CFG_ABLOCK_INFO     stuABLockInfo;                          // AB lock info 
}CFG_ACCESS_GENERAL_INFO;

// Access status
typedef enum CFG_ACCESS_STATE
{
	ACCESS_STATE_NORMAL,                                        // General
	ACCESS_STATE_CLOSEALWAYS,                                   // Normally Off, open door is invalid 
	ACCESS_STATE_OPENALWAYS,                                    // Normally On, open door is invalid
    ACCESS_STATE_NOPERSONNC,                                    // Normally Off if in NO PERSON state
    ACCESS_STATE_NOPERSONNO                                     // Normally On if in NO PERSON state
}CFG_ACCESS_STATE; 

// Access mode
typedef enum CFG_ACCESS_MODE
{
	ACCESS_MODE_HANDPROTECTED,                                  // Fangga mode
	ACCESS_MODE_SAFEROOM,                                       // Protective room mode    
	ACCESS_MODE_OTHER,                                          // others
}CFG_ACCESS_MODE;


// Period of time to open the door 
typedef struct tagCFG_DOOROPEN_TIMESECTION_INFO
{
	CFG_TIME_PERIOD			stuTime;				// Period of time 
	CFG_DOOR_OPEN_METHOD	emDoorOpenMethod;		// Open Mode 
}CFG_DOOROPEN_TIMESECTION_INFO;

#define MAX_DOOR_TIME_SECTION		4				// Access the maximum number of daily time-period

// First card right verification passed access control status
typedef enum CFG_ACCESS_FIRSTENTER_STATUS
{
	ACCESS_FIRSTENTER_STATUS_UNKNOWN,	// Unknown status
	ACCESS_FIRSTENTER_STATUS_KEEPOPEN,	// KeepOpen-first card right verification passed, door remains NO
	ACCESS_FIRSTENTER_STATUS_NORMAL		// Normal-first card right verification passed, other user can swipe card (fingerprint and so on) to pass verification
}CFG_ACCESS_FIRSTENTER_STATUS;

// First card unlock info 
typedef struct tagCFG_ACCESS_FIRSTENTER_INFO
{
	BOOL							bEnable;	// Within certain period, only when user with first card right passes verification, other users can swipe card (fingerprint and so on) to enter, TRUE enable FALSE off
	CFG_ACCESS_FIRSTENTER_STATUS	emStatus;	// First card right verification passed accesscontrol status
	int								nTimeIndex;	// Need first card verification period, value as channel no.
}CFG_ACCESS_FIRSTENTER_INFO;

// Remote check detail
typedef struct tagCFG_REMOTE_DETAIL_INFO 
{
    int                 nTimeOut;                       // over time, 0:unlimited wait, unit: sec
    BOOL                bTimeOutDoorStatus;             // door status after over time, TRUE:open, FALSE:close
}CFG_REMOTE_DETAIL_INFO;

// time out info for handicap
typedef struct tagCFG_HANDICAP_TIMEOUT_INFO
{
    int                 nUnlockHoldInterval;            // Unlock hold time(max time to close door automatically),unit: ms, [250, 60000]  
    int                 nCloseTimeout;                  // max time to close door, there will be alarm if door still open after max time; unit: s,[0,9999];0 means do not check the time out
}CFG_HANDICAP_TIMEOUT_INFO;

// remote check to open door
typedef struct tagCFG_AUTO_REMOTE_CHECK_INFO
{
    BOOL                bEnable;                        // enable auto remote check to open door, TRUE: ENABLE, FALSE: DISABLE
    int                 nTimeSechdule;                  // corresponding to index of config "CFG_CMD_ACCESSTIMESCHEDULE"
}CFG_AUTO_REMOTE_CHECK_INFO;

// Access Event Configuration
typedef struct tagCFG_ACCESS_EVENT_INFO
{
	char                szChannelName[MAX_NAME_LEN];	// Access Channel Name
	CFG_ACCESS_STATE    emState;						// Access Status
	CFG_ACCESS_MODE     emMode;							// Access Mode
	int					nEnableMode;					// Enable access level value, 0: active low (powered down start); 1: active high (power-up);
	BOOL                bSnapshotEnable;				// Event linkage screenshots can make
	
    // Ability
	bool                abDoorOpenMethod;
    bool                abUnlockHoldInterval;
	bool                abCloseTimeout;
	bool                abOpenAlwaysTimeIndex;
    bool                abCloseAlwaysTimeIndex;
	bool                abHolidayTimeIndex;
	bool                abBreakInAlarmEnable;
	bool				abRepeatEnterAlarmEnable;
	bool                abDoorNotClosedAlarmEnable;
	bool				abDuressAlarmEnable;
	bool                abDoorTimeSection;
	bool				abSensorEnable;
	bool				abFirstEnterEnable;
    bool                abRemoteCheck;
    bool                abRemoteDetail;
    bool                abHandicapTimeOut;
    bool                abCheckCloseSensor;
    bool                abAutoRemoteCheck;
    BYTE                reverse[2];

	CFG_DOOR_OPEN_METHOD	emDoorOpenMethod;			// Open the door way 
	int					nUnlockHoldInterval;			// Lock hold time (automatic closing time), in milliseconds, [250, 20000]
	int					nCloseTimeout;					// Closed timeout, more than threshold value are not closed will trigger the alarm, unit of seconds, [0999]; 0 means no detection timeout 
	int					nOpenAlwaysTimeIndex;			// always open time period, subscript of CFG ACCESS_TIME SCHEDULEINFO array
    int                 nCloseAlwaysTimeIndex;          // always close time period, subscript of CFG ACCESS_TIME SCHEDULEINFO array
	int					nHolidayTimeRecoNo;				// Within the holiday period, value of holiday record set record number, corresponding NET_RECORDSET_HOLIDAY nRecNo 
	BOOL				bBreakInAlarmEnable;			// Intrusion alarm enable
	BOOL				bRepeatEnterAlarm;				// Antisubmarine alarm enable
	BOOL				bDoorNotClosedAlarmEnable;		// The door is not closed alarm enable
	BOOL				bDuressAlarmEnable;				// Duress alarm enable
	CFG_DOOROPEN_TIMESECTION_INFO	stuDoorTimeSection[WEEK_DAY_NUM][MAX_DOOR_TIME_SECTION];// The information period of time to open the door 
	BOOL				bSensorEnable;					//Magnetic enable
	CFG_ACCESS_FIRSTENTER_INFO stuFirstEnterInfo;		// First card unlock info 
    BOOL                bRemoteCheck;                   // Need platform verification, TRUE means when right verification is passed, you must pass platform verification before you can unlock, FALSE means when right verification is passed, you can unlock
    CFG_REMOTE_DETAIL_INFO  stuRemoteDetail;            // work with "bRemoteCheck", door will open or close after over time if remove check on platform side is not responsed
    CFG_HANDICAP_TIMEOUT_INFO   stuHandicapTimeOut;     // time out info for handicap
    BOOL                bCloseCheckSensor;              // check the lock sensor or not before close
    CFG_AUTO_REMOTE_CHECK_INFO  stuAutoRemoteCheck;     // remote check to open door, if enabled, controller will send "DH_ALARM_OPENDOORGROUP" event to notify platform whether to open door
    BOOL                bLocalControlEnable;            // Enable local control, TRUE: enable, FALSE: disable
    BOOL                bRemoteControlEnable;           // Enable remote control, TRUE: enable, FALSE: disable
    int                 nSensorDelay;                   // Sensor output delay, unit: sec, 0~10
    int                 nHumanStatusSensitivity;        // Detect sensitivity of human status, unit: sec, 0~300
    int                 nDetectSensitivity;             // Detect sensitivity of sensor itself, unit: %, 0~100             
}CFG_ACCESS_EVENT_INFO;



// Access control card time
typedef struct tagCFG_ACCESS_TIMESCHEDULE_INFO 
{
	CFG_TIME_SECTION		stuTime[WEEK_DAY_NUM][MAX_DOOR_TIME_SECTION];	// Charge Time 
	BOOL					bEnable;										// Period of time to enable the switch
}CFG_ACCESS_TIMESCHEDULE_INFO;

//////////////////////////////////////////////////////////////////////////
// Wireless network configuration 

// Daily traffic control strategy
enum EM_CFG_DAY3GFLUXTACTIC
{
	EM_CFG_DAY3GFLUXTACTIC_BYFLUX = 0,	// By traffic
	EM_CFG_DAY3GFLUXTACTIC_BYTIME,		// By time
};

// the name of the network access 
enum EM_CFG_APN
{
	EM_CFG_APN_CTNET = 0,				// CTNET
};

// Traffic police tactics
enum EM_CFG_DAY3GFLUXACTION
{
	EM_CFG_DAY3GFLUXACTION_NOTHING = 0,	// No Action
	EM_CFG_DAY3GFLUXACTION_3GNETDOWN,	// 3G offline
};

typedef struct tagCFG_WIRELESS_INFO
{
	BOOL			bEnable;						// 2G Network Enables
	int				nKeepAlive;						// Keep-alive time, in seconds, 0 means always connected, does not automatically disconnect
	EM_CFG_APN		emAPN;							// the name of the 2G network access 
	char			szUseName[MAX_USERNAME_LEN];	// User Name
	char			szPassword[MAX_PASSWORD_LEN];	// Password
	EM_CFG_DAY3GFLUXTACTIC	emDay3GFluxTactic;		// Daily Traffic Control Strategy
	DWORD			dwDay3GFluxUp;					// Daily Traffic Usage Limit, MB or minute
	DWORD			dwDay3GFluxUse;					// Used Traffic Day, MB or minute
	EM_CFG_DAY3GFLUXACTION	emDay3GFluxAction;		// Traffic police tactics
	CFG_TIME_SECTION        stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Time sections
}CFG_WIRELESS_INFO;

#define MAX_CONNECTION_TYPE_LEN		32	// The length of the connection type name

// Having time to type 
enum emCFG_REPORTWEEKDAY
{
	emReportWeekDay_DoNotReport = -1,	// Not advertised
	emReportWeekDay_Sunday,				// Every Sunday Regular Reports
	emReportWeekDay_Monday,				// Every Monday Regular Reports
	emReportWeekDay_Tuesday,			// Every Tuesday Regular Reports
	emReportWeekDay_Wednesday,			// Every Wednesday Regular Reports
	emReportWeekDay_Thursday,			// Every Thursday Regular Reports
	emReportWeekDay_Friday,				// Every Friday Regular Reports
	emReportWeekDay_Saturday,			// Every Saturday Regular Reports
	emReportWeekDay_Everyday,			// Regular Daily Reports
};

// The configure of alarm server
typedef struct tagCFG_ALARMSERVER_INFO
{
	BOOL			bEnable;								// Enable
	char			szProtocol[MAX_PROTOCOL_NAME_LEN];		// Protocol type, currently supports "DAHUA"
	char			szConnection[MAX_CONNECTION_TYPE_LEN];	// Connection type
	char			szAddress[MAX_ADDRESS_LEN];				// IP address or network name
	int				nPort;									// Port number
	char			szUserName[MAX_USERNAME_LEN];			// User name
	char			szPsw[MAX_PASSWORD_LEN];				// Password
	emCFG_REPORTWEEKDAY	emReportWeekDay;					// Reporting date
	int				nHour;									// Point in time when the report
	int				nMinute;								// The Minute of the report time
	int				nSecond;								// The Second of the report time
}CFG_ALARMSERVER_INFO;

#define MAX_ALARMSERVER_NUM		8

// Alarm host use alarm center and backup center configuration 
typedef struct tagCFG_ALARMCENTER_INFO
{
	CFG_ALARMSERVER_INFO	stuMainServer;						// Alarm host use alarm center server 
	int						nBackupAlarmServerNum;				// The number of backup alarm center server
	CFG_ALARMSERVER_INFO	stuBackupAlarmServer[MAX_ALARMSERVER_NUM];	// Backup alarm center server configuration 
}CFG_ALARMCENTER_INFO;

//////////////////////////////////////////////////////////////////////////
// Arm, disarm configuration

#define	MAX_SCENE_COUNT	8		//	Maximum number of scenarios

// Scene mode 
typedef enum tagemCFG_SCENE_MODE
{	
	emCFG_SCENE_MODE_UNKNOWN,			// Unknown mode
	emCFG_SCENE_MODE_OUTDOOR,			// AWAY Mode
	emCFG_SCENE_MODE_INDOOR,			// Home mode
    emCFG_SCENE_MODE_WHOLE ,            // global mode
    emCFG_SCENE_MODE_RIGHTNOW,          // instant mode
    emCFG_SCENE_MODE_AUTO,              // auto mode
    emCFG_SCENE_MODE_FORCE,             // duress mode
}emCFG_SCENE_MODE;

typedef struct tagCFG_SCENE_INFO
{
	emCFG_SCENE_MODE emName;							// Mode Name
	int				 nAlarmInChannelsCount;				// Number of alarm channel
	int				 nRetAlarmInChannelsCount;			// The number of alarm channel in the actual return 
	int*			 pnAlarmInChannels;					// Enable the alarm input channel number list, need to user memory 
}CFG_SCENE_INFO;

// CommGlobal(for arm/disarm configuration), corresponding to cmd(CFG_CMD_COMMGLOBAL)
// nSceneCount and stuScense[MAX_SCENE_COUNT] are enabled only when device type is "AS5008", 
// otherwise use "bSceneEnable" and "emCurrentScene" instead
typedef struct tagCFG_COMMGLOBAL_INFO	// =>CFG_CMD_COMMGLOBAL
{
    BOOL                bEnable;                            // TRUE: Arming; FALSE: disarm; acting on the entire device, does not distinguish between channels
    BOOL                bSceneEnable;                       // Whether to enable scene mode 
    emCFG_SCENE_MODE    emCurrentScene;                     // The currently selected scene mode 
    int                 nSceneCount;                        // Effective number of scenarios mode
    CFG_SCENE_INFO      stuScense[MAX_SCENE_COUNT];         // Profiles define each mode corresponds to a configuration
}CFG_COMMGLOBAL_INFO;

#define MAX_ALARM_LIMITS_NUM    8                                   // alarm limit max


// Analog alarm input channel configuration
typedef struct tagCFG_ANALOGALARM_INFO	// =>CFG_CMD_ANALOGALARM
{
	BOOL				bEnable;									// Enable switch (the entire device is armed and enabled the passage of non-bypass)
	char				szChnName[MAX_CHANNELNAME_LEN];				// Alarm channel name
	float				fUpperLimit;								// Maximum range 
	float				fLowerLimit;								// The subscript range 
	int					nSensitivity;								// Sensitivity, Unit: Percent
	float				fCompensation;								// The compensation value, depending on the type of sensor 
	float				fLimit1;									// Alarm limit 1
	float				fLimit2;									// Alarm limit 2
	float				fLimit3;									// Alarm limit 3
	float				fLimit4;									// Alarm limit 4
	BYTE				byMode;										// Alarm mode, mask said, may the following values 1111, 1110, 1100, 1110, 1100 
																	// 1 indicates that exceeds the alarm threshold, 0 means below the alarm threshold
																	// From left to right pattern corresponding to four alarm thresholds, in ascending order
																	// Example: 1110 said more than 1, 2, 3 alarm threshold, and lower than the fourth alarm threshold 
	BYTE				byReserve[3];								// Reserved bytes
	CFG_ALARM_MSG_HANDLE	stuEventHandler;						// Alarm linkage 
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
	EM_SENSE_METHOD		emSense;									// Sensor method
	char				szSensorType[CFG_COMMON_STRING_64];			// Sensor type
    int                 nSlot;                                      // Root address, 0 means local channel, 1 means extention channel connected to 1st serial, 2, 3...and so on 
	int                 nLevel1;                                    // 1st level cascading address, means connected to no. nSlot serial no.nLevel1 detector or meter, from 0
    bool                abLevel2;                                   // means if nLevel2 text exists or not
    int                 nLevel2;                                    // 2nd cascadingaddress, means connected to no. nLevel1 meter detector no., from 0
    int                 nAlamrLimits;                               // valid alarm limit number
    float               fAlarmLimits[MAX_ALARM_LIMITS_NUM];         // alarm limit
    int                 nNotifyInterval;                            // analog quantity upload period, unit: s
    int                 nAlarmInterval;                             // upload period after limit, unit: s
}CFG_ANALOGALARM_INFO;

// The state of the alarm output channel configuration 
typedef struct tagCFG_ALARMOUT_INFO		// =>CFG_CMD_ALARMOUT
{
	int					nChannelID;									// Alarm channel number (from zero)
	char				szChnName[MAX_CHANNELNAME_LEN];				// Alarm channel name
	char				szOutputType[MAX_NAME_LEN];					// Output types, user-defined
	int					nOutputMode;								// Output mode, 0 - automatic alarm 1 - Forced Alarm 2 - Turn off the alarm
    int                 nPulseDelay;                                // Pulse mode output time, unit is second(0-255s)
    int                 nSlot;                                      // Root address, 0 means local channel, 1 means connection expansion channel on first serial, 2??é3...and so on, -1 means invalid
    int                 nLevel1;                                    // First level cascading address, means connected at no. nSlot serial no. nLevel1 sensor or meter, start from 0, -1 means invalid
    bool                abLevel2;                                   // means nLevel2 field exists or not
    int                 nLevel2;                                    // Second level cascading address, means connected at no. nLevel1 meter sensor no., start from 0
}CFG_ALARMOUT_INFO;


// Time zone definitions (NTP)
typedef enum __EM_CFG_TIME_ZONE_TYPE
{
	EM_CFG_TIME_ZONE_0,								// {0, 0*3600,"GMT+00:00"}
	EM_CFG_TIME_ZONE_1,								// {1, 1*3600,"GMT+01:00"}
	EM_CFG_TIME_ZONE_2,								// {2, 2*3600,"GMT+02:00"}
	EM_CFG_TIME_ZONE_3,								// {3, 3*3600,"GMT+03:00"}
	EM_CFG_TIME_ZONE_4,								// {4, 3*3600+1800,"GMT+03:30"}
	EM_CFG_TIME_ZONE_5,								// {5, 4*3600,"GMT+04:00"}
	EM_CFG_TIME_ZONE_6,								// {6, 4*3600+1800,"GMT+04:30"}
	EM_CFG_TIME_ZONE_7,								// {7, 5*3600,"GMT+05:00"}
	EM_CFG_TIME_ZONE_8,								// {8, 5*3600+1800,"GMT+05:30"}
	EM_CFG_TIME_ZONE_9,								// {9, 5*3600+1800+900,"GMT+05:45"}
	EM_CFG_TIME_ZONE_10,							// {10, 6*3600,"GMT+06:00"}
	EM_CFG_TIME_ZONE_11,							// {11, 6*3600+1800,"GMT+06:30"}
	EM_CFG_TIME_ZONE_12,							// {12, 7*3600,"GMT+07:00"}
	EM_CFG_TIME_ZONE_13,							// {13, 8*3600,"GMT+08:00"}
	EM_CFG_TIME_ZONE_14,							// {14, 9*3600,"GMT+09:00"}
	EM_CFG_TIME_ZONE_15,							// {15, 9*3600+1800,"GMT+09:30"}
	EM_CFG_TIME_ZONE_16,							// {16, 10*3600,"GMT+10:00"}
	EM_CFG_TIME_ZONE_17,							// {17, 11*3600,"GMT+11:00"}
	EM_CFG_TIME_ZONE_18,							// {18, 12*3600,"GMT+12:00"}
	EM_CFG_TIME_ZONE_19,							// {19, 13*3600,"GMT+13:00"}
	EM_CFG_TIME_ZONE_20,							// {20, -1*3600,"GMT-01:00"}
	EM_CFG_TIME_ZONE_21,							// {21, -2*3600,"GMT-02:00"}
	EM_CFG_TIME_ZONE_22,							// {22, -3*3600,"GMT-03:00"}
	EM_CFG_TIME_ZONE_23,							// {23, -3*3600-1800,"GMT-03:30"}
	EM_CFG_TIME_ZONE_24,							// {24, -4*3600,"GMT-04:00"}
	EM_CFG_TIME_ZONE_25,							// {25, -5*3600,"GMT-05:00"}
	EM_CFG_TIME_ZONE_26,							// {26, -6*3600,"GMT-06:00"}
	EM_CFG_TIME_ZONE_27,							// {27, -7*3600,"GMT-07:00"}
	EM_CFG_TIME_ZONE_28,							// {28, -8*3600,"GMT-08:00"}
	EM_CFG_TIME_ZONE_29,							// {29, -9*3600,"GMT-09:00"}
	EM_CFG_TIME_ZONE_30,							// {30, -10*3600,"GMT-10:00"}
	EM_CFG_TIME_ZONE_31,							// {31, -11*3600,"GMT-11:00"}
	EM_CFG_TIME_ZONE_32,							// {32, -12*3600,"GMT-12:00"}
}EM_CFG_TIME_ZONE_TYPE;

// Time Synchronization Server Configuration
typedef struct tagCFG_NTP_INFO
{
	BOOL				bEnable;									// Enable switch
	char				szAddress[MAX_ADDRESS_LEN];					// IP address or network name
	int					nPort;										// Port number
	int					nUpdatePeriod;								// Update cycle, in minutes.
	EM_CFG_TIME_ZONE_TYPE emTimeZoneType;							// Time zone
	char				szTimeZoneDesc[MAX_NAME_LEN];				// Time zone description
}CFG_NTP_INFO;

//Alarm configuration
typedef struct tagCFG_ALARMBELL_INFO
{
    int                 nPersistentTime;                            // Duty cycle
}CFG_ALARMBELL_INFO;

#define MAX_MSG_NUMBER_LEN	32				// The maximum length of the message numbers
#define MAX_RECEIVER_NUM	100				// The maximum number of users to receive messages

// SMS type
typedef enum tagEM_MSG_TYPE
{
	EM_MSG_UNKNOWN = 0,												// Unknown Type
	EM_MSG_SMS,														// SMS messages
	EM_MSG_MMS,														// MMS 
}EM_MSG_TYPE;

// System event trigger configuration MMS / SMS sent
typedef struct tagCFG_EVENT_MSG_SENDING_INFO
{
	BOOL				bEnable;									// Enable switch
	EM_MSG_TYPE			emMsgType;									// Types of information transmitted
	char				szTitle[MAX_NAME_LEN];						// The title, which is the first line of SMS / MMS text
	DWORD				dwReceiverCount;							// The number of the recipient number
	char				szReceiverNumbersList[MAX_RECEIVER_NUM][MAX_MSG_NUMBER_LEN];// Recipient number
}CFG_EVENT_MSG_SENDING_INFO;

// Mobile-related service configuration
typedef struct tagCFG_MOBILE_INFO
{
	CFG_EVENT_MSG_SENDING_INFO	stuEventMsgSending;					// Send SMS system time-triggered / MMS Configuration
}CFG_MOBILE_INFO;

#define MAX_CONTACT_NUM		100				// Maximum number of contacts

// Telephone voice reminds configuration
typedef struct tagCFG_PHONEEVENTNOTIFY_INFO
{
	BOOL				bEnable;									// Enable switch
	DWORD				dwContactCount;								// The number of call numbers
	char				szContactNumbersList[MAX_CONTACT_NUM][MAX_MSG_NUMBER_LEN];// Call number list
}CFG_PHONEEVENTNOTIFY_INFO;

// Telephone Alarm Center Configuration
enum CFG_EM_SIGNALTRANSMIT_MODE
{
	CFG_EM_SIGNALTRANSMIT_ERROR = 0,								// Unknown Mode
	CFG_EM_SIGNALTRANSMIT_DTMF_5S,									// "DTMF 5/S" - DTMF mode dial slowly
	CFG_EM_SIGNALTRANSMIT_DTMF_10S,									// "DTMF 10/S" - DTMF mode speed dial
};
enum CFG_EM_PSTN_PROTOCOL_TYPE
{
	CFG_EM_PSTN_PROTOCOL_ERROR = 0,									// Unknown Mode
	CFG_EM_PSTN_PROTOCOL_CID,										// "CID" - Contact ID Protocol
};
typedef struct tagCFG_PSTN_ALARM_SERVER_INFO
{
	char							szName[MAX_NAME_LEN];						// Phone alarm center name
	char							szNumber[MAX_PHONE_NUMBER_LEN];				// Phone numbers alarm center receiver
																				// "057188888888PPP888",The format is [number] [pauses] [ext], where P represents pause two seconds??ê
	CFG_EM_PSTN_PROTOCOL_TYPE		emProtocol;									// Protocol type?ê?
	CFG_EM_SIGNALTRANSMIT_MODE		emMode;										// Signal transmission mode																															
	int								nTryCount;									// Dialing Attempts
	int								nDelay;										// Dial-up delay, Unit: sec
	char							szAccount[MAX_PHONE_NUMBER_LEN];			// User ID
}CFG_PSTN_ALARM_SERVER_INFO;

typedef struct tagCFG_PSTN_ALARM_CENTER_INFO
{
	BOOL						bEnable;								// Enable switch
	int							nServerCount;							// Phone number of alarms server
	CFG_PSTN_ALARM_SERVER_INFO	stuPSTNAlarmServer[MAX_PSTN_SERVER_NUM];		// Telephone alarm server
}CFG_PSTN_ALARM_CENTER_INFO;

// Volume input configuration
typedef struct tagCFG_AUDIO_INPUT_VOLUME
{
	int				nAudioInputCount;									// The actual number of audio input channels
	char			szAudioInputVolume[MAX_AUDIO_INPUT_NUM];			// Each element corresponds to a volume value of the audio input channels, the range [0, 100]
}CFG_AUDIO_INPUT_VOLUME;


// Volume output configuration
typedef struct tagCFG_AUDIO_OUTPUT_VOLUME
{
	int				nAudioOutputCount;									// The actual number of audio output channels
	char			szAudioOutputVolume[MAX_AUDIO_OUTPUT_NUM];			// Each element corresponds to a volume value of the audio output channels, the range [0, 100]
}CFG_AUDIO_OUTPUT_VOLUME;

// Volume mix configuration
typedef struct tagCFG_AUDIO_MIX_VOLUME
{
	int				nAudioMixCount;										// The actual number of audio mix channels
	char			szAudioMixVolume[MAX_AUDIO_MIX_NUM];				// Each element corresponds to a volume value of the audio mix channels, the range [0, 100]
}CFG_AUDIO_MIX_VOLUME;



// Alarm keyboard layout
typedef struct tagCFG_ALARMKEYBOARD_INFO
{
	BOOL			bEnable;								//Enable Switch
	char			szProtocolName[MAX_PROTOCOL_NAME_LEN];	// Name of Agreement
	int				nPort;									// Serial port number to use
	int				nAddress;								// Device address, if more than one serial port devices hung by distinguishing this address
	CFG_COMM_PROP	stuCommAttr;							// Serial property
}CFG_ALARMKEYBOARD_INFO;

// Get the file management capabilities
typedef struct tagCFG_CAP_FILEMANAGER
{
	int			nMaxUploadFileSize;		// Maximum upload file size, unit: byte
}CFG_CAP_FILEMANAGER;

// The ability to obtain equipment alarm linkage
typedef struct tagCFG_CAP_EVENTMANAGER_INFO
{
	BOOL				bTimeSectionEnable;                               // Whether to support incident response time
	BOOL				bRecordEnable;                                    // Whether to support video
	BOOL				bAlarmOutEnable;                                  // Whether to support alarm output
	BOOL				bPtzLinkEnable;                                   // Whether to support PTZ linkage
	BOOL				bSnapshotEnable;                                  // Whether to support snapshot 
	BOOL				bMailEnable;                                      // Whether to support send e-mail 
	BOOL				bBeepEnable;                                      // Whether to support the buzzer
	BOOL				bDejitterEnable;                                  // Whether to support the de-jitter
	BOOL				bTipEnable;										  // Whether to support the local message box prompts
	BOOL				bMonitorTourEnable;								  // Whether to polling linkage configuration 
	BOOL				bMMSEnable;										  // Whether to support the short message
	BOOL				bSupportAlarmBell;								  // Whether to support alarm bell output
	BOOL				bSupportAccessControl;							  // Whether to support access control
	BOOL				bSupportAlarmServer;							  // Whether to uploaded to the alarm server 
	BOOL				bSupportPtzLinkDelay;							  // Whether to support PTZ linkage delay
	BOOL				bSupportPSTNAlarmServer;						  // Whether to support telephone is uploaded to the alarm center
    BOOL                bVoiceEnable;                                     // Whether to support voice prompt
}CFG_CAP_EVENTMANAGER_INFO;

// Power failure configuration
typedef struct tagCFG_POWERFAULT_ONE
{
	BOOL			bEnable;									// Enable switch
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// alarmLinkage
}CFG_POWERFAULT_ONE;

typedef struct tagCFG_POWERFAULT_INFO
{
	int				nPowerCount;								// Power Number
	CFG_POWERFAULT_ONE stuPowerFault[MAX_POWER_NUM];			// alarmLinkage
}CFG_POWERFAULT_INFO;

// Chassis intrusion alarm (tamper alarm) configuration
typedef struct tagCFG_CHASSISINTRUSION_INFO
{
	BOOL			bEnable;									// Enable switch
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// alarmLinkage
}CFG_CHASSISINTRUSION_INFO;

// Emergency configuration
typedef struct tagCFG_URGENCY_INFO 
{
	BOOL			bEnable;									// Enable switch
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// alarmLinkage
}CFG_URGENCY_INFO;

/************************************************************************
** Extend the alarm module
***********************************************************************/
// Extension module alarm input configuration 
typedef struct tagCFG_EXALARMINPUT_INFO
{
	CFG_ALARMIN_INFO		stuAlarmIn;						// Alarm input parameters, see CFG_ALARMIN_INFO
	
}CFG_EXALARMINPUT_INFO;

// Extension module alarm output configuration 
typedef struct tagCFG_EXALARMOUTPUT_INFO
{
	char		szChnName[MAX_CHANNELNAME_LEN];				// Alarm channel name
	int			nOutputMode;								// Output mode, 0 - automatic alarm 1 - Forced Alarm 2 - Turn off the alarm
}CFG_EXALARMOUTPUT_INFO;

// Extension module alarm box configured 
typedef struct tagCFG_EXALARMBOX_INFO
{
	BOOL			bEnable;								// Enable switch
	char			szProtocolName[MAX_PROTOCOL_NAME_LEN];	// Name of Agreement
	int				nPort;									// Use the serial port number
	int				nAddress;								// Device address 
	CFG_COMM_PROP	stuCommAttr;							// Serial Property
}CFG_EXALARMBOX_INFO;

// Extended alarm boxes protocol type
enum CFG_EM_EXALARM_PROTOCOL_TYPE
{
	CFG_EM_EXALARM_PROTOCOL_ERROR,								// Unknown Type
	CFG_EM_EXALARM_PROTOCOL_DH_ALARMBOX,						// DH_AlarmBox Dahua Alarm Boxes agreement
};


// Extension module alarm capability sets 
typedef struct tagCFG_CAP_EXALARM_INFO
{	
	int					 nAlarmInCount;											// The number of input extension alarm module 
	int					 nAlarmOutCount;										// Output the number of extension alarm module 
	int				 	 nMaxDelay;												// The maximum delay of time delay protection zones, the unit is in seconds, only support delay to play the field. 
	int					 nDefenceAreaTypeNum;									// Zone type species number, 0 indicates no such field not as a zone alarm input use.
	EM_CFG_DEFENCEAREATYPE	emDefenceAreaType[MAX_ALARM_DEFENCE_TYPE_NUM];		// Support Zone Type 
	int					 nExAlarmChannelNum;									// Expansion Module alarm channel number, in order to maintain compatibility, 0 means that each channel supports all types of sensors
	CFG_EXALARM_SENSE_METHOD stuExAlarmChannel[MAX_EXALARM_CHANNEL_NUM];		// Alarm Channel Collection
	int					 nProtocolNum;											// Kind of protocol support
	CFG_EM_EXALARM_PROTOCOL_TYPE emProtocolType[MAX_EXALARMBOX_PROTOCOL_NUM];	// Extension alarm module alarm box support protocol type 	
}CAP_EXALARM_INFO;

// Extension module alarm box capability sets
typedef struct tagCFG_CAP_EXALARMBOX_INFO 
{
	int nAlarmInCount; // Input the number of extension alarm module 
	int nAlarmOutCount; // Output the number of extension alarm module  
}CFG_CAP_EXALARMBOX_INFO; 

// Query record capability sets 
typedef struct tagCFG_CAP_RECORDFINDER_INFO 
{
	int nMaxPageSize; // The biggest article page number 
}CFG_CAP_RECORDFINDER_INFO;


// Sensor sampling ==>CFG_CMD_SENSORSAMPLING
typedef struct  tagCFG_SENSORSAMPLING_INFO 
{
	int			nDetectionPeriod;			// Check Cycle, Unit: second, according to the test cycle upload real-time temperature condition 
	int			nStorageItem;				// Storage information, unit: article number, local to write the file, can export (0 ~ 5000) 
}CFG_SENSORSAMPLING_INFO;

// Loop net ==>CFG_CMD_STP
typedef struct tagCFG_STP_INFO 
{
	BOOL			bEnable;                // Enable
}CFG_STP_INFO;

#define DH_MAX_ZONE_NUM					(256)	// Max zone quantity
#define DH_MAX_PUBLIC_SUBSYSTEM_NUM		(8)		// Max public sub system quantity

// Alarm sub system config ==>CFG_CMD_ALARM_SUBSYSTEM
typedef struct tagCFG_ALARM_SUBSYSTEM_INFO 
{
	char		szName[CFG_COMMON_STRING_128];	// name
	int			nZoneNum;						// Local zone quantity
	int			anZone[DH_MAX_ZONE_NUM];		// Local zone no.
	int			nExZoneNum;						// Extention zone quantity
	int			anExZone[DH_MAX_ZONE_NUM];		// Extention zone no.
	int			nDisableDelay;					// Delay disarm time?ê?§entry time?ê?,unit is s
	int			nEnableDelay;					// Delay arm time?ê?§exit delay?ê?, unit is s
	BOOL		bIsPublic;						// Public sub system
	int			nPublicSubSystem;				// Public sub system quantity
	int			anPublicSubSystem[DH_MAX_PUBLIC_SUBSYSTEM_NUM];// Public link sub system
}CFG_ALARM_SUBSYSTEM_INFO;

// Battery voltage low config ==>CFG_CMD_BATTERY_LOW_POWER
typedef struct tagCFG_BATTERY_LOW_POWER_INFO 
{
	BOOL		bEnable;						// Enable
	CFG_ALARM_MSG_HANDLE stuEventHandler;		// Alarm activation
}CFG_BATTERY_LOW_POWER_INFO;


// Snapshot channel link external config ==>CFG_CMD_SNAPLINKAGE
typedef struct tagCFG_SNAPLINKAGE_INFO 
{
    int         nChannelNum;                    // Video channel link analog channelquantity
    int         anAnalogAlarm[DH_MAX_ZONE_NUM]; // Video channel link analog channel no.
}CFG_SNAPLINKAGE_INFO;

// Video input config
typedef struct tagCFG_AUDIO_INPUT 
{
    char        szAudioSource[CFG_COMMON_STRING_256];   // Input audio source, if audio channel input is composed of multiple channels, use | to split.
                                                        // i.e.?êo"Mic|LineIn|Remote" means this audio channel is composed of Mic, LineIn and remote channel audio input.
                                                        // "Coaxial" 
                                                        // "BNC" 
                                                        // "HDCVI_BNC" remote HDCVI device audio
                                                        // "LineIn" line input
                                                        // "Mic" MIC input
                                                        // "MicOut" MIC output
                                                        // "Remote" remote channel
}CFG_AUDIO_INPUT;

// Mail Report Device Status
typedef struct tagCFG_HEALTHREPORT_INFO 
{
    BOOL			bEnable;				// Enable
    int             nInterval;              // Mail sending interval, unit is s, range?êo0~3600
}CFG_HEALTHREPORT_INFO;

// Mail sending config ==>CFG_CMD_EMAIL
typedef struct tagCFG_EMAIL_INFO 
{
    BOOL			bEnable;				                            // Enable
    BOOL            bSslEnable;                                         // If SSL encrypt 
    BOOL            bTlsEnable;                                         // If TLS encrypt
    char            szAddress[MAX_ADDRESS_LEN];                         // SMTP Server IP address or network name
    int             nPort;                                              // Port no.
    char            szUserName[MAX_USERNAME_LEN];                       // Account
    char            szPassword[MAX_PASSWORD_LEN];                       // Password
    BOOL            bAnonymous;                                         // Anonymous mail?ê?true is anonymous?ê?false is non-anonymous
    char            szSendAddress[MAX_ADDRESS_LEN];                     // Sender address
    int             nRetReciversNum;                                    // Valid receiver quantity
    char            szReceivers[MAX_RECEIVER_NUM][MAX_ADDRESS_LEN];     // Receiver list
    char            szTitle[MAX_MAILTITLE_LEN];                         // Mail title keywork
    BOOL            bOnlyAttachment;                                    // Event link mail, only send mail with attachment
    BOOL            bAttachEnable;                                      // Enable attachment
    int             nSendInterv;                                        // Same event min main sending interval, unit is s
    
    bool            abHealthReport;                                     // Capacity,is true ,stuHealthReport is valiud
    BYTE            byReserved[3];
    CFG_HEALTHREPORT_INFO   stuHealthReport;                            // Mail report device status
}CFG_EMAIL_INFO;

#define MAX_TRANSFER_SERVER_NUM          10                             // Maxsending server quantity
// Send oddline file config
typedef struct tagTRAFFIC_TRANSFER_OFFLINE_INFO
{
    BOOL            bEnable;                                                // Enable
    int             nType;                                                  // 0: use IP address; 1: use MAC address
    int             nIpAddrNum;                                             // Return IP address quantity
    char            szIpAddr[MAX_TRANSFER_SERVER_NUM][MAX_ADDRESS_LEN];     // IP address or network name
    int             nMacAddrNum;                                            // Return mac address quantity
    char            szClientID[MAX_TRANSFER_SERVER_NUM][MAX_ADDRESS_LEN];   // mac address

}TRAFFIC_TRANSFER_OFFLINE_INFO;

#define MAX_DEVCOMM_NUM          16                                     // Max serial number
// Order serial data config-single serial config
typedef struct tagCFG_DEVCOMM_SUBSCRIBE_INFO
{
    int             nReadCycle;                                         // Serial read interval,unit: s    
}CFG_DEVCOMM_SUBSCRIBE_INFO;

// Order serial data config
typedef struct tagCFG_DEVCOMM_SUBSCRIBE
{
    int                             nSubscribeInfoNum;                  // Serial data config number
    CFG_DEVCOMM_SUBSCRIBE_INFO      stuSubscribeInfo[MAX_DEVCOMM_NUM];  // Order serial data config?ê?is a group?ê?each element represents a serial    
}CFG_DEVCOMM_SUBSCRIBE;

// Parking status indicator
typedef enum tagEM_CFG_PARKINGSPACE_LIGHT_COLOR
{
    EM_CFG_PARKINGSPACE_LIGHT_RED,                                      // red
    EM_CFG_PARKINGSPACE_LIGHT_YELLOW,                                   // yellow
    EM_CFG_PARKINGSPACE_LIGHT_BLUE,                                     // blue 
    EM_CFG_PARKINGSPACE_LIGHT_GREEN,                                    // green
    EM_CFG_PARKINGSPACE_LIGHT_PURPLE,                                   // purple
    EM_CFG_PARKINGSPACE_LIGHT_WHITE,                                    // white
    EM_CFG_PARKINGSPACE_LIGHT_PINK,                                     // pink
}EM_CFG_PARKINGSPACE_LIGHT_COLOR;

// indicator status
typedef enum tagEM_CFG_PARKINGSPACE_LIGHT_STATE
{
    EM_CFG_PARKINGSPACE_LIGHT_OFF,                                      // off
    EM_CFG_PARKINGSPACE_LIGHT_ON,                                       // on
    EM_CFG_PARKINGSPACE_LIGHT_GLINT,                                    // flash
}EM_CFG_PARKINGSPACE_LIGHT_STATE;

#define CFG_MAX_PARKINGSPACE_LIGHT_NUM       8
#define CFG_MAX_NET_PORT_NUM                4 
typedef struct tagCFG_PARKINGSPACE_LIGHT_STATE
{
    BYTE                            bySpaceFreeLinght[CFG_MAX_PARKINGSPACE_LIGHT_NUM]; // parking idle indicator, color enumeration as group mark?ê?group element value means indicator status?ê?as bySpaceFreeLinght[0]=1, means red indicator on
    BYTE                            bySpaceFullLinght[CFG_MAX_PARKINGSPACE_LIGHT_NUM]; // parking full status indicator?ê?color enumeration value as group mark?ê?group element means indicator status?ê?as bySpaceFullLinght[1]=1, means yellow indicator on
    BYTE                            bySpaceOverLineLight[CFG_MAX_PARKINGSPACE_LIGHT_NUM];   // 车位压线状态灯色,颜色枚举值作为数组下标，数组元素值表示指示灯状态
    BYTE                            bySpaceOrderLight[CFG_MAX_PARKINGSPACE_LIGHT_NUM];      // 车位预定状态灯色,颜色枚举值作为数组下标，数组元素值表示指示灯状态
    int                             nNetPortNum;                                            // 网口数
    BYTE                            byNetPortAbortLight[CFG_MAX_NET_PORT_NUM][CFG_MAX_PARKINGSPACE_LIGHT_NUM];    // 网口断开状态灯色
}CFG_PARKINGSPACE_LIGHT_STATE;

// Air working mode
typedef enum tagEM_CFG_AIRCONDITION_MODE
{
    EM_CFG_AIRCONDITION_MODE_UNKNOWN = 0,
    EM_CFG_AIRCONDITION_MODE_AUTO,             // auto
    EM_CFG_AIRCONDITION_MODE_HOT,              // cool
    EM_CFG_AIRCONDITION_MODE_COLD,             // cool
    EM_CFG_AIRCONDITION_MODE_WET,              // dehumidification
    EM_CFG_AIRCONDITION_MODE_WIND,             // ventilation
} EM_CFG_AIRCONDITION_MODE;

// Air fan mode
typedef enum tagEM_CFG_AIRCONDITION_WINDMODE
{
    EM_CFG_AIRCONDITION_WINDMODE_UNKNOWN = 0,
    EM_CFG_AIRCONDITION_WINDMODE_STOP,            // stop
    EM_CFG_AIRCONDITION_WINDMODE_AUTO,            // auto
    EM_CFG_AIRCONDITION_WINDMODE_HIGH,            // high speed
    EM_CFG_AIRCONDITION_WINDMODE_MIDDLE,          // mid speed
    EM_CFG_AIRCONDITION_WINDMODE_LOW,             // low speed
} EM_CFG_AIRCONDITION_WINDMODE;

// Serial address
typedef struct tagCFG_COMMADDR_INFO
{
    int                 nAddressNum;                            // serial address number
    int 				nAddress[MAX_ADDRESS_NUM];			// address description, different manufacturer has different addresses, in group
}CFG_COMMADDR_INFO;

// Air device config detail
typedef struct tagCFG_AIRCONDITION_DETAIL
{
    char				szDeviceID[MAX_DEVICE_ID_LEN];			// Device config, SN
    char                szName[MAX_DEVICE_MARK_LEN];            // Device description
    char                szBrand[MAX_BRAND_NAME_LEN];            // Device brand
    CFG_COMMADDR_INFO   stuCommAddr;                            // Serial address
    int                 nState;                                 // Device status: 1-on,0-1?off
    int                 nRange;                                 // Range value(temperature)unit?êoCelsius
    EM_CFG_AIRCONDITION_MODE        emAirconditionMode;         // Air work mode
    EM_CFG_AIRCONDITION_WINDMODE    emAirconditionWindMode;     // Air fan mode
}CFG_AIRCONDITION_DETAIL;

// Fan device config(corresponding CFG_CMD_AIRCONDITION command)
typedef struct tagCFG_AIRCONDITION_INFO
{
    int                         nAirConditionNum;                        // Air device number
    CFG_AIRCONDITION_DETAIL 	stuAirConditions[MAX_AIRCONDITION_NUM];	 // Air deviceconfig detail, gourp as
}CFG_AIRCONDITION_INFO;

//Compression playback config info
typedef struct tagCFG_COMPRESS_PLAY_INFO
{
    BOOL                bEnable;                // Enable
	CFG_CAPTURE_SIZE    emResolution;           // Video resolution
	unsigned int        nBitRate;               // Video fixed stream value(kbps), range?êo192~1024
}CFG_COMPRESS_PLAY_INFO;

// System type 
typedef enum tagEM_CFG_BUILDING_SYSTEM_TYPE
{
    EM_CFG_BUILDING_SYSTEM_TYPE_UNKNOWN = 0,        // Unknown
    EM_CFG_BUILDING_SYSTEM_TYPE_DIGITAL,            // Digital system
    EM_CFG_BUILDING_SYSTEM_TYPE_ANALOG,             // Analog system
}EM_CFG_BUILDING_SYSTEM_TYPE;

// VTO floor config(corresponding to  CFG_CMD_BUILDING command)
typedef struct tagCFG_BUILDING_INFO
{
    char                            szIssueNumber[CFG_COMMON_STRING_16];                // Issue no.?ê?range: 0 ~ 99
    char                            szSectionNumber[CFG_COMMON_STRING_16];              // Section no.?ê?range: 0 ~ 99
    char                            szBuildingNumber[CFG_COMMON_STRING_16];             // Building no.?ê?range: 0 ~ 999
    char                            szBuildingUnitNumber[CFG_COMMON_STRING_16];         // Building unit no.?ê?range: 0 ~ 9
    char                            szSectionUnitNumber[CFG_COMMON_STRING_16];          // Residence unit no.?ê?range: 0 ~ 999
    int                             nUnitFloorNumber;                                   // Unit floor no.?ê?range: 0 ~ 99
    int                             nFloorPerRoomNumber;                                // Room on one floor?ê?range: 0 ~ 99
    BOOL                            bCreateRoomEnable;                                  // Create room no. enable
    EM_CFG_BUILDING_SYSTEM_TYPE     emSystemType;                                       // System type 
}CFG_BUILDING_INFO;

//VTO floor expansion config(corresponding to  CFG_CMD_BUILDING_EXTERNAL  command)
typedef struct tagCFG_BUILDING_EXTERNAL_INFO
{
    int                                     nFloorCount;                                            // Unit total floor
    int                                     nRoomCount;                                             // Room on one floor
    int                                     nBeginNumberCount;                                      // Get/setup?ê?corresponding room no. valid number
    // When get, gotten start room no. exceeds MAX_FLOOR_NUM?ê?first MAX_FLOOR_NUM is valid
    // When set, set start room no. exceeds MAX_FLOOR_NUM?ê?first MAX_FLOOR_NUM is valid
    char                                    szBeginNumber[MAX_FLOOR_NUM][CFG_COMMON_STRING_16];     // Start room no.?ê?nBeginNumber[0] as first floor start room no.?ê?nBeginNumber[1] as second start room no.?ê?
    int                                     nTotalBuildingNumber;                                   // Residence total building no.?ê?range: 0 ~ 99
    int                                     nBuildingPerUintNumber;                                 // Unit in each building?ê?range: 0 ~ 9
}CFG_BUILDING_EXTERNAL_INFO;

//Dial rule(corresponding to  CFG_CMD_DIALRULE  command)
typedef struct tagCFG_DIALRULE_INFO
{
    BOOL                            bBuildingModeEnable;            //Building mode enable
    BOOL                            bUnitModeEnable;                //Unit modeenable
    BOOL                            bExtentionModeEnable;           //Extension mode enable
    char                            cSeperator;                     //Dial saparator, as "#", "-"
    BYTE				            byReserved[3];				    //Field alignment 
}CFG_DIALRULE_INFO;

// vehicle tank config
typedef struct tagCFG_OIL_MASS_INFO
{
    int                 nTankVolume;            // ank capacity?ê?unit?êoL
    int                 nNotifyIntervalTime;    // report tank info interval, unit ?êos
    int                 nLowOil;                // tank oil level low alarm percentage(i.e.?êobelow 20% to alarm), unit?êopercentage?ê?0?ê-100
    int                 nAlarmIntervalTime;     // report oil level low alarm time interval(as after alarms, alarm is reapeat periodically), unit?êos
}CFG_OIL_MASS_INFO; 

// MAC conflict event alarm config
typedef struct tagCFG_MACCONFLICT_INFO 
{
    BOOL                bEnable;                // enable siwtch
    CFG_ALARM_MSG_HANDLE stuEventHandler;       // alarm link
}CFG_MACCONFLICT_INFO;

// idle action function enumeration
typedef enum tagEM_CFG_IDLEMOTION_FUNCTION
{
    EM_CFG_IDLEMOTION_FUNCTION_NONE = 0,         // none
    EM_CFG_IDLEMOTION_FUNCTION_PRESET,           // preset
    EM_CFG_IDLEMOTION_FUNCTION_SCAN,             // auto scan
    EM_CFG_IDLEMOTION_FUNCTION_TOUR,             // tour
    EM_CFG_IDLEMOTION_FUNCTION_PATTERN,          // auto pattern
} EM_CFG_IDLEMOTION_FUNCTION;

// idle action config info
typedef struct tagCFG_IDLE_MOTION_INFO
{
    BOOL                        bEnable;         // enable
    int                         nTime;           // enable idle action time 1~60 minute
    EM_CFG_IDLEMOTION_FUNCTION  emFunction;      // idle action function, see enumeration EM_CFG_IDLEMOTION_FUNCTION
    int                         nPresetId;       // preset no.,   rage refer to CFG_PTZ_PROTOCOL_CAPS_INFO wPresetMin and wPresetMax
    int                         nScanId;         // auto scan no.o?, range refer to CFG_PTZ_PROTOCOL_CAPS_INFO wAutoScanMin and wAutoScanMax
    int                         nTourId;         // tour no.,     range refer to CFG_PTZ_PROTOCOL_CAPS_INFO wTourMin and wTourMax
    int                         nPatternId;      // auto tour no., range refer to CFG_PTZ_PROTOCOL_CAPS_INFO wPatternMin and wPatternMax
}CFG_IDLE_MOTION_INFO;

// TV wall scheme tour config
typedef struct tagCFG_MONITORWALL_COLLECTION_TOUR_INFO
{
    int                 nInterval;               // tour interval, unit is s
    int                 nCollectionNum;          // scheme toup includes scehem quantity
    char                szCollectionGroup[CFG_MAX_COLLECTION_NUM][CFG_COMMON_STRING_128]; // scheme tour content, each item is scheme name
}CFG_MONITORWALL_COLLECTION_TOUR_INFO;

// PSTN offline event config
typedef struct tagCFG_PSTN_BREAK_LINE_INFO
{
    BOOL                bEnable;                // enable siwtch
    CFG_ALARM_MSG_HANDLE stuEventHandler;       // alarm link
}CFG_PSTN_BREAK_LINE_INFO;

// network captue device config, correspoinding CFG_CMD_NET_COLLECTION command
typedef struct tagCFG_NET_COLLECTION_INFO
{
    char                szIp[MAX_ADDRESS_LEN];  // IP
	int                 nPort;                  // port
}CFG_NET_COLLECTION_INFO;

// physical port type
typedef enum tagEM_CFG_INTERFACE_TYPE
{
    EM_CFG_INTERFACE_TYPE_UNKNOWN = 0,
	EM_CFG_INTERFACE_TYPE_COMM,                 // Comm type, as serial, corresponding to CFG_COMMGROUP_INFO config 
	EM_CFG_INTERFACE_TYPE_NETCOLLECTION,        // NetCollection type, as network capture, corresponding CFG_NET_COLLECTION_INFO config
}EM_CFG_INTERFACE_TYPE;

// virtual Slot node and detailed physical corresponding relation, corresponding CFG_CMD_ALARM_SLOT_BOND command
// first channel(as channel 0)is bound to local channel?ê?so cannot set;
// other channel corresponding Slot node no., element content is corresponding physical port
typedef struct tagCFG_ALARM_SLOT_BOND_INFO
{
    EM_CFG_INTERFACE_TYPE   emType;             // physical port type
	int                     nIndex;	            // channel no., from 0
	                                            // type as EM_CFG_INTERFACE_TYPE_COMM , means CFG_COMMGROUP_INFO config group subscript;
	                                            // type as EM_CFG_INTERFACE_TYPE_NETCOLLECTION, means CFG_NET_COLLECTION_INFO configured group limit;
}CFG_ALARM_SLOT_BOND_INFO;

#define CFG_MAX_CTRLTYPE_NUM       16            // max gateway control method
// gateway control method enumeration
typedef enum tagEM_CFG_TRAFFICSTROBE_CTRTYPE
{
    EM_CFG_CTRTYPE_UNKNOWN = 0,                 // undefined
    EM_CFG_CTRTYPE_TRAFFICTRUSTLIST,            // via white list control gateway?ê?only white list vehicle open gateway
    EM_CFG_CTRTYPE_ALLSNAPCAR,                  // vehicle open gateway for all snapshots
    EM_CFG_CTRTYPE_ORDER,                       // open gateway commend sent from upper level
} EM_CFG_TRAFFICSTROBE_CTRTYPE;

// Gateway config info(corresponding CFG_CMD_TRAFFICSTROBE command)
typedef struct tagCFG_TRAFFICSTROBE_INFO
{
    BOOL                            bEnable;                            // enable
    int                             nCtrlTypeCount;                     // gateway control method number
    EM_CFG_TRAFFICSTROBE_CTRTYPE    emCtrType[CFG_MAX_CTRLTYPE_NUM];    // gateway control method, see enumeration EM_CFG_TRAFFICSTROBE_CTRTYPE
    CFG_ALARM_MSG_HANDLE            stuEventHandler;					// enable gateway link parameter
    CFG_ALARM_MSG_HANDLE            stuEventHandlerClose;               // disable gateway link parameter
}CFG_TRAFFICSTROBE_INFO;

#define CFG_MAX_PLATEENABLE_NUM       16        //max enable pass vehicle plate report number
#define CFG_MAX_TRAFFICVOICE_NUM      8         // max audio report config number
// enable pass vehile plate report function enumeration
typedef enum tagEM_CFG_PLATEENABLE_TYPE
{
    EM_CFG_PLATEENABLE_UNKNOWN = 0,             // undefined
    EM_CFG_PLATEENABLE_TIPS,                    // welcome word
    EM_CFG_PLATEENABLE_PLATE,                   // play plaet
} EM_CFG_PLATEENABLE_TYPE;

// intelligent traffic audio report info
typedef struct tagCFG_TRAFFICVOICE_BROADCAST_INFO
{
    int                             nEnableCount;                       // enable report number
    EM_CFG_PLATEENABLE_TYPE         emEnable[CFG_MAX_PLATEENABLE_NUM];  // enable pass vehicle plate, see enumeration EM_CFG_PLATEENABLE_TYPE
    char                            szNormalCar[MAX_PATH];              // normal vehicle report content, such as : play audio file"welcome.wav"
    char                            szTrustCar[MAX_PATH];               // trusted vehicle pass report content, such as: play audio file"welcome.wav"
    char                            szSuspiciousCar[MAX_PATH];          // suspected vehicle pass report content, such as: play audio file"non-resigtered vehicle.wav"
}CFG_TRAFFICVOICE_BROADCAST_INFO;

// intelligent traffic audio play config(corresponding CFG_CMD_TRAFFICVOICE command)
typedef struct tagCFG_TRAFFICVOICE_BROADCAST
{
    int                             nTrafficVoiceNum;                           // audio play config number
    CFG_TRAFFICVOICE_BROADCAST_INFO stuTrafficVoices[CFG_MAX_TRAFFICVOICE_NUM];	// audio play config detail, group means
}CFG_TRAFFICVOICE_BROADCAST;

// parking time config
typedef struct tagCFG_STANDING_TIME_INFO
{
    BOOL                        bEnable;         // enable parking overtime alarm function
    int                         nUpperlimit;     // duration limit, unit?êomin
    int                         nInterval;       // DH_ALARM_VEHICLE_STANDING_OVER_TIME event report interval, unit?êos, -1 means report only one time
} CFG_STANDING_TIME_INFO;

// e-fence alarm period info
typedef struct tagENCLOSURE_TIME_SCHEDULE_INFO
{
    int                         nEnclosureID;                                          // fence ID
    CFG_TIME_SECTION            stuTimeSection[MAX_TIME_SCHEDULE_NUM][MAX_REC_TSECT];  // event response period
} ENCLOSURE_TIME_SCHEDULE_INFO;

// e-fence max quantity
#define MAX_ENCLOSURE_NUM 128

// e-fence alarm period config
typedef struct tagCFG_ENCLOSURE_TIME_SCHEDULE_INFO
{
    int                                nEnclosureInfoCount;                     // fence quantity
    ENCLOSURE_TIME_SCHEDULE_INFO       stuEnclosureInfo[MAX_ENCLOSURE_NUM];     // fence info
    char                               szVersion[CFG_COMMON_STRING_64];         // fence period config version no.
} CFG_ENCLOSURE_TIME_SCHEDULE_INFO;

// Parking lot entrance/exit controller working mode
typedef enum tagEM_ECK_WORK_MODE_TYPE
{
    EM_ECK_WORK_MODE_UNKNOWN = 0,
    EM_ECK_WORK_MODE_IMPORT,                                    // Entrance controller
    EM_ECK_WORK_MODE_EXPORT,                                    // Exit controller
}EM_ECK_WORK_MODE_TYPE;

// Parking extrance/exit controller open mode
typedef enum tagEM_ECK_STROBE_MODE_TYPE
{
    EM_ECK_STROBE_MODE_UNKNOWN = 0,
    EM_ECK_STROBE_MODE_ON,                                      // Always open
    EM_ECK_STROBE_MODE_OFF,                                     // Always close
    EM_ECK_STROBE_MODE_AUTO,                                    // Auto open
}EM_ECK_STROBE_MODE_TYPE;

// Parking entrance/exit controller roll screen initial rolling speed
typedef enum tagEM_ECK_LED_SPEED_TYPE
{
    EM_ECK_LED_SPEED_UNKNOWN = 0,
    EM_ECK_LED_SPEED_LOW,                                       // Slow
    EM_ECK_LED_SPEED_NORMAL,                                    // Normal
    EM_ECK_LED_SPEED_HIGH,                                      // Fadt
}EM_ECK_LED_SPEED_TYPE;

// Parking entrance/exit controller LED roll screen config
typedef struct tagCFG_ECK_LED_INFO 
{
    EM_ECK_LED_SPEED_TYPE   emLEDSpeed;                         // LED roll screen initial rolling speed
    char                    szCustomData[CFG_COMMON_STRING_512];// LED roll screen initial custom character, valid length 0-256 bytes
}CFG_ECK_LED_INFO;

// Parking entrance/exit controller config 
typedef struct tagCFG_ECKCONFIG_INFO 
{
    EM_ECK_WORK_MODE_TYPE   emWorkMode;                         // Working mode
    EM_ECK_STROBE_MODE_TYPE emStrobeMode;                       // Open mode
    BOOL                    bForceOffline;                      // Forced offline button, TRUE: forced offline work,  FALSE: accept platform control work
    BOOL                    bLoopSence;                         // Sensor function switch, TRUE: enable senser function, FALSE: disable sensor function
    CFG_ECK_LED_INFO        stuLED;                             // Roll screen config
}CFG_ECKCONFIG_INFO;

// Direction
typedef enum tagEM_DIRECTION
{
    EM_DIRECTION_UNKNOWN,
    EM_DIRECTION_LEFT,                                          // Left
    EM_DIRECTION_UPLEFT,                                        // Upleft
    EM_DIRECTION_UP,                                            // Up
    EM_DIRECTION_UPRIGHT,                                       // Upright
    EM_DIRECTION_RIGHT,                                         // Right
    EM_DIRECTION_DOWNRIGHT,                                     // Downright
    EM_DIRECTION_DOWN,                                          // Down
    EM_DIRECTION_DOWNLEFT,                                      // Downleft
}EM_DIRECTION;

// The position of guide screen
typedef enum tagEM_GUIDESCREEN_POS
{
    EM_GUIDESCREEN_POS_UNKNOWN,
    EM_GUIDESCREEN_POS_LEFT,                                    // Left
    EM_GUIDESCREEN_POS_RIGHT,                                   // Right
}EM_GUIDESCREEN_POS;

// The roll state of guid screen
typedef enum tagEM_GUIDESCREEN_ROLL
{
    EM_GUIDESCREEN_ROLL_UNKNOWN,
    EM_GUIDESCREEN_ROLL_DISABLE,                                // Disable
    EM_GUIDESCREEN_ROLL_ENABLE,                                 // Enable
}EM_GUIDESCREEN_ROLL;

// The arrow state of guid screen
typedef struct tagCFG_GUISCREEN_ARROW
{
    EM_DIRECTION            emDirect;                           // Direction
    EM_GUIDESCREEN_POS      emPos;                              // Position of guide screen
    EM_GUIDESCREEN_ROLL     emRoll;                             // Roll state
}CFG_GUISCREEN_ARROW;

#define CFG_GUIDE_SCREEN_NUM_MAX (8)                            // Max number of guide screen

// Config of guid screen(CFG_CMD_GUIDESCREEN)
typedef struct tagCFG_GUIDESCREEN_INFO
{
    char                    szText[CFG_COMMON_STRING_128];      // Context of screen
    int                     nArrowNum;                          // The number of arrow
    CFG_GUISCREEN_ARROW     stuArrow[CFG_GUIDE_SCREEN_NUM_MAX]; // The config of arrow
}CFG_GUIDESCREEN_INFO;



//  Parking entrance/exit swiping card alarm event config(correspoinding CFG_CMD_PARKING_CARD command)
typedef struct tagCFG_PARKING_CARD_INFO
{
    BOOL                            bEnable;                // Enable or not
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // Alarm link
} CFG_PARKING_CARD_INFO;

// Alarm method, as alarm sent out via which method
typedef enum tagEM_CFG_RCEMERGENCY_MODE_TYPE
{
    EM_CFG_RCEMERGENCY_MODE_UNKNOWN = 0,
    EM_CFG_RCEMERGENCY_MODE_KEYBOARD,                       // Keyboard
    EM_CFG_RCEMERGENCY_MODE_WIRELESS_CONTROL,               // Remote control
}EM_CFG_RCEMERGENCY_MODE_TYPE;

// Emergency alarm type 
typedef enum tagEM_CFG_RCEMERGENCY_CALL_TYPE
{
    EM_CFG_RCEMERGENCY_CALL_UNKNOWN = 0,
    EM_CFG_RCEMERGENCY_CALL_FIRE,                           // Fire
    EM_CFG_RCEMERGENCY_CALL_DURESS,                         // Forced
    EM_CFG_RCEMERGENCY_CALL_ROBBER,                         // Police
    EM_CFG_RCEMERGENCY_CALL_MEDICAL,                        // Medical
}EM_CFG_RCEMERGENCY_CALL_TYPE;

// Emergence call alarm event config(corresponding to  CFG_CMD_RCEMERGENCYCALL  command)
typedef struct tagCFG_RCEMERGENCY_CALL_INFO 
{
    BOOL                            bEnable;                // Enable or not
    EM_CFG_RCEMERGENCY_MODE_TYPE    emMode;                 // Alarm method
    EM_CFG_RCEMERGENCY_CALL_TYPE    emAlarmType;            // Alarm type 
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // Alarm link
}CFG_RCEMERGENCY_CALL_INFO;

// Lane info report config(corresponding to  CFG_CMD_LANES_STATE_REPORT  command)
typedef struct tagCFG_LANES_STATE_REPORT
{
    BOOL                bEnable;        //Report eanble	true: report enable ,false: report disable
    int                 nPeriod;        //Report period	unit?êos
}CFG_LANES_STATE_REPORT;

#define CFG_MAX_USER_ID_LEN                     32              // Access controlcard user ID max length

// Multi-people group unlock method
typedef enum tagEM_CFG_OPEN_DOOR_GROUP_METHOD
{
    EM_CFG_OPEN_DOOR_GROUP_METHOD_UNKNOWN = 0,
    EM_CFG_OPEN_DOOR_GROUP_METHOD_CARD,                         // Swipe card
    EM_CFG_OPEN_DOOR_GROUP_METHOD_PWD,                          // Password
    EM_CFG_OPEN_DOOR_GROUP_METHOD_FINGERPRINT,                  // Fingerprint
}EM_CFG_OPEN_DOOR_GROUP_METHOD;

// Multi-group unlock detail info 
typedef struct tagCFG_OPEN_DOOR_GROUP_DETAIL 
{
    char                            szUserID[CFG_MAX_USER_ID_LEN];  // UserID
    EM_CFG_OPEN_DOOR_GROUP_METHOD   emMethod;                       // Unlock method
}CFG_OPEN_DOOR_GROUP_DETAIL;

#define CFG_MAX_OPEN_DOOR_GROUP_DETAIL_NUM      64               // Each group multi-people unlock group max number

// Multi-people group unlock group info 
typedef struct tagCFG_OPEN_DOOR_GROUP 
{
    int                         nUserCount;                     // User quantity?ê?means people needed to unlock
    int                         nGroupNum;                      // Valid group number
    CFG_OPEN_DOOR_GROUP_DETAIL  stuGroupDetail[CFG_MAX_OPEN_DOOR_GROUP_DETAIL_NUM];// Multi-people group unlock group detail info 
}CFG_OPEN_DOOR_GROUP;

#define CFG_MAX_OPEN_DOOR_GROUP_NUM             4               // Multi-people unlock group max group number

// Multi-people unlock method group(corresponding to  CFG_CMD_OPEN_DOOR_GROUP  command), means each channel group info ?ê?
// Each channel group unlock priority is the highest, decending one by one
typedef struct tagCFG_OPEN_DOOR_GROUP_INFO 
{
    int                         nGroup;                         // Valid group number
    CFG_OPEN_DOOR_GROUP         stuGroupInfo[CFG_MAX_OPEN_DOOR_GROUP_NUM];// Multi-people unlock group info 
}CFG_OPEN_DOOR_GROUP_INFO;

#define MAX_READER_ID_LEN                       32              // Card reader ID max length

// Unlock path each node info 
typedef struct tagCFG_DOOR_ROUTE_NODE_INFO
{
    char                        szReaderID[MAX_READER_ID_LEN];  // card reader ID?ê? as access control connected card reader ID
}CFG_DOOR_ROUTE_NODE_INFO;

// Each unlock path max node(card reader quantity)
#define MAX_DOOR_ROUTE_NODE_NUM     4

// Foor group set info ?ê?by group subscript ascending, means unlock path
typedef struct tagCFG_DOOR_ROUTE_INFO
{
    int                         nDoors;                             // Unlock pathvalid node number
    CFG_DOOR_ROUTE_NODE_INFO    stuDoors[MAX_DOOR_ROUTE_NODE_NUM];  // Unlock path node info 
}CFG_DOOR_ROUTE_INFO;

#define MAX_OPEN_DOOR_ROUTE_NUM                 16                  // Max unlock path quantity

// Unlock path set?ê?or anti-passby path config(corresponding to  CFG_CMD_OPEN_DOOR_ROUTE  command)
typedef struct tagCFG_OPEN_DOOR_ROUTE_INFO
{
    int                         nDoorList;
    CFG_DOOR_ROUTE_INFO         stuDoorList[MAX_OPEN_DOOR_ROUTE_NUM];
}CFG_OPEN_DOOR_ROUTE_INFO;

#define MAX_BURNPLAN_DEVICES_NUM                     32
#define MAX_BURNPLAN_CHANNELS_NUM                     32

// Burning stream format
typedef enum tagEM_CFG_BURNPLAN_RECORDPACK_TYPE
{
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_UNKNOWN,        // Unknown
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_DHAV,           // "DHAV"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_PS,             // "PS"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_ASF,            // "ASF"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_MP4,            // "MP4"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_TS,             // "TS"
}EM_CFG_BURNPLAN_RECORDPACK_TYPE;

// Burning mode
typedef enum tagEM_CFG_BURNPLAN_MODE
{
    EM_CFG_BURNPLAN_MODE_UNKNOWN,           // Unknown
    EM_CFG_BURNPLAN_MODE_SYNC,              // Sync?êo "Sync"
    EM_CFG_BURNPLAN_MODE_TURN,              // Turn:  "Turn"
    EM_CFG_BURNPLAN_MODE_CYCLE,             // cycle:  "Cycle"
}EM_CFG_BURNPLAN_MODE;

// Burning plan info 
typedef struct tagCFG_BURNPLAN_DETAIL
{
    int                                 nSessionId;                             // Interrogation room
    int                                 nDevicesNum;                            // Joined session device list valid number
    int                                 nDevices[MAX_BURNPLAN_DEVICES_NUM];     // Joined session device list
    int                                 nChannelsNum;                           // Burning video channel valid number
    int                                 nChannels[MAX_BURNPLAN_CHANNELS_NUM];   // Burned video channel
    EM_CFG_BURNPLAN_RECORDPACK_TYPE     emRecordpack;                           // Burning stream format
    EM_CFG_BURNPLAN_MODE                emMode;                                 // Burning mode
    CFG_NET_TIME                        stuStarttime;                           // Burning start time
}CFG_BURNPLAN_DETAIL;

#define MAX_BURNPLAN_DETAIL_NUM          32

// Burning plan config(corresponding to CFG_BURNPLAN_INFO)
typedef struct tagCFG_BURNPLAN_INFO
{
    int                         nBurnPlanDetailNum;                                 // Burning plan info list valid number
    CFG_BURNPLAN_DETAIL         stuBurnPlanDetail[MAX_BURNPLAN_DETAIL_NUM];         // Burning plan info list
}CFG_BURNPLAN_INFO;

typedef struct tagCFG_SCADA_DEV_INFO 
{
    BOOL                            bEnable;                // Enable or not
    char                            szDevType[CFG_COMMON_STRING_64];// Device type 
    char                            szDevName[CFG_COMMON_STRING_64];// Devicename, SN
    int                             nSlot;                  // Virtual slot no., , see AlarmSlotBond config
    int                             nLevel;                 // If Slot binding is NetCollectiontype, this field is-1
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // Alarm link
}CFG_SCADA_DEV_INFO;

// Channel related info 
typedef struct tagCFG_VSP_GAYS_CHANNEL_INFO
{
    char                            szId[CFG_COMMON_STRING_64];             // Channel no.	string?ê?§24 bit?ê?
    int                             nAlarmLevel;                            // Alarm level [1,6]	whole
}CFG_VSP_GAYS_CHANNEL_INFO;

// Alarm related info 
typedef struct tagCFG_VSP_GAYS_ALARM_INFO
{
    char                            szId[CFG_COMMON_STRING_64];             // Channel no.	string?ê?§24 bit?ê?
    int                             nAlarmLevel;                            // Alarm level[1,6]	whold
}CFG_VSP_GAYS_ALARM_INFO;

// Public security 1 platform input config(CFG_VSP_GAYS_INFO)
typedef struct tagCFG_VSP_GAYS_INFO
{
    BOOL                            bEnable;                                // Enable or not, TRUE enable?ê?FALSE disable
    char                            szSipSvrId[CFG_COMMON_STRING_64];       // SIP server no.	string?ê?§24 bits?ê?
    char                            szDomain[CFG_COMMON_STRING_256];        // SIP domain	 string?ê?§128 bits?ê?
    char                            szSipSvrIp[CFG_COMMON_STRING_32];       // SIP server IP	 string?ê?§16 bits?ê?
    char                            szDeviceId[CFG_COMMON_STRING_64];       // Device no.?ê?as registered username	 string?ê?§24 bits?ê?
    char                            szPassword[CFG_COMMON_STRING_64];       // Registration password , ciphertext string?ê?§24 bits?ê?
    unsigned short                  nLocalSipPort;                          // Local SIP server port	no symbol short whole 
    unsigned short                  nSipSvrPort;                            // SIP server port	no symbol short whole 
    int                             nSipRegExpires;                         // Registration validity	 whole 
    int                             nKeepAliveCircle;                       // Beat period	 whole 
    int                             nMaxTimeoutTimes;                       // Max beat overtime times	 whole 
    char                            szCivilCode[CFG_COMMON_STRING_64];      // District code 	 string?ê?§24 bits?ê?
    char                            szIntervideoID[CFG_COMMON_STRING_64];   // Input module recognition code 	 string?ê?§24 bits?ê?
    unsigned short                  nChannelSum;                            // Channel no.	no symbol short whole 
    unsigned short                  nAlarmInSum;                            // External alarm input number	no symbol short whole 
    CFG_VSP_GAYS_CHANNEL_INFO       stuChannelInfo[MAX_VIDEO_CHANNEL_NUM];  // Chanel related info 	group?ê?valid number same as channelSum
    CFG_VSP_GAYS_ALARM_INFO         stuAlarmInfo[MAX_ALARM_CHANNEL_NUM];    // Alarm related info 	group?ê?valid number same as alarmInSum
}CFG_VSP_GAYS_INFO;

// Audio detection alarm config(CFG_CMD_AUDIODETECT)
typedef struct tagCFG_AUDIO_DETECT_INFO
{
    BOOL                            bEnable;                                // Enable or not?ê?TRUE enable?ê?FALSE disable
    int                             nMinVolume;                             // Min Volume
    int                             nMaxVolume;                             // Max Volume
    BOOL                            bAnomalyDetect;                         // Sound abnormal detection enable
    int                             nAnomalySensitive;                      // Sound abnormal detection sensitivity value	range 1~100
    BOOL                            bMutationDetect;                        // Sound intensity detection enable
    int                             nMutationThreold;                       // Sound intensity detection threshold value	range 1~100
    CFG_ALARM_MSG_HANDLE            stuEventHandler;						// Link config
}CFG_AUDIO_DETECT_INFO;

// VTS call config(CFG_CMD_VTS_CALL_INFO)
typedef struct tagCFG_VTS_CALL_INFO 
{
    CFG_TIME_SECTION                stuCallEnableTime;                      // The time section of VTS call
}CFG_VTS_CALL_INFO;

// Each device info in device list config
typedef struct tagCFG_DEV_LIST
{
    char                            szDevType[CFG_COMMON_STRING_128];       // device type, support : "VTT", "VTS"
    char                            szDevName[CFG_COMMON_STRING_128];       // device name
    char                            szIP[MAX_ADDRESS_LEN];                  // IP address
    int                             nPort;                                  // port no.
    char                            szUser[CFG_COMMON_STRING_64];           // username
    char                            szPassword[CFG_COMMON_STRING_64];       // password
    char                            szDevID[CFG_COMMON_STRING_128];         // device ID no., must be exclusive
    char                            szParentID[CFG_COMMON_STRING_128];      // father node ID, must be exclusive
}CFG_DEV_LIST;

// device list config (correspondingcommand CFG_CMD_DEV_LIST_INFO)
typedef struct tagCFG_DEV_LIST_INFO 
{
    CFG_DEV_LIST*                   pstuDevList;                            // config info, user allocate memory
    DWORD                           dwDevListMaxCount;                      // pstuDevList allocate memory valid structure number
    DWORD                           dwDevListRetCount;                      // actual return structure number, valid when analyzing to structure
}CFG_DEV_LIST_INFO;

#define MAX_CALIBRATE_MATRIX_LEN    8										// max length of mark matrix


#define MAX_CALIBRATE_MATRIX_EX_LEN 32      // max length of mark matrix_EX
#define MAX_POINT_PAIR_LEN			10		// max length of  master-slave points
// master-slave tracking mark matrix config (corresponding to CFG_CMD_CALIBRATE_MATRIX command)
typedef struct tagCFG_CALIBRATE_MATRIX_INFO 
{
    char                szSlaveSN[CFG_COMMON_STRING_128];                   
    DWORD               dwMatrixLen;                                       
    DWORD               dwMatrix[MAX_CALIBRATE_MATRIX_LEN];                
}CFG_CALIBRATE_MATRIX_INFO;

// the points of master(8192 coordinate system)
typedef struct tagCFG_MASTER_POINT
{
	int 	nX;
	int		nY;
} CFG_MASTER_POINT;

// the points of slave
typedef struct tagCFG_SLAVE_POINT
{
	float                    fPositionX;
	float                    fPositionY;
	float                    fZoom;
} CFG_SLAVE_POINT;


// the data of master-slave points
typedef struct tagCFG_POINT_PAIR
{
    CFG_MASTER_POINT     	stuMasterPoint;           //  the points of master, 8192 coordinate system
    CFG_SLAVE_POINT			stuSlavePoint;            // the points of slave
} CFG_POINT_PAIR;


// the data of master-slave tracking mark matrix
typedef struct tagCFG_CALIBRATE_MATRIX_ELEMENT
{
	char                szMasterSN[CFG_COMMON_STRING_128];                  // the serial number of master(optional)
    char                szSlaveSN[CFG_COMMON_STRING_128];                   // the serial number of slave
    DWORD               dwMatrixLen;                                        // the counts of effective matrixs
    DWORD               dwMatrix[MAX_CALIBRATE_MATRIX_EX_LEN];				// calibrate matrix, a 128-bytes binary sequance, represented as 32 DWORDs for efficiency
    DWORD               dwPointPairNum;                                     // the count of master-slave points
    CFG_POINT_PAIR      stuPointPair[MAX_POINT_PAIR_LEN];                   // the data of master-slave points(optional), which is a arry, and it can store up to 10 datas
	BOOL				bExpectRatio;										// do or not have the config of expect ratio
	float               szExpectRatio[2];                                   // the data of expect ratio(optional), the first data is T coordinates[-1.0, 1.0], the second data is scale
} CFG_CALIBRATE_MATRIX_ELEMENT;

// master-slave tracking mark matrix config (corresponding to CFG_CMD_CALIBRATE_MATRIX command)
typedef struct tagCFG_CALIBRATE_MATRIX_EX_INFO 
{
    DWORD							 nMaxCalibElement;			// the max counts of master-slave tracking mark matrix config
	DWORD							 nRetCalibElement;			// the counts of effective master-slave tracking mark matrix config
	CFG_CALIBRATE_MATRIX_ELEMENT	*pstCaliMatrixElement;		// the data of master-slave tracking mark matrix config,and the memory malloced by user
} CFG_CALIBRATE_MATRIX_EX_INFO;


// zone delay config (corresponding to CFG_CMD_DEFENCE_AREA_DELAY command)
typedef struct tagCFG_DEFENCE_AREA_DELAY_INFO 
{
    int                 nEnterDelay1;										// enter delay zone type, except zone type EM_CFG_DefenceAreaType_Entrance2, all use this to enter delay
    int                 nEnterDelay2;										// only zone type as EM_CFG_DefenceAreaType_Entrance2, will use this to enter delay
    int                 nExitDelay;											// all exit delay zone, all use this to exit delay
}CFG_DEFENCE_AREA_DELAY_INFO;

// thermal imaging gain mode
typedef enum tagCFG_THERMO_GAIN_MODE 
{
    CFG_THERMO_GAIN_MODE_UNKNOWN,
    CFG_THERMO_GAIN_MODE_HIGHTEMP,                      // high temperature
    CFG_THERMO_GAIN_MODE_LOWTEMP,                       // low temperature
    CFG_THERMO_GAIN_MODE_AUTO,                          // auto
} CFG_THERMO_GAIN_MODE;

// thermal imaging auto gain setup
typedef struct tagCFG_THERMO_AUTO_GAIN
{
    int                         nLowToHigh;             // when temperature exceeds this set value, auto switch to high temperature mode
    int                         nLHROI;                 // ROI percentage 0~100 when switch from low to high temperature
    int                         nHighToLow;             // when temperature lower to this set value, auto switch to low temperature mode
    int                         nHLROI;             	// ROI percentage 0~100 when switch from high to low temperature
} CFG_THERMO_AUTO_GAIN;

// thermal imaging config, single mode config
typedef struct tagCFG_THERMOGRAPHY_OPTION
{
	int                         nEZoom;                 // zoom
	int                         nThermographyGamma;     // gamma value
	int                         nColorization;	        // pseudo-color, see NET_THERMO_COLORIZATION
	int                         nSmartOptimizer;        // intelligent scene optimization indicator 0~100, detailed range depending on capacity
    BOOL                        bOptimizedRegion;       // whether enable ROI, only ROI info will be included in statistics for AGC
	int                         nOptimizedROIType;      // ROI type, see NET_THERMO_ROI
	int                         nCustomRegion;          // custom region number
	CFG_RECT                    stCustomRegions[64];    // custom region, only valid when nOptimizedROIType is NET_THERMO_ROI_CUSTOM
    char                        Reserved[256];          // this reserved field make sure this structure layout match NET_THERMO_GRAPHY_INFO
    int                         nAgc;                   // auto gain control [0-255] detailed value range depending on capacity
    int                         nAgcMaxGain;            // max auto gain [0-255] detailed value range depending on capacity
    int                         nAgcPlateau;            // gain balance, detailed value range depending on capacity
    int                         nGainMode;              // gain mode, see CFG_THERMO_GAIN_MODE
    CFG_THERMO_AUTO_GAIN        stAutoGain;             // auto gain setup, only valid when gain mode is CFG_THERMO_GAIN_MODE_AUTO
} CFG_THERMOGRAPHY_OPTION;

// thermal imaging config
typedef struct tagCFG_THERMOGRAPHY_INFO
{
	int                         nModeCount;             // mode number, only one currently
	CFG_THERMOGRAPHY_OPTION     stOptions[16];          // corresponding to different mode config
} CFG_THERMOGRAPHY_INFO;

// statistics type
typedef enum tagCFG_STATISTIC_TYPE
{
	CFG_STATISTIC_TYPE_UNKNOWN,
	CFG_STATISTIC_TYPE_VAL, // detailed value
	CFG_STATISTIC_TYPE_MAX, // max
	CFG_STATISTIC_TYPE_MIN, // min
	CFG_STATISTIC_TYPE_AVR, // average
	CFG_STATISTIC_TYPE_STD, // standard
	CFG_STATISTIC_TYPE_MID, // center
	CFG_STATISTIC_TYPE_ISO, // ISO
} CFG_STATISTIC_TYPE;

// compare algorithm result
typedef enum tagCFG_COMPARE_RESULT
{
	CFG_COMPARE_RESULT_UNKNOWN,
	CFG_COMPARE_RESULT_BELOW, // below
	CFG_COMPARE_RESULT_MATCH, // match
	CFG_COMPARE_RESULT_ABOVE, // above
} CFG_COMPARE_RESULT;

// Temperature set point alarm
typedef struct tagRADIOMETRY_ALARMSETTING 
{
	int                         nId;                    // alarm SN alarm no. unified SN
	BOOL                        bEnable;                // enable this point alarm
    int                         nResultType;            // temperature measurement alarm result type, see CFG_STATISTIC_TYPE, may take value:
                                                        // point temperature measurement, detailed value,
                                                        // line temperature measurement: max, min, average
                                                        // region temperature measurement: max, min, average, standard, medium, ISO
	int                         nAlarmCondition;        // alarm condition, see CFG_COMPARE_RESULT
	float                       fThreshold;             // alarm threshold temperature, floating point number
	float                       fHysteresis;            // temperature error, flosting point number, such as 0.1 means +/- error is within 0.1
	int                         nDuration;              // threshold temperature duration time, unit:s
} CFG_RADIOMETRY_ALARMSETTING;

// temperature measurement rule local parameter config
typedef struct tagRADIOMETRY_LOCALPARAM
{
	BOOL                        bEnable;                // enable local config or not
	float                       fObjectEmissivity;      // target radiation coefficient, floating poing number
	int                         nObjectDistance;        // target distance	
	int                         nRefalectedTemp;        // target reflection temperature
} CFG_RADIOMETRY_LOCALPARAM;

// temperature measurement rule	
typedef struct tagCFG_RADIOMETRY_RULE
{
	BOOL                        bEnable;                // temperature measurement enable
	int                         nPresetId;              // preset point no.
	int                         nRuleId;                // rule no.
	char                        szName[128];            // custom name
	int                         nMeterType;             // temperature measurement mode type, see NET_RADIOMETRY_METERTYPE
	CFG_POLYGON                 stCoordinates[64];      // temperature point coordinate, use relative coordinate system, take average value as 0~8191
	int                         nCoordinateCnt;         // temperature measurement point coordinate actual number
	int                         nSamplePeriod;          // temperature sampling period unit :s
	CFG_RADIOMETRY_ALARMSETTING stAlarmSetting[64];     // temperature measurement point alarm setup
	int                         nAlarmSettingCnt;       // actual number of measurement points alarm settings
	CFG_RADIOMETRY_LOCALPARAM   stLocalParameters;      // local parameter setup
} CFG_RADIOMETRY_RULE;

// temperature rule configuration structure
typedef struct tagCFG_RADIOMETRY_RULE_INFO
{
    int                         nCount;                 // rule number
    CFG_RADIOMETRY_RULE         stRule[512];			// temperature measurement rule
} CFG_RADIOMETRY_RULE_INFO;

// temperature statistcis
typedef struct tagCFG_TEMP_STATISTICS
{
	BOOL                        bEnable;                // Whether open temperature statistics
	char                        szName[128];            // temperature item name
	int                         nMeterType;             // type temperature measurement mode, see NET_RADIOMETRY_METERTYPE
	int                         nPeriod;                // storage temperature data cycle
} CFG_TEMP_STATISTICS;

// temperature statistics configuration structure
typedef struct tagCFG_TEMP_STATISTICS_INFO
{
	int                         nCount;                 // number
	CFG_TEMP_STATISTICS         stStatistics[64];       // temperature statistcis
} CFG_TEMP_STATISTICS_INFO;

// temperature unit
typedef enum tagCFG_TEMPERATURE_UNIT
{
	TEMPERATURE_UNIT_UNKNOWN,
	TEMPERATURE_UNIT_CENTIGRADE, // Celsius
	TEMPERATURE_UNIT_FAHRENHEIT, // Fahrenheit
} CFG_TEMPERATURE_UNIT;

// thermal imaging temperature measurement global config
typedef struct tagCFG_THERMOMETRY_INFO
{
    int                         nRelativeHumidity;          // relative humidity
    float                       fAtmosphericTemperature;    // atmospheric temperature
    float                       fObjectEmissivity;          // object radiation coefficient
    int                         nObjectDistance;            // object distance
    float                       fReflectedTemperature;      // object reflection temperature
    int                         nTemperatureUnit;           // temperature unit, see TEMPERATURE_UNIT
    BOOL                        bIsothermEnable;            // color batch enable
    int                         nMinLimitTemp;              // isotherm minimum temperature value
    int                         nMediumTemp;                // isotherm median temperature value	
    int                         nMaxLimitTemp;              // isotherm upper limit temperature 
    int                         nSaturationTemp;            // isotherm Saturated temperature 
    CFG_RECT                    stIsothermRect;             // Color temperature rectangular area (OSD position), use the relative coordinates system, the value are 0-8191
    BOOL                        bColorBarDisplay;           // whether to display the color batch (OSD overlay)
    BOOL                        bHotSpotFollow;             // whether enable hotspot detector tracking or not
    BOOL                        bTemperEnable;              // color temperature switch
    CFG_RGBA                    stHighCTMakerColor;         // high color temperature color
    CFG_RGBA                    stLowCTMakerColor;          // low temperature mark color
} CFG_THERMOMETRY_INFO;

// low beam info
typedef struct tagCFG_NEARLIGHT_INFO
{
    BOOL                bEnable;                //Whether enabled, TRUE enabled, FALSE does not enable
    DWORD               dwLightPercent;         // Light brightness percentage (0~100)
    DWORD               dwAnglePercent;         // Lighting angle in percentage (0~100)
}CFG_NEARLIGHT_INFO;

// High beam information 
typedef struct tagCFG_FARLIGHT_INFO 
{
    BOOL                bEnable;                //Whether enabled, TRUE enabled, FALSE does not enable
    DWORD               dwLightPercent;         // Light brightness percentage (0~100)
    DWORD               dwAnglePercent;         //Lighting angle in percentage (0~100)
}CFG_FARLIGHT_INFO;

// The light pattern 
typedef enum tagEM_CFG_LIGHTING_MODE
{
    EM_CFG_LIGHTING_MODE_UNKNOWN,               // Unknown
    EM_CFG_LIGHTING_MODE_MANUAL,                // Manual
    EM_CFG_LIGHTING_MODE_ZOOMPRIO,              // Zoom ratio is preferred
    EM_CFG_LIGHTING_MODE_TIMING,                // Timing
    EM_CFG_LIGHTING_MODE_AUTO,                  // Auto
    EM_CFG_LIGHTING_MODE_OFF,                   // Off
}EM_CFG_LIGHTING_MODE;

#define MAX_LIGHTING_NUM         16

// Light setting details
typedef struct tagCFG_LIGHTING_DETAIL
{
    int                                 nCorrection;                     // Light compensation (0 ~ 4) effective ratio is preferred 
    int                                 nSensitive;                      // Light sensitivity (0 ~ 5) are effective ratio is preferred, the default value is 3    EM_CFG_LIGHTING_MODE                emMode;                          // Light pattern 
    EM_CFG_LIGHTING_MODE                emMode;                          // Light mode
    int                                 nNearLight;                      // Dipped headlights effective number
    CFG_NEARLIGHT_INFO                  stuNearLights[MAX_LIGHTING_NUM]; // Dipped headlight list 
    int                                 nFarLight;                       // High beam effective number 
    CFG_FARLIGHT_INFO                   stuFarLights[MAX_LIGHTING_NUM];  // High beam list 
}CFG_LIGHTING_DETAIL;

#define MAX_LIGHTING_DETAIL_NUM  16

// Light setting (corresponding CFG_CMD_LIGHTING command)
typedef struct tagCFG_LIGHTING_INFO
{
    int                         nLightingDetailNum;                         // Light setting effective number 
    CFG_LIGHTING_DETAIL         stuLightingDetail[MAX_LIGHTING_DETAIL_NUM]; // Light setting information list 
}CFG_LIGHTING_INFO;

// Lighting schedule configuration (CFG_CMD_LIGHTINGSCHEDULE), valid when 'Mode' in CFG_CMD_LIGHTING is 'Timing'
typedef struct tagCFG_LIGHTINGSCHEDULE_INFO
{
    CFG_TIME_SCHEDULE           stuTimeSchedule;                            // Time Schedule
}CFG_LIGHTINGSCHEDULE_INFO;

// RainBrush working mode type
typedef enum tagEM_CFG_RAINBRUSHMODE_MODE
{
    EM_CFG_RAINBRUSHMODE_MODE_UNKNOWN,           // unknown
    EM_CFG_RAINBRUSHMODE_MODE_MANUAL,            // manual
    EM_CFG_RAINBRUSHMODE_MODE_TIMING,            // timing
}EM_CFG_RAINBRUSHMODE_MODE;

// RainBrush voltage enable mode type
typedef enum tagEM_CFG_RAINBRUSHMODE_ENABLEMODE
{
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_UNKNOWN,     // unknown
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_LOW,         // low voltage is valid￡¨close always￡?
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_HIGH,        // high voltage is valid(open always￡?
}EM_CFG_RAINBRUSHMODE_ENABLEMODE;

// RainBrush config(corresponding to CFG_RAINBRUSHMODE_INFO)
typedef struct tagCFG_RAINBRUSHMODE_INFO
{
    EM_CFG_RAINBRUSHMODE_MODE        emMode;         // RainBrush working mode
    EM_CFG_RAINBRUSHMODE_ENABLEMODE  emEnableMode;   // RainBrush voltage enable mode
    int                              nPort;          // I/O port used by RainBrush,-1:no device found,-2:Invalid(device may not offer￡?
}CFG_RAINBRUSHMODE_INFO;

#define MAX_EMERGENCY_REOCRD_CLIENT_NUM         8       // max client number for emergency record

// every client's emergency record config info
typedef struct tagCFG_EMERGENCY_RECORD_CLIENT 
{
    char        szDevID[CFG_COMMON_STRING_128];         // defined by client, may be named as mac address or device sn
    BOOL        bEnable;                                // if enable emergency record or not, TRUE:yes, FLASE:no
    int         nMaxTime;                               // max emergency reocrd time, unit: second 
}CFG_EMERGENCY_RECORD_CLIENT;

// Emergency record for pull(corresponding to CFG_CMD_EMERGENCY_RECORD_FOR_PULL)
typedef struct tagCFG_EMERGENCY_RECORD_FOR_PULL_INFO 
{
    int         nClientNum;                             // valid number of client's config
    CFG_EMERGENCY_RECORD_CLIENT stuEmRecordInfo[MAX_EMERGENCY_REOCRD_CLIENT_NUM];// client's config info 
}CFG_EMERGENCY_RECORD_FOR_PULL_INFO;

// high frequency alarm info
typedef struct tagCFG_HIGH_FREQUENCY 
{
    int         nPeriod;                            // period, unit:second, default:30min(1800s)
    int         nMaxCount;                          // max alarm event alowed uploading to client in a period
}CFG_HIGH_FREQUENCY;

//Alarm shield rule config(corresponding to CFG_CMD_ALARM_SHIELD_RULE)
typedef struct tagCFG_ALARM_SHIELD_RULE_INFO 
{
    CFG_HIGH_FREQUENCY  stuHighFreq;                // high frequency alarm info, set max alarm events alowed to upload in a peroid, prevent from too many events disturbing
}CFG_ALARM_SHIELD_RULE_INFO;


#define CFG_MAX_VIDEOIN_ANALYSER_NUM        3       // Max analyser number
#define CFG_MAX_ANALYSE_RULE_GROUP_NUM      8       // Max rule group number

// Analyser rule group
typedef struct tagCFG_ANALYSERULE_GROUP
{
    DWORD				dwRuleType;					// Rule type
    int                 nRuleStructSize;            // Rule struct size
    BOOL                bEnable;                    // Enable
    BOOL                bEventHandlerEnable;        // Event handler enable
    CFG_ALARM_MSG_HANDLE stuEventHandler;			// Event handler
    CFG_TIME_SCHEDULE   stuEventTimeSection;        // Time section of event
    int                 nRuleNum;                   // Rule number
    char*               pRuleBuf;                   // Rule buffer
    int                 nRuleBufSize;               // Rule buffer size
}CFG_ANALYSERULE_GROUP;

// Analyser information
typedef struct tagCFG_VIDEO_IN_ANALYSER_INFO
{
    CFG_ANALYSEGLOBAL_INFO  stuGlobal;              // Global configuration
    CFG_ANALYSEMODULES_INFO stuModules;             // Module configuration
    CFG_ANALYSERULE_GROUP	stuRuleGroup[CFG_MAX_ANALYSE_RULE_GROUP_NUM]; // Rule configuration
    int                     nRuleGroupNum;          // Rule group number
}CFG_VIDEOIN_ANALYSER_INFO;

// Analyser rule info
typedef struct tagCFG_VIDEO_IN_ANALYSE_RULE_INFO
{
    int                     nAnalyserNum;                               // Analyser number
    CFG_VIDEOIN_ANALYSER_INFO stuAnalysers[CFG_MAX_VIDEOIN_ANALYSER_NUM]; // Analyser information
}CFG_VIDEOIN_ANALYSE_RULE_INFO;

typedef enum tagEM_CFG_ACCESS_WORD_MODE
{
    EM_CFG_ACCESS_WORD_MODE_UNKNOWN,                // Unknown
    EM_CFG_ACCESS_WORD_MODE_NORMAL,                 // Normal
    EM_CFG_ACCESS_WORD_MODE_CLEAN,                  // Clean
    EM_CFG_ACCESS_WORD_MODE_DECORATION,             // Decoration
    EM_CFG_ACCESS_WORD_MODE_UNUSED,                 // Unused
    EM_CFG_ACCESS_WORD_MODE_OUTSTANDING,            // Outstanding
}EM_CFG_ACCESS_WORD_MODE;

// Access work mode(CFG_CMD_ACCESS_WORK_MODE)
typedef struct tagCFG_ACCESS_WORK_MODE_INFO 
{
    EM_CFG_ACCESS_WORD_MODE  emMode;                // work mode
}CFG_ACCESS_WORK_MODE_INFO;

// talk remote time limit
typedef struct tagCFG_VIDEO_TALK_TIME_LIMIT
{
    int                                 nMaxRingingTime;      // incoming ring max length, overtime auto handup, 1-600s
    int                                 nMaxConnectingTime;   // max call duration, overtime auto hang up, 1-600 min
} CFG_VIDEO_TALK_TIME_LIMIT;

// remote device type
typedef enum tagEM_CFG_VT_TYPE
{
    EM_CFG_VT_TYPE_VTH = 0,                                   // VTH
    EM_CFG_VT_TYPE_VTO,                                       // VTO
    EM_CFG_VT_TYPE_VTS,                                       // VTS
    EM_CFG_VT_TYPE_MAX,
} EM_CFG_VT_TYPE;

// video talk call general config (CFG_CMD_VIDEO_TALK_PHONE_GENERAL)
typedef struct tagCFG_VIDEO_TALK_PHONE_GENERAL
{
    char                                szRingFile[MAX_PATH];               // ring file path
    int                                 nRingVolume;                        // ring volume, 0-100
    int                                 nTalkVolume;                        // call volume, 0-100
    CFG_NET_TIME                        stuDisableRingStartTime;            // DND start time
    CFG_NET_TIME                        stuDisableRingEndTime;              // DND end time
    CFG_VIDEO_TALK_TIME_LIMIT           stuTimeLimit[EM_CFG_VT_TYPE_MAX];   // each element correspond to one remote device type, currently only VTS is valid
                                                                            // 0-VTH,1-VTO,2-VTS
    int                                 nMaxMonitorTime;                    // monitoring max length, overt time auto end, 1-600 min
    int                                 nMaxRecordTime;                     // record max length, overtime auto end, 15-300s
    BOOL                                bSnapEnable;                        // call link snapshot enable
                                                                            // after snapshot upload path see config item RecordStoragePoint EventSnapShot
} CFG_VIDEO_TALK_PHONE_GENERAL;

// snapshot combination config
typedef struct tagCFG_TRAFFIC_SNAP_MOSAIC_INFO
{
    BOOL                                bEnable;                            // combine picture or not
    int                                 nPicCompressRate;                   // picture compression ratio, 10-100
    BOOL                                bUploadNormalSnap;                  // upload original picture
} CFG_TRAFFIC_SNAP_MOSAIC_INFO;

// traffic snapshot times
#define TRAFFIC_SNAP_COUNT 4

// snapshot setup, corresponding to one rule
typedef struct tagCFG_SNAPSHOT_RULE
{
    int                                 nType;                              // see in dhnetsdk.h, “intelligent analysis event type” macro definiton
    int                                 nRepeatInterval;                    // 1~1440, unit:min, default
    int                                 nSnapShotType[TRAFFIC_SNAP_COUNT];  // snapshot type group, 0: undefined, 1:close, 2:far
    int                                 nSingleInterval[TRAFFIC_SNAP_COUNT];// snapshot time interval group，
                                                                            // first time: 5~180 default 10 (illegal parking rule valid) unit s
                                                                            // second, third, fourth time: 1~60a default 20s
} CFG_SNAPSHOT_RULE;

// snapshot setup, corresponding to one scene
typedef struct tagCFG_SCENE_SNAPSHOT_RULE
{
    int                                 nPresetID;                          // scene preset no.
    int                                 nCount;                             // rule no.
    CFG_SNAPSHOT_RULE                   stRule[32];                         // single tule setup
} CFG_SCENE_SNAPSHOT_RULE;

// scene snapshot setup
typedef struct tagCFG_SCENE_SNAPSHOT_RULE_INFO
{
    int                                 nCount;                             // scene number
    CFG_SCENE_SNAPSHOT_RULE             stScene[32];                        // single scene config
} CFG_SCENE_SNAPSHOT_RULE_INFO;

#define CFG_MAX_PTZTOUR_NUM             64          // patrol path quantity
#define CFG_MAX_PTZTOUR_PRESET_NUM      64          // patrol path included preset quantity

// patrol path preset
typedef struct tagCFG_PTZTOUR_PRESET 
{
    int             nPresetID;              // preset no.
    int             nDuration;              // change preset duration time, unit s
    int             nSpeed;                 // rotation speed reaching this preset, 1~10
} CFG_PTZTOUR_PRESET;

// patrol path
typedef struct tagCFG_PTZTOUR_SINGLE 
{
    BOOL                        bEnable;                                    // enable
    char                        szName[CFG_COMMON_STRING_64];               // name
    int                         nPresetsNum;                                // preset quantity
    CFG_PTZTOUR_PRESET          stPresets[CFG_MAX_PTZTOUR_PRESET_NUM];      // this path included preset parameter
} CFG_PTZTOUR_SINGLE;

// PTZ patrol path config
typedef struct tagCFG_PTZTOUR_INFO 
{
    int                         nCount;                                     // patrol path quantity
    CFG_PTZTOUR_SINGLE          stTours[CFG_MAX_PTZTOUR_NUM];               // patrol path, each channel includes multiple patrol paths
} CFG_PTZTOUR_INFO;

// VTO type
typedef enum tagEM_CFG_VTO_TYPE
{
    EM_CFG_VTO_TYPE_UNKNOW =0   ,		// unknown
    EM_CFG_VTO_TYPE_VTO         ,		// unit VTO
    EM_CFG_VTO_TYPE_WALL        ,		// fence station
	EM_CFG_VTO_TYPE_MAX			,
}EM_CFG_VTO_TYPE;

// VTO info
typedef struct tagCFG_VTO_INFO 
{
    BOOL            bEnable;                                    // enable
    char            szID[CFG_COMMON_STRING_64];                 // VTO mark
    char            szIP[CFG_COMMON_STRING_64];                 // IP address
    unsigned int    nPort;                                      // port
    EM_CFG_VTO_TYPE emType;                                     // VTO type
    char            szMidNum[CFG_COMMON_STRING_32];             // VTO middle no.
    char            szMachineAddress[CFG_COMMON_STRING_128];    // VTO location
}CFG_VTO_INFO;

// VTO info list
typedef struct tagCFG_VTO_LIST 
{
    int             nVTONum;                            // VTO quantity
    CFG_VTO_INFO    stuVTOInfos[CFG_MAX_VTO_NUM];       // VTO info
}CFG_VTO_LIST;

//touch sceen coordinate
typedef struct tagCFG_TS_POINT
{
    unsigned int     nX;     //coordinate range [0 - 65535]
    unsigned int     nY;     //coordinate range [0 - 65535]
}CFG_TS_POINT;

//touch screen calibration position
typedef struct tagCFG_TSPOINT_INFO
{
    CFG_TS_POINT         stDisplay[TS_POINT_NUM];         //display coordinate, currently only support 3
    CFG_TS_POINT         stScreen[TS_POINT_NUM];          //screen coordinate, currently only support 3
}CFG_TSPOINT_INFO;

//device usa scene
typedef enum tagEM_CFG_VTH_TYPE
{
    EM_CFG_VTH_TYPE_UNKNOW=0 ,   // unknown
    EM_CFG_VTH_TYPE_MAIN     ,   // main VTH
    EM_CFG_VTH_TYPE_SUB      ,   // extension
}EM_CFG_VTH_TYPE;

// device Using Scene
typedef enum tagEM_CFG_VTH_APPTYPE
{
    EM_CFG_VTH_APPTYPE_UNKNOW = 0,                              // Unknown
    EM_CFG_VTH_APPTYPE_COMMON,                                  // normal indoor unit
    EM_CFG_VTH_APPTYPE_MANAGER,                                 // Management Center
}EM_CFG_VTH_APPTYPE;

//VTH no. info
typedef struct tagCFG_VTH_NUMBER_INFO
{
    char                szShortNumber[CFG_COMMON_STRING_32];    // short no. range [1,9999], marking different indoor unit; if it is indoor extension, cornet was "9901-N" N 1,2,3.
    char                szMiddleNumber[CFG_COMMON_STRING_32];   // middle no. format: residence No. (1) + Building No. (2) + unit number (1) + Cornet (4)
    char                szVirtualNumber[CFG_COMMON_STRING_32];  // VTH virtual no. network call, this device foreign number, such as mobile phone nu.
    EM_CFG_VTH_TYPE     emVthType;                              // VTH type
    char                szMainNumber[CFG_COMMON_STRING_32];     // main room no. range [1,9999], when emVthType is EM_CFG_VTH_TYPE_SUB, valid 
    char                szSubNumber[CFG_COMMON_STRING_32];      // extension range [1,5], when emVthType is EM_CFG_VTH_TYPE_SUB, valid
    char                szMainDeviceIP[CFG_COMMON_STRING_64];   // main VTH IP, used to sync extension config with main VTH, when emVthType is EM_CFG_VTH_TYPE_SUB, valid
    EM_CFG_VTH_APPTYPE  emVthAppType;                           // device use scene
}CFG_VTH_NUMBER_INFO;

// GPSOperating mode
typedef enum tagEM_CFG_GPS_MODE
{
    EM_CFG_GPS_MODE_UNKNOWN,
    EM_CFG_GPS_MODE_GPS,                                                    // GPS
    EM_CFG_GPS_MODE_BEIDOU,                                                 // BEIDOU
    EM_CFG_GPS_MODE_GLONASS,                                                // GLONASS
    EM_CFG_GPS_MODE_MIX,                                                    // MIX
    EM_CFG_GPS_MODE_END,                                                    // used to mark sum
} EM_CFG_GPS_MODE;

// Platform Type
typedef enum tagEM_CFG_TRANSFER_PLATFORM
{
    EM_CFG_TRANSFER_PLATFORM_UNKNOWN,
    EM_CFG_TRANSFER_PLATFORM_DSS,                                           // DSS
    EM_CFG_TRANSFER_PLATFORM_JTBB,                                          // JTBB
    EM_CFG_TRANSFER_PLATFORM_END,                                           // used to mark sum
} EM_CFG_TRANSFER_PLATFORM;

// single GPS config
typedef struct tagCFG_GPS_INFO
{
    BOOL                        bEnable;                                    // enable or not
    int                         nSampleInterval;                            // hardware collection period, unit is ms
    int                         nNotifyInterval;                            // application program notice period, unit is ms
    BOOL                        bSyncTime;                                  // sync GPS to device
    EM_CFG_GPS_MODE             emCurMode;                                  // module current work mode
    int                         nSupportModes;                              // support positioning mode quantity
    EM_CFG_GPS_MODE             emSupportModes[EM_CFG_GPS_MODE_END];        // module support positioning mode
    char                        szCurModule[CFG_COMMON_STRING_64];          // current module manufacturer type mark
    BOOL                        bShowLocation;                              // support geographic position display
    int                         nSaveDays;                                  // GPS storage day, used to send as compensation, unit:day, range: 0-365
    int                         nTransferPlatform;                          // support compensation platform quantity
    EM_CFG_TRANSFER_PLATFORM    emTransferPlatform[EM_CFG_TRANSFER_PLATFORM_END];   // support compensation platform, data receiver
} CFG_GPS_INFO;

#define CFG_GPS_INFO_MAX        16

// GPS config
typedef struct tagCFG_GPS_INFO_ALL
{
    int                         nGps;                                       // GPS number
    CFG_GPS_INFO                stGps[CFG_GPS_INFO_MAX];                    // GPS config, each GPS device corresponding to one config
} CFG_GPS_INFO_ALL;


// VTO device type
typedef enum tagNET_CFG_VTO_TYPE
{
	NET_CFG_VTO_TYPE_UNKNOWN = 0,							// unknown
	NET_CFG_VTO_TYPE_VILLA,									// 1 villa
	NET_CFG_VTO_TYPE_DOOR,                                  // 2 VTO
	NET_CFG_VTO_TYPE_LADDER,                                // 3 ladder
	NET_CFG_VTO_TYPE_MAX,
} NET_CFG_VTO_TYPE;

// VTO type

// VTO basic information
typedef struct tagCFG_VTO_BASIC_INFO
{
	 char			  szNumber[AV_CFG_DeviceNo_Len];			// VTO no.
	 NET_CFG_VTO_TYPE emCfgVtoType;								// device type: 1 villa 2 VTO 3 ladder
	 EM_CFG_VTO_TYPE  emType;									// VTO type 1 unit VTO 2 fence station
	 char			  szAnalogVersion[CFG_COMMON_STRING_64];	// analog system version
	 BOOL			  bFaceDetect;								// face recognition 1 enable 2 disable
	 int			  nPositon;									// VTO floor location Int32, 0 means invalid
																// 1,2, means level 1, 2; -1, -2 means basement 1, 2
}CFG_VTO_BASIC_INFO;

typedef enum tagEM_CFG_SHORTCUT_CALL_POSITION_TYPE
{
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_UNKNOWN,         // unknown
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_SUPERMARKET,     // supermarket
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_RESTAURANT,      // restaurant
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_HOSPITAL,        // hospital
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_MANAGER,         // MGT center	
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_CUSTOM,          // custom
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE_FRUITSTORE,      // fruitstore
}EM_CFG_SHORTCUT_CALL_POSITION_TYPE;

//Shortcut no. info
typedef struct tagCFG_SHORTCUT_CALL
{
    char			                    szCallNumber[CFG_COMMON_STRING_64];	// shortcut no.
    EM_CFG_SHORTCUT_CALL_POSITION_TYPE  emPositionType;						// location type
}CFG_SHORTCUT_CALL;

//shortcut no. config
typedef struct tagCFG_SHORTCUT_CALL_INFO
{
    int                 nMaxNum;                        // max structure number, keep identical with pShortcutCallInfo pointed structure number
    CFG_SHORTCUT_CALL*  pShortcutCallInfo;              // used to store shortcut no. info structure indicator, applied by user
    int                 nValidNum;                      // valid structure number, filled by sdk when gotten, and filled by user when set
}CFG_SHORTCUT_CALL_INFO;

// record set GPSLocation version no.	
typedef struct tagCFG_LOCATION_VER_INFO
{
    unsigned int        nVer;                           // version no.
} CFG_LOCATION_VER_INFO;

// Access filter configuration ( CFG_CMD_PARKING_SPACE_ACCESS_FILTER )
typedef struct tagCFG_PARKING_SPACE_ACCESS_FILTER_INFO
{
    BOOL                    bEnable;                                                // filter enable
    int                     nTrustListNum;                                          // number of trust ip in szTrustList
    char                    szTrustList[CFG_MAX_TRUST_LIST][CFG_FILTER_IP_LEN];	    // trust ip array
} CFG_PARKING_SPACE_ACCESS_FILTER_INFO;

// work time config CFG_CMD_WORK_TIME
typedef struct tagCFG_WORK_TIME_INFO
{
    BOOL                bEnable;                        // config is valid when TRUE, DH_ALARM_BUS_DRIVE_AFTER_WORK event will be reported out of work time,config is invalid when FALSE
    CFG_TIME            stWorkTimeBegin;                // work time begin
    CFG_TIME            stWorkTimeEnd;                  // work time end
    DWORD               dwOutTimeBegin;                 // out and maintain time begin, utc, unit second
    DWORD               dwOutTimeEnd;                   // out and maintain time end, utc, unit second
} CFG_WORK_TIME_INFO;

// 车位监管状态
typedef enum tagEM_CFG_LANE_STATUS
{
    EM_CFG_LANE_STATUS_UNKOWN = -1,                     // status unkown
    EM_CFG_LANE_STATUS_UNSUPERVISE = 0,                 // not supervise
    EM_CFG_LANE_STATUS_SUPERVISE = 1,                   // supervise
}EM_CFG_LANE_STATUS;

#define MAX_LANES_NUM               64                  // the max number of parking spaces

// 单个车位指示灯本机配置 
typedef struct tagCFG_PARKING_SPACE_LIGHT_GROUP_INFO
{
    BOOL                bEnable;                            // config is valid when TRUE，config is invalid when FALSE
    EM_CFG_LANE_STATUS  emLaneStatus[MAX_LANES_NUM];        // the status of parking spaces
    int                 nLanesNum;                          // the number of parking spaces in actually
    BOOL                bAcceptNetCtrl;                     // Is accept remote control    
}CFG_PARKING_SPACE_LIGHT_GROUP_INFO;

#define MAX_LIGHT_GROUP_INFO_NUM        8                   // the max number of Parking Space Light Group Config

// Parking Space Light Group config    CFG_CMD_PARKING_SPACE_LIGHT_GROUP
typedef struct tagCFG_PARKING_SPACE_LIGHT_GROUP_INFO_ALL
{
    int                                         nCfgNum;                                            // config number from device
    CFG_PARKING_SPACE_LIGHT_GROUP_INFO          stuLightGroupInfo[MAX_LIGHT_GROUP_INFO_NUM];        // Parking Space Light Group config,each Light Group corresponding to one config
}CFG_PARKING_SPACE_LIGHT_GROUP_INFO_ALL;

// Custom audio(CFG_CMD_CUSTOM_AUDIO)
typedef struct tagCFG_CUSTOM_AUDIO 
{
    char                szPlateNotInDB[MAX_PATH];           // file path of alarm audio which indicats plate not in database
}CFG_CUSTOM_AUDIO;


// radar configuration - car speed
typedef struct tagCFG_RADAR_CARSPEED 
{
    int                 nTriggerLower;                  // lowerbound of trigger value
    int                 nTriggerUpper;                  // upperbound of trigger value
    int                 nLimitLower;                    // lowerbound of limit value
    int                 nLimitUpper;                    // upperbound of limit value
} CFG_RADAR_CARSPEED;

// dahua radar configuration (CFG_CMD_DHRADER_PP)
typedef struct tagCFG_DAHUA_RADAR
{
    int                 nAngle;                         // Angle, useful when correcting speed error from radar sensor installation angle. Unit: degree, range: 0~45
    BOOL                bLowSpeed;                      // whether or not enable lowerbounds. if TRUE, the lowerbounds in CFG_RADAR_CARSPEED are valid
    BOOL                bSpeedForSize;                  // whether or not discriminate different car size, if FALSE, only small car speed config (stuSmallCarSpeed) is valid
    CFG_RADAR_CARSPEED  stuSmallCarSpeed;               // small car speed, if bSpeedForSize is TRUE, nTriggerLower member is ALSO lowerbounds for medium car and large car
    CFG_RADAR_CARSPEED  stuMediumCarSpeed;              // medium car speed, valid only if bSpeedForSize is TRUE, but nTriggerLower member is ALWAYS invalid.
    CFG_RADAR_CARSPEED  stuBigCarSpeed;                 // large car speed, valid only if bSpeedForSize is TRUE, but nTriggerLower member is ALWAYS invalid.
    char                szName[256];                    // device installation address
    int                 nSensitivity;                   // Sensitivity, range: 0~5, 0 is most sensitive
    int                 nDetectMode;                    // Detect Mode, values: -1  nonsense, 0 approaching in front, 1 leaving in front, 2 approaching behind, 3 leaving behind, 4 in front (approaching or leaving), 5 behind (approaching or leaving)
} CFG_DAHUA_RADAR;

// configuration of searching wifi device, CFG_CMD_WIFI_SEARCH
typedef struct tagCFG_WIFI_SEARCH_INFO
{
    BOOL                bEnable;                        // is configuration enable or not
    int                 nPeriod;                        // event reported period, unit s
} CFG_WIFI_SEARCH_INFO;

// vehicle-mounted communication module can auto change 3G/4G (CFG_CMD_G3G4AUTOCHANGE)       
typedef struct tagCFG_G3G4AUTOCHANGE
{
    BOOL                bEnable;                            // config is valid when TRUE，config is invalid when FALSE   
}CFG_G3G4AUTOCHANGE;


#define MAX_POS_CODE_LENGTH             32                                      // The max length of POS check code
#define MAX_ARRAY_POS_CODE              10                                      // The max number of the array 

// configuration of POS checkcode(CFG_CMD_CHECKCODE)
typedef struct tagCFG_CHECKCODE_INFO 
{
    BOOL                    bEnable;                                            // is configuration enable or not
    int                     nCodeCount;                                         // the number of check code array in actually
    char                    szCode[MAX_ARRAY_POS_CODE][MAX_POS_CODE_LENGTH];    // array of check code
}CFG_CHECKCODE_INFO;

// configuration of Sichuan Mobile keep an eye on shop (CFG_CMD_VSP_SCYDKD)
typedef struct tagCFG_VSP_SCYDKD_INFO
{
    BOOL                    bEnable;                            // is configuration enable or not
    char                    szServerIP[128];                    // Server IP
    int                     nServerPort;                        // Server Port
    char                    szDeviceID[32];                     // ID of video input device
    char                    szUserName[32];                     // UserName of Qidi Platform
}CFG_VSP_SCYDKD_INFO;

// ptz power up action config
typedef struct tagCFG_PTZ_POWERUP_INFO 
{
    BOOL                    bEnable;                            // whether or not enable power-up action
    int                     nFunction;                          // power-up function, -1: continue the action before power down, for other valid values, see EM_PTZ_ACTION
    int                     nScanId;                            // Scan Id
    int                     nPresetId;                          // Preset Id
    int                     nPatternId;                         // Pattern Id
    int                     nTourId;                            // Tour Id
} CFG_PTZ_POWERUP_INFO;

// VTH's remote IPC config
#define MAX_REMOTE_IPC_NUM 32    // max remote IPC num

// remote IPC protocol type
typedef enum tagEM_CFG_REMOTE_IPC_DEVICE_PROTOCOL
{
    EM_CFG_REMOTE_IPC_DEVICE_PROTOCOL_UNKNOWN = 0,      // unknown
    EM_CFG_REMOTE_IPC_DEVICE_PROTOCOL_HIKVISION,        // hikvision
    EM_CFG_REMOTE_IPC_DEVICE_PROTOCOL_PRIVATE3,          // private 3rd protocol
}EM_CFG_REMOTE_IPC_DEVICE_PROTOCOL;

// remote IPC stream type
typedef enum tagEM_CFG_REMOTE_IPC_DEVICE_STREAMTYPE
{
    EM_CFG_REMOTE_IPC_DEVICE_STREAM_TYPE_UNKNOWN = 0,      // unknown
    EM_CFG_REMOTE_IPC_DEVICE_STREAM_TYPE_MAIN,             // main stream
    EM_CFG_REMOTE_IPC_DEVICE_STREAM_TYPE_EXTRA1,           // extra stream
}EM_CFG_REMOTE_IPC_DEVICE_STREAMTYPE;

#define MAX_REMOTEIPCINFO_IPADDR_LEN        128     // max remote IPC IP address length
#define MAX_REMOTEIPCINFO_MACADDR_LEN       64      // max remote IPC MAC address length
#define MAX_REMOTEIPCINFO_USERNAME_LEN      128     // max remote IPC username length
#define MAX_REMOTEIPCINFO_USERPSW_LENGTH    128     // max remote IPC password length

// remote IPC information
typedef struct tagCFG_REMOTE_IPC_INFO
{
    char		                        szIP[MAX_REMOTEIPCINFO_IPADDR_LEN];	            // device ip
    char                                szMac[MAX_REMOTEIPCINFO_MACADDR_LEN];           // MAC address
    char		                        szUser[MAX_REMOTEIPCINFO_USERNAME_LEN];	        // username 
	char		                        szPassword[MAX_REMOTEIPCINFO_USERPSW_LENGTH];   // password 
	int	                                nPort;					                        // port
	EM_CFG_REMOTE_IPC_DEVICE_PROTOCOL   emProtocol;                                     // protocol type, 
	EM_CFG_REMOTE_IPC_DEVICE_STREAMTYPE emStreamType;                                   // media stream type
	int                                 nChannel;                                       // channel number
}CFG_REMOTE_IPC_INFO;

// VTH's remote IPC config structure, corresponding to CFG_CMD_VTH_REMOTE_IPC_INFO
// this config is global, not for single channel 
typedef struct tagCFG_VTH_REMOTE_IPC_INFO
{
    int nRemoteIPCNum;                                              // remote IPC number
    CFG_REMOTE_IPC_INFO stuCfgRemoteIpcInfo[MAX_REMOTE_IPC_NUM];     // remote IPC information
}CFG_VTH_REMOTE_IPC_INFO;

// day/night color change config - for a single time section
typedef struct tagDAYNIGHT_INFO
{
    int                     nType;                              // type of switch, 1 - electronic, 2 - mechanical, usually ICR
    int                     nMode;                              // colorful/monochrome mode, 1- always colorful, 2- automatically changed by illumination, 3- always monochrome, 4- by Photo resistor, 5-  by gain, 6- by external alarm input, 7?by external IO
    int                     nSensitivity;                       // colorful/monochrome switch's sensitivity, 0~7
    int                     nDelay;                             // day/night mode switch delay, 3 ~ 30 (seconds)
} DAYNIGHT_INFO;

// day/night color change config
typedef struct tagCFG_VIDEOIN_DAYNIGHT_INFO
{
    DAYNIGHT_INFO           stuSection[VIDEOIN_TSEC_NUM];       // config for time sections, in the order: normal, day, night
} CFG_VIDEOIN_DAYNIGHT_INFO;

// single configuration of mix channel
typedef struct tagCFG_AUDIO_MIX_CHANNEL_INFO
{
    int                    nChannelNum;                              // the number of combination channel
    int                    nCombination[32];                         // combination of audio in channel
}CFG_AUDIO_MIX_CHANNEL_INFO;

// configuration of audio mix channel(CFG_CMD_AUDIO_MIX_CHANNEL)
typedef struct tagCFG_AUDIO_MIX_CHANNEL_INFO_ALL
{
    
    int                           nMixChnInfoNum;                     // the number of audio mix channel
    CFG_AUDIO_MIX_CHANNEL_INFO    stuMixChnInfo[16];                  // array of audio mix channel information 
}CFG_AUDIO_MIX_CHANNEL_INFO_ALL;

#define CFG_AUDIOTOUCH_PITCH_INVALID_VALUE    -999                    // the invalid value of nPitch
#define CFG_AUDIOTOUCH_PITCH_MIN_VALUE        -50                     // the min value of nPitch
#define CFG_AUDIOTOUCH_PITCH_MAX_VALUE         50                     // the max value of nPitch
// single audio channel pitch config
typedef struct tagCFG_AUDIO_TOUCH_INFO
{
    int                           nPitch;                             // value of pitch,  range(-50~50)  0 means not change 
}CFG_AUDIO_TOUCH_INFO;

// configuration of audio pitch change (CFG_CMD_AUDIO_TOUCH)
typedef struct tagCFG_AUDIO_TOUCH_INFO_ALL
{
    BOOL                          bEnable;                            // is configuration enable or not
    int                           nAudioTouchNum;                     // the Number of Configuration
    CFG_AUDIO_TOUCH_INFO          stuTouchInfo[64];                   // array of audio pitch information
}CFG_AUDIO_TOUCH_INFO_ALL;

//unfocusdetect config(CFG_CMD_UNFOCUSDETECT)
typedef struct tagCFG_UNFOCUSDETECT_INFO
{
    BOOL                    bEnable;                        // Enable
    int                     nSensitivity;                   // sensitivity   1~100
	CFG_ALARM_MSG_HANDLE    stuEventHandler;				// Alarm activation
    CFG_TIME_SECTION	    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];   // Event responding period,if you want set and get time, take this as the standard;ignore the "stuTimeSection" filed in stuEventHandler
}CFG_UNFOCUSDETECT_INFO;

// configuration of video mosaic(corresponding to CFG_CMD_VIDEO_MOSAIC)
typedef struct tagCFG_VIDEO_MOSAIC_INFO
{
	BOOL			bEnable;					//  is configuration enable or not
	int				nMosaic;					//  the size of mosaic
	int				nRectCount;					//  the count of valid rect
	CFG_RECT		stuRect[MAX_RECT_COUNT];	//  the value of rect
} CFG_VIDEO_MOSAIC_INFO;

// configuration of scene moved detect
typedef struct tagCFG_MOVE_DETECT_INFO
{
	BOOL					bEnable;			// is scene moved detect enable or not
	int						nSensitivity;		// the sensitivity of detect[0~100]
	CFG_ALARM_MSG_HANDLE	stuEventHandler;	// the configuration of event handler
} CFG_MOVE_DETECT_INFO;

typedef enum tagEM_CFG_ATMCONTROLLER_MODE
{
    EM_CFG_ATMCONTROLLER_MODE_UNKNOWN = 0,        //Unknown
    EM_CFG_ATMCONTROLLER_MODE_CLOSE,              //Close
    EM_CFG_ATMCONTROLLER_MODE_OPEN,               //Open
    EM_CFG_ATMCONTROLLER_MODE_LINKAGE,            //LinkAge
}EM_CFG_ATMCONTROLLER_MODE;

// configuration of AtmController FloodLight mode
typedef struct tagCFG_FLOODLIGHT_CONTROLMODE_INFO
{
    EM_CFG_ATMCONTROLLER_MODE emControlMode;          //Controlmode
}CFG_FLOODLIGHT_CONTROLMODE_INFO;

// configuration of AtmController AirFan mode
typedef struct tagCFG_AIRFAN_CONTROLMODE_INFO
{
    EM_CFG_ATMCONTROLLER_MODE emControlMode;          //Controlmode
}CFG_AIRFAN_CONTROLMODE_INFO;
// EAP method
typedef enum tagEM_CFG_EAP_METHOD
{
    EM_CFG_EAP_METHOD_UNKNOWN,                            // UnKnown
    EM_CFG_EAP_METHOD_PEAP,                               // PEAP
    EM_CFG_EAP_METHOD_TLS,                                // TLS
    EM_CFG_EAP_METHOD_TTLS,                               // TTLS
} EM_CFG_EAP_METHOD;

// EAP AuthType
typedef enum tagEM_CFG_EAP_AUTH_TYPE
{
    EM_CFG_EAP_AUTH_TYPE_UNKNOWN,                            // UnKnown
    EM_CFG_EAP_AUTH_TYPE_NONE,                               // NONE
    EM_CFG_EAP_AUTH_TYPE_PAP,                                // PAP
    EM_CFG_EAP_AUTH_TYPE_MSCHAP,                             // MSCHAP
    EM_CFG_EAP_AUTH_TYPE_MSCHAPV2,                           // MSCHAPV2
    EM_CFG_EAP_AUTH_TYPE_GTC,                                // GTC
} EM_CFG_EAP_AUTH_TYPE;

// wireless Authentication
typedef enum tagEM_CFG_WIRELESS_AUTHENTICATION
{
    EM_CFG_WIRELESS_AUTHENTICATION_UNKNOWN,                             // UnKnown
    EM_CFG_WIRELESS_AUTHENTICATION_OPEN,                                // OPEN
    EM_CFG_WIRELESS_AUTHENTICATION_SHARED,                              // SHARED
    EM_CFG_WIRELESS_AUTHENTICATION_WPA,                                 // WPA
    EM_CFG_WIRELESS_AUTHENTICATION_WPAPSK,                              // WPA-PSK
    EM_CFG_WIRELESS_AUTHENTICATION_WPA2,                                // WPA2
    EM_CFG_WIRELESS_AUTHENTICATION_WPA2PSK,                             // WPA2-PSK
    EM_CFG_WIRELESS_AUTHENTICATION_WPANONE,                             // WPA-NONE
    EM_CFG_WIRELESS_AUTHENTICATION_WPAPSK_WPA2PSK,                      // WPA-PSK/WPA2-PSK
    EM_CFG_WIRELESS_AUTHENTICATION_WPA_WPA2,                            // WPA/WPA2
    EM_CFG_WIRELESS_AUTHENTICATION_WPA_WPAPSK,                          // WPA/WPA-PSK
    EM_CFG_WIRELESS_AUTHENTICATION_WPA2_WPA2PSK,                        // WPA2/WPA2-PSK
    EM_CFG_WIRELESS_AUTHENTICATION_WPA_WPAPSK_WPA2_WPA2PSK,             // WPA/WPA-PSK|WPA2/WPA2-PSK
} EM_CFG_WIRELESS_AUTHENTICATION;

// DataEncryption type
typedef enum tagEM_CFG_WIRELESS_DATA_ENCRYPT
{
    EM_CFG_WIRELESS_DATA_ENCRYPT_UNKNOWN,                            // UnKnown
    EM_CFG_WIRELESS_DATA_ENCRYPT_NONE,                               // NONE
    EM_CFG_WIRELESS_DATA_ENCRYPT_WEP,                                // WEP
    EM_CFG_WIRELESS_DATA_ENCRYPT_TKIP,                               // TKIP
    EM_CFG_WIRELESS_DATA_ENCRYPT_AES,                                // AES(CCMP)
    EM_CFG_WIRELESS_DATA_ENCRYPT_TKIP_AES,                           // TKIP+AES
} EM_CFG_WIRELESS_DATA_ENCRYPT;

// EAP of one WLAN
typedef struct tagCFG_WLAN_EAP
{
    EM_CFG_EAP_METHOD       emMethod;                           // EAP method
    EM_CFG_EAP_AUTH_TYPE    emAuthType;                         // EAP auth
    char                    szIdentity[MAX_USERNAME_LEN];       // Identity
    char                    szAnonymousID[MAX_USERNAME_LEN];    // AnonymousID
    char                    szPassword[MAX_PASSWORD_LEN];       // Password
    char                    szCaCert[512];                      // CA
    char                    szUserCert[512];                    // User Cert
} CFG_WLAN_EAP;

// Network of one WLAN
typedef struct tagCFG_WLAN_NETWORK
{
    char                    szIPAddress[AV_CFG_IP_Address_Len_EX];        // IP
    char                    szSubnetMask[AV_CFG_IP_Address_Len_EX];       // subnet mask
    char                    szDefaultGateway[AV_CFG_IP_Address_Len_EX];   // gateway
    BOOL                    bDhcpEnable;                                  // DHCP enable
    char                    szDnsServers[2][AV_CFG_IP_Address_Len_EX];    // DNS servers
} CFG_WLAN_NETWORK;

// WLAN configure
typedef struct tagCFG_WLAN_INFO
{
    char                    szWlanName[CFG_COMMON_STRING_32];   // Wlan name, read only
    BOOL                    bEnable;                            // WIFI interface enable
    char                    szSSID[CFG_MAX_SSID_LEN];           // SSID
    BOOL                    bConnectEnable;                     // manual connect to WLAN, TRUE: connect, FALSE: disconnect
    BOOL                    bLinkEnable;                        // auto connect to WALN, TRUE: no, FALSE: yes, no scene for IPC
    int                     nLinkMode;                          // link mode, 0: auto, 1: adhoc, 2: Infrastructure
    int                     nEncryption;                        // Encryption, 0: off, 1: on, 2: WEP-OPEN, 3: WEP-SHARED, 4: WPA-TKIP, 5: WPA-PSK-TKIP, 6: WPA2-TKIP, 7: WPA2-PSK-TKIP, 8: WPA-AES, 9: WPA-PSK-AES, 10: WPA2-AES, 11: WPA2-PSK-AES
                                                                /* byAuthMode  , byEncrAlgr  reference to nEncryption
                                                                                                                Authentication         DataEncryption              Encryption
                                                                                                                OPEN                    NONE                        "On" 
                                                                                                                OPEN                    WEP                         "WEP-OPEN"
                                                                                                                SHARD                   WEP                         "WEP-SHARED"
                                                                                                                WPA                     TKIP                        "WPA-TKIP"
                                                                                                                WPA-PSK                 TKIP                        "WPA-PSK-TKIP"
                                                                                                                WPA2                    TKIP                        "WPA2-TKIP"
                                                                                                                WPA2-PSK                TKIP                        "WPA2-PSK-TKIP"
                                                                                                                WPA                     AES(CCMP)                   "WPA-AES"
                                                                                                                WPA-PSK                 AES(CCMP)                   "WPA-PSK-AES"
                                                                                                                WPA2                    AES(CCMP)                   "WPA2-AES"
                                                                                                                WPA2-PSK                AES(CCMP)                   "WPA2-PSK-AES"
                                                                                                                WPA                     TKIP+AES( mix Mode)         "WPA-TKIP" or "WPA-AES"
                                                                                                                WPA-PSK                 TKIP+AES( mix Mode)         "WPA-PSK-TKIP" or "WPA-PSK-AES"
                                                                                                                WPA2                    TKIP+AES( mix Mode)         "WPA2-TKIP" or "WPA2-AES"
                                                                                                                WPA2-PSK                TKIP+AES( mix Mode)         "WPA2-PSK-TKIP" or "WPA2-PSK-AES"
                                                                                                                */
    EM_CFG_WIRELESS_AUTHENTICATION emAuthentication;            // Authentication, unused
    EM_CFG_WIRELESS_DATA_ENCRYPT   emDataEncryption;            // Data Encryption, unused
    int                     nKeyType;                           // Key Type, 0: Hex, 1: ASCII
    int                     nKeyID;                             // Key index, range of 0~3
    char                    szKeys[4][32];                      // four keys
    BOOL                    bKeyFlag;                           // is key set or not
    CFG_WLAN_EAP            stuEap;                             // EAP
    CFG_WLAN_NETWORK        stuNetwork;                         // Network
} CFG_WLAN_INFO;

// all WLAN configure(corresponding to CFG_CMD_WLAN)
typedef struct tagCFG_NETAPP_WLAN
{
    int                     nNum;                               // valid WLAN info in stuWlanInfo
    CFG_WLAN_INFO           stuWlanInfo[8];                     // WLAN info
} CFG_NETAPP_WLAN;

// Smart H264 encode
typedef struct tagCFG_SMART_ENCODE_INFO
{
	BOOL				bSmartH264;							    //is key set of SmartH264
	BYTE                byReserved[256];						//reserved
} CFG_SMART_ENCODE_INFO;

// vehicle mounted high speed alarm config
typedef struct tagCFG_VEHICLE_HIGHSPEED_INFO
{
	BOOL                    bEnable;							// speed upper limit, trigger alarm if speed is higher
	int						nSpeedHighLine;						// high speed limit alarm value  unit:Km/h
	int						nTime;								// time interval between overspeed and alarming unit:second
	int						nAlertSpeed;						// Alerting speed  unit:Km/h
	int						nInstantSpeed;						// Instantaneous speed  unit:Km/h
	CFG_ALARM_MSG_HANDLE    stuEventHandler;			        // alarm linkage
} CFG_VEHICLE_HIGHSPEED_INFO;

// vehicle mounted low speed alarm config
typedef struct tagCFG_VEHICLE_LOWSPEED_INFO
{
	BOOL                    bEnable;							// low speed alarm enable
	int						nSpeedLowLine;						// speed lower limit, trigger alarm if speed is lower  unit:Km/h
	int						nTime;								// time interval between low-speed and alarming unit:second
	int						nSpeedMotion;						// open motion detection if speed is lower  unit:Km/h
	CFG_ALARM_MSG_HANDLE    stuEventHandler;			        // alarm linkage
} CFG_VEHICLE_LOWSPEED_INFO;

// single configuration of personal telephone
typedef struct tagCFG_PSTN_PERSON_SERVER_INFO
{
    char					szName[MAX_NAME_LEN];						// personal telephone name
    char					szNumber[MAX_PHONE_NUMBER_LEN];				// personal telephone number
}CFG_PSTN_PERSON_SERVER_INFO;

// configuration of personal telephone(corresponding to CFG_CMD_PSTN_PERSON_SERVER)
typedef struct tagCFG_PSTN_PERSON_SERVER_INFO_ALL
{
    BOOL                            bEnable;                                    // is configuration enable or not
    int                             nServerCount;                               // valid personal telephone information in stuPSTNPersonServer,the max number is 3 at present
    CFG_PSTN_PERSON_SERVER_INFO     stuPSTNPersonServer[MAX_PSTN_SERVER_NUM];   // personal telephone information configuration array,Each element corresponds to one personal telephone information
                                                                                // use CLIENT_QueryNewSystemInfo(CFG_CAP_ALARM) can get the max number of valid element 
}CFG_PSTN_PERSON_SERVER_INFO_ALL;

// configuration of Arm or disarm(corresponding to CFG_CMD_ARM_LINK)
typedef struct tagCFG_ARMLINK_INFO
{
    BOOL                            bMMSEnable;                                 // is send short massage(default:send)
    CFG_PSTN_ALARM_SERVER	        stuPSTNAlarmServer;						    // Telephone Alarm Center Linkage Information
    BOOL                            bPersonAlarmEnable;                         // is call person who is the linkman in the PSTNPersonServer configuration
}CFG_ARMLINK_INFO;



/************************************************************************
 ** Interface Definition 
 ***********************************************************************/
// Alarm event type. It is the alarm type parsing from the dhnetsdk.h.
typedef int  (CALLBACK *fALARMEvent)(DWORD dwAlarmType, void* pAlarmInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// Data analysis by callback. dwDataType is the type after the data analysis. 
typedef int  (CALLBACK *fAnalyzerData)(DWORD dwDataType, void* pDataInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// Analyze searched config info
CLIENT_CFG_API BOOL  CALL_METHOD CLIENT_ParseData(char* szCommand, char* szInBuffer, LPVOID lpOutBuffer, DWORD dwOutBufferSize, void* pReserved);

// Constitute the configuration information to be set.
CLIENT_CFG_API BOOL  CALL_METHOD CLIENT_PacketData(char* szCommand, LPVOID lpInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize);

// Recrod alarm event analysis
CLIENT_CFG_API BOOL  CALL_METHOD CLIENT_ParseAnalyzerEventData(LPVOID lpInBuffer, DWORD dwInBufferSize, fALARMEvent cbEvent, LDWORD dwUser);

// Data analysis via the callback. 
CLIENT_CFG_API BOOL CALL_METHOD CLIENT_ParseDataByCallback(LPVOID lpInBuffer, DWORD dwInBufferSize, fAnalyzerData cbAnalyzer, LDWORD dwUser);
#ifdef __cplusplus
}
#endif

#endif // DHCONFIGSDK_H
