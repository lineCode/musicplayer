#ifndef __DUI_MANAGER_H__
#define __DUI_MANAGER_H__
#include <deque>
#include <vector>

namespace DirectUICore {

class CControlUI;

/////////////////////////////////////////////////////////////////////////////////////
// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040


/////////////////////////////////////////////////////////////////////////////////////
//

typedef struct tagTFontInfo
{
	HFONT hFont;             // 该字体的句柄
    CStdString sFontName;    // 字体名称
    int iSize;               // 字号
    bool bBold;              // 是否粗体
    bool bUnderline;         // 是否有下划线
    bool bItalic;            // 是否斜体
    TEXTMETRIC tm;           // 该字体的TEXTMETRIC信息
} TFontInfo;

typedef struct tagTImageInfo
{
    HBITMAP hBitmap;
    int nX;
    int nY;
    bool alphaChannel;
    CStdString sResType;
    DWORD dwMask;
	bool bGray;
} TImageInfo;

// Structure for relative position to the parent
typedef struct tagTRelativePosUI
{
	bool bRelative;
	SIZE szParent;
	int nMoveXPercent;
	int nMoveYPercent;
	int nZoomXPercent;
	int nZoomYPercent;
}TRelativePosUI;


// 日志跟踪信息结构体
#if !COMMERCIAL_VERSION
typedef struct  tagNotifyUITracer
{
	time_t				m_tSendTime;		// 发送时间
	TNotifyUI			m_tNotifyUI;		// Notify信息
	CStdString			m_strSenderName;	// 消息发送控件Name(记录因为记录后此控件可能释放，后面不能再通过此指针取值)
	bool				m_bAys;				// 同步/异步

	HWND				m_hProcWnd;			// 控件所属窗口句柄
	CStdString			m_strProcWndClass;	// 控件所属窗口类名
	CStdString			m_strProcWndText;	// 控件所属窗口标题

	tagNotifyUITracer()
		: m_tSendTime( 0 )
		, m_strSenderName( _T("") )
		, m_bAys( false )
		, m_hProcWnd( NULL )
		, m_strProcWndClass( _T("") )
		, m_strProcWndText( _T("") )
	{
	}
}TNotifyUITracer, *PTNotifyUITracer;
#endif


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);


class DIRECTUI_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

	// 日志跟踪列表
#if !COMMERCIAL_VERSION	
	static std::deque<TNotifyUITracer> m_deqNotify;
#endif


