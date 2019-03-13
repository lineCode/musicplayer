#ifndef __DUI_CONTROL_H__
#define __DUI_CONTROL_H__
#include <deque> 
#include <time.h>

namespace DirectUICore {

/////////////////////////////////////////////////////////////////////////////////////
// 此类定义了所有控件的可能具有的基本属性
//////////////////////////////////////////////////////////////////////////
class CControlUI;
typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

#if COMMERCIAL_VERSION
#else
typedef struct tagCtrlCrashTracer
{
	time_t  m_tDesTime;				// 控件获取时间
	void*	m_pCtrlPointer;			// 控件指针
	CStdString m_strCtrlName;		// 控件Name
	HWND	m_hOwnWnd;				// 控件所属窗口句柄
	CStdString m_strOwnWndClass;	// 控件所属窗口类名
	CStdString m_strOwnWndCaption;	// 控件所属窗口标题

	tagCtrlCrashTracer()
		: m_pCtrlPointer( NULL )
		, m_tDesTime( 0 )
		, m_strCtrlName( _T("") )
		, m_hOwnWnd( NULL )
		, m_strOwnWndClass( _T("") )
		, m_strOwnWndCaption( _T("") )
	{			
	}
}TCtrlCrashTracer, *PTCtrlCrashTracer;
#endif


class DIRECTUI_API CControlUI
{
public:
    CControlUI();
    virtual ~CControlUI();

#if COMMERCIAL_VERSION
#else
	static std::deque<TCtrlCrashTracer> m_deqTracer;
#endif

public:
	// 得到控件名称 名称为控件的唯一ID
    virtual CStdString GetName() const;
	// 设置控件名称
    virtual void SetName( LPCTSTR pstrName );
	// 得到控件类名
    virtual LPCTSTR GetClass() const;
	// 得到控件指针
    virtual LPVOID GetInterface( LPCTSTR pstrName );
	// 得到控件类型标志
    virtual UINT GetControlFlags() const;
	// 控件是否活跃 (非不可用状态，非不可见状态)
    virtual bool Activate();
	// 得到绘制管理者
    virtual CPaintManagerUI* GetManager() const;
	// 设置控件的绘制管理者（初始化）
    virtual void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );
    // 得到父控件
	virtual CControlUI* GetParent() const;

    // 得到控件显示内容
    virtual CStdString GetText() const;
	// 设置控件显示内容
    virtual void SetText( LPCTSTR pstrText );

	// * 背景色1,2,3用于渐变色 颜色渐变过程为1->2->3
    // 得到背景色
    DWORD GetBkColor() const;
	// 设置背景色
    void SetBkColor( DWORD dwBackColor) ;
	// 得到背景色 2
    DWORD GetBkColor2() const;
	// 设置背景色 2
    void SetBkColor2( DWORD dwBackColor );
	// 得到背景色 3
    DWORD GetBkColor3() const;
	// 设置背景色 3
    void SetBkColor3( DWORD dwBackColor );

	// 得到背景图片
    LPCTSTR GetBkImage();
	// 设置背景图片
    void SetBkImage( LPCTSTR pStrImage );
	// 得到边的颜色
    DWORD GetBorderColor() const;
	// 设置边的颜色
    void SetBorderColor( DWORD dwBorderColor );
	// 获取获得焦点时边的颜色
	DWORD GetFocusBorderColor() const;
	// 设置获得焦点时边的颜色
	void SetFocusBorderColor( DWORD dwBorderColor );
    bool IsColorHSL() const;
    void SetColorHSL( bool bColorHSL );

	// 得到边的宽度
    int GetBorderSize() const;
	// 设置边的宽度
    void SetBorderSize( int nSize );
	// 得到圆角
    SIZE GetBorderRound() const;
	// 设置圆角
    void SetBorderRound( SIZE cxyRound );
	// 绘制图片
    bool DrawImage( HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL );
	BOOL DrawButtonImage( HDC hDC, LPCTSTR pStrImage, int nCurState, int nStateCount, BOOL bPicSize = FALSE );
	bool DrawRectImage( HDC hDC, LPCTSTR pStrImage, RECT rc,  LPCTSTR pStrModify = NULL );

