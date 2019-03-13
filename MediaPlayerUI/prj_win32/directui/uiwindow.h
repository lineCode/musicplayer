#ifndef __DUI_WINDOW_H__
#define __DUI_WINDOW_H__

namespace DirectUICore 
{

	// 窗体样式宏
#define UI_WNDSTYLE_CONTAINER  (0)																							// 容器样式，无任何样式  
#define UI_WNDSTYLE_FRAME      (WS_OVERLAPPEDWINDOW)															// UI标准框架窗体样式(标题栏、边框、图标、标题、最大、最小按钮、关闭按钮)
#define UI_WNDSTYLE_CHILD      (WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)									// UI窗体子控件样式
#define UI_WNDSTYLE_DIALOG     (WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN) // UI对话框窗体样式
#define UI_WNDSTYLE_BOX        (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME )
	// 扩展窗体样式宏
#define UI_WNDSTYLE_EX_FRAME    (WS_EX_WINDOWEDGE)							// 窗体客户区凹陷样式
#define UI_WNDSTYLE_EX_DIALOG   (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)	// 工具栏窗口样式+模式对话框样式

	// 类样式宏
#define UI_CLASSSTYLE_CONTAINER  (0)													// 类容器样式
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)								// 水平、垂直大小改变时绘制
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)	// 水平、垂直大小改变时绘制、支持双击事件、保存窗体位图
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)	// 水平、垂直大小改变时绘制、支持双击事件、保存窗体位图

/////////////////////////////////////////////////////////////////////////////////////
// 窗口类
/////////////////////////////////////////////////////////////////////////////////////
class DIRECTUI_API CWindowWnd : public CNotifyUIImpl
{
public:
	CWindowWnd();
	// 获取窗口句柄
	HWND GetHWND() const;
	operator HWND() const;
	HWND m_hWnd;			// 窗体句柄，初始化为NULL

	BOOL IsWindowVisible() const;
	BOOL IsIconic() const;
	BOOL GetWindowRect(LPRECT lpRect) const;
	BOOL GetClientRect(LPRECT lpRect) const;
	void SetActiveWindow();
	BOOL SetForegroundWindow();
	BOOL FlashWindow(BOOL bInvert);
	void UpdateWindow();
	void Invalidate(BOOL bErase = TRUE);
	void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);

	bool IsMaxShow(){ return m_bMaxShow; }

	/************************************************************************/
	/*	注册窗口过程														*/
	/*	1.调用GetClassStyle获取样式信息										*/
	/*	2.调用绘图管理器的静态函数获取实例CPaintManagerUI::GetInstance()	*/
	/*	3.调用GetWindowClassName()获取要注册的类名称                        */
	/************************************************************************/
	bool RegisterWindowClass();
	// 通过已存在的窗体作为父类注册窗口类
	bool RegisterSuperclass();
	// 窗口创建
	HWND Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL );
	/************************************************************************/
	/* 	创建窗口															*/
	/*	1.如果存在父类名，就用注册父类来创建								*/
	/*	2.不存在父类名，进行正常的窗口注册									*/
	/*	3.以上注册成功后，创建窗口                                          */
	/************************************************************************/
	HWND Create( HWND hwndParent, LPCTSTR pstrName
			  , DWORD dwStyle, DWORD dwExStyle
			  , int x = CW_USEDEFAULT, int y = CW_USEDEFAULT
			  , int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT
			  , HMENU hMenu = NULL );
	// 窗口子类化
	HWND Subclass( HWND hWnd );
	// 卸载窗口子类化
	void Unsubclass();
	// 显示窗口
	void ShowWindow( bool bShow = true, bool bTakeFocus = false );
	// 显示模式窗口
	UINT ShowModal();
	// 关闭窗口
	void Close( UINT nRet = IDOK );
	// 窗口居中，如果为子窗口，则居于父窗口的中央
	void CenterWindow();
	// 通过资源ID号设置图标
	void SetIcon( UINT nRes );
	// 发送UI同步消息
	LRESULT SendMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
	// 投递UI异步消息
	LRESULT PostMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
	// 调整客户区大小
	void ResizeClient( int cx = -1, int cy = -1 );

	DECLARE_UI_MSG_MAP()

protected:
	// 获取窗口类名称，子类必须实现该纯虚函数
	virtual LPCTSTR GetWindowClassName() const = 0;	
	// 获取父类名称，用以子类化
	virtual LPCTSTR GetSuperClassName() const;		
	// 获得类样式
	virtual UINT GetClassStyle() const;						
	// 消息处理函数
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );	
	// 窗体销毁前最后的处理工作
	virtual void OnFinalMessage( HWND hWnd );									
	//  窗口过程回调函数
	static LRESULT CALLBACK __WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	// 控件过程回调函数
	static LRESULT CALLBACK __ControlProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	// add by zlg 2014/02/24
	void DestroyWindow();

protected:
	WNDPROC m_OldWndProc;	// Win32窗口过程，默认为DefWindowProc
	HWND m_hWndParent;
	bool m_bSubclassed;		// 是否子类化，默认为false
	bool m_bMaxShow;
};
} // namespace DirectUICore

#endif // __UIWINDOW_H__