public:
	// 绘图管理器的初始化(m_hWndPaint,m_hDcPaint赋值，在预处理消息中加入管理器)
    void Init( HWND hWnd );
	// 当前需要更新界面
    void NeedUpdate();
	// 指定区域无效
    void Invalidate( RECT& rcItem );
	// 获取绘图设备DC
    HDC GetPaintDC() const;
	// 获取绘图的窗口句柄
    HWND GetPaintWindow() const;
	// 获取提示窗口句柄
    HWND GetTooltipWindow() const;
	// 获取当前鼠标位置
    POINT GetMousePos() const;
	// 获取客户区大小
    SIZE GetClientSize() const;
	// 获取窗口初始化时的大小
    SIZE GetInitSize();
	// 设置窗体初始化大小
    void SetInitSize( int cx, int cy );
	// 设置窗体大小
	void SetSize( int cx, int cy );
	// 获取窗体的边框区域大小
    RECT& GetSizeBox();
	// 设置窗体的边框区域大小
    void SetSizeBox( RECT& rcSizeBox );
	// 获取标题区域大小
    RECT& GetCaptionRect();
	// 设置标题区域大小
    void SetCaptionRect( RECT& rcCaption );
	// 获取窗体四角的圆角弧度
    SIZE GetRoundCorner() const;
	// 设置窗体四角的圆角弧度
    void SetRoundCorner( int cx, int cy );
	// 获取窗体可以调整到得最小的大小
    SIZE GetMinInfo() const;
	// 设置窗体可以调整到得最小的大小
    void SetMinInfo( int cx, int cy );
	// 获取窗体可以调整到得最大的大小
    SIZE GetMaxInfo() const;
	// 设置窗体可以调整到得最大的大小
    void SetMaxInfo( int cx, int cy );
	// 设置窗体的不透明度(0完全透明-255完全不透明)
    void SetTransparent( int nOpacity );
	// 设置绘图是否支持透明处理
    void SetBackgroundTransparent( bool bTrans );
	// 是否显示更新区域
    bool IsShowUpdateRect() const;
	// 设置是否显示更新
    void SetShowUpdateRect( bool show );
	// 是否阴影窗口
	bool IsShadow() const;
	// 设置阴影窗口
	void SetShadow( bool shadow );
	// TAB实现控件间切换
	void TabChange( std::vector<CControlUI*>& tabChangeControls );

	// 获取当前管理的实例句柄
    static HINSTANCE GetInstance();
	// 获得当前运行的实例的路径
    static CStdString GetInstancePath();
	// 获得当前的工作路径
    static CStdString GetCurrentPath();
	// 获取资源DLL的实例句柄
    static HINSTANCE GetResourceDll();
	// 获取资源的路径(以"\"结尾)
    static const CStdString& GetResourcePath();
	// 获取Zip资源的路径
    static const CStdString& GetResourceZip();
	// 获取资源索引文件名
	static const CStdString& GetResourceIndexFileName();

	static bool IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
	// 设置实例句柄
    static void SetInstance( HINSTANCE hInst );
	// 设置当前的工作路径
    static void SetCurrentPath( LPCTSTR pStrPath );
	// 设置当前的DLL资源的实例句柄
    static void SetResourceDll( HINSTANCE hInst );
	// 设置资源所在文件夹路径
    static void SetResourcePath( LPCTSTR pStrPath );
	// 设置Zip资源的路径(包括Zip文件名)
    static void SetResourceZip( LPVOID pVoid, unsigned int len );
    static void SetResourceZip( LPCTSTR pstrZip, bool bCachedResourceZip = false );
	static void SetResourceIndexFileName( LPCTSTR pStrIndexFileName );
	static void SetYaHei( bool bYaHei );

    static void GetHSL( short* H, short* S, short* L );
    static void SetHSL( bool bUseHSL, short H, short S, short L ); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
	static bool LoadPlugin( LPCTSTR pstrModuleName );
    static CStdPtrArray* GetPlugins();

	// 设置使用上级资源的绘图管理器
    bool UseParentResource( CPaintManagerUI* pm );
	//  获得上级资源绘图管理器
    CPaintManagerUI* GetParentResource() const;
	// 获取禁用状态的默认颜色
    DWORD GetDefaultDisabledColor() const;
	// 设置禁用状态的默认颜色
    void SetDefaultDisabledColor( DWORD dwColor );
	// 获取字体默认颜色
    DWORD GetDefaultFontColor() const;
	// 设置字体默认颜色
    void SetDefaultFontColor( DWORD dwColor );
	// 获取链接文字的默认字体颜色   
    DWORD GetDefaultLinkFontColor() const;
	// 设置链接文字的默认字体颜色   
    void SetDefaultLinkFontColor( DWORD dwColor );
	// 获取鼠标悬停于超链上的默认字体颜色
    DWORD GetDefaultLinkHoverFontColor() const;
	// 设置鼠标悬停于超链上的默认字体颜色
    void SetDefaultLinkHoverFontColor( DWORD dwColor );
	// 获取选中状体的默认背景颜色
    DWORD GetDefaultSelectedBkColor() const;
	// 设置选中状体的默认背景颜色
    void SetDefaultSelectedBkColor( DWORD dwColor );
	// 获取默认使用的字体信息
    TFontInfo* GetDefaultFontInfo();
	// 设置默认使用的字体信息
    void SetDefaultFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	//  获取用户自定义字体的数量(一般对应xml中Font的数量)
	DWORD GetCustomFontCount() const;
	// 向字体数组列表中插入字体资源
	HFONT AddFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// 向字体数组列表中插入字体资源
	HFONT AddFontAt( int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// 获取数组中指定下标的字体对象句柄
	HFONT GetFont( int index );
	// 字体数组集合中是否存在指定配置的字体对象
    HFONT GetFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// 字体数组集合中是否存在字体对象
	bool FindFont( HFONT hFont );
	// 字体数组集合中是否存在指定配置的字体对象
	bool FindFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// 获得字体对象的索引
	int GetFontIndex( HFONT hFont );
	// 根据指定的配置信息查询字体索引
	int GetFontIndex( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// 从字体数组列表中移除字体对象
	bool RemoveFont( HFONT hFont );
	// 从字体数组列表中移除指定位置的字体信息
    bool RemoveFontAt( int index );
	// 清空字体数组列表
    void RemoveAllFonts();
	// 通过字体数组索引查找字体信息
    TFontInfo* GetFontInfo( int index );
	// 通过字体对象句柄获取字体信息
    TFontInfo* GetFontInfo( HFONT hFont );

	// 根据图像路径查找图像信息
    const TImageInfo* GetImage( LPCTSTR bitmap );
	// 根据名称,类型，遮罩色 查询 图像信息
    const TImageInfo* GetImageEx( LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGrey = false );
    // 添加图像
	const TImageInfo* AddImage( LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGray = false  );
    const TImageInfo* AddImage( LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha );
	// 根据图像名称移除图像
	bool RemoveImage( LPCTSTR bitmap );
	// 移除所有图像
    void RemoveAllImages();
	// 重新加载所有图像
    void ReloadAllImages();

	// 添加控件的默认配置信息(如button)
    void AddDefaultAttributeList( LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList );
	// 根据控件名称查询该类控件的默认配置
    LPCTSTR GetDefaultAttributeList( LPCTSTR pStrControlName ) const;
	// 移除指定控件类型名称的默认配置
    bool RemoveDefaultAttributeList( LPCTSTR pStrControlName );
	// 获取默认配置信息列表
    const CStdStringPtrMap& GetDefaultAttribultes() const;
	// 清空默认配置信息列表
    void RemoveAllDefaultAttributeList();

	// 将对话框控件附加到当前的管理器中
    bool AttachDialog( CControlUI* pControl );
	// 控件初始化
    bool InitControls( CControlUI* pControl, CControlUI* pParent = NULL );
	// 控件回收
    void ReapObjects( CControlUI* pControl );

	// 添加控件到指定的选项组
    bool AddOptionGroup( LPCTSTR pStrGroupName, CControlUI* pControl );
	// 查询指定选项组名称中的全部选项
    CStdPtrArray* GetOptionGroup( LPCTSTR pStrGroupName );
	// 从指定控件中移除指定选项组名称的选项组
    void RemoveOptionGroup( LPCTSTR pStrGroupName, CControlUI* pControl );
	// 清空全部选项组列表
    void RemoveAllOptionGroups();

	// 获取焦点状态的控件
    CControlUI* GetFocus() const;
	// 设置控件为获得焦点状态
    void SetFocus( CControlUI* pControl );
	// 设置控件为需要绘制焦点
    void SetFocusNeeded( CControlUI* pControl );
	void SetFocusNeeded( bool bFocusNeeded );

	// 设置下一个获得Tab键会获得焦点的控件，Tab是否继续往下走
    bool SetNextTabControl( bool bForward = true );

	// 为指定控件以及其子控件设置定时器
    bool SetTimer( CControlUI* pControl, UINT nTimerID, UINT uElapse );
	// 移除指定控件上的指定编号的定时器
    bool KillTimer( CControlUI* pControl, UINT nTimerID );
    void KillTimer( CControlUI* pControl );
	// 清空所有的定时器
    void RemoveAllTimers();

	// 设置窗体接受鼠标事件
    void SetCapture();
	// 释放窗体捕获鼠标事件
    void ReleaseCapture();
	//  判断窗体是否接受鼠标事件
    bool IsCaptured();

	// 添加控件到通知集合中
    bool AddNotifier( INotifyUI* pControl );
	// 将控件从通知集合中移除
    bool RemoveNotifier( INotifyUI* pControl );   
	// 发送同步/异步通知
    void SendNotify( TNotifyUI& Msg, bool bAsync = false );
	// 构建同步或异步通知并发送
    void SendNotify( CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false );

	// 向预处理消息过滤器链中添加消息过滤器
    bool AddPreMessageFilter( IMessageFilterUI* pFilter );
	// 从预处理消息过滤器链合中移除指定的消息过滤器
    bool RemovePreMessageFilter( IMessageFilterUI* pFilter );

	// 向消息过滤器链中添加消息过滤器
    bool AddMessageFilter( IMessageFilterUI* pFilter );
	// 从消息过滤器链中移除消息过滤器
    bool RemoveMessageFilter( IMessageFilterUI* pFilter );

	bool AddAnimJob( const CAnimJobUI& job );

	//  获取发送需要绘制的控件的数量
    int GetPostPaintCount() const;
	// 向绘制请求集合中添加要绘制的控件
    bool AddPostPaint( CControlUI* pControl );
	// 从绘制请求集合中移除指定的控件
    bool RemovePostPaint( CControlUI* pControl );
	// 将绘制请求控件插入到绘制请求集合的指定位置
    bool SetPostPaintIndex( CControlUI* pControl, int iIndex );
	// 向延迟清理集合中添加需要延迟清理的对象
    void AddDelayedCleanup( CControlUI* pControl );

	// 获取根节点控件
    CControlUI* GetRoot() const;
	// 从根节点开始查找指定点所在的控件
    CControlUI* FindControl( POINT pt ) const;
	// 从根节点开始，查找指定名称的控件
    CControlUI* FindControl( LPCTSTR pstrName ) const;
    CControlUI* FindSubControlByPoint( CControlUI* pParent, POINT pt ) const;
    CControlUI* FindSubControlByName( CControlUI* pParent, LPCTSTR pstrName ) const;
    CControlUI* FindSubControlByClass( CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0 );
    CStdPtrArray* FindSubControlsByClass( CControlUI* pParent, LPCTSTR pstrClass );
    CStdPtrArray* GetSubControlsByClass();

	bool AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool TranslateAccelerator(LPMSG pMsg);
	void CPaintManagerUI::UsedVirtualWnd(bool bUsed);
	// 消息循环，非游戏框架消息泵，无法利用无消息的空闲时间 
    static void MessageLoop();
	// 消息翻译，在Win32原有的消息转换基础上，将需要自己处理的消息转发给消息预处理器
    static bool TranslateMessage( const LPMSG pMsg );
	static void Term();

    bool MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );

	/************************************************************************/
	/*	消息预处理器														*/
	/*	1.消息预处理过滤(消息预处理过滤器集合对消息进行过滤处理)			*/
	/*	2.检查是否按下Tab键，设置下一个获得焦点的控件						*/
	/*	3.处理Alt+Shortcut Key按下后的控件获得焦点和激活的设置				*/
	/*	4.检查是否有系统键消息，有则发送获得焦点的控件的事件                */
	/************************************************************************/
    bool PreMessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );
	bool IsDropAvailable( POINT pt, CControlUI* pParent = NULL );

	void UsedWaterRoutine( bool bUsed ){ m_bUsedWaterRoutine = bUsed; }
	bool IsUsedWaterRoutine(){ return m_bUsedWaterRoutine; }
	HDC GetSourceDC(){ return m_hDcOffscreen; }
	HDC GetTargetDC(){ return m_hDcWaterRoutine; }
	HBITMAP GetSourceBitmap(){ return m_hbmpOffscreen; }
	HBITMAP GetTargetBitmap(){ return m_hBmpWaterRoutine; }