    // 得到控件位置
    virtual const RECT& GetPos() const;
	// 设置控件位置并重绘
    virtual void SetPos( RECT rc );
	// 得到控件宽度
    virtual int GetWidth() const;
	// 得到控件高度
    virtual int GetHeight() const;
	// 得到控件横坐标位置(左上点横坐标)
    virtual int GetX() const;
	// 得到控件纵坐标位置(左上点纵坐标)
    virtual int GetY() const;
	// 获取外边距
    virtual RECT GetPadding() const;
	// 设置外边距，由上层窗口绘制(求周围控件离它远点或近点(负值，不过受绘制顺序影响，比较少用)
    virtual void SetPadding( RECT rcPadding );
	// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual SIZE GetFixedXY() const;   
	// 仅float为true时有效
    virtual void SetFixedXY( SIZE szXY );
	// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual int GetFixedWidth() const; 
	// 预设的参考值
    virtual void SetFixedWidth( int cx ); 
	// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual int GetFixedHeight() const;        
    // 预设的参考值
	virtual void SetFixedHeight( int cy ); 
	// 预设的参考值
	virtual void SetBkImageWidth( int cx ); 
	virtual int GetBkImageWidth() const; 
	// 预设的参考值
	virtual void SetBkImageHeight( int cy ); 
	virtual int GetBkImageHeight() const; 

	// 设置大小的限制值
	virtual int GetMinWidth() const;
    virtual void SetMinWidth( int cx );
    virtual int GetMaxWidth() const;
    virtual void SetMaxWidth( int cx );
    virtual int GetMinHeight() const;
    virtual void SetMinHeight( int cy );
    virtual int GetMaxHeight() const;
    virtual void SetMaxHeight( int cy );

	// 设置相对位置比例
    virtual void SetRelativePos( SIZE szMove, SIZE szZoom );
	// 设置父控件大小
    virtual void SetRelativeParentSize( SIZE sz );
	// 得到相对位置比例
    virtual TRelativePosUI GetRelativePos() const;
	// 是否使用相对位置
    virtual bool IsRelativePos() const;

    // 获取/设置 提示信息
    virtual CStdString GetToolTip() const;
    virtual void SetToolTip( LPCTSTR pstrText );

	virtual int GetMaxTipWidth() const;
	virtual void SetMaxTipWidth( int nWidth );

	// 提示是否置顶显示，谨慎使用
	virtual bool IsToolTipTop() const{ return m_bToolTipTopMost; }
	virtual void SetToolTipTop( bool bTopMost ){ m_bToolTipTopMost = bTopMost; }

    // 获取/设置 快捷键
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut( TCHAR ch );

    // 获取/设置 上下文菜单是否被使用
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed( bool bMenuUsed );

    // 获取/设置 用户数据(字符串)
    virtual const CStdString& GetUserData();       // 辅助函数，供用户使用
    virtual void SetUserData( LPCTSTR pstrText );   // 辅助函数，供用户使用
	
	// 获取/设置 用户指针
	virtual UINT_PTR GetTag() const;               // 辅助函数，供用户使用
    virtual void SetTag( UINT_PTR pTag );           // 辅助函数，供用户使用

    // 获取/设置 控件是否可见
    virtual bool IsVisible() const;
    virtual void SetVisible( bool bVisible = true );
	// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
	// 有窗口句柄的UI在设置不可见时，需要先失去焦点
    virtual void SetInternVisible( bool bVisible = true );
    
	// 获取/设置 控件是否可用
	virtual bool IsEnabled() const;
    virtual void SetEnabled( bool bEnable = true );
	// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
	virtual void SetInternEnable( bool bEnable = true ); 

	// 获取/设置 是否处理鼠标事件
    virtual bool IsMouseEnabled() const;
    virtual void SetMouseEnabled( bool bEnable = true );

	virtual bool IsKeyboardEnabled() const;
    virtual void SetKeyboardEnabled( bool bEnable = true );

	// 控件是否获得焦点
    virtual bool IsFocused() const;
	// 设置控件获得焦点
    virtual void SetFocus();

	// 控件是否悬浮
    virtual bool IsFloat() const;
	// 设置控件为悬浮
    virtual void SetFloat( bool bFloat = true );

	// 强制Float时是否显示滚动条
	virtual bool IsFloatScroll() const;
	virtual void SetFloatScroll( bool bScroll = true );

	// 查找控件
    virtual CControlUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

	// 功能 - 设置无效,引起刷新
	// 实现 - 循环至顶层控件为止, 计算当前无效区域与父控件交叉区域作为新无效区域。
    virtual void Invalidate();

