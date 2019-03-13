/******************************************************************************
	模块名      : mediaplay
	文件名      : UserLoginDlg.cpp
	相关文件    : UserLoginDlg.h
	文件实现功能: 登录对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#include "UserLoginDlg.h"

CUserLoginDlg::CUserLoginDlg( STRINGorID strUI, unsigned int dwTransparent, bool bDeleteSelf):
CAppWindow( strUI, dwTransparent, bDeleteSelf)
,m_pBtnClose(NULL)
,m_pOptTaiheLogin(NULL)
,m_pOptBaiduLogin(NULL)
,m_pTabLoginPage(NULL)
{

}

CUserLoginDlg::~CUserLoginDlg(void)
{

}

bool CUserLoginDlg::Notify( TNotifyUI& msg )
{
	if(msg.sType == NOTIFY_BUTTONDOWN)
	{
		if(msg.pSender->GetName() == m_pBtnClose->GetName())
		{
			Close(0);
		}
		else
		{
			return false;
		}
	}
	if(msg.sType == NOTIFY_SELECT_CHANGED)
	{
		if(msg.pSender->GetName() == m_pOptBaiduLogin->GetName())
		{
			//选中百度帐号登录页面
			m_pTabLoginPage->SelectItem(0);
		}
		else if(msg.pSender->GetName() == m_pOptTaiheLogin->GetName())
		{
			//选中太和帐号登录页面
			m_pTabLoginPage->SelectItem(1);
		}
		else
		{
			return  false;
		}
	}
	return false;
}

void CUserLoginDlg::Init()
{
	//CButtonUI
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("CloseBtn")));
	ASSERT(m_pBtnClose);

	//CoptionUI
	m_pOptBaiduLogin = static_cast<COptionUI*>(m_pm.FindControl(_T("BaiduLoginOpt")));
	ASSERT(m_pOptBaiduLogin);
	m_pOptTaiheLogin = static_cast<COptionUI*>(m_pm.FindControl(_T("TaiheLoginOpt")));
	ASSERT(m_pOptTaiheLogin);

	//CTabLayoutUI
	m_pTabLoginPage = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("LoginPageTab")));
	ASSERT(m_pTabLoginPage);

}