private:
	// 将所有的控件添加到m_mNameHash哈希表中
    static CControlUI* CALLBACK __FindControlFromNameHash( CControlUI* pThis, LPVOID pData );
	// 计算控件数量
	static CControlUI* CALLBACK __FindControlFromCount( CControlUI* pThis, LPVOID pData );
	// 根据点是否在区域中，查询控件
	static CControlUI* CALLBACK __FindControlFromPoint( CControlUI* pThis, LPVOID pData );
	// 通过Tab信息查询控件
	static CControlUI* CALLBACK __FindControlFromTab( CControlUI* pThis, LPVOID pData );
    // 从快照中查询控件
	static CControlUI* CALLBACK __FindControlFromShortcut( CControlUI* pThis, LPVOID pData );
    // 查询需要更新的控件
	static CControlUI* CALLBACK __FindControlFromUpdate( CControlUI* pThis, LPVOID pData );
    // 通过名称比较查询控件
	static CControlUI* CALLBACK __FindControlFromName( CControlUI* pThis, LPVOID pData );
    // 通过类名比较查询控件
	static CControlUI* CALLBACK __FindControlFromClass( CControlUI* pThis, LPVOID pData );
    static CControlUI* CALLBACK __FindControlsFromClass( CControlUI* pThis, LPVOID pData );

