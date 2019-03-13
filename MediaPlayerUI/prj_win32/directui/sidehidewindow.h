/******************************************************************************
	模块名      : 贴边掩藏窗口类
	文件名      : SideHideWindow.h
	相关文件    : SideHideWindow.cpp
	文件实现功能: 实现主窗口的贴边隐藏
	作者        : 张振兴
	版本        : 1.0
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2011/11/10  1.0         张振兴        创建
	2013/11/05  2.0         缪钱勇        DUI
******************************************************************************/
#ifndef SIDE_HIDE_WINDOW_H
#define SIDE_HIDE_WINDOW_H

namespace DirectUICore {

// 主窗口贴边收缩模式
enum EmSideHideMode
{
    SIDEHIDE_NONE   = 0,  // 不收缩
    SIDEHIDE_TOP    = 1,  // 向上收缩
    SIDEHIDE_LEFT   = 2,  // 向左收缩
    SIDEHIDE_RIGHT  = 3,  // 向右收缩
	SIDEHIDE_BOTTOM = 4,  // 向下收缩
};
enum EmTaskBarSideMode
{
	TASKBAR_BOTTOM  = 0,   //在下方
	TASKBAR_TOP     = 1,   //在上边
	TASKBAR_LEFT    = 2,   //在左边
	TASKBAR_RIGHT   = 3,   //在右边
	TASKBAR_HIDE    = 4,   //任务栏隐藏状态
};

//框架类
class DIRECTUI_API CSideHideWindow : public CAppWindow
{
public:
	CSideHideWindow( STRINGorID strUI, unsigned int dwTransparent = 255, bool bDeleteSelf = true );
	virtual ~CSideHideWindow( void );

public:
	// 默认回调函数
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual LRESULT OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

	// bEnable-TRUE，使能贴边掩藏；bEnable-FALSE，取消贴边掩藏
	void EnableSideHide( BOOL bEnable ); 
	// bCancelTop-TRUE，取消置顶；bCancelTop-FALSE，不取消置顶
	void IsCancelTop( BOOL bCancelTop ){ m_bCancelTop = bCancelTop; }
	EmSideHideMode GetSideHideMode();    // 获取贴边掩藏模式
 
	// 注意：在使能贴边掩藏和取消贴边掩藏之间切换时，在调用EnableSideHide()接口的函数中，入口处调用该
	// 函数(传入FALSE参数)，出口处调用该函数(传入TRUE参数)，保证切换时不会因为窗口失去激活状态时引起的
	// 掩藏异常, 2011/12/22 (此方法比较牵强，有待优化)
	// QQ、飞信等不会有这种异常，因为它们不需要在使能贴边掩藏和取消贴边掩藏之间切换
	void EnableInactiveWndHide( BOOL bEnable );
    void UpdateTaskBarSideMode(); //获取任务栏位置
	CRect GetWorkArea(); //获取工作区位置
	EmTaskBarSideMode GetTaskBarSideMode(){ return m_emTaskBarSideMode; }
	void SetEdgeHeight( int nEdgeHeight ){ m_nEdgeHeight = nEdgeHeight; }
	int GetEdgeHeight() { return m_nEdgeHeight; }
	void SetEdgeWidth( int nEdgeWidth ){ m_nEdgeWidth = nEdgeWidth; }
	BOOL IsHide() { return m_bHide; }
	void SetHide(bool bHide) { m_bHide = bHide; }

protected:
	virtual void DoShowWnd();  // 显示窗口
	virtual void DoHideWnd();  // 掩藏窗口

private:
	void FixMoving(LPRECT lpRect ); // 根据窗口拖动时的鼠标位置来判断是否要贴边掩藏
	BOOL HasRunningMenu();
	
private:
	int  m_nEdgeHeight;   // 边缘高度(向上收缩会用到)
	int  m_nEdgeWidth;    // 边缘宽度(向左和向右收缩会用到) 

	EmSideHideMode m_emSideHideMode;  // 主窗口收缩模式

	EmTaskBarSideMode m_emTaskBarSideMode; //任务栏的位置
	CRect m_rcWorkArea;

	BOOL m_bEnableSideHide;      // 使能/取消贴标掩藏标识(TRUE-使能贴边掩藏，FALSE-取消贴边掩藏)
	BOOL m_bCancelTop;           // 是否取消置顶标识(TRUE-取消置顶，FALSE-不取消置顶)
	BOOL m_bMouseDetectTimerSet; // 鼠标检测定时器是否开启(检测鼠标是否在主窗口内)
	BOOL m_bHide;                // 窗口是否掩藏
	BOOL m_bMainWndSizeChanged;  // 窗口大小是否改变，如果已经改变则要将收缩前的窗口高度记录到m_dwOldMainWndHeight变量中
	BOOL m_bEnableInactiveWndHide; // 使能窗口在失去激活状态时的掩藏动作，用来规避在使能贴边掩藏和取消贴边掩藏之间切换时的异常

	int m_nOldMainWndHeight;     // 向左或向右收缩前的窗口高度(退出贴边收缩状态后，窗口要变回原来大小)
};

}
#endif