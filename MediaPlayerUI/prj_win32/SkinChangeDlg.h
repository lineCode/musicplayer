/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : SkinChangeDlg.h
	����ļ�    : 
	�ļ�ʵ�ֹ���: �����Ի���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#pragma once
#include "stdafx.h"

class CSkinChangeDlg: public CAppWindow
{
public:
	CSkinChangeDlg(STRINGorID strUI, unsigned int dwTransparent = 255
		, bool bDeleteSelf = true);
	~CSkinChangeDlg(void);
	
private:
	bool Notify( TNotifyUI& msg );
	void Init(void);

	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

protected:
	//CButtonUI
	CButtonUI* m_pBtnClose;
};

