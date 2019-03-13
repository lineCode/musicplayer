/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : PlayListDlg.h
	����ļ�    : 
	�ļ�ʵ�ֹ���: ���Ŷ��жԻ���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#pragma once
#include "stdafx.h"

class CPlayListDlg: public CAppWindow
{
public:
	CPlayListDlg(STRINGorID strUI, unsigned int dwTransparent = 255
		, bool bDeleteSelf = true);
	~CPlayListDlg(void);

	//�򲥷��б��������
	void AddListElement(CControlUI* pControl);	
	
protected:
	bool OnClose(TNotifyUI& msg);
	DECLARE_UI_MSG_MAP()

private:

	//������������Ϊ��Ԫ��,�������濪���ڲ�Ȩ��
	friend class CMainWnd;			

	bool Notify( TNotifyUI& msg );
	void Init(void);
	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

private:
	//CLsitUI
	CListUI  *m_pLisPlay;
};