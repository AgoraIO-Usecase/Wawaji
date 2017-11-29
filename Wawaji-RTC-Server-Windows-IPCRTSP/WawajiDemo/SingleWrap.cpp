#include "stdafx.h"
#include "commonFun.h"
#include "SingleWrap.h"

CSingleCallBack::CSingleCallBack(HWND wnd) :wnd_(wnd)
{
}

CSingleCallBack::~CSingleCallBack()
{
	wnd_ = nullptr;
}

void CSingleCallBack::onReconnecting(uint32_t nretry)
{
	CString logMsg;
	logMsg.Format(_T("onReconnecting(%u)"),nretry);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_Reconnecting,WPARAM(pLog),LPARAM(nretry));
}

void CSingleCallBack::onReconnected(int fd)
{
	CString logMsg;
	logMsg.Format(_T("onReconnected(%d)"),fd);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_Reconnected,WPARAM(pLog),LPARAM(fd));
}

void CSingleCallBack::onLoginSuccess(uint32_t uid, int fd)
{
	CString logMsg;
	logMsg.Format(_T("onLoginSuccess(%u,%d)"),uid,fd);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_LoginSuccess,WPARAM(pLog),LPARAM(fd));
}

void CSingleCallBack::onLogout(int ecode)
{
	CString logMsg;
	logMsg.Format(_T("onLogout(%d)"),ecode);
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_LogOut,WPARAM(pLog),LPARAM(ecode));
}

void CSingleCallBack::onLoginFailed(int ecode)
{
	CString logMsg;
	logMsg.Format(_T("onLoginFailed(%d)"),ecode);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_LoginFailed,WPARAM(pLog),LPARAM(ecode));
}

void CSingleCallBack::onChannelJoined(char const * channelID, size_t channelID_size)
{
	CString logMsg;
	std::string channelID1 = gbk2utf8(channelID);
	channelID1 = utf82gbk(channelID);
	logMsg.Format(_T("onChannelJoined(%s,%u)"),s2cs(utf82gbk(channelID)),utf82gbk(channelID).size());
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelJoined,WPARAM(pLog));
}

void CSingleCallBack::onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode)
{
	CString logMsg;
	logMsg.Format(_T("onChannelJoinFailed(%s,%u,%d)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(),ecode);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelJoinedFailed,WPARAM(pLog));
}

void CSingleCallBack::onChannelLeaved(char const * channelID, size_t channelID_size, int ecode)
{
	CString logMsg;
	logMsg.Format(_T("onChannelLeaved(%s,%u,%d)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), ecode);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelLeaved,WPARAM(pLog));
}

void CSingleCallBack::onChannelUserJoined(char const * account, size_t account_size, uint32_t uid)
{
	CString logMsg;
	logMsg.Format(_T("onChannelUserJoined(%s,%d,%u)"),s2cs(utf82gbk(account)),utf82gbk(account).size(),uid);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelUserJoined,WPARAM(pLog));
}

void CSingleCallBack::onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid)
{
	CString logMsg;
	logMsg.Format(_T("onChannelUserLeaved(%s,%d,%u)"), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelUserLeaved,WPARAM(pLog));
}

void CSingleCallBack::onChannelUserList(int n, char** accounts, uint32_t* uids)
{
	std::string userList;
	userList.append("(");
	char** temp = accounts;
	for (int i = 0; i < n; i++)
	{
		userList.append(utf82gbk(*temp));
		userList.append(",");
		temp++;
	}
	userList.append(")");
	CString logMsg;
	logMsg.Format(_T("onChannelUserList(%d,%s,%u)"),n,s2cs(userList),*uids);
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelUserList,WPARAM(pLog));
}

void CSingleCallBack::onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num)
{
	CString logMsg;
	logMsg.Format(_T("onChannelQueryUserNumResult(%s,%u,%u,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), ecode, num);
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelQueryUserNumResult, WPARAM(pLog));
}

void CSingleCallBack::onChannelQueryUserIsIn(char const * channelID, size_t channelID_size, char const * account, size_t account_size, int isIn)
{
	postMsg(WM_ChannelQueryUserIsIn);
}

void CSingleCallBack::onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)
{
	CString logMsg;
	logMsg.Format(_T("onChannelAttrUpdated(%s,%u,%s,%u,%s,%u,%s,%u)"),s2cs(utf82gbk(channelID)),utf82gbk(channelID).size(),s2cs(utf82gbk(name)),utf82gbk(name).size(),s2cs(utf82gbk(value)),utf82gbk(value).size(),s2cs(utf82gbk(type)),utf82gbk(type).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_ChannelAttrUpdated,WPARAM(pLog));
}

