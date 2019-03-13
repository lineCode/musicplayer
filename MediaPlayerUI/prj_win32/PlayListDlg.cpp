/******************************************************************************
	模块名      : mediaplay
	文件名      : PlayListDlg.cpp
	相关文件    : PlayListDlg.h
	文件实现功能: 播放队列对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#include "PlayListDlg.h"

BEGIN_UI_MSG_MAP(CPlayListDlg,CAppWindow)
	MSG_CLICK(_T("CloseBtn"),OnClose)
END_UI_MSG_MAP()

CPlayListDlg::CPlayListDlg( STRINGorID strUI, unsigned int dwTransparent, bool bDeleteSelf)
:CAppWindow( strUI, dwTransparent, bDeleteSelf)
,m_pLisPlay(NULL)
{

}

CPlayListDlg::~CPlayListDlg(void)
{

}

/*=========================================================================
	函数名		: CPlayListDlg::AddListElement
	功能		: 向播放列表中添加List项
	引用全局变量: 
	参数		: pControl 添加进播放列表的控件
	返回值		: 
=========================================================================*/ 
void CPlayListDlg::AddListElement(CControlUI* pControl)
{
	if(pControl)
		m_pLisPlay->AddAt( pControl, m_pLisPlay->GetCount());
}

bool CPlayListDlg::Notify( TNotifyUI& msg )
{
	return CAppWindow::Notify(msg);
}

void CPlayListDlg::Init()
{
	m_pLisPlay = static_cast<CListUI*>(m_pm.FindControl(_T("PlayLis")));
	ASSERT(m_pLisPlay);
}
	
bool CPlayListDlg::OnClose(TNotifyUI& msg)
{
	ShowWindow(false);
	return true;
}

LRESULT CPlayListDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = FALSE;//此参数暂时无作用
	switch(uMsg)
	{
	case WM_KILLFOCUS:
		{
			lRes=OnKillFocus( uMsg, wParam, lParam, bHandled);
		}
		break;

	default:
		break;
	}

	return CAppWindow::HandleMessage( uMsg, wParam, lParam);
}

LRESULT CPlayListDlg::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	//对话框焦点消失用于隐藏对话框
	ShowWindow(false);
	bHandled = FALSE;
	return 0L;
}