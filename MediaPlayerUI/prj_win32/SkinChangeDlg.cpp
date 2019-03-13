/******************************************************************************
	模块名      : mediaplay
	文件名      : SkinChangeDlg.cpp
	相关文件    : SkinChangeDlg.h
	文件实现功能: 换肤对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#include "SkinChangeDlg.h"
#include"MainWnd.h"

CSkinChangeDlg::CSkinChangeDlg( STRINGorID strUI, unsigned int dwTransparent, bool bDeleteSelf)
:CAppWindow( strUI, dwTransparent, bDeleteSelf)
,m_pBtnClose(NULL)
{

}

CSkinChangeDlg::~CSkinChangeDlg(void)
{

}

bool CSkinChangeDlg::Notify( TNotifyUI& msg )
{
	if(msg.sType == NOTIFY_BUTTONDOWN)
	{
		if(msg.pSender->GetName() == m_pBtnClose->GetName())
		{
			ShowWindow(false);
			return true;
		}
	}
	else if(msg.sType == NOTIFY_SELECT_CHANGED)
	{
		CStdString strName = msg.pSender->GetName();
		strName = strName.Mid(8,-1);
		strName.Format(_T(".\\resxml\\skin\\main_bg%s.png"),strName);
		
		CMainWnd::m_pBkCtrl->SetBkImage(strName);
	}

	return false;
}

void CSkinChangeDlg::Init()
{
	//CButtonUI
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("CloseBtn")));
	ASSERT(m_pBtnClose);
}

LRESULT CSkinChangeDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = FALSE;//此参数暂时无作用
	switch(uMsg)
	{
	case WM_KILLFOCUS:
		{
			lRes = OnKillFocus( uMsg, wParam, lParam, bHandled);
		}
		break;

	default:
		break;
	}

	return CAppWindow::HandleMessage( uMsg, wParam, lParam);
}

LRESULT CSkinChangeDlg::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	//对话框焦点消失用于隐藏对话框
	ShowWindow(false);
	bHandled = FALSE;
	return 0L;
}