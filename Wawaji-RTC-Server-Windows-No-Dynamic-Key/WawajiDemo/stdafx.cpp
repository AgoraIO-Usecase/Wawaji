
// stdafx.cpp : source file that includes just the standard includes
// AgoraWawajiDemo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "InfoManager.h"

CInfoManager pInfoManager;
CInfoManager* getInfoManager()
{
	return &pInfoManager;
}