void CSingleCallBack::onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	CString logMsg;
	logMsg.Format(_T("onInviteReceived(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid, s2cs(utf82gbk(extra)), utf82gbk(extra).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	std::string *accountParam = new std::string(account);

	postMsg(WM_InviteReceived,WPARAM(pLog),LPARAM(accountParam));
}

void CSingleCallBack::onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	CString logMsg;
	logMsg.Format(_T("onInviteReceivedByPeer(%s,%u,%s,%u,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid);
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteReceivedByPeer,WPARAM(pLog));
}

void CSingleCallBack::onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	CString logMsg;
	logMsg.Format(_T("onInviteAcceptedByPeer(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid,s2cs(utf82gbk(extra)),utf82gbk(extra).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteAcceptedByPeer,WPARAM(pLog));
}

void CSingleCallBack::onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	CString logMsg;
	logMsg.Format(_T("onInviteRefusedByPeer(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid,s2cs(utf82gbk(extra)),utf82gbk(extra).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteRefusedByPeer,WPARAM(pLog));
}

void CSingleCallBack::onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode, char const * extra, size_t extra_size)
{
	CString logMsg;
	logMsg.Format(_T("onInviteFailed(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid, s2cs(utf82gbk(extra)), utf82gbk(extra).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteFailed,WPARAM(pLog));
}

void CSingleCallBack::onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size)
{
	CString logMsg;
	logMsg.Format(_T("onInviteEndByPeer(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid, s2cs(utf82gbk(extra)), utf82gbk(extra).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteEndByPeer,WPARAM(pLog));
}

void CSingleCallBack::onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid)
{
	CString logMsg;
	logMsg.Format(_T("onInviteEndByMyself(%s,%u,%s,%u,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid);
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_InviteEndByMyself,WPARAM(pLog));
}

void CSingleCallBack::onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)
{
	postMsg(WM_InviteMsg);
}

void CSingleCallBack::onMessageSendError(char const * messageID, size_t messageID_size, int ecode)
{
	postMsg(WM_MessageSendError);
}

void CSingleCallBack::onMessageSendProgress(char const * account, size_t account_size, char const * messageID, size_t messageID_size, char const * type, size_t type_size, char const * info, size_t info_size)
{
	postMsg(WM_MessageSendProgress);
}

void CSingleCallBack::onMessageSendSuccess(char const * messageID, size_t messageID_size)
{
	CString logMsg;
	logMsg.Format(_T("onMessageSendSuccess(%s,%u)"), s2cs(utf82gbk(messageID)), utf82gbk(messageID).size());
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_MessageSendSuccess,WPARAM(pLog));
}

void CSingleCallBack::onMessageAppReceived(char const * msg, size_t msg_size)
{
	postMsg(WM_MessageAppReceived);
}

void CSingleCallBack::onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	CString logMsg;
	//logMsg.Format(_T("onMessageInstantReceive(%s,%u,%u,%s,%u)"), s2cs(utf82gbk(account)), utf82gbk(account).size(),uid,s2cs(utf82gbk(msg)),utf82gbk(msg).size());
	std::string* pLog = new std::string;
	//*pLog = cs2s(logMsg);
	*pLog = utf82gbk(msg);

	postMsg(WM_MessageInstantReceive,WPARAM(pLog),LPARAM(uid));
}

void CSingleCallBack::onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)
{
	CString logMsg;
	logMsg.Format(_T("onMessageChannelReceive(%s,%u,%s,%u,%u,%s,%u)"), s2cs(utf82gbk(channelID)), utf82gbk(channelID).size(), s2cs(utf82gbk(account)), utf82gbk(account).size(), uid, s2cs(utf82gbk(msg)), utf82gbk(msg).size());
	std::string* pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_MessageChannelReceive,WPARAM(pLog));
}

void CSingleCallBack::onLog(char const * txt, size_t txt_size)
{
	SendMessage(wnd_, WM_Log, WPARAM(utf82gbk(txt).c_str()),NULL);
}

void CSingleCallBack::onInvokeRet(char const * callID, size_t callID_size, char const * err, size_t err_size, char const * resp, size_t resp_size)
{
	postMsg(WM_InvokeRet);
}

void CSingleCallBack::onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size)
{
	postMsg(WM_Msg);
}

void CSingleCallBack::onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size)
{
	CString logMsg;
	logMsg.Format(_T("onUserAttrResult(%s,%u,%s,%u,%s,%u)"), s2cs(utf82gbk(account)), utf82gbk(account).size(), s2cs(utf82gbk(name)), utf82gbk(name).size(), s2cs(utf82gbk(value)), utf82gbk(value).size());
	std::string* pLog = new std::string;
	std::string slogMsg = cs2s(logMsg);
	*pLog = slogMsg;

	postMsg(WM_UserAttrResult,WPARAM(pLog));
}

void CSingleCallBack::onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size)
{
	CString logMsg;
	logMsg.Format(_T("onUserAttrAllResult(%s,%u,%s,%u)"),s2cs(utf82gbk(account)),utf82gbk(account).size(),s2cs(utf82gbk(value)),utf82gbk(value).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);

	postMsg(WM_UserAttrAllResult,WPARAM(pLog));
}

void CSingleCallBack::onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size)
{
	CString logMsg;
	logMsg.Format(_T("onError(%s,%u,%d,%s,%u)"),s2cs(utf82gbk(name)),utf82gbk(name).size(),ecode,s2cs(utf82gbk(desc)),utf82gbk(desc).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);
	logMsg.ReleaseBuffer();

	postMsg(WM_Error,WPARAM(pLog));
}

void CSingleCallBack::onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size)
{
	CString logMsg;
	logMsg.Format(_T("onQueryUserStatusResult(%s,%u,%s,%u)"),s2cs(utf82gbk(name)),utf82gbk(name).size(),s2cs(utf82gbk(status)),utf82gbk(status).size());
	std::string *pLog = new std::string;
	*pLog = cs2s(logMsg);
	logMsg.ReleaseBuffer();

	postMsg(WM_QueryUserStatusResult,WPARAM(pLog));
}

void CSingleCallBack::onDbg(char const * a, size_t a_size, char const * b, size_t b_size)
{
	postMsg(WM_Dbg);
}

void CSingleCallBack::onBCCall_result(char const * reason, size_t reason_size, char const * json_ret, size_t json_ret_size, char const * callID, size_t callID_size)
{
	postMsg(WM_BCCall_result);
}

void CSingleCallBack::postMsg(UINT msg, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
	::PostMessage(wnd_, msg, wParam, lParam);
}