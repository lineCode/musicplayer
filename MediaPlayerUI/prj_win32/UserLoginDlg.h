/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : UserLoginDlg.h
	����ļ�    : 
	�ļ�ʵ�ֹ���: ��¼�Ի���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#pragma once
#include "stdafx.h"

class CUserLoginDlg:public CAppWindow
{
public:
	CUserLoginDlg( STRINGorID strUI, unsigned int dwTransparent = 255
		, bool bDeleteSelf = true);
	~CUserLoginDlg(void);

protected:
	bool Notify( TNotifyUI& msg );
	void Init(void);

protected:
	//CButtonUI
	CButtonUI *m_pBtnClose;

	//CoptionUI
	COptionUI *m_pOptBaiduLogin;
	COptionUI *m_pOptTaiheLogin;

	//CTabLayoutUI
	CTabLayoutUI *m_pTabLoginPage;
};