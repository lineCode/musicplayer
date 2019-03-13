/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : SkinChangeDlg.cpp
	����ļ�    : SkinChangeDlg.h
	�ļ�ʵ�ֹ���: �����Ի���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
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
	BOOL bHandled = FALSE;//�˲�����ʱ������
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
	//�Ի��򽹵���ʧ�������ضԻ���
	ShowWindow(false);
	bHandled = FALSE;
	return 0L;
}