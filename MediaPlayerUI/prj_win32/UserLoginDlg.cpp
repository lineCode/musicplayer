/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : UserLoginDlg.cpp
	����ļ�    : UserLoginDlg.h
	�ļ�ʵ�ֹ���: ��¼�Ի���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
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
			//ѡ�аٶ��ʺŵ�¼ҳ��
			m_pTabLoginPage->SelectItem(0);
		}
		else if(msg.pSender->GetName() == m_pOptTaiheLogin->GetName())
		{
			//ѡ��̫���ʺŵ�¼ҳ��
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

