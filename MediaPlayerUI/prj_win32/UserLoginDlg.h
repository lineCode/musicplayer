/******************************************************************************
	模块名      : mediaplay
	文件名      : UserLoginDlg.h
	相关文件    : 
	文件实现功能: 登录对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
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