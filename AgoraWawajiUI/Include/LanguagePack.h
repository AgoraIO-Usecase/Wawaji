#pragma once
#include "stdafx.h"
#include <atlstr.h>

/*Author:baluoteliz@gmail.com
  CreateTime: 20180327

  Note: light language pack
*/

extern CFileIO gAgoraWawajiLog;
extern std::string gStrCurRunningExeName;
extern std::string gStrInstance;

namespace
	AgoraWawaji{

	namespace
		Language_Pack{//default

		enum eTagLanguageType{
			eLanguage_NULL = -1, 
			eLanguage_ENU,
			eLanguage_CHZ,

			eLanguage_UNKNOWN = 0xff
		};

		static eTagLanguageType gEnumLangType = eLanguage_ENU;

		static CString gStrUIDKey = L"";
		static CString gStrCameraKey = L"";
		static CString gStrAppId = L"";
		static CString gStrAppCertificateId = L"";
		static CString gStrChannel = L"";
		static CString gStrVideoProfile = L"";
		static CString gStrUpTime = L"";
		static CString gStrSettings = L"";
		static CString gStrStart = L"";
		static CString gStrRestart = L"";
		static CString gStrUploadLog = L"";

		static CString gStrTitleUI = L"";

		namespace
			Language_Chinese{

			const TCHAR* const  KUIDKey = L"账号";
			const TCHAR* const  KCameraKey = L"摄像头";
			const TCHAR* const  KBtnSettings = L"设置";
			const TCHAR* const  KBtnStartLive = L"开始直播";
			const TCHAR* const  KBtnRestart =   L"重新直播";
			const TCHAR* const  KBtnUpLoads = L"上传日志";
			const TCHAR* const  KTitleNameUI = L"声网娃娃机推流程序";


		}

		namespace
			Language_English{

			const TCHAR* const KUIDKey = L"UID";
			const TCHAR* const KCameraKey = L"CameraName";
			const TCHAR* const  KBtnSettings = L"Settings";
			const TCHAR* const  KBtnStartLive = L"StartLive";
			const TCHAR* const  KBtnRestart = L"Restart Live";
			const TCHAR* const  KBtnUpLoads = L"Upload Logs";
			const TCHAR* const KTitleNameUI = L"AgoraWawaji";

		}

		static void switchLang(){

			switch (gEnumLangType){
			case eTagLanguageType::eLanguage_CHZ:{
#define IMPLEMENT_Chinese(gObject,Key)\
	gObject = (TCHAR*)(Language_Chinese::Key);

				IMPLEMENT_Chinese(gStrUIDKey, KUIDKey)
				IMPLEMENT_Chinese(gStrCameraKey, KCameraKey)
				IMPLEMENT_Chinese(gStrTitleUI, KTitleNameUI)
				IMPLEMENT_Chinese(gStrSettings, KBtnSettings)
				IMPLEMENT_Chinese(gStrStart, KBtnStartLive)
				IMPLEMENT_Chinese(gStrRestart, KBtnRestart)
				IMPLEMENT_Chinese(gStrUploadLog, KBtnUpLoads)
			}
												 break;
			case eTagLanguageType::eLanguage_ENU:{
#define IMPLEMENT_English(gObject,Key)\
	gObject = (TCHAR*)(Language_English::Key);

				IMPLEMENT_English(gStrUIDKey, KUIDKey)
				IMPLEMENT_English(gStrCameraKey, KCameraKey)
				IMPLEMENT_English(gStrTitleUI, KTitleNameUI)
				IMPLEMENT_English(gStrSettings, KBtnSettings)
				IMPLEMENT_English(gStrStart, KBtnStartLive)
				IMPLEMENT_English(gStrRestart, KBtnRestart)
				IMPLEMENT_English(gStrUploadLog, KBtnUpLoads)
			}
												 break;
			case eTagLanguageType::eLanguage_NULL:
			case eTagLanguageType::eLanguage_UNKNOWN:
				break;
			default:break;
			}
		}

	}

	namespace
		StrKeyQuote{
		
		const char* const KAppAttributeMainUI = "MainUI";
		const char* const KStreamInstance1 = "Instance1";
		const char* const KStreamInstance2 = "Instance2";
		const char* const KAppAttributeInstance = "Instance";
		const char* const KMediaSDKInstance = "Instance";
		const char* const KSignalSdkInstance = "Instance";
		const char* const KConfigBaseInfo = "BaseInfo";
		const char* const KWawajiStream = "WawajiStreamInstance.exe";
	}

	namespace
		FormatStr{

		class CAgoraFormatStr{
		public:

			static void PASCAL AgoraMessageBox(LPCTSTR lpFormat, ...){

				TCHAR szBuffer[1024] = { _T("\0") };
				va_list args;
				_tcsnccat_s(szBuffer, s2cs(gStrInstance + ": "), gStrInstance.length() + 2);
				va_start(args, lpFormat);
				_vsnwprintf(szBuffer + _tcslen(szBuffer), sizeof(szBuffer) / sizeof(TCHAR) - _tcslen(szBuffer), lpFormat, args);
				va_end(args);

				AfxMessageBox(szBuffer);
			}

			static void PASCAL AgoraOutDebugStr(LPCTSTR lpFormat, ...){

				TCHAR szBuffer[1024] = { _T("\0") };
				va_list args;
				_tcsnccat(szBuffer,_T("\n"),1);
				va_start(args, lpFormat);
				_vsnwprintf(szBuffer + _tcslen(szBuffer), sizeof(szBuffer) / sizeof(TCHAR) - _tcslen(szBuffer), lpFormat, args);
				va_end(args);

				OutputDebugString(szBuffer);
			}

			static void  PASCAL AgoraWriteLog(LPSTR lpFormat, ...){

				char szBuffer[1024] = { '\0' };
				va_list args;
				va_start(args, lpFormat);

				SYSTEMTIME st;
				GetLocalTime(&st);
				sprintf_s(szBuffer, "%04d%02d%02d:%02d%02d%02d [%s] ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, gStrInstance.data());

				_vsnprintf(szBuffer + strlen(szBuffer), sizeof(szBuffer) / sizeof(char) - strlen(szBuffer), lpFormat, args);
				va_end(args);

				gAgoraWawajiLog.write(szBuffer);
			}
		};

	}
}