private:
	// 窗体句柄
    HWND m_hWndPaint;					// 控件布局窗口句柄 
	HWND m_hwndTooltip;					// 提示窗口句柄

	// 绘图设备
	HDC m_hDcPaint;						// 控件布局窗口设备DC 
	HDC m_hDcOffscreen;					// 离屏内存DC, 内存缓冲区绘图DC
	HDC m_hDcBackground;				// 背景内存DC, (支持AlphaBackground时使用)

	// 位图
    HBITMAP m_hbmpOffscreen;			// 离屏内存DC相关联HBITMAP 
	HBITMAP m_hbmpBackground;			// 背景内存DC相关联HBITMAP 

	// 控件信息
    CControlUI* m_pRoot;				// 如果控件是叠加的则存放最下层的控件对象,否则存放第一个创建的控件对象
    CControlUI* m_pFocus;				// 存放获得焦点的控件对象指针 
	CControlUI* m_pEventHover;			// 存放当前有鼠标移进移出事件的控件对象指针 
    CControlUI* m_pEventClick;			// 存放当前有点击事件的控件对象指针
    CControlUI* m_pEventKey;			// 存放当前有按键事件的控件对象指针
	
	// 位置记录信息
	POINT m_ptLastMousePos;				// 鼠标最新的位置
	SIZE m_szMinWindow;					// 设置窗体可以调整到的最小大小
	SIZE m_szMaxWindow;					// 窗体可以调整到的最大大小
	SIZE m_szInitWindowSize;			// 窗体初始化时的大小
	RECT m_rcSizeBox;					// 窗体外边框区域的大小
	SIZE m_szRoundCorner;				// 窗体四角的圆角弧度
	RECT m_rcCaption;					// 窗体标题栏区域大小
	UINT m_uTimerID;					// 当前定时器ID

	// 标识类信息 
	bool m_bShowUpdateRect;				// 是否显示更新区域
    bool m_bFirstLayout;				// 是否是首个布局
	bool m_bUpdateNeeded;				// 是否需要更新界面
	bool m_bFocusNeeded;				// 是否需要焦点
	bool m_bOffscreenPaint;				// 是否需要开双缓存绘图
	bool m_bAlphaBackground;			// 窗体背景是否需要支持Alpha通道(如png图片的半透明效果)
	bool m_bMouseTracking;				// 是否需要支持鼠标追踪
	bool m_bMouseCapture;				// 是否需要支持鼠标捕获
	bool m_bShadow;				        // 是否支持阴影窗口

	// 集合类信息
    CStdPtrArray m_aNotifiers;					// 记录所有需要事件通知的窗口,根据窗口名称调用相应的消息处理函数
	CStdPtrArray m_aTimers;						// 定时器集合
	CStdPtrArray m_aPreMessageFilters;			// 预处理消息集合
	CStdPtrArray m_aMessageFilters;				// 保存需要进行消息过滤的控件或功能(如动画类) 
	CStdPtrArray m_aPostPaintControls;			// 发送绘制请求的控件集合
	CStdPtrArray m_aDelayedCleanup;				// 延迟清理的对象集合
	CStdPtrArray m_aAsyncNotify;				// 异步通知消息集合
    CStdPtrArray m_aFoundControls;
	CStdStringPtrMap m_mNameHash;				// 保存控件对象指针hash表(用控件名称生成hash值) 
	CStdStringPtrMap m_mOptionGroup;			// 选项组Map
    
	// xml对应资源
	CPaintManagerUI* m_pParentResourcePM;		// 上级(父类)资源的PaintManagerUI绘图管理器
	DWORD m_dwDefaultDisabledColor;				// 默认失效状态颜色
	DWORD m_dwDefaultFontColor;					// 默认字体颜色
	DWORD m_dwDefaultLinkFontColor;				//  默认超链接字体颜色
	DWORD m_dwDefaultLinkHoverFontColor;		// 默认超链接鼠标悬停状态的字体颜色
	DWORD m_dwDefaultSelectedBkColor;			// 默认选中状态背景色
	TFontInfo m_DefaultFontInfo;				// 默认字体信息
    CStdPtrArray m_aCustomFonts;				// 自定义字体资源集合
    CStdStringPtrMap m_mImageHash;				// 图片资源的HashMap
    CStdStringPtrMap m_DefaultAttrHash;			// DefaultAttr资源HashMap
    
	//
	static HINSTANCE m_hInstance;				// 当前管理的Instance实例
	static HINSTANCE m_hResourceInstance;		// 当前管理的资源DLL Instance实例
	static CStdString m_pStrResourcePath;		// 当前使用的资源路径
	static CStdString m_pStrResourceZip;		// 当前使用的资源压缩包文件全称
	static CStdString m_pStrResIndexFileName;   // 当前使用的资源索引文件
	static bool m_bCachedResourceZip;
	static bool m_bYaHei;                       // 是否有微软雅黑
    static HANDLE m_hResourceZip;
    static short m_H;
    static short m_S;
    static short m_L;
    static CStdPtrArray m_aPreMessages;			// 预处理消息 
    static CStdPtrArray m_aPlugins;
	TOOLINFO m_ToolTip;

	bool m_bUsedVirtualWnd;
	CStdPtrArray m_aTranslateAccelerator;

	// 水波效果相关
	bool    m_bUsedWaterRoutine;
	HDC     m_hDcWaterRoutine;
	HBITMAP m_hBmpWaterRoutine;
};

} // namespace DirectUICore

#endif // __UIMANAGER_H__
