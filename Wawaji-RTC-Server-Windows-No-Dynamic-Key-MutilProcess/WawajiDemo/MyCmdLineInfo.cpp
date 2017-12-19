#include "stdafx.h"
#include "MyCmdLineInfo.h"
#include "InfoManager.h"
#include "commonFun.h"

CMyCmdLineInfo::CMyCmdLineInfo()
{

}

CMyCmdLineInfo::~CMyCmdLineInfo()
{

}

void CMyCmdLineInfo::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag && bLast){
		getInfoManager()->setCurSection(cs2s(pszParam));
	}
}