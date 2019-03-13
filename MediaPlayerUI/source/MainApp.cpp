/******************************************************************************
	模块名      : mediaplay
	文件名      : MainApp.cpp
	相关文件    : 
	文件实现功能: 程序执行起始入口，创建显示主窗口
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#include"stdafx.h"
#include"MainWnd.h"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//为CPaintManagerUI设置实例句柄
	CPaintManagerUI::SetInstance(hInstance);

	//设置资源路径为实例路径
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	//为CSkinShadow设置实例句柄
	CSkinShadow::Initialize( hInstance );
	
	//设置背景阴影图片
	CSkinShadow::SetImage( IDB_SHDAW_BK, _T("png"), hInstance );

	//初始化com库(应用程序调用com库函数（除CoGetMalloc和内存分配函数）之前必须初始化com库)
	HRESULT Hr = ::CoInitialize(NULL);
    if (FAILED(Hr)) 
	{
		return 0;
	}

	//实例化主窗口类对象
	CMainWnd* m_pwnd = new CMainWnd(IDR_XML_MAIN_FRAM); 
	if( m_pwnd == NULL )
	{
		return 0;
	}

	//创建主窗口
	m_pwnd->Create( NULL, _T("百度音乐"), UI_WNDSTYLE_DIALOG
		, WS_EX_DLGMODALFRAME|WS_EX_LAYERED, 0, 0,1000,660);

	//主窗口居中
	m_pwnd->CenterWindow();

	//显示主窗口
	m_pwnd->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	return 0;
}