	// 获取/设置 需更新状态
    bool IsUpdateNeeded() const;
	void NeedUpdate( bool bNeed = true ); // 参数bNeed于2014/02/27新加的，极少数情况会用到该参数，基本都是使用默认参数true
	void NeedParentUpdate();

    DWORD GetAdjustColor( DWORD dwColor );

	// 初始化控件事件响应, 在SetManager()中被调用
    virtual void Init();
	// 做初始化处理函数, 被Init()调用
    virtual void DoInit();

	// 事件响应函数
    virtual void Event( TEventUI& event );
    virtual void DoEvent( TEventUI& event );

	// 设置属性, 根据解析后的名称对所关心的属性设置状态成员变量的值
    virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// 解析标签的属性字符串, 调用SetAttribute()
    CControlUI* ApplyAttributeList( LPCTSTR pstrList );

	// 预估控件大小
    virtual SIZE EstimateSize( SIZE szAvailable );

	// 功能 - 控件绘制
	// 实现 - 绘制循序：背景颜色->背景图->状态图->文本->边框
    virtual void DoPaint( HDC hDC, const RECT& rcPaint );
	// 绘制背景色
    virtual void PaintBkColor( HDC hDC );
	// 绘制背景图片
    virtual void PaintBkImage( HDC hDC );
	// 根据状态绘制背景图片
    virtual void PaintStatusImage( HDC hDC );
	// 绘制文字
    virtual void PaintText( HDC hDC );
	// 绘制边框
    virtual void PaintBorder( HDC hDC );

    virtual void DoPostPaint( HDC hDC, const RECT& rcPaint );

	// 设置控件是否可以接受拖动数据
	virtual bool IsDropAvailable();
	virtual void SetDropAvailable( bool bAvailable = true );

	// 将Control控件中的单个图片居中显示，可能需要对图片进行宽高的等比例缩放
	virtual void SetCenterImage( bool bCenterImage = true );
	virtual RECT CalcCenterImageRect( RECT& rc );

public:
	// 事件源 - 可以通过委托的设计模式为初始化，销毁，事件处理过程中加入更多的处理过程
    CEventSource OnInit;	// 初始化事件源
    CEventSource OnDestroy;	// 销毁事件源
    CEventSource OnSize;
    CEventSource OnEvent;	// 事件响应事件源
    CEventSource OnNotify;

protected:
	CPaintManagerUI* m_pManager;	// 窗口或控件绘图及消息管理器 
    CControlUI* m_pParent;			// 逻辑上的父窗口(控件)对象指针
    CStdString m_sName;				// 控件标识
    bool m_bUpdateNeeded;
    bool m_bMenuUsed;
    RECT m_rcItem;
    RECT m_rcPadding;
    SIZE m_cXY;                     // 由pos属性值得到的相对于父容器的左上角的坐标
    SIZE m_cxyFixed;                // 由pos属性值得到的当前控件的宽度和高度
    SIZE m_cxyMin;
    SIZE m_cxyMax;
	SIZE m_cxyBkImage;
    bool m_bVisible;
    bool m_bInternVisible;
	bool m_bInternEnabled;
    bool m_bEnabled;
    bool m_bMouseEnabled;
	bool m_bKeyboardEnabled;
	bool m_bDropAvailable;
	bool m_bCenterImage;                // 将Control控件中的单个图片居中显示，可能需要对图片进行宽高的等比例缩放
    bool m_bFocused;
    bool m_bFloat;
	bool m_bFloatScroll;
    bool m_bSetPos;						// 防止SetPos循环调用
    TRelativePosUI m_tRelativePos;

    CStdString m_sText;					// 控件显示标题或显示脚本字符串
	CStdString m_sToolTip;				// 控制的Tip信息
	DWORD	m_dwToolTipMaxWidth;		// ToolTip最大宽度(用于多行显示)
	bool m_bToolTipTopMost;
    TCHAR m_chShortcut;
    CStdString m_sUserData;
    UINT_PTR m_pTag;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    CStdString m_sBkImage;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
    bool m_bColorHSL;
    int m_nBorderSize;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;
};



// 日志跟踪打印类
class DIRECTUI_API CCrachTracer
{
public:
	void PrintControlDestructMap();
	void PrintNotifyMessage();
};

} // namespace DirectUICore

#endif // __UICONTROL_H__
