/******************************************************************************
	模块名      : mediaplay
	文件名      : PlayListDlg.h
	相关文件    : 
	文件实现功能: 播放队列对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#pragma once
#include "stdafx.h"

class CPlayListDlg: public CAppWindow
{
public:
	CPlayListDlg(STRINGorID strUI, unsigned int dwTransparent = 255
		, bool bDeleteSelf = true);
	~CPlayListDlg(void);

	//向播放列表中添加项
	void AddListElement(CControlUI* pControl);	
	
protected:
	bool OnClose(TNotifyUI& msg);
	DECLARE_UI_MSG_MAP()

private:

	//设置主界面类为友元类,对主界面开放内部权限
	friend class CMainWnd;			

	bool Notify( TNotifyUI& msg );
	void Init(void);
	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

private:
	//CLsitUI
	CListUI  *m_pLisPlay;
};