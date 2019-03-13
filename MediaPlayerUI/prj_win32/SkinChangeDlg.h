/******************************************************************************
	模块名      : mediaplay
	文件名      : SkinChangeDlg.h
	相关文件    : 
	文件实现功能: 换肤对话框
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
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

