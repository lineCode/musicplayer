/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : PlayListDlg.cpp
	����ļ�    : PlayListDlg.h
	�ļ�ʵ�ֹ���: ���Ŷ��жԻ���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
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
	������		: CPlayListDlg::AddListElement
	����		: �򲥷��б������List��
	����ȫ�ֱ���: 
	����		: pControl ��ӽ������б�Ŀؼ�
	����ֵ		: 
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
	BOOL bHandled = FALSE;//�˲�����ʱ������
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
	//�Ի��򽹵���ʧ�������ضԻ���
	ShowWindow(false);
	bHandled = FALSE;
	return 0L;